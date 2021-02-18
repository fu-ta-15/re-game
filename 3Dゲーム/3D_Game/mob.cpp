//##################################################################################################################################################################//
//																																									//
// モデル処理 [model.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "keyinput.h"
#include "effect.h"
#include "mob.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.3f)		// モデルのスピード
#define MAX_SIZE_MEMORY		(4000)		// メモリのサイズ
#define MOB_SIZE			(10)



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Moblayer g_Mob;							// プレイヤー（モデル）の構造体


//==================================================================================================================================================================//
// 初期化処理
//==================================================================================================================================================================//
void InitMob(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	Moblayer *pMoblayer = &g_Mob;

	/* モデル */
		/* No.0 体 */
	pMoblayer->aModel[0].pos = D3DXVECTOR3(0.0f, 400.0f, 0.0f);
	pMoblayer->aModel[0].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->aModel[0].pMesh = NULL;
	pMoblayer->aModel[0].pBuffMat = NULL;
	pMoblayer->aModel[0].pTexture = NULL;
	pMoblayer->aModel[0].nIdxModelParent = -1;

		/* プレイヤー */
	pMoblayer->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pMoblayer->bUse = true;
	pMoblayer->nNumShadow = 1;
	pMoblayer->nNumModel = 1;
	pMoblayer->nCuntDown = 120;
	pMoblayer->nCuntUp = 0;
	pMoblayer->nlife = 3;


	// ファイルの読み込み
	/* No.0 岩 */
	D3DXLoadMeshFromX("data\\MODEL\\rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pMoblayer->aModel[0].pBuffMat, NULL, &pMoblayer->aModel[0].NumMat, &pMoblayer->aModel[0].pMesh);

	pMoblayer->aModel[0].pMat = (D3DXMATERIAL*)pMoblayer->aModel[0].pBuffMat->GetBufferPointer();
	
	for (int nCntMat = 0; nCntMat < (int)pMoblayer->aModel[0].NumMat; nCntMat++)
	{
		if (pMoblayer->aModel[0].pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, pMoblayer->aModel[0].pMat[nCntMat].pTextureFilename, &pMoblayer->aModel[0].pTexture);
		}
	}

	//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

		/* モデルの頂点情報抜き出し */
		int nNumVtx;													// 頂点数
		DWORD sizeFVF;													// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;													// 頂点バッファへのポインタ
		float MinModel_X = 0.0f, MinModel_Z = 0.0f, MinMob_Y = 0.0f;	// 最小値保管用
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f, MaxMob_Y = 0.0f;	// 最大値保管用

		// 頂点数を取得
		nNumVtx = g_Mob.aModel[0].pMesh->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Mob.aModel[0].pMesh->GetFVF());
		// 頂点バッファをロック
		g_Mob.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
			// 最大値・最小値の代入処理
			if (Vtx.x < MinModel_X)
			{/* 最小値 */
				MinModel_X = Vtx.x;
				g_Mob.aModel[0].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				g_Mob.aModel[0].g_VtxMinModel.y = MinMob_Y;
			}
			if (Vtx.z < MinModel_Z)
			{
				MinModel_Z = Vtx.z;
				g_Mob.aModel[0].g_VtxMinModel.z = MinModel_Z;
			}
			if (Vtx.x > MaxModel_X)
			{/* 最大値 */
				MaxModel_X = Vtx.x;
				g_Mob.aModel[0].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				g_Mob.aModel[0].g_VtxMinModel.y = MaxMob_Y;
			}
			if (Vtx.z > MaxModel_Z)
			{
				MaxModel_Z = Vtx.z;
				g_Mob.aModel[0].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}
		// 頂点バッファのアンロック
		g_Mob.aModel[0].pMesh->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// 終了処理
//==================================================================================================================================================================//
void UninitMob(void)
{
		for (int nCntModel = 0; nCntModel < 1; nCntModel++)
		{
			if (g_Mob.aModel[nCntModel].pMesh != NULL)
			{// メッシュの破棄
				g_Mob.aModel[nCntModel].pMesh->Release();
				g_Mob.aModel[nCntModel].pMesh = NULL;
			}
			if (g_Mob.aModel[nCntModel].pBuffMat != NULL)
			{// マテリアルの破棄
				g_Mob.aModel[nCntModel].pBuffMat->Release();
				g_Mob.aModel[nCntModel].pBuffMat = NULL;
			}
			if (g_Mob.aModel[nCntModel].pTexture != NULL)
			{
				g_Mob.aModel[nCntModel].pTexture->Release();
				g_Mob.aModel[nCntModel].pTexture = NULL;
			}
		}
}

//==================================================================================================================================================================//
// 更新処理
//==================================================================================================================================================================//
void UpdateMob(void)
{
	// 影の設定
	//SetPositionShadow(g_Mob.nNumShadow, g_Mob.pos);

	Moblayer *pMoblayer = &g_Mob;
	if (g_Mob.bUse == true)
	{

		pMoblayer->aModel[0].oldpos = pMoblayer->aModel[0].pos;

		// 位置の更新
		pMoblayer->aModel[0].move.y -= 1.3f;
		pMoblayer->aModel[0].pos.z += pMoblayer->aModel[0].move.z;
		pMoblayer->aModel[0].pos.x += pMoblayer->aModel[0].move.x;
		pMoblayer->aModel[0].pos.y += pMoblayer->aModel[0].move.y;

		// 移動量の減衰
		pMoblayer->aModel[0].move.z += (0.0f - pMoblayer->aModel[0].move.z) * 0.4f;
		pMoblayer->aModel[0].move.x += (0.0f - pMoblayer->aModel[0].move.x) * 0.4f;
		pMoblayer->aModel[0].move.y += (0.0f - pMoblayer->aModel[0].move.y) * 0.013f;


		if (g_Mob.aModel[0].oldpos.y < 0 + g_Mob.aModel[0].g_VtxMinModel.y)
		{
			pMoblayer->aModel[0].pos.y = 0 + g_Mob.aModel[0].g_VtxMinModel.y;
			pMoblayer->aModel[0].move.y += 20.0f;
		}
	}
}

//==================================================================================================================================================================//
// 描画処理
//==================================================================================================================================================================//
void DrawMob(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Moblayer *pMoblayer = &g_Mob;

		D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
		D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
		D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

			D3DXMatrixIdentity(&pMoblayer->mtxWorld);

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMoblayer->rot.y, pMoblayer->rot.x, pMoblayer->rot.z);
			D3DXMatrixMultiply(&pMoblayer->mtxWorld, &pMoblayer->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pMoblayer->pos.x, pMoblayer->pos.y, pMoblayer->pos.z);
			D3DXMatrixMultiply(&pMoblayer->mtxWorld, &pMoblayer->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pMoblayer->mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			for (int nCntModel = 0; nCntModel < g_Mob.nNumModel; nCntModel++)
			{
				D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用
				D3DXMATRIX mtxParent;					// 親のマトリックス

														// 各パーツのワールドマトリックスの初期化
				D3DXMatrixIdentity(&pMoblayer->aModel[nCntModel].mtxWorld);

				// 各パーツの向き
				D3DXMatrixRotationYawPitchRoll(&mtxRotModel, pMoblayer->aModel[nCntModel].rot.y, pMoblayer->aModel[nCntModel].rot.x, pMoblayer->aModel[nCntModel].rot.z);
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld, &pMoblayer->aModel[nCntModel].mtxWorld, &mtxRotModel);

				// 各パーツの位置
				D3DXMatrixTranslation(&mtxTransModel, pMoblayer->aModel[nCntModel].pos.x, pMoblayer->aModel[nCntModel].pos.y, pMoblayer->aModel[nCntModel].pos.z);
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld, &g_Mob.aModel[nCntModel].mtxWorld, &mtxTransModel);

				// 各パーツの親マトリックスを設定
				if (pMoblayer->aModel[nCntModel].nIdxModelParent != -1)
				{// 親のインデックスを設定
					mtxParent = pMoblayer->aModel[pMoblayer->aModel[nCntModel].nIdxModelParent].mtxWorld;
				}
				else
				{// プレイヤーマトリックスを設定
					mtxParent = pMoblayer->mtxWorld;
				}

				// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
				D3DXMatrixMultiply(&pMoblayer->aModel[nCntModel].mtxWorld,
					&pMoblayer->aModel[nCntModel].mtxWorld,
					&mtxParent);
				// 各パーツのワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD,
					&pMoblayer->aModel[nCntModel].mtxWorld);

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)pMoblayer->aModel[nCntModel].pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)pMoblayer->aModel[nCntModel].NumMat; nCntMat++)
				{
					// 各モデルパーツの描画
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャの設定
					pDevice->SetTexture(0, pMoblayer->aModel[0].pTexture);
					// モデルの描画
					pMoblayer->aModel[nCntModel].pMesh->DrawSubset(nCntMat);
				}
			}
		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
}

void SetMob(void)
{



}


//==================================================================================================================================================================//
// テキストの読み込み
//==================================================================================================================================================================//
void FileLoadMob(void)
{
	// 文字列のポイント
	char *str;
	// 文字列の長さ
	int length = 1000;
	// ファイル
	FILE *fMob;
	char *fName = "Mobs.txt";

	// メモリ確保
	str = (char*)malloc(sizeof(char) * length);

	memset(str, 0, sizeof(char) * length);

	if (!str)
	{// メモリ確保に失敗
		printf("%s", "\nメモリ確保に失敗");
		exit(0);
	}

	fMob = fopen(fName, "r");
	if (fMob == NULL)
	{
		printf("%sファイルが開けませんでした", fName);
	}
	else
	{
		while (fgets(str, length, fMob) != NULL);
	}
	fclose(fMob);
	free(str);
}



//==================================================================================================================================================================//
// プレイヤーの情報
//==================================================================================================================================================================//
Moblayer *GetMoblayer(void)
{
	return &g_Mob;
}