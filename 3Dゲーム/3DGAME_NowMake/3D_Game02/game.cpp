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
#include "player.h"
#include "shadow.h"
#include "meshfield.h"
#include "meshwall.h"
#include "collision.h"
#include "effect.h"
#include "mob.h"
#include "score.h"
#include "time.h"
#include "modelparticl.h"

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
	InitPlayer();
	InitShadow();
	InitMeshfield();
	InitMeshWall();
	InitPause();
	InitEffect();
	InitMob();
	InitCollision();
	InitScore();
	InitTime();
	InitModelP();

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
	UninitPlayer();
	UninitShadow();
	UninitMeshfield();
	UninitMeshWall();
	UninitPause();
	UninitEffect();
	UninitMob();
	UninitScore();
	UninitTime();
	UninitModelP();
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
	Rock *pMoblayer = GetRock();

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
		UpdatePlayer();
		UpdateMob();
		UpdatePos();
		UpdateScore();
		UpdateTime();
		PlayerCollision();
		UpdateModelP();
		if (GetKeypadTrigger(0) == true)
		{
			SetModelP(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), 3.0f, 0.5f, -2.0f, 2, 100);
		}
	
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
	//DrawShadow();
	DrawMeshWall();
	DrawScore();
	DrawTime();
	DrawPlayer();
	DrawModelP();
	DrawMob();
	DrawEffect();

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

