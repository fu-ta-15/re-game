//#############################################################################
//
// ���b�V������ [mesh.cpp]
// Author : SUZUKI FUUTA
//
//#############################################################################

//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "mesh3D.h"
#include "Dinput.h"
#include "renderer.h"
#include "manager.h"

//-----------------------------------------------------------------------------
//�@�}�N����`
//-----------------------------------------------------------------------------
#define POLYGON_VTX							(2)
#define ADD_SIDE_INDEX						(6 + (2 * m_nVertical))
#define ADD_VER_INDEX						(2 * m_nVertical)
#define DRAW_INDX							((m_nIdx-4))

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh3D::CMesh3D(Priority type) : CScene(type)
{
	// �����o�ϐ��̏�����
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMesh3D::~CMesh3D()
{

}

//=============================================================================
// ���b�V���̐���
//=============================================================================
CMesh3D * CMesh3D::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �|�C���^�ϐ�
	CMesh3D *pMesh = NULL;
	
	// NULL�`�F�b�N
	if (pMesh == NULL)
	{
		pMesh = new CMesh3D(OBJ_NONE);	// �C���X�^���X����
		pMesh->SetPos(pos);				// �ʒu
		pMesh->SetSize(size);			// �T�C�Y
		pMesh->SetSide(nSide);			// �����̐�
		pMesh->SetVertical(nVertical);	// �c���̐�
		pMesh->Init();					// ������
	}

	return pMesh;
}

//=============================================================================
// ���b�V���̐���
//=============================================================================
CMesh3D * CMesh3D::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, Priority nPriority)
{
	// �|�C���^�ϐ�
	CMesh3D *pMesh = NULL;

	// NULL�`�F�b�N
	if (pMesh == NULL)
	{
		pMesh = new CMesh3D(nPriority);	// �C���X�^���X����
		pMesh->SetPos(pos);				// �ʒu
		pMesh->SetSize(size);			// �T�C�Y
		pMesh->SetSide(nSide);			// �����̐�
		pMesh->SetVertical(nVertical);	// �c���̐�
		pMesh->Init();					// ������
	}

	return pMesh;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
HRESULT CMesh3D::CreateTexture(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̏���������
//=============================================================================
HRESULT CMesh3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	// �������_��
	m_nVtx = VertexCreate(m_nVertical, m_nSide);

	// �����C���f�b�N�X
	m_nIdx = IndexCreate(m_nVertical, m_nSide);

	// ���̏c���̐�
	int nVertical = (m_nVertical + 2);

	// ���̉����̐�
	int nSide = (m_nSide + 2);

	// �z��𓮓I�Ɋm��
	m_Vector = new D3DXVECTOR3*[nVertical];

	// �z��𓮓I�Ɋm��
	for (int nSize = 0; nSize < nVertical; nSize++)
	{
		m_Vector[nSize] = new D3DXVECTOR3[nSide];
	}

	// �z���񎟌��z��Ɋm��
	m_Nor = new D3DXVECTOR3[(((1 + m_nVertical) * 2) * (1 + m_nSide))];

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_3D) * m_nVtx),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL))) {
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �ʒu�̐ݒ�
	MeshSetPos(m_nVertical, m_nSide, m_pVtx);

	// ���Z�� 1.0f�ŌŒ�								
	MeshSetNor(m_pVtx);

	// �F�̐ݒ�
	MeshSetCol(m_pVtx);

	// �e�N�X�`���̒��_���W�̐ݒ�
	MeshSetTex(m_nVertical, m_nSide, m_pVtx);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nIdx - 2) * 3,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// �C���f�b�N�X���ւ̃|�C���^
	WORD *pIdx;

	// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// ���b�V���C���f�b�N�X
	MeshCreate(m_nVertical, m_nSide, pIdx);

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̏I������
//=============================================================================
void CMesh3D::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �폜
	Release();
}

