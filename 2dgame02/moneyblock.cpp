//##################################################################################################################################################################//
//
// �G�̏��� [enemy.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "moneyblock.h"
#include "input.h"
#include "score.h"
#include "player.h"
#include "brock.h"
#include "sound.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_MONEYBLOCK_TYPE			(300)																										// �G�̎��
#define MAX_MoneyBrock				(256)																										// �G�̐�
#define COLOR_RED					(255)																										// �ԐF
#define COLOR_BULUE					(255)																										// �F
#define COLOR_GREEN					(255)																										// �ΐF
#define COLOR_ALPHA					(255)																										// �A���t�@�l
#define MAX_COLOR					(255)																										// �F�̍ő�l
#define COLOR_DAMAGEALPHA			(255/5)																										// �_���[�W��Ԃ̃A���t�@�l
#define VECTORO_ZERO				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))																				// VECTORO�̏�����
#define MOVE_ZERO					(D3DXVECTOR3(0.0f, 0.0f, 0.0f))																				// �X�s�[�h�[��
#define COLOR_ZERO					(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))																			// �F�̏�����
#define ALPHA_INTERVAL				(5)																											// �A���t�@�l�̃C���^�[�o��
#define PVTEX_MAX					(4)																											// pVtx
#define TEXPOS_ONE					(1.0f)																										// �e�N�X�`�����W�P
#define TEXPOS_HALF					(0.5f)																										// �e�N�X�`�����W�Q
#define TEXPOS_ZERO					(0.0f)																										// �e�N�X�`�����W�R
#define ADD_SCORE					(1)																											// �X�R�A
#define MONEYBLOCK_SIZE				(30)																										// �G�l�~�[�̃T�C�Y
#define MONEYBLOCK_TEX				(30)
#define MOVE_SPEED_RIGTH			(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT				(D3DXVECTOR3(5.1f,0.0f,0.0f))


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureMoneyBlock = {};			// �e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMoneyBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
MONEYBLOCK g_aMoneyBlock[MAX_MoneyBrock];				// �G�̎��
int g_AppCuntBlock;

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitMoneyBlock(void)
{
	//�|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	MONEYBLOCK *pMoneyBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	pMoneyBlock = &g_aMoneyBlock[0];

	// �����_��
	srand((unsigned int)time(NULL));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\brock.png", &g_apTextureMoneyBlock);

	//�G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{// �G�̍\����
		g_aMoneyBlock[nCntEnemy].pos = VECTORO_ZERO;
		g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_ZERO;
		g_aMoneyBlock[nCntEnemy].bUse = false;
		g_aMoneyBlock[nCntEnemy].nCounterState = 0;
		g_aMoneyBlock[nCntEnemy].nLife = 0;
		g_aMoneyBlock[nCntEnemy].state = MONEYBLOCKSTATE_NORMAL;
	}
	g_AppCuntBlock = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX * MAX_MoneyBrock, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMoneyBlock, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);
	//�G�̏������ݒ�
	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		//�e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		//�v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMoneyBlock->Unlock();
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitMoneyBlock(void)
{
	if (g_pVtxBuffMoneyBlock != NULL)
	{//���_�o�b�t�@�̊J��
		g_pVtxBuffMoneyBlock->Release();
		g_pVtxBuffMoneyBlock = NULL;
	}
	if (g_apTextureMoneyBlock != NULL)
	{//�e�N�X�`���̊J��
		g_apTextureMoneyBlock->Release();
		g_apTextureMoneyBlock = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateMoneyBlock(void)
{
	//�\���̂̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == true)
		{// �G�����݂��Ă���Ƃ�
		 //���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

			// �n�ʂ̓����蔻��
			if (g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_TEX > 400)
			{// �c�͈̔�
				g_aMoneyBlock[nCntEnemy].pos.y = 400 - MONEYBLOCK_TEX;
			}
			//�G�̏�ԊǗ�
			StateMoneyBlock(nCntEnemy);
		}
		//�v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}
	//�G�̔z�u
	RandSetMoneyBlock();
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawMoneyBlock(void)
{
	//�|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	MONEYBLOCK *pEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	pEnemy = &g_aMoneyBlock[0];

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMoneyBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureMoneyBlock);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * PVTEX_MAX, 2);
		}
	}
}

//=====================================================================================================================================================================//
//�G�̐ݒu����Ƃ��̐ݒ�											                                                                                                   //
//=====================================================================================================================================================================//
void SetMoneyBlock(D3DXVECTOR3 pos, int nLife)
{
	// ���_�|�C���^
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == false)
		{// �g�p���Ă��Ȃ��G
		 // �G�̈ʒu�Ǝ�ނ̏��
			g_aMoneyBlock[nCntEnemy].pos = pos;				// �ʒu
			g_aMoneyBlock[nCntEnemy].nLife = nLife;			// �̗�
															// �n�ʂɗ�������
			g_aMoneyBlock[nCntEnemy].pos.y = 400 - MONEYBLOCK_TEX;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x - MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y + MONEYBLOCK_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aMoneyBlock[nCntEnemy].pos.x + MONEYBLOCK_SIZE, g_aMoneyBlock[nCntEnemy].pos.y - MONEYBLOCK_SIZE, 0.0f);

			//�G�����݂��Ă���
			g_aMoneyBlock[nCntEnemy].bUse = true;
			break;
		}
		//���_���S�i�߂�
		pVtx += PVTEX_MAX;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
