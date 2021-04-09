//===============================================
//
// フィールド処理 (field.cpp)
// Author : 樋宮匠
//
//===============================================

#define _CRT_SECURE_NO_WARNINGS

//========================
// インクルードファイル
//========================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include "cube.h"
#include "player.h"
#include "rail.h"
#include "tool.h"
#include "train.h"

//========================================
// 静的メンバ変数宣言
//========================================

//=============================================================================
// コンストラクタ
// Author : 樋宮匠
//=============================================================================
CField::CField()
{
	for (int nCountHeight = 0; nCountHeight < FIELD_HEIGHT; nCountHeight++)
	{
		for (int nCountWidth = 0; nCountWidth < FIELD_WIDTH; nCountWidth++)
		{
			m_aGround[nCountHeight][nCountWidth] = NONE;
		}
	}

	m_nHeight = FIELD_HEIGHT;
	m_nWidth = FIELD_WIDTH;
}

//=============================================================================
// デストラクタ
// Author : 樋宮匠
//=============================================================================
CField::~CField()
{
}

//=============================================================================
// 初期化処理
// Author : 樋宮匠
//=============================================================================
HRESULT CField::Init(void)
{
	m_nHeight = FIELD_HEIGHT;
	m_nWidth = FIELD_WIDTH;

	return S_OK;
}

//=============================================================================
// 終了処理
// Author : 樋宮匠
//=============================================================================
void CField::Uninit(void)
{
}

//=============================================================================
// 更新処理
// Author : 樋宮匠
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// 描画処理
// Author : 樋宮匠
//=============================================================================
void CField::Draw(void)
{
}

//=============================================================================
// マップデータ読み込み処理
// Author : 樋宮匠
//=============================================================================
void CField::LoadMapData(void)
{
	FILE *pFile = NULL;
	int nLoadHeight = 0;
	int nLoadWidth = 0;

		pFile = fopen("./Data/map/rail_map.csv", "r");
	m_nWidth = FIELD_WIDTH;

	// 開けた
	if (pFile != NULL)
	{
		for (int nCountMap = 0; nCountMap < m_nWidth * m_nHeight; nCountMap++)
		{
			while (fscanf(pFile, "%d,", &m_aGround[nLoadHeight][nLoadWidth]) != EOF)
			{
				nLoadWidth++;
				if (nLoadWidth >= m_nWidth)
				{
					nLoadWidth = 0;
					nLoadHeight++;
				}
			}
		}

		fclose(pFile);
	}
	// 開けない
	else
	{
		printf("開けれませんでした\n");
	}
}

//=============================================================================
// インスタンス生成処理
// Author : 樋宮匠
//=============================================================================
CField* CField::Create(TYPE_FIELD type)
{
	CField *m_pField;

	m_pField = new CField;
	m_pField->Init();

	// フィールド読み込み
	m_pField->LoadMapData();

	// フィールド設置
	m_pField->SetField();

	return m_pField;
}

//=============================================================================
// フィールド生成処理
// Author : 樋宮匠
//=============================================================================
void CField::SetField(void)
{
	int nHeight = 0;

	for (int nCountHeight = m_nHeight - 1; nCountHeight > -1; nCountHeight--)
	{
		for (int nCountWidth = 0; nCountWidth < m_nWidth; nCountWidth++)
		{
			CCube::Create(CCube::DIRT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, 0.0f, -nCountWidth * CUBE_SIZE));

			switch (m_aGround[nHeight][nCountWidth])
			{
			case TREE:
				CCube::Create(CCube::TREE, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case STONE_BREAK:
				CCube::Create(CCube::STONE_BREAK, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case STONE_UNBREAK:
				CCube::Create(CCube::STONE_UNBREAK, D3DXVECTOR3((nCountHeight - 0.5f) * CUBE_SIZE, CUBE_SIZE, -nCountWidth * CUBE_SIZE));
				break;
			case PLAYER:
				CPlayer::Create(D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
				CTool::Create(CTool::PICKAXE, D3DXVECTOR3((nCountHeight - 1.5f) * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
				CTool::Create(CTool::AXE, D3DXVECTOR3((nCountHeight - 1.5f) * CUBE_SIZE, CUBE_SIZE / 2.0f, -(nCountWidth + 1) * CUBE_SIZE));
				break;
			case RAIL:
				CRail::Create(CRail::STRAIGHT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE))->SetRailed();
				break;
			case TRAIN:
				CRail::Create(CRail::STRAIGHT, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE))->SetRailed();
				m_pTrain = CTrain::Create(D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -(nCountWidth + 0.5f) * CUBE_SIZE));
				break;
			case GOAL:
				CRail::Create(CRail::GOAL, D3DXVECTOR3(nCountHeight * CUBE_SIZE, CUBE_SIZE / 2.0f, -nCountWidth * CUBE_SIZE));
			default:
				break;
			}
		}

		nHeight++;
	}
}

//・・・・・・・・・・・・・・・・・・・・・・・・・・・
//タイル取得
//・・・・・・・・・・・・・・・・・・・・・・・・・・・
CField::TYPE_TILE CField::GetTile(int nHeight, int nWidth)
{
	return m_aGround[nHeight][nWidth];
}