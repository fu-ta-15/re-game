//##################################################################################################################################################################//
//
// タイトルモデル処理 [titlemodel.cpp]
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
#define TITLE_MODEL_MAX					(1)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
TitleModel g_aTitleModel[TITLE_MODEL_MAX];					// Title用のモデル


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void GetVtxTitle(int nIdx);



//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
void InitTitleModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* モデル */
	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{
		/* No.0 体 */
		g_aTitleModel[nNumCnt].pos = D3DXVECTOR3(0.0f, 100.0f, 0.0f);
		g_aTitleModel[nNumCnt].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleModel[nNumCnt].rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
		g_aTitleModel[nNumCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitleModel[nNumCnt].pMesh = NULL;
		g_aTitleModel[nNumCnt].pBuffMat = NULL;
		g_aTitleModel[nNumCnt].pTexture = NULL;
		g_aTitleModel[nNumCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ファイルの読み込み
		/* No.0 岩 */
		D3DXLoadMeshFromX("data\\MODEL\\Title.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aTitleModel[nNumCnt].pBuffMat, NULL, &g_aTitleModel[nNumCnt].NumMat, &g_aTitleModel[nNumCnt].pMesh);

		g_aTitleModel[nNumCnt].pMat = (D3DXMATERIAL*)g_aTitleModel[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nNumCnt].NumMat; nCntMat++)
		{
			if (g_aTitleModel[nNumCnt].pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, g_aTitleModel[nNumCnt].pMat[nCntMat].pTextureFilename, &g_aTitleModel[nNumCnt].pTexture);
			}
		}

		// モデルの頂点抜き出し
		GetVtxTitle(nNumCnt);
	}
}


//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitTitleModel(void)
{
	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{
		if (g_aTitleModel[nNumCnt].pMesh != NULL)
		{// メッシュの破棄
			g_aTitleModel[nNumCnt].pMesh->Release();
			g_aTitleModel[nNumCnt].pMesh = NULL;
		}
		if (g_aTitleModel[nNumCnt].pBuffMat != NULL)
		{// マテリアルの破棄
			g_aTitleModel[nNumCnt].pBuffMat->Release();
			g_aTitleModel[nNumCnt].pBuffMat = NULL;
		}
		if (g_aTitleModel[nNumCnt].pTexture != NULL)
		{
			g_aTitleModel[nNumCnt].pTexture->Release();
			g_aTitleModel[nNumCnt].pTexture = NULL;
		}
	}
}


//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateTitleModel(void)
{
}


//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawTitleModel(void)
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ


	for (int nNumCnt = 0; nNumCnt < TITLE_MODEL_MAX; nNumCnt++)
	{

		D3DXMatrixIdentity(&g_aTitleModel[nNumCnt].mtxWorld);

		// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTitleModel[nNumCnt].rot.y, g_aTitleModel[nNumCnt].rot.x, g_aTitleModel[nNumCnt].rot.z);
		D3DXMatrixMultiply(&g_aTitleModel[nNumCnt].mtxWorld, &g_aTitleModel[nNumCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aTitleModel[nNumCnt].pos.x, g_aTitleModel[nNumCnt].pos.y, g_aTitleModel[nNumCnt].pos.z);
		D3DXMatrixMultiply(&g_aTitleModel[nNumCnt].mtxWorld, &g_aTitleModel[nNumCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aTitleModel[nNumCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aTitleModel[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aTitleModel[nNumCnt].NumMat; nCntMat++)
		{
			// 各モデルパーツの描画
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// モデルの描画
			g_aTitleModel[nNumCnt].pMesh->DrawSubset(nCntMat);
		}
		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}


//=====================================================================================================================================================================//
// 頂点抜き出し
//=====================================================================================================================================================================//
void GetVtxTitle(int nIdx)
{
	/* モデルの頂点情報抜き出し */
	int nNumVtx;													// 頂点数
	DWORD sizeFVF;													// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;													// 頂点バッファへのポインタ
	float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// 最小値保管用
	float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// 最大値保管用

																// 頂点数を取得
	nNumVtx = g_aTitleModel[nIdx].pMesh->GetNumVertices();
	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_aTitleModel[nIdx].pMesh->GetFVF());
	// 頂点バッファをロック
	g_aTitleModel[nIdx].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
													// 最大値・最小値の代入処理
		if (Vtx.x < MinMob_X)
		{/* 最小値 */
			MinMob_X = Vtx.x;
			g_aTitleModel[nIdx].g_VtxMinTitle.x = MinMob_X;
		}
		if (Vtx.y < MinMob_Y)
		{
			MinMob_Y = Vtx.y;
			g_aTitleModel[nIdx].g_VtxMinTitle.y = MinMob_Y;
		}
		if (Vtx.z < MinMob_Z)
		{
			MinMob_Z = Vtx.z;
			g_aTitleModel[nIdx].g_VtxMinTitle.z = MinMob_Z;
		}

		if (Vtx.x > MaxMob_X)
		{/* 最大値 */
			MaxMob_X = Vtx.x;
			g_aTitleModel[nIdx].g_VtxMaxTitle.x = MaxMob_X;
		}
		if (Vtx.y > MaxMob_Y)
		{
			MaxMob_Y = Vtx.y;
			g_aTitleModel[nIdx].g_VtxMaxTitle.y = MaxMob_Y;
		}
		if (Vtx.z > MaxMob_Z)
		{
			MaxMob_Z = Vtx.z;
			g_aTitleModel[nIdx].g_VtxMaxTitle.z = MaxMob_Z;
		}
		pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
	}
	// 頂点バッファのアンロック
	g_aTitleModel[nIdx].pMesh->UnlockVertexBuffer();


}
