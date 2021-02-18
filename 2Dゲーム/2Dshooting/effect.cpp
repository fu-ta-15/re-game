//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "effect.h"
#include "enemy.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_EFFECT		(256)
#define COLOR_RED		(100)
#define COLOR_BULUE		(130)
#define COLOR_GREEN		(10)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�e�̍\����
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR color;
	int Idx;
	int nLife;
	float nSize;
	bool bUse;			//�g�p���Ă��邩�ǂ���
}EFFECT;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;
EFFECT g_aEffect[MAX_EFFECT];
float fYard[MAX_EFFECT];
float fMetth[MAX_EFFECT];
int g_Idx;


HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\effe.png", &g_pTextureEffect);

	for (int nCounterEffect = 0; nCounterEffect < MAX_EFFECT; nCounterEffect++)
	{
		g_aEffect[nCounterEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCounterEffect].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aEffect[nCounterEffect].nLife = 0;
		g_aEffect[nCounterEffect].nSize = 0.0f;
		g_aEffect[nCounterEffect].Idx = 0;
		g_aEffect[nCounterEffect].bUse = false;
		fYard[nCounterEffect] = 0.0f;
		fMetth[nCounterEffect] = 0.0f;
	}


	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEffect, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounterEffect = 0; nCounterEffect < MAX_EFFECT; nCounterEffect++)
	{
		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);
																	
		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.6f, 0.4f, 1.0f);

		//�e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
	return S_OK;

}


void UninitEffect(void)
{
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}

	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

}


void UpdateEffect(void)
{
	VERTEX_2D *pVtx;
	EFFECT *pEffect;
	ENEMY *pEnemy;

	pEnemy = GetEnemy();
	pEffect = &g_aEffect[0];

	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCounterEffect = 0; nCounterEffect < MAX_EFFECT; nCounterEffect++)
	{

		if (g_aEffect[nCounterEffect].bUse == true)
		{
			g_aEffect[nCounterEffect].nLife--;
			g_aEffect[nCounterEffect].nSize += 1.0f;


			//�e���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);

			if (g_aEffect[nCounterEffect].nLife <= 0)
			{
				g_aEffect[nCounterEffect].bUse = false;
				g_aEffect[nCounterEffect].nSize = 0.0f;
			}
		}
		pVtx += 4;
	}
	g_pVtxBuffEffect->Unlock();
}


void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureEffect);

	for (int nCounterEffect = 0; nCounterEffect < MAX_EFFECT; nCounterEffect++)
	{
		if (g_aEffect[nCounterEffect].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCounterEffect * 4, 2);
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	
}


void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR color)
{
	EFFECT *pEffect;
	VERTEX_2D *pVtx;


	pEffect = &g_aEffect[0];


	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);


	for (int nCounterEffect = 0; nCounterEffect < MAX_EFFECT; nCounterEffect++)
	{
		if (g_aEffect[nCounterEffect].bUse == false)
		{
			g_aEffect[nCounterEffect].pos = pos;
			g_aEffect[nCounterEffect].color = color;

			//�e���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x - g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y + g_aEffect[nCounterEffect].nSize, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCounterEffect].pos.x + g_aEffect[nCounterEffect].nSize, g_aEffect[nCounterEffect].pos.y - g_aEffect[nCounterEffect].nSize, 0.0f);

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = g_aEffect[nCounterEffect].color;
			pVtx[1].col = g_aEffect[nCounterEffect].color;
			pVtx[2].col = g_aEffect[nCounterEffect].color;
			pVtx[3].col = g_aEffect[nCounterEffect].color;


			g_aEffect[nCounterEffect].nLife = 500;

			g_aEffect[nCounterEffect].bUse = true;
			break;
		}
		pVtx += 4;
	}

g_pVtxBuffEffect->Unlock();
}
