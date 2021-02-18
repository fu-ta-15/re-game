//##################################################################################################################################################################//
//
// �X�e�[�W�Ǘ����� [stage.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "stage.h"
#include "player.h"
#include "brock.h"
#include "prebg.h"
#include "backbg.h"
#include "bg.h"
#include "input.h"
#include "padinput.h"
#include "enemy.h"
#include "moneyblock.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)								// �ԐF
#define COLOR_BULUE			(255)								// �F
#define COLOR_GREEN			(255)								// �ΐF
#define COLOR_ALPHA			(255)								// �A���t�@�l
#define HEIGTH_SIZE			(570)
#define MAX_RIGTH			(3000)
#define MAX_LEFT			(-3000)
#define MOVE_SPEED			(0.005f)
#define LENGTH_PLAYER_X		(30)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_PLAYER_Y		(50)								// ���S����e���_�̋��������߂鐔�l
#define MAX_BROCK			(1080)
#define PLAYER_TEX			(12)								// �e�N�X�`���̗]��



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
STAGE g_Stage;
GAMEPOS g_Gamepos;											// �Q�[���̍��W


															//=====================================================================================================================================================================//
															// �X�e�[�W�̏���������
															//=====================================================================================================================================================================//
HRESULT InitStage(void)
{
	g_Stage.fHeigth = 0.0f;
	g_Stage.fLeft = MAX_LEFT;
	g_Stage.fRigth = MAX_RIGTH;
	// �Q�[�����W�̏�����
	g_Gamepos.GamePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �X�e�[�W�̏I������
//=====================================================================================================================================================================//
void UninitStage(void)
{


}

//=====================================================================================================================================================================//
// �X�e�[�W�̍X�V����
//=====================================================================================================================================================================//
void UpdateStage(void)
{
	// �\���̂̃|�C���^
	PLAYER *pPlayer;
	BROCK *pBrock;
	BACKBG *pBackBg;
	PREBG *pPreBg;

	// ���擾
	pPlayer = GetPlayer();
	pBrock = GetBrock();
	pBackBg = GetBackBg();
	pPreBg = GetPreBg();

	// �v���C���[�̈ړ�
	MovePlayer();
	MoveStage();


}

void MoveStage(void)
{
	BROCK *pBrock;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	bool *pPad = GetPadPlress();

	if (GetKeyboardPresse(DIK_D) == true || pPad[JPPRESS_RIGTH] == true)
	{// �E
		if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->move.x != 0.0f)
		{// �v���C���[���E�����E�u���b�N���ړ����Ă���E�G���A�͈̔͂ɂ���
			MoveBack();						// ��
			MovePre();						// ��O
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x += 0.5f;	// �X�e�[�W�̍��W
		}
		else if (pBrock->bUse == false)
		{// �u���b�N���Ȃ����E�G���A�͈̔͂ɂ���
			MoveBack();						// ��
			MovePre();						// ��O
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x += 0.5f;	// �X�e�[�W�̍��W
		}
		MoveBrock();					// �u���b�N�̈ړ�
	}
	else if (GetKeyboardPresse(DIK_A) == true || pPad[JPPRESS_LEFT] == true)
	{// ��
		if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->move.x != 0.0f)
		{
			MoveBack();						// ��
			MovePre();						// ��O
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x -= 0.5f;	// �X�e�[�W�̍��W
		}
		else if (pBrock->bUse == false)
		{
			MoveBack();						// ��
			MovePre();						// ��O
			MoveEnemy();
			MoveMoneyBlock();
			g_Gamepos.GamePos.x -= 0.5f;	// �X�e�[�W�̍��W
		}
		MoveBrock();					// �u���b�N�̈ړ�
	}
}

//=====================================================================================================================================================================//
// �X�e�[�W�̏��
//=====================================================================================================================================================================//
GAMEPOS *GetGamePos(void)
{
	return &g_Gamepos;
}

