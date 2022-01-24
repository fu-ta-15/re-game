//==============================================================================
//
// タイマーロゴ描画処理〔timer_logo.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "number.h"
#include "texture.h"
#include "bonus_logo.h"

//==============================================================================
// コンストラクタ
//==============================================================================
CBonusLogo::CBonusLogo()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CBonusLogo::~CBonusLogo()
{

}

//==============================================================================
// タイマーロゴの初期化処理
//==============================================================================
HRESULT CBonusLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// 2Dポリゴンを生成
	m_pScene2D = CScene2D::Create();

	if (m_pScene2D != NULL)
	{
		// 位置設定
		m_pScene2D->SetPosition(pos);

		// サイズ設定
		m_pScene2D->SetSize(size);

		// テクスチャ設定
		m_pScene2D->BindTexture("BONUS_LOGO");

		m_pScene2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScene2D->SetTex(1, 1, 0, 0, 0, 0);
	}

	return S_OK;
}

//==============================================================================
// タイマーロゴの終了処理
//==============================================================================
void CBonusLogo::Uninit(void)
{
	if (m_pScene2D != NULL)
	{
		m_pScene2D->Uninit();
		m_pScene2D = NULL;
	}
}

//==============================================================================
// タイマーロゴの更新処理
//==============================================================================
void CBonusLogo::Update(void)
{

}

//==============================================================================
// タイマーロゴの描画処理
//==============================================================================
void CBonusLogo::Draw(void)
{

}

//==============================================================================
// タイマーロゴの生成処理
//==============================================================================
CBonusLogo *CBonusLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	// ローカル変数宣言
	CBonusLogo *pBonusLogo;
	pBonusLogo = new CBonusLogo;

	// 初期化
	if (pBonusLogo != NULL)
	{
		pBonusLogo->Init(pos, size);
	}

	return pBonusLogo;
}