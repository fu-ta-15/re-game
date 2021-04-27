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
#include "meshwall.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　マクロ定義
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED							(255)								// 赤色
#define COLOR_BULUE							(255)								// 青色
#define COLOR_GREEN							(255)								// 緑色
#define COLOR_ALPHA							(255)								// アルファ値
#define INDEX_MAX							(14)
#define PVTEX_MAX							(9)									// pVtx

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshWall = NULL;	// 頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureMeshWall = NULL;		// テクスチャの情報
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshWall = NULL;	// インデックスバッファの情報

MeshWall g_aMeshWall[MAX_WALL];

//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
HRESULT InitMeshWall(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスのポインタ
	VERTEX_3D *pVtx;							// 頂点ポインタ
	MeshWall *pMeshWall = &g_aMeshWall[0];

	// テクスチャの読み込み
	//D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wall001.jpg", &g_pTextureMeshWall);

	if (g_pTextureMeshWall == NULL)
	{
		printf("%s", "データ読み込み失敗");
	}
	else
	{
		printf("%s", "\n データ読み込み成功 \n data\\TEXTURE\\wall001.jpg");
	}

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		pMeshWall->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中心座標
		pMeshWall->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転
		pMeshWall->fIdxDeceHeight = 0.0f;				// 高さ
		pMeshWall->fIdxDeceWidth = 0.0f;				// 幅
		pMeshWall->bUse = false;
	}

	// 番号
	int pVtxIdx = 0;


	// 頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshWall,
		NULL)))
	{
		return E_FAIL;
	}

	// 頂点バッファをロック
	g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		//各頂点の座標
		pVtx[0].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[4].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[5].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[6].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[7].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
		pVtx[8].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);

		// 法線
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[5].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[6].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[7].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[8].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		// 頂点情報分進める
		pVtx += PVTEX_MAX;
	}
	// 頂点バッファをアンロック
	g_pVtxBuffMeshWall->Unlock();

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX_MAX * MAX_WALL,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshWall,
		NULL);

	WORD *pIdx;	// インデックス情報へのポインタ

	// インデックスバッファをロックし、番号データへのポインタを取得
	g_pIdxBuffMeshWall->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++)
	{
		// 番号データの設定
		pIdx[0] = 3 + pVtxIdx;
		pIdx[1] = 0 + pVtxIdx;
		pIdx[2] = 4 + pVtxIdx;
		pIdx[3] = 1 + pVtxIdx;
		pIdx[4] = 5 + pVtxIdx;
		pIdx[5] = 2 + pVtxIdx;
		pIdx[6] = 2 + pVtxIdx;
		pIdx[7] = 6 + pVtxIdx;
		pIdx[8] = 6 + pVtxIdx;
		pIdx[9] = 3 + pVtxIdx;
		pIdx[10] = 7 + pVtxIdx;
		pIdx[11] = 4 + pVtxIdx;
		pIdx[12] = 8 + pVtxIdx;
		pIdx[13] = 5 + pVtxIdx;

		// 総合頂点（９）分進める
		pVtxIdx += PVTEX_MAX;
		// 総合番号（１４）分進める
		pIdx += INDEX_MAX;
	}
	// インデックスバッファをアンロック
	g_pIdxBuffMeshWall->Unlock();

	// 初期化完了
	return S_OK;
}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitMeshWall(void)
{
	// テクスチャの開放
	if (g_pTextureMeshWall != NULL)
	{
		g_pTextureMeshWall->Release();
		g_pTextureMeshWall = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshWall != NULL)
	{
		g_pVtxBuffMeshWall->Release();
		g_pVtxBuffMeshWall = NULL;
	}
	// インデックスバッファの開放
	if (g_pIdxBuffMeshWall != NULL)
	{
		g_pIdxBuffMeshWall->Release();
		g_pIdxBuffMeshWall = NULL;
	}
}

//=====================================================================================================================================================================//
// ポリゴンの更新処理
//=====================================================================================================================================================================//
void UpdateMeshWall(void)
{
	// 構造体のポインタ取得
	MeshWall *pMeshWall = &g_aMeshWall[0];

	VERTEX_3D *pVtx;							// 頂点ポインタ

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == true)
		{
			// 頂点バッファをロック
			g_pVtxBuffMeshWall->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (PVTEX_MAX * nCntWall);

			//各頂点の座標
			pVtx[0].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);

			pVtx[1].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);
			
			pVtx[2].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + (pMeshWall->fIdxDeceHeight * 2), pMeshWall->pos.z);
			
			pVtx[3].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[4].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[5].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y + pMeshWall->fIdxDeceHeight, pMeshWall->pos.z);
			
			pVtx[6].pos = D3DXVECTOR3(pMeshWall->pos.x - pMeshWall->fIdxDeceWidth, pMeshWall->pos.y , pMeshWall->pos.z);
			
			pVtx[7].pos = D3DXVECTOR3(pMeshWall->pos.x, pMeshWall->pos.y , pMeshWall->pos.z);
			
			pVtx[8].pos = D3DXVECTOR3(pMeshWall->pos.x + pMeshWall->fIdxDeceWidth, pMeshWall->pos.y , pMeshWall->pos.z);

			// 頂点バッファをアンロック
			g_pVtxBuffMeshWall->Unlock();
		}
	}
}

//=====================================================================================================================================================================//
// ポリゴンの描画処理
//=====================================================================================================================================================================//
void DrawMeshWall(void)
{
	// デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	// デバイスの取得
	pDevice = GetDevice();

	MeshWall *pMeshWall = &g_aMeshWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == true)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&pMeshWall->mtxWorld);

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMeshWall->rot.y, pMeshWall->rot.x, pMeshWall->rot.z);
			D3DXMatrixMultiply(&pMeshWall->mtxWorld, &pMeshWall->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pMeshWall->pos.x, pMeshWall->pos.y, pMeshWall->pos.z);
			D3DXMatrixMultiply(&pMeshWall->mtxWorld, &pMeshWall->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pMeshWall->mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffMeshWall, 0, sizeof(VERTEX_3D));
			// インデックスバッファをデータストリームに設定
			pDevice->SetIndices(g_pIdxBuffMeshWall);
			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
				0, 0,
				9 * nCntWall, 0, 12);
		}
	}
}

void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight)
{
	MeshWall *pMeshWall = &g_aMeshWall[0];

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, pMeshWall++)
	{
		if (pMeshWall->bUse == false)
		{
			pMeshWall->pos = pos;
			pMeshWall->rot = rot;
			pMeshWall->fIdxDeceHeight = fHeight;
			pMeshWall->fIdxDeceWidth = fWidth;

			pMeshWall->bUse = true;
			break;
		}
	}
}

MeshWall * GetMeshWall(void)
{
	return &g_aMeshWall[0];
}
