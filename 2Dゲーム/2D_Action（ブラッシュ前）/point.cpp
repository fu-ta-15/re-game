//##################################################################################################################################################################//
//
// カーソル処理 [point.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "point.h"
#include "input.h"
#include "player.h"
#include "brock.h"
#include "padinput.h"
#include "action.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED						(255)											// 赤色
#define COLOR_BULUE						(255)											// 青色
#define COLOR_GREEN						(255)											// 緑色
#define COLOR_ALPHA						(255)											// アルファ値

#define POINT_X							(15)											// 中心座標X
#define POINT_Y							(15)											// 中心座標Y
#define POINT_POS						(50.0f)
#define POINT_TYPE						(2)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTexturePoint[2] = {};		// テクスチャへのポイント
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPoint = NULL;	// 頂点バッファへのポインタ
POINTER g_Pointer;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ポイントの初期化処理
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
HRESULT InitPoint(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// デバイスのポインタ
	VERTEX_2D *pVtx;			// VERTEXのポインタ

								// 構造体の初期化
	g_Pointer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Pointer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// デバイスの取得
	pDevice = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wepon0.png", &g_pTexturePoint[ACTION_MODE_ATTACK]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wepon1.png", &g_pTexturePoint[ACTION_MODE_DIG]);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * POINT_TYPE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPoint, NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファのロック
	g_pVtxBuffPoint->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCuntPointer = 0; nCuntPointer < POINT_TYPE; nCuntPointer++)
	{
		// テクスチャの頂点座標
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		// rhwの設定		=	1.0f固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// 頂点カラーの設定・赤・緑・青
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		pVtx += 4;
	}

	// 頂点バッファのアンロック
	g_pVtxBuffPoint->Unlock();
	// S_OKを返す
	return S_OK;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ポイントの終了処理
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void UninitPoint(void)
{
	if (g_pVtxBuffPoint != NULL)
	{
		g_pVtxBuffPoint->Release();
		g_pVtxBuffPoint = NULL;
	}
	for (int nCuntPointer = 0; nCuntPointer < POINT_TYPE; nCuntPointer++)
	{
		if (g_pTexturePoint[nCuntPointer] != NULL)
		{
			g_pTexturePoint[nCuntPointer]->Release();
			g_pTexturePoint[nCuntPointer] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ポイントの更新処理
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void UpdatePoint(void)
{
	// VERTEXのポインタ
	VERTEX_2D *pVtx;
	// 構造体のポインタ
	PLAYER *pPlayer = GetPlayer();
	POINTER *pPoint = GetPointer();

	// プレイヤーの位置を取得
	if (pPlayer->PlayerDire == DIRECTION_RIGTH)
	{// 右向き
		pPoint->pos.x = (pPlayer->pos.x + POINT_POS);
	}
	else if (pPlayer->PlayerDire == DIRECTION_LEFT)
	{// 左向き
		pPoint->pos.x = (pPlayer->pos.x - POINT_POS);
	}

	pPoint->pos.y = pPlayer->pos.y;

	// 頂点バッファのロック
	g_pVtxBuffPoint->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の更新(X座標・Y座標・Z座標(2Dは0固定)右回りで描画）
	pVtx[0].pos = D3DXVECTOR3(pPoint->pos.x - POINT_X, pPoint->pos.y + POINT_X, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPoint->pos.x - POINT_X, pPoint->pos.y - POINT_X, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPoint->pos.x + POINT_X, pPoint->pos.y + POINT_X, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPoint->pos.x + POINT_X, pPoint->pos.y - POINT_X, 0.0f);

	// 頂点バッファのアンロック
	g_pVtxBuffPoint->Unlock();

	if (GetKeyboardTrigger(DIK_K) == true || GetKeypadTrigger(1) == true)
	{

	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ポイントの描画処理
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void DrawPoint(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 情報の取得
	ACTIONPLAYER *pActionPlayer = GetAction();

	// テクスチャの番号
	int SetTex = 0;

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPoint, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (pActionPlayer->Amode)
	{// テクスチャの設定
	case ACTION_MODE_ATTACK:
		SetTex = ACTION_MODE_ATTACK;
		break;
	case ACTION_MODE_DIG:
		SetTex = ACTION_MODE_DIG;
		break;
	default:
		break;
	}
	// 指定したテクスチャをセット
	pDevice->SetTexture(0, g_pTexturePoint[SetTex]);
	// 開始のポイントから描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 , 2);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ポイントの情報
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
POINTER *GetPointer(void)
{
	return &g_Pointer;
}
