//==============================================================================
//
// エンターサイン描画処理〔title_enter.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "title_logo.h"
#include "title_enter.h"
#include "input.h"
#include "gamepad.h"
#include "fade.h"
#include "tutorial_page.h"

CTutorialPage *CTitleEnter::m_pTutorialPage = NULL;


//==============================================================================
// コンストラクタ
//==============================================================================
CTitleEnter::CTitleEnter(int nPriority) : CScene2D(nPriority)
{
	// ポリゴンの初期化
	m_p2DGameUI = NULL;
	m_p2DTutorialUI = NULL;
	m_bTutorial = false;
}

//==============================================================================
// デストラクタ
//==============================================================================
CTitleEnter::~CTitleEnter()
{
}

//==============================================================================
// エンターサインの初期化処理
//==============================================================================
HRESULT CTitleEnter::Init(D3DXVECTOR3 pos)
{
	// メンバー変数初期化
	m_pos = pos;
	m_GameUIpos = pos;
	m_GameUIpos.x -= 250.0f;
	m_TutorialUIpos = pos;
	m_TutorialUIpos.x += 250.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_SelectID = SELECT_TUTORIAL;
	m_nMoveTime = 0;

	// ゲームモード移動UI
	if (m_p2DGameUI == NULL)
	{
		m_p2DGameUI = CScene2D::Create();
		m_p2DGameUI->SetPosition(pos);
		m_p2DGameUI->SetSize(T_ENTER_SIZE);
		m_p2DGameUI->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_p2DGameUI->SetCol(m_col);
		m_p2DGameUI->BindTexture("GAME_MODE_MOVE");
	}

	// チュートリアルモード移動UI
	if (m_p2DTutorialUI == NULL)
	{
		m_p2DTutorialUI = CScene2D::Create();
		m_p2DTutorialUI->SetPosition(pos);
		m_p2DTutorialUI->SetSize(T_ENTER_SIZE);
		m_p2DTutorialUI->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
		m_p2DTutorialUI->SetCol(m_col);
		m_p2DTutorialUI->BindTexture("TUTORIAL_MODE_MOVE");
	}

	return S_OK;
}

//==============================================================================
// エンターサインの終了処理
//==============================================================================
void CTitleEnter::Uninit(void)
{
	if (m_p2DGameUI != NULL)
	{// NULLチェック後に破棄
		m_p2DGameUI->Uninit();
		m_p2DGameUI = NULL;
	}
	if (m_p2DTutorialUI != NULL)
	{// NULLチェック後に破棄
		m_p2DTutorialUI->Uninit();
		m_p2DTutorialUI = NULL;
	}


	Release();	// インスタンスのデリート
}

