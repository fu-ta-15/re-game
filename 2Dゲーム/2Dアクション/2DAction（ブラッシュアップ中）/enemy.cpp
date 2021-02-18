//##################################################################################################################################################################//
//
// �G�̏��� [enemy.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "enemy.h"
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
#define MAX_ENYMY_TYPE				(ENEMY_TYPE_MAX)																							// �G�̎��
#define MAX_ENEMY					(256)																										// �G�̐�
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
#define ENEMY_SIZE					(30)																										// �G�l�~�[�̃T�C�Y
#define ENEMY_TEX					(30)
#define MOVE_SPEED_RIGTH			(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT				(D3DXVECTOR3(5.1f,0.0f,0.0f))
#define POS_Y_MAX					(400)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_ENYMY_TYPE] = {};	//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̎��
float g_fAngleEnemy;										//�G�̑Ίp���̊p�x
int g_fEnemyAlpha[MAX_ENEMY];								//�G�̓����x
int g_AppCuntEnemy;

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitEnemy(void)
{
	//�|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;
	ENEMY *pEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	pEnemy = &g_aEnemy[0];

	// �����_��
	srand((unsigned int)time(NULL));

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy3.png", &g_apTextureEnemy[ENEMY_TYPE_MANY]);
	//�G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		// �G�̍\����
		g_aEnemy[nCntEnemy].pos = VECTORO_ZERO;
		g_aEnemy[nCntEnemy].move = MOVE_ZERO;
		g_aEnemy[nCntEnemy].PlayerMove = MOVE_ZERO;
		g_aEnemy[nCntEnemy].Type = {};
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].bScreenVisible = false;
		// �z��̕ϐ�
		g_fEnemyAlpha[nCntEnemy] = COLOR_ALPHA;
	}

	g_AppCuntEnemy = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	//�G�̏������ݒ�
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//�e���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitEnemy(void)
{
	if (g_pVtxBuffEnemy != NULL)
	{//���_�o�b�t�@�̊J��
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENYMY_TYPE; nCntEnemy++)
	{
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{//�e�N�X�`���̊J��
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateEnemy(void)
{
	//�\���̂̃|�C���^
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G�����݂��Ă���Ƃ�

		 // �ړ��̍X�V
			g_aEnemy[nCntEnemy].move.y += 1.0f;
			//g_aEnemy[nCntEnemy].move.x = 1.0f;
			// �ʒu�̍X�V
			g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;

			// �ړ��E��]�ʂ̌���
			g_aEnemy[nCntEnemy].move.y += (0 - g_aEnemy[nCntEnemy].move.y) * 0.002f;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

			// �n�ʂ̓����蔻��
			if (g_aEnemy[nCntEnemy].pos.y + ENEMY_TEX > POS_Y_MAX)
			{// �c�͈̔�
				g_aEnemy[nCntEnemy].move.y = 0.0f;
				g_aEnemy[nCntEnemy].pos.y = POS_Y_MAX - ENEMY_TEX;
			}
			//�G�̏�ԊǗ�
			StateEnemy(nCntEnemy);
		}
		//�v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}
	//�G�̔z�u
	RandSetEnemy();
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawEnemy(void)
{
	//�|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	ENEMY *pEnemy;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();
	pEnemy = &g_aEnemy[0];

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->Type]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * PVTEX_MAX, 2);
		}
	}
}

//=====================================================================================================================================================================//
//�G�̐ݒu����Ƃ��̐ݒ�											                                                                                                   //
//=====================================================================================================================================================================//
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, ENEMY_TYPE Type, int nLife)
{
	// ���_�|�C���^
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{// �g�p���Ă��Ȃ��G
		 // �G�̈ʒu�Ǝ�ނ̏��
			g_aEnemy[nCntEnemy].pos = pos;				// �ʒu
			g_aEnemy[nCntEnemy].Type = Type;			// ���
			g_aEnemy[nCntEnemy].nLife = nLife;			// �̗�

			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH / 2)
			{
				g_aEnemy[nCntEnemy].move = move * -1;		// �ړ�
			}
			if (g_aEnemy[nCntEnemy].pos.x < SCREEN_WIDTH / 2)
			{
				g_aEnemy[nCntEnemy].move = move;			// �ړ�
			}

			// �n�ʂɗ�������
			g_aEnemy[nCntEnemy].pos.y = POS_Y_MAX - ENEMY_TEX;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);

			//�G�����݂��Ă���
			g_aEnemy[nCntEnemy].bUse = true;
			break;
		}
		//���_���S�i�߂�
		pVtx += PVTEX_MAX;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
