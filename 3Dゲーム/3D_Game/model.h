//##################################################################################################################################################################//
//
// モデルヘッダファイル [model.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MODEL_H_
#define _MODEL_H_


#include "main.h"

//=====================================================================================================================================================================//
// 構造体
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 move;				// 移動量
	D3DXVECTOR3 rot;				// 回転
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	LPD3DXMESH pMesh;				// メッシュへのポインタ
	LPD3DXBUFFER pBuffMat;			// マテリアルへのポインタ
	DWORD NumMat;					// マテリアルの数
	int nIdxModelParent;			// 親モデルのインデックス
	D3DXVECTOR3 g_VtxMinModel;		// モデルの最小値（MIN）
	D3DXVECTOR3	g_VtxMaxModel;		// モデルの最大値（MAX）

}Model;		// モデル

typedef struct
{
	/* 位置 */
	float Pos_X;
	float Pos_Y;
	float Pos_Z;

	/* 回転 */
	float Rot_X;
	float Rot_Y;
	float Rot_Z;
}KEY;	// キー

typedef struct
{
	int nFrame;						// 再生フレーム
	KEY aKey[2];					// 各モデルのキー要素[パーツの総数]
}KEY_INFO;	// キーの情報の構造体

typedef struct
{
	bool bLoop;				// ループの有・無
	int nNumKey;			// キーの総数
	KEY_INFO aKeyInfo[2];	// キー情報[キーの最大数]
}MOTION_INFO;	// モーション情報構造体

typedef struct
{
	/* プレイヤー情報 */
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 回転
	D3DXVECTOR3 rotDest;			// 回転目的
	D3DXVECTOR3 move;				// 移動量
	D3DXMATRIX mtxWorld;			// ワールドマトリックス

	/* モデル情報 */
	Model aModel[20];				// モデルパーツ[数]
	int nNumModel;					// モデルパーツ数

	/* 影 */
	int nNumShadow;					// 影

	/* モーション */
	MOTION_INFO aMotionInfo[1];		// モーション情報[モーション最大数]
	int nNumMotion;					// モーション数
	bool bLoopMotion;				// ループ有・無
	int nNumKey;					// キー数
	int nKey_No;					// キーNo
	int nCounterMotion;				// モーションカウンター
}Player;	// プレイヤー(見えないモデル)

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void MoveModel(void);
void MotionModel(void);
void FileLoad(void);
Player *GetPlayer(void);

#endif // !_MODEL_H_
