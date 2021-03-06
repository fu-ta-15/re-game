﻿//##################################################################################################################################################################//
//
// ゲージヘッダファイル [gauge.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _GAUGE_H_
#define _GAUGE_H_

#include "main.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 第一ゲージ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef enum
{
	GAUGE_TYPE_BATTLE = 0,	// 戦闘
	GAUGE_TYPE_SEARCH,		// 探索
	GAUGE_TYPE_MAX
}GAUGE_TYPE;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 第二ゲージ（戦闘
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef enum
{
	BATTLE_TYPE_ATTACK = 0,	// 攻撃
	BATTLE_TYPE_GUARD,		// 防御
	BATTLE_TYPE_MAX
}BATTLE_TYPE;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 第二ゲージ（探索
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef enum
{
	SEARCH_TYPE_ONE = 0,	// 一倍
	SEARCH_TYPE_TWO,		// 二倍
	SEARCH_TYPE_MAX
}SEARCH_TYPE;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 第三ゲージ（速さ・長さ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef enum
{
	GAUGE_STAT_GOOD = 0,	// 高
	GAUGE_STAT_MIDDLE,		// 普通
	GAUGE_STAT_BAD,			// 低
	GAUGE_STAT_MAX
}GAUGE_STAT;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 最終ゲージ
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef enum
{
	GAUGE_EVALUATION_PERFECT = 0,	// 高評価
	GAUGE_EVALUATION_GOOD,			// 普通
	GAUGE_EVALUATION_BAD,			// 低評価
	GAUGE_EVALUATION_MAX
}GAUGE_EVALUATION;


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// ゲージの構造体
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef struct
{
	D3DXCOLOR PerfectColor;		// ゲージの色
	D3DXCOLOR GoodColor;		// ゲージの色
	D3DXCOLOR BadColor;			// ゲージの色

	float PerfectStart;			// ゲージの開始
	float PerfectGole;			// ゲージのゴール

	float GoodStart;			// ゲージの開始
	float GoodGole;				// ゲージのゴール

	float BadStart;				// ゲージの開始
	float BadGole;				// ゲージのゴール


	GAUGE_TYPE Gauge_Type;				 // ゲージの種類
	GAUGE_EVALUATION Gauge_Evaluation;	 // ゲージの最終評価

}GAUGE_ONE;

typedef struct
{
	D3DXCOLOR PerfectColor;		// ゲージの色
	D3DXCOLOR GoodColor;		// ゲージの色
	D3DXCOLOR BadColor;			// ゲージの色

	float PerfectStart;			// ゲージの開始
	float PerfectGole;			// ゲージのゴール

	float GoodStart;			// ゲージの開始
	float GoodGole;				// ゲージのゴール

	float BadStart;				// ゲージの開始
	float BadGole;				// ゲージのゴール


	BATTLE_TYPE Battle_Type;			 // 戦闘の種類
	GAUGE_EVALUATION Gauge_Evaluation;	 // ゲージの最終評価

}GAUGE_TWO;

typedef struct
{
	D3DXCOLOR PerfectColor;		// ゲージの色
	D3DXCOLOR GoodColor;		// ゲージの色
	D3DXCOLOR BadColor;			// ゲージの色

	float PerfectStart;			// ゲージの開始
	float PerfectGole;			// ゲージのゴール

	float GoodStart;			// ゲージの開始
	float GoodGole;				// ゲージのゴール

	float BadStart;				// ゲージの開始
	float BadGole;				// ゲージのゴール


	SEARCH_TYPE Search_Type;			 // 探索の種類
	GAUGE_EVALUATION Gauge_Evaluation;	 // ゲージの最終評価

}GAUGE_THREE;

typedef struct
{
	D3DXCOLOR PerfectColor;		// ゲージの色
	D3DXCOLOR GoodColor;		// ゲージの色
	D3DXCOLOR BadColor;			// ゲージの色

	float PerfectStart;			// ゲージの開始
	float PerfectGole;			// ゲージのゴール

	float GoodStart;			// ゲージの開始
	float GoodGole;				// ゲージのゴール

	float BadStart;				// ゲージの開始
	float BadGole;				// ゲージのゴール


	GAUGE_STAT Gauge_Stat;				 // ゲージのステータス
	GAUGE_EVALUATION Gauge_Evaluation;	 // ゲージの最終評価

}GAUGE_FOUR;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//プロトタイプ宣言
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
HRESULT InitGauge(void);
void UninitGauge(void);
void UpdateGauge(void);
void DrawGauge(void);
GAUGE_ONE *GetGauge(void);

#endif 