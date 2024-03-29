//##################################################################################################################################################################//
//
// 当たり判定処理 [Collision.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "model.h"
#include "meshwall.h"
#include "meshfield.h"
#include "collision.h"
#include "mob.h"
#include "fade.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//マクロ変数
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
CollPlayer g_cPlayer;	 // プレイヤー
CollMob g_cMob;			 // 岩
CollCircle g_cCircle;	 // 円の当たり判定用


//=====================================================================================================================================================================//
// 当たり判定の初期化
//=====================================================================================================================================================================//
void InitCollision(void)
{
	g_cMob.nNumMobMax = MOB_MAX;

}

//=====================================================================================================================================================================//
// 情報の取得
//=====================================================================================================================================================================//
void UpdatePos(void)
{
	// 構造体の情報取得
	Player *pPlayer = GetPlayer();

	// プレイヤーの当たり判定領域
	g_cPlayer.CollPlayerMax = D3DXVECTOR3(pPlayer->pos.x + pPlayer->aModel[0].g_VtxMaxModel.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMaxModel.y, pPlayer->pos.z + pPlayer->aModel[0].g_VtxMaxModel.z);
	g_cPlayer.CollPlayerMin = D3DXVECTOR3(pPlayer->pos.x + pPlayer->aModel[0].g_VtxMinModel.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMinModel.y, pPlayer->pos.z + pPlayer->aModel[0].g_VtxMinModel.z);



}

//=====================================================================================================================================================================//
// 当たり判定の処理
//=====================================================================================================================================================================//
void PlayerCollision(void)
{
	// 各構造体のポインタ
	Player *pPlayer = GetPlayer();			 // プレイヤー
	MeshWall *pMeshWall = GetMeshWall();	 // 壁
	Moblayer *pMob = GetMoblayer();			 // モブ（岩）

	// プレイヤーの中心座標
	g_cPlayer.rPlayer = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMaxModel.y + pPlayer->aModel[1].g_VtxMaxModel.y, pPlayer->pos.z);

	pPlayer->oldpos = g_cPlayer.rPlayer;	  // 過去の位置を保存

	g_cPlayer.PlayerHight = g_cPlayer.rPlayer.y + 40.0f + pPlayer->aModel[1].g_VtxMaxModel.y;	   // プレイヤーの一番高い座標
	g_cPlayer.PlayerLow = g_cPlayer.rPlayer.y - pPlayer->aModel[0].g_VtxMaxModel.y;	   // プレイヤーの一番低い座標

	// プレイヤーの半径（モデルの最大値）
	g_cPlayer.PlayerRadWidth = pPlayer->aModel[0].g_VtxMaxModel.x;
	g_cPlayer.PlayerRadHight = pPlayer->aModel[0].g_VtxMaxModel.y;

	for (int nColl = 0; nColl < MOB_MAX; nColl++, pMob++)
	{
		if (pMob->bUse == true)
		{// 岩が存在している時

				// 岩5個分の中心座標
				D3DXVECTOR3 rMob = D3DXVECTOR3(pMob->pos.x, pMob->pos.y + pMob->g_VtxMaxMob.y, pMob->pos.z);

				// 岩五個分の半径（モデルの最大値）
				g_cCircle.MobRadWidth = pMob->g_VtxMaxMob.x;
				g_cCircle.MobRadHight = pMob->g_VtxMaxMob.y;

				// 二点の距離を算出
				g_cCircle.wAa = g_cPlayer.rPlayer.x - rMob.x;
				g_cCircle.wBb = g_cPlayer.rPlayer.z - rMob.z;
				g_cCircle.wCc = (float)sqrt(g_cCircle.wAa * g_cCircle.wAa + g_cCircle.wBb * g_cCircle.wBb);

				g_cCircle.hAa = g_cPlayer.rPlayer.x - rMob.x;
				g_cCircle.hBb = g_cPlayer.rPlayer.y - rMob.y;
				g_cCircle.hCc = (float)sqrt(g_cCircle.hAa * g_cCircle.hAa + g_cCircle.hBb * g_cCircle.hBb);


				// 二つの半径の和
				g_cCircle.wSumRad = g_cPlayer.PlayerRadWidth + g_cCircle.MobRadWidth;
				g_cCircle.hSumRad = g_cPlayer.PlayerRadHight + g_cCircle.MobRadHight;


				D3DXVECTOR3 MobCollMax = D3DXVECTOR3(pMob->pos.x + pMob->g_VtxMaxMob.x, pMob->pos.y + pMob->g_VtxMaxMob.y, pMob->pos.z + pMob->g_VtxMaxMob.z);
				D3DXVECTOR3 MobCollMin = D3DXVECTOR3(pMob->pos.x + pMob->g_VtxMinMob.x, pMob->pos.y + pMob->g_VtxMinMob.y, pMob->pos.z + pMob->g_VtxMinMob.z);

				// 岩の反射
				if (MobCollMax.x > LENGTH_POLYGON_X)
				{
					pMob->move.x = pMob->move.x * (-1);
				}
				if (MobCollMin.x < -LENGTH_POLYGON_X)
				{
					pMob->move.x = pMob->move.x * (-1);
				}
				if (MobCollMax.z > LENGTH_POLYGON_Z)
				{
					pMob->move.z = pMob->move.z * (-1);
				}
				if (MobCollMin.z < -LENGTH_POLYGON_Z)
				{
					pMob->move.z = pMob->move.z * (-1);
				}

				if (g_cPlayer.PlayerHight < rMob.y - pMob->g_VtxMaxMob.y || g_cPlayer.PlayerLow > rMob.y)
				{
				}
				else
				{
					if (g_cCircle.wCc <= g_cCircle.wSumRad)
					{// 当たり判定の距離になった時
						printf("当たりました。");
						g_cMob.nNumMobMax -= 1;
						pMob->bUse = false;
					}
				}
				// 内積の当たり判定
				InnerProduct(nColl);
			}
	}

	if (g_cMob.nNumMobMax == 0)
	{// 岩が全部なくなったら
		SetFade(FADE_OUT, MODE_RESULT);
	}

	// プレイヤーの移動範囲
	if (g_cPlayer.CollPlayerMax.x > LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMaxModel.x;
	}
	if (g_cPlayer.CollPlayerMin.x < -LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = -LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMinModel.x;
	}
	if (g_cPlayer.CollPlayerMax.z > LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMaxModel.z;
	}
	if (g_cPlayer.CollPlayerMin.z < -LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = -LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMinModel.z;
	}
}


//=====================================================================================================================================================================//
// 内積の当たり判定
//=====================================================================================================================================================================//
void InnerProduct(int nmobIdx)
{
	Moblayer *pMob = GetMoblayer();			// モブ（岩）

	D3DXVECTOR3 VecF[MOB_MAX];				// 進行ベクトル
	float VecN;								// 壁の法線ベクトル(法線のため1固定）

	float VecAX[MOB_MAX];					// 未知の値（内積で使う値）X
	float VecAZ[MOB_MAX];					// 未知の値（内積で使う値）Z
	
	float VecPX[MOB_MAX];					// 壁に平行なベクトル X
	float VecPZ[MOB_MAX];					// 壁に平行なベクトル Z
	
	float VecRX[MOB_MAX];					// 反射ベクトル X
	float VecRZ[MOB_MAX];					// 反射ベクトル Z

	for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++, pMob++)
	{
		if (pMob->bUse == true)
		{
			VecF[nCntMob] = pMob->move;

			VecN = -1.0f;

			VecAX[nCntMob] = -VecF[nCntMob].x * VecN;
			VecAZ[nCntMob] = -VecF[nCntMob].z * VecN;

			VecPX[nCntMob] = VecF[nCntMob].x + VecAX[nCntMob] * VecN;
			VecPZ[nCntMob] = VecF[nCntMob].z + VecAZ[nCntMob] * VecN;

			VecRX[nCntMob] = VecF[nCntMob].x + (VecAX[nCntMob] * 2) * VecN;
			VecRZ[nCntMob] = VecF[nCntMob].z + (VecAZ[nCntMob] * 2) * VecN;
		}
	}
}

