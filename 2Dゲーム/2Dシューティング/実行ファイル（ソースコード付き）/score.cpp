//##################################################################################################################################################################//
//
// �X�R�A���� [score.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "score.h"
#include "ranking.h"
#include <stdlib.h>
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MAX_SCORE	(3)
#define SCORE_STZEX	(580)
#define SCORE_SIZEY	(630)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_pTextureScore = NULL;;		//�e�N�X�`���ւ̃|�C���g
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int g_nScore;

//����������
HRESULT InitScore(void)
{
	srand((unsigned int)time(0));
	LPDIRECT3DDEVICE9 pDevice;
	VERTEX_2D *pVtx;

	//�ϐ��̏�����
	g_nScore = 0;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number002.png", &g_pTextureScore);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�|���S���E�e�N�X�`���̏������ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_SCORE; nCntBullet++)
	{

		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(SCORE_STZEX + ((float)nCntBullet * 50), SCREEN_HEIGHT-10, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCORE_STZEX + ((float)nCntBullet * 50), SCREEN_HEIGHT-110, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(SCORE_SIZEY + ((float)nCntBullet * 50), SCREEN_HEIGHT-10, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCORE_SIZEY + ((float)nCntBullet * 50), SCREEN_HEIGHT-110, 0.0f);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(125, 10, 125, 225);
		pVtx[1].col = D3DCOLOR_RGBA(125, 10, 125, 225);
		pVtx[2].col = D3DCOLOR_RGBA(125, 10, 125, 225);
		pVtx[3].col = D3DCOLOR_RGBA(125, 10, 125, 225);

		//���_4�i�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffScore->Unlock();

	AddScore(0);

	return S_OK;
}

//�I������
void UninitScore(void)
{
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}

	//�e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}


}

//�X�V����
void UpdateScore(void)
{

}

//�`�揈��
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	for (int nCntEnemy = 0; nCntEnemy < MAX_SCORE; nCntEnemy++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
	}

}

//�X�R�A�̉��Z
void AddScore(int nValue)
{
	int nMath = 1000;		//�X�R�A�v�Z
	int aNumber[MAX_SCORE];	//�X�R�A�̃i���o�[
	g_nScore += nValue;		//�X�R�A
	VERTEX_2D *pVtx;		//�|�C���^

	//�o�b�t�@�̃��b�N
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	//�X�R�A�̕ύX
	for (int nCunNum = 0; nCunNum < MAX_SCORE; nCunNum++)
	{
		//�X�R�A�̌v�Z
		aNumber[nCunNum] = (g_nScore%nMath / (nMath / 10));

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		pVtx += 4;		//�|�C���^���W���l�i�߂�
		nMath /= 10;	//����10�����Ď��̌���
	}

	//�o�b�t�@�̃A�����b�N
	g_pVtxBuffScore->Unlock();

}

int GetScore(void)
{
	return g_nScore;
}