//==============================================================================
//
// 入力処理〔input.h〕
// AUTHOR : MARE HORIAI
//
//==============================================================================
#pragma once
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//==============================================================================
// マクロ定義
//==============================================================================
#define KEY_STATE	(256)	// 入力情報

// 入力クラス
class CInput
{
public:
	typedef enum 
	{
		KEYINFO_OK = 0,				// 決定
		KEYINFO_UP,					// 上
		KEYINFO_DOWN,				// 下
		KEYINFO_LEFT,				// 左
		KEYINFO_RIGHT,				// 右
		KEYINFO_ARROW_UP,			// 上(方向キー)
		KEYINFO_ARROW_DOWN,			// 下(方向キー)
		KEYINFO_ARROW_LEFT,			// 左(方向キー)
		KEYINFO_ARROW_RIGHT,		// 右(方向キー)
		KEYINFO_START_SPACE,		// ジャンプ
		KEYINFO_PAUSE,				// ポーズ
		KEYINFO_TUTO_BACK,			// チュートリアルページ戻し
		KEYINFO_GO_LEFT,			// 左プレイヤーの入力
		KEYINFO_GO_RIGHT,			// 右プレイヤーの入力
		KEYINFO_MAX
	}KEYINFO;

	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;	// 純粋仮想関数化

protected:
	LPDIRECTINPUTDEVICE8 m_pDevice;		// デバイスポインタ
	static LPDIRECTINPUT8 m_pInput;		// 全体で一つで良い(static:静的メンバ変数)	
	static int m_aKeyInfo[KEYINFO_MAX];	// 入力キー情報
};

class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	static CInputKeyboard *Create(HINSTANCE hInstance, HWND hWnd);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);

private:
	BYTE m_aKeyState[KEY_STATE];			// キープレス情報
	BYTE m_aKeyStateTrigger[KEY_STATE];		// キートリガー情報
	BYTE m_aKeyStateRelease[KEY_STATE];		// キーリリース情報
	BYTE m_aKeyStateRepeat[KEY_STATE];		// キーリピート情報

	int m_nCountRepeat;						// リピートカウント
};

#endif