//�G�̃����_���z�u																																					   //
//=====================================================================================================================================================================//
void RandSetMoneyBlock(void)
{
	g_AppCuntBlock++;
	// ���E�̓G�̔z�u�̏����l
	int RandPosRight = SCREEN_WIDTH + (rand() % 30 + 20);
	int RandPosLeft = 0 - (rand() % 30 + 20);
	int MOVE = rand() % 1 + 4;
	if ((g_AppCuntBlock % (rand() % 400 + 500)) == 0)
	{
		SetMoneyBlock(D3DXVECTOR3(((float)RandPosRight), 0.0f, 0.0f), 10);
	}
	if ((g_AppCuntBlock % (rand() % 600 + 600)) == 0)
	{
		SetMoneyBlock(D3DXVECTOR3(((float)RandPosLeft), 0.0f, 0.0f), 10);
	}
}

//=====================================================================================================================================================================//
// �G�̏�ԊǗ��@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void StateMoneyBlock(int nIdx)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	// �ϐ��̏�����
	int nScore = 0;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);
	if (g_aMoneyBlock[nIdx].state == MONEYBLOCKSTATE_FALSE)
	{// �G�����ł���Ƃ�

	 // ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		// �e���_�̃J���[���
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 255);

		// �A���t�@�l�����炷
		//g_fEnemyAlpha[nIdx] -= ALPHA_INTERVAL;

		//	if (g_fEnemyAlpha[nIdx] <= 0)
		//	{// �A���t�@�l���[���ȉ��̂Ƃ�
		//	 // �X�R�A
		//		nScore += ADD_SCORE;
		//		// �X�R�A���Z
		//		//AddScore(nScore);

		//		// �e�N�X�`�����W�̍X�V
		//		pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
		//		pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
		//		pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		//		pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);

		//		// �e���_�̃J���[���
		//		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//		// �A���t�@�l��߂�
		//		g_fEnemyAlpha[nIdx] = COLOR_ALPHA;

		//		// �G������
		//		g_aMoneyBlock[nIdx].bUse = false;

		//		// �G�̏�Ԃ��m�[�}����
		//		g_aMoneyBlock[nIdx].state = ENEMYSTATE_NORMAL;
		//	}
		//}
		//else if (g_aMoneyBlock[nIdx].state == ENEMYSTATE_DAMAGE)
		//{//�_���[�W���
		// // �v���X4�i�߂�
		//	pVtx += (PVTEX_MAX * nIdx);

		//	// �J�E���^�[���}�C�i�X
		//	g_aMoneyBlock[nIdx].nCounterState--;

		//	if (g_aMoneyBlock[nIdx].nCounterState <= 0)
		//	{// �J�E���^�[���[���̏ꍇ

		//	 // �m�[�}�����
		//		g_aMoneyBlock[nIdx].state = ENEMYSTATE_NORMAL;

		//		// �F�̍X�V
		//		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	}
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffMoneyBlock->Unlock();
}

//=====================================================================================================================================================================//
// �G�̈ړ��Ǘ��@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void MoveMoneyBlock(void)
{
	PLAYER *pPlayer;
	BROCK *pBrock;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	for (int nCntEnemy = 0; nCntEnemy < MAX_MoneyBrock; nCntEnemy++)
	{
		if (g_aMoneyBlock[nCntEnemy].bUse == true)
		{//�G�����݂��Ă���Ƃ�

			if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
			{
				g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_SPEED_RIGTH;
			}
			else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
			{
				g_aMoneyBlock[nCntEnemy].PlayerMove = MOVE_SPEED_LEFT;
			}

			g_aMoneyBlock[nCntEnemy].pos.x += g_aMoneyBlock[nCntEnemy].PlayerMove.x;
		}
	}
}


//=====================================================================================================================================================================//
// �G���e�̓���������                                                                                                                                                   //
//=====================================================================================================================================================================//
bool HitMoneyBlock(int nIdx, int nDamage)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	// �G�̗̑͌���
	g_aMoneyBlock[nIdx].nLife -= nDamage;

	if (g_aMoneyBlock[nIdx].nLife <= 0)
	{// �̗͂��[���̂Ƃ�
	 // �G�̏���
		g_aMoneyBlock[nIdx].state = MONEYBLOCKSTATE_FALSE;
		return true;
	}
	else
	{// �[������Ȃ��Ƃ�
	 // �_���[�W��
	 //PlaySound(SOUND_LABEL_SE_HIT);

	 // �_���[�W���
		g_aMoneyBlock[nIdx].state = MONEYBLOCKSTATE_DAMAGE;

		// ��Ԃ̃J�E���^�[
		g_aMoneyBlock[nIdx].nCounterState = ALPHA_INTERVAL;

		// ���_�o�b�t�@�̃��b�N
		g_pVtxBuffMoneyBlock->Lock(0, 0, (void**)&pVtx, 0);

		// �G�̏�񕪐i�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �F�̍X�V
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);

		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffMoneyBlock->Unlock();
		return false;
	}
}

//=====================================================================================================================================================================//
// �G�̏��@�@�@�@�@                                                                                                                                                   //
//=====================================================================================================================================================================//
MONEYBLOCK *GetMoneyBlock(void)
{
	return &g_aMoneyBlock[0];
}
