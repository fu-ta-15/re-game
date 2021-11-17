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

//-----------------------------------------------------------------------------
//�@�ÓI�����o�ϐ�
//-----------------------------------------------------------------------------


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh3D::CMesh3D(Priority type) : CScene(type)
{
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
	CMesh3D *pMesh = NULL;

	pMesh = new CMesh3D(OBJ_NONE);
	pMesh->SetPos(pos);
	pMesh->SetSize(size);
	pMesh->SetSide(nSide);
	pMesh->SetVertical(nVertical);
	pMesh->Init();

	return pMesh;
}

//=============================================================================
// ���b�V���̐���
//=============================================================================
CMesh3D * CMesh3D::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, Priority nPriority)
{
	CMesh3D *pMesh = NULL;

	pMesh = new CMesh3D(nPriority);
	pMesh->SetPos(pos);
	pMesh->SetSize(size);
	pMesh->SetSide(nSide);
	pMesh->SetVertical(nVertical);
	pMesh->Init();

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
HRESULT CMesh3D::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̏���������
//=============================================================================
HRESULT CMesh3D::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_nVtx = VertexCreate(m_nVertical, m_nSide);			// �������_��
	m_nIdx = IndexCreate(m_nVertical, m_nSide);				// �����C���f�b�N�X

	int nVertical = (m_nVertical + 2);
	int nSide = (m_nSide + 2);

	m_Vector = new D3DXVECTOR3*[nVertical];

	for (int nSize = 0; nSize < nVertical; nSize++)
	{
		m_Vector[nSize] = new D3DXVECTOR3[nSide];
	}

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

	MeshSetPos(m_nVertical, m_nSide, m_pVtx);		// �ʒu�̐ݒ�

	MeshSetRhw(m_pVtx);							// ���Z�� 1.0f�ŌŒ�

	MeshSetCol(m_pVtx);							// �F�̐ݒ�

	MeshSetTex(m_nVertical, m_nSide, m_pVtx);		// �e�N�X�`���̒��_���W�̐ݒ�

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * (m_nIdx-2)*3,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;	// �C���f�b�N�X���ւ̃|�C���^

				// �C���f�b�N�X�o�b�t�@�����b�N���A�ԍ��f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// ���b�V���C���f�b�N�X
	MeshCreate(m_nVertical, m_nSide, pIdx);

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;	// ����������
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
	Release();
}

