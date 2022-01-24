//=============================================================================
//
// テキストデータ管理 [textdata.h]
// Author : Mare Horiai
//
//============================================================================= 
#ifndef _TEXTDATA_H_
#define _TEXTDATA_H_

#include "main.h"

// マクロ定義
#define TEXT_NUM	(128)		// テキストデータバイト数

// 前方宣言
class CTextDataObject;			// オブジェクトデータクラス
class CTextDataTexture;			// テクスチャデータクラス
class CTextDataPause;			// ポーズデータクラス
class CTextDataRankingSelect;	// ランキング選択データクラス
class CTextDataRanking;			// ランキングデータ

//==============================================================================
// テキスト管理クラス
//==============================================================================
class CTextData
{
public:
	// テキストデータの種類
	typedef enum
	{
		TEXTDATA_SYSTEM = 0,	// ゲームルールデータ
		TEXTDATA_TEXTURE,		// テクスチャデータ
		TEXTDATA_PAUSE,			// ポーズデータ
		TEXTDATA_RANKING,
		TEXTDATA_RANKINGSELECT,	// ランキング選択データ
		TEXTDATA_MAX
	}TEXTDATA;

	CTextData();
	~CTextData();

	static CTextData *Create(void);	// 生成

	static void LoadTextAll(void);
	static void UninitAll(void);

	// データの取得

	static CTextDataObject *GetDataObject(void) { return m_pDataObject; }
	static CTextDataTexture *GetDataTexture(void) { return m_pDataTexture; }
	static CTextDataPause *GetDataPause(void) { return m_pDataPause; }

	static CTextDataRanking	*GetDataRanking(void) { return m_pDataRanking; }
	static CTextDataRankingSelect *GetDataSelectRanking(void) { return m_pDataRankingSelect; }

protected:
	static char *m_pFileName[TEXTDATA_MAX];			// 読み込むファイル名パス
	//static char *m_pFileNameObj;					// 読み取るオブジェクトファイル名パス
	//static char *m_pFileNameRanking;				// 読み取るランキングファイル名パス

private:
	static CTextDataObject *m_pDataObject;					// オブジェクトデータ
	static CTextDataTexture *m_pDataTexture;				// テクスチャデータ
	static CTextDataPause *m_pDataPause;					// ポーズデータ
	static CTextDataRanking *m_pDataRanking;				// ランキングデータ
	static CTextDataRankingSelect *m_pDataRankingSelect;	// ランキング選択データ
};

#endif