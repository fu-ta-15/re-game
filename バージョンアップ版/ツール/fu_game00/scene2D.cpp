//*****************************************************************************
//
// �V�[��2D���� [scene2D.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "scene2D.h"
#include "keyinput.h"

//=============================================================================
// �V�[���I�u�W�F�N�g�̃R���X�g���N�^
//=============================================================================
CScene2D::CScene2D(Priority type) : CScene(type)
{
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_size = ZeroVector3;
	m_move = ZeroVector3;
	m_col = WhiteColor;
	m_bUse = true;
	m_fAngle = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CScene2D * CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D(OBJ_NONE);
		pScene2D->m_bUse = true;
		pScene2D->Init(pos, size);
	}

	return pScene2D;
}

//=============================================================================
// �|���S���̐���
//=============================================================================
CScene2D * CScene2D::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, Priority type)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		pScene2D = new CScene2D(type);
		pScene2D->m_bUse = true;
		pScene2D->Init(pos, size);
	}

	return pScene2D;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CScene2D::CreateTexture(const LPCSTR pSrcFile)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &m_pTex);

	return S_OK;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CScene2D::Init(void)
{
	// �|���S���̃����o�ϐ��̒l���
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_rot = D3DXVECTOR3(45.0f, 45.0f, 0.0f);
	m_fAngle = atan2f(m_size.x, m_size.y);

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fAngle, m_pos.y + m_fAngle, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x - m_fAngle, m_pos.y - m_fAngle, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_fAngle, m_pos.y + m_fAngle, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fAngle, m_pos.y - m_fAngle, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

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
// �������i�ʒu�ƃT�C�Y�w��j
//=============================================================================
HRESULT CScene2D::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size)
{
	m_pos = pos;
	m_size = size;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

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
// �A�j���[�V�����t���������i�ʒu�ƃT�C�Y�w��j
//=============================================================================
HRESULT CScene2D::AnimationInit(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXVECTOR2 tex)
{
	m_pos = pos;
	m_size = size;
	m_fAnimeX = tex.x;
	m_fAnimeY = tex.y;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(CREATE_POLYGON, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL)))
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
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(((m_fAnimeX + 0.0f) / m_tex.x), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(((m_fAnimeX + 0.0f) / m_tex.x), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(((m_fAnimeX + 1.0f) / m_tex.x), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(((m_fAnimeX + 1.0f) / m_tex.x), 0.0f);

	//�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CScene2D::Uninit(void)
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

	// �V�[��2D�̊J��
	Release();
}

//=============================================================================
// pause�̏I������
//=============================================================================
void CScene2D::Uninit(bool bPause)
{
	// �|�[�Y����Ă���
	if (bPause == true)
	{
		// NULL�`�F�b�N
		if (m_pVtxBuff != NULL)
		{
			//���_�o�b�t�@�̊J��
			m_pVtxBuff->Release();
			m_pVtxBuff = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CScene2D::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CScene2D::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

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
void CScene2D::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
	CScene::SetPos(m_pos);
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
void CScene2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
	CScene::SetSize(m_size);
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
void CScene2D::SetCol(const D3DXCOLOR col)
{
	m_col = col;
	CScene::SetCol(m_col);
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
// �g�p�����ۂ�
//=============================================================================
void CScene2D::SetUse(const bool bUse)
{
	m_bUse = bUse;
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CScene2D::SetTexture(const LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void CScene2D::SetTex(const D3DXVECTOR2 tex, const D3DXVECTOR2 fnumber)
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
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CScene2D::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �F�̎擾
//=============================================================================
D3DCOLOR CScene2D::GetCol(void)
{
	return m_col;
}

