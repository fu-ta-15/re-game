//==============================================================================
//
// テキストデータ管理〔textdata.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include "textdata.h"
#include "textdata_system.h"
#include "textdata_texture.h"
#include "textdata_pause.h"
#include "textdata_ranking.h"
#include "textdata_rankingselect.h"
#include "stdio.h"

// 静的メンバ変数宣言
char *CTextData::m_pFileName[TEXTDATA_MAX] =
{
	{ "data/TEXT/systemdata.txt" },			// ルール管理
	{ "data/TEXT/texturedata.txt" },		// テクスチャデータ
	{ "data/TEXT/pausedata.txt" },			// ポーズポリゴン情報
	{ "data/TEXT/ranking.txt" },			// ランキング
	{ "data/TEXT/ranking_selectdata.txt" },	// ランキング選択データ情報
};

CTextDataTexture *CTextData::m_pDataTexture = NULL;					// テクスチャデータのポインタ
CTextDataPause *CTextData::m_pDataPause = NULL;						// ポーズデータのポインタ
CTextDataRankingSelect *CTextData::m_pDataRankingSelect = NULL;		// ランキング選択データのポインタ

//==============================================================================
// コンストラクタ
//==============================================================================
CTextData::CTextData()
{

}

//==============================================================================
// デストラクタ
//==============================================================================
CTextData::~CTextData()
{

}

//==============================================================================
// 生成処理
//==============================================================================
CTextData *CTextData::Create(void)
{
	// ローカル変数宣言
	CTextData *pTextData;
	pTextData = new CTextData;	// インスタンス生成

								// テキストデータ
	if (pTextData != NULL)
	{
		// テキストデータの読み込み
		pTextData->LoadTextAll();
	}

	return pTextData;
}

//==============================================================================
// テキストデータの全読み込み
//==============================================================================
void CTextData::LoadTextAll(void)
{
	// テクスチャデータの生成
	m_pDataTexture = CTextDataTexture::Create();

	// ポーズデータの生成
	m_pDataPause = CTextDataPause::Create();

	// ランキング選択データの生成
	m_pDataRankingSelect = CTextDataRankingSelect::Create();

	// ルールのデータ読み込み
	CTextDataSystem::LoadData();
}

//==============================================================================
// テキストデータの全読み込み
//==============================================================================
void CTextData::UninitAll(void)
{
	// テクスチャデータの破棄
	if (m_pDataTexture != NULL)
	{
		m_pDataTexture->Unload();
		m_pDataTexture = NULL;
	}

	// ポーズデータの破棄
	if (m_pDataPause != NULL)
	{
		m_pDataPause->Unload();
		m_pDataPause = NULL;
	}

	// ランキング選択データの破棄
	if (m_pDataRankingSelect != NULL)
	{
		m_pDataRankingSelect->Unload();
		m_pDataRankingSelect = NULL;
	}
}