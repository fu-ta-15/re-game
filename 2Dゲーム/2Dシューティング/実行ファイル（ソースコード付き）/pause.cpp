//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


#include "game.h"
#include "fade.h"
#include "pause.h"
#include "input.h"

#define MAX_MENU		(PAUSE_MENU_MAX)
#define COLOR_RED		(255)		//�ԐF
#define COLOR_BULUE		(255)		//�F
#define COLOR_GREEN		(255)		//�ΐF
#define COLOR_ALPHA		(255)	//�A���t�@�l


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		//���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_apTexturePause[MAX_MENU] = {};	//�e�N�X�`���̏��
PAUSE g_Pause;										//�\���̂̕ϐ�

//�|�[�Y�̏���������
HRESULT InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevi;
	VERTEX_2D *pVtx;

	//�ϐ��̏�����
	g_Pause.nSelectCounter = PAUSE_MENU_CONTINUE;
	g_Pause.nSelectold = PAUSE_MENU_QUIT;
	g_Pause.bPause = false;

	//�f�o�C�X�̎擾
	pDevi = GetDevice();

	//�e�N�X�`���̓ǂݎ��
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\pbg.png", &g_apTexturePause[0]);			//�e�N�X�`���u�w�i�v
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\continue.png", &g_apTexturePause[1]);		//�e�N�X�`���u�R���e�B�j���[�v
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\retry.png", &g_apTexturePause[2]);			//�e�N�X�`���u���g���C�v
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\quit.png", &g_apTexturePause[3]);			//�e�N�X�`���u�I���v

	//���_�o�b�t�@�̐���
	if (FAILED(pDevi->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MENU, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCuntPause = 0; nCuntPause < MAX_MENU; nCuntPause++)
	{
		if (nCuntPause == 0)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);

			//�e�N�X�`���̒��_���W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 0);

		}
		else if (nCuntPause == 1 || nCuntPause == 2 || nCuntPause == 3)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(430.0f, 100.0f + (nCuntPause * 200), 0.0f);
			pVtx[1].pos = D3DXVECTOR3(430.0f, 0.0f + (nCuntPause * 200), 0.0f);
			pVtx[2].pos = D3DXVECTOR3(840.0f, 100.0f + (nCuntPause * 200), 0.0f);
			pVtx[3].pos = D3DXVECTOR3(840.0f, 0.0f + (nCuntPause * 200), 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA/3);

			//�e�N�X�`���̒��_���W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1, 1);
			pVtx[3].tex = D3DXVECTOR2(1, 0);

		}
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();
	return S_OK;


}

//�|�[�Y�̏I������
void UninitPause(void)
{
	for (int nCuntPause = 0; nCuntPause < MAX_MENU; nCuntPause++)
	{

		//�e�N�X�`���̊J��
		if (g_apTexturePause[nCuntPause] != NULL)
		{
			g_apTexturePause[nCuntPause]->Release();
			g_apTexturePause[nCuntPause] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

}

//�|�[�Y�̍X�V����
void UpdatePause(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += ((g_Pause.nSelectCounter) * 4);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += ((g_Pause.nSelectold) * 4);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA / 3);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA / 3);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA / 3);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA / 3);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPause->Unlock();


	if (GetKeyboardTrigger(DIK_S) == true)
	{
		g_Pause.nSelectold = g_Pause.nSelectCounter;

		g_Pause.nSelectCounter += 1;

	}
	else if (GetKeyboardTrigger(DIK_W) == true)
	{
		g_Pause.nSelectold = g_Pause.nSelectCounter;

		g_Pause.nSelectCounter -= 1;

		if (g_Pause.nSelectCounter == 0)
		{
			g_Pause.nSelectCounter = 3;
		}

	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SelectBuuton(g_Pause.nSelectCounter);
	}

	if (((g_Pause.nSelectCounter) % 4) == 0)
	{
		g_Pause.nSelectCounter = 1;
	}


}


void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCuntPause = 0; nCuntPause < MAX_MENU; nCuntPause++)
	{

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTexturePause[nCuntPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCuntPause*4, 2);		// 0//�`����J�n���钸�_�C���f�b�N�X

	}
}

void SelectBuuton(int Buuton)
{

	if (Buuton == PAUSE_MENU_CONTINUE)
	{
		SetPause(g_Pause.bPause);
	}
	else if (Buuton == PAUSE_MENU_RETRY)
	{
		SetFade(FADE_OUT, MODE_GAME);	//�t�F�[�h�A�E�g�E�Q�[�����[�h�Ɉڍs
		SetPause(g_Pause.bPause);


	}
	else if (Buuton == PAUSE_MENU_QUIT)
	{
		SetFade(FADE_OUT, MODE_TITLE);	//�t�F�[�h�A�E�g�E�Q�[�����[�h�Ɉڍs
		SetPause(g_Pause.bPause);

	}

}

