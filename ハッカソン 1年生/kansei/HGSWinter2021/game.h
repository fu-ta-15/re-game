
//=============================================================================
//
// ゲームモード処理 [game.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
#include "scene.h"
#include "mode.h"

// 前方宣言
class CPause;			// ポーズクラス
class CTimer;			// タイマークラス
class CFall;			// 落下数クラス
class CSound;			// サウンドクラス
class CStartCntdown;	// 開始時カウントダウンクラス
class CBonus;			// ボーナスクラス
class CCheckpointLogo;	// チェックポイントロゴクラス
class CGamesetLogo;		// ゲーム結果ロゴ
class CUi;				// UIクラス
class CBg;				// 背景クラス
class CSign;			// サインクラス
class CChara;			// キャラクタークラス
class CStandBy;			// スタンバイ画面クラス
class CMatchResult;		// 結果
class CSelect;			// 選択クラス

//==============================================================================
// ゲームモードクラス
//==============================================================================
class CGame : public CMode
{
public:
	// 試合結果の種類
	typedef enum
	{
		MATCH_NONE = 0,	// 決着前
		MATCH_LEFT,		// 左の勝ち
		MATCH_RIGHT,	// 右の勝ち
		MATCH_DRAW,		// 引き分け
		MATCH_MAX	
	}MATCH;

	CGame(int nPriority = PRIORITY_DEFAULT);
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CGame *Create(void);

	//void EndGame(void);

	//void GameClear(void);
	//void GameOver(void);

	static CUi *GetUi(void) { return m_pUi; }			// UIの取得
	static CChara *GetChara(void) { return m_pChara; }	// キャラクターの取得
	static CMatchResult *GetMatchResult(void) { return m_pMatchResult; }

	// ゲーム終了フラグの取得・設定
	static bool GetGameEnd(void) { return m_bGameEnd; }
	static void SetGameEnd(bool bGameEnd) { m_bGameEnd = bGameEnd; }

	// 勝敗情報取得・設定
	static MATCH GetMatch(void) { return m_match; }
	static void SetMatch(MATCH match) { m_match = match; }

private:
	int m_nNumObject;						// オブジェクト数
	int m_nNumMeshfield;					// メッシュフィールドの数
	static CPause *m_pPause;				// ポーズのポインタ

	static bool m_bGameEnd;					// ゲーム終了のフラグ
	static int m_nClearDirectingCnt;		// クリア演出カウント

	static CGamesetLogo *m_pGamesetLogo;

	static CBg *m_pBg;						// 背景ポインタ
	static CUi *m_pUi;						// UIのポインタ
	static CSign *m_pSign;					// サインクラス
	static CChara *m_pChara;				// キャラクラス
	static CStandBy *m_pStandBy;			// スタンバイ画面クラス
	static CMatchResult *m_pMatchResult;	// 結果クラス
	static CSelect *m_pSelect;				// 選択クラス

	static MATCH m_match;							// 勝敗情報
};

#endif