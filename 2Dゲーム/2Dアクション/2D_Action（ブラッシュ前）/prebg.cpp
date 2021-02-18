//##################################################################################################################################################################//
//
// 手前背景処理 [prebg.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "prebg.h"
#include "player.h"
#include "stage.h"
#include "brock.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// 赤色
#define COLOR_BULUE			(255)			// 青色
#define COLOR_GREEN			(255)			// 緑色
#define COLOR_ALPHA			(255)			// アルファ値
#define HEIGTH_SIZE			(500)
#define MAX_RIGTH			(3000)
#define MAX_LEFT			(-3000)
#define MOVE_SPEED			(0.004f)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPreBg = NULL;	// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTexturePreBg = NULL;			// テクスチャの情報
PREBG g_PreBg;
//=====================================================================================================================================================================//
// 背景の初期化処理
//=====================================================================================================================================================================//
HRESULT InitPreBg(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点ポインタ
	VERTEX_2D *pVtx;

	g_PreBg.PreMove = PREBG_MOVE_START;
	g_PreBg.move = 0.0f;
	g_PreBg.nCunt = 0;
	g_PreBg.Move = 0.0f;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ground.png", &g_pTexturePreBg);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPreBg, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, HEIGTH_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, HEIGTH_SIZE, 0.0f);

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

	//頂点バッファをアンロック
	g_pVtxBuffPreBg->Unlock();

	// 処理完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitPreBg(void)
{
	//テクスチャの開放
	if (g_pTexturePreBg != NULL)
	{
		g_pTexturePreBg->Release();
		g_pTexturePreBg = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffPreBg != NULL)
	{
		g_pVtxBuffPreBg->Release();
		g_pVtxBuffPreBg = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdatePreBg(void)
{

}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawPreBg(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPreBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePreBg);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================================================================================================================================//
// 背景の移動
//=====================================================================================================================================================================//
void MovePre(void)
{
	// 頂点ポインタ
	VERTEX_2D *pVtx;
	GAMEPOS *pGamePos;
	PLAYER *pPlayer;
	BROCK *pBrock;

	pBrock = GetBrock();
	pPlayer = GetPlayer();
	pGamePos = GetGamePos();

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);

	g_PreBg.Move = MOVE_SPEED;

	if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
	{
		g_PreBg.move -= g_PreBg.Move;	// テクスチャの移動
	}
	else if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
	{
		g_PreBg.move += g_PreBg.Move;	// テクスチャの移動
	}
	else if (pBrock->HitPlayer == true)
	{
		g_PreBg.move += 0.0f;	// テクスチャの移動
	}

	//テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffPreBg->Unlock();
}
////=====================================================================================================================================================================//
//// 背景の移動
////=====================================================================================================================================================================//
//void LeftMovePre(void)
//{
//	// 頂点ポインタ
//	VERTEX_2D *pVtx;
//	GAMEPOS *pGamePos;
//	pGamePos = GetGamePos();
//
//
//	//頂点バッファをロック・頂点情報へのポインタを取得
//	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);
//
//	g_PreBg.move -= g_PreBg.Move;	// テクスチャの移動
//
//	g_PreBg.Move = MOVE_SPEED;
//
//	//テクスチャの頂点座標の設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 0.0f);
//
//	//頂点バッファをアンロック
//	g_pVtxBuffPreBg->Unlock();
//}

PREBG *GetPreBg(void)
{
	return &g_PreBg;
}
