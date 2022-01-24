//=============================================================================
//
// サイン(指示)描画処理 [sign.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SIGN_H_
#define _SIGN_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define SIGNCNT_MAX	(180)

//==============================================================================
// タイマークラス
//==============================================================================
class CSign : public CScene
{
public:
	typedef enum
	{
		SIGNPHASE_NONE = 0,	// 開始前
		SIGNPHASE_WAIT,		// 入力待機
		SIGNPHASE_ACTIVE,	// 入力開始
		SIGNPHASE_INTERVAL,	// 入力間隔
		SIGNPHASE_DUMMY,	// 偽物の入力
		SIGNPHASE_MAX
	}SIGNPHASE;

	typedef enum
	{
		IMAGETYPE_NONE = 0,	// 待機状態
		IMAGETYPE_TRUE,		// 正しい画像
		IMAGETYPE_DAMMY_A,	// 偽画像0
		IMAGETYPE_DAMMY_B,	// 偽画像1
		IMAGETYPE_DAMMY_C,	// 偽画像2
		IMAGETYPE_DAMMY_D,	// 偽画像3
		IMAGETYPE_DAMMY_E,	// 偽画像4
		IMAGETYPE_DAMMY_F,	// 偽画像5
		IMAGETYPE_DAMMY_G,	// 偽画像6
		IMAGETYPE_DAMMY_H,	// 偽画像7
		IMAGETYPE_DAMMY_I,	// 偽画像8
		IMAGETYPE_DAMMY_J,	// 偽画像9
		IMAGETYPE_DAMMY_K,	// 偽画像10
		IMAGETYPE_DAMMY_L,	// 偽画像11
		IMAGETYPE_DAMMY_M,	// 偽画像12
		IMAGETYPE_DAMMY_N,	// 偽画像13
		IMAGETYPE_DAMMY_O,	// 偽画像14
		IMAGETYPE_DAMMY_P,	// 偽画像15
		IMAGETYPE_DAMMY_Q,	// 偽画像16
		IMAGETYPE_DAMMY_R,	// 偽画像17
		IMAGETYPE_MAX
	}IMAGETYPE;


	CSign(int nPriority = PRIORITY_UI);
	~CSign();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSign *Create(void);

	// サイン処理の開始
	void StartSign(void) { m_signPhase = SIGNPHASE_WAIT; }

	void SignBehave(void);	// サインの挙動

	SIGNPHASE GetPhase(void) { return m_signPhase; }

private:
	CScene2D *m_pScene2D;		// 2Dポリゴンのポインタ

	D3DXVECTOR2 m_size;			// サインのサイズ
	D3DXCOLOR m_col;			// サインの色
	int m_nCntActive;			// 入力指示までのカウント

	int m_nCntChange;			// 変更数
	int m_nCntEnd;				// 終了する値
	int m_nCntSelect;			// 選択

	SIGNPHASE m_signPhase;		// サインの状態
	IMAGETYPE m_imageType;		// 出す画像の種類
};

#endif