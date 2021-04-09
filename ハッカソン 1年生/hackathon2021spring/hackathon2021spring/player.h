#pragma once
//====================================================================
//
// プレイヤーの処理 (player.h)
// Author : 樋宮匠
//
//====================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//================================================
// インクルードファイル
//================================================
#include "main.h"
#include "model_himiya.h"

//================================================
// マクロ定義
//================================================
#define MOVE_SPEED (3)
#define PLAYER_ROT_SPEED (0.1f)
//================================================
// クラス宣言
//================================================

// UIクラス
class CPlayer : public CModelHimiya
{
public:
	CPlayer();
	~CPlayer();

	typedef enum
	{
		ANGLE_UP = 0,
		ANGLE_RIGHT,
		ANGLE_DOWN,
		ANGLE_LEFT,
		ANGLE_MAX
	}ANGLE;

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void Unload(void);
	static CPlayer *Create(D3DXVECTOR3 pos);
	ANGLE GetAngle(void);
private:

	float InputToAngle(void);
	void Interaction(void);
	void Move(void);
	void LimitMap(void);
	static LPDIRECT3DTEXTURE9		m_pTexture;
	static LPD3DXMESH				m_pMesh;
	static LPD3DXBUFFER				m_pBuffMat;
	static DWORD					m_nNumMat;
	D3DXVECTOR3						m_rotdest;
	int								m_nPosMapWidth;
	int								m_nPosMapHeight;
	ANGLE							m_angle;
	D3DXVECTOR3						m_posold;
};

#endif