//##################################################################################################################################################################//
//
// �J�[�\������ [point.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "point.h"
#include "input.h"
#include "player.h"
#include "brock.h"
#include "padinput.h"
#include "action.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED						(255)											// �ԐF
#define COLOR_BULUE						(255)											// �F
#define COLOR_GREEN						(255)											// �ΐF
#define COLOR_ALPHA						(255)											// �A���t�@�l

#define POINT_X							(15)											// ���S���WX
#define POINT_Y							(15)											// ���S���WY
#define POINT_POS						(50.0f)
#define POINT_TYPE						(2)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTexturePoint[2] = {};		// �e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPoint = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
POINTER g_Pointer;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �|�C���g�̏���������
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
HRESULT InitPoint(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;			// VERTEX�̃|�C���^

								// �\���̂̏�����
	g_Pointer.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Pointer.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wepon0.png", &g_pTexturePoint[ACTION_MODE_ATTACK]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\wepon1.png", &g_pTexturePoint[ACTION_MODE_DIG]);

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * POINT_TYPE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPoint, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffPoint->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCuntPointer = 0; nCuntPointer < POINT_TYPE; nCuntPointer++)
	{
		// �e�N�X�`���̒��_���W
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		// rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		pVtx += 4;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPoint->Unlock();
	// S_OK��Ԃ�
	return S_OK;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �|�C���g�̏I������
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void UninitPoint(void)
{
	if (g_pVtxBuffPoint != NULL)
	{
		g_pVtxBuffPoint->Release();
		g_pVtxBuffPoint = NULL;
	}
	for (int nCuntPointer = 0; nCuntPointer < POINT_TYPE; nCuntPointer++)
	{
		if (g_pTexturePoint[nCuntPointer] != NULL)
		{
			g_pTexturePoint[nCuntPointer]->Release();
			g_pTexturePoint[nCuntPointer] = NULL;
		}
	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �|�C���g�̍X�V����
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void UpdatePoint(void)
{
	// VERTEX�̃|�C���^
	VERTEX_2D *pVtx;
	// �\���̂̃|�C���^
	PLAYER *pPlayer = GetPlayer();
	POINTER *pPoint = GetPointer();

	// �v���C���[�̈ʒu���擾
	if (pPlayer->PlayerDire == DIRECTION_RIGTH)
	{// �E����
		pPoint->pos.x = (pPlayer->pos.x + POINT_POS);
	}
	else if (pPlayer->PlayerDire == DIRECTION_LEFT)
	{// ������
		pPoint->pos.x = (pPlayer->pos.x - POINT_POS);
	}

	pPoint->pos.y = pPlayer->pos.y;

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffPoint->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̍X�V(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	pVtx[0].pos = D3DXVECTOR3(pPoint->pos.x - POINT_X, pPoint->pos.y + POINT_X, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pPoint->pos.x - POINT_X, pPoint->pos.y - POINT_X, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pPoint->pos.x + POINT_X, pPoint->pos.y + POINT_X, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pPoint->pos.x + POINT_X, pPoint->pos.y - POINT_X, 0.0f);

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffPoint->Unlock();

	if (GetKeyboardTrigger(DIK_K) == true || GetKeypadTrigger(1) == true)
	{

	}
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �|�C���g�̕`�揈��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
void DrawPoint(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���̎擾
	ACTIONPLAYER *pActionPlayer = GetAction();

	// �e�N�X�`���̔ԍ�
	int SetTex = 0;

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPoint, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	switch (pActionPlayer->Amode)
	{// �e�N�X�`���̐ݒ�
	case ACTION_MODE_ATTACK:
		SetTex = ACTION_MODE_ATTACK;
		break;
	case ACTION_MODE_DIG:
		SetTex = ACTION_MODE_DIG;
		break;
	default:
		break;
	}
	// �w�肵���e�N�X�`�����Z�b�g
	pDevice->SetTexture(0, g_pTexturePoint[SetTex]);
	// �J�n�̃|�C���g����`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 , 2);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �|�C���g�̏��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
POINTER *GetPointer(void)
{
	return &g_Pointer;
}
