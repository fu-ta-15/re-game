//==============================================================================
//
// サイン(指示)描画処理〔sign.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "sign.h"
#include "input.h"
#include "game.h"
#include "chara.h"
#include "match_result.h"
#include "select.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CSign::CSign(int nPriority) : CScene(nPriority)
{
	m_nCntActive = 0;
	m_nCntChange = 0;
	m_nCntSelect = 0;
}

//==============================================================================
// デストラクタ
//==============================================================================
CSign::~CSign()
{
}

//==============================================================================
// サインの初期化処理
//==============================================================================
HRESULT CSign::Init(void)
{
	// 初期化
	if (m_pScene2D == NULL)
	{
		m_pScene2D = new CScene2D;
		m_pScene2D->Init();
		m_pScene2D->SetPosition(SCREEN_CENTER);
		m_pScene2D->SetSize(VECTOR2_NULL);
		m_pScene2D->BindTexture("MERRY_SIGN");
		m_pScene2D->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	// 終了する値
	m_nCntEnd = rand() % 4 + 2 ;

	return S_OK;
}

//==============================================================================
// サインの終了処理
//==============================================================================
void CSign::Uninit(void)
{
	// ポリゴンの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}

	Release();
}

//==============================================================================
// サインの更新処理
//==============================================================================
void CSign::Update(void)
{
	// サインの挙動
	SignBehave();
}

//==============================================================================
// サインの描画処理
//==============================================================================
void CSign::Draw(void)
{

}

//==============================================================================
// サインの生成処理
//==============================================================================
CSign *CSign::Create(void)
{
	// インスタンス生成
	CSign *pSign;
	pSign = new CSign;

	// 初期化
	if (pSign != NULL)
	{
		pSign->Init();
	}

	return pSign;
}

//==============================================================================
// サインの挙動
//==============================================================================
void CSign::SignBehave(void)
{
	// ローカル変数宣言
	D3DXVECTOR2 size = m_pScene2D->GetSize();	// サイズの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	CGame::MATCH match = CGame::GetMatch();	// 勝敗情報の取得
	CChara *pChara = CGame::GetChara();		// キャラ情報の取得
	CMatchResult *pMatchResult = CGame::GetMatchResult();

	// 状態ごとの挙動
	switch (m_signPhase)
	{
	case SIGNPHASE_WAIT:	// 待機状態
		m_pScene2D->BindTexture("SIGN_MERRY");

		size += D3DXVECTOR2(1.0f, 0.5f);

		m_pScene2D->SetSize(size);

		// 移動
		pChara->CharaMove();

		m_nCntActive++;

		if (m_nCntActive >= 180)
		{
			m_signPhase = SIGNPHASE_ACTIVE;
			m_pScene2D->SetSize(D3DXVECTOR2(400.0f, 400.0f));
			m_pScene2D->BindTexture("DUMMY0");
			m_nCntActive = 0;
		}

		break;

	case SIGNPHASE_ACTIVE:	// 入力可能状態

		if (m_imageType != IMAGETYPE_TRUE)
		{
			m_nCntActive++;
		}
		else
		{
			m_nCntActive = 1;
		}
		
		// 画像の差し替えランダム
		if ((m_nCntActive % 150 == 0) )
		{
			int nType = -1;
			while (nType == (int)m_imageType)
			{// 重複回避
				nType = (rand() % (int)IMAGETYPE_MAX - 1) + 1;
			}

			m_imageType = (IMAGETYPE)nType;
			m_nCntChange++;

			if (m_nCntChange == m_nCntEnd)
			{
				m_imageType = IMAGETYPE_TRUE;
			}

			m_pSound->Play(CSound::SOUND_LABEL_SE_SAVEPOINT);
		}

		switch (m_imageType)
		{
		case IMAGETYPE_TRUE:
			m_pScene2D->BindTexture("SIGN_XMAS");
			break;

		case IMAGETYPE_DAMMY_A:
			m_pScene2D->BindTexture("DUMMY0");
			break;

		case IMAGETYPE_DAMMY_B:
			m_pScene2D->BindTexture("DUMMY1");
			break;

		case IMAGETYPE_DAMMY_C:
			m_pScene2D->BindTexture("DUMMY2");
			break;

		case IMAGETYPE_DAMMY_D:
			m_pScene2D->BindTexture("DUMMY3");
			break;

		case IMAGETYPE_DAMMY_E:
			m_pScene2D->BindTexture("DUMMY4");
			break;

		case IMAGETYPE_DAMMY_F:
			m_pScene2D->BindTexture("DUMMY5");
			break;

		case IMAGETYPE_DAMMY_G:
			m_pScene2D->BindTexture("DUMMY6");
			break;

		case IMAGETYPE_DAMMY_H:
			m_pScene2D->BindTexture("DUMMY7");
			break;

		case IMAGETYPE_DAMMY_I:
			m_pScene2D->BindTexture("DUMMY8");
			break;

		case IMAGETYPE_DAMMY_J:
			m_pScene2D->BindTexture("DUMMY9");
			break;

		case IMAGETYPE_DAMMY_K:
			m_pScene2D->BindTexture("DUMMY10");
			break;

		case IMAGETYPE_DAMMY_L:
			m_pScene2D->BindTexture("DUMMY11");
			break;

		case IMAGETYPE_DAMMY_M:
			m_pScene2D->BindTexture("DUMMY12");
			break;

		case IMAGETYPE_DAMMY_N:
			m_pScene2D->BindTexture("DUMMY13");
			break;

		case IMAGETYPE_DAMMY_O:
			m_pScene2D->BindTexture("DUMMY14");
			break;

		case IMAGETYPE_DAMMY_P:
			m_pScene2D->BindTexture("DUMMY15");
			break;

		case IMAGETYPE_DAMMY_Q:
			m_pScene2D->BindTexture("DUMMY16");
			break;

		case IMAGETYPE_DAMMY_R:
			m_pScene2D->BindTexture("DUMMY17");
			break;
		}

		if (CGame::GetMatch() == CGame::MATCH_NONE && m_imageType == IMAGETYPE_TRUE)
		{
			// 同時押し
			if (keyboard->GetTrigger(CInput::KEYINFO_GO_LEFT) == true && keyboard->GetTrigger(CInput::KEYINFO_GO_RIGHT) == true)
			{
				CGame::SetMatch(CGame::MATCH_DRAW);
			}

			// 左が早押し
			if (keyboard->GetTrigger(CInput::KEYINFO_GO_LEFT) == true)
			{
				CGame::SetMatch(CGame::MATCH_LEFT);
			}

			// 右が早押し	
			if (keyboard->GetTrigger(CInput::KEYINFO_GO_RIGHT) == true)
			{
				CGame::SetMatch(CGame::MATCH_RIGHT);
			}
		}

		if (CGame::GetMatch() != CGame::MATCH_NONE)
		{
			pMatchResult->MatchResult();
			
			m_nCntSelect++;

			if (m_nCntSelect >= 120)
			{
				CSelect::On();
			}
		}
		
		
		break;

	//case SIGNPHASE_DUMMY:		// 偽の入力
	//	break;

	case SIGNPHASE_INTERVAL:	// 入力間隔
		break;
	}
}