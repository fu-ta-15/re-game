//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�C���N���[�h�t�@�C���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "game.h"
#include "Keyinput.h"
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
// �}�N���@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define WALL_POS			(FIELD_POS / 2)
#define WALL_WIGTH			(FIELD_POS)
#define WALL_HEIGHHT		(300.0f)
#define PI_HAFE				(D3DX_PI / 2)


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//
bool g_bPause;		// �|�[�Y
int g_nCuntTime;	// �Q�[���J�n�܂ł̃J�E���g

//=====================================================================================================================================================================//
// �Q�[���̏���������                                                                                                                
//=====================================================================================================================================================================//
HRESULT InitGame()
{
	// �ϐ��̏�����
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
	InitPause();
	InitBulletPT();
	InitEffect();
	InitMob();
	InitCollision();
	//PlaySound(SOUND_LABEL_BGM002);

	// �ǂ̔z�u
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, WALL_POS), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_POS), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(-WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	return S_OK;
}

//=====================================================================================================================================================================//
// �Q�[���̏I������
//=====================================================================================================================================================================//
void UninitGame(void)
{
	// �T�E���h��~
	StopSound();

	UninitCamera();
	Uninitlight();
	UninitModel();
	UninitShadow();
	UninitBillboard();
	UninitMeshfield();
	UninitMeshWall();
	UninitBullet();
	UninitPause();
	UninitBulletPT();
	UninitEffect();
	UninitMob();

	// �T�E���h�X�g�b�v
	//StopSound(SOUND_LABEL_BGM002);	//BGM
	//StopSound(SOUND_LABEL_SE_PAUSE2);	//BGM
}

//=====================================================================================================================================================================//
//�Q�[���̍X�V����
//=====================================================================================================================================================================//
void UpdateGame(void)
{
	// �t�F�[�h�̏��
	FADE pFade;
	pFade = GetFade();

	Player *pPlayer = GetPlayer();
	Moblayer *pMoblayer = GetMoblayer();

	g_nCuntTime--;

	// �|�[�Y�J�n
	if (pFade == FADE_NONE)
	{// �t�F�[�h���������Ă��Ȃ��Ƃ�
		if (GetKeyboardTrigger(DIK_P) == true || GetKeypadTrigger(11) == true)
		{// P�������ꂽ�Ƃ�
			//PlaySound(SOUND_LABEL_SE_PAUSE2);
			g_bPause = g_bPause ? false : true;	// false��true�ɐ؂�ւ���
		}
	}
	if (g_bPause == true)
	{// �|�[�Y��
		UpdatePause();
	}
	else if (g_nCuntTime < 0)
	{

		UpdateModel();
		UpdateShadow();
		UpdateBillboard();
		UpdateBullet();
		UpdatePos();
		UpdateBulletPT();
		UpdateMob();
		UpdateEffect();
		SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.8f, 0.5f, 0.23f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 4);
		SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.8f, 0.5f, 0.3f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 3);
		SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(0.9f, 0.3f, 0.1f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 1);
		SetEffect(D3DXVECTOR3(pPlayer->aModel[0].pos.x + pPlayer->pos.x, pPlayer->aModel[0].pos.y + pPlayer->pos.y - 5.0f, pPlayer->aModel[0].pos.z + pPlayer->pos.z), D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f), 3.0f, 0.5f, -2.0f, 100, 5);
		UpdateCamera();
		Updatelight();
		UpdateMeshfield();
		UpdateMeshWall();


	}


#ifdef _DEBUG	// �f�o�b�O�̂�
	if (pFade == FADE_NONE)
	{// �t�F�[�h���������Ă��Ȃ���Ԃ̂Ƃ�
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{// �t�F�[�h�̍X�V
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
#endif

}

//=====================================================================================================================================================================//
// �Q�[���̕`�揈��
//=====================================================================================================================================================================//
void DrawGame(void)
{
	Moblayer *pMoblayer = GetMoblayer();
	Player *pPlayer = GetPlayer();


	SetCamera();
	DrawMeshfield();
	DrawShadow();
	DrawMeshWall();
	DrawBullet();
	DrawBulletPT();
	DrawBillboard();
	DrawEffect();

	for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++, pMoblayer++)
	{
		if (pMoblayer->pos.z > pPlayer->pos.z)
		{
			DrawMob();
			DrawModel();
		}
		else
		{
			DrawModel();
			DrawMob();
		}
	}


	//�|�[�Y�̕`��
	if (g_bPause == true)
	{//TRUE�̏ꍇ
		DrawPause();
	}
}

//=====================================================================================================================================================================//
//�|�[�Y�̃Z�b�g
//=====================================================================================================================================================================//
void SetPause(bool bPause)
{
	g_bPause = bPause;
}

