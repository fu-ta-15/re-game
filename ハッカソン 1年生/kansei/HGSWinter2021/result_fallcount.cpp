//==============================================================================
//
// リザルトの落下カウント描画処理〔result_fallcount.cpp〕
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
#include "result_fallcount.h"
#include "fall_count.h"


//==============================================================================
// コンストラクタ
//==============================================================================
CResultFallCount::CResultFallCount(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CResultFallCount::~CResultFallCount()
{
}

//==============================================================================
// リザルトの落下カウントの初期化処理
//==============================================================================
HRESULT CResultFallCount::Init(void)
{
	// 落下カウントの生成
	m_pFallCount = CFallCount::Create(RESULT_FC_POS, RESULT_FC_SIZE);

	m_nFall = m_pFallCount->GetFallNum();
	m_pFallCount->SetNumber(m_nFall);

	return S_OK;
}

//==============================================================================
// リザルトの落下カウントの終了処理
//==============================================================================
void CResultFallCount::Uninit(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->Uninit();
		m_pFallCount = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// リザルトの落下カウントの更新処理
//==============================================================================
void CResultFallCount::Update(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->SetNumber(m_nFall);

		m_pFallCount->Update();
	}
}

//==============================================================================
// リザルトの落下カウントの描画処理
//==============================================================================
void CResultFallCount::Draw(void)
{
	if (m_pFallCount != NULL)
	{
		m_pFallCount->Draw();
	}
}

//==============================================================================
// リザルトの落下カウントの生成処理
//==============================================================================
CResultFallCount *CResultFallCount::Create(void)
{
	// インスタンス生成
	CResultFallCount *pResultFallCount;
	pResultFallCount = new CResultFallCount;

	// 初期化
	pResultFallCount->Init();

	return pResultFallCount;
}