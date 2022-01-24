
//==============================================================================
//
// リザルトモード処理〔result.cpp〕
// Author : Mare Horiai
//
//==============================================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "gamepad.h"
#include "result.h"
#include "bg.h"
#include "fade.h"
#include "result_picture.h"
#include "result_score.h"
#include "result_timer.h"
#include "result_fallcount.h"
#include "result_score_extra.h"
#include "result_bonuscount.h"
#include "sound.h"
#include "mode.h"

// 静的メンバ変数宣言
CResultPicture *CResult::m_pResultPicture[PICTYPE_MAX] = {};
CResultScore *CResult::m_pResultScore = NULL;
CResultTimer *CResult::m_pResultTimer = NULL;
CResultBonus *CResult::m_pResultBonus = NULL;
CResultFallCount *CResult::m_pResultFallCount = NULL;
CResultScoreEx *CResult::m_pResultScoreEx[EXSCORETYPE_MAX] = {};
CResult::ENDSTATE CResult::m_endState;	// ゲーム終了時の状態

//==============================================================================
// コンストラクタ
//==============================================================================
CResult::CResult(int nPriority) : CMode(nPriority)
{
	
}

//==============================================================================
// デストラクタ
//==============================================================================
CResult::~CResult()
{

}

//==============================================================================
// リザルト画面の初期化処理
//==============================================================================
HRESULT CResult::Init(void)
{
	// 背景の生成
	CBg::Create();

	// ロゴの生成
	if (m_endState == ENDSTATE_CLEAR)
	{	// クリア状況
		m_pResultPicture[PICTYPE_MAIN] = CResultPicture::Create(R_PICT_POS, VECTOR3_NULL, R_PICT_SIZE, "RESULT_LOGO_CLEAR");
	}
	else
	{
		m_pResultPicture[PICTYPE_MAIN] = CResultPicture::Create(R_PICT_POS, VECTOR3_NULL, R_PICT_SIZE, "RESULT_LOGO_OVER");
	}

	m_pResultPicture[PICTYPE_YOURSCORE] = CResultPicture::Create(R_PICT_SCORE_POS, VECTOR3_NULL, R_PICT_SCORE_SIZE, "RANKING_YOURSCORE");
	m_pResultPicture[PICTYPE_TIMERLOGO] = CResultPicture::Create(R_PICT_TIMER_POS, VECTOR3_NULL, R_PICT_TIMER_SIZE, "TIMER_LOGO");
	m_pResultPicture[PICTYPE_COUNTLOGO] = CResultPicture::Create(R_PICT_COUNT_POS, VECTOR3_NULL, R_PICT_COUNT_SIZE, "FALL_LOGO");
	m_pResultPicture[PICTYPE_BONUSLOGO] = CResultPicture::Create(R_PICT_BONUS_POS, VECTOR3_NULL, R_PICT_BONUS_SIZE, "BONUS_LOGO");


	m_pResultPicture[PICTYPE_TIMERMARK_0] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");
	m_pResultPicture[PICTYPE_TIMERMARK_1] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "PLUS");
	m_pResultPicture[PICTYPE_TIMERMARK_2] = CResultPicture::Create(R_PICT_TIMER_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");

	m_pResultPicture[PICTYPE_COUNTMARK_0] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");
	m_pResultPicture[PICTYPE_COUNTMARK_1] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "MINUS");
	m_pResultPicture[PICTYPE_COUNTMARK_2] = CResultPicture::Create(R_PICT_COUNT_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");

	m_pResultPicture[PICTYPE_BONUSMARK_0] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_0, VECTOR3_NULL, R_PICT_MARK_SIZE, "MULTI");
	m_pResultPicture[PICTYPE_BONUSMARK_1] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_1, VECTOR3_NULL, R_PICT_MARK_SIZE, "PLUS");
	m_pResultPicture[PICTYPE_BONUSMARK_2] = CResultPicture::Create(R_PICT_BONUS_MARK_POS_2, VECTOR3_NULL, R_PICT_MARK_SIZE, "EQUAL");

	// リザルトスコアの生成
	m_pResultScore = CResultScore::Create(RESULT_SCORE_POS);

	// リザルトタイマー生成
	m_pResultTimer = CResultTimer::Create();

	// リザルトの落下カウント生成
	m_pResultFallCount = CResultFallCount::Create();

	// リザルトのボーナスカウント生成
	m_pResultBonus = CResultBonus::Create();

	// 他リザルトスコアの生成
	// タイマー
	m_pResultScoreEx[EXSCORETYPE_TIMER] = CResultScoreEx::Create(EXSCORE_TIMER_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_TIMER);		// タイマー
	m_pResultScoreEx[EXSCORETYPE_TIMER_CALCU] = CResultScoreEx::Create(EXSCORE_TIMERCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_TIMER]->SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));

	// カウント
	m_pResultScoreEx[EXSCORETYPE_COUNT] = CResultScoreEx::Create(EXSCORE_COUNT_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_TIMER);	// カウント
	m_pResultScoreEx[EXSCORETYPE_COUNT_CALCU] = CResultScoreEx::Create(EXSCORE_COUNTCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_COUNT]->SetCol(D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f));

	// ボーナス
	m_pResultScoreEx[EXSCORETYPE_BONUS] = CResultScoreEx::Create(EXSCORE_BONUS_POS, EXSCORE_SIZE, EXSCORE_DIGIT, EXSCORE_TIMER);
	m_pResultScoreEx[EXSCORETYPE_BONUS_CALCU] = CResultScoreEx::Create(EXSCORE_BONUSCALCU_POS, EXSCORE_CALCU_SIZE, EXSCORE_CALCU_DIGIT, 0);

	m_pResultScoreEx[EXSCORETYPE_BONUS]->SetCol(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));

	// BGMの再生
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RESULT) == true)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM005);
	}

	return S_OK;
}

