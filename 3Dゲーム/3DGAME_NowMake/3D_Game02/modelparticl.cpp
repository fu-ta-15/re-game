//##################################################################################################################################################################//
//																																									//
// モデルパーティクル処理 [modelparticl.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "keyinput.h"
#include "collision.h"
#include "shadow.h"
#include "modelparticl.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(2.3f)		// モデルのスピード
#define MAX_SIZE_MEMORY		(4000)		// メモリのサイズ
#define MOB_SIZE			(10)
#define MPT_MAX				(500)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
ModelParticl g_MPT[MPT_MAX];							// プレイヤー（モデル）の構造体

LPD3DXMESH g_pMeshMPT;				// メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatMPT;			// マテリアルへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMPT;	// テクスチャへのポインタ
D3DXMATERIAL *g_pMatMPT;				// マテリアルのポインタ
DWORD g_NumMatMPT;					// マテリアルの数




//==================================================================================================================================================================//
// 初期化処理
//==================================================================================================================================================================//
void InitModelP(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ModelParticl *pMPT = &g_MPT[0];

	/* モデル */
	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		/* No.0 体 */
		pMPT->pos = D3DXVECTOR3(0.0f + (nNumCnt * 50), 100.0f, 0.0f);
		pMPT->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pMPT->bUse = false;
		pMPT->nNumShadow = 1;
		pMPT->nNumModel = 1;
		pMPT->nCuntDown = 15;
		pMPT->nCuntUp = 0;
		pMPT->nlife = 3;
	}
	// ファイルの読み込み
	/* No.0 小さい岩 */
	D3DXLoadMeshFromX("data\\MODEL\\rockmini.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_pBuffMatMPT, NULL, &g_NumMatMPT, &g_pMeshMPT);

	g_pMatMPT = (D3DXMATERIAL*)g_pBuffMatMPT->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_NumMatMPT; nCntMat++)
	{
		if (g_pMatMPT->pTextureFilename != NULL)
		{
			// テクスチャの読み込み
			D3DXCreateTextureFromFile(pDevice, g_pMatMPT->pTextureFilename, &g_pTextureMPT);
		}
	}

	//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

	/* モデルの頂点情報抜き出し */
	int nNumVtx;													// 頂点数
	DWORD sizeFVF;													// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;													// 頂点バッファへのポインタ
	float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// 最小値保管用
	float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// 最大値保管用

																// 頂点数を取得
	nNumVtx = g_pMeshMPT->GetNumVertices();
	// 頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(g_pMeshMPT->GetFVF());
	// 頂点バッファをロック
	g_pMeshMPT->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
													// 最大値・最小値の代入処理
		if (Vtx.x < MinMob_X)
		{/* 最小値 */
			MinMob_X = Vtx.x;
			pMPT->g_VtxMinMob.x = MinMob_X;
		}
		if (Vtx.y < MinMob_Y)
		{
			MinMob_Y = Vtx.y;
			pMPT->g_VtxMinMob.y = MinMob_Y;
		}
		if (Vtx.z < MinMob_Z)
		{
			MinMob_Z = Vtx.z;
			pMPT->g_VtxMinMob.z = MinMob_Z;
		}

		if (Vtx.x > MaxMob_X)
		{/* 最大値 */
			MaxMob_X = Vtx.x;
			pMPT->g_VtxMaxMob.x = MaxMob_X;
		}
		if (Vtx.y > MaxMob_Y)
		{
			MaxMob_Y = Vtx.y;
			pMPT->g_VtxMinMob.y = MaxMob_Y;
		}
		if (Vtx.z > MaxMob_Z)
		{
			MaxMob_Z = Vtx.z;
			pMPT->g_VtxMaxMob.z = MaxMob_Z;
		}
		pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
	}
	// 頂点バッファのアンロック
	g_pMeshMPT->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// 終了処理
//==================================================================================================================================================================//
void UninitModelP(void)
{
	if (g_pMeshMPT != NULL)
	{// メッシュの破棄
		g_pMeshMPT->Release();
		g_pMeshMPT = NULL;
	}
	if (g_pBuffMatMPT != NULL)
	{// マテリアルの破棄
		g_pBuffMatMPT->Release();
		g_pBuffMatMPT = NULL;
	}
	if (g_pTextureMPT != NULL)
	{
		g_pTextureMPT->Release();
		g_pTextureMPT = NULL;
	}
}

//==================================================================================================================================================================//
// 更新処理
//==================================================================================================================================================================//
void UpdateModelP(void)
{
	ModelParticl *pMPT = &g_MPT[0];

	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		if (pMPT->bUse == true)
		{
			pMPT->oldpos = pMPT->pos;

			// 位置の更新
			pMPT->move.y -= 0.1f;
			pMPT->pos.z += pMPT->move.z;
			pMPT->pos.x += pMPT->move.x;
			pMPT->pos.y += pMPT->move.y;


			// 移動量の減衰
			pMPT->move.z += (0.0f - pMPT->move.z) * 0.4f;
			pMPT->move.x += (0.0f - pMPT->move.x) * 0.4f;
			pMPT->move.y += (0.0f - pMPT->move.y) * 0.013f;

			//if (pMPT->oldpos.y - EFFECT_SIZEW < 0)
			//{// 前回の位置が床より下に行ったら

			// // 移動の設定
			//	float fAngle = (float)((rand() % 628) - 628) / 100.f;

			//	pMPT->move.z = cosf(fAngle + D3DX_PI) * 8.0f;
			//	pMPT->move.x = sinf(fAngle - D3DX_PI) * 8.0f;

			//	pMPT->pos.y = 0 + EFFECT_SIZEW;
			//	pMPT->move.y += 20.0f;
			//}

			// ライフの減少
			pMPT->nlife -= 1;

			// 寿命チェック
			if (pMPT->nlife == 0)
			{
				// 0になったらフォルスに変える
				pMPT->bUse = false;
			}


		}
	}
}

//==================================================================================================================================================================//
// 描画処理
//==================================================================================================================================================================//
void DrawModelP(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	ModelParticl *pMPT = &g_MPT[0];

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nNumCnt = 0; nNumCnt < MPT_MAX; nNumCnt++, pMPT++)
	{
		if (pMPT->bUse == true)
		{
			D3DXMatrixIdentity(&pMPT->mtxWorld);

			// 向きの反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, pMPT->rot.y, pMPT->rot.x, pMPT->rot.z);
			D3DXMatrixMultiply(&pMPT->mtxWorld, &pMPT->mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pMPT->pos.x, pMPT->pos.y, pMPT->pos.z);
			D3DXMatrixMultiply(&pMPT->mtxWorld, &pMPT->mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &pMPT->mtxWorld);

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);

			// マテリアルデータへのポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatMPT->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_NumMatMPT; nCntMat++)
			{
				// 各モデルパーツの描画
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureMPT);
				// モデルの描画
				g_pMeshMPT->DrawSubset(nCntMat);
			}
			// 保存していたマテリアルを戻す
			pDevice->SetMaterial(&matDef);
		}
	}
}


//==================================================================================================================================================================//
// モブの設置
//==================================================================================================================================================================//
void SetModelP(D3DXVECTOR3 pos, float movex, float movez, float movey, int nIdx, int nLife)
{
	ModelParticl *pMPT = &g_MPT[0];

	for (int nNumCnt = 0; nNumCnt < nIdx; pMPT++)
	{
		if (pMPT->bUse == false)
		{
			// 位置の設定
			pMPT->pos.x = pos.x;
			pMPT->pos.z = pos.z;
			pMPT->pos.y = pos.y;

			// 移動の設定
			float fAngle = (float)((rand() % 628) - 628) / 100.f;
			// 情報代入
			pMPT->move.z = cosf(fAngle + D3DX_PI) * 100.0f;
			pMPT->move.x = sinf(fAngle - D3DX_PI) * 100.0f;

			pMPT->move.y = movey;

			//pMPT->move.y = tanf(fAngle + D3DX_PI) * 3.0f;

			// 寿命の設定
			pMPT->nlife = nLife;

			// 弾を発射
			pMPT->bUse = true;

			nNumCnt++;

	//		break;
		}
	}
}


//==================================================================================================================================================================//
// プレイヤーの情報
//==================================================================================================================================================================//
ModelParticl *GetModelP(void)
{
	return &g_MPT[0];
}