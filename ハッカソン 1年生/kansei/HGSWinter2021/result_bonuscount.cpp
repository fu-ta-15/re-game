//==============================================================================
//
// リザルトのボーナスカウント描画処理〔result_bonuscount.cpp〕
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
#include "bonus_count.h"
#include "result_bonuscount.h"
#include "fall_count.h"


//==============================================================================
// コンストラクタ
//==============================================================================
CResultBonus::CResultBonus(int nPriority) : CResult(nPriority)
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CResultBonus::~CResultBonus()
{
}

//==============================================================================
// リザルトの落下カウントの初期化処理
//==============================================================================
HRESULT CResultBonus::Init(void)
{
	// 落下カウントの生成
	m_pBonusCount = CBonusCount::Create(RESULT_BONUS_POS, RESULT_BONUS_SIZE);

	m_nBonus = m_pBonusCount->GetBonusNum();
	m_pBonusCount->SetNumber(m_nBonus);

	return S_OK;
}

//==============================================================================
// リザルトの落下カウントの終了処理
//==============================================================================
void CResultBonus::Uninit(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->Uninit();
		m_pBonusCount = NULL;
	}

	Release();	// インスタンスのデリート
}

//==============================================================================
// リザルトの落下カウントの更新処理
//==============================================================================
void CResultBonus::Update(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->SetNumber(m_nBonus);

		m_pBonusCount->Update();
	}
}

//==============================================================================
// リザルトのボーナスカウントの描画処理
//==============================================================================
void CResultBonus::Draw(void)
{
	if (m_pBonusCount != NULL)
	{
		m_pBonusCount->Draw();
	}
}

//==============================================================================
// リザルトのボーナスカウントの生成処理
//==============================================================================
CResultBonus *CResultBonus::Create(void)
{
	// インスタンス生成
	CResultBonus *pResultBonus;
	pResultBonus = new CResultBonus;

	// 初期化
	if (pResultBonus != NULL)
	{
		pResultBonus->Init();
	}

	return pResultBonus;
}