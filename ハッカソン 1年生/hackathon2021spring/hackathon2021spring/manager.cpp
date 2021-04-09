//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::m_pRenderer               = NULL;
CFade* CManager::m_pFade                       = NULL;
CManager::MODE CManager::m_mode  = MODE_NONE;
//CSound* CManager::m_pSound                     = NULL;
ICGamemode* CManager::m_pGamemode = NULL;
CInputKeyboard* CManager::m_pInput = NULL;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::CManager()
{
    m_pRenderer   = NULL;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CManager::~CManager()
{
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CManager::Init(HWND hWnd, bool bWindow, HINSTANCE hInstance)
{
    HRESULT hResult = NULL;
    m_pRenderer     = new CRenderer;                    //レンダラを生成
    hResult         = m_pRenderer->Init(hWnd, true);    //レンダラを初期化
    CLight* pLight = NULL;    //ライトの生成
    pLight         = new CLight;
    pLight->Init();
	LoadFile();    //ファイル読み込み
	m_pInput = new CInputKeyboard;
	m_pInput->Init(hInstance,hWnd);
    //サウンドの生成
    //if(m_pSound == NULL)
    //{
    //    m_pSound = new CSound;
    //}
    //サウンドの初期化
   // m_pSound->Init(hWnd);
    m_pFade = CFade::Create();
	m_pFade->SetFade(MODE_TITLE);
    return hResult;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Uninit(void)
{
    //フェード終了
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
	//シーンの終了
	CObject::ReleaseAll();
    //レンダラの終了
    m_pRenderer->Uninit();
    delete m_pRenderer;
    m_pRenderer = NULL;

    //サウンドの停止
    //m_pSound->StopSound();

    //サウンドの破棄
    //if(m_pSound != NULL)
    //{
    //    m_pSound->Uninit();
    //    delete m_pSound;
    //    m_pSound = NULL;
    //}

    //読み込んだファイルのアンロード
    UnloadFiles();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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
    //フェード更新
    if(m_pFade != NULL)
    {
        m_pFade->Update();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CManager::Draw(void)
{
    //レンダラの描画
    if(m_pRenderer != NULL)
    {
        m_pRenderer->Draw();
    }
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ゲッター関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CRenderer* CManager::GetRenderer(void)
{
    return m_pRenderer;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//ファイルのアンロード
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//モード切替
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
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