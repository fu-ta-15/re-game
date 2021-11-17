//*****************************************************************************
//
// �}�l�[�W���[���� [manager.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "fade.h"
#include "keyinput.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "sound.h"
#include "camera.h"
#include "light.h"

//-----------------------------------------------------------------------------
//�ÓI�����o�ϐ��錾
//-----------------------------------------------------------------------------
CRenderer		*CManager::m_pRenderer = NULL;				// �����_���[�|�C���^
CKey			*CManager::m_pKey = NULL;					// �L�[�{�[�h���̓|�C���^
CFade			*CManager::m_pFade = NULL;					// �t�F�[�h�|�C���^
CTitle			*CManager::m_pTitle = NULL;					// �^�C�g���|�C���^
CTutorial		*CManager::m_pTutorial = NULL;				// �`���[�g���A���|�C���^
CGame			*CManager::m_pGame = NULL;					// �Q�[���|�C���^
CResult			*CManager::m_pResult = NULL;				// ���U���g�|�C���^
CSound			*CManager::m_pSound = NULL;					// �T�E���h�|�C���^
CCamera			*CManager::m_pCamera = NULL;				// �J�����̃|�C���^
CLight			*CManager::m_pLight = NULL;					// ���C�g�̃|�C���^
CPause			*CManager::m_pPause = NULL;					// �|�[�Y�|�C���^
bool			 CManager::m_bPause = false;				// �|�[�Y�̐؂�ւ��ϐ�
CManager::MODE	 CManager::m_mode = CManager::MODE_GAME;	// ���݂̃��[�h�̕ϐ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// ���ݎ����̏��ŏ�����
	srand((unsigned)time(NULL));	

	// �����_���[����
	m_pRenderer = new CRenderer;

	// �����_��������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{// NULL�`�F�b�N
		return -1;
	}

	// �L�[�{�[�h����
	m_pKey = new CKey;

	// �L�[�{�[�h������
	if (FAILED(m_pKey->Init(hInstance, hWnd)))
	{// NULL�`�F�b�N
		return -1;
	}

	// �T�E���h�̐���
	m_pSound = new CSound;

	// �T�E���h�̏�����
	if (FAILED(m_pSound->Init(hWnd)))
	{// NULL�`�F�b�N
		return -1;
	}

	// �J�����̐���
	m_pCamera = new CCamera;

	// �J�����̏�����
	if (m_pCamera != NULL)
	{// NULL�`�F�b�N
		m_pCamera->Init();
	}

	// ���C�g�̐���
	m_pLight = new CLight;

	// ���C�g�̏�����
	if (m_pLight != NULL)
	{// NULL�`�F�b�N
		m_pLight->Init();
	}

	// �t�F�[�h�̐���
	m_pFade = new CFade;

	//�t�F�[�h�̏�����
	if (m_pFade != NULL)
	{// NULL�`�F�b�N
		m_pFade->Init();
	}

	// �t�F�[�h���Ă���^�C�g����
	m_pFade->SetFade(m_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//���݃��[�h�̏I��
	UninitMode(m_mode);

	// �t�F�[�h�̊J��
	if (m_pFade != NULL)		
	{// NULL�`�F�b�N
		m_pFade->Uninit();		
		delete m_pFade;			
		m_pFade = NULL;			
	}

	// �����_���[�̊J��
	if (m_pRenderer != NULL)	
	{// NULL�`�F�b�N
		m_pRenderer->Uninit();	
		delete m_pRenderer;		
		m_pRenderer = NULL;		
	}

	// �L�[�̊J��
	if (m_pKey != NULL)			
	{// NULL�`�F�b�N
		m_pKey->Uninit();		
		delete m_pKey;			
		m_pKey = NULL;			
	}

	// �T�E���h�̊J��
	if (m_pSound != NULL)
	{// NULL�`�F�b�N
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	// �J�����̊J��
	if (m_pCamera != NULL)
	{// NULL�`�F�b�N
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}

	// ���C�g�̊J��
	if (m_pLight != NULL)
	{// NULL�`�F�b�N
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	// �V�[���̑S�폜
	CScene::ReleaseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	// �����_���[�̍X�V
	if (m_pRenderer != NULL)
	{// NULL�`�F�b�N
		m_pRenderer->Update();	
	}

	// �L�[�̍X�V
	if (m_pKey != NULL)
	{// NULL�`�F�b�N
		m_pKey->Update();		
	}

	// �t�F�[�h�̍X�V
	if (m_pFade != NULL)
	{// NULL�`�F�b�N
		m_pFade->Update();		
	}

	// �J�����̍X�V
	if (m_pCamera != NULL)
	{// NULL�`�F�b�N
		m_pCamera->Update();
	}

	// ���C�g�̍X�V
	if (m_pLight != NULL)
	{// NULL�`�F�b�N
		m_pLight->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	// �`�揈��
	if (m_pRenderer != NULL)
	{// NULL�`�F�b�N
		m_pRenderer->Draw();
	}
}

//=============================================================================
// ���[�h�̏I������
//=============================================================================
void CManager::UninitMode(MODE mode)
{
	// �e���[�h�̊J��
	switch (mode)
	{
	//	// �^�C�g�����[�h
	//case MODE_TITLE:
	//	if (m_pTitle != NULL)
	//	{// NULL�`�F�b�N
	//		m_pTitle->Uninit();
	//		m_pTitle = NULL;
	//	}
	//	break;

	//	// �`���[�g���A�����[�h
	//case MODE_TUTORIAL:
	//	if (m_pTutorial != NULL)
	//	{// NULL�`�F�b�N
	//		m_pTutorial->Uninit();
	//		m_pTutorial = NULL;
	//	}
	//	break;

		// �Q�[�����[�h
	case MODE_GAME:
		if (m_pGame != NULL)
		{// NULL�`�F�b�N
			m_pGame->Uninit();
			m_pGame = NULL;
		}
		break;

	//	// ���U���g���[�h
	//case MODE_RESULT:
	//	if (m_pResult != NULL)
	//	{// NULL�`�F�b�N
	//		m_pResult->Uninit();
	//		m_pResult = NULL;
	//	}
	//	break;

	default:
		break;
	}
}

//=============================================================================
// ���[�h�̐���
//=============================================================================
void CManager::CreateMode(MODE mode)
{
	// �e���[�h�̐���
	switch (mode)
	{
	//	// �^�C�g�����[�h
	//case MODE_TITLE:	
	//	if (m_pTitle == NULL)
	//	{// NULL�`�F�b�N
	//		m_pTitle = CTitle::Create();
	//	}
	//	break;

	//	// �`���[�g���A�����[�h
	//case MODE_TUTORIAL:
	//	if (m_pTutorial == NULL)
	//	{// NULL�`�F�b�N
	//		m_pTutorial = CTutorial::Create();
	//	}
	//	break;

		// �Q�[�����[�h
	case MODE_GAME:		
		if (m_pGame == NULL)
		{// NULL�`�F�b�N
			m_pGame = CGame::Create();
		}
		break;

	//	// ���U���g���[�h
	//case MODE_RESULT:	
	//	if (m_pResult == NULL)
	//	{// NULL�`�F�b�N
	//		m_pResult = CResult::Create();
	//	}
	//	break;

	default:
		break;
	}
}

//=============================================================================
// ���[�h�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//���݃��[�h�̏I��
	UninitMode(m_mode);

	// �V�[�����̃����[�X
	CScene::ReleaseAll();

	//���[�h��ݒ�
	m_mode = mode;


	// ���[�h�̐���
	CreateMode(m_mode);
}

