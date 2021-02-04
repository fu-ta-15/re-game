//##################################################################################################################################################################//
//
// �Q�[�W���� [gauge.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "gauge.h"
#include "input.h"
#include "fade.h"
#include "point.h"
#include "action.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define GAUGE_TYPE				(2)						//�Q�[�W�̎��
#define COLOR_RED				(255)					//�ԐF
#define COLOR_BULUE				(255)					//�F
#define COLOR_GREEN				(255)					//�ΐF
#define COLOR_ALPHA				(255)					//�A���t�@�l

#define GAUGE_HEITH				(570)
#define GAUGE_START				(620.0f)
#define GAUGE_GOLE				(660.0f)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureGauge[GAUGE_TYPE] = {};	//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGauge = NULL;		//���_�o�b�t�@�ւ̃|�C���^
GAUGE g_Gauge;

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitGauge(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_Gauge.g_GaugeStart = GAUGE_START;
	g_Gauge.g_GaugeGole = GAUGE_GOLE;
	g_Gauge.g_GaugeColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\life-geage.png", &g_apTextureGauge[0]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * GAUGE_TYPE , D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGauge, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		if (nCunt == 0)
		{
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, GAUGE_HEITH, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, GAUGE_HEITH, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_Gauge.g_GaugeColor;
			pVtx[1].col = g_Gauge.g_GaugeColor;
			pVtx[2].col = g_Gauge.g_GaugeColor;
			pVtx[3].col = g_Gauge.g_GaugeColor;
		}
		else if (nCunt == 1)
		{
			pVtx[0].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, GAUGE_HEITH, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, GAUGE_HEITH, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
		}

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		pVtx += 4;
	}
	g_pVtxBuffGauge->Unlock();

	return S_OK;
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
void UninitGauge(void)
{
	if (g_pVtxBuffGauge != NULL)
	{
		g_pVtxBuffGauge->Release();
		g_pVtxBuffGauge = NULL;
	}
	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		if (g_apTextureGauge[nCunt] != NULL)
		{
			g_apTextureGauge[nCunt]->Release();
			g_apTextureGauge[nCunt] = NULL;
		}
	}
}

//=====================================================================================================================================================================//
//�Q�[�W�̍X�V
//=====================================================================================================================================================================//
void UpdateGauge(void)
{
	VERTEX_2D *pVtx;
	POINTER *pPoint = GetPointer();
	ACTIONPLAYER *pActionPlayer = GetAction();

	switch (pActionPlayer->Amode)
	{
	case ACTION_MODE_ATTACK:
		g_Gauge.g_GaugeStart = 620.0f;
		g_Gauge.g_GaugeGole = 660.0f;
		break;
	case ACTION_MODE_DIG:
		g_Gauge.g_GaugeStart = 625.0f;
		g_Gauge.g_GaugeGole = 655.0f;
		break;
	default:
		break;
	}
	g_pVtxBuffGauge->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	pVtx[0].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Gauge.g_GaugeStart, GAUGE_HEITH, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Gauge.g_GaugeGole, GAUGE_HEITH, 0.0f);

	//���_�J���[�̐ݒ�E�ԁE�΁E��
	pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);
	pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, 0, 0, COLOR_ALPHA);

	g_pVtxBuffGauge->Unlock();
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
void DrawGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGauge, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunt = 0; nCunt < GAUGE_TYPE; nCunt++)
	{
		pDevice->SetTexture(0, g_apTextureGauge[nCunt]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunt * 4 , 2);
	}
}

//=====================================================================================================================================================================//
//
//=====================================================================================================================================================================//
GAUGE *GetGauge(void)
{
	return &g_Gauge;
}
