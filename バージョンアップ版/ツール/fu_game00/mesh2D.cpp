//#############################################################################
//
// ���b�V������ [mesh.cpp]
// Author : SUZUKI FUUTA
//
//#############################################################################

//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "mesh2D.h"
#include "Dinput.h"
#include "renderer.h"
#include "manager.h"

//-----------------------------------------------------------------------------
//�@�}�N����`
//-----------------------------------------------------------------------------
#define POLYGON_VTX							(2)
#define ADD_SIDE_INDEX						(6 + (2 * m_nVertical))
#define ADD_VER_INDEX						(2 * m_nVertical)
#define DRAW_INDX							(m_nIdx - 2)

//-----------------------------------------------------------------------------
//�@�ÓI�����o�ϐ�
//-----------------------------------------------------------------------------


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMesh::CMesh(int nPriority) : CScene((Priority)nPriority)
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
	m_pIdxBuff = NULL;
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
CMesh * CMesh::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CMesh *pMesh = NULL;

	pMesh = new CMesh(0);
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
CMesh * CMesh::Create(const int nVertical, const int nSide, const D3DXVECTOR3 pos, const D3DXVECTOR3 size,int nPriority)
{
	CMesh *pMesh = NULL;

	pMesh = new CMesh(nPriority);
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
HRESULT CMesh::CreateTexture(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTexture);

	return S_OK;
}

HRESULT CMesh::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;

	return S_OK;
}

//=============================================================================
// ���b�V���|���S���̏���������
//=============================================================================
HRESULT CMesh::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	m_nVtx = VertexCreate(m_nVertical, m_nSide);			// �������_��
	m_nIdx = IndexCreate(m_nVertical, m_nSide);				// �����C���f�b�N�X

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

	MeshSetPos(m_nVertical, m_nSide, m_pVtx);		// �ʒu�̐ݒ�

	MeshSetRhw(m_pVtx);							// ���Z�� 1.0f�ŌŒ�

	MeshSetCol(m_pVtx);							// �F�̐ݒ�

	MeshSetTex(m_nVertical, m_nSide, m_pVtx);		// �e�N�X�`���̒��_���W�̐ݒ�

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdx,
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
void CMesh::Uninit(void)
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
void CMesh::Update(void)
{
	
}

//=============================================================================
// ���b�V���|���S���̕`�揈��
//=============================================================================
void CMesh::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

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
		0, 0,
		m_nVtx, 0, DRAW_INDX);
}

//=============================================================================
// ���_�ɍ��W����
//=============================================================================
void CMesh::SetWavePos(int nID, float pos)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	m_pVtx[nID].pos.y = pos;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

void CMesh::SetVtxPosY(int nID, float posy)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	m_pVtx[nID].pos.y = posy;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

void CMesh::SetVtxPosX(int nID, float posx)
{
	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&m_pVtx, 0);

	m_pVtx[nID].pos.x = posx;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// ���b�V���|���S���̐��������@���_�ɔԍ��U�蕪��
//=============================================================================
HRESULT CMesh::MeshCreate(int nVertical, int nSide, WORD * pIdx)
{
	int nT = 0;
	int nCntSide = nSide;
	int nCntVertical = ((2 + nVertical));
	int nWrapBack = 2 + nVertical;
	int nCntPoly = 0;
	int nCnt = 0;

	for (nCnt = 0; nCnt < m_nIdx / 2; nCnt++)
	{
		if (nCntPoly == nWrapBack && nCntSide != 0)
		{
			pIdx[0] = nT - 1;
			pIdx[1] = nT + nWrapBack;

			nCntPoly = 0;
			nCntSide -= 1;
			nCntVertical = ((2 + nVertical));
			pIdx += 2;
		}
		else if (nCntSide == 0 && nCntVertical == 0)
		{
			break;
		}
		else
		{
			pIdx[0] = nT + nWrapBack;
			pIdx[1] = nT;

			nT += 1;
			nCntVertical -= 1;
			nCntPoly += 1;
			pIdx += 2;
		}
	}
	return S_OK;	// ����������
}

//=============================================================================
// ���b�V���|���S���̃e�N�X�`�����W�ݒ�
//=============================================================================
void CMesh::MeshSetTex(int nVertical, int nSide, VERTEX_2D * pVtx)
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
void CMesh::MeshSetPos(int nVertical, int nSide, VERTEX_2D * pVtx)
{
	int nNumVertical = (1 + nVertical);
	int nNumSide = (1 + nSide);
	int nCntVertical = 0;
	int nCntSide = 0;

	// �e���_�̍��W
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++)
	{
		pVtx[nCnt].pos = D3DXVECTOR3((m_pos.x + ((m_size.x / nNumVertical) * nCntVertical)), (m_pos.y + ((m_size.y / nNumSide) * nCntSide)), 0.0f);
		
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
void CMesh::MeshSetRhw(VERTEX_2D * pVtx)
{
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
	// ���_�J���[�E�ԁE�΁E�E�A���t�@
	for (int nCnt = 0; nCnt < m_nVtx; nCnt++, pVtx++)
	{
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
}

//=============================================================================
// ���b�V���|���S���̒��_�̌v�Z
//=============================================================================
int CMesh::VertexCreate(int nVertical, int nSide)
{
	int nVtxVertical = POLYGON_VTX;
	int nVtxSide = POLYGON_VTX;
	int nVtx = 0;

	nVtx = (nVertical + nVtxVertical) * (nSide + nVtxSide);

	return nVtx;
}

//=============================================================================
// ���b�V���|���S���̕`��ԍ��̌v�Z
//=============================================================================
int CMesh::IndexCreate(int nVertical, int nSide)
{
	int nIdx = 0;

	nIdx = 4 + (nSide * ADD_SIDE_INDEX) + ADD_VER_INDEX;

	return nIdx;
}










