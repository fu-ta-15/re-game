//##################################################################################################################################################################//
//
// �G�̏��� [enemy.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bullet.h"
#include "enemy.h"
#include "input.h"
#include "score.h"
#include "objct.h"
#include "sound.h"
#include "explosion.h"
#include "enemyobj.h"
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
#define FLAWAR_NUMBER				(4)																											// �Ԃ̓G�̐�
#define FLAWAR_LIFE					(4)																											// �Ԃ̗̑�
#define FLAWAR_P					(1100)																										// �Ԃ̓G�̈ʒu
#define FLAWAR_O					(150)																										// �Ԃ̓G�̈ʒu
#define FLAWAR_S					(810)																										// �Ԃ̓G�̈ʒu
#define FLAWAR_ZERO					(atan2f(g_EnemySetPos[nIdx].x - FLAWAR_P, g_EnemySetPos[nIdx].y - FLAWAR_O))								// �ԃi���o�[0
#define FLAWAR_ONE					(atan2f(g_EnemySetPos[nIdx].x - FLAWAR_O, g_EnemySetPos[nIdx].y - FLAWAR_O))								// �ԃi���o�[1
#define FLAWAR_TWO					(atan2f(g_EnemySetPos[nIdx].x - FLAWAR_O, g_EnemySetPos[nIdx].y - FLAWAR_S))								// �ԃi���o�[2
#define FLAWAR_THREE				(atan2f(g_EnemySetPos[nIdx].x - FLAWAR_P, g_EnemySetPos[nIdx].y - FLAWAR_S))								// �ԃi���o�[3
#define GUS_POS_RIGHT				(D3DXVECTOR3(SCREEN_WIDTH + 10, (SCREEN_HEIGHT - 600) + (float)g_Gus[nIdx].AddPosRand, 0.0f))				// �����G�E��
#define GUS_POS_LEFT				(D3DXVECTOR3(0 - 10, (SCREEN_HEIGHT - 600) + (float)g_Gus[nIdx].AddPosRand, 0.0f))							// �����G����
#define ENEMY_GUS_LIFE				(1)																											// �����G�̗̑�
#define GUS_DAMAGE					(1.0f)																										// �����G�̍U����
#define FIRE_APPER					(7)																											// �΂̏o��
#define TANK_APPER					(7)																											// ��Ԃ̏o��
#define GUS_FLAWAR					(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f))																			// �Ԑ�p
#define GUS_FIRE					(D3DXCOLOR(0.7f, 0.2f, 0.3f, 1.0f))																			// �ΐ�p
#define GUS_TANK					(D3DXCOLOR(0.0f, 0.6f, 0.0f, 1.0f))																			// ��Ԑ�p
#define GUS_NORMAL					(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))																			// �m�[�}��
#define CASTLE_ANGLE				(atan2f(g_EnemySetPos[nIdx].x - (float)pObj->objpos.x, g_EnemySetPos[nIdx].y - (float)pObj->objpos.y))		// ��Ƃ̊p�x
#define CASTLE_POS					(60)																										// ��̒��S����̋���
#define FLAWAR_BULLET				(300)																										// �Ԃ̒e���ˎ���
#define FRAME_MATH					(60)																										// 


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEnemy[ENEMY_TYPE_MAX] = {};	//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;				//���_�o�b�t�@�ւ̃|�C���^
ENEMY g_aEnemy[MAX_ENEMY];									//�G�̎��
D3DXVECTOR3 g_EnemySetPos[MAX_ENEMY];						//�G�̈ʒu
ENEMY_GUS g_Gus[MAX_ENEMY];									//���̓G
ENEMY_FIRE g_Fire;											//�΂̓G
ENEMY_TANK g_Tank;											//��Ԃ̓G
ENEMY_FLAWAR g_Flawar[FLAWAR_NUMBER];						//�Ԃ̓G
int g_anApperCounter;										//�����_���J�E���^�[
int g_nCounterEnemy;										//�G�̔ԍ�
float g_fAngleEnemy;										//�G�̑Ίp���̊p�x
int g_fEnemyAlpha[MAX_ENEMY];								//�G�̓����x
int g_anFlame[MAX_ENEMY];									//�Ԃ̓G

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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy0.png", &g_apTextureEnemy[ENEMY_TYPE_GUS]);			//���̓G
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\0202.png", &g_apTextureEnemy[ENEMY_TYPE_FIRE]);			//�΂̓G
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy0-1-1.png", &g_apTextureEnemy[ENEMY_TYPE_TANK]);	//��Ԃ̓G
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\flowers.png", &g_apTextureEnemy[ENEMY_TYPE_FLAWAR]);		//�Ԃ̓G

	//�G�̏��̏�����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_anFlame[nCntEnemy] = 0;
		// �G�̍\����
		g_aEnemy[nCntEnemy].pos = VECTORO_ZERO;
		g_aEnemy[nCntEnemy].move = MOVE_ZERO;
		g_aEnemy[nCntEnemy].Type = {};
		g_aEnemy[nCntEnemy].EneSkill = false;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCountBullet = 0;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		// �z��̕ϐ�
		g_EnemySetPos[nCntEnemy] = VECTORO_ZERO;
		g_fEnemyAlpha[nCntEnemy] = COLOR_ALPHA;
		// �����G
		g_Gus[nCntEnemy].AddPosRand = 0;								// �����v���X�����ʒu
		g_Gus[nCntEnemy].ObjctNunber = 0;								// �I�u�W�F�N�g�̃i���o�[
		g_Gus[nCntEnemy].RandApper = 0;									// �o���J�E���^�[
		g_Gus[nCntEnemy].StandardPos = 0;								// ��ʒu
		g_Gus[nCntEnemy].GusType = NULL;								// �����G�̃^�C�v
		g_Gus[nCntEnemy].GusCol = COLOR_ZERO;							// �����G�̐F
		// �Ԃ̓G
		g_Flawar[nCntEnemy].LifeDeath = false;
		g_Flawar[nCntEnemy].RandApper = 0;
		g_Flawar[nCntEnemy].BulletTime = MAX_COLOR;
		g_Flawar[nCntEnemy].FlawarNumber = ENEMY_TYPE_FLAWAR;
	}
	// �z��Ȃ��̕ϐ��̏�����
	g_fAngleEnemy = 0.0f;
	g_nCounterEnemy = 0;
	g_anApperCounter = 0;
	// �΂̓G
	g_Fire.AddPosRand = 0;												// �����v���X�����ʒu
	g_Fire.RandApper = 0;												// �o���J�E���^�[
	g_Fire.StandardPos = 0;												// ��ʒu
	// ��Ԃ̓G
	g_Tank.AddPosRand = 0;												// �����v���X�����ʒu
	g_Tank.RandApper = 0;												// �o���J�E���^�[
	g_Tank.StandardPos = 0;												// ��ʒu

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
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);

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
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);

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
	ENEMY *pEnemy;
	VERTEX_2D *pVtx;
	OBJCT *pObj;

	//�I�u�W�F�N�g�̏��擾
	pObj = GetObjct();

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G�����݂��Ă���Ƃ�
			//�G�̐擪�A�h���X
			pEnemy = &g_aEnemy[0];

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);

			/*�G�̍X�V*/
			if (g_aEnemy[nCntEnemy].Type == ENEMY_TYPE_GUS)
			{//�����G
				EnemyGus(nCntEnemy);
			}
			if (g_aEnemy[nCntEnemy].Type == ENEMY_TYPE_FIRE)
			{//�΂̓G
				EnemyFire(nCntEnemy);
			}
			if (g_aEnemy[nCntEnemy].Type == ENEMY_TYPE_TANK)
			{//��Ԃ̓G
				EnemyTank(nCntEnemy);
			}
			if (g_aEnemy[nCntEnemy].Type == ENEMY_TYPE_FLAWAR)
			{//�Ԃ̓G
				EnemyFlawar(nCntEnemy);
			}
			//�G�̏�ԊǗ�
			StateEnemy(nCntEnemy);
		}
		//�g�p���Ă��Ȃ��G�̔ԍ�
		g_nCounterEnemy = nCntEnemy;

		//�v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}
	//�G�̔z�u
	RandSetEnemy(g_nCounterEnemy);
	SetEnemyGus(g_nCounterEnemy);
	//�G�o���^�C��
	g_anApperCounter += 1;
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

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++,pEnemy++)
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
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move,ENEMY_TYPE Type,int nLife)
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
			g_aEnemy[nCntEnemy].move = move;			// �ړ�
			if (g_aEnemy[nCntEnemy].Type == ENEMY_TYPE_FLAWAR)
			{// �Ԃ̍ŏ��̏��
				g_aEnemy[nCntEnemy].state = ENEMYSTATE_FALSE;
			}

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE , 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE , g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE , 0.0f);

			if (g_aEnemy[nCntEnemy].Type != ENEMY_TYPE_GUS)
			{
				// �e���_�̃J���[���
				pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			}

			//�G����ʓ��ɑ��݂��Ă���
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
void RandSetEnemy(int nIdx)
{
	//-----------------------//
	/*		  �΂̓G		 */
	//-----------------------//
	g_Fire.AddPosRand = rand() % 360 + 300;

	if (g_Fire.RandApper == FIRE_APPER)
	{
		SetEnemy(D3DXVECTOR3(-10, SCREEN_HEIGHT - (float)g_Fire.AddPosRand, 0), D3DXVECTOR3(2.0f, 0.0f, 0.0f), ENEMY_TYPE_FIRE, 10);
		g_Fire.RandApper = 0;
	}

	//-----------------------//
	/*		  �@�B�̓G�@	 */
	//-----------------------//
	g_Tank.AddPosRand = rand() % 360 + 300;

	if (g_Tank.RandApper == TANK_APPER)
	{
		SetEnemy(D3DXVECTOR3(SCREEN_WIDTH + 10, SCREEN_HEIGHT - (float)g_Tank.AddPosRand, 0), D3DXVECTOR3(2.0f, 0.0f, 0.0f), ENEMY_TYPE_TANK, 10);
		g_Tank.RandApper = 0;
	}

	//-----------------------//
	/*		  �Ԃ̓G�@�@�@�@ */
	//-----------------------//
	// �l�̌Œ� //
	if (g_anApperCounter == 1)
	{
		SetEnemy(D3DXVECTOR3(FLAWAR_P, FLAWAR_O, 0),MOVE_ZERO, ENEMY_TYPE_FLAWAR, FLAWAR_LIFE);
	}
	if (g_anApperCounter == 2)
	{
		SetEnemy(D3DXVECTOR3(FLAWAR_O, FLAWAR_O, 0), MOVE_ZERO, ENEMY_TYPE_FLAWAR, FLAWAR_LIFE);
	}
	if (g_anApperCounter == 3)
	{
		SetEnemy(D3DXVECTOR3(FLAWAR_O, FLAWAR_S, 0), MOVE_ZERO, ENEMY_TYPE_FLAWAR, FLAWAR_LIFE);
	}
	if (g_anApperCounter == 4)
	{
		SetEnemy(D3DXVECTOR3(FLAWAR_P, FLAWAR_S, 0), MOVE_ZERO, ENEMY_TYPE_FLAWAR, FLAWAR_LIFE);
	}
}

