//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	title.cpp
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//インクルードファイル
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#include "title.h"
#include "object2d.h"
#include "manager.h"
#include "inputkeyboard.h"
#include "fade.h"
#include "renderer.h"

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//静的メンバ変数宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
LPDIRECT3DTEXTURE9 CTitle::m_pTexture = NULL;

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//コンストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTitle::CTitle()
{
	m_pTitleScreen = NULL;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//デストラクタ
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CTitle::~CTitle()
{

}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//初期化関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTitle::Init(void)
{
	m_pTitleScreen = CObject2D::Create(SCREEN_SIZE / 2, SCREEN_SIZE, 0);
	m_pTitleScreen->BindTexture(m_pTexture);
	return S_OK;
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//更新関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTitle::Update(void)
{
	if (CManager::GetInput()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_TUTORIAL);
	}
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//描画関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTitle::Draw(void)
{
	
}
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//終了関数
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTitle::Uninit(void)
{
	m_pTitleScreen->Uninit();
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ読み込み
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
HRESULT CTitle::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,"Data/tex/title.png",	&m_pTexture);					
	return S_OK;
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//テクスチャ破棄
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
void CTitle::Unload()
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}