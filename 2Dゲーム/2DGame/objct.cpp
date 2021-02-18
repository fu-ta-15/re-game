//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//


#include "objct.h"
#include "hp.h"

#define MAX_OBJ			(OBJTYPE_MAX)	//�I�u�W�F�N�g�̎��
#define MAX_ENEMYOBJ	(OBJTYPE_ENEMY)
#define OBJ__WARTER		(300)
#define OBJ_ENEMY_X		(300)
#define COLOR_RED		(255)			//�ԐF
#define COLOR_BULUE		(255)			//�F
#define COLOR_GREEN		(255)			//�ΐF
#define COLOR_ALPHA		(255)			//�A���t�@�l
#define POINT_X			(650)			//���S���WX
#define POINT_Y			(520)			//���S���WY


//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_apTextureObjct[MAX_OBJ] = {};	//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffObjct = NULL;		//���_�o�b�t�@�ւ̃|�C���^
OBJCT g_Obj;
int g_nCounter;

//�I�u�W�F�N�g�̏���������
HRESULT InitObjct(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�̃|�C���^
	VERTEX_2D *pVtx;			//VERTEX�̃|�C���^

	g_Obj.nDownLife = 0;
	g_Obj.objpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nCounter = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\01.png", &g_apTextureObjct[0]);				//�e�N�X�`���u��v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\life-obj.png", &g_apTextureObjct[1]);		//�e�N�X�`���uHP�I�u�W�F�N�g�v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\outelia.png", &g_apTextureObjct[2]);			//�e�N�X�`���u�����P�v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\outelia.png", &g_apTextureObjct[3]);			//�e�N�X�`���u�����Q�v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\outelia.png", &g_apTextureObjct[4]);			//�e�N�X�`���u�����R�v
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\outelia.png", &g_apTextureObjct[5]);			//�e�N�X�`���u�����S�v

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_OBJ, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffObjct, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffObjct->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunObj = 0; nCunObj < MAX_OBJ; nCunObj++)
	{
		if (nCunObj == OBJTYPE_CASTLE)
		{
			pVtx[0].pos = D3DXVECTOR3(540, 580, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(540, 380, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(740, 580, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(740, 380, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		else if (nCunObj == OBJTYPE_HPBAR)
		{
			pVtx[0].pos = D3DXVECTOR3(550, 470, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(550, 260, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(750, 470, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(750, 260, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0);

		}
		//-------------------------------------------------------------------------------------------------------------------------------------------------//
		//�����G���A�̐ݒ�
		//-------------------------------------------------------------------------------------------------------------------------------------------------//
		if (nCunObj == OBJTYPE_WATER1)
		{
			pVtx[0].pos = D3DXVECTOR3(0, OBJ__WARTER, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(OBJ__WARTER, OBJ__WARTER, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(OBJ__WARTER, 0, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f / 2, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / 2, 0);

		}
		else if (nCunObj == OBJTYPE_WATER2)
		{
			pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0, SCREEN_HEIGHT - OBJ__WARTER, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(OBJ__WARTER, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(OBJ__WARTER, SCREEN_HEIGHT - OBJ__WARTER, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f / 2, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / 2, 0);

		}
		else if (nCunObj == OBJTYPE_WATER3)
		{
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - OBJ__WARTER, SCREEN_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - OBJ__WARTER, SCREEN_HEIGHT - OBJ__WARTER, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT - OBJ__WARTER, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f / 2, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / 2, 0);

		}
		else if (nCunObj == OBJTYPE_WATER4)
		{
			pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - OBJ__WARTER, OBJ__WARTER, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH - OBJ__WARTER, 0, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, OBJ__WARTER, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

			//�e�N�X�`���̒��_���W
			pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(1.0f / 2, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f / 2, 0);

		}

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
	//�u��v�̒��S���W
	g_Obj.objpos = D3DXVECTOR3(POINT_X, POINT_Y, 0.0f);
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffObjct->Unlock();
	return S_OK;	//S_OK��Ԃ�
}

//�I�u�W�F�N�g�̏I������
void UninitObjct(void)
{
	if (g_pVtxBuffObjct != NULL)
	{
		g_pVtxBuffObjct->Release();
		g_pVtxBuffObjct = NULL;
	}

	for (int nCunObj = 0; nCunObj < MAX_OBJ; nCunObj++)
	{
		if (g_apTextureObjct[nCunObj] != NULL)
		{
			g_apTextureObjct[nCunObj]->Release();
			g_apTextureObjct[nCunObj] = NULL;
		}
	}
}

//�I�u�W�F�N�g�̍X�V����
void UpdateObjct(void) 
{

	VERTEX_2D *pVtx;			//VERTEX�̃|�C���^
	
	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffObjct->Lock(0, 0, (void**)&pVtx, 0);

	g_nCounter += 1;

	if ((g_nCounter % 60) == 0)
	{
		pVtx += (4 * OBJTYPE_WATER1);

		for (int nTexCounter = 2; nTexCounter < MAX_OBJ; nTexCounter++)
		{
			if (nTexCounter == OBJTYPE_WATER1 || nTexCounter == OBJTYPE_WATER2 || nTexCounter == OBJTYPE_WATER3 || nTexCounter == OBJTYPE_WATER4)
			{
				//�e�N�X�`���̒��_���W
				pVtx[0].tex = D3DXVECTOR2(1.0 / 2, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0 / 2, 0);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 1, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 1, 0);
			}
			pVtx += 4;
		}
	}
	else if ((g_nCounter % 110) == 0)
	{
		pVtx += (4 * OBJTYPE_WATER1);

		for (int nTexCounter = 2; nTexCounter < MAX_OBJ; nTexCounter++)
		{
			if (nTexCounter == OBJTYPE_WATER1 || nTexCounter == OBJTYPE_WATER2 || nTexCounter == OBJTYPE_WATER3 || nTexCounter == OBJTYPE_WATER4)
			{
				//�e�N�X�`���̒��_���W
				pVtx[0].tex = D3DXVECTOR2(0, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0, 0);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 2, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 2, 0);
			}
			pVtx += 4;
		}
		g_nCounter = 0;
	}
	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffObjct->Unlock();
}

//�I�u�W�F�N�g�̕`�揈��
void DrawObjct(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffObjct, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCunObj = 0; nCunObj < MAX_OBJ; nCunObj++)
	{
		pDevice->SetTexture(0, g_apTextureObjct[nCunObj]);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCunObj * 4, 2);
	}
}

bool HitObjct(float nDamage)
{
	g_Obj.nDownLife = nDamage;

	DownHp(g_Obj.nDownLife);
	return true;
}


//�I�u�W�F�N�g�̏��
OBJCT *GetObjct(void)
{
	return &g_Obj;
}