//=====================================================================================================================================================================//
// �����G�̃����_���z�u�@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void SetEnemyGus(int nIdx)
{
	// �e�\���̂̃|�C���^
	OBJCT *pObj;
	ENEOBJCT *pEneObj;
	// ���擾
	pEneObj = GetEnObjct();
	pObj = GetObjct();

	//-----------------------//
	/*		  �����G		 */
	//-----------------------//
	// �o���J�E���^�[�ϐ�
	g_Gus[nIdx].AddPosRand = rand() % 250 + 50;
	g_Gus[nIdx].ObjctNunber = rand() % 5;

		pEneObj += g_Gus[nIdx].ObjctNunber;	//�I�u�W�F�N�g�i���o�[
		if ((g_anApperCounter % g_Gus[nIdx].AddPosRand) == 0 && pEneObj->EneOState == ENEMY_OBJ_NORMAL)
		{// �I�u�W�F�N�g
			g_EnemySetPos[nIdx] = pEneObj->objpos;																													// ���W
			g_fAngleEnemy = CASTLE_ANGLE;																															// ��Ƃ̊p�x
			SetEnemy(g_EnemySetPos[nIdx], D3DXVECTOR3(sinf(D3DX_PI + g_fAngleEnemy) * 2, cosf(D3DX_PI - g_fAngleEnemy) * 2, 0.0f), ENEMY_TYPE_GUS, ENEMY_GUS_LIFE);	// �G�̔z�u
		}
	//�����_���X�V
	g_Gus[nIdx].AddPosRand = rand() % 250 + 50;
	g_Gus[nIdx].RandApper = rand() % 300 + 100;
	if ((g_anApperCounter % g_Gus[nIdx].RandApper) == 0)
	{// �E����̓G
	 // ���W
		g_EnemySetPos[nIdx] = GUS_POS_RIGHT;

		// ��Ƃ̊p�x
		g_fAngleEnemy = atan2f(g_EnemySetPos[nIdx].x - (float)pObj->objpos.x, g_EnemySetPos[nIdx].y - (float)pObj->objpos.y);

		// �G�̔z�u
		SetEnemy(g_EnemySetPos[nIdx], D3DXVECTOR3(sinf(D3DX_PI + g_fAngleEnemy) * 2, cosf(D3DX_PI - g_fAngleEnemy) * 2, 0.0f), ENEMY_TYPE_GUS, ENEMY_GUS_LIFE);
	}
	// �o���J�E���^�[�ϐ�
	g_Gus[nIdx].AddPosRand = rand() % 250 + 50;
	g_Gus[nIdx].RandApper = rand() % 300 + 100;
	if ((g_anApperCounter % g_Gus[nIdx].RandApper) == 0)
	{// ������̓G
	 // ���W
		g_EnemySetPos[nIdx] = GUS_POS_LEFT;

		// ��Ƃ̊p�x
		g_fAngleEnemy = atan2f(g_EnemySetPos[nIdx].x - (float)pObj->objpos.x, g_EnemySetPos[nIdx].y - (float)pObj->objpos.y);

		// �G�̔z�u
		SetEnemy(g_EnemySetPos[nIdx], D3DXVECTOR3(sinf(D3DX_PI + g_fAngleEnemy) * 2, cosf(D3DX_PI - g_fAngleEnemy) * 2, 0.0f), ENEMY_TYPE_GUS, ENEMY_GUS_LIFE);
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
	if (g_aEnemy[nIdx].state == ENEMYSTATE_FALSE && g_aEnemy[nIdx].Type != ENEMY_TYPE_FLAWAR)
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
			AddScore(nScore);

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
// �����G�@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void EnemyGus(int nIdx)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	// �I�u�W�F�N�g�̏��擾
	OBJCT *pObj;
	pObj = GetObjct();

	g_anFlame[nIdx]++;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	// �ړ�
	g_aEnemy[nIdx].pos.x += g_aEnemy[nIdx].move.x;	// X����
	g_aEnemy[nIdx].pos.y += g_aEnemy[nIdx].move.y;	// Y����
	if ((g_anFlame[nIdx] % FRAME_MATH) == 0)
	{// ��b�Ɉ��
		g_Gus[nIdx].GusType = rand() % 4;		// �����G�̎��
	}
	if (g_Gus[nIdx].GusType == 3 && g_aEnemy[nIdx].Type == ENEMY_TYPE_GUS)
	{
		// ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);
		//�m�[�}���F
		g_Gus[nIdx].GusCol = GUS_NORMAL;
	}
	else if (g_Gus[nIdx].GusType == 0 && g_aEnemy[nIdx].Type == ENEMY_TYPE_GUS)
	{
		// ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);
		//�ԃ^�C�v
		g_Gus[nIdx].GusCol = GUS_FLAWAR;
	}
	else if (g_Gus[nIdx].GusType == 1 && g_aEnemy[nIdx].Type == ENEMY_TYPE_GUS)
	{
		// ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);
		//�΃^�C�v
		g_Gus[nIdx].GusCol = GUS_FIRE;
	}
	else if (g_Gus[nIdx].GusType == 2 && g_aEnemy[nIdx].Type == ENEMY_TYPE_GUS)
	{
		// ���̓G�̒��_�ԍ��܂Ői�߂�
		pVtx += (PVTEX_MAX * nIdx);
		//��ԃ^�C�v
		g_Gus[nIdx].GusCol = GUS_TANK;
	}
	// �e���_�̃J���[���
	pVtx[0].col = g_Gus[nIdx].GusCol;
	pVtx[1].col = g_Gus[nIdx].GusCol;
	pVtx[2].col = g_Gus[nIdx].GusCol;
	pVtx[3].col = g_Gus[nIdx].GusCol;
	// ��Ƃ̓����蔻��
	if (g_aEnemy[nIdx].pos.x >= pObj->objpos.x - CASTLE_POS &&
		g_aEnemy[nIdx].pos.y >= pObj->objpos.y - CASTLE_POS &&
		g_aEnemy[nIdx].pos.x <= pObj->objpos.x + CASTLE_POS &&
		g_aEnemy[nIdx].pos.y <= pObj->objpos.y + CASTLE_POS)
	{
		// �_���[�W��
		float nDamage = GUS_DAMAGE;

		// �邪��e�����ꍇ
		HitObjct(nDamage);

		// �_���[�W��
		PlaySound(SOUND_LABEL_SE_HIT);

		if (g_Gus[nIdx].GusType == 1)
		{//�΂̏o���J�E���^�[
			g_Fire.RandApper += 1;
		}
		if (g_Gus[nIdx].GusType == 2)
		{//��Ԃ̏o���J�E���^�[
			g_Tank.RandApper += 1;
		}
		// �G���g���Ă��Ȃ���Ԃɂ���
		g_aEnemy[nIdx].bUse = false;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
}

//=====================================================================================================================================================================//
// �΂̓G�@�@                                                                                                                                                   //
//=====================================================================================================================================================================//
void EnemyFire(int nIdx)
{
	g_aEnemy[nIdx].pos.x += g_aEnemy[nIdx].move.x;
	int nBullet = rand() % FLAWAR_BULLET + FLAWAR_BULLET;

	if (g_aEnemy[nIdx].pos.x >= 100)
	{
		g_aEnemy[nIdx].move = MOVE_ZERO;
	}
	// �G�̈ʒu���
	D3DXVECTOR3 pos = g_aEnemy[nIdx].pos;
	// �G�̒e�̔��˂̃^�C�~���O
	g_aEnemy[nIdx].nCountBullet += 1;

	if (g_aEnemy[nIdx].state == ENEMYSTATE_NORMAL && (g_aEnemy[nIdx].nCountBullet % nBullet) == 0)
	{// �΂̓G
		D3DXVECTOR3 move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);	//�e�̈ړ�
		SetBullet(pos, move, 600, BULLET_TYPE_ENEMY);		//�e�̔���
	}

}

//=====================================================================================================================================================================//
// ��Ԃ̓G�@�@                                                                                                                                                   //
//=====================================================================================================================================================================//
void EnemyTank(int nIdx)
{
	// �ړ�
	g_aEnemy[nIdx].pos.x -= g_aEnemy[nIdx].move.x;
	int nBullet = rand() % FLAWAR_BULLET + FLAWAR_BULLET;


	if (g_aEnemy[nIdx].pos.x <= SCREEN_WIDTH - 60)
	{// �X�g�b�v
		g_aEnemy[nIdx].move = MOVE_ZERO;
	}
	// �G�̈ʒu
	D3DXVECTOR3 pos = g_aEnemy[nIdx].pos;
	// �G�̒e�̔��˂̃^�C�~���O
	g_aEnemy[nIdx].nCountBullet += 1;

	if (g_aEnemy[nIdx].state == ENEMYSTATE_NORMAL && (g_aEnemy[nIdx].nCountBullet % nBullet) == 0)
	{// �e�̔���
		D3DXVECTOR3 move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);	//�e�̈ړ�
		SetBullet(pos, move, 600, BULLET_TYPE_ENEMY);		//�e�̔���
	}
}

