//##################################################################################################################################################################//
//
// �e���� [bullet.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bullet.h"
#include "player.h"
#include "input.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"
#include "sound.h"
#include "objct.h"
#include "effect.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define BULLET_SIZE_XY					(20)						// �e�̃T�C�Y
#define COLOR_RED						(255)						// �ԐF
#define COLOR_BULUE						(255)						// �F
#define COLOR_GREEN						(255)						// �ΐF
#define COLOR_ALPHA						(255)						// �A���t�@�l
#define RHW								(10/10)						// rhw�̐��l1.0�Œ�
#define HALF_MATH						(2)							// ����
#define PVTEX_MAX						(4)							// pVtx
#define PLAYER_GREEN_BULLET				(pEnemy->bUse == true && g_aBullet[nCntBullet].state == BULLET_TYPE_PLAYER_GREEN && pEnemy->Type != ENEMY_TYPE_FIRE && pEnemy->state == ENEMYSTATE_NORMAL)
#define PLAYER_RED_BULLET				(pEnemy->bUse == true && g_aBullet[nCntBullet].state == BULLET_TYPE_PLAYER_RED && pEnemy->Type != ENEMY_TYPE_TANK && pEnemy->state == ENEMYSTATE_NORMAL)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureBullet[BULLET_TYPE_MAX] = {};	// �e�N�X�`���̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			// ���_�o�b�t�@�̏��
BULLET g_aBullet[MAX_BULLET];								// �e�̏��
D3DXVECTOR3 pos;											// �ʒu
D3DXCOLOR color;											// �F
int g_nType;												// �e�̃^�C�v
float g_fAngleBullet;										// �Ίp���̊p�x

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitBullet(void)
{
	VERTEX_2D *pVtx;			// ���_�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �O���[�o���ϐ��̏�����
	g_nType = BULLET_TYPE_PLAYER_GREEN;
	g_fAngleBullet = 0.0f;							
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			
	color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\refe.png", &g_apTextureBullet[BULLET_TYPE_PLAYER_GREEN]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\warter.png", &g_apTextureBullet[BULLET_TYPE_PLAYER_RED]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemybullet01.png", &g_apTextureBullet[BULLET_TYPE_ENEMY]);

	// �e�̏������ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
		g_aBullet[nCntBullet].state = BULLET_TYPE_PLAYER_GREEN;		
		g_aBullet[nCntBullet].nLife = 100;							
		g_aBullet[nCntBullet].bUse = false;							
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}
	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// �e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);

		// rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = RHW;
		pVtx[1].rhw = RHW;
		pVtx[2].rhw = RHW;
		pVtx[3].rhw = RHW;

		// ���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		// �v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}
	
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	for (int nCuntBullet = 0; nCuntBullet < BULLET_TYPE_MAX; nCuntBullet++)
	{// �e�N�X�`���̊J��
		if (g_apTextureBullet[nCuntBullet] != NULL)
		{
			g_apTextureBullet[nCuntBullet]->Release();
			g_apTextureBullet[nCuntBullet] = NULL;
		}
	}
	StopSound(SOUND_LABEL_SE_SHOT_E);	//BGM
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateBullet(void)
{
	// �\���̂̃|�C���^
	VERTEX_2D *pVtx;
	BULLET *pBullet;
	ENEMY *pEnemy;
	PLAYER *pPlayer;
	OBJCT *pObj;
	ENEMY_FLAWAR *pFlawar;

	// �\���̂̏��擾
	pBullet = &g_aBullet[0];
	pObj = GetObjct();
	pPlayer = GetPlayer();

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true )
		{
			// �ʒu�̍X�V
			g_aBullet[nCntBullet].pos.y += g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x += g_aBullet[nCntBullet].move.x;

			// ���C�t�̌���
			g_aBullet[nCntBullet].nLife -= 2;

			// ���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);

			// �G�̏������Ȃ���
			pEnemy = GetEnemy();
			pFlawar = GetFlawar();

			// �G�Ƃ̓����蔻��
			for (int nCntEnemy = 0; nCntEnemy < 256; nCntEnemy++, pEnemy++, pFlawar++)
			{// �G�����݂��Ă���E�v���C���[�̒e�ł���ꍇ
			 // �v���C���[�̏���
				if (PLAYER_GREEN_BULLET || PLAYER_RED_BULLET)
				{
					// �G�ƃv���C���[�̒e�̓����蔻��
					if (pEnemy->pos.y + ENEMY_SIZE / 3 > g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / 3 &&
						pEnemy->pos.x + ENEMY_SIZE / 3 > g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / 3 &&
						pEnemy->pos.y - ENEMY_SIZE / 3 < g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / 3 &&
						pEnemy->pos.x - ENEMY_SIZE / 3 < g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / 3 )
					{
						// �e�̏���
						g_aBullet[nCntBullet].bUse = false;

						// �_���[�W
						int nDamage = 1;

						// �G����e����
						HitEnemy(nCntEnemy, nDamage);
					}
				}
			}
			//�v���C���[�E��ƓG�̒e�̓����蔻��
			if (g_aBullet[nCntBullet].state == BULLET_TYPE_ENEMY)
			{
				// �v���C���[�̓����蔻��
				if (pPlayer->Playerpos.y + 40 > g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / 3 &&
					pPlayer->Playerpos.x + 20 > g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / 3 &&
					pPlayer->Playerpos.y - 10 < g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / 3 &&
					pPlayer->Playerpos.x - 20 < g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / 3)
				{
					// �e�̏���
					g_aBullet[nCntBullet].bUse = false;

					// �_���[�W��
					int nDamage = 1;

					// �v���C���[����e�����ꍇ
					HitPlayer(nDamage);
				}
				// ��̓����蔻��
				if (pObj->objpos.y + 60 > g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / 3 &&
					pObj->objpos.x + 60 > g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / 3 &&
					pObj->objpos.y - 60 < g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / 3 &&
					pObj->objpos.x - 60 < g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / 3)
				{
					// �e�̏���
					g_aBullet[nCntBullet].bUse = false;

					// �_���[�W��
					float nDamage = 3.2f;

					// �邪��e�����ꍇ
					HitObjct(nDamage);

					// �_���[�W��
					PlaySound(SOUND_LABEL_SE_HIT);
				}
			} 
			// �����`�F�b�N
			if (g_aBullet[nCntBullet].nLife == 0)
			{
				// 0�ɂȂ�����t�H���X�ɕς���
				g_aBullet[nCntBullet].bUse = false;
			}
			// ��ʊO�`�F�b�N�E�e���������̉�ʊO�ɏo���ꍇ
			if (g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH < 0 || g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH > SCREEN_HEIGHT ||
				g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH < 0 || g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH > SCREEN_WIDTH)
			{
				// �t�H���X����
				g_aBullet[nCntBullet].bUse = false;
			}
		}
		// 4���_�������
		pVtx += PVTEX_MAX;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawBullet(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// �v���C���[�̎擾
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBullet[g_aBullet[nCntBullet].state]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, HALF_MATH);
		}
	}
}

