
//==============================================================================
//
// ゲームモード処理〔game.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "result.h"
#include "pause.h"

#include "timer_count.h"
#include "camera.h"

#include "effect.h"
#include "gamesetlogo.h"
#include "bg.h"
#include "ui.h"
#include "sign.h"
#include "chara.h"
#include "stand_by.h"
#include "match_result.h"
#include "select.h"
#include "input.h"

//==============================================================================
// 静的メンバ変数宣言
//==============================================================================
CPause *CGame::m_pPause = NULL;										// ポーズポインタ
bool CGame::m_bGameEnd = false;										// ゲーム終了のフラグ
int CGame::m_nClearDirectingCnt = 0;								// ゲーム終了演出カウント
CGamesetLogo *CGame::m_pGamesetLogo = NULL;							// ゲーム終了ロゴ

CUi *CGame::m_pUi = NULL;											// UIクラス
CBg *CGame::m_pBg = NULL;											// 背景クラス
CSign *CGame::m_pSign = NULL;										// サインクラス
CChara *CGame::m_pChara = NULL;										// キャラクラス
CStandBy *CGame::m_pStandBy = NULL;									// スタンバイ画面クラス
CMatchResult *CGame::m_pMatchResult = NULL;							// 結果
CSelect *CGame::m_pSelect = NULL;									// 選択
CGame::MATCH CGame::m_match = MATCH_NONE;

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame(int nPriority) : CMode(nPriority)
{
	m_bGameEnd = false;
	m_nClearDirectingCnt = 0;
	m_match = MATCH_NONE;
}

//==============================================================================
// デストラクタ
//==============================================================================
CGame::~CGame()
{
}

//==============================================================================
// ゲームモードの初期化処理
//==============================================================================
HRESULT CGame::Init(void)
{
	// カメラの位置初期化
	CCamera *pCamera = CManager::GetCamera();
	if (pCamera != NULL)
	{
		pCamera->SetInit();
	}

	// 背景の生成
	if (m_pBg == NULL)
	{
		m_pBg = CBg::Create();
	}

	// サインクラス
	if (m_pSign == NULL)
	{
		m_pSign = CSign::Create();
	}

	// キャラクター生成
	if (m_pChara == NULL)
	{
		m_pChara = CChara::Create();
	}

	// スタンバイ画面クラス
	if (m_pStandBy == NULL)
	{
		m_pStandBy = CStandBy::Create();
	}

	// 結果
	if (m_pMatchResult == NULL)
	{
		m_pMatchResult = CMatchResult::Create();
	}

	// UIの生成
	if (m_pUi == NULL)
	{
		m_pUi = CUi::Create();
	}

	// ポーズの生成
	if (m_pPause == NULL)
	{
		m_pPause = CPause::Create();
	}

	// 選択クラス
	if (m_pSelect == NULL)
	{
		m_pSelect = CSelect::Create();
	}
	
	return S_OK;
}

//==============================================================================
// ゲームモードの終了処理
//==============================================================================
void CGame::Uninit(void)
{
	// 背景の生成
	if (m_pBg != NULL)
	{
		m_pBg->Uninit();
		m_pBg = NULL;
	}

	// BGMの停止
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_GAME) == true)
	{
		m_pSound->Stop();
	}

	// ポーズの終了
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	// UIの終了
	if (m_pUi != NULL)
	{
		m_pUi->Uninit();
		m_pUi = NULL;
	}

	// キャラクターの終了
	if (m_pChara != NULL)
	{
		m_pChara->Uninit();
		m_pChara = NULL;
	}

	// サインの終了
	if (m_pSign != NULL)
	{
		m_pSign->Uninit();
		m_pSign = NULL;
	}

	// スタンバイ画面の終了
	if (m_pStandBy != NULL)
	{
		m_pStandBy->Uninit();
		m_pStandBy = NULL;
	}

	// 結果
	if (m_pMatchResult != NULL)
	{
		m_pMatchResult->Uninit();
		m_pMatchResult = NULL;
	}


	// 選択
	if (m_pSelect != NULL)
	{
		m_pSelect->Uninit();
		m_pSelect = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// ゲームモードの更新処理
//==============================================================================
void CGame::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();


	// サイン処理の開始
	if (m_pSign->GetPhase() == CSign::SIGNPHASE_NONE)
	{
		if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || keyboard->GetTrigger(CInput::KEYINFO_START_SPACE) == true)
		{
			m_pSign->StartSign();
			m_pStandBy->DeleteWindow();
		}
	}

	// ゲーム終了
	if (m_bGameEnd == true)
	{
		//EndGame();
	}
}

//==============================================================================
// ゲームモードの描画処理
//==============================================================================
void CGame::Draw(void)
{
}

//==============================================================================
// ゲームモードの生成処理
//==============================================================================
CGame *CGame::Create()
{
	// インスタンス生成
	CGame *pGame;
	pGame = new CGame;

	// 初期化
	if (pGame != NULL)
	{
		pGame->Init();
	}

	return pGame;
}

//==============================================================================
// ゲーム終了演出
//==============================================================================
//void CGame::EndGame(void)
//{
//	// クリア演出カウントの加算
//	m_nClearDirectingCnt++;
//
//	switch (CResult::GetEndState())
//	{
//	case CResult::ENDSTATE_CLEAR:		// クリア時
//
//		//GameClear();
//
//		break;
//
//	case CResult::ENDSTATE_GAMEOVER:	// ゲームオーバー時
//
//		GameOver();
//
//		break;
//	}
//}