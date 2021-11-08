//*****************************************************************************
//
// �����i�X�R�A��^�C���j���� [number.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "number.h"
#include "renderer.h"

//-----------------------------------------------------------------------------
// �ÓI�ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 CNumber::m_pTexture;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// �i���o�[�|���S���̐���
//=============================================================================
CNumber * CNumber::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const float fSplit)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		pNumber = new CNumber;

		pNumber->m_pos = pos;
		pNumber->m_size = size;
		pNumber->m_fSplit = fSplit;
		pNumber->Init();
	}

	return pNumber;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CNumber::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = WhiteColor;
	pVtx[1].col = WhiteColor;
	pVtx[2].col = WhiteColor;
	pVtx[3].col = WhiteColor;

	SetNumber(0);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CNumber::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{//���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Unload();
}

//=============================================================================
// �X�V����
//=============================================================================
void CNumber::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CNumber::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �`��ݒ�
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �ԍ��̐ݒ�
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2((((float)nNumber + 0.0f) / m_fSplit), 1.0f);
	pVtx[1].tex = D3DXVECTOR2((((float)nNumber + 0.0f) / m_fSplit), 0.0f);
	pVtx[2].tex = D3DXVECTOR2((((float)nNumber + 1.0f) / m_fSplit), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((((float)nNumber + 1.0f) / m_fSplit), 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �i���o�[�̃A�����[�h
//=============================================================================
void CNumber::Unload()
{
	if (m_pTexture != NULL)
	{//���_�o�b�t�@�̊J��
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// �i���o�[�̃��[�h
//=============================================================================
HRESULT CNumber::Load(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTexture);

	return S_OK;
}
