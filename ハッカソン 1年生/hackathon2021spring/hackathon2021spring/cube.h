#pragma once
//====================================================================
//
// キューブの処理 (cube.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _CUBE_H_
#define _CUBE_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// マクロ定義
//================================================


//================================================
// クラス宣言
//================================================

// UIクラス
class CCube : public CModelHimiya
{
public:
	CCube();
	~CCube();

	typedef enum
	{
		DIRT = 0,
		STONE_BREAK,
		STONE_UNBREAK,
		TREE,
		MAX_CUBE
	}TYPE_CUBE;

	HRESULT Init(TYPE_CUBE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CCube *Create(TYPE_CUBE type, D3DXVECTOR3 pos);
private:
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh[MAX_CUBE];
	static LPD3DXBUFFER				m_pBuffMat[MAX_CUBE];
	static DWORD					m_nNumMat[MAX_CUBE];
	D3DXVECTOR3						m_rot;
	TYPE_CUBE						m_type;
};

#endif