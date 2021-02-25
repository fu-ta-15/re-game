//##################################################################################################################################################################//
//
// プレイヤー処理 [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//インクルードファイル　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "game.h"
#include "Keyinput.h"
#include "sound.h"
#include "fade.h"
#include "pause.h"
#include "Dinput.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "meshfield.h"
#include "meshwall.h"
#include "collision.h"
#include "effect.h"
#include "mob.h"
#include "score.h"
#include "time.h"


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// マクロ　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//グローバル変数　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
bool g_bPause;		// ポーズ
int g_nCuntTime;	// ゲーム開始までのカウント

//=====================================================================================================================================================================//
// ゲームの初期化処理                                                                                                                
//=====================================================================================================================================================================//
HRESULT InitGame()
{
	// 変数の初期化
	g_bPause = false;
	g_nCuntTime = 120;

	InitCamera();
	Initlight();
	InitModel();
	InitShadow();
	InitMeshfield();
	InitMeshWall();
	InitPause();
	InitEffect();
	InitMob();
	InitCollision();
	InitScore();
	InitTime();
	//PlaySound(SOUND_LABEL_BGM002);

	// 壁の配置
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, WALL_POS), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_POS), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(-WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	return S_OK;
}

//=====================================================================================================================================================================//
// ゲームの終了処理
//=====================================================================================================================================================================//
void UninitGame(void)
{
	// サウンド停止
	StopSound();

	UninitCamera();
	Uninitlight();
	UninitModel();
	UninitShadow();
	UninitMeshfield();
	UninitMeshWall();
	UninitPause();
	UninitEffect();
	UninitMob();
	UninitScore();
	UninitTime();

	// サウンドストップ
	//StopSound(SOUND_LABEL_BGM002);	//BGM
	//StopSound(SOUND_LABEL_SE_PAUSE2);	//BGM
}

//=====================================================================================================================================================================//
//ゲームの更新処理
//=====================================================================================================================================================================//
void UpdateGame(void)
{
	// フェードの情報
	FADE pFade;
	pFade = GetFade();

	Player *pPlayer = GetPlayer();
	Moblayer *pMoblayer = GetMoblayer();

	g_nCuntTime--;

	// ポーズ開始
	if (pFade == FADE_NONE)
	{// フェードが何もしていないとき
		if (GetKeyboardTrigger(DIK_P) == true || GetKeypadTrigger(11) == true)
		{// Pが押されたとき
			//PlaySound(SOUND_LABEL_SE_PAUSE2);
			g_bPause = g_bPause ? false : true;	// falseかtrueに切り替える
		}
	}
	if (g_bPause == true)
	{// ポーズ中
		UpdatePause();
	}
	else if (g_nCuntTime < 0)
	{
		UpdateCamera();
		Updatelight();
		UpdateModel();
		UpdateMob();
		UpdatePos();
		UpdateScore();
		UpdateTime();
	}

	UpdateMeshfield();
	UpdateMeshWall();
	UpdateShadow();

	UpdateEffect();
	SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.8f, 0.5f, 0.23f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 4);
	SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.8f, 0.5f, 0.3f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 3);
	SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.9f, 0.3f, 0.1f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 1);
	SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 5);


#ifdef _DEBUG	// デバッグのみ
	if (pFade == FADE_NONE)
	{// フェードが何もしていない状態のとき
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{// フェードの更新
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
#endif

}

//=====================================================================================================================================================================//
// ゲームの描画処理
//=====================================================================================================================================================================//
void DrawGame(void)
{

	SetCamera();
	DrawMeshfield();
	DrawShadow();
	DrawMeshWall();
	DrawEffect();
	DrawMob();
	DrawModel();
	DrawScore();
	DrawTime();


	//ポーズの描画
	if (g_bPause == true)
	{//TRUEの場合
		DrawPause();
	}
}

//=====================================================================================================================================================================//
//ポーズのセット
//=====================================================================================================================================================================//
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

