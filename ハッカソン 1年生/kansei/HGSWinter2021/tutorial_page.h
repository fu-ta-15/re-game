//=============================================================================
//
// チュートリアルページ描画処理 [tutorial_page.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TUTORIAL_PAGE_H_
#define _TUTORIAL_PAGE_H_

#include "main.h"
#include "scene.h"

//==============================================================================
// チュートリアルページクラス
//==============================================================================
class CTutorialPage : public CScene2D
{
public:
	typedef enum
	{
		TUTORIAL_PAGE_0 = 0,
		TUTORIAL_PAGE_1,
		TUTORIAL_PAGE_2,
		TUTORIAL_PAGE_3,
		TUTORIAL_PAGE_4,
		TUTORIAL_PAGE_5,
		TUTORIAL_PAGE_MAX
	}TUTORIAL_PAGE;

	CTutorialPage(int nPriority = PRIORITY_BG);
	~CTutorialPage();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CTutorialPage *Create(D3DXVECTOR3 pos);

	int GetPageCnt(void) { return m_nPageCnt; }

private:
	CScene2D *m_pScene2D[TUTORIAL_PAGE_MAX];		// ポリゴンクラスポインタ
	int m_nPageCnt;									// ページのカウント
	static D3DXCOLOR m_col[TUTORIAL_PAGE_MAX];		// 色
};
#endif
