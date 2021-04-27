//##################################################################################################################################################################//
//
// タイトルヘッダファイル [title.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _TITLE_H_
#define _TITLE_H_

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// インクルードファイル
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "main.h"

typedef struct
{
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
	D3DXVECTOR3 g_VtxMinTitle;		// モデルの最小値（MIN）
	D3DXVECTOR3	g_VtxMaxTitle;		// モデルの最大値（MAX）
}TitleModel;

typedef struct
{
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 size;				// サイズ
	D3DXCOLOR col;					// 色
	int nTurnFade;					// フェイドの切り替え用
}TitleUi;

//=====================================================================================================================================================================//
// プロトタイプ宣言
//=====================================================================================================================================================================//
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

/* モデル */
void InitTitleModel(void);
void UninitTitleModel(void);
void UpdateTitleModel(void);
void DrawTitleModel(void);

/* UI */
HRESULT InitTitleUi(void);
void UninitTitleUi(void);
void UpdateTitleUi(void);
void DrawTitleUi(void);

#endif 