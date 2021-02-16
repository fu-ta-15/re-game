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
	InitScore();
	InitPause();
	InitBulletPT();
	InitEffect();
	InitMob();

	//PlaySound(SOUND_LABEL_BGM002);

	// �ǂ̔z�u
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f, 25.0f);
	SetMeshWall(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f), 100.0f, 25.0f);
	SetMeshWall(D3DXVECTOR3(-50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -D3DX_PI / 2, 0.0f), 100.0f, 25.0f);
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
	UninitScore();
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

