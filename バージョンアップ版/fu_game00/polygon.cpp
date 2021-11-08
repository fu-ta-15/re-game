//*****************************************************************************
//
// �|���S������ [polygon.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "polygon.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPolygon::CPolygon()
{
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_move = ZeroVector3;
	m_col = WhiteColor;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// �|���S���̃N���G�C�g
//=============================================================================
CPolygon * CPolygon::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CPolygon *pPolygon = new CPolygon;

	pPolygon->SetPos(pos);
	pPolygon->SetSize(size);
	pPolygon->Init(pos,size);

	return pPolygon;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CPolygon::CreateTexture(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTex);

	return S_OK;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CPolygon::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_bUse = true;

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

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{//���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_bUse == true)
	{
		//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTex);

		// �`��ݒ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CPolygon::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �T�C�Y�̐ݒ�
//=============================================================================
void CPolygon::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CPolygon::SetCol(const D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �e�N�X�`�����W�̍X�V
//=============================================================================
void CPolygon::SetTex(const D3DXVECTOR2 tex, const D3DXVECTOR2 fnumber)
{
	m_fAnimeX = fnumber.x;
	m_fAnimeY = fnumber.y;
	m_tex = tex;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(((m_fAnimeX + 0.0f) / m_tex.x), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(((m_fAnimeX + 0.0f) / m_tex.x), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(((m_fAnimeX + 1.0f) / m_tex.x), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(((m_fAnimeX + 1.0f) / m_tex.x), 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �|���S���̎g�p
//=============================================================================
void CPolygon::SetUse(bool bUse)
{
	m_bUse = bUse;
}

//=============================================================================
// X�T�C�Y�̕ύX
//=============================================================================
void CPolygon::SizeChangeX(float AddSize, POLYGON_MOVE type)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	switch (type)
	{
	case CPolygon::POLYGON_CENTER:
		// �e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x + AddSize, m_pos.y + m_size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x + AddSize, m_pos.y - m_size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x - AddSize, m_pos.y + m_size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x - AddSize, m_pos.y - m_size.y, 0.0f);
		break;

	case CPolygon::POLYGON_LIGHT:
		// �e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x - AddSize, m_pos.y + m_size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x - AddSize, m_pos.y - m_size.y, 0.0f);
		break;

	case CPolygon::POLYGON_LEFT:
		// �e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x + AddSize, m_pos.y + m_size.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_size.x + AddSize, m_pos.y - m_size.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
		break;

	default:
		break;
	}

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CPolygon::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �F�̎擾
//=============================================================================
D3DCOLOR CPolygon::GetCol(void)
{
	return m_col;
}
