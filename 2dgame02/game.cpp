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
#include "enemy.h"
#include "input.h"
#include "score.h"
#include "sound.h"
#include "fade.h"
#include "pause.h"
#include "time.h"
#include "player.h"
#include "brock.h"
#include "bg.h"
#include "prebg.h"
#include "backbg.h"
#include "point.h"
#include "stage.h"
#include "padinput.h"
#include "action.h"
#include "moneyblock.h"
#include "gauge.h"
#include "ui.h"
#include "stock.h"

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

	// �w�i�̏�����
	InitBg();
	InitBackBg();
	InitPreBg();

	// �v���C���[�̏�����
	InitPlayer();

	// �A�N�V����
	InitAction();

	// �u���b�N�̏�����
	InitBrock();

	// �z��
	InitMoneyBlock();

	// �|�C���g
	InitPoint();

	// �X�e�[�W�̏�����
	InitStage();

	// �G�̏������ݒ�
	InitEnemy();

	// �X�R�A�̏������ݒ�
	InitScore();

	// �^�C���̏�����
	InitTime();

	// �|�[�Y�̏���������
	InitPause();

	// �Q�[�W
	InitGauge();

	InitUi();

	InitStock();

	PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//=====================================================================================================================================================================//
// �Q�[���̏I������
//=====================================================================================================================================================================//
void UninitGame(void)
{
	// �T�E���h��~
	StopSound();

	// �w�i�̏I������
	UninitBg();
	UninitBackBg();
	UninitPreBg();

	// �v���C���[�̏I������
	UninitPlayer();

	// �A�N�V����
	UninitAction();

	// �u���b�N�̏I������
	UninitBrock();

	// �z��
	UninitMoneyBlock();

	// �|�C���g
	UninitPoint();

	// �G�̏I������
	UninitEnemy();

	// �X�R�A�̏I������
	UninitScore();

	// �^�C���̏I������
	UninitTime();

	// �|�[�Y�̏I������
	UninitPause();

	// �Q�[�W
	UninitGauge();

	UninitUi();

	UninitStock();

	// �T�E���h�X�g�b�v
	StopSound(SOUND_LABEL_BGM002);	//BGM
	StopSound(SOUND_LABEL_SE_PAUSE2);	//BGM
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
			PlaySound(SOUND_LABEL_SE_PAUSE2);
			g_bPause = g_bPause ? false : true;	// false��true�ɐ؂�ւ���
		}
	}
	if (g_bPause == true)
	{// �|�[�Y��
		UpdatePause();
	}
	else if (g_nCuntTime < 0)
	{
		// �X�e�[�W�Ǘ�
		UpdateStage();

		// �w�i
		UpdateBg();

		// ���̔w�i
		UpdateBackBg();

		// �u���b�N
		UpdateBrock();

		// �z��
		UpdateMoneyBlock();

		// �v���C���[
		UpdatePlayer();

		// �A�N�V����
		UpdateAction();

		// �|�C���g
		UpdatePoint();

		// �Q�[�W
		UpdateGauge();

		UpdateUi();

		UpdateStock();

		// �G�̍X�V����
		UpdateEnemy();

		// �X�R�A�̍X�V����
		UpdateScore();

		// �^�C���̍X�V����
		UpdateTime();

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
}

//=====================================================================================================================================================================//
// �Q�[���̕`�揈��
//=====================================================================================================================================================================//
void DrawGame(void)
{
	//�w�i
	DrawBg();

	//���̔w�i
	DrawBackBg();

	//��O�̔w�i
	DrawPreBg();

	//�u���b�N
	DrawBrock();

	// �z��
	DrawMoneyBlock();

	//�G�̕`�揈��
	DrawEnemy();

	//�v���C���[
	DrawPlayer();

	//�|�C���g
	DrawPoint();

	//�A�N�V����
	DrawAction();

	//�^�C���̕`�揈��
	DrawTime();

	// �Q�[�W
	DrawGauge();

	DrawAction();

	DrawUi();

	//�X�R�A�̕`�揈��
	DrawScore();

	DrawStock();

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
