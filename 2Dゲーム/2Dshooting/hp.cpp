//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


#include "hp.h"
#include "input.h"
#include "fade.h"

#define HP_TYPE			(HPTYPE_MAX)	//�̗̓Q�[�W�̎��
#define MAX_HP			(170)			//�̗�
#define COLOR_RED		(255)			//�ԐF
#define COLOR_BULUE		(255)			//�F
#define COLOR_GREEN		(255)			//�ΐF
#define COLOR_ALPHA		(255)			//�A���t�@�l


//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_apTextureHp[HP_TYPE] = {};	//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHp = NULL;		//���_�o�b�t�@�ւ̃|�C���^
HP g_Hp;
int g_nCun;


HRESULT InitHp(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	 g_Hp.fHpGreen = MAX_HP;
	 g_Hp.fHpRed = MAX_HP;
	 g_nCun = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\life-geage.png", &g_apTextureHp[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\life-geage.png", &g_apTextureHp[1]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * HP_TYPE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHp, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHp = 0; nCntHp < HP_TYPE; nCntHp++)
	{
		if (nCntHp == HPTYPE_RED)
		{

			pVtx[0].pos = D3DXVECTOR3(566, 380, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(566, 355, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpRed), 380, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpRed), 355, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);


			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		else if (nCntHp == HPTYPE_GREEN)
		{
			pVtx[0].pos = D3DXVECTOR3(566, 380, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(566, 355, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 380, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 355, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(0, COLOR_GREEN, 0, COLOR_ALPHA);


			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		pVtx += 4;
	}

	g_pVtxBuffHp->Unlock();

	return S_OK;
}


void UninitHp(void)
{
	if (g_pVtxBuffHp != NULL)
	{
		g_pVtxBuffHp->Release();
		g_pVtxBuffHp = NULL;
	}
	for (int nCntHp = 0; nCntHp < HP_TYPE; nCntHp++)
	{
		if (g_apTextureHp[nCntHp] != NULL)
		{
			g_apTextureHp[nCntHp]->Release();
			g_apTextureHp[nCntHp] = NULL;
		}
	}
}

//�̗͂̍X�V
void UpdateHp(void)
{
	VERTEX_2D *pVtx;
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (4 * HPTYPE_GREEN);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(566, 380, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(566, 355, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 380, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 355, 0.0f);

	if (g_Hp.fHpGreen <= 0)
	{
		g_nCun += 1;

		if (g_nCun >= 100)
		{
			SetFade(FADE_OUT, MODE_RANKING);
		}
	}
	g_pVtxBuffHp->Unlock();
}

void DrawHp(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHp, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntHp = 0; nCntHp < HP_TYPE; nCntHp++)
	{
		pDevice->SetTexture(0, g_apTextureHp[nCntHp]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntHp * 4, 2);
	}
}

bool DownHp(float nDamage)
{
	g_Hp.fHpGreen -= nDamage;

	VERTEX_2D *pVtx;
	g_pVtxBuffHp->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (4 * HPTYPE_GREEN);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(566, 380, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(566, 355, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 380, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(566 + ((float)g_Hp.fHpGreen), 355, 0.0f);

	g_pVtxBuffHp->Unlock();


	return true;
}


HP *GetHp(void)
{
	return &g_Hp;
}
