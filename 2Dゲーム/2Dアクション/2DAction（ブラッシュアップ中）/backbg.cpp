//##################################################################################################################################################################//
//
// ���w�i���� [backbg.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "backbg.h"
#include "player.h"
#include "stage.h"
#include "brock.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// �ԐF
#define COLOR_BULUE			(255)			// �F
#define COLOR_GREEN			(255)			// �ΐF
#define COLOR_ALPHA			(255)			// �A���t�@�l
#define HEIGTH_SIZE			(200)			// 
#define MAX_RIGTH			(3000)			// 
#define MAX_LEFT			(-3000)			// 
#define MOVE_SPEED			(0.003f)		// 

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBackBg = NULL;	// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureBackBg = NULL;			// �e�N�X�`���̏��
BACKBG g_BackBg;

//=====================================================================================================================================================================//
// �w�i�̏���������
//=====================================================================================================================================================================//
HRESULT InitBackBg(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�|�C���^
	VERTEX_2D *pVtx;

	g_BackBg.BackMove = BACKBG_MOVE_START;
	g_BackBg.move = 0.0f;
	g_BackBg.nCunt = 0;
	g_BackBg.Move = 0.0f;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bg000.png", &g_pTextureBackBg);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBackBg, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffBackBg->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, HEIGTH_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, HEIGTH_SIZE, 0.0f);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	//�e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBackBg->Unlock();

	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitBackBg(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureBackBg != NULL)
	{
		g_pTextureBackBg->Release();
		g_pTextureBackBg = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBackBg != NULL)
	{
		g_pVtxBuffBackBg->Release();
		g_pVtxBuffBackBg = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateBackBg(void)
{


}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawBackBg(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBackBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBackBg);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void MoveBack(void)
{
	// ���_�|�C���^
	VERTEX_2D *pVtx;
	GAMEPOS *pGamePos;
	PLAYER *pPlayer;
	BROCK *pBrock;

	pBrock = GetBrock();
	pPlayer = GetPlayer();
	pGamePos = GetGamePos();

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffBackBg->Lock(0, 0, (void**)&pVtx, 0);

	g_BackBg.Move = MOVE_SPEED;

	if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
	{
		g_BackBg.move -= g_BackBg.Move;	// �e�N�X�`���̈ړ�
	}
	else if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
	{
		g_BackBg.move += g_BackBg.Move;	// �e�N�X�`���̈ړ�
	}
	else if (pBrock->HitPlayer == true)
	{
		g_BackBg.move += 0.0f;
	}

	//�e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_BackBg.move), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_BackBg.move), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_BackBg.move), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_BackBg.move), 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBackBg->Unlock();
}

BACKBG *GetBackBg(void)
{
	return &g_BackBg;
}
