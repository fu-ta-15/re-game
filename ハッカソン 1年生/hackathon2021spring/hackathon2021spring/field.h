//=============================================================================
//
// 背景処理 [wall.h]
// Author : 樋宮 匠
//
//=============================================================================

// 2重インクルード防止用
#ifndef _WALL_H_
#define _WALL_H_
//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "main.h"
#include "object.h"
#include "train.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FIELD_WIDTH  50
#define FIELD_HEIGHT 20

#define FIELD_WIDTH_GAME     100
#define FIELD_WIDTH_TUTORIAL 50

#define CUBE_SIZE 50

//*****************************************************************************
// プレイヤークラス定義
//*****************************************************************************
class CField
{
public:
	CField();
	~CField();

	typedef enum
	{
		TUTORIAL = 0,
		GAME
	}TYPE_FIELD;

	typedef enum
	{
		NONE = 0,
		TREE,
		STONE_BREAK,
		STONE_UNBREAK,
		PLAYER,
		RAIL,
		TRAIN,
		GOAL,
	}TYPE_TILE;

	HRESULT Init(void);
	void Update();
	void Draw();
	void Uninit();
	void LoadMapData();
	static CField * Create(TYPE_FIELD type = TUTORIAL);
	void SetField(void);
	TYPE_TILE GetTile(int nHeight, int nWidth);
	CTrain * GetTrain(void) { return m_pTrain; }
private:
	// メンバ変数
	TYPE_TILE					m_aGround[FIELD_HEIGHT][FIELD_WIDTH];
	int							m_nWidth;
	int							m_nHeight;
	CTrain						*m_pTrain;
};
#endif