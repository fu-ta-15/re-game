//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "Keyinput.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "Dinput.h"
#include "meshfield.h"
#include "meshwall.h"
#include "camera.h"
#include "light.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define RESULT_MAX_MODEL			(1)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//頂点バッファの情報
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;		//テクスチャの情報
ResultModel g_aResult[RESULT_MAX_MODEL];

//=====================================================================================================================================================================//
// リザルトの初期化処理
//=====================================================================================================================================================================//
HRESULT InitResult(void)
{
	InitCamera();
	InitResultModel();
	Initlight();
	InitMeshfield();
	InitMeshWall();
	// 壁の配置
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, WALL_POS), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_POS), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(-WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);

	//PlaySound(SOUND_LABEL_BGM003);

	return S_OK;

}

//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitResult(void)
{
	UninitCamera();
	UninitResultModel();
	Uninitlight();
	UninitMeshfield();
	UninitMeshWall();

	//StopSound(SOUND_LABEL_BGM003);

}

//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
	UpdateResultModel();
	UpdateCamera();
	Updatelight();
	UpdateMeshfield();
	UpdateMeshWall();

}

//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawResult(void)
{
	SetCamera();
	DrawMeshfield();
	DrawMeshWall();
	DrawResultModel();
}


//=====================================================================================================================================================================//
// 初期化処理
//=====================================================================================================================================================================//
void InitResultModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* モデル */
	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{
		/* No.0 体 */
		g_aResult[nNumCnt].pos = D3DXVECTOR3(0.0f + (nNumCnt * 50), 100.0f, 0.0f);
		g_aResult[nNumCnt].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].pMesh = NULL;
		g_aResult[nNumCnt].pBuffMat = NULL;
		g_aResult[nNumCnt].pTexture = NULL;
		g_aResult[nNumCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// ファイルの読み込み
		/* No.0 岩 */
		D3DXLoadMeshFromX("data\\MODEL\\Title.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aResult[nNumCnt].pBuffMat, NULL, &g_aResult[nNumCnt].NumMat, &g_aResult[nNumCnt].pMesh);

		g_aResult[nNumCnt].pMat = (D3DXMATERIAL*)g_aResult[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aResult[nNumCnt].NumMat; nCntMat++)
		{
			if (g_aResult[nNumCnt].pMat[nCntMat].pTextureFilename != NULL)
			{
				// テクスチャの読み込み
				D3DXCreateTextureFromFile(pDevice, g_aResult[nNumCnt].pMat[nCntMat].pTextureFilename, &g_aResult[nNumCnt].pTexture);
			}
		}

		//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

		/* モデルの頂点情報抜き出し */
		int nNumVtx;												// 頂点数
		DWORD sizeFVF;												// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;												// 頂点バッファへのポインタ
		float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// 最小値保管用
		float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// 最大値保管用

		// 頂点数を取得
		nNumVtx = g_aResult[nNumCnt].pMesh->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_aResult[nNumCnt].pMesh->GetFVF());
		// 頂点バッファをロック
		g_aResult[nNumCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
														// 最大値・最小値の代入処理
			if (Vtx.x < MinMob_X)
			{/* 最小値 */
				MinMob_X = Vtx.x;
				g_aResult[nNumCnt].g_VtxMinTitle.x = MinMob_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				g_aResult[nNumCnt].g_VtxMinTitle.y = MinMob_Y;
			}
			if (Vtx.z < MinMob_Z)
			{
				MinMob_Z = Vtx.z;
				g_aResult[nNumCnt].g_VtxMinTitle.z = MinMob_Z;
			}

			if (Vtx.x > MaxMob_X)
			{/* 最大値 */
				MaxMob_X = Vtx.x;
				g_aResult[nNumCnt].g_VtxMaxTitle.x = MaxMob_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				g_aResult[nNumCnt].g_VtxMaxTitle.y = MaxMob_Y;
			}
			if (Vtx.z > MaxMob_Z)
			{
				MaxMob_Z = Vtx.z;
				g_aResult[nNumCnt].g_VtxMaxTitle.z = MaxMob_Z;
			}
			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}
		// 頂点バッファのアンロック
		g_aResult[nNumCnt].pMesh->UnlockVertexBuffer();
	}
}


//=====================================================================================================================================================================//
// 終了処理
//=====================================================================================================================================================================//
void UninitResultModel(void)
{
	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{
		if (g_aResult[nNumCnt].pMesh != NULL)
		{// メッシュの破棄
			g_aResult[nNumCnt].pMesh->Release();
			g_aResult[nNumCnt].pMesh = NULL;
		}
		if (g_aResult[nNumCnt].pBuffMat != NULL)
		{// マテリアルの破棄
			g_aResult[nNumCnt].pBuffMat->Release();
			g_aResult[nNumCnt].pBuffMat = NULL;
		}
		if (g_aResult[nNumCnt].pTexture != NULL)
		{
			g_aResult[nNumCnt].pTexture->Release();
			g_aResult[nNumCnt].pTexture = NULL;
		}
	}
}


//=====================================================================================================================================================================//
// 更新処理
//=====================================================================================================================================================================//
void UpdateResultModel(void)
{
}


//=====================================================================================================================================================================//
// 描画処理
//=====================================================================================================================================================================//
void DrawResultModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{

		D3DXMatrixIdentity(&g_aResult[nNumCnt].mtxWorld);

		// 向きの反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aResult[nNumCnt].rot.y, g_aResult[nNumCnt].rot.x, g_aResult[nNumCnt].rot.z);
		D3DXMatrixMultiply(&g_aResult[nNumCnt].mtxWorld, &g_aResult[nNumCnt].mtxWorld, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aResult[nNumCnt].pos.x, g_aResult[nNumCnt].pos.y, g_aResult[nNumCnt].pos.z);
		D3DXMatrixMultiply(&g_aResult[nNumCnt].mtxWorld, &g_aResult[nNumCnt].mtxWorld, &mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aResult[nNumCnt].mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_aResult[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aResult[nNumCnt].NumMat; nCntMat++)
		{
			// 各モデルパーツの描画
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// モデルの描画
			g_aResult[nNumCnt].pMesh->DrawSubset(nCntMat);
		}
		// 保存していたマテリアルを戻す
		pDevice->SetMaterial(&matDef);
	}
}


//=====================================================================================================================================================================//
// セット処理
//=====================================================================================================================================================================//
void SetResultModel(void)
{
}
