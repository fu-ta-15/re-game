//#############################################################################
//
// ���b�V������ [mesh.cpp]
// Author : SUZUKI FUUTA
//
//#############################################################################
//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "mesh.h"
#include "Dinput.h"
#include "renderer.h"
#include "manager.h"
#include "move.h"

//-----------------------------------------------------------------------------
//�@�}�N����`
//-----------------------------------------------------------------------------
#define ADD_SIDE_INDEX						(6 + (2 * m_nVertical))		// �����̌v�Z
#define ADD_VER_INDEX						(2 * m_nVertical)			// �c���̌v�Z
#define DRAW_INDX							(m_nIdx - 3)				// �`�悷��Ƃ��̃|���S����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh::CMesh(Priority type) : CScene(type)
{
	m_pVtxBuff = NULL;	 // ���_�o�b�t�@�̃|�C���^
	m_pTexture = NULL;	 // �e�N�X�`���̃|�C���^
	m_pIdxBuff = NULL;	 // �C���f�b�N�X�o�b�t�@�̃|�C���^
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMesh::~CMesh()
{
}

//=============================================================================
// ���b�V���̐���
//=============================================================================
CMesh * CMesh::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, CScene::ObjectType type)
{
	// �N���X�̃|�C���^�ϐ�
	CMesh *pMesh = new CMesh(type);

	if (pMesh != NULL)
	{// NULL�`�F�b�N
		pMesh->Init(nVertical, nSide, pos, size);	// ������
	}

	return pMesh;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
HRESULT CMesh::CreateTexture(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTexture);

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̏���������
//=============================================================================
HRESULT CMesh::Init(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	// �ʒu
	m_pos = pos;

	// �T�C�Y
	m_size = size;

	// ���̏c���̐�
	m_nVertical = nVertical;

	// ���̉����̐�
	m_nSide = nSide;

	// �F�̏�����
	m_col = WhiteColor;

	// �ړ���
	m_move = ZeroVector3;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	// �������_��
	m_nVtx = VertexCreate(m_nVertical, m_nSide);

	// �����C���f�b�N�X
	m_nIdx = IndexCreate(m_nVertical, m_nSide);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer((sizeof(VERTEX_2D) * m_nVtx),
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
	MeshSetRhw(m_pVtx);

	// �F�̐ݒ�
	MeshSetCol(m_pVtx);

	// �e�N�X�`���̒��_���W�̐ݒ�
	MeshSetTex(m_nVertical, m_nSide, m_pVtx);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdx,
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
void CMesh::Uninit(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{// NULL�`�F�b�N
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{// NULL�`�F�b�N
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{// NULL�`�F�b�N
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �폜
	Release();
}

//=============================================================================
// ���b�V���|���S���̍X�V����
//=============================================================================
void CMesh::Update(void)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̕`�揈��
//=============================================================================
void CMesh::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 
		0,
		m_nVtx, 
		0, 
		DRAW_INDX);
}

//=============================================================================
// ���_�ɍ��W�����iY���W�j
//=============================================================================
void CMesh::SetVtxPosY(int nID, float posy)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ���W���
	m_pVtx[nID].pos.y = posy;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_�ɍ��W�����iX���W�j
//=============================================================================
void CMesh::SetVtxPosX(int nID, float posx)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// ���W���
	m_pVtx[nID].pos.x = posx;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���_���W�Ɉړ��ʂ����Z
//=============================================================================
void CMesh::SetMove(const D3DXVECTOR3 move)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		m_pVtx[nCnt].pos += move ;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̐��������@���_�ɔԍ��U�蕪��
//=============================================================================
HRESULT CMesh::MeshCreate(int nVertical, int nSide, WORD * pIdx)
{
	// �C���f�b�N�X�ɐU�蕪������ID
	int nIdxID = 0;

	// �T�C�h�̐�
	int nCntSide = nSide;

	// �c���̈��̑���
	int nCntVertical = ((2 + nVertical));	

	// �܂�Ԃ��̔ԍ�
	int nWrapBack = 2 + nVertical;		

	// �J�E���g�p�ϐ�
	int nCnt = 0;							

	for (nCnt = 0; nCnt < m_nIdx; nCnt++)
	{
		// �J�E���g����Ŋ����Ƃ�
		if ((nCnt % 2) == 0)
		{
			if (nCntVertical != 0)
			{
				// ���_�|���S���̔ԍ��L��
				pIdx[nCnt] = nIdxID + nWrapBack;
			}
			else
			{
				// �k�ރ|���S���̔ԍ�
				pIdx[nCnt] = nIdxID - 1;
			}
		}
		else if ((nCnt % 2) == 1)
		{
			if (nCntVertical != 0)
			{
				// ���_�|���S���̔ԍ��L��
				pIdx[nCnt] = nIdxID;

				// �c����i�߂�
				nIdxID += 1;
				nCntVertical -= 1;
			}
			else
			{
				// �k�ރ|���S���̔ԍ�
				pIdx[nCnt] = nIdxID + nWrapBack;

				// ������i�߂�
				nCntSide -= 1;
				nCntVertical = ((2 + nVertical));
			}
		}
	}

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̃e�N�X�`�����W�ݒ�
//=============================================================================
void CMesh::MeshSetTex(int nVertical, int nSide, VERTEX_2D * pVtx)
{
	float nNumVertical = (float)(1 + nVertical);	 // ��񕪂̏c���̑���
	float nNumSide = (float)(1 + nSide);			 // �����̐�
	float nCntVertical = 0.0f;						 // �c���̃J�E���g
	float nCntSide = 0.0f;							 // �����̃J�E���g

	// �e�N�X�`�����W�U�蕪��
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{	
		// ���W�̑��
		pVtx[0].tex = D3DXVECTOR2((float)(nCntVertical / (nNumVertical)), (float)(nCntSide / nNumSide));

		// Y�i�ڂ�X�i���[�ɍs������
		if (nCntVertical == nNumVertical)
		{
			// ��i������
			nCntSide += 1;			

			// X�����ɖ߂�
			nCntVertical = 0.0f;	
		}
		else
		{// X���܂��[�ɐU�蕪���ĂȂ���

			// �P�i�߂�
			nCntVertical += 1;		
		}
	}
}

//=============================================================================
// ���b�V���|���S���̈ʒu���̐ݒ�
//=============================================================================
void CMesh::MeshSetPos(int nVertical, int nSide, VERTEX_2D * pVtx)
{
	int nNumVertical = (1 + nVertical);	 // ��񕪂̏c���̑���
	int nNumSide = (1 + nSide);			 // �����̐�
	int nCntVertical = 0;				 // �c���̃J�E���g
	int nCntSide = 0;					 // �����̃J�E���g

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		// ���W��ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3((m_pos.x + ((m_size.x / nNumVertical) * nCntVertical)), (m_pos.y + ((m_size.y / nNumSide) * nCntSide)), 0.0f);
		
		// �[�܂ŃJ�E���g������
		if (nCntVertical == nNumVertical)
		{
			// ���ɂ��炷
			nCntSide += 1;

			// �J�E���g������
			nCntVertical = 0;
		}
		else
		{// �c���̃J�E���g�A�b�v
			nCntVertical += 1;
		}
	}
}

//=============================================================================
// ���b�V���|���S����
//=============================================================================
void CMesh::MeshSetRhw(VERTEX_2D * pVtx)
{
	// �e���_�ɏ��Z�����P�D�O�ŌŒ�
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		pVtx[0].rhw = 1.0f;
	}
}

//=============================================================================
// ���b�V���|���S���̐F�ݒ�
//=============================================================================
void CMesh::MeshSetCol(VERTEX_2D * pVtx)
{
	// �e���_�ɐF�̏�����
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		pVtx[0].col = m_col;
	}
}

//=============================================================================
// ���b�V���|���S���̒��_�̌v�Z
//=============================================================================
int CMesh::VertexCreate(int nVertical, int nSide)
{
	return (nVertical + 2) * (nSide + 2);
}

//=============================================================================
// ���b�V���|���S���̕`��ԍ��̌v�Z
//=============================================================================
int CMesh::IndexCreate(int nVertical, int nSide)
{
	return (((nVertical + 2) * (nSide + 1)) * 2) + ((nSide + 1) * 2);
}

