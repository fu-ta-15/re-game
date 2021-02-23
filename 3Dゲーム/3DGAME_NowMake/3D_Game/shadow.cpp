//##################################################################################################################################################################//
//
// 影処理 [shadow.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "shadow.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define LENGTH_SHADOW_X						(15)								// 中心から各頂点の距離を求める数値
#define LENGTH_SHADOW_Y						(3)								// 中心から各頂点の距離を求める数値
#define LENGTH_SHADOW_Z						(15)								// 中心から各頂点の距離を求める数値
#define COLOR_RED							(155)								// 赤色
#define COLOR_BULUE							(255)								// 青色
#define COLOR_GREEN							(155)								// 緑色
#define COLOR_ALPHA							(255)								// アルファ値
#define PVTEX_MAX							(4)									// pVtx
#define MAX_SHADOW							(3)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;		// テクスチャの情報
Shadow g_Shadow;

//=====================================================================================================================================================================//
// プレイヤーの初期化処理
//=====================================================================================================================================================================//
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_pTextureShadow);

	if (g_pTextureShadow == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\shadow000.jpg");
	}
	// 中心座標
	g_Shadow.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 回転
	g_Shadow.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_Shadow.pos.x - LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z + LENGTH_SHADOW_Z);
	pVtx[1].pos = D3DXVECTOR3(g_Shadow.pos.x + LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z + LENGTH_SHADOW_Z);
	pVtx[2].pos = D3DXVECTOR3(g_Shadow.pos.x - LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z - LENGTH_SHADOW_Z);
	pVtx[3].pos = D3DXVECTOR3(g_Shadow.pos.x + LENGTH_SHADOW_X, g_Shadow.pos.y, g_Shadow.pos.z - LENGTH_SHADOW_Z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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
	g_pVtxBuffShadow->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// ポリゴンの終了処理
//=====================================================================================================================================================================//
void UninitShadow(void)
{
	// テクスチャの開放
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateShadow(void)
{

	if (g_Shadow.bUse == true)
	{

	}

}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawShadow(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	// デバイスの取得
	pDevice = GetDevice();

	// 減産合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Shadow.mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow.rot.y, g_Shadow.rot.x, g_Shadow.rot.z);
	D3DXMatrixMultiply(&g_Shadow.mtxWorld, &g_Shadow.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Shadow.pos.x, g_Shadow.pos.y, g_Shadow.pos.z);
	D3DXMatrixMultiply(&g_Shadow.mtxWorld, &g_Shadow.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Shadow.mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureShadow);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// 影の設定
int SetShadow(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	int nIdx = -1;
	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow.bUse == false)
		{
			g_Shadow.pos = pos;


			g_Shadow.bUse = true;
		}
	}

	return nIdx;
}

// 誰の影か
void SetPositionShadow(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;							// 頂点ポインタ
												// 頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(pos.x - LENGTH_SHADOW_X, 0.0f, pos.z + LENGTH_SHADOW_Z);
	pVtx[1].pos = D3DXVECTOR3(pos.x + LENGTH_SHADOW_X, 0.0f, pos.z + LENGTH_SHADOW_Z);
	pVtx[2].pos = D3DXVECTOR3(pos.x - LENGTH_SHADOW_X, 0.0f, pos.z - LENGTH_SHADOW_Z);
	pVtx[3].pos = D3DXVECTOR3(pos.x + LENGTH_SHADOW_X, 0.0f, pos.z - LENGTH_SHADOW_Z);
	// 頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

}

Shadow *GetShadow(void)
{
	return &g_Shadow;
}