//�G�̃����_���z�u																																					   //
//=====================================================================================================================================================================//
void RandSetEnemy(void)
{
	g_AppCuntEnemy++;
	// ���E�̓G�̔z�u�̏����l
	int RandPosRight = SCREEN_WIDTH + (rand() % 30 + 20);
	int RandPosLeft = 0 - (rand() % 30 + 20);
	int MOVE = rand() % 1 + 4;
	if ((g_AppCuntEnemy % (rand() % 400 + 500)) == 0)
	{
		SetEnemy(D3DXVECTOR3(((float)RandPosRight), 0.0f, 0.0f), D3DXVECTOR3((float)(MOVE), 0.0f, 0.0f), ENEMY_TYPE_MANY, 10);
	}
	if ((g_AppCuntEnemy % (rand() % 600 + 600)) == 0)
	{
		SetEnemy(D3DXVECTOR3(((float)RandPosLeft), 0.0f, 0.0f), D3DXVECTOR3((float)(MOVE), 0.0f, 0.0f), ENEMY_TYPE_MANY, 10);
	}

}

//=====================================================================================================================================================================//
// �G�̏�ԊǗ��@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void StateEnemy(int nIdx)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	// �ϐ��̏�����
	int nScore = 0;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
	if (g_aEnemy[nIdx].state == ENEMYSTATE_FALSE)
	{// �G�����ł���Ƃ�

	 // ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �ړ���~
		g_aEnemy[nIdx].move = MOVE_ZERO;

		// �e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		// �e���_�̃J���[���
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_fEnemyAlpha[nIdx]);

		// �A���t�@�l�����炷
		g_fEnemyAlpha[nIdx] -= ALPHA_INTERVAL;

		if (g_fEnemyAlpha[nIdx] <= 0)
		{// �A���t�@�l���[���ȉ��̂Ƃ�
		 // �X�R�A
			nScore += ADD_SCORE;
			// �X�R�A���Z
			//AddScore(nScore);

			// �e�N�X�`�����W�̍X�V
			pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
			pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
			pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
			pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);

			// �e���_�̃J���[���
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

			// �A���t�@�l��߂�
			g_fEnemyAlpha[nIdx] = COLOR_ALPHA;

			// �G������
			g_aEnemy[nIdx].bUse = false;

			// �G�̏�Ԃ��m�[�}����
			g_aEnemy[nIdx].state = ENEMYSTATE_NORMAL;
		}
	}
	else if (g_aEnemy[nIdx].state == ENEMYSTATE_DAMAGE)
	{//�_���[�W���
	 // �v���X4�i�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �J�E���^�[���}�C�i�X
		g_aEnemy[nIdx].nCounterState--;

		if (g_aEnemy[nIdx].nCounterState <= 0)
		{// �J�E���^�[���[���̏ꍇ

		 // �m�[�}�����
			g_aEnemy[nIdx].state = ENEMYSTATE_NORMAL;

			// �F�̍X�V
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		}
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
// �G�̈ړ��Ǘ��@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void MoveEnemy(void)
{
	PLAYER *pPlayer;
	BROCK *pBrock;

	pPlayer = GetPlayer();
	pBrock = GetBrock();

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G�����݂��Ă���Ƃ�

			if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
			{
				g_aEnemy[nCntEnemy].PlayerMove = MOVE_SPEED_RIGTH;
			}
			else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
			{
				g_aEnemy[nCntEnemy].PlayerMove = MOVE_SPEED_LEFT;
			}

			g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].PlayerMove.x;
		}
	}
}


//=====================================================================================================================================================================//
// �G���e�̓���������                                                                                                                                                   //
//=====================================================================================================================================================================//
bool HitEnemy(int nIdx, int nDamage)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	// �G�̗̑͌���
	g_aEnemy[nIdx].nLife -= nDamage;

	if (g_aEnemy[nIdx].nLife <= 0)
	{// �̗͂��[���̂Ƃ�
	 // �G�̏���
		g_aEnemy[nIdx].state = ENEMYSTATE_FALSE;
		return true;
	}
	else
	{// �[������Ȃ��Ƃ�
	 // �_���[�W��
	 //PlaySound(SOUND_LABEL_SE_HIT);

	 // �_���[�W���
		g_aEnemy[nIdx].state = ENEMYSTATE_DAMAGE;

		// ��Ԃ̃J�E���^�[
		g_aEnemy[nIdx].nCounterState = ALPHA_INTERVAL;

		// ���_�o�b�t�@�̃��b�N
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		// �G�̏�񕪐i�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �F�̍X�V
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_DAMAGEALPHA);

		// ���_�o�b�t�@�̃A�����b�N
		g_pVtxBuffEnemy->Unlock();
		return false;
	}
}

//=====================================================================================================================================================================//
// �G�̏��@�@�@�@�@                                                                                                                                                   //
//=====================================================================================================================================================================//
ENEMY *GetEnemy(void)
{
	return &g_aEnemy[0];
}
