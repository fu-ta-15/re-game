//##################################################################################################################################################################//
//
// 壁処理 [wall.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "billboard.h"
#include "shadow.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define LENGTH_POLYGON_X					(5)								// 中心から各頂点の距離を求める数値
#define LENGTH_POLYGON_Y					(5)								// 中心から各頂点の距離を求める数値
#define LENGTH_POLYGON_Z					(50)								// 中心から各頂点の距離を求める数値
#define COLOR_RED							(255)								// 赤色
#define COLOR_BULUE							(255)								// 青色
#define COLOR_GREEN							(255)								// 緑色
#define COLOR_ALPHA							(255)								// アルファ値
#define PVTEX_MAX							(4)									// pVtx


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;		// テクスチャの情報
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;	// 頂点バッファの情報
Billboard g_Billboard;
int g_nNumShadowBillboard;

//=====================================================================================================================================================================//
// プレイヤーの初期化処理
//=====================================================================================================================================================================//
HRESULT InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg", &g_pTextureBillboard);

	if (g_pTextureBillboard == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\wall001.jpg");
	}

	// 中心座標
	g_Billboard.pos = D3DXVECTOR3(0.0f, 20.0f, 10.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_Billboard.pos.x - LENGTH_POLYGON_X, g_Billboard.pos.y + LENGTH_POLYGON_Y, g_Billboard.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_Billboard.pos.x + LENGTH_POLYGON_X, g_Billboard.pos.y + LENGTH_POLYGON_Y, g_Billboard.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_Billboard.pos.x - LENGTH_POLYGON_X, g_Billboard.pos.y, g_Billboard.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_Billboard.pos.x + LENGTH_POLYGON_X, g_Billboard.pos.y, g_Billboard.pos.z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	// 頂点カラーの設定・赤・緑・青・アルファ
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffBillboard->Unlock();

	//g_nNumShadowBillboard = SetShadow(g_Billboard.pos, 10.0f, 10.0f);

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitBillboard(void)
{
	// テクスチャの開放
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateBillboard(void)
{
	//SetPositionShadow(g_nNumShadowBillboard, g_Billboard.pos);
}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawBillboard(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// 計算用マトリックス
	D3DXMATRIX mtxTrans;
	// ビューマトリックス取得用
	D3DXMATRIX mtxView;
	// デバイスの取得
	pDevice = GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Billboard.mtxWorld);

	// ビューマトリックスの取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_Billboard.mtxWorld, NULL, &mtxView); // 逆行列を求める

	g_Billboard.mtxWorld._41 = 0.0f;
	g_Billboard.mtxWorld._42 = 0.0f;
	g_Billboard.mtxWorld._43 = 0.0f;

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Billboard.pos.x, g_Billboard.pos.y, g_Billboard.pos.z);
	D3DXMatrixMultiply(&g_Billboard.mtxWorld, &g_Billboard.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Billboard.mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

