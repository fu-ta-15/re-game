//==============================================================================
//
// リザルトタイマー描画処理〔result_fallcount.cpp〕
// Author : Mare Horiai
//
//==============================================================================
//#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "polygon.h"
#include "sound.h"
#include "title.h"
#include "fade.h"
#include "result_timer.h"
#include "timer_count.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CResultTimer::CResultTimer(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CResultTimer::~CResultTimer()
{
}

//==============================================================================
// リザルトタイマーの初期化処理
//==============================================================================
HRESULT CResultTimer::Init(void)
{
	// 落下カウントの生成
	m_pTimerCount = CTimerCount::Create(RESULT_TIMER_POS, RESULT_TIMER_SIZE);

	m_nTimer = m_pTimerCount->GetTimerNum();
	m_pTimerCount->SetNumber(m_nTimer);

	return S_OK;
}

//==============================================================================
// リザルトタイマーの終了処理
//==============================================================================
void CResultTimer::Uninit(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Uninit();
		m_pTimerCount = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// リザルトタイマーの更新処理
//==============================================================================
void CResultTimer::Update(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->SetNumber(m_nTimer);

		m_pTimerCount->Update();
	}
}

//==============================================================================
// リザルトタイマーの描画処理
//==============================================================================
void CResultTimer::Draw(void)
{
	if (m_pTimerCount != NULL)
	{
		m_pTimerCount->Draw();
	}
}

//==============================================================================
// リザルトタイマーの生成処理
//==============================================================================
CResultTimer *CResultTimer::Create(void)
{
	// インスタンス生成
	CResultTimer *pResultTimer;
	pResultTimer = new CResultTimer;

	// 初期化
	if (pResultTimer != NULL)
	{
		pResultTimer->Init();
	}

	return pResultTimer;
}