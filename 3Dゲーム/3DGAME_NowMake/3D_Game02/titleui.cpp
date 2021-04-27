//##################################################################################################################################################################//
//
// タイトルUI処理 [titleui.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "title.h"



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define TITLE_UI_SIZE		(D3DXVECTOR3(200.0f,70.0f,0.0f))
#define TITLE_UI_POS		(D3DXVECTOR3(SCREEN_WIDTH/2,500.0f,0.0f))
#define ALPHA_SPEED			(0.02f)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleUi = NULL;		// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureTitleUi = NULL;	// テクスチャの情報
TitleUi g_TitleUi;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void VtxBuffSet(void);
void FadeAlpha(void);


//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitTitleUi(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_TitleUi.col = COLOR_WHITE;
	g_TitleUi.pos = TITLE_UI_POS;
	g_TitleUi.size = TITLE_UI_SIZE;
	g_TitleUi.nTurnFade = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Button.png", &g_pTextureTitleUi);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitleUi, NULL)))
	{
		return E_FAIL;
	}

	// 頂点情報の設定
	VtxBuffSet();

	return S_OK;
}


//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitTitleUi(void)
{
	if (g_pVtxBuffTitleUi != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffTitleUi->Release();
		g_pVtxBuffTitleUi = NULL;
	}
	if (g_pTextureTitleUi != NULL)
	{// テクスチャの開放
		g_pTextureTitleUi->Release();
		g_pTextureTitleUi = NULL;
	}
}


//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateTitleUi(void)
{
	// 頂点のポインタ
	VERTEX_2D *pVtx;

	FadeAlpha();

	//頂点バッファのロック
	g_pVtxBuffTitleUi->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定・赤・緑・青
	pVtx[0].col = g_TitleUi.col;
	pVtx[1].col = g_TitleUi.col;
	pVtx[2].col = g_TitleUi.col;
	pVtx[3].col = g_TitleUi.col;

	//頂点バッファのアンロック
	g_pVtxBuffTitleUi->Unlock();
}


//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawTitleUi(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitleUi, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTitleUi);

	// 描画設定
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}


//=====================================================================================================================================================================//
// 頂点バッファの情報の設定
//=====================================================================================================================================================================//
void VtxBuffSet(void)
{
	// 頂点のポインタ
	VERTEX_2D *pVtx;

	//頂点バッファのロック
	g_pVtxBuffTitleUi->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_TitleUi.pos.x - g_TitleUi.size.x, g_TitleUi.pos.y + g_TitleUi.size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_TitleUi.pos.x - g_TitleUi.size.x, g_TitleUi.pos.y - g_TitleUi.size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_TitleUi.pos.x + g_TitleUi.size.x, g_TitleUi.pos.y + g_TitleUi.size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_TitleUi.pos.x + g_TitleUi.size.x, g_TitleUi.pos.y - g_TitleUi.size.y, 0.0f);

	//rhwの設定		=	1.0f固定
	pVtx[0].rhw = RHW;
	pVtx[1].rhw = RHW;
	pVtx[2].rhw = RHW;
	pVtx[3].rhw = RHW;

	//頂点カラーの設定・赤・緑・青
	pVtx[0].col = g_TitleUi.col;
	pVtx[1].col = g_TitleUi.col;
	pVtx[2].col = g_TitleUi.col;
	pVtx[3].col = g_TitleUi.col;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点バッファのアンロック
	g_pVtxBuffTitleUi->Unlock();
}

//=====================================================================================================================================================================//
// α値の更新
//=====================================================================================================================================================================//
void FadeAlpha(void)
{
	// αフェイドの設定
	if (g_TitleUi.nTurnFade == 0) { g_TitleUi.col.a -= ALPHA_SPEED; }		// 0の場合 = 減少
	if (g_TitleUi.nTurnFade == 1) { g_TitleUi.col.a += ALPHA_SPEED; }		// 1の場合 = 増加

	// 0と1を切り替え
	if (g_TitleUi.col.a <= 0 || g_TitleUi.col.a >= 1) { g_TitleUi.nTurnFade ^= 1; }

}
