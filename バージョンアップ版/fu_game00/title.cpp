//*****************************************************************************
//
// �^�C�g������ [title.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "title.h"
#include "scene2D.h"
#include "keyinput.h"
#include "manager.h"
#include "fade.h"
#include "player.h"
#include "mesh.h"
#include "move.h"
#include "sound.h"

//-----------------------------------------------------------------------------
// �}�N���ϐ�
//-----------------------------------------------------------------------------
#define TITLE_BG_SIZE		(D3DXVECTOR3(WIDTH_HALF, HEIGHT_HALF, 0.0f))
#define TITLE_BUTTON_POS	(D3DXVECTOR3(WIDTH_HALF, HEIGHT_HALF+250.0f, 0.0f))
#define TITLE_BUTTON_SIZE	(D3DXVECTOR3(150.0f, 50.0f, 0.0f))
#define TITLE_LOGO_POS		(D3DXVECTOR3(WIDTH_HALF-300, HEIGHT_HALF-100.0f, 0.0f))
#define TITLE_LOGO_SIZE		(D3DXVECTOR3(600.0f, 400.0f, 0.0f))

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------
CScene2D *CTitle::m_paTitleUI[UI_MAX] = {};
CMesh *CTitle::m_pTitleLogo = NULL;
CMesh3D *CTitle::m_pNote = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTitle::CTitle() : CScene(OBJ_NONE)
{
	m_ButtonCol = WhiteColor;	// �F�̏�����
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// �^�C�g���̐���
//=============================================================================
CTitle * CTitle::Create(void)
{
	CTitle* pTitle = NULL;

	if (pTitle == NULL)
	{// NULL�`�F�b�N

		// �������m��
		CTitle* pTitle = new CTitle;

		// ����������
		pTitle->Init();
	}

	return pTitle;
}

//=============================================================================
// ������
//=============================================================================
HRESULT CTitle::Init(void)
{
	// �w�i�̐���
	m_paTitleUI[UI_BG] = CScene2D::Create(CENTER_POS, TITLE_BG_SIZE);
	m_paTitleUI[UI_BG]->CreateTexture("data/TEXTURE/BG.jpg");

	// Button�̐���
	m_paTitleUI[UI_BUTTON] = CScene2D::Create(TITLE_BUTTON_POS, TITLE_BUTTON_SIZE);
	m_paTitleUI[UI_BUTTON]->CreateTexture("data/TEXTURE/Next_Mode.png");

	// LOGO�̐���
	m_pTitleLogo = CMesh::Create(90, 0, TITLE_LOGO_POS, TITLE_LOGO_SIZE, CScene::OBJ_NONE);
	m_pTitleLogo->CreateTexture("data/TEXTURE/TitleUI.png");

	// �T�E���h�̊J�n
	CSound *pSound = CManager::GetSound();
	pSound->PlaySound(CSound::SOUND_LABEL_BGM000);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitle::Uninit(void)
{
	// �T�E���h�̍폜
	CSound *pSound = CManager::GetSound();
	pSound->StopSound();

	// �폜
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTitle::Update(void)
{
	// �L�[���
	CKey *pKey = CManager::GetKey();

	// �t�F�[�h���
	CFade::FADE Fade = CFade::GetFade();   

	// �J�E���g�A�b�v
	m_nCntTime++;

	if (pKey->GetState(CKey::STATE_TRIGGER, DIK_SPACE) && Fade == CFade::FADE_NONE)
	{// �g���K�[�E�X�y�[�X����������E�t�F�[�h�̏�Ԃ������Ȃ���Ԃ�������
		CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	}

	// �^�C�g����LOGO�̏���
	TitleLogo(m_nCntTime);

	// Button�̏���
	ButtonUI();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitle::Draw(void)
{
	
}

//=============================================================================
// Button�̏���
//=============================================================================
void CTitle::ButtonUI(void)
{
	// ���l�̍X�V
	m_paTitleUI[UI_BUTTON]->SetCol(m_ButtonCol);

	// ���l�̌��Z�Ɖ��Z
	m_ButtonCol.a += AddCol; 

	if (m_ButtonCol.a >= 1.0f)
	{// ���Z������l
		AddCol = -0.02f;
	}
	if (m_ButtonCol.a <= 0.0f)
	{// ���Z������l
		AddCol = 0.02f;
	}
}

//=============================================================================
// TitleLogo�̏���
//=============================================================================
void CTitle::TitleLogo(int nTime)
{
	for (int nVtx = 0; nVtx < m_pTitleLogo->GetVtxNum(); nVtx++)
	{
		D3DXVECTOR3 pos = ZeroVector3;

		// Sin�g�̔g�̕\��
		pos.y = Move::SinWave(HEIGHT_HALF - 350.0f, 25.0f,200.0f, ((float)nTime + nVtx));

		if (nVtx >= m_pTitleLogo->GetVtxNum() / 2)
		{// ���_����ӑ��ɍs������
			pos.y += 400.0f;
		}

		// �ʒu�̍X�V
		m_pTitleLogo->SetVtxPosY(nVtx, pos.y);
	}
}
