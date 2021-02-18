//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "player.h"
#include "objct.h"
#include "input.h"
#include "bullet.h"
#include "enemy.h"
#include "sound.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define PLAYER_ONE			(PLAYER_TYPE_GREEN)					// �v���C���[�P
#define PLAYER_TWO			(PLAYER_TYPE_RED)					// �v���C���[�Q
#define MOVE_SPEED			(5)									// �X�s�[�h
#define LENGTH_PLAYER_X		(40)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_PLAYER_Y		(40)								// ���S����e���_�̋��������߂鐔�l
#define COLOR_RED			(255)								// �ԐF
#define COLOR_BULUE			(255)								// �F
#define COLOR_GREEN			(255)								// �ΐF
#define COLOR_ALPHA			(255)								// �A���t�@�l
#define PLAYER_POS_FS_X		(490)								// pVtx�̂P�ƂQ��X�̐��l
#define PLAYER_POS_TF_X		(570)								// pVtx�̂R�ƂS��X�̐��l
#define PLAYER_POS_SF_Y		(190)								// pVtx�̂Q�ƂS��Y�̐��l
#define PLAYER_POS_FT_Y		(270)								// pVtx�̂P�ƂR��Y�̐��l
#define PLAYER_TYPE_TEX		(2)									// �v���C���[�̎��
#define PVTEX_MAX			(4)									// pVtx
#define CENTER_POS_X		(650)								// ���S���W�iX) 
#define CENTER_POS_Y		(500)								// ���S���W�iY)
#define HALF_MATH			(2)									// ����
#define FRAME_COUNT			(10)								// FRAME�̃J�E���g
#define NORMAL_PLAYER		(240)								// �C���^�[�o��
#define BULLET_LIFE			(100)								// �e�̃��C�t
#define EFFECT_COLORO		(D3DXCOLOR(0.8f, 0.2f, 0.1f, 1.0f))	// �G�t�F�N�g�̐F
#define PLAYER_LIFE			(5)									// �v���C���[�̗̑�
#define RHW					(10/10)								// rhw�̐��l1.0�Œ�
#define G_POS_X				(40)								// ���S����̂��̋���
#define G_POS_Y				(50)								// ���S����̂��̋���
#define WATER_SIZE			(300)								// �����G���A�̈��
#define SCREEN_ALPHA		(100)								// �w�i�̗΂̕���

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;			// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTexturePlayer[PLAYER_TYPE_TEX] = {};	// �e�N�X�`���̏��
D3DXVECTOR3 g_posPlayer;									// �ʒu���
D3DXVECTOR3 g_rotPlayer;									// ��]���
D3DXVECTOR3 g_movePlayer;									// ���������
PLAYER g_Player;											// �v���C���[���
BULLET_TYPE g_Btype;										// �e�̏��
int g_nConterAnim;											// �A�j���[�V�����̃J�E���^�[
int g_nPatternAnim;											// �A�j���[�V����
int g_nAlpha;												// ���l
float g_fLengthPlayer;										// �Ίp���̒���
float g_fAnglePlayer;										// �Ίp���̊p�x
float g_fTexY;												// �e�N�X�`��y���W

//=====================================================================================================================================================================//
// �v���C���[�̏���������
//=====================================================================================================================================================================//
HRESULT InitPlayer(MODE mode)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;			// ���_�|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �O���[�o���ϐ��̏�����
	g_nConterAnim = 0;
	g_nPatternAnim = 0;
	g_fLengthPlayer = 0.0f;
	g_fAnglePlayer = 0.0f;
	g_fTexY = 0.0f;
	g_nAlpha = COLOR_ALPHA;

	// �v���C���[���̏�����
	g_Player.nCounterState = 0;
	g_Player.nCounterDisp = 0;
	g_Player.nLife = PLAYER_LIFE;
	g_Player.player = PLAYER_ONE;
	g_Player.Playerpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.PlayerState = PLAYERSTATE_NORMAL;
	g_Player.bSkills = false;
	g_Player.g_mode = mode;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2Dchara2.png", &g_pTexturePlayer[PLAYER_ONE]);	// �v���C���[�P
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\2Dchara1.png", &g_pTexturePlayer[PLAYER_TWO]);	// �v���C���[�Q

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �Ίp���̒���
	g_fLengthPlayer = sqrtf(LENGTH_PLAYER_X * LENGTH_PLAYER_X + LENGTH_PLAYER_Y * LENGTH_PLAYER_Y);

	// �Ίp���̊p�x
	g_fAnglePlayer = atan2f(LENGTH_PLAYER_X, LENGTH_PLAYER_Y);

	// �����̏ꏊ�ɖ߂�
	g_posPlayer = D3DXVECTOR3(CENTER_POS_X, CENTER_POS_Y, 0.0f);

	// �e���_�̍��W
	pVtx[0].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	// ���S���W
	g_posPlayer = D3DXVECTOR3(CENTER_POS_X, CENTER_POS_Y, 0.0f);

	// ��]�p�x
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = RHW;
	pVtx[1].rhw = RHW;
	pVtx[2].rhw = RHW;
	pVtx[3].rhw = RHW;

	// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	// �e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitPlayer(void)
{
	// �e�N�X�`���̊J��
	for (int nCuntPlayer = 0; nCuntPlayer < PLAYER_TYPE_TEX; nCuntPlayer++)
	{
		if (g_pTexturePlayer[g_Player.player] != NULL)
		{
			g_pTexturePlayer[g_Player.player]->Release();
			g_pTexturePlayer[g_Player.player] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	StopSound(SOUND_LABEL_SE_SHOT);	//BGM

}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdatePlayer(void)
{
	// �|�C���^
	VERTEX_2D *pVtx;	// ���_�̃|�C���^ 
	PLAYER *pPlayer;	// �v���C���[�̃|�C���^
	ENEMY *pEnemy;		// �G�̃|�C���^

	// SETBULLET�p�̕ϐ�
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 move;	// �ړ�
	int nLife;			// ����

	// ���擾
	pEnemy = GetEnemy();// �G
	pPlayer = &g_Player;// �v���C���[

	// �o�b�t�@�̃��b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
//----------------------//
//	�v���C���[�̈ړ�	//
//----------------------//
	if (GetKeyboardPresse(DIK_D) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// �E
		g_movePlayer.x += sinf(g_fAnglePlayer) * MOVE_SPEED;				// X����
		g_movePlayer.z = 0.0f;												// �p�x
	// �΂߈ړ�
		if (GetKeyboardPresse(DIK_W) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
		{// �E��
			g_movePlayer.y += cosf(D3DX_PI + g_fAnglePlayer) * MOVE_SPEED;	// Y����
		}
		else if (GetKeyboardPresse(DIK_S) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
		{// �E��
			g_movePlayer.y -= cosf(D3DX_PI + g_fAnglePlayer) * MOVE_SPEED;	// Y����
		}
	}
	else if (GetKeyboardPresse(DIK_A) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ��
		g_movePlayer.x -= sinf(g_fAnglePlayer) * MOVE_SPEED;				// X����
		g_movePlayer.z = 0.0f;												// �p�x
	// �΂߈ړ� 
		if (GetKeyboardPresse(DIK_W) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
		{// ����
			g_movePlayer.y += cosf(D3DX_PI + g_fAnglePlayer) * MOVE_SPEED;	// Y����
		}
		else if (GetKeyboardPresse(DIK_S) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
		{// ����
			g_movePlayer.y -= cosf(D3DX_PI + g_fAnglePlayer) * MOVE_SPEED;	// Y����
		}
	}
	else if (GetKeyboardPresse(DIK_W) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ��
			g_movePlayer.y -= cosf(g_fAnglePlayer) * MOVE_SPEED;			// Y����
			g_movePlayer.z = 0.0f;											// �p�x
	}
	else if (GetKeyboardPresse(DIK_S) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ��
			g_movePlayer.y += cosf(g_fAnglePlayer) * MOVE_SPEED;			// Y����
			g_movePlayer.z = 0.0f;											 // �p�x
	}
//----------------------//
//		 �e�̔���		//
//----------------------//
	if (GetKeyboardTrigger(DIK_UP) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ��ɔ���
	 // �e�̏��
		pos = g_posPlayer;								// �v���C���[�̈ʒu			
		move.x = 0;										// X�����̈ړ���
		move.y = -(cosf(g_fAnglePlayer) + MOVE_SPEED);	// Y�����̈ړ���
		nLife = BULLET_LIFE;							// ����

		// �e�̐ݒ�
		SetBullet(pos, move, nLife, g_Btype);			
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ���ɔ���
	 // �e�̏��
		pos = g_posPlayer;								// �v���C���[�̈ʒu
		move.x = 0;										// X�����̈ړ���
		move.y = (cosf(g_fAnglePlayer) + MOVE_SPEED);	// Y�����̈ړ���
		nLife = BULLET_LIFE;							// ����

		// �e�̐ݒ�
		SetBullet(pos, move, nLife, g_Btype);	
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
	else if (GetKeyboardTrigger(DIK_RIGHT) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// �E�ɔ���
	 // �e�̏��
		pos = g_posPlayer;								// �v���C���[�̈ʒu
		move.x = (sinf(g_fAnglePlayer) + MOVE_SPEED);	// X�����̈ړ���
		move.y = 0;										// Y�����̈ړ���
		nLife = BULLET_LIFE;							// ����

		// �e�̐ݒ�
		SetBullet(pos, move, nLife, g_Btype);	
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ���ɔ���
	 // �e�̏��
		pos = g_posPlayer;								// �v���C���[�̈ʒu
		move.x = -(sinf(g_fAnglePlayer) + MOVE_SPEED);	// X�����̈ړ���
		move.y = 0;										// Y�����̈ړ���
		nLife = BULLET_LIFE;							// ����

		// �e�̐ݒ�
		SetBullet(pos, move, nLife, g_Btype);
		PlaySound(SOUND_LABEL_SE_SHOT);
	}
//----------------------//
//		 ����\��		//
//----------------------//
	if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.player == PLAYER_TYPE_GREEN && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ON �� OFF
		g_Player.bSkills = g_Player.bSkills ? false : true;
	}
	else if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.player == PLAYER_TYPE_RED && g_Player.PlayerState == PLAYERSTATE_NORMAL)
	{// ON �� OFF
		g_Player.bSkills = g_Player.bSkills ? false : true;
	}
	// ON �̂Ƃ�
	if (g_Player.bSkills == true)
	{// ����\�́@X�Ŏg�p
		if (GetKeyboardTrigger(DIK_Q) == true)
		{// �G�t�F�N�g�̔����i���j

		}
		else if (GetKeyboardTrigger(DIK_E) == true)
		{// �G�t�F�N�g�̔����i���j

		}
	}
//----------------------//
//	  �v���C���[�ύX	//
//----------------------//
	if (GetKeyboardTrigger(DIK_Q) == true)
	{// Q�@�L�����ύX
		if (g_Player.player == PLAYER_TYPE_RED)
		{
			g_Player.player = PLAYER_TYPE_GREEN;
			g_Player.bSkills = false;	//����\�͂�OFF
		}
		else if (g_Player.player == PLAYER_TYPE_GREEN)
		{
			g_Player.player = PLAYER_TYPE_RED;
			g_Player.bSkills = false;	//����\�͂�OFF
		}
	}
	// �ʒu�̍X�V
	g_posPlayer.x += g_movePlayer.x;
	g_posPlayer.y += g_movePlayer.y;
	g_rotPlayer.z += g_movePlayer.z;
//-----------------------//
// �`���[�g���A�����[�h
//-----------------------//
	if (g_Player.g_mode == MODE_TUTORIAL)
	{
		// ���͈̔�
		if (g_posPlayer.x + G_POS_X > SCREEN_WIDTH || g_posPlayer.x - G_POS_X < 0)
		{// �ړ��s��
			g_posPlayer.x -= g_movePlayer.x;
		}
		// �c�͈̔�
		if (g_posPlayer.y + G_POS_Y > SCREEN_HEIGHT - 200 || g_posPlayer.y - G_POS_Y < SCREEN_ALPHA)
		{// �ړ��s��
			g_posPlayer.y -= g_movePlayer.y;
		}
	}
//-----------------------//
// �Q�[�����[�h
//-----------------------//
	if (g_Player.g_mode == MODE_GAME)
	{
		// ���͈̔�
		if (g_posPlayer.x + G_POS_X > SCREEN_WIDTH || g_posPlayer.x - G_POS_X < 0)
		{// �ړ��s��
			g_posPlayer.x -= g_movePlayer.x;
		}
		// �c�͈̔�
		if (g_posPlayer.y + G_POS_Y > SCREEN_HEIGHT - SCREEN_ALPHA || g_posPlayer.y - G_POS_Y < SCREEN_ALPHA)
		{// �ړ��s��
			g_posPlayer.y -= g_movePlayer.y;
		}
		//�����G���A
		// ����
		if (g_posPlayer.x - G_POS_X < WATER_SIZE && g_posPlayer.y - G_POS_Y < WATER_SIZE || g_posPlayer.x - G_POS_X < WATER_SIZE && g_posPlayer.y + G_POS_Y > SCREEN_HEIGHT - WATER_SIZE)
		{// �ړ��s��

			g_posPlayer.x -= g_movePlayer.x;
			g_posPlayer.y -= g_movePlayer.y;
		}
		// �E��
		if (g_posPlayer.x + G_POS_X > SCREEN_WIDTH - WATER_SIZE && g_posPlayer.y - G_POS_Y < WATER_SIZE || g_posPlayer.x + G_POS_X > SCREEN_WIDTH - WATER_SIZE && g_posPlayer.y + G_POS_Y > SCREEN_HEIGHT - WATER_SIZE)
		{// �ړ��s��
			g_posPlayer.x -= g_movePlayer.x;
			g_posPlayer.y -= g_movePlayer.y;
		}
	}
//-----------------------//
// ���_���
//-----------------------//
	// �ړ��E��]�ʂ̌���
	g_movePlayer.x += (0 - g_movePlayer.x)*1.0f;
	g_movePlayer.y += (0 - g_movePlayer.y)*1.0f;
	g_movePlayer.z += (0 - g_movePlayer.z)*1.0f;

	// �A�j���e�N�X�`���̍��W
	pVtx[0].tex = D3DXVECTOR2(1.0f*(float)g_nPatternAnim, g_fTexY + 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f*(float)g_nPatternAnim, g_fTexY + 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f*((float)g_nPatternAnim + 1), g_fTexY + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f*((float)g_nPatternAnim + 1), g_fTexY + 0.0f);

	// �e���_�̍��W
	pVtx[0].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z - (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[1].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z - (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + g_fAnglePlayer) * g_fLengthPlayer;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = g_posPlayer.x + sinf(g_rotPlayer.z + (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[3].pos.y = g_posPlayer.y + cosf(g_rotPlayer.z + (g_fAnglePlayer * 3)) * g_fLengthPlayer;
	pVtx[3].pos.z = 0.0f;

	// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@�i�����x�j
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);

	// �v���C���[�̈ʒu�����擾
	g_Player.Playerpos = g_posPlayer;
//-----------------------//
// �v���C���[�̏��
//-----------------------//
	if (g_Player.PlayerState == PLAYERSTATE_WAIT)
	{// �o���҂�
	 // ��Ԃ̃J�E���^�[��i�߂�
		g_Player.nCounterState ++;

		if ((g_Player.nCounterState % FRAME_COUNT) == 0)
		{// �P�O�t���[��
			g_nAlpha = COLOR_ALPHA;	// ���l��߂�
		}
		if ((g_Player.nCounterState % (FRAME_COUNT * HALF_MATH)) == 0)
		{// �Q�O�t���[��
			g_nAlpha = COLOR_ALPHA / HALF_MATH;	// ���l�𔼕�
		}
		if ((g_Player.nCounterState % NORMAL_PLAYER) == 0)
		{// �Q�S�O�t���[��
			g_Player.PlayerState = PLAYERSTATE_NORMAL;	// �v���C���[�̏�Ԃ�ʏ�
			g_nAlpha = COLOR_ALPHA;						// ���l��߂�
			g_Player.nLife = PLAYER_LIFE;				// �̗͂��R��
			g_Player.nCounterState = 0;					// ��Ԃ̃J�E���^�[��������
		}
	}
	else if (g_Player.PlayerState == PLAYERSTATE_DAMAGE)
	{// �_���[�W�̍d��
		// �J�E���g��i�߂�
		g_Player.nCounterDisp ++;

		// �v���C���[�̓����x�𔼕��ɂ���
		g_nAlpha = COLOR_ALPHA / HALF_MATH;
		if ((g_Player.nCounterDisp % (FRAME_COUNT / HALF_MATH)) == 0)
		{// �T�t���[����
			g_Player.PlayerState = PLAYERSTATE_NORMAL;	// ��Ԃ��m�[�}����
			g_Player.nCounterDisp = 0;					// �J�E���g��������
			g_nAlpha = COLOR_ALPHA;						// ���l��߂�
		}
	}
	// �v���C���[�o�b�t�@�̃A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawPlayer(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer[g_Player.player]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);		
}

//=====================================================================================================================================================================//
// �v���C���[�̃_���[�W
//=====================================================================================================================================================================//
bool HitPlayer(int Damage)
{
	// �_���[�W
	g_Player.nLife -= Damage;

	if (g_Player.nLife == 0)
	{// LIFE���[���ɂȂ����ꍇ

		// �v���C���[���S
		g_Player.PlayerState = PLAYERSTATE_DEATH;
		 
		// �����x�𔼕��ɂ���
		g_nAlpha /= 2;

		// �����̏ꏊ�ɖ߂�
		g_posPlayer = D3DXVECTOR3(CENTER_POS_X, CENTER_POS_Y, 0.0f);

		// �o����Ԃɂ���
		g_Player.PlayerState = PLAYERSTATE_WAIT;

		return true;
	}
	else
	{
		// ��Ԃ��_���[�W
		g_Player.PlayerState = PLAYERSTATE_DAMAGE;

		return false;
	}
}


//=====================================================================================================================================================================//
// �v���C���[���̎擾
//=====================================================================================================================================================================//
PLAYER *GetPlayer(void)
{
	return &g_Player;
}