//==============================================================================
// リザルト画面の終了処理
//==============================================================================
void CResult::Uninit(void)
{
	// BGMの停止
	if (m_pSound != NULL && CManager::GetBGMPlay(CSound::BGMTYPE_RESULT) == true)
	{
		m_pSound->Stop();
	}

	// 表示する図の開放
	for (int nCntType = 0; nCntType < PICTYPE_MAX; nCntType++)
	{
		if (m_pResultPicture[nCntType] != NULL)
		{
			m_pResultPicture[nCntType]->Uninit();
			m_pResultPicture[nCntType] = NULL;
		}
	}

	// リザルトスコアの開放
	if (m_pResultScore != NULL)
	{
		m_pResultScore->Uninit();
		m_pResultScore = NULL;
	}

	// リザルトタイマーの開放
	if (m_pResultTimer != NULL)
	{
		m_pResultTimer->Uninit();
		m_pResultTimer = NULL;
	}

	// リザルトカウントの開放
	if (m_pResultFallCount != NULL)
	{
		m_pResultFallCount->Uninit();
		m_pResultFallCount = NULL;
	}

	// 他リザルトスコアの開放
	for (int nCntScore = 0; nCntScore < EXSCORETYPE_MAX; nCntScore++)
	{
		if (m_pResultScoreEx[nCntScore] != NULL)
		{
			m_pResultScoreEx[nCntScore]->Uninit();
			m_pResultScoreEx[nCntScore] = NULL;
		}
	}


	Release();	// インスタンスのデリート
}

//==============================================================================
// リザルト画面の更新処理
//==============================================================================
void CResult::Update(void)
{
	// フェード情報の取得
	CFade *pFade;
	pFade = CManager::GetFade();
	CFade::FADE fade = pFade->GetFade();

	// キーボードの取得
	CInputKeyboard *keyboard = CManager::GetInputKeyboard();

	// ゲームパッドの取得
	CGamepad *gamepad = CManager::GetInputGamepad();

	// シーン遷移
	if (keyboard->GetTrigger(CInput::KEYINFO_OK) == true || gamepad->GetTrigger(CInput::KEYINFO_OK) == true)
	{
		if (fade == CFade::FADE_NONE && CResultScore::GetShuffleCnt() >= (RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)))
		{
			pFade->SetFade(CFade::FADE_OUT, CMode::MODE_RANKING);
		}
		else if (fade == CFade::FADE_IN)
		{// フェードインのカット
			pFade->FadeInCancel();
		}

		if (CResultScore::GetShuffleCnt() < (RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)) && fade == CFade::FADE_NONE)
		{// カウントの短縮
			CResultScore::SetShuffleCnt((RESULT_SHUFFLE + CNT_ONE_SECOND * (CResultScore::SCORETYPE_MAX - 1)));
		}
	}

	m_pResultScoreEx[EXSCORETYPE_TIMER_CALCU]->ShffleNum(EXSCORETYPE_TIMER_CALCU);
	m_pResultScoreEx[EXSCORETYPE_COUNT_CALCU]->ShffleNum(EXSCORETYPE_COUNT_CALCU);
	m_pResultScoreEx[EXSCORETYPE_BONUS_CALCU]->ShffleNum(EXSCORETYPE_BONUS_CALCU);
}

//==============================================================================
// リザルト画面の描画処理
//==============================================================================
void CResult::Draw(void)
{
}

//==============================================================================
// リザルトモードの生成処理
//==============================================================================
CResult *CResult::Create()
{
	// インスタンス生成
	CResult *pResult;
	pResult = new CResult;

	// 初期化
	pResult->Init();

	return pResult;
}