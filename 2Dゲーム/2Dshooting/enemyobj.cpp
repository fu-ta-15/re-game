//##################################################################################################################################################################//
//
// �G�I�u�W�F�N�g���� [enemyobj.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "enemyobj.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_ENEOBJ		(6)			// �I�u�W�F�N�g�̎��
#define ENEMY_OBJ		(6/2)		// ��ɕ��ԃI�u�W�F�N�g�̐�
#define MINUS_COUNT		(3)			// ��ɕ��ԃI�u�W�F�N�g�̐��i�v�Z�p�j
#define HALF_MATH		(2)			// ����
#define OBJ_ENEMY_X		(310)		// x���W
#define OBJ_NEXT_X		(530)		// x���W�ƂȂ��
#define OBJ_ENEMY_Y		(120)		// y���W
#define OBJ_NEXT_Y		(280)		// y���W�ƂȂ��
#define OBJ_WIDTH		(220)		// �I�u�W�F�N�g�̉���
#define COLOR_RED		(255)		// �ԐF
#define COLOR_BULUE		(255)		// �F
#define COLOR_GREEN		(255)		// �ΐF
#define COLOR_ALPHA		(255)		// �A���t�@�l
#define POINT_X			(110)		// ���S���WX
#define POINT_Y			(80)		// ���S���WY

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureEneObjct = NULL;		//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEneObjct = NULL;	//���_�o�b�t�@�ւ̃|�C���^
ENEOBJCT g_EneObj[MAX_ENEOBJ];
float g_fpos[MAX_ENEOBJ];

//�I�u�W�F�N�g�̏���������
HRESULT InitEnObjct(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;			//VERTEX�̃|�C���^

	for (int nCounterEO = 0; nCounterEO < MAX_ENEOBJ; nCounterEO++)
	{
		g_EneObj[nCounterEO].fLife = 0;
		g_EneObj[nCounterEO].objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_EneObj[nCounterEO].EneOState = ENEMY_OBJ_NORMAL;
		g_fpos[nCounterEO] = 0.0f;
	}

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemyobj.png", &g_pTextureEneObjct);				

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEOBJ, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEneObjct, NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEneObjct->Lock(0, 0, (void**)&pVtx, 0);

	// �I�u�W�F�N�g�z�u
	for (int nCunObj = 0; nCunObj < MAX_ENEOBJ; nCunObj++)
	{
		if (nCunObj < ENEMY_OBJ)
		{
			pVtx[0].pos = D3DXVECTOR3((OBJ_ENEMY_X + (float)nCunObj * OBJ_WIDTH), OBJ_NEXT_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((OBJ_ENEMY_X + (float)nCunObj * OBJ_WIDTH), OBJ_ENEMY_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((OBJ_NEXT_X + (float)nCunObj * OBJ_WIDTH), OBJ_NEXT_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((OBJ_NEXT_X + (float)nCunObj * OBJ_WIDTH), OBJ_ENEMY_Y, 0.0f);

			g_EneObj[nCunObj].objpos = D3DXVECTOR3(((OBJ_ENEMY_X + POINT_X) + (float)nCunObj * OBJ_WIDTH), POINT_Y + OBJ_ENEMY_Y, 0.0f);
		}
		else if (nCunObj >= ENEMY_OBJ)
		{
			pVtx[0].pos = D3DXVECTOR3((OBJ_ENEMY_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3((OBJ_ENEMY_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_NEXT_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3((OBJ_NEXT_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3((OBJ_NEXT_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_NEXT_Y, 0.0f);

			g_EneObj[nCunObj].objpos = D3DXVECTOR3(((OBJ_ENEMY_X + POINT_X) + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y - POINT_Y , 0.0f);
		}

		//�e�N�X�`���̒��_���W
		pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//pVtx��4�i�߂�
		pVtx += 4;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEneObjct->Unlock();
	//S_OK��Ԃ�
	return S_OK;	
}

//�I�u�W�F�N�g�̏I������
void UninitEnObjct(void)
{
	if (g_pVtxBuffEneObjct != NULL)
	{
		g_pVtxBuffEneObjct->Release();
		g_pVtxBuffEneObjct = NULL;
	}
	if (g_pTextureEneObjct != NULL)
	{
		g_pTextureEneObjct->Release();
		g_pTextureEneObjct = NULL;
	}
}

//�I�u�W�F�N�g�̍X�V����
void UpdateEnObjct(void)
{
	VERTEX_2D *pVtx;			//VERTEX�̃|�C���^
	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEneObjct->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCunObj = 0; nCunObj < MAX_ENEOBJ; nCunObj++)
	{
		if (g_EneObj[nCunObj].EneOState == ENEMY_OBJ_NORMAL)
		{
			if (nCunObj < ENEMY_OBJ)
			{
				pVtx[0].pos = D3DXVECTOR3((OBJ_ENEMY_X + (float)nCunObj * OBJ_WIDTH), OBJ_NEXT_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3((OBJ_ENEMY_X + (float)nCunObj * OBJ_WIDTH), OBJ_ENEMY_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3((OBJ_NEXT_X + (float)nCunObj * OBJ_WIDTH), OBJ_NEXT_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3((OBJ_NEXT_X + (float)nCunObj * OBJ_WIDTH), OBJ_ENEMY_Y, 0.0f);

				g_EneObj[nCunObj].objpos = D3DXVECTOR3(((OBJ_ENEMY_X + POINT_X) + (float)nCunObj * OBJ_WIDTH), POINT_Y + OBJ_ENEMY_Y, 0.0f);
			}
			else if (nCunObj >= ENEMY_OBJ)
			{
				pVtx[0].pos = D3DXVECTOR3((OBJ_ENEMY_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y, 0.0f);
				pVtx[1].pos = D3DXVECTOR3((OBJ_ENEMY_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_NEXT_Y, 0.0f);
				pVtx[2].pos = D3DXVECTOR3((OBJ_NEXT_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y, 0.0f);
				pVtx[3].pos = D3DXVECTOR3((OBJ_NEXT_X + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_NEXT_Y, 0.0f);

				g_EneObj[nCunObj].objpos = D3DXVECTOR3(((OBJ_ENEMY_X + POINT_X) + ((float)nCunObj - MINUS_COUNT) * OBJ_WIDTH), SCREEN_HEIGHT - OBJ_ENEMY_Y - POINT_Y, 0.0f);
			}
			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
			pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

			//pVtx��4�i�߂�
			pVtx += 4;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEneObjct->Unlock();
}

//�I�u�W�F�N�g�̕`�揈��
void DrawEnObjct(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEneObjct, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, g_pTextureEneObjct);

	for (int nCunObj = 0; nCunObj < MAX_ENEOBJ; nCunObj++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunObj * 4, 2);
	}
}

bool HitEnObjct(float nDamage)
{
	return true;
}


//�I�u�W�F�N�g�̏��
ENEOBJCT *GetEnObjct(void)
{
	return &g_EneObj[0];
}
