//=============================================================================
//
// 終了後選択描画処理 [select.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _SELECT_H_
#define _SELECT_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define SELECT_SIZE		(D3DXVECTOR2(200.0f, 100.0f))
#define RETRY_POS		(D3DXVECTOR3(640.0f, 200.0f,0.0f))
#define TOTITLE_POS		(D3DXVECTOR3(640.0f, 400.0f,0.0f))

//==============================================================================
// 選択肢クラス
//==============================================================================
class CSelect : public CScene
{
public:
	typedef enum
	{
		SELECT_RETRY = 0, 
		SELECT_TOTITLE,
		SELECT_MAX
	}SELECT;

	CSelect(int nPriority = PRIORITY_UI);
	~CSelect();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CSelect *Create(void);

	// 勝敗演出
	void Active(void);

	static void On(void) { m_bActiveOn = true; }

private:
	CScene2D *m_pBase;			// ベース
	CScene2D *m_apScene[2];		// 選択肢

	SELECT m_select;
	static bool m_bActiveOn;
};

#endif