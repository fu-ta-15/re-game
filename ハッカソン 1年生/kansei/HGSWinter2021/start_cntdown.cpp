//==============================================================================
//
// 開始時カウントダウン描画処理〔start_cntdown.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "start_cntdown.h"
#include "game.h"
#include "timer.h"
#include "timer_count.h"
#include "ui.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CStartCntdown::CStartCntdown(int nPriority) : CScene(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CStartCntdown::~CStartCntdown()
{

}

//==============================================================================
// 開始時カウントダウンの初期化処理
//==============================================================================
HRESULT CStartCntdown::Init(void)
{
	// タイマー設定
	m_nCntDown = 3;

	// フラグ初期化
	m_bStartCntdown = false;
	m_bCntDowning = false;
	m_nDecereaseCnt = 0;

	// ポリゴンの設定
	if (m_pScene2D == NULL)
	{
		m_pScene2D = CScene2D::Create();						// 生成
		m_pScene2D->SetPosition(SCREEN_CENTER);					// 位置
		m_pScene2D->SetSize(START_CNT_SIZE);					// サイズ
		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);					// テクスチャ座標
		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色の設定
	}

	return S_OK;
}

//==============================================================================
// 開始時カウントダウンの終了処理
//==============================================================================
void CStartCntdown::Uninit(void)
{
	// 2Dポリゴンの破棄
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// 開始時カウントダウンの更新処理
//==============================================================================
void CStartCntdown::Update(void)
{
	// サウンド
	m_pSound = CManager::GetSound();

	CUi *pUi = CGame::GetUi();

	if (m_bStartCntdown == true)
	{
		if (m_nDecereaseCnt == 0)
		{
			m_pSound->Play(CSound::SOUND_LABEL_SE_CNTDOWN);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_bCntDowning = true;
		}

		m_nDecereaseCnt++;

		if (m_nDecereaseCnt % CNT_ONE_SECOND == 0 && m_nDecereaseCnt != 0)
		{
			m_nCntDown--;
		}

		if (m_nDecereaseCnt >= CNT_ONE_SECOND * CNTDOWN_MAX)
		{
			// カウントダウンの開始
			pUi->GetTimer()->GetTimerCnt()->SetStartCnt(true);
			m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_bCntDowning = false;
		}
	}

	switch (m_nCntDown)
	{
	case 0:
		m_pScene2D->BindTexture("GO");		// テクスチャ設定
		break;

	case 1:
		m_pScene2D->BindTexture("ONE");		// テクスチャ設定
		break;

	case 2:
		m_pScene2D->BindTexture("TWO");		// テクスチャ設定
		break;

	case 3:
		m_pScene2D->BindTexture("THREE");	// テクスチャ設定
		break;
	}
}

//==============================================================================
// 開始時カウントダウンの描画処理
//==============================================================================
void CStartCntdown::Draw(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Draw();
	}
}

//==============================================================================
// 開始時カウントダウンの生成処理
//==============================================================================
CStartCntdown *CStartCntdown::Create(void)
{
	// インスタンス生成
	CStartCntdown *pStartCntdown;
	pStartCntdown = new CStartCntdown;

	// 初期化
	pStartCntdown->Init();

	return pStartCntdown;
}