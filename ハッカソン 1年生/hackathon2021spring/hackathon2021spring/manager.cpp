//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//
//	manager.cpp
//	Author:�r�c�I��
//
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�C���N���[�h�t�@�C��
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
#include "manager.h"

#include "camera.h"
#include "fade.h"
#include "gamemode.h"
#include "light.h"
#include "object.h"
#include "object2d.h"
#include "object3d.h"
#include "renderer.h"
#include "sound.h"
#include "cube.h"
#include "input.h"
#include "inputkeyboard.h"
#include "gamemode.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "player.h"
#include "rail.h"
#include "tool.h"
#include "train.h"

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�ÓI�����o�ϐ��錾
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::m_pRenderer               = NULL;
CFade* CManager::m_pFade                       = NULL;
CManager::MODE CManager::m_mode  = MODE_NONE;
//CSound* CManager::m_pSound                     = NULL;
ICGamemode* CManager::m_pGamemode = NULL;
CInputKeyboard* CManager::m_pInput = NULL;
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�R���X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::CManager()
{
    m_pRenderer   = NULL;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�f�X�g���N�^
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CManager::~CManager()
{
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�������֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;                    //�����_���𐶐�
    hResult         = m_pRenderer->Init(hWnd, true);    //�����_����������
    CLight* pLight = NULL;    //���C�g�̐���
    pLight         = new CLight;
    pLight->Init();
	LoadFile();    //�t�@�C���ǂݍ���
	m_pInput = new CInputKeyboard;
	m_pInput->Init(hInstance,hWnd);
    //�T�E���h�̐���
    //if(m_pSound == NULL)
    //{
    //    m_pSound = new CSound;
    //}
    //�T�E���h�̏�����
   // m_pSound->Init(hWnd);
    m_pFade = CFade::Create();
	m_pFade->SetFade(MODE_TITLE);
    return hResult;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�I���֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Uninit(void)
{
    //�t�F�[�h�I��
    if(m_pFade != NULL)
    {
        m_pFade->Uninit();
        delete m_pFade;
        m_pFade = NULL;
    }

	if (m_pGamemode != NULL)
	{
		m_pGamemode->Uninit();
		delete m_pGamemode;
		m_pGamemode = NULL;
	}
	//�V�[���̏I��
	CObject::ReleaseAll();
    //�����_���̏I��
    m_pRenderer->Uninit();
    delete m_pRenderer;
    m_pRenderer = NULL;

    //�T�E���h�̒�~
    //m_pSound->StopSound();

    //�T�E���h�̔j��
    //if(m_pSound != NULL)
    //{
    //    m_pSound->Uninit();
    //    delete m_pSound;
    //    m_pSound = NULL;
    //}

    //�ǂݍ��񂾃t�@�C���̃A�����[�h
    UnloadFiles();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�X�V�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Update(void)
{

	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	
	if (m_pGamemode != NULL)
	{
		m_pGamemode->Update();
	}
	CObject::UpdateAll();
    //�t�F�[�h�X�V
    if(m_pFade != NULL)
    {
        m_pFade->Update();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�`��֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::Draw(void)
{
    //�����_���̕`��
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�Q�b�^�[�֐�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃��[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::LoadFile(void)
{
	CCube::Load();
	CTitle::Load();
	CResult::Load();
	CTutorial::Load();
	CPlayer::Load();
	CRail::Load();
	CTool::Load();
	CTrain::Load();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//�t�@�C���̃A�����[�h
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::UnloadFiles(void)
{
	CCube::Unload();
	CTitle::Unload();
	CResult::Unload();
	CTutorial::Unload();
	CPlayer::Unload();
	CRail::Unload();
	CTool::Unload();
	CTrain::Unload();
}

//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
//���[�h�ؑ�
//�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E�E
void CManager::SetMode(const MODE mode)
{
	//m_pSound->StopSound();
	if (m_pGamemode != NULL)
	{
		m_pGamemode->Uninit();
		delete m_pGamemode;
		m_pGamemode = NULL;
	}
	CObject::ReleaseAll();
	switch (mode)
	{
	case MODE_TITLE:
		m_pGamemode = new CTitle;
		break;
	case MODE_TUTORIAL:
		m_pGamemode = new CTutorial;
		break;
	case MODE_GAME:
		m_pGamemode = new CGame;
		break;
	case MODE_RESULT:
		m_pGamemode = new CResult;
		break;
}
	m_pGamemode->Init();
}

CManager::MODE CManager::GetMode(void)
{
    return m_mode;
}

ICGamemode*CManager::GetGamemode(void)
{
	return m_pGamemode;
}
CInputKeyboard* CManager::GetInput(void)
{
	return m_pInput;
}