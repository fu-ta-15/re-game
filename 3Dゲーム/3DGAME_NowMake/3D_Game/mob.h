//##################################################################################################################################################################//
//
// モブヘッダファイル [mob.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MOB_H_
#define _MOB_H_


#include "main.h"


#define MOB_MAX				(10)


//=====================================================================================================================================================================//
// 構造体
//=====================================================================================================================================================================//

typedef struct
{
	/* プレイヤー情報 */
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 oldpos;				// 過去の位置
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 rot;				// 回転
	D3DXVECTOR3 rotDest;			// 回転目的
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	LPD3DXMESH pMesh;				// メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアルへのポインタ
	LPDIRECT3DTEXTURE9 pTexture;	// テクスチャへのポインタ
	D3DXMATERIAL *pMat;				// マテリアルのポインタ
	DWORD NumMat;					// マテリアルの数
	D3DXVECTOR3 g_VtxMinMob;		// モデルの最小値（MIN）
	D3DXVECTOR3	g_VtxMaxMob;		// モデルの最大値（MAX）
									/* モデル情報 */
	int nNumModel;					// モデルパーツ数
	int nCuntDown;					// 出現までのカウントダウン
	int nCuntUp;					// カウントアップ
	int nlife;						// ライフ
	int nMobNum;					// モブの数
	bool bColl;
	bool bUse;						// 使用しているか

									/* 影 */
	int nNumShadow;					// 影
}Moblayer;	// プレイヤー(見えないモデル)



typedef struct
{
	D3DXVECTOR3 MotionPos;
	D3DXVECTOR3 MotionRot;
	D3DXVECTOR3 MotionPosDest;
	D3DXVECTOR3 MotionRotDest;
	int Key;
	int NextKey;

}MotionMob;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
void InitMob(void);
void UninitMob(void);
void UpdateMob(void);
void DrawMob(void);
void SummonMob(void);
void SetMob(void);
void FileLoadMob(void);
Moblayer *GetMoblayer(void);

#endif // !_MODEL_H_