//=============================================================================
// ���b�V���|���S���̍X�V����
//=============================================================================
void CMesh3D::Update(void)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	MeshNor();

	//D3DXVECTOR3 nor[8];
	//
	//nor[0] = PolygonNormal(m_pVtx[3].pos, m_pVtx[0].pos, m_pVtx[4].pos);
	//nor[1] = PolygonNormal(m_pVtx[1].pos, m_pVtx[4].pos, m_pVtx[0].pos);

	//nor[2] = PolygonNormal(m_pVtx[4].pos, m_pVtx[1].pos, m_pVtx[5].pos);
	//nor[3] = PolygonNormal(m_pVtx[2].pos, m_pVtx[5].pos, m_pVtx[1].pos);

	//nor[4] = PolygonNormal(m_pVtx[6].pos, m_pVtx[3].pos, m_pVtx[7].pos);
	//nor[5] = PolygonNormal(m_pVtx[4].pos, m_pVtx[7].pos, m_pVtx[3].pos);

	//nor[6] = PolygonNormal(m_pVtx[7].pos, m_pVtx[4].pos, m_pVtx[8].pos);
	//nor[7] = PolygonNormal(m_pVtx[5].pos, m_pVtx[8].pos, m_pVtx[4].pos);



	//m_pVtx[0].nor = (nor[0] + nor[1]) / 2;

	//m_pVtx[1].nor = (nor[1] + nor[3] + nor[2]) / 3;

	//m_pVtx[2].nor = (nor[3]);

	//m_pVtx[3].nor = (nor[0] + nor[5] + nor[4]) / 3;

	//m_pVtx[4].nor = (nor[0] + nor[1] + nor[2] + nor[7] + nor[6] + nor[5]) / 6;

	//m_pVtx[5].nor = (nor[2] + nor[3] + nor[7]) / 3;

	//m_pVtx[6].nor = (nor[4]);

	//m_pVtx[7].nor = (nor[4] + nor[5] + nor[6]) / 3;

	//m_pVtx[8].nor = (nor[6] + nor[7]) / 2;


	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̕`�揈��
//=============================================================================
void CMesh3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

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
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 0,
		m_nVtx, 0, DRAW_INDX);

}


void CMesh3D::MeshWave(const D3DXVECTOR3& center, int ntime, float fHeight, int nCycle)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		float Dicetan = getDistance(center.x, center.z, m_pVtx[nCnt].pos.x, m_pVtx[nCnt].pos.z);

		m_pVtx[nCnt].pos.y = (fHeight) * sinf((2.0f * D3DX_PI) / nCycle * (ntime - Dicetan));
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

void CMesh3D::MeshWave(const D3DXVECTOR3 & center, int ntime, int nCycle)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		float Dicetan = getDistance(center.x, center.z, m_pVtx[nCnt].pos.x, m_pVtx[nCnt].pos.z);

		m_pVtx[nCnt].pos.y += sinf((2.0f * D3DX_PI) / nCycle * (ntime - Dicetan));
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

void CMesh3D::MeshWave(int nID, int ntime, float fHeight)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		float Dicetan = getDistance(m_pVtx[nID].pos.x, m_pVtx[nID].pos.z, m_pVtx[nCnt].pos.x, m_pVtx[nCnt].pos.z);

		m_pVtx[nCnt].pos.y = fHeight * sinf((2.0f * D3DX_PI) / 50 * (ntime - Dicetan));
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

void CMesh3D::VtxPos(int nID, float fHeight)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);


	m_pVtx[nID].pos.y = fHeight;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

void CMesh3D::MeshCycleMove(void)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	float fRadiusX = 0.0f;
	float fRadiusY = 0.0f;
	float fAddX = 0.0f;
	float fAddY = 0.0f;
	int nCntVertical = 0;
	int nNumVertical = (1 + m_nVertical);
	int nNumSide = (1 + m_nSide);
	int nCntSide = 0;

	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		fRadiusX = m_moveRot.x * D3DX_PI / 90;
		fRadiusY = m_moveRot.y * D3DX_PI / 90;

		fAddX = sinf(fRadiusX) * ((m_size.x / (nNumVertical)) * nCntVertical);
		fAddY = cosf(fRadiusY) * ((m_size.x / (nNumVertical)) * nCntVertical);

		m_pVtx[nCnt].pos = D3DXVECTOR3(m_pos.x + fAddX, fAddY, (m_pos.z - ((m_size.z / nNumSide) * nCntSide)));

		if (nCntVertical == nNumVertical)
		{
			nCntSide += 1;
			nCntVertical = 0;
		}
		else
		{
			nCntVertical += 1;
		}

	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	m_moveRot.x++;
	m_moveRot.y++;
}

//=============================================================================
// ���b�V���|���S���̐��������@���_�ɔԍ��U�蕪��
//=============================================================================
HRESULT CMesh3D::MeshCreate(int nVertical, int nSide, WORD * pIdx)
{
	int nT = 0;
	int nCntSide = 2 + nSide;
	int nCntVertical = ((2 + nVertical));
	int nWrapBack = 2 + nVertical;
	int nCnt = 0;

	for (nCnt = 0; nCnt < m_nIdx; nCnt++)
	{
		if ((nCnt % 2) == 0)
		{
			if (nCntVertical != 0)
			{
				pIdx[nCnt] = nT + nWrapBack;
			}
			else
			{
				pIdx[nCnt] = nT - 1;
			}
		}
		else if ((nCnt % 2) == 1)
		{
			if (nCntVertical != 0)
			{
				pIdx[nCnt] = nT;
				nT += 1;
				nCntVertical -= 1;
			}
			else
			{
				pIdx[nCnt] = nT + nWrapBack;

				nCntSide -= 1;
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
	float nNumVertical = (1.0f + (float)nVertical);
	float nNumSide = (1.0f + (float)nSide);
	float nCntVertical = 0.0f;
	float nCntSide = 0.0f;

	// �e�N�X�`�����W�U�蕪��
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{	// ���W�̑��
		pVtx[0].tex = D3DXVECTOR2((float)(nCntVertical / (nNumVertical)), (float)(nCntSide / nNumSide));
		if (nCntVertical == nNumVertical)
		{// Y�i�ڂ�X�i���[�ɍs������
			nCntSide += 1;			// ��i������
			nCntVertical = 0.0f;	// X�����ɖ߂�
		}
		else
		{// X���܂��[�ɐU�蕪���ĂȂ���
			nCntVertical += 1;		// �P�i�߂�
		}
	}
}

//=============================================================================
// ���b�V���|���S���̈ʒu���̐ݒ�
//=============================================================================
void CMesh3D::MeshSetPos(int nVertical, int nSide, VERTEX_3D * pVtx)
{
	int nNumVertical = (1 + nVertical);
	int nNumSide = (1 + nSide);
	int nCntVertical = 0;
	int nCntSide = 0;

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3((m_pos.x + ((m_size.x / nNumVertical) * nCntVertical)),0.0f, (m_pos.z - ((m_size.z / nNumSide) * nCntSide)));

		if (nCntVertical == nNumVertical)
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

//=============================================================================
// ���b�V���|���S���̖@���̌���
//=============================================================================
void CMesh3D::MeshSetRhw(VERTEX_3D * pVtx)
{
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	}
}

//=============================================================================
// ���b�V���|���S���̐F�ݒ�
//=============================================================================
void CMesh3D::MeshSetCol(VERTEX_3D * pVtx)
{
	// ���_�J���[�E�ԁE�΁E�E�A���t�@
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}

//=============================================================================
// ���b�V���|���S���̒��_�̌v�Z
//=============================================================================
int CMesh3D::VertexCreate(int nVertical, int nSide)
{
	int nVtxVertical = POLYGON_VTX;
	int nVtxSide = POLYGON_VTX;
	int nVtx = 0;

	nVtx = 
		(nVertical + nVtxVertical) * (nSide + nVtxSide);


	return nVtx;
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

void CMesh3D::MeshNor(void)
{
	int nNumVertical = (1 + m_nVertical);
	int nNumSide = (1 + m_nSide);

	int nCntVertical = 0;
	int nCntSide = 0;

	int nNumNor = ((nNumVertical * 2) * nNumSide);

	int nXID1 = 0, nYID1 = 0;
	int nXID2 = 0, nYID2 = 0;
	bool bReturn = false;


	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		m_Vector[nCntVertical][nCntSide] = m_pVtx[nCnt].pos;

		if (nCntVertical == nNumVertical)
		{
			nCntSide += 1;
			nCntVertical = 0;
		}
		else
		{
			nCntVertical += 1;
		}
	}

	nCntSide = 0;
	nCntVertical = 0;

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

		//printf("\n %d X : %.3f Y : %.3f Z : %.3f\n", nCntNor, m_Nor[nCntNor].x, m_Nor[nCntNor].y, m_Nor[nCntNor].z);

	}

	nCntSide = 0;
	nCntVertical = 0;

	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		if (nCntSide == 0)
		{
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
		{
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
		{
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

		//printf("\n %d X : %.3f Y : %.3f Z : %.3f\n", nCnt,m_pVtx[nCnt].nor.x, m_pVtx[nCnt].nor.y, m_pVtx[nCnt].nor.z);

		if (nCntVertical == nNumVertical)
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

D3DXVECTOR3 CMesh3D::PolygonNormal(const D3DXVECTOR3 & pos0, const D3DXVECTOR3 & pos1, const D3DXVECTOR3 & pos2)
{
	D3DXVECTOR3 Pos01, Pos12;
	D3DXVECTOR3 Normal;


	Pos01 = (pos1 - pos0);
	Pos12 = (pos2 - pos0);

	Normal.x = Pos01.y  * Pos12.z - Pos01.z * Pos12.y;
	Normal.y = Pos01.z  * Pos12.x - Pos01.x * Pos12.z;
	Normal.z = Pos01.x  * Pos12.y - Pos01.y * Pos12.x;

	D3DXVec3Normalize(&Normal, &Normal);

	//printf("\n X : %.3f Y : %.3f Z : %.3f\n", Normal.x, Normal.y, Normal.z);


	return Normal;
}

float CMesh3D::getDistance(float x, float y, float x2, float y2)
{
	return sqrtf((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y));
}

