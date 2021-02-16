//##################################################################################################################################################################//
//
// 壁ヘッダファイル [meshwall.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"
//=====================================================================================================================================================================//
// マクロ宣言
//=====================================================================================================================================================================//
#define STAGE_MAXPOS_X		(50.0f)
#define STAGE_MAXPOS_Y		(25.0f)	
#define STAGE_MAXPOS_Z		(25.0f)

//=====================================================================================================================================================================//
// 構造体
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 rot;							//向き
	D3DXMATRIX mtxWorld;						//ワールドマトリックス
	float fIdxDeceWidth;						//一頂点の距離
	float fIdxDeceHeight;						//一頂点の距離
	bool bUse;
}MeshWall;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitMeshWall(void);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
void SetMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
MeshWall *GetMeshWall(void);
#endif