//=============================================================================
// ���b�V���|���S���̍X�V����
//=============================================================================
void CMesh3D::Update(void)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �@���x�N�g���̌v�Z�Ɣ��f
	MeshNor();

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̕`�揈��
//=============================================================================
void CMesh3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 0,
		m_nVtx, 0, (m_nIdx - 4));
}

//=============================================================================
// ���b�V����h�炷����
//=============================================================================
void CMesh3D::MeshWave(const D3DXVECTOR3& center, int ntime, float fHeight, int nCycle)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		// ��̓_�̋������v�Z
		float Dicetan = getDistance(center.x, center.z, m_pVtx[nCnt].pos.x, m_pVtx[nCnt].pos.z);

		// ���炩�ɂȂ�悤�ɍ��������ꂼ��X�V
		m_pVtx[nCnt].pos.y = (fHeight) * sinf((2.0f * D3DX_PI) / nCycle * (ntime - Dicetan));
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̐��������@���_�ɔԍ��U�蕪��
//=============================================================================
HRESULT CMesh3D::MeshCreate(int nVertical, int nSide, WORD * pIdx)
{
	// �J�E���g�p�ϐ�
	int nT = 0, nCnt = 0;

	// ���_�̃J�E���g�ϐ�
	int nCntVertical = (2 + nVertical), nCntSide = (2 + nSide);

	// �܂�Ԃ��̐��l
	int nWrapBack = 2 + nVertical;

	for (nCnt = 0; nCnt < m_nIdx; nCnt++)
	{
		if ((nCnt % 2) == 0)
		{
			if (nCntVertical != 0)
			{// �l�p�̏��̔ԍ�
				pIdx[nCnt] = nT + nWrapBack;
			}
			else
			{// �k�ރ|���S���p�̔ԍ�
				pIdx[nCnt] = nT - 1;
			}
		}
		else if ((nCnt % 2) == 1)
		{
			if (nCntVertical != 0)
			{// �l�p�̉���̔ԍ�
				pIdx[nCnt] = nT;

				// �J�E���g�A�b�v
				nT += 1;

				// ���Ɉ�i��
				nCntVertical -= 1;
			}
			else
			{// �k�ރ|���S���p�̔ԍ�
				pIdx[nCnt] = nT + nWrapBack;

				// �c�Ɉ�i��
				nCntSide -= 1;

				// �J�E���g��������
				nCntVertical = ((2 + nVertical));
			}
		}
	}

	return S_OK;	// ����������
}

//=============================================================================
// ���b�V���|���S���̃e�N�X�`�����W�ݒ�
//=============================================================================
void CMesh3D::MeshSetTex(int nVertical, int nSide, VERTEX_3D * pVtx)
{
	// ���̍Ō�̒l�̃i���o�[
	float nNumVertical = (1.0f + (float)nVertical), nNumSide = (1.0f + (float)nSide);

	// �J�E���g�p�ϐ�
	float nCntVertical = 0.0f, nCntSide = 0.0f;

	// �e�N�X�`�����W�U�蕪��
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{	// ���W�̑��
		pVtx[0].tex = D3DXVECTOR2((float)(nCntVertical / (nNumVertical)), (float)(nCntSide / nNumSide));

		// �[�����܂ŗ�����
		if (nCntVertical == nNumVertical)
		{
			// ���Ɉ�i��
			nCntSide += 1;

			// �O����̃X�^�[�g
			nCntVertical = 0;
		}
		else
		{
			// ���ɐi�߂�
			nCntVertical += 1;
		}
	}
}

//=============================================================================
// ���b�V���|���S���̈ʒu���̐ݒ�
//=============================================================================
void CMesh3D::MeshSetPos(int nVertical, int nSide, VERTEX_3D * pVtx)
{
	// ���̍Ō�̒l�̃i���o�[
	int nNumVertical = (1 + nVertical), nNumSide = (1 + nSide);

	// �J�E���g�p�ϐ�
	int nCntVertical = 0, nCntSide = 0;

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		// �e���_�ɍ��W����
		pVtx[nCnt].pos = D3DXVECTOR3((m_pos.x + ((m_size.x / nNumVertical) * nCntVertical)), 0.0f, (m_pos.z - ((m_size.z / nNumSide) * nCntSide)));

		// �[�����܂ŗ�����
		if (nCntVertical == nNumVertical)
		{
			// ���Ɉ�i��
			nCntSide += 1;

			// �O����̃X�^�[�g
			nCntVertical = 0;
		}
		else
		{
			// ���ɐi�߂�
			nCntVertical += 1;
		}
	}
}

