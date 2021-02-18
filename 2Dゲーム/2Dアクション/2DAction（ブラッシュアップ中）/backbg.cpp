//##################################################################################################################################################################//
//
// 奥背景処理 [backbg.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "backbg.h"
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
#define HEIGTH_SIZE			(200)			// 
#define MAX_RIGTH			(3000)			// 
#define MAX_LEFT			(-3000)			// 
#define MOVE_SPEED			(0.003f)		// 

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackBg = NULL;	// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureBackBg = NULL;			// テクスチャの情報
BACKBG g_BackBg;

//=====================================================================================================================================================================//
// 背景の初期化処理
//=====================================================================================================================================================================//
HRESULT InitBackBg(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// 頂点ポインタ
	VERTEX_2D *pVtx;

	g_BackBg.BackMove = BACKBG_MOVE_START;
	g_BackBg.move = 0.0f;
	g_BackBg.nCunt = 0;
	g_BackBg.Move = 0.0f;
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg000.png", &g_pTextureBackBg);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBackBg, NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロック・頂点情報へのポインタを取得
	g_pVtxBuffBackBg->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffBackBg->Unlock();

	// 処理完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitBackBg(void)
{
	//テクスチャの開放
	if (g_pTextureBackBg != NULL)
	{
		g_pTextureBackBg->Release();
		g_pTextureBackBg = NULL;
	}

	//頂点バッファの開放
	if (g_pVtxBuffBackBg != NULL)
	{
		g_pVtxBuffBackBg->Release();
		g_pVtxBuffBackBg = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateBackBg(void)
{


}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawBackBg(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBackBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBackBg);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void MoveBack(void)
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
	g_pVtxBuffBackBg->Lock(0, 0, (void**)&pVtx, 0);

	g_BackBg.Move = MOVE_SPEED;

	if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
	{
		g_BackBg.move -= g_BackBg.Move;	// テクスチャの移動
	}
	else if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
	{
		g_BackBg.move += g_BackBg.Move;	// テクスチャの移動
	}
	else if (pBrock->HitPlayer == true)
	{
		g_BackBg.move += 0.0f;
	}

	//テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_BackBg.move), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_BackBg.move), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_BackBg.move), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_BackBg.move), 0.0f);

	//頂点バッファをアンロック
	g_pVtxBuffBackBg->Unlock();
}

BACKBG *GetBackBg(void)
{
	return &g_BackBg;
}
