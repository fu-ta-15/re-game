//=============================================================================
//
// スタンバイ画面描画処理 [stand_by.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _STAND_BY_H_
#define _STAND_BY_H_

#include "main.h"
#include "scene.h"

// マクロ定義
#define STAND_BY_SIZE			(D3DXVECTOR2(1000.0f, 800.0f))			// 画面のサイズ
#define STAND_BY_SIGN_SIZE		(D3DXVECTOR2(400.0f, 100.0f))			// サインサイズ
#define STAND_BY_SIGN_POS		(D3DXVECTOR3(1000.0f, 600.0f,0.0f))

//==============================================================================
// スタンバイ画面クラス
//==============================================================================
class CStandBy : public CScene
{
public:
	CStandBy(int nPriority = PRIORITY_UI);
	~CStandBy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CStandBy *Create(void);

	// 消去
	void DeleteWindow(void);

private:
	CScene2D *m_pBase;			// 大元ポインタ
	CScene2D *m_pControlSign;	// 操作サイン用画像

	D3DXVECTOR2 m_size;			// キャラのサイズ
};

#endif