//=============================================================================
// ���b�V���|���S���̖@���̌���
//=============================================================================
void CMesh3D::MeshSetNor(VERTEX_3D * pVtx)
{
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		// �e���_�ɖ@���x�N�g�����
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// ���b�V���|���S���̐F�ݒ�
//=============================================================================
void CMesh3D::MeshSetCol(VERTEX_3D * pVtx)
{
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		// �e���_�ɃJ���[�E�ԁE�΁E�E�A���t�@�𔽉f
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}

//=============================================================================
// ���b�V���|���S���̒��_�̌v�Z
//=============================================================================
int CMesh3D::VertexCreate(int nVertical, int nSide)
{
	// �|���S���̑������_��
	return ((nVertical + POLYGON_VTX) * (nSide + POLYGON_VTX));
}

//=============================================================================
// ���b�V���|���S���̕`��ԍ��̌v�Z
//=============================================================================
int CMesh3D::IndexCreate(int nVertical, int nSide)
{
	int nIdx = 0;

	nIdx = (((nVertical + 2) * (nSide + 1)) * 2) + ((nSide + 1) * 2);

	return nIdx;
}

//=============================================================================
// ���b�V���|���S���̊O�ςɂ��@���x�N�g���̌v�Z�ƍ���
//=============================================================================
void CMesh3D::MeshNor(void)
{
	// ���̍ő咸�_
	int nNumVertical = (1 + m_nVertical), nNumSide = (1 + m_nSide);

	// �J�E���g�p�ϐ�
	int	nCntVertical = 0, nCntSide = 0;

	// �@���̏�񂪕K�v�ɂȂ钸�_�̐�
	int	nNumNor = ((nNumVertical * 2) * nNumSide);

	// ���W�̕ۑ�
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		// ���W��񎟌��z��ɕۑ�
		m_Vector[nCntVertical][nCntSide] = m_pVtx[nCnt].pos;

		// �[�����܂ŗ�����
		if (nCntVertical == nNumVertical)
		{
			// ���Ɉ�i��
			nCntSide += 1;

			// �O����̃X�^�[�g
			nCntVertical = 0;
		}
		else
		{
			// ���ɐi�߂�
			nCntVertical += 1;
		}
	}

	// ���l���Z�b�g
	nCntSide = 0, nCntVertical = 0;

	// �e�|�C���g�̖@�����v�Z
	for (int nCntNor = 0; nCntNor < nNumNor; nCntNor += 1)
	{
		if ((nCntNor % 2) == 0)
		{
			m_Nor[nCntNor] = PolygonNormal(m_Vector[nCntVertical][nCntSide + 1], m_Vector[nCntVertical][nCntSide], m_Vector[nCntVertical + 1][nCntSide + 1]);
		}
		else if ((nCntNor % 2) == 1)
		{
			m_Nor[nCntNor] = PolygonNormal(m_Vector[nCntVertical + 1][nCntSide], m_Vector[nCntVertical + 1][nCntSide + 1], m_Vector[nCntVertical][nCntSide]);

			if (nCntVertical == (nNumVertical - 1))
			{
				nCntSide += 1;
				nCntVertical = 0;
			}
			else
			{
				nCntVertical += 1;
			}
		}
	}

	// ���l���Z�b�g
	nCntSide = 0, nCntVertical = 0;

	// �@���x�N�g���̍���
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		if (nCntSide == 0)
		{// ��ԏ�̃p�^�[��
			if (nCntVertical == 0)
			{
				m_pVtx[nCnt].nor = m_Nor[0] + m_Nor[1];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 2;
			}
			else if (nCntVertical == nNumVertical)
			{
				m_pVtx[nCnt].nor = m_Nor[(nCntVertical * 2) - 1];
			}
			else
			{
				m_pVtx[nCnt].nor = m_Nor[((nNumVertical * 2) * nCntSide) + (nCntVertical * 2) - 1] + m_Nor[((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)] + m_Nor[((nNumVertical * 2) * nCntSide) + (nCntVertical * 2) + 1];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 3;
			}
		}
		else if (nCntSide != 0 && nCntSide != nNumSide)
		{// �^�񒆂̃p�^�[��
			if (nCntVertical == 0)
			{
				m_pVtx[nCnt].nor = m_Nor[(((nNumVertical * 2) * nCntSide) - (nNumVertical * 2))] + m_Nor[((nNumVertical * 2) * nCntSide)] + m_Nor[(((nNumVertical * 2) * nCntSide) + 1)];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 3;
			}
			else if (nCntVertical == nNumVertical)
			{
				m_pVtx[nCnt].nor = m_Nor[(((nNumVertical * 2) * nCntSide) + (nNumVertical * 2) - 1)] + m_Nor[(((nNumVertical * 2) * nCntSide) - 1)] + m_Nor[(((nNumVertical * 2) * nCntSide) - 2)];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 3;
			}
			else
			{
				m_pVtx[nCnt].nor = m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2) + 2))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2) + 1))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2)))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - 1)] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) + 1)];

				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 6;
			}
		}
		else if (nCntSide == nNumSide)
		{// ��ԉ��̃p�^�[��
			if (nCntVertical == 0)
			{
				m_pVtx[nCnt].nor = m_Nor[(((nNumVertical * 2) * nCntSide) - (nNumVertical * 2))];
			}
			else if (nCntVertical == nNumVertical)
			{
				m_pVtx[nCnt].nor = m_Nor[(((nNumVertical * 2) * nCntSide) - 1)] + m_Nor[(((nNumVertical * 2) * nCntSide) - 2)];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 2;
			}
			else
			{
				m_pVtx[nCnt].nor = m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2)))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2) + 1))] +
					m_Nor[((((nNumVertical * 2) * nCntSide) + (nCntVertical * 2)) - ((nNumVertical * 2) + 2))];
				m_pVtx[nCnt].nor = m_pVtx[nCnt].nor / 3;
			}
		}

		// �[�����܂ŗ�����
		if (nCntVertical == nNumVertical)
		{
			// ���Ɉ�i��
			nCntSide += 1;

			// �O����̃X�^�[�g
			nCntVertical = 0;
		}
		else
		{
			// ���ɐi�߂�
			nCntVertical += 1;
		}
	}
}

//=============================================================================
// �|���S���ɂ��遢�̐����x�N�g�����O�ςɂ��v�Z�ŋ��߂鏈��
//=============================================================================
D3DXVECTOR3 CMesh3D::PolygonNormal(const D3DXVECTOR3 & pos0, const D3DXVECTOR3 & pos1, const D3DXVECTOR3 & pos2)
{
	// �v�Z�ۊǕϐ�
	D3DXVECTOR3 Pos01, Pos12, Normal;

	// �x�N�g�����v�Z
	Pos01 = (pos1 - pos0);
	Pos12 = (pos2 - pos0);

	// �e���W�̃x�N�g�����v�Z
	Normal.x = Pos01.y  * Pos12.z - Pos01.z * Pos12.y;
	Normal.y = Pos01.z  * Pos12.x - Pos01.x * Pos12.z;
	Normal.z = Pos01.x  * Pos12.y - Pos01.y * Pos12.x;

	// �v�Z���ʂ𐳋K������
	D3DXVec3Normalize(&Normal, &Normal);

	return Normal;
}

//=============================================================================
// �|�C���g�P�ƃ|�C���g�Q�̋���
//=============================================================================
float CMesh3D::getDistance(float x, float y, float x2, float y2)
{
	return sqrtf((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
}

