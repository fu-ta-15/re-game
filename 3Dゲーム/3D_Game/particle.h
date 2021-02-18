//##################################################################################################################################################################//
//
// パーティクルヘッダファイル [particle.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	  // 位置
	D3DXVECTOR3 move;	  // 移動量
	D3DXCOLOR color;	  // 色
	D3DXMATRIX mtxWorld;			// ワールドマトリックス
	float fRadius;		  // 半径
	int nLife;			  // 生存時間
	bool bUse;			  // 使用しているかどうか
}PARTICLE;


//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos,D3DXVECTOR3 move, int number, int life, D3DXCOLOR color);
PARTICLE *GetParticle(void);

#endif
