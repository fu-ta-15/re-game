//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	tutorial.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "tutorial.h"
#include "object2d.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTutorial::CTutorial()
{
	m_pTutorialScreen = NULL;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTutorial::~CTutorial()
{

}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTutorial::Init(void)
{
	m_pTutorialScreen = CObject2D::Create(SCREEN_SIZE / 2, SCREEN_SIZE, 0);
	m_pTutorialScreen->BindTexture(m_pTexture);
	return S_OK;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorial::Update(void)
{
	if (CManager::GetInput()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorial::Draw(void)
{

}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorial::Uninit(void)
{
	m_pTutorialScreen->Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTutorial::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, "Data/tex/tutorial.png", &m_pTexture);
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTutorial::Unload()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}