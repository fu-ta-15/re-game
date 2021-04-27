//##################################################################################################################################################################//
//
// 地面処理 [meshfield.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "meshfield.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED							(255)								// 赤色
#define COLOR_BULUE							(255)								// 青色
#define COLOR_GREEN							(255)								// 緑色
#define COLOR_ALPHA							(255)								// アルファ値
#define INDEX_MAX							(14)
#define PVTEX_MAX							(9)									// pVtx
#define MAX_WALL							(3)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;	// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;		// テクスチャの情報
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	// インデックスバッファの情報
Meshfield g_aMeshfield;

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	Meshfield *pMeshfield = &g_aMeshfield;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg", &g_pTextureMeshfield);

	pMeshfield->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中心座標
	pMeshfield->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
	pMeshfield->fHeight = 0.0f;
	pMeshfield->fWidth = 0.0f;

	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//各頂点の座標
	pVtx[0].pos = D3DXVECTOR3(-LENGTH_POLYGON_X, 0.0f, LENGTH_POLYGON_Z);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, LENGTH_POLYGON_Z);
	pVtx[2].pos = D3DXVECTOR3(LENGTH_POLYGON_X, 0.0f, LENGTH_POLYGON_Z);
	pVtx[3].pos = D3DXVECTOR3(-LENGTH_POLYGON_X, 0.0f, 0.0f);
	pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(LENGTH_POLYGON_X, 0.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(-LENGTH_POLYGON_X, 0.0f, -LENGTH_POLYGON_Z);
	pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -LENGTH_POLYGON_Z);
	pVtx[8].pos = D3DXVECTOR3(LENGTH_POLYGON_X, 0.0f, -LENGTH_POLYGON_Z);

	// 法線
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[8].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定・赤・緑・青・アルファ
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[4].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[5].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[6].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[7].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[8].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// テクスチャの頂点座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[4].tex = D3DXVECTOR2(0.5f, 0.5f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.5f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[7].tex = D3DXVECTOR2(0.5f, 0.0f);
	pVtx[8].tex = D3DXVECTOR2(1.0f, 0.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffMeshfield->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD)*INDEX_MAX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	WORD *pIdx;	// インデックス情報へのポインタ

	// インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	// 番号データの設定
	//pIdx[0] = 3;
	//pIdx[1] = 0;

	//pIdx[2] = 4;
	//pIdx[3] = 1;

	//pIdx[4] = 5;
	//pIdx[5] = 2;

	//pIdx[6] = 2;
	//pIdx[7] = 6;

	//pIdx[8] = 6;
	//pIdx[9] = 3;

	//pIdx[10] = 7;
	//pIdx[11] = 4;

	//pIdx[12] = 8;
	//pIdx[13] = 5;

	int nT = 0;

	for (int nCnt = 0; nCnt < 7; nCnt++)
	{

		if ((nCnt) == 3)
		{
			pIdx[0] = nT - 1;
			pIdx[1] = nT + 3;
		}
		else
		{
			pIdx[0] = nT + 3;
			pIdx[1] = nT;
			nT += 1;
		}
		pIdx += 2;
	}

	// インデックスバッファをアンロック
	g_pIdxBuffMeshField->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitMeshfield(void)
{
	// テクスチャの開放
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}
	// インデックスバッファの開放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField->Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateMeshfield(void)
{

}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawMeshfield(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	// デバイスの取得
	pDevice = GetDevice();
	Meshfield *pMeshfield = &g_aMeshfield;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&pMeshfield->mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pMeshfield->rot.y, pMeshfield->rot.x, pMeshfield->rot.z);
	D3DXMatrixMultiply(&pMeshfield->mtxWorld, &pMeshfield->mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, pMeshfield->pos.x, pMeshfield->pos.y, pMeshfield->pos.z);
	D3DXMatrixMultiply(&pMeshfield->mtxWorld, &pMeshfield->mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &pMeshfield->mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));
	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
		0, 0,
		9, 0, 12);
}

Meshfield *GetMeshfield(void)
{
	return &g_aMeshfield;
}

