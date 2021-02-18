//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "title.h"
#include "fade.h"
#include "player.h"
#include "keyinput.h"
#include "Dinput.h"
#include "sound.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_TITLEMODEL	(TITLEMODEL_MAX)
#define COLOR_RED		(255)	//�ԐF
#define COLOR_BULUE		(255)	//�F
#define COLOR_GREEN		(255)	//�ΐF
#define COLOR_ALPHA		(255)	//�A���t�@�l


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLEMODEL] = {};	//�e�N�X�`���̏��
int g_TitleY[2];
int g_Buuton[2];
int g_nCunt;

//=====================================================================================================================================================================//
//�|���S���̏���������
//=====================================================================================================================================================================//
HRESULT InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevi;
	g_TitleY[0] = -50;
	g_TitleY[1] = 1;
	g_Buuton[0] = 0;
	g_Buuton[1] = 1;
	g_nCunt = 0;
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevi = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\titlelog.png", &g_apTextureTitle[0]);
	//D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\bg000.png", &g_apTextureTitle[1]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevi->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLEMODEL, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�e�e�N�X�`���̏������ݒ�
	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		if (nCunTil == TITLEMODEL_BG)
		{// �w�i
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		}
		//else if (nCunTil == TITLEMODEL_TITLE)
		//{// �^�C�g�����S
		// //���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
		//	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		//	pVtx[1].pos = D3DXVECTOR3(0, 570, 0.0f);
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 570, 0.0f);

		//	//���_�J���[�̐ݒ�E�ԁE�΁E��
		//	pVtx[0].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[1].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[2].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		//	pVtx[3].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);

		//}
		//else if (nCunTil == TITLEMODEL_BUUTON)
		//{// �{�^��
		//	//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
		//	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
		//	pVtx[1].pos = D3DXVECTOR3(0, 570, 0.0f);
		//	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		//	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 570, 0.0f);

		//	//���_�J���[�̐ݒ�E�ԁE�΁E��
		//	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		//}

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1, 1);
		pVtx[3].tex = D3DXVECTOR2(1, 0);

		//pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//PlaySound(SOUND_LABEL_BGM000);

	return S_OK;
}

//�|���S���̏I������
void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{	//���_�o�b�t�@�̊J��
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		//�e�N�X�`���̊J��
		if (g_apTextureTitle[nCunTil] != NULL)
		{
			g_apTextureTitle[nCunTil]->Release();
			g_apTextureTitle[nCunTil] = NULL;
		}
	}
	//StopSound(SOUND_LABEL_BGM000);	//BGM
}

//�|���S���̍X�V����
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	// �t�F�[�h�̏��
	FADE pFade;
	pFade = GetFade();
	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g�����S���������Ă���ꍇ
	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TUTORIAL);	//�t�F�[�h�A�E�g�E�Q�[�����[�h�Ɉڍs
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//�|���S���̕`�揈��
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureTitle[nCunTil]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunTil * 4, 2);		// 0//�`����J�n���钸�_�C���f�b�N�X
	}

}