//==============================================================================
// エンターサインの更新処理
//==============================================================================
void CTitleEnter::Update(void)
{
	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// フェードの取得
	CFade *pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// タイマー
	m_nTimer++;

	if (m_bTutorial == false)
	{
		// モードの選択
		if (keyboard->GetTrigger(CInput::KEYINFO_RIGHT) == true ||
			keyboard->GetTrigger(CInput::KEYINFO_LEFT) == true)
		{
			// BGMの再生
			if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_TITLE) == true)
			{
				m_pSound->Play(CSound::SOUND_LABEL_SE_SELECT);
			}
			// IDの入替
			m_SelectID = m_SelectID ? SELECT_GAME : SELECT_TUTORIAL;
		}
		// 判定がtrueの場合
		if (m_bEnter == true && (keyboard->GetTrigger(CInput::KEYINFO_OK) == true && fade == CFade::FADE_NONE ||
			gamepad->GetTrigger(CInput::KEYINFO_OK) == true) && m_bNextScene == false)
		{
			// 判定をtrueに変える
			m_bNextScene = true;

			// SE
			m_pSound->Play(CSound::SOUND_LABEL_SE_TITLEENTER);
		}
		else if (m_bEnter == false)
		{// 判定がfalseの場合

		 // エンターキーを押した場合
			if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
			{
				// 判定をtrueに変える
				m_bEnter = true;

				// カウントの値を0にする
				m_nTimeColor = 0;
			}
		}

	}
	else
	{
		int nPageCnt = m_pTutorialPage->GetPageCnt();

		if (nPageCnt == 0 && keyboard->GetTrigger(CInput::KEYINFO_OK) == true)
		{
			// チュートリアルページの破棄
			if (m_pTutorialPage != NULL)
			{
				m_pTutorialPage->Uninit();
				m_pTutorialPage = NULL;
			}
			m_bTutorial = false;
		}
	}

	// 判定がどちらもtrueの場合
	if (m_bEnter == true && m_bNextScene == true)
	{
		// カウント加算
		m_nTimeColor++;

		// カウントが5で割ると0になる場合
		if (m_nTimeColor % 5 == 0)
		{
			// 色
			m_col.a = 1.0f;
		}
		else
		{
			// 色
			m_col.a = 0.5f;
		}

		// カウントが50を超えた場合
		if (m_nTimeColor >= TIME_COLOR)
		{
			switch (m_SelectID)
			{
			case CTitleEnter::SELECT_GAME:
				// フェード
				pFade->SetFade(CFade::FADE_OUT, CMode::MODE_GAME);
				break;

			case CTitleEnter::SELECT_TUTORIAL:
				// チュートリアルページの生成
				m_pTutorialPage = CTutorialPage::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f));
				m_bTutorial = true;
				break;

			default:
				break;
			}

			// 判定をfalseに変える
			m_bEnter = false;
			// 判定をfalseに変える
			m_bNextScene = false;
			// タイマーを0にする
			m_nTimer = 0;
		}
		switch (m_SelectID)
		{
		case CTitleEnter::SELECT_GAME:
			m_p2DGameUI->SetCol(m_col);
			break;
		case CTitleEnter::SELECT_TUTORIAL:
			m_p2DTutorialUI->SetCol(m_col);
			break;
		default:
			break;
		}
	}
	else
	{
		// 選択中の色設定
		switch (m_SelectID)
		{
		case CTitleEnter::SELECT_GAME:
			m_p2DGameUI->SetCol(m_SelectCol);
			m_p2DTutorialUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		case CTitleEnter::SELECT_TUTORIAL:
			m_p2DTutorialUI->SetCol(m_SelectCol);
			m_p2DGameUI->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			break;

		default:
			break;
		}
	}

	// 位置が一定よりも高い位置にあるかつ判定がfalseの場合
	if (m_pos.y > T_ENTER_SETPOS.y && m_bEnter == false)
	{
		// 移動値
		m_move.y = MOVE_START_Y;

		// 色
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_SelectCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else
	{
		// 位置を与える
		m_pos = T_ENTER_SETPOS;
		m_TutorialUIpos.y = m_pos.y;
		m_GameUIpos.y = m_pos.y;

		// 移動値
		m_move.y = 0.0f;

		// 判定をtrueに変える
		m_bEnter = true;

		//待機点滅カウント
		m_nCntColor++;

		// 選択中のUIの更新
		SelectModeUI(m_SelectID);
	}

	// 位置の加算
	m_pos += m_move;
	m_TutorialUIpos += m_move;
	m_GameUIpos += m_move;

	// 位置設定
	m_p2DGameUI->SetPosition(m_GameUIpos);

	// 位置設定
	m_p2DTutorialUI->SetPosition(m_TutorialUIpos);
}

//==============================================================================
// エンターサインの描画処理
//==============================================================================
void CTitleEnter::Draw(void)
{

}

//==============================================================================
// エンターサインの生成処理
//==============================================================================
CTitleEnter *CTitleEnter::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CTitleEnter *pTitleEnter;
	pTitleEnter = new CTitleEnter;

	// 初期化
	if (pTitleEnter != NULL)
	{
		pTitleEnter->Init(pos);
	}

	return pTitleEnter;
}

void CTitleEnter::SelectModeUI(SELECT_TYPE ID)
{
	// 移動用の時間加算
	m_nMoveTime++;

	// 選択中のIDのみ移動開始
	switch (ID)
	{
	case CTitleEnter::SELECT_GAME:
		m_GameUIpos.y += (sinf((D3DX_PI * 2) / 120 * (m_nMoveTime)) * 10);
		m_TutorialUIpos.y = m_pos.y;
		break;

	case CTitleEnter::SELECT_TUTORIAL:
		m_TutorialUIpos.y += (sinf((D3DX_PI * 2) / 120 * (m_nMoveTime)) * 10);
		m_GameUIpos.y = m_pos.y;
		break;

	default:
		break;
	}
}

