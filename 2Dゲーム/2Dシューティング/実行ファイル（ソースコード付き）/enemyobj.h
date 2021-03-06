//##################################################################################################################################################################//
//
// 敵オブジェクトヘッダファイル [enemyobj.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _ENEMY_OBJCT_H_
#define _ENEMY_OBJCT_H_

#include "main.h"

//=====================================================================================================================================================================//
// 状態
//=====================================================================================================================================================================//
typedef enum
{
	ENEMY_OBJ_NORMAL = 0, 
	ENEMY_OBJ_FALSE,
}ENEMY_OBJ;

//=====================================================================================================================================================================//
//オブジェクトのの構造体
//=====================================================================================================================================================================//
typedef struct
{
	ENEMY_OBJ obj;
	D3DXVECTOR3 objpos;
	ENEMY_OBJ EneOState;
	float fLife;
}ENEOBJCT;

//=====================================================================================================================================================================//
//プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitEnObjct(void);
void UninitEnObjct(void);
void UpdateEnObjct(void);
void DrawEnObjct(void);
ENEOBJCT *GetEnObjct(void);
bool HitEnObjct(float nDamage);

#endif 