//=====================================================================================================================================================================//
// �Ԃ̓G�@�@                                                                                                                                                   
//=====================================================================================================================================================================//
void EnemyFlawar(int nIdx)
{
	// �|�C���^
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	// �G�̈ʒu���
	D3DXVECTOR3 pos = g_aEnemy[nIdx].pos;

	if (g_aEnemy[nIdx].state == ENEMYSTATE_NORMAL)
	{// �퓬�Ԑ�

		 // �G�̒e�̔��˂̃^�C�~���O
		g_aEnemy[nIdx].nCountBullet += 1;
		g_Flawar[nIdx].BulletTime = rand() % FLAWAR_BULLET + FLAWAR_BULLET;

		// �v���X4�i�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_ONE, TEXPOS_ZERO);

		// �F�̍X�V
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// �e�̔���
		if ((g_aEnemy[nIdx].nCountBullet % g_Flawar[nIdx].BulletTime) == 0)
		{// ����̃t���[���ɗ�����
			D3DXVECTOR3 move = D3DXVECTOR3(5.0f, 0.0f, 0.0f);			// �e�̈ړ�
			SetBullet(pos, move, 2000, BULLET_TYPE_ENEMY);		// �e�̔���
		}
	}
	else if (g_aEnemy[nIdx].state == ENEMYSTATE_FALSE)
	{// �퓬�s�\
		// �o���J�E���^�[��i�߂�
		g_Flawar[nIdx].RandApper++;
		if ((g_Flawar[nIdx].RandApper % 600) == 0)
		{// �퓬���[�h
			g_aEnemy[nIdx].state = ENEMYSTATE_NORMAL;
			g_aEnemy[nIdx].nLife = 4;
		}
		// �v���X4�i�߂�
		pVtx += (PVTEX_MAX * nIdx);

		// �e�N�X�`�����W�̍X�V
		pVtx[0].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ONE);
		pVtx[1].tex = D3DXVECTOR2(TEXPOS_ZERO, TEXPOS_ZERO);
		pVtx[2].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ONE);
		pVtx[3].tex = D3DXVECTOR2(TEXPOS_HALF, TEXPOS_ZERO);
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEnemy->Unlock();
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
		if (g_aEnemy[nIdx].Type == ENEMY_TYPE_FIRE)
		{
			g_Fire.RandApper += 1;

		}
		if (g_aEnemy[nIdx].Type == ENEMY_TYPE_FIRE)
		{
			g_Tank.RandApper += 1;

		}

		g_aEnemy[nIdx].state = ENEMYSTATE_FALSE;
		return true;
	}
	else
	{// �[������Ȃ��Ƃ�
	 // �_���[�W��
		PlaySound(SOUND_LABEL_SE_HIT);

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

//=====================================================================================================================================================================//
// �G�̏��@�@�@�@�@                                                                                                                                                   //
//=====================================================================================================================================================================//
ENEMY_FLAWAR *GetFlawar(void)
{
	return &g_Flawar[0];
}
