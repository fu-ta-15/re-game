//##################################################################################################################################################################//
//
// UI処理 [ui.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "ui.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// 赤色
#define COLOR_BULUE			(255)			// 青色
#define COLOR_GREEN			(255)			// 緑色
#define COLOR_ALPHA			(255)			// アルファ値

#define UI_HEIGHT_UP		(0)				// UI背景のPOS
#define UI_HEIGHT_DOWN		(350)			// UI背景のPOS
#define UI_WIDTH_RIGHT		(SCREEN_WIDTH)	// UI背景のPOS
#define UI_WIDTH_LEFT		(980)			// UI背景のPOS

#define P_HEIGHT_UP			(10)			// PerfectのUIのPOS
#define P_HEIGHT_DOWN		(55)			// PerfectのUIのPOS
#define P_WIDTH_RIGHT		(1160)			// PerfectのUIのPOS
#define P_WIDTH_LEFT		(1000)			// PerfectのUIのPOS

#define G_HEIGHT_UP			(90)			// GoodのUIのPOS
#define G_HEIGHT_DOWN		(130)			// GoodのUIのPOS
#define G_WIDTH_RIGHT		(1150)			// GoodのUIのPOS
#define G_WIDTH_LEFT		(1000)			// GoodのUIのPOS

#define B_HEIGHT_UP			(170)			// BadのUIのPOS
#define B_HEIGHT_DOWN		(200)			// BadのUIのPOS
#define B_WIDTH_RIGHT		(1180)			// BadのUIのPOS
#define B_WIDTH_LEFT		(1000)			// BadのUIのPOS

#define S_HEIGHT_UP			(270)			// ScoreのUIのPOS
#define S_HEIGHT_DOWN		(295)			// ScoreのUIのPOS
#define S_WIDTH_RIGHT		(1080)			// ScoreのUIのPOS
#define S_WIDTH_LEFT		(1030)			// ScoreのUIのPOS

#define MAX_UI_NUM			(5)				// UIの数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;		// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureUi = NULL;				// テクスチャの情報
LPDIRECT3DTEXTURE9 g_pTextureUiPerfect = NULL;		// テクスチャの情報
LPDIRECT3DTEXTURE9 g_pTextureUiGood = NULL;			// テクスチャの情報
LPDIRECT3DTEXTURE9 g_pTextureUiBad = NULL;			// テクスチャの情報
LPDIRECT3DTEXTURE9 g_pTextureUiScore = NULL;		// テクスチャの情報

//=====================================================================================================================================================================//
// 背景の初期化処理
//=====================================================================================================================================================================//
HRESULT InitUi(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点ポインタ
	VERTEX_2D *pVtx;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI.png", &g_pTextureUi);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi02.png", &g_pTextureUiPerfect);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi01.png", &g_pTextureUiGood);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi00.png", &g_pTextureUiBad);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Score00.png", &g_pTextureUiScore);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUi, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
	/* UIの背景 */
	pVtx[0].pos = D3DXVECTOR3(UI_WIDTH_LEFT, UI_HEIGHT_DOWN, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(UI_WIDTH_LEFT, UI_HEIGHT_UP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(UI_WIDTH_RIGHT, UI_HEIGHT_DOWN, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(UI_WIDTH_RIGHT, UI_HEIGHT_UP, 0.0f);
	/* Perfectの文字 */
	pVtx[4].pos = D3DXVECTOR3(P_WIDTH_LEFT, P_HEIGHT_DOWN, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(P_WIDTH_LEFT, P_HEIGHT_UP, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(P_WIDTH_RIGHT, P_HEIGHT_DOWN, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(P_WIDTH_RIGHT, P_HEIGHT_UP, 0.0f);
	/* Goodの文字 */
	pVtx[8].pos = D3DXVECTOR3(G_WIDTH_LEFT, G_HEIGHT_DOWN, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(G_WIDTH_LEFT, G_HEIGHT_UP, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(G_WIDTH_RIGHT, G_HEIGHT_DOWN, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(G_WIDTH_RIGHT, G_HEIGHT_UP, 0.0f);
	/* Badの文字 */
	pVtx[12].pos = D3DXVECTOR3(B_WIDTH_LEFT, B_HEIGHT_DOWN, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(B_WIDTH_LEFT, B_HEIGHT_UP, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(B_WIDTH_RIGHT, B_HEIGHT_DOWN, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(B_WIDTH_RIGHT, B_HEIGHT_UP, 0.0f);
	/* Scoreの文字 */
	pVtx[16].pos = D3DXVECTOR3(S_WIDTH_LEFT, S_HEIGHT_DOWN, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(S_WIDTH_LEFT, S_HEIGHT_UP, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(S_WIDTH_RIGHT, S_HEIGHT_DOWN, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(S_WIDTH_RIGHT, S_HEIGHT_UP, 0.0f);

	for (int nCnt = 0; nCnt < MAX_UI_NUM; nCnt++)
	{
		//rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定・赤・緑・青・アルファ
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//テクスチャの頂点座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点情報更新
		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffUi->Unlock();

	// 処理完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitUi(void)
{
	if (g_pTextureUi != NULL)
	{// テクスチャの開放
		g_pTextureUi->Release();
		g_pTextureUi = NULL;
	}
	if (g_pTextureUiPerfect != NULL)
	{// テクスチャの開放
		g_pTextureUiPerfect->Release();
		g_pTextureUiPerfect = NULL;
	}
	if (g_pTextureUiGood != NULL)
	{// テクスチャの開放
		g_pTextureUiGood->Release();
		g_pTextureUiGood = NULL;
	}
	if (g_pTextureUiBad != NULL)
	{// テクスチャの開放
		g_pTextureUiBad->Release();
		g_pTextureUiBad = NULL;
	}
	if (g_pTextureUiScore != NULL)
	{// テクスチャの開放
		g_pTextureUiScore->Release();
		g_pTextureUiScore = NULL;
	}

	if (g_pVtxBuffUi != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateUi(void)
{

}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawUi(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureUi);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureUiPerfect);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureUiGood);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureUiBad);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 12, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureUiScore);
	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 16, 2);
}