//=====================================================================================================================================================================//
// �e�̐ݒ菈��
//=====================================================================================================================================================================//
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLET_TYPE Btype)
{
	//�|�C���^
	BULLET *pBullet;
	PLAYER *pPlayer;
	OBJCT *pObj;
	ENEMY *pEnemy;
	VERTEX_2D *pVtx;
	//���擾
	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	pObj = GetObjct();
	pBullet = &g_aBullet[0];
	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
	//�e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�g�p����Ă��Ȃ��e
			//�v���C���[�̃^�C�v���
			g_nType = pPlayer->player;

			// �v���C���[1�̒e
			if (g_nType == BULLET_TYPE_PLAYER_GREEN)
			{
					// �e�̎�ނ̏��
					g_aBullet[nCntBullet].state = BULLET_TYPE_PLAYER_GREEN;

					// �ʒu�̐ݒ�
					g_aBullet[nCntBullet].pos.x = pos.x;
					g_aBullet[nCntBullet].pos.y = pos.y;

					// �ړ��̐ݒ�
					g_aBullet[nCntBullet].move.y = move.y;
					g_aBullet[nCntBullet].move.x = move.x;

					// �����̐ݒ�
					g_aBullet[nCntBullet].nLife = nLife;

					// ���_���W
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);
			}
			else if (g_nType == BULLET_TYPE_PLAYER_RED)
			{// �v���C���[2�̒e
				// �e�̎�ނ̏��
				g_aBullet[nCntBullet].state = BULLET_TYPE_PLAYER_RED;

				// �ʒu�̐ݒ�
				g_aBullet[nCntBullet].pos.x = pos.x;
				g_aBullet[nCntBullet].pos.y = pos.y;

				// �ړ��̐ݒ�
				g_aBullet[nCntBullet].move.y = move.y;
				g_aBullet[nCntBullet].move.x = move.x;

				// �����̐ݒ�
				g_aBullet[nCntBullet].nLife = nLife;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / HALF_MATH, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / HALF_MATH, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / HALF_MATH, 0.0f);

			}
			if (Btype == BULLET_TYPE_ENEMY)
			{// �G�̒e
				// �e�̎�ނ̏��
				g_aBullet[nCntBullet].state = BULLET_TYPE_ENEMY;
				PlaySound(SOUND_LABEL_SE_SHOT_E);

				// �ʒu�̐ݒ�
				g_aBullet[nCntBullet].pos.x = pos.x;
				g_aBullet[nCntBullet].pos.y = pos.y;

				// �G�̒e�Ə�̊p�x
				g_fAngleBullet = atan2f(g_aBullet[nCntBullet].pos.x - (float)pObj->objpos.x, g_aBullet[nCntBullet].pos.y - (float)pObj->objpos.y);

				// �ړ��̐ݒ�
				g_aBullet[nCntBullet].move.y = cosf(D3DX_PI-g_fAngleBullet)*HALF_MATH;
				g_aBullet[nCntBullet].move.x = sinf(D3DX_PI+g_fAngleBullet)*HALF_MATH;

				// �����̐ݒ�
				g_aBullet[nCntBullet].nLife = nLife;

				// ���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / 2, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_XY / 2, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / 2, g_aBullet[nCntBullet].pos.y + BULLET_SIZE_XY / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_XY / 2, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_XY / 2, 0.0f);
			}
			// �e�𔭎�
			g_aBullet[nCntBullet].bUse = true;
			break;
		}
		pVtx += PVTEX_MAX;	// ���_����4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}
