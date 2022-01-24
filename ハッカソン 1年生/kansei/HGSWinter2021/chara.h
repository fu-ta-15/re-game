//=============================================================================
//
// キャラクター描画処理 [chara.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _CHARA_H_
#define _CHARA_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define CHARA_SIZE			(D3DXVECTOR2(150.0f,300.0f))			// キャラクターのサイズ
#define CHARA_POS_LEFT		(D3DXVECTOR3(300.0f, 520.0f, 0.0f))		// キャラクター左の位置
#define CHARA_POS_RIGHT		(D3DXVECTOR3(980.0f, 520.0f, 0.0f))		// キャラクター右の位置

//==============================================================================
// キャラクタークラス
//==============================================================================
class CChara : public CScene
{
public:
	typedef enum
	{
		CHARAPHASE_NONE = 0,	// 開始前
		CHARAPHASE_WAIT,		// 入力待機
		CHARAPHASE_ACTIVE,		// 入力開始
		CHARAPHASE_INTERVAL,	// 入力間隔
		CHARAPHASE_DUMMY,		// 偽物の入力
		CHARAPHASE_MAX
	}CHARAPHASE;

	CChara(int nPriority = PRIORITY_UI);
	~CChara();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CChara *Create(void);

	void CharaMove(void);	// キャラ演出

	void GameEnd(void);		// 終了時の演出

private:
	CScene2D *m_apScene2D[2];	// 2Dポリゴンのポインタ

	D3DXVECTOR2 m_size;			// キャラのサイズ

	int m_nCntActive;			// 入力指示までのカウント

	bool m_bFallSide;			// 降下左右	
};

#endif