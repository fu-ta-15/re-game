//##################################################################################################################################################################//
//
// ��O�w�i���� [prebg.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "prebg.h"
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
#define HEIGTH_SIZE			(500)
#define MAX_RIGTH			(3000)
#define MAX_LEFT			(-3000)
#define MOVE_SPEED			(0.004f)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPreBg = NULL;	// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTexturePreBg = NULL;			// �e�N�X�`���̏��
PREBG g_PreBg;
//=====================================================================================================================================================================//
// �w�i�̏���������
//=====================================================================================================================================================================//
HRESULT InitPreBg(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�|�C���^
	VERTEX_2D *pVtx;

	g_PreBg.PreMove = PREBG_MOVE_START;
	g_PreBg.move = 0.0f;
	g_PreBg.nCunt = 0;
	g_PreBg.Move = 0.0f;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ground.png", &g_pTexturePreBg);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPreBg, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);

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
	g_pVtxBuffPreBg->Unlock();

	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitPreBg(void)
{
	//�e�N�X�`���̊J��
	if (g_pTexturePreBg != NULL)
	{
		g_pTexturePreBg->Release();
		g_pTexturePreBg = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPreBg != NULL)
	{
		g_pVtxBuffPreBg->Release();
		g_pVtxBuffPreBg = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdatePreBg(void)
{

}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawPreBg(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPreBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePreBg);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=====================================================================================================================================================================//
// �w�i�̈ړ�
//=====================================================================================================================================================================//
void MovePre(void)
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
	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);

	g_PreBg.Move = MOVE_SPEED;

	if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
	{
		g_PreBg.move -= g_PreBg.Move;	// �e�N�X�`���̈ړ�
	}
	else if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
	{
		g_PreBg.move += g_PreBg.Move;	// �e�N�X�`���̈ړ�
	}
	else if (pBrock->HitPlayer == true)
	{
		g_PreBg.move += 0.0f;	// �e�N�X�`���̈ړ�
	}

	//�e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 0.0f);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPreBg->Unlock();
}
////=====================================================================================================================================================================//
//// �w�i�̈ړ�
////=====================================================================================================================================================================//
//void LeftMovePre(void)
//{
//	// ���_�|�C���^
//	VERTEX_2D *pVtx;
//	GAMEPOS *pGamePos;
//	pGamePos = GetGamePos();
//
//
//	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
//	g_pVtxBuffPreBg->Lock(0, 0, (void**)&pVtx, 0);
//
//	g_PreBg.move -= g_PreBg.Move;	// �e�N�X�`���̈ړ�
//
//	g_PreBg.Move = MOVE_SPEED;
//
//	//�e�N�X�`���̒��_���W�̐ݒ�
//	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 1.0f);
//	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_PreBg.move), 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 1.0f);
//	pVtx[3].tex = D3DXVECTOR2(1.0f + (g_PreBg.move), 0.0f);
//
//	//���_�o�b�t�@���A�����b�N
//	g_pVtxBuffPreBg->Unlock();
//}

PREBG *GetPreBg(void)
{
	return &g_PreBg;
}
