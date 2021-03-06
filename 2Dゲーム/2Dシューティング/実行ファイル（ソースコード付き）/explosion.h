//##################################################################################################################################################################//
//
// エクスプロージョンヘッダファイル [explosion.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//=====================================================================================================================================================================//
// 爆発の種類
//=====================================================================================================================================================================//
typedef enum
{
	EXP_TYPE_ENEMY = 0,
	EXP_TYPE_PLAYER,
	EXP_TYPE_SKILL,
	EXP_TYPE_MAX
}EXP_TYPE;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR color);

#endif 