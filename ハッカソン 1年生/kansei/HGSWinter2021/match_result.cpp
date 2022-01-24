//==============================================================================
//
// スタンバイ描画処理〔stand_by.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
//#include "sign.h"
#include "match_result.h"
#include "input.h"
#include "game.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CMatchResult::CMatchResult(int nPriority) : CScene(nPriority)
{
}

//==============================================================================
// デストラクタ
//==============================================================================
CMatchResult::~CMatchResult()
{
}

//==============================================================================
// キャラクターの初期化処理
//==============================================================================
HRESULT CMatchResult::Init(void)
{
	// 初期化
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apScene[nCnt] == NULL)
		{
			m_apScene[nCnt] = CScene2D::Create();
			m_apScene[nCnt]->SetPosition(VECTOR3_NULL);
			m_apScene[nCnt]->SetSize(RESULT_SIZE);
			m_apScene[nCnt]->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
			m_apScene[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	return S_OK;
}

//==============================================================================
// スタンバイ画面の終了処理
//==============================================================================
void CMatchResult::Uninit(void)
{
	// ポリゴンの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_apScene[nCnt] != NULL)
		{
			m_apScene[nCnt]->Uninit();
			m_apScene[nCnt] = NULL;
		}
	}

	Release();
}

//==============================================================================
// スタンバイ画面の更新処理
//==============================================================================
void CMatchResult::Update(void)
{

}

//==============================================================================
// スタンバイ画面の描画処理
//==============================================================================
void CMatchResult::Draw(void)
{
}

//==============================================================================
// スタンバイ画面の生成処理
//==============================================================================
CMatchResult *CMatchResult::Create(void)
{
	// インスタンス生成
	CMatchResult *pMatchResult;
	pMatchResult = new CMatchResult;

	// 初期化
	if (pMatchResult != NULL)
	{
		pMatchResult->Init();
	}

	return pMatchResult;
}

// 勝敗演出
void CMatchResult::MatchResult(void)
{
	switch (CGame::GetMatch())
	{
	case CGame::MATCH_LEFT:

		m_apScene[0]->SetPosition(RESULT_POS_WIN_LEFT);
		m_apScene[0]->BindTexture("WIN");

		m_apScene[1]->SetPosition(RESULT_POS_LOSE_RIGHT);
		m_apScene[1]->BindTexture("LOSE");

		break;

	case CGame::MATCH_RIGHT:

		m_apScene[0]->SetPosition(RESULT_POS_LOSE_LEFT);
		m_apScene[0]->BindTexture("LOSE");

		m_apScene[1]->SetPosition(RESULT_POS_WIN_RIGHT);
		m_apScene[1]->BindTexture("WIN");
		
		break;

	case CGame::MATCH_DRAW:
		break;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_apScene[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}