//##################################################################################################################################################################//
//
// �u���b�N���� [brock.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "brock.h"
#include "player.h"
#include "stage.h"
#include "backbg.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_BROCK			(1080)
#define MAX_COLOR			(D3DCOLOR_RGBA(255, 255, 255, 255))
#define LENGTH_PLAYER_X		(30)								// ���S����e���_�̋��������߂鐔�l
#define LENGTH_PLAYER_Y		(50)								// ���S����e���_�̋��������߂鐔�l
#define MOVE_SPEED_RIGTH	(D3DXVECTOR3(-5.1f,0.0f,0.0f))
#define MOVE_SPEED_LEFT		(D3DXVECTOR3(5.1f,0.0f,0.0f))

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureBrock = NULL;;		//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBrock = NULL;		//���_�o�b�t�@�ւ̃|�C���^
BROCK g_Brock;
//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT InitBrock(void)
{
	// �|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	g_Brock.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Brock.bUse = false;
	g_Brock.fHeigth = 0.0f;
	g_Brock.fWidth = 0.0f;
	g_Brock.HitPlayer = false;
	g_Brock.BrockStop = BROCK_STOP_NO;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\block.jpg", &g_pTextureBrock);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BROCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBrock, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	//rhw�̐ݒ�		=	1.0f�Œ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = MAX_COLOR;
	pVtx[1].col = MAX_COLOR;
	pVtx[2].col = MAX_COLOR;
	pVtx[3].col = MAX_COLOR;

	//�e�N�X�`���̒��_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0, 1);
	pVtx[1].tex = D3DXVECTOR2(0, 0);
	pVtx[2].tex = D3DXVECTOR2(1, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 0);

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBrock->Unlock();

	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void UninitBrock(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBrock != NULL)
	{
		g_pVtxBuffBrock->Release();
		g_pVtxBuffBrock = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_pTextureBrock != NULL)
	{
		g_pTextureBrock->Release();
		g_pTextureBrock = NULL;
	}
}

//=====================================================================================================================================================================//
//�X�V����
//=====================================================================================================================================================================//
void UpdateBrock(void)
{

}

//=====================================================================================================================================================================//
//�`�揈��
//=====================================================================================================================================================================//
void DrawBrock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBrock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBrock);

	if (g_Brock.bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=====================================================================================================================================================================//
//�u���b�N�̐ݒu
//=====================================================================================================================================================================//
void SetBrock(D3DXVECTOR3 pos, float fWidth, float fHeigth)
{
	// �|�C���^
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;

	pPlayer = GetPlayer();


	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Brock.bUse == false)
	{
		// �ʒu�E�����E��
		g_Brock.pos = pos;
		g_Brock.pos.y -= fHeigth;
		if (pPlayer->PlayerDire == DIRECTION_LEFT)
		{
			g_Brock.pos.x -= fWidth;
		}
		g_Brock.fHeigth = fHeigth;
		g_Brock.fWidth = fWidth;

		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Brock.pos.x, g_Brock.pos.y + g_Brock.fHeigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Brock.pos.x, g_Brock.pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Brock.pos.x + g_Brock.fWidth, g_Brock.pos.y + g_Brock.fHeigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Brock.pos.x + g_Brock.fWidth, g_Brock.pos.y, 0.0f);

		// �g�p���ɂ���
		g_Brock.bUse = true;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBrock->Unlock();
}


//=====================================================================================================================================================================//
//�u���b�N�̈ړ�
//=====================================================================================================================================================================//
void MoveBrock(void)
{
	// �|�C���^
	VERTEX_2D *pVtx;

	PLAYER *pPlayer;
	BROCK *pBrock;

	// ���擾
	pPlayer = GetPlayer();
	pBrock = &g_Brock;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBrock->Lock(0, 0, (void**)&pVtx, 0);

	if (pBrock->bUse == true)
	{// �g�p��
	 // �ߋ��̍��W�ۊ�
		pBrock->Oldpos.x = pBrock->pos.x;
		if (pPlayer->PlayerDire == DIRECTION_RIGTH && pBrock->HitPlayer == false)
		{// �v���C���[���E�ɐi��ł���
		 // �ړ��ʂ̑��
			pBrock->move = MOVE_SPEED_RIGTH;
		}
		else if (pPlayer->PlayerDire == DIRECTION_LEFT && pBrock->HitPlayer == false)
		{// �v���C���[�����ɐi��ł���
		 // �ړ��ʂ̑��
			pBrock->move = MOVE_SPEED_LEFT;
		}
		else if (pBrock->HitPlayer == true)
		{// �v���C���[�ɂԂ����Ă���
			pBrock->move.x = 0.0f;
		}

		// ���W�X�V
		pBrock->pos.x += pBrock->move.x;

		// ������擾
		g_Brock.HitPlayer = CollisionPlayer(&pBrock->pos, &pBrock->Oldpos, &pBrock->move, pBrock->fWidth, pBrock->fHeigth);

		// �e���_���W
		pVtx[0].pos = D3DXVECTOR3(pBrock->pos.x, pBrock->pos.y + pBrock->fHeigth, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pBrock->pos.x, pBrock->pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pBrock->pos.x + pBrock->fWidth, pBrock->pos.y + pBrock->fHeigth, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pBrock->pos.x + pBrock->fWidth, pBrock->pos.y, 0.0f);
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBrock->Unlock();
}

//=====================================================================================================================================================================//
//�u���b�N�̏��
//=====================================================================================================================================================================//
BROCK *GetBrock(void)
{
	return &g_Brock;
}
