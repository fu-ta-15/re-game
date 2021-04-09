#pragma once
//====================================================================
//
// 線路の処理 (rail.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _RAIL_H_
#define _RAIL_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// マクロ定義
//================================================
#define RAIL_MAX 100

//================================================
// クラス宣言
//================================================

// UIクラス
class CRail : public CModelHimiya
{
public:
	CRail();
	~CRail();

	typedef enum
	{
		UNRAILED = 0,
		RAILED,
	}RAIL_STATE;

	typedef enum
	{
		STRAIGHT = 0,
		LEFT,
		RIGHT,
		GOAL,
		MAX_RAIL
	}TYPE_RAIL;

	HRESULT Init(TYPE_RAIL type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CRail *Create(TYPE_RAIL type, D3DXVECTOR3 pos);

	void SetRailed(void);
	static CRail * GetRailedTop(void) { return m_pRailedTop; }
	CRail * GetRailedNext(void) { return m_pRailedNext; }
	CRail * GetRailedCur(void) { return m_pRailedCur; }
	TYPE_RAIL GetType(void) { return m_type; }
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh[MAX_RAIL];
	static LPD3DXBUFFER				m_pBuffMat[MAX_RAIL];
	static DWORD					m_nNumMat[MAX_RAIL];
	D3DXVECTOR3						m_rot;
	RAIL_STATE						m_state;
	TYPE_RAIL						m_type;
	static CRail					*m_pRailedTop;
	static CRail					*m_pRailedCur;
	CRail							*m_pRailedNext;
	CRail							*m_pRailedPrev;
};

#endif