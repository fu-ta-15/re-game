//##################################################################################################################################################################//
//
// �X�R�A���� [score.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "stock.h"
#include "ranking.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_STOCK					(6)

#define POS_DINTANCE				(30)

#define PERFECT_POS_LEFT			(1100)
#define PERFECT_POS_RIGHT			(1140)
#define PERFECT_POS_UP				(50)
#define PERFECT_POS_DOWN			(80)

#define GOOD_POS_LEFT				(1100)
#define GOOD_POS_RIGHT				(1140)
#define GOOD_POS_UP					(130)
#define GOOD_POS_DOWN				(160)

#define BAD_POS_LEFT				(1100)
#define BAD_POS_RIGHT				(1140)
#define BAD_POS_UP					(205)
#define BAD_POS_DOWN				(235)

#define STOCK_TAKARA				(2)
#define STOCK_ATTACK				(4)
#define STOCK_BLOCK					(6)

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureStock = NULL;;			// �e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStock = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int g_nStock;										// �X�g�b�N�̕ۑ��p
STOCK g_Stock[STOCK_TYPE_MAX];						// �X�g�b�N�̍\����

//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitStock(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntStock = 0; nCntStock < STOCK_TYPE_MAX; nCntStock++)
	{// �X�g�b�N�̒��g������
		g_Stock[nCntStock].nStock = 0;
	}

	// �ϐ��̏�����
	g_nStock = 0;
	srand((unsigned int)time(0));

	//�@�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cunt00.png", &g_pTextureStock);

	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStock, NULL)))
	{// ���_�o�b�t�@�̐���
		return E_FAIL;
	}

	//�@�|���S���E�e�N�X�`���̏������ݒ�
	for (int nCntStock = 0; nCntStock < STOCK_TYPE_MAX; nCntStock++)
	{
		// �w��̈ʒu�ɃZ�b�g
		pVtxSet(nCntStock);
	}

	// �e�X�g�b�N�̏�����
	AddStock(0, 0);
	AddStock(0, 1);
	AddStock(0, 2);

	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitStock(void)
{
	//�@���_�o�b�t�@�̊J��
	if (g_pVtxBuffStock != NULL)
	{
		g_pVtxBuffStock->Release();
		g_pVtxBuffStock = NULL;
	}

	//�@�e�N�X�`���̊J��
	if (g_pTextureStock != NULL)
	{
		g_pTextureStock->Release();
		g_pTextureStock = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateStock(void)
{


}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawStock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�@�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�@���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStock, 0, sizeof(VERTEX_2D));

	//�@���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�@�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStock);

	for (int nCntStock = 0; nCntStock < MAX_STOCK; nCntStock++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntStock * 4, 2);
	}
}

//=====================================================================================================================================================================//
// �X�g�b�N�̉��Z
//=====================================================================================================================================================================//
void AddStock(int nValue, int Type)
{
	int nMath = 100;	//�@�X�R�A�v�Z

	int aNumber[2];	//�@�X�R�A�̃i���o�[

	g_Stock[Type].nStock += nValue;		//�@�X�R�A

	VERTEX_2D *pVtx;		//�@�|�C���^

	switch (Type)
	{
	case STOCK_TYPE_PERFECT:	// PERFECT�̕]��
		//�@�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//�@�X�R�A�̌v�Z
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_PERFECT].nStock % nMath / (nMath / 10));

			//�@�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//�@�|�C���^���W���l�i�߂�
			nMath /= 10;	//�@����10�����Ď��̌���
		}
		//�@�o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();
		break;

	case STOCK_TYPE_GOOD:	// GOOD�̕]��
		//�@�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//�@�X�R�A�̌v�Z
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_GOOD].nStock % nMath / (nMath / 10));

			//�@�e�N�X�`�����W
			pVtx[8].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[9].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[10].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[11].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//�@�|�C���^���W���l�i�߂�
			nMath /= 10;	// ����10�����Ď��̌���
		}
		// �o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();
		break;

	case STOCK_TYPE_BAD:	// BAD�̕]��
		//�@�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++)
		{
			//�@�X�R�A�̌v�Z
			aNumber[nCntStock] = (g_Stock[STOCK_TYPE_BAD].nStock % nMath / (nMath / 10));

			//�@�e�N�X�`�����W
			pVtx[16].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 1.0f);
			pVtx[17].tex = D3DXVECTOR2((float)aNumber[nCntStock] / 10.0f, 0);
			pVtx[18].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 1.0f);
			pVtx[19].tex = D3DXVECTOR2(((float)aNumber[nCntStock] / 10.0f) + 0.1f, 0);

			pVtx += 4;		//�@�|�C���^���W���l�i�߂�
			nMath /= 10;	//�@����10�����Ď��̌���
		}
		//�@�o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();
		break;

	default:
		break;
	}
}


//=====================================================================================================================================================================//
// �e�N�X�`���̃Z�b�g
//=====================================================================================================================================================================//
void pVtxSet(int Num)
{
	// ���_�̃|�C���^
	VERTEX_2D *pVtx;
	// �e�N�X�`���Ƃ̌���
	int nDice = 0;

	switch (Num)
	{
	case STOCK_TYPE_PERFECT:
		//���_�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{
			//�e���_���W
			pVtx[0].pos = D3DXVECTOR3(PERFECT_POS_LEFT + ((float)nDice * POS_DINTANCE), PERFECT_POS_DOWN, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PERFECT_POS_LEFT + ((float)nDice * POS_DINTANCE), PERFECT_POS_UP, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PERFECT_POS_RIGHT + ((float)nDice * POS_DINTANCE), PERFECT_POS_DOWN, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PERFECT_POS_RIGHT + ((float)nDice * POS_DINTANCE), PERFECT_POS_UP, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`���̒��_���W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0, 1);
			pVtx[1].tex = D3DXVECTOR2(0, 0);
			pVtx[2].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

			//���_4�i�߂�
			pVtx += 4;
		}
		break;
		//�o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();

	case STOCK_TYPE_GOOD:
		//���_�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{

			//�e���_���W
			pVtx[8].pos = D3DXVECTOR3(GOOD_POS_LEFT + ((float)nDice * POS_DINTANCE), GOOD_POS_DOWN, 0.0f);
			pVtx[9].pos = D3DXVECTOR3(GOOD_POS_LEFT + ((float)nDice * POS_DINTANCE), GOOD_POS_UP, 0.0f);
			pVtx[10].pos = D3DXVECTOR3(GOOD_POS_RIGHT + ((float)nDice * POS_DINTANCE), GOOD_POS_DOWN, 0.0f);
			pVtx[11].pos = D3DXVECTOR3(GOOD_POS_RIGHT + ((float)nDice * POS_DINTANCE), GOOD_POS_UP, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[8].rhw = 1.0f;
			pVtx[9].rhw = 1.0f;
			pVtx[10].rhw = 1.0f;
			pVtx[11].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[8].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[9].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[10].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[11].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`���̒��_���W�̐ݒ�
			pVtx[8].tex = D3DXVECTOR2(0, 1);
			pVtx[9].tex = D3DXVECTOR2(0, 0);
			pVtx[10].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[11].tex = D3DXVECTOR2(0.1f, 0);

			//���_4�i�߂�
			pVtx += (4);
		}
		break;
		//�o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();

	case STOCK_TYPE_BAD:
		//���_�o�b�t�@�̃��b�N
		g_pVtxBuffStock->Lock(0, 0, (void**)&pVtx, 0);
		for (int nCntStock = 0; nCntStock < STOCK_TAKARA; nCntStock++, nDice++)
		{
			//�e���_���W
			pVtx[16].pos = D3DXVECTOR3(BAD_POS_LEFT + ((float)nDice * POS_DINTANCE), BAD_POS_DOWN, 0.0f);
			pVtx[17].pos = D3DXVECTOR3(BAD_POS_LEFT + ((float)nDice * POS_DINTANCE), BAD_POS_UP, 0.0f);
			pVtx[18].pos = D3DXVECTOR3(BAD_POS_RIGHT + ((float)nDice * POS_DINTANCE), BAD_POS_DOWN, 0.0f);
			pVtx[19].pos = D3DXVECTOR3(BAD_POS_RIGHT + ((float)nDice * POS_DINTANCE), BAD_POS_UP, 0.0f);

			//rhw�̐ݒ�		=	1.0f�Œ�
			pVtx[16].rhw = 1.0f;
			pVtx[17].rhw = 1.0f;
			pVtx[18].rhw = 1.0f;
			pVtx[19].rhw = 1.0f;

			//���_�J���[�̐ݒ�E�ԁE�΁E��
			pVtx[16].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[17].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[18].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[19].col = D3DCOLOR_RGBA(255, 255, 255, 255);

			//�e�N�X�`���̒��_���W�̐ݒ�
			pVtx[16].tex = D3DXVECTOR2(0, 1);
			pVtx[17].tex = D3DXVECTOR2(0, 0);
			pVtx[18].tex = D3DXVECTOR2(0.1f, 1);
			pVtx[19].tex = D3DXVECTOR2(0.1f, 0);

			//���_4�i�߂�
			pVtx += (4);
		}
		break;
		//�o�b�t�@�̃A�����b�N
		g_pVtxBuffStock->Unlock();

	default:
		break;
	}
}

//=====================================================================================================================================================================//
// �X�g�b�N�̏��
//=====================================================================================================================================================================//
STOCK *GetStock(void)
{
	return &g_Stock[0];
}