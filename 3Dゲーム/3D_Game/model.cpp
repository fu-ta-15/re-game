//##################################################################################################################################################################//
//																																									//
// モデル処理 [model.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//　インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "model.h"
#include "keyinput.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "bulletptcl.h"
#include "memory.h"
#include "effect.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.3f)		// モデルのスピード
#define MAX_SIZE_MEMORY		(4000)		// メモリのサイズ


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Player g_Player;							// プレイヤー（モデル）の構造体


//==================================================================================================================================================================//
// 初期化処理
//==================================================================================================================================================================//
void InitModel(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	/* モデル */

	/* No.0 体 */
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].pMesh = NULL;
	g_Player.aModel[0].pBuffMat = NULL;
	g_Player.aModel[0].nIdxModelParent = -1;

	/* No.1 頭 */
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].pMesh = NULL;
	g_Player.aModel[1].pBuffMat = NULL;
	g_Player.aModel[1].nIdxModelParent = 0;

	/* No.2 右腕 */
	g_Player.aModel[2].pos = D3DXVECTOR3(-4.0f, 10.0f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].pMesh = NULL;
	g_Player.aModel[2].pBuffMat = NULL;
	g_Player.aModel[2].nIdxModelParent = 0;

	/* No.3 左腕 */
	g_Player.aModel[3].pos = D3DXVECTOR3(4.0f, 10.0f, 0.0f);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].pMesh = NULL;
	g_Player.aModel[3].pBuffMat = NULL;
	g_Player.aModel[3].nIdxModelParent = 0;

	/* No.4 右腿１ */
	g_Player.aModel[4].pos = D3DXVECTOR3(-4.5f, 0.0f, 3.0f);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].pMesh = NULL;
	g_Player.aModel[4].pBuffMat = NULL;
	g_Player.aModel[4].nIdxModelParent = 0;

	/* No.5 右腿２ */
	g_Player.aModel[5].pos = D3DXVECTOR3(-4.5f, 0.0f, -3.0f);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].pMesh = NULL;
	g_Player.aModel[5].pBuffMat = NULL;
	g_Player.aModel[5].nIdxModelParent = 0;

	/* No.6 左腿１ */
	g_Player.aModel[6].pos = D3DXVECTOR3(4.5f, 0.0f, 3.0f);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].pMesh = NULL;
	g_Player.aModel[6].pBuffMat = NULL;
	g_Player.aModel[6].nIdxModelParent = 0;

	/* No.7 左腿２ */
	g_Player.aModel[7].pos = D3DXVECTOR3(4.5f, 0.0f, -3.0f);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].pMesh = NULL;
	g_Player.aModel[7].pBuffMat = NULL;
	g_Player.aModel[7].nIdxModelParent = 0;

	/* No.8 右腕につながる部位 */
	g_Player.aModel[8].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].pMesh = NULL;
	g_Player.aModel[8].pBuffMat = NULL;
	g_Player.aModel[8].nIdxModelParent = 2;

	/* No.9 右手  */
	g_Player.aModel[9].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].pMesh = NULL;
	g_Player.aModel[9].pBuffMat = NULL;
	g_Player.aModel[9].nIdxModelParent = 8;

	/* No.10 左腕につながる部位 */
	g_Player.aModel[10].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].pMesh = NULL;
	g_Player.aModel[10].pBuffMat = NULL;
	g_Player.aModel[10].nIdxModelParent = 3;

	/* No.11 左手 */
	g_Player.aModel[11].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].pMesh = NULL;
	g_Player.aModel[11].pBuffMat = NULL;
	g_Player.aModel[11].nIdxModelParent = 10;

	/* No.12 右腿１につながる部位 */
	g_Player.aModel[12].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].pMesh = NULL;
	g_Player.aModel[12].pBuffMat = NULL;
	g_Player.aModel[12].nIdxModelParent = 4;

	/* No.13 右腿２につながる部位 */
	g_Player.aModel[13].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].pMesh = NULL;
	g_Player.aModel[13].pBuffMat = NULL;
	g_Player.aModel[13].nIdxModelParent = 5;

	/* No.14 右足１ */
	g_Player.aModel[14].pos = D3DXVECTOR3(-18.0f, 0.0f, 0.0f);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].pMesh = NULL;
	g_Player.aModel[14].pBuffMat = NULL;
	g_Player.aModel[14].nIdxModelParent = 12;

	/* No.15 右足２ */
	g_Player.aModel[15].pos = D3DXVECTOR3(-18.0f, 0.0f, 0.0f);
	g_Player.aModel[15].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[15].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[15].pMesh = NULL;
	g_Player.aModel[15].pBuffMat = NULL;
	g_Player.aModel[15].nIdxModelParent = 13;

	/* No.16 左腿１につながる部位 */
	g_Player.aModel[16].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);
	g_Player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[16].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[16].pMesh = NULL;
	g_Player.aModel[16].pBuffMat = NULL;
	g_Player.aModel[16].nIdxModelParent = 6;

	/* No.17 左腿２につながる部位 */
	g_Player.aModel[17].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);
	g_Player.aModel[17].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[17].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[17].pMesh = NULL;
	g_Player.aModel[17].pBuffMat = NULL;
	g_Player.aModel[17].nIdxModelParent = 7;

	/* No.18 左足１ */
	g_Player.aModel[18].pos = D3DXVECTOR3(18.0f, 0.0f, 0.0f);
	g_Player.aModel[18].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[18].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[18].pMesh = NULL;
	g_Player.aModel[18].pBuffMat = NULL;
	g_Player.aModel[18].nIdxModelParent = 16;

	/* No.19 左足２ */
	g_Player.aModel[19].pos = D3DXVECTOR3(18.0f, 0.0f, 0.0f);
	g_Player.aModel[19].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[19].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[19].pMesh = NULL;
	g_Player.aModel[19].pBuffMat = NULL;
	g_Player.aModel[19].nIdxModelParent = 17;

	/* プレイヤー */
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nNumShadow = 1;
	g_Player.nNumModel = 20;

	///* モーション */
	//g_Player.nNumMotion = 1;
	//g_Player.nNumKey = 2;
	//g_Player.nKey_No = 0;
	//g_Player.nCounterMotion = 0;
	//g_Player.bLoopMotion = false;

	//g_Player.aMotionInfo[0].bLoop = true;
	//g_Player.aMotionInfo[0].nNumKey = 2;

	//g_Player.aMotionInfo[0].aKeyInfo[0].nFrame = 60;
	//g_Player.aMotionInfo[0].aKeyInfo[1].nFrame = 60;

	///* パーツ０ */
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_X = 5.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_X = -5.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Z = 0.0f;

	///* パーツ１ */
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Z = 0.0f;

	// ファイルの読み込み
	/* No.0 体 */
	D3DXLoadMeshFromX("data\\suzuki_model\\body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].NumMat, &g_Player.aModel[0].pMesh);
	/* No.1 頭 */
	D3DXLoadMeshFromX("data\\suzuki_model\\hed.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].NumMat, &g_Player.aModel[1].pMesh);
	/* No.2 右腕 */
	D3DXLoadMeshFromX("data\\suzuki_model\\armeR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].NumMat, &g_Player.aModel[2].pMesh);
	/* No.3 左腕 */
	D3DXLoadMeshFromX("data\\suzuki_model\\arme.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].NumMat, &g_Player.aModel[3].pMesh);
	/* No.4 右腿１ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].NumMat, &g_Player.aModel[4].pMesh);
	/* No.5 右腿２ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].NumMat, &g_Player.aModel[5].pMesh);
	/* No.6 左腿１ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].NumMat, &g_Player.aModel[6].pMesh);
	/* No.7 左腿２ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].NumMat, &g_Player.aModel[7].pMesh);
	/* No.8 右腕につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\armeseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].NumMat, &g_Player.aModel[8].pMesh);
	/* No.9 右手  */
	D3DXLoadMeshFromX("data\\suzuki_model\\handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].NumMat, &g_Player.aModel[9].pMesh);
	/* No.10 左腕につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\armese.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].NumMat, &g_Player.aModel[10].pMesh);
	/* No.11 左手 */
	D3DXLoadMeshFromX("data\\suzuki_model\\hand.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].NumMat, &g_Player.aModel[11].pMesh);
	/* No.12 右腿１につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].NumMat, &g_Player.aModel[12].pMesh);
	/* No.13 右腿２につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\legRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].NumMat, &g_Player.aModel[13].pMesh);
	/* No.14 右足１ */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].NumMat, &g_Player.aModel[14].pMesh);
	/* No.15 右足２ */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].NumMat, &g_Player.aModel[15].pMesh);
	/* No.16 左腿１につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[16].pBuffMat, NULL, &g_Player.aModel[16].NumMat, &g_Player.aModel[16].pMesh);
	/* No.17 左腿２につながる部位 */
	D3DXLoadMeshFromX("data\\suzuki_model\\legLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[17].pBuffMat, NULL, &g_Player.aModel[17].NumMat, &g_Player.aModel[17].pMesh);
	/* No.18 左足１ */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[18].pBuffMat, NULL, &g_Player.aModel[18].NumMat, &g_Player.aModel[18].pMesh);
	/* No.19 左足２ */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[19].pBuffMat, NULL, &g_Player.aModel[19].NumMat, &g_Player.aModel[19].pMesh);

	for (int nCnt = 0; nCnt < g_Player.nNumModel; nCnt++)
	{
		if (g_Player.aModel[nCnt].pBuffMat == NULL)
		{
			printf("%s %d", "データ読み込み失敗", nCnt);
		}
		else
		{
			printf("%s %d\n", "\n データ読み込み成功", nCnt);
		}
	}


	g_Player.nNumShadow = SetShadow(g_Player.pos, 10.0f, 10.0f);


	/* モデルの頂点情報抜き出し */
		int nNumVtx;								// 頂点数
		DWORD sizeFVF;								// 頂点フォーマットのサイズ
		BYTE *pVtxBuff;								// 頂点バッファへのポインタ
		float MinModel_X = 0.0f, MinModel_Z = 0.0f;
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f;

		// 頂点数を取得
		nNumVtx = g_Player.aModel[0].pMesh->GetNumVertices();
		// 頂点フォーマットのサイズを取得
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMesh->GetFVF());
		// 頂点バッファをロック
		g_Player.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入
			
			if (Vtx.x < MinModel_X)
			{/* 最小値 */
				MinModel_X = Vtx.x;
				g_Player.aModel[0].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.z < MinModel_Z)
			{
				MinModel_Z = Vtx.z;
				g_Player.aModel[0].g_VtxMinModel.z = MinModel_Z;
			}
			if (Vtx.x > MaxModel_X)
			{/* 最大値 */
				MaxModel_X = Vtx.x;
				g_Player.aModel[0].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.z > MaxModel_Z)
			{
				MaxModel_Z = Vtx.z;
				g_Player.aModel[0].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
		}
		// 頂点バッファのアンロック
		g_Player.aModel[0].pMesh->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// 終了処理
//==================================================================================================================================================================//
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < 20; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{// メッシュの破棄
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{// マテリアルの破棄
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==================================================================================================================================================================//
// 更新処理
//==================================================================================================================================================================//
void UpdateModel(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Player.pos, sinf(-g_Player.rot.y), cosf(g_Player.rot.y), 50);
		SetBulletPT(g_Player.pos, sinf(-g_Player.rot.y), cosf(g_Player.rot.y), 50);
	}

	MoveModel();

	// 位置の更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// 目的回転制限
	if ((g_Player.rotDest.y - g_Player.rot.y) > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if ((g_Player.rotDest.y - g_Player.rot.y) < (-D3DX_PI))
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}

	// 向いてる方向
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	// 回転制限
	if (g_Player.rot.y < (-D3DX_PI))
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}

	// 移動・回転量の減衰
	g_Player.move.x += (0 - g_Player.move.x) * 0.3f;
	g_Player.move.y += (0 - g_Player.move.y) * 0.3f;
	g_Player.move.z += (0 - g_Player.move.z) * 0.3f;

	// モーション
	if (GetKeyboardTrigger(DIK_1) == true)
	{
		MotionModel();
	}

	// 影の設定
	SetPositionShadow(g_Player.nNumShadow, g_Player.pos);
}

//==================================================================================================================================================================//
// 描画処理
//==================================================================================================================================================================//
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	/* プレイヤー（見えない原点）の設定 */
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// 向きの反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// 計算用
		D3DXMATRIX mtxParent;					// 親のマトリックス

		// 各パーツのワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// 各パーツの向き
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// 各パーツの位置
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// 各パーツの親マトリックスを設定
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{// 親のインデックスを設定
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{// プレイヤーマトリックスを設定
			mtxParent = g_Player.mtxWorld;
		}

		// 算出した各パーツのワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
							&g_Player.aModel[nCntModel].mtxWorld,
							&mtxParent);
		// 各パーツのワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD,
			&g_Player.aModel[nCntModel].mtxWorld);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// 各モデルパーツの描画
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// テクスチャの設定
			pDevice->SetTexture(0, NULL);
			// モデルの描画
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	// 保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================================================================================//
// モデルの移動
//==================================================================================================================================================================//
void MoveModel(void)
{
	Camera *pCamera = GetCamera();

	/*モデル操作*/
	// 前移動・後移動
	if (GetKeyboardPresse(DIK_UP) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_DOWN) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_RIGHT) == true)
	{// 右移動・左移動
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = -D3DX_PI * 2 / 4 - pCamera->rot.y ;
	}
	else if (GetKeyboardPresse(DIK_LEFT) == true)
	{
		g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;
	}

	// 上移動・下移動
	if (GetKeyboardPresse(DIK_O) == true)
	{
		g_Player.move.y += 0.5f;
	}
	if (GetKeyboardPresse(DIK_L) == true)
	{
		g_Player.move.y -= 0.5f;
	}
	// 右旋回・左旋回
	if (GetKeyboardPresse(DIK_9) == true)
	{
		g_Player.rotDest.y += 0.08f;
	}
	if (GetKeyboardPresse(DIK_0) == true)
	{
		g_Player.rotDest.y -= 0.08f;
	}
}

//==================================================================================================================================================================//
// モーション管理
//==================================================================================================================================================================//
void MotionModel(void)
{
	D3DXVECTOR3 fNowPos = g_Player.aModel[1].pos;

	// 何のモーションか
	// ループはするのか
	if (g_Player.aMotionInfo[0].bLoop == true)
	{
		// カウンタースタート
		g_Player.nCounterMotion++;
		// モデル分
		for (int nModel = 0; nModel < g_Player.nNumModel; nModel++)
		{
			// キーの数は
			for (int nKey = 0; nKey < g_Player.nNumKey; nKey++)
			{
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_X = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_X - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_X;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Y = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Y - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_Y;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Z = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Z - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_Z;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_X = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_X - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_X;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Y = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Y - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_Y;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Z = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Z - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_Z;


				g_Player.aModel[0].pos.x = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_X * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].pos.y = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_Y * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].pos.z = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_Z * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.x = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_X * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.y = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_Y * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.z = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_Z * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			}
		}
	}
}


//==================================================================================================================================================================//
// テキストの読み込み
//==================================================================================================================================================================//
void FileLoad(void)
{
	// 文字列のポイント
	char *str;
	// 文字列の長さ
	int length = 1000;

	// メモリ確保
	str = (char*)malloc(sizeof(char) * length);

	memset(str, 0, sizeof(char) * 1000);

	if (!str)
	{// メモリ確保に失敗
		printf("%s", "\nメモリ確保に失敗");
		exit(0);
	}


}



//==================================================================================================================================================================//
// プレイヤーの情報
//==================================================================================================================================================================//
Player * GetPlayer(void)
{
	return &g_Player;
}