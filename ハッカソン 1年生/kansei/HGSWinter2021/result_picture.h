//=============================================================================
//
// リザルトに描画する図の処理 [result_picture.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _RESULT_PICTURE_H_
#define _RESULT_PICTURE_H_

#include "main.h"
#include "scene.h"
#include "result.h"

// マクロ定義
#define R_PICT_POS				(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0.0f))	// メインロゴ
#define R_PICT_SIZE				(D3DXVECTOR2(480.0f, 80.0f))
		  
#define R_PICT_SCORE_POS		(D3DXVECTOR3(250.0f, 260.0f, 0.0f))				// スコアロゴ
#define R_PICT_SCORE_SIZE		(D3DXVECTOR2(120.0f, 50.0f))
		  
#define R_PICT_TIMER_POS		(D3DXVECTOR3(100.0f, 450.0f, 0.0f))				// タイマーロゴ
#define R_PICT_TIMER_SIZE		(D3DXVECTOR2(80.0f, 50.0f))
#define R_PICT_TIMER_MARK_POS_0	(D3DXVECTOR3(400.0f, 450.0f, 0.0f))
#define R_PICT_TIMER_MARK_POS_1	(D3DXVECTOR3(500.0f, 450.0f, 0.0f))
#define R_PICT_TIMER_MARK_POS_2	(D3DXVECTOR3(780.0f, 450.0f, 0.0f))

#define R_PICT_COUNT_POS		(D3DXVECTOR3(100.0f, 550.0f, 0.0f))				// カウントロゴ
#define R_PICT_COUNT_SIZE		(D3DXVECTOR2(80.0f, 50.0f))						
#define R_PICT_COUNT_MARK_POS_0	(D3DXVECTOR3(400.0f, 550.0f, 0.0f))
#define R_PICT_COUNT_MARK_POS_1	(D3DXVECTOR3(500.0f, 550.0f, 0.0f))
#define R_PICT_COUNT_MARK_POS_2	(D3DXVECTOR3(780.0f, 550.0f, 0.0f))

#define R_PICT_BONUS_POS		(D3DXVECTOR3(100.0f, 650.0f, 0.0f))				// ボーナスロゴ
#define R_PICT_BONUS_SIZE		(D3DXVECTOR2(80.0f, 50.0f))						
#define R_PICT_BONUS_MARK_POS_0	(D3DXVECTOR3(400.0f, 650.0f, 0.0f))
#define R_PICT_BONUS_MARK_POS_1	(D3DXVECTOR3(500.0f, 650.0f, 0.0f))
#define R_PICT_BONUS_MARK_POS_2	(D3DXVECTOR3(780.0f, 650.0f, 0.0f))

#define R_PICT_MARK_SIZE		(D3DXVECTOR2(30.0f, 30.0f))						// 算用記号のサイズ

// 前方宣言
class CScene2D;	// 2Dポリゴン描画クラス

//==============================================================================
// リザルト画面に描画する図のクラス
//==============================================================================
class CResultPicture : public CResult
{
public:
	CResultPicture(int nPriority = PRIORITY_UI);
	~CResultPicture();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 生成処理
	static CResultPicture *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR2 size, char *pTypeCheck);

private:
	CScene2D *m_pScene2D;	// 2Dポリゴンクラス
};
#endif