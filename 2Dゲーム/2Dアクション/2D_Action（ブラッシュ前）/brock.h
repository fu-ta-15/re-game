//##################################################################################################################################################################//
//
// ブロックヘッダファイル [brock.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _BROCK_H_
#define _BROCK_H_

#include "main.h"


typedef enum
{
	BROCK_STOP_RIGHT = 0,
	BROCK_STOP_LEFT,
	BROCK_STOP_NO,
	BROCK_STOP_MAX
}BROCK_STOP;

//=====================================================================================================================================================================//
// 構造体
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;	// 中心座標・現在の座標
	D3DXVECTOR3 Oldpos;	// 過去の座標
	D3DXVECTOR3 move;	// 移動量
	float fWidth;		// 幅
	float fHeigth;		// 高さ
	bool HitPlayer;
	bool bUse;			// 使用か不使用か
	BROCK_STOP BrockStop;
}BROCK;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitBrock(void);
void UninitBrock(void);
void UpdateBrock(void);
void DrawBrock(void);
void SetBrock(D3DXVECTOR3 pos, float fWidth, float fHeigth);
void MoveBrock(void);
BROCK *GetBrock(void);
#endif 