//=====================================================================================================================================================================//
// �u���b�N�̓����蔻��
//=====================================================================================================================================================================//
bool CollisionBrock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldpos, D3DXVECTOR3 *pMove, float fWidth, float fHeirth)
{
	// �|�C���^
	BROCK *pBrock;
	// ���擾
	pBrock = GetBrock();
	// ����
	bool bLandBrock = false;

	if (pBrock->bUse == true)
	{// �g�p���̂�
		if ((pPos->x + fWidth) > pBrock->pos.x && (pPos->x - fWidth) < (pBrock->pos.x + pBrock->fWidth))
		{// �u���b�N�͈̔�X�Ƀ|�C���^������
			if ((pOldpos->y + fHeirth) <= (pBrock->pos.y))
			{// �|�C���^���u���b�N����ɂ���
				if ((pPos->y + fHeirth) > (pBrock->pos.y))
				{// �u���b�N�̏�Ŏ~�܂�
					pMove->y = 0.0f;
					pPos->y = pBrock->pos.y - fHeirth;
					bLandBrock = true;
				}
			}
			if ((pOldpos->y - fHeirth) >= (pBrock->pos.y + pBrock->fHeigth))
			{// �|�C���^���u���b�N��艺�ɂ���
				if ((pPos->y - fHeirth) < (pBrock->pos.y + pBrock->fHeigth))
				{// �|�C���^�̓����u���b�N�ɓ�����
					pMove->y = 1.0f;
					pPos->y = (pBrock->pos.y + pBrock->fHeigth) + fHeirth;
				}
			}
		}
		if ((pPos->y + fHeirth) > pBrock->pos.y && (pPos->y - fHeirth) < (pBrock->pos.y + pBrock->fHeigth))
		{// �|�C���^���u���b�N��Y���W�ɂ���
			if ((pOldpos->x + fWidth) <= pBrock->pos.x)
			{// �|�C���^������
				if ((pPos->x + fWidth) > pBrock->pos.x)
				{// �E���ɂ߂荞��
					pPos->x = pBrock->pos.x - fWidth;
				}
			}
			if ((pOldpos->x - fWidth) >= (pBrock->pos.x + pBrock->fWidth))
			{// �|�C���^���E��
				if ((pPos->x - fWidth) < (pBrock->pos.x + pBrock->fWidth))
				{// �����ɂ߂荞��
					pPos->x = pBrock->pos.x + pBrock->fWidth + fWidth;
				}
			}
		}
	}
	// �����Ԃ�
	return bLandBrock;
}
//=====================================================================================================================================================================//
// �v���C���[�̓����蔻��
//=====================================================================================================================================================================//
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pOldpos, D3DXVECTOR3 *pMove, float fWidth, float fHeirth)
{
	bool bLandPlayer = false;
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	if ((pPos->y + fHeirth) > (pPlayer->pos.y - LENGTH_PLAYER_Y) && (pPos->y) < (pPlayer->pos.y + LENGTH_PLAYER_Y))
	{// �v���C���[���u���b�N��Y���W�ɂ���
		if ((pOldpos->x + fWidth) <= pPlayer->pos.x - PLAYER_TEX)
		{// �v���C���[������
			if ((pPos->x + fWidth) > pPlayer->pos.x - PLAYER_TEX)
			{// �E���ɂ߂荞��
				pPos->x = pPlayer->pos.x - PLAYER_TEX - fWidth;
				pMove->x = 0.0f;
				bLandPlayer = true;
			}
		}
		if ((pOldpos->x) >= (pPlayer->pos.x + PLAYER_TEX))
		{// �v���C���[���E��
			if ((pPos->x) < (pPlayer->pos.x + PLAYER_TEX))
			{// �����ɂ߂荞��
				pPos->x = pPlayer->pos.x + PLAYER_TEX;
				pMove->x = 0.0f;
				bLandPlayer = true;
			}
		}
	}
	return bLandPlayer;
}
