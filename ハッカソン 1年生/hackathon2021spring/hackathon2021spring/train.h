#pragma once
//====================================================================
//
// 線路の処理 (rail.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _TRAIN_H_
#define _TRAIN_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "model_himiya.h"
#include "rail.h"

//================================================
// マクロ定義
//================================================


//================================================
// クラス宣言
//================================================

// UIクラス
class CTrain : public CModelHimiya
{
public:
	CTrain();
	~CTrain();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CTrain *Create(D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rot;
	CRail							*m_pRailed;
	bool							m_bGetTop;
};

#endif
