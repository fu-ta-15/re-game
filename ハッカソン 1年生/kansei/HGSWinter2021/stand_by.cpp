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
#include "stand_by.h"
#include "input.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CStandBy::CStandBy(int nPriority) : CScene(nPriority)
{
	m_pBase = NULL;
	m_pControlSign = NULL;
}

//==============================================================================
// デストラクタ
//==============================================================================
CStandBy::~CStandBy()
{
}

//==============================================================================
// キャラクターの初期化処理
//==============================================================================
HRESULT CStandBy::Init(void)
{
	// 初期化
	if (m_pBase == NULL)
	{
		m_pBase = CScene2D::Create();
		m_pBase->SetPosition(SCREEN_CENTER);
		m_pBase->SetSize(STAND_BY_SIZE);
		//m_pBase->BindTexture("GAME_BG");
		m_pBase->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f));
		m_pBase->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	if (m_pControlSign == NULL)
	{
		m_pControlSign = CScene2D::Create();
		m_pControlSign->SetPosition(SCREEN_CENTER);
		m_pControlSign->SetSize(STAND_BY_SIGN_SIZE);

		m_pControlSign->BindTexture("STANDBY_LOGO");
		m_pControlSign->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pControlSign->SetTex(1, 1, 0, 0, 0.0f, 0.0f);
	}

	return S_OK;
}

//==============================================================================
// スタンバイ画面の終了処理
//==============================================================================
void CStandBy::Uninit(void)
{
	// ポリゴンの破棄
	if (m_pBase != NULL)
	{
		m_pBase->Uninit();
		m_pBase = NULL;
	}

	if (m_pControlSign != NULL)
	{
		m_pControlSign->Uninit();
		m_pControlSign = NULL;
	}

	Release();
}

//==============================================================================
// スタンバイ画面の更新処理
//==============================================================================
void CStandBy::Update(void)
{
	
}

//==============================================================================
// スタンバイ画面の描画処理
//==============================================================================
void CStandBy::Draw(void)
{
}

//==============================================================================
// スタンバイ画面の生成処理
//==============================================================================
CStandBy *CStandBy::Create(void)
{
	// インスタンス生成
	CStandBy *pStandBy;
	pStandBy = new CStandBy;

	// 初期化
	if (pStandBy != NULL)
	{
		pStandBy->Init();
	}

	return pStandBy;
}

// 画面の消去
void CStandBy::DeleteWindow(void)
{
	if (m_pBase != NULL)
	{
		m_pBase->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
	if (m_pControlSign != NULL)
	{
		m_pControlSign->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}