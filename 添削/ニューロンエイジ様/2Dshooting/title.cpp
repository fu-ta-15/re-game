//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

#include "input.h"
#include "title.h"
#include "fade.h"
#include "sound.h"


//�}�N����`
#define MAX_TITLEMODEL	(TITLEMODEL_MAX)
#define COLOR_RED		(255)	//�ԐF
#define COLOR_BULUE		(255)	//�F
#define COLOR_GREEN		(255)	//�ΐF
#define COLOR_ALPHA		(255)	//�A���t�@�l


//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_apTextureTitle[MAX_TITLEMODEL] = {};	//�e�N�X�`���̏��
int g_TitleY[2];
int g_Buuton[2];
int g_nCunt;

//�|���S���̏���������
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
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\taitoll.png", &g_apTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\titlelog2.png", &g_apTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevi, "data\\TEXTURE\\buuton.png", &g_apTextureTitle[2]);

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
		{
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
		else if (nCunTil == TITLEMODEL_TITLE)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 4, (float)g_TitleY[0], 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 4, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, (float)g_TitleY[0], 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, 0.0f, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);

		}
		else if (nCunTil == TITLEMODEL_BUUTON)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH/4, 800, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH/4, 500, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH/2+ SCREEN_WIDTH / 4, 800, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH/2+ SCREEN_WIDTH / 4, 500, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
		}

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

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffTitle->Unlock();

	PlaySound(SOUND_LABEL_BGM004);

	return S_OK;
}

//�|���S���̏I������
void UninitTitle(void)
{
	for (int nCunTil = 0; nCunTil < MAX_TITLEMODEL; nCunTil++)
	{
		//�e�N�X�`���̊J��
		if (g_apTextureTitle[nCunTil] != NULL)
		{
			g_apTextureTitle[nCunTil]->Release();
			g_apTextureTitle[nCunTil] = NULL;
		}
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	StopSound(SOUND_LABEL_BGM004);	//BGM

}

//�|���S���̍X�V����
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;
	FADE pFade;
	pFade = GetFade();
	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	if (g_TitleY[0] <= 0 || g_TitleY[0] <= SCREEN_HEIGHT / 3)
	{
		pVtx += (4 * TITLEMODEL_TITLE);
		g_TitleY[0] += g_TitleY[1];

		//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
		pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 4, (float)g_TitleY[0], 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 4, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, (float)g_TitleY[0], 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, 0.0f, 0.0f);

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);

		//�^�C�g�����S���������ĂȂ��ꍇ
		if (GetKeyboardTrigger(DIK_RETURN) == true && pFade == FADE_NONE || g_TitleY[0] >= SCREEN_HEIGHT / 3)
		{
			//�^�C�g�����S���������Ă���ꍇ
			if (GetKeyboardTrigger(DIK_RETURN) == true && g_TitleY[0] >= SCREEN_HEIGHT / 3 && g_nCunt == 1 && pFade == FADE_NONE)
			{
				g_Buuton[1] = 10;				//�{�^��
				SetFade(FADE_OUT, MODE_TUTORIAL);	//�t�F�[�h�A�E�g�E�Q�[�����[�h�Ɉڍs
			}

			g_TitleY[0] = SCREEN_HEIGHT / 3;
			g_TitleY[1] = 0;

			//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
			g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (4 * TITLEMODEL_BUUTON);

			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

			g_Buuton[0] += g_Buuton[1];
			g_nCunt = 1;

			if (g_Buuton[0] >= 50)
			{
				pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
				pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
				pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
				pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 0);
			}

			if (g_Buuton[0] >= 100)
			{
				pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
				g_Buuton[0] = 0;
			}
			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffTitle->Unlock();
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