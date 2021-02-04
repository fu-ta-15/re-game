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
#include "input.h"
#include "brock.h"
#include "prebg.h"
#include "backbg.h"
#include "stage.h"
#include "padinput.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MOVE_SPEED			(4)									// �X�s�[�h
#define LENGTH_PLAYER_X		(30)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_PLAYER_Y		(50)								// ���S����e���_�̋��������߂鐔�l
#define COLOR_RED			(255)								// �ԐF
#define COLOR_BULUE			(255)								// �F
#define COLOR_GREEN			(255)								// �ΐF
#define COLOR_ALPHA			(255)								// �A���t�@�l
#define PVTEX_MAX			(4)									// pVtx
#define FRAME_COUNT			(10)								// FRAME�̃J�E���g
#define RHW					(10/10)								// rhw�̐��l1.0�Œ�
#define PLAYER_TEX			(13)								// �e�N�X�`���̗]��
#define TEXTURE_PLAYER_X	(4)									// �e�N�X�`�����̕�����
#define TEXTURE_PLAYER_Y	(1)									// �e�N�X�`��y�̕�����
#define HEIGTH_SIZE			(510)								// �n�ʂ̏�ӂ̍���



//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;			// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;					// �e�N�X�`���̏��
PLAYER g_Player;											// �v���C���[���
int g_nConterAnim;											// �A�j���[�V�����̃J�E���^�[
int g_nPatternAnim;											// �A�j���[�V����
int g_nNextAnim;											// ���̃A�j���[�V�����ɍs���܂ł̃J�E���g
int g_nAlpha;												// ���l
float g_fTexY;												// �e�N�X�`��y���W
bool g_bLandP;												// �����蔻��

//=====================================================================================================================================================================//
// �v���C���[�̏���������
//=====================================================================================================================================================================//
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;			// ���_�|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �O���[�o���ϐ��̏�����
	g_nConterAnim = 0;
	g_nPatternAnim = 0;
	g_nNextAnim = 0;
	g_fTexY = 0.0f;
	g_nAlpha = COLOR_ALPHA;
	g_bLandP = false;

	// �v���C���[���̏�����
	g_Player.nCounterState = 0;
	g_Player.nCounterDisp = 0;
	g_Player.Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.PlayerDire = DIRECTION_RIGTH;
	g_Player.PlayerBrock = HIT_BROCK_NO;
	g_Player.PlayerState = PLAYERSTATE_NORMAL;
	g_Player.Junp = true;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tori_tokage3.png", &g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * PVTEX_MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �����̏ꏊ�ɖ߂�
	g_Player.pos = D3DXVECTOR3(SCREEN_WIDTH / 5, 400 - LENGTH_PLAYER_Y, 0.0f);

	//�e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);

	// ��]�p�x
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

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
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
	//StopSound(SOUND_LABEL_SE_SHOT);	//BGM

}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdatePlayer(void)
{
	// �|�C���^
	VERTEX_2D *pVtx;	// ���_�̃|�C���^ 
	PLAYER *pPlayer;	// �v���C���[�̃|�C���^
	MODE pMode;

	// ���擾
	pPlayer = &g_Player;// �v���C���[
	pMode = GetMode();

	// �ߋ��̈ʒu
	g_Player.Oldpos = g_Player.pos;

	// �ʒu�̍X�V
	g_Player.move.y += 1.0f;
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.rot.z += g_Player.move.z;

	// �ړ��E��]�ʂ̌���
	g_Player.move.x += (0 - g_Player.move.x) * 0.8f;
	g_Player.move.y += (0 - g_Player.move.y) * 0.002f;
	g_Player.move.z += (0 - g_Player.move.z) * 1.0f;

	// �u���b�N�Ƃ̓����蔻��
	g_bLandP = CollisionBrock(&g_Player.pos, &g_Player.Oldpos, &g_Player.move, PLAYER_TEX, LENGTH_PLAYER_Y);

	if (g_bLandP == true)
	{// �u���b�N�̏�ɂ���Ƃ�
		pPlayer->Junp = false;
	}
	if (g_Player.pos.y + LENGTH_PLAYER_Y > HEIGTH_SIZE)
	{// �c�͈̔�
		g_Player.move.y = 0.0f;
		g_Player.pos.y = HEIGTH_SIZE - LENGTH_PLAYER_Y;
		pPlayer->Junp = false;
	}
	if ((g_nPatternAnim + 1) % 5 == 0)
	{// �l�Ԗڂ܂ŗ����珉���ɖ߂�
		g_nPatternAnim = 0;
	}

	// �o�b�t�@�̃��b�N
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[1].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));
	pVtx[2].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY + 1));
	pVtx[3].tex = D3DXVECTOR2(1.0f / TEXTURE_PLAYER_X * ((float)g_nPatternAnim + 1), 1.0f / TEXTURE_PLAYER_Y * (g_fTexY));

	// �e���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y + LENGTH_PLAYER_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + LENGTH_PLAYER_X, g_Player.pos.y - LENGTH_PLAYER_Y, 0.0f);

	// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@�i�����x�j
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, g_nAlpha);
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
	pDevice->SetTexture(0, g_pTexturePlayer);
	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================================================================================================================================//
// �v���C���[�̈ړ�
//=====================================================================================================================================================================//
void MovePlayer(void)
{
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	bool *pPad = GetPadPlress();

	if (GetKeyboardPresse(DIK_D) == true || pPad[JPPRESS_RIGTH] == true)
	{// �E
		g_Player.PlayerDire = DIRECTION_RIGTH;				// ����
		g_fTexY = DIRECTION_RIGTH;							// �A�j���e�N�X�`��Y
		if (g_Player.Junp == false)
		{// �A�j���[�V�����J�E���^�[�J�n
			g_nConterAnim += 1;								// �A�j���[�V�����J�E���^�[
			if ((g_nConterAnim % 5) == 0)
			{// �A�j���[�V�������x
				g_nPatternAnim += 1;						// �A�j���e�N�X�`��X
			}
		}
	}
	//else if (GetKeyboardPresse(DIK_A) == true || pPad[JPPRESS_LEFT] == true)
	//{// ��
	//	g_Player.PlayerDire = DIRECTION_LEFT;				// ����
	//	g_fTexY = DIRECTION_LEFT;							// �A�j���e�N�X�`��Y

	//	if (g_Player.Junp == false)
	//	{// �A�j���[�V�����J�E���^�[�J�n
	//		g_nConterAnim += 1;								// �A�j���[�V�����J�E���^�[
	//		if ((g_nConterAnim % 5) == 0)
	//		{// �A�j���[�V�������x
	//			g_nPatternAnim += 1;						// �A�j���e�N�X�`��X
	//		}
	//	}
	//}
	//else if (GetKeyboardPresse(DIK_A) == false)
	//{// �~�܂�����
	//	g_nPatternAnim = 0;									// �A�j���[�V�����X�g�b�v
	//}
	else if (GetKeyboardPresse(DIK_D) == false)
	{// �~�܂�����
		g_nPatternAnim = 0;									// �A�j���[�V�����X�g�b�v
	}
	if (g_Player.Junp == false)
	{// �󒆂ɂ��Ȃ��Ƃ�
		if (GetKeyboardTrigger(DIK_J) == true || GetKeypadTrigger(0) == true)
		{// �W�����v�J�n
			g_Player.move.y -= 20.0f;						// �W�����v��
			g_Player.Junp = true;							// �W�����v��
		}
	}
	if (g_Player.Junp == true)
	{// �󒆂ɂ���Ƃ�
		g_nPatternAnim = 1;									// �A�j���[�V�����X�g�b�v
	}
	if (g_Player.move.y != 0.0f)
	{// �W�����v�s��
		g_Player.Junp = true;								// ��
	}
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

