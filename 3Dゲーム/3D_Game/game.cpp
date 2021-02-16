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
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "pause.h"
#include "player.h"
#include "Dinput.h"
#include "camera.h"
#include "light.h"
#include "model.h"
#include "shadow.h"
#include "billboard.h"
#include "meshfield.h"
#include "meshwall.h"
#include "bullet.h"
#include "collision.h"
#include "bulletptcl.h"
#include "effect.h"
#include "mob.h"

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
	InitBillboard();
	InitMeshfield();
	InitMeshWall();
	InitBullet();
	InitScore();
	InitPause();
	InitBulletPT();
	InitEffect();
	InitMob();

	//PlaySound(SOUND_LABEL_BGM002);

	// 壁の配置
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f);
	SetMeshWall(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 100.0f, 25.0f);
	SetMeshWall(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 100.0f, 25.0f);
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
	UninitBillboard();
	UninitMeshfield();
	UninitMeshWall();
	UninitBullet();
	UninitScore();
	UninitPause();
	UninitBulletPT();
	UninitEffect();
	UninitMob();

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

		UpdateModel();
		UpdateShadow();
		UpdateBillboard();
		UpdateBullet();
		UpdatePos();
		PlayerCollision();
		UpdateScore();
		UpdateBulletPT();
		UpdateEffect();
		UpdateMob();
		SetEffect(D3DXVECTOR3(20.0f, 0.0f, 20.0f), D3DXCOLOR(1.0f, 0.4f, 0.7f, 1.0f), 5.0f, 5.0f, 5.0f, 5, 60);
		SetEffect(D3DXVECTOR3(20.0f, 0.0f, 20.0f), D3DXCOLOR(0.0f, 0.4f, 0.7f, 1.0f), 5.0f, 5.0f, 5.0f, 5, 60);

	}
	UpdateCamera();
	Updatelight();
	UpdateMeshfield();
	UpdateMeshWall();


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
	DrawBullet();
	DrawScore();
	DrawBulletPT();
	DrawBillboard();
	DrawEffect();
	DrawModel();
	DrawMob();

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

