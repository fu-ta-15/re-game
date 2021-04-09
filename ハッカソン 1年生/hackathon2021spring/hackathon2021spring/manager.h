//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//
//	manager.h
//	Author:池田悠希
//
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "main.h"
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//前方宣言
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CRenderer;
class CFade;
class CSound;
class CInputKeyboard;
class ICGamemode;
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//クラス定義
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
class CManager
{
public:
	//モードタイプ
	typedef enum
	{
		MODE_NONE = -1,
		MODE_TITLE,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_RESULT,
		MODE_MAX
	} MODE;

	CManager();     //コンストラクタ
	~CManager();    //デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);    //初期化関数
	void Uninit(void);                                             //終了関数
	void Update(void);                                             //更新関数
	void Draw(void);                                               //描画関数
	static CRenderer* GetRenderer(void);                           //ゲッター
	//static CSound* GetSound(void){return m_pSound;}
	static void LoadFile(void);
	static void UnloadFiles(void);
	static void SetMode(const MODE mode);    // モード切替
	static MODE GetMode(void);
	static CFade* GetFade(void){return m_pFade;}   // フェードの取得
	static ICGamemode*CManager::GetGamemode(void);
	static CInputKeyboard* GetInput(void);
private:
    static CRenderer* m_pRenderer;    //レンダラのポインタ
    //static CSound* m_pSound;
    static CFade* m_pFade;            // フェードのポインタ
    static MODE m_mode;               // モードの変数
	static CInputKeyboard* m_pInput;
	static ICGamemode* m_pGamemode;
};

#endif
