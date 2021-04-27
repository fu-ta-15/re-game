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
#include "fade.h"
#include "collision.h"
#include "shadow.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(2.3f)		// モデルのスピード
#define MAX_SIZE_MEMORY		(4000)		// メモリのサイズ
#define MOB_SIZE			(10)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Rock g_Mob[MOB_MAX];							// プレイヤー（モデル）の構造体
Rock *g_pMob;									// プレイヤー（モデル）の構造体


//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
void SummonMob(void);
void SetMob(void);
void FileLoadMob(void);


//==================================================================================================================================================================//
// 初期化処理
//==================================================================================================================================================================//
void InitMob(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	Rock *pMoblayer = &g_Mob[0];

	/* モデル */
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
		/* No.0 体 */
		pMoblayer->pos = D3DXVECTOR3(0.0f + (nNumCnt * 50) , 100.0f, 0.0f);
		pMoblayer->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->pMesh = NULL;
		pMoblayer->pBuffMat = NULL;
		pMoblayer->pTexture = NULL;
		pMoblayer->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMoblayer->bUse = false;
		pMoblayer->nNumShadow = 1;
		pMoblayer->nNumModel = 1;
		pMoblayer->nCuntDown = 15;
		pMoblayer->nCuntUp = 0;
		pMoblayer->nlife = 3;

		// ファイルの読み込み
		/* No.0 岩 */
		D3DXLoadMeshFromX("data\\MODEL\\rock.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &pMoblayer->pBuffMat, NULL, &pMoblayer->NumMat, &pMoblayer->pMesh);

		pMoblayer->pMat = (D3DXMATERIAL*)pMoblayer->pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)pMoblayer->NumMat; nCntMat++)
		{
			if (pMoblayer->pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, pMoblayer->pMat[nCntMat].pTextureFilename, &pMoblayer->pTexture);
			}
		}

		/* モデルの頂点情報抜き出し */
		int nNumVtx;													// 頂点数
		DWORD sizeFVF;													// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;													// 頂点バッファへのポインタ
		float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;		// 最小値保管用
		float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;		// 最大値保管用

		// 頂点数を取得
		nNumVtx = pMoblayer->pMesh->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(pMoblayer->pMesh->GetFVF());
		// 頂点バッファをロック
		pMoblayer->pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
														// 最大値・最小値の代入処理
			if (Vtx.x < MinMob_X)
			{/* 最小値 */
				MinMob_X = Vtx.x;
				pMoblayer->g_VtxMinMob.x = MinMob_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				pMoblayer->g_VtxMinMob.y = MinMob_Y;
			}
			if (Vtx.z < MinMob_Z)
			{
				MinMob_Z = Vtx.z;
				pMoblayer->g_VtxMinMob.z = MinMob_Z;
			}

			if (Vtx.x > MaxMob_X)
			{/* 最大値 */
				MaxMob_X = Vtx.x;
				pMoblayer->g_VtxMaxMob.x = MaxMob_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				pMoblayer->g_VtxMinMob.y = MaxMob_Y;
			}
			if (Vtx.z > MaxMob_Z)
			{
				MaxMob_Z = Vtx.z;
				pMoblayer->g_VtxMaxMob.z = MaxMob_Z;
			}
			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}
		// 頂点バッファのアンロック
		pMoblayer->pMesh->UnlockVertexBuffer();
	}
}

//==================================================================================================================================================================//
// 終了処理
//==================================================================================================================================================================//
void UninitMob(void)
{
	Rock *pMoblayer = &g_Mob[0];
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
			if (pMoblayer->pMesh != NULL)
			{// メッシュの破棄
				pMoblayer->pMesh->Release();
				pMoblayer->pMesh = NULL;
			}
			if (pMoblayer->pBuffMat != NULL)
			{// マテリアルの破棄
				pMoblayer->pBuffMat->Release();
				pMoblayer->pBuffMat = NULL;
			}
			if (pMoblayer->pTexture != NULL)
			{
				pMoblayer->pTexture->Release();
				pMoblayer->pTexture = NULL;
			}
	}
}

//==================================================================================================================================================================//
// 更新処理
//==================================================================================================================================================================//
void UpdateMob(void)
{
	Rock *pMoblayer = &g_Mob[0];


	SummonMob();
	for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
	{
		if (pMoblayer->bUse == true)
		{
			pMoblayer->oldpos = pMoblayer->pos;

			// 位置の更新
			pMoblayer->pos.z += pMoblayer->move.z;
			pMoblayer->pos.x += pMoblayer->move.x;
			pMoblayer->pos.y += pMoblayer->move.y;

		}
	}
}

//==================================================================================================================================================================//
// 描画処理
//==================================================================================================================================================================//
void DrawMob(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	Rock *pMoblayer = &g_Mob[0];

		D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
		D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
		D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

		for (int nNumCnt = 0; nNumCnt < MOB_MAX; nNumCnt++, pMoblayer++)
		{
			if (pMoblayer->bUse == true)
			{
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

				// マテリアルデータへのポインタを取得
				pMat = (D3DXMATERIAL*)pMoblayer->pBuffMat->GetBufferPointer();

				for (int nCntMat = 0; nCntMat < (int)pMoblayer->NumMat; nCntMat++)
				{
					// 各モデルパーツの描画
					// マテリアルの設定
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
					// テクスチャの設定
					pDevice->SetTexture(0, pMoblayer->pTexture);
					// モデルの描画
					pMoblayer->pMesh->DrawSubset(nCntMat);
				}
				// 保存していたマテリアルを戻す
				pDevice->SetMaterial(&matDef);
			}
		}
}


//==================================================================================================================================================================//
// モブの召喚
//==================================================================================================================================================================//
void SummonMob(void)
{
	Rock *pMoblayer = &g_Mob[0];


	for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++,pMoblayer++)
	{

		if (pMoblayer->bUse == false)
		{
			pMoblayer->nCuntUp++;	// カウントスタート

			if ((pMoblayer->nCuntUp % (20 * nCntMob + 1)) == 0)
			{
				pMoblayer->nCuntDown--;
				if (pMoblayer->nCuntDown == 0)
				{
					// 移動の設定
					float fAngle = (float)((rand() % 628) - 628) / 100.f;
					pMoblayer->move.z = cosf(fAngle + D3DX_PI) * 5.0f;
					pMoblayer->move.x = sinf(fAngle - D3DX_PI) * 5.0f;
					pMoblayer->bUse = true;
					break;

				}
			}
		}
	}
}

//==================================================================================================================================================================//
// モブの設置
//==================================================================================================================================================================//
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
Rock *GetRock(void)
{
	return &g_Mob[0];
}