//##################################################################################################################################################################//
//
// �����L���O���� [ranking.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define _CRT_SECURE_NO_WARNINGS
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "score.h"
#include "stdio.h"
#include "sound.h"
#include "padinput.h"
#include "rankingbg.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// �ԐF
#define COLOR_BULUE			(255)			// �F
#define COLOR_GREEN			(255)			// �ΐF
#define COLOR_ALPHA			(255)			// �A���t�@�l
#define RANKING_TEX			(12)				// �����L���O�̐�
#define RANKING_TEX_HERF	(12/2)				// �����L���O�̐�

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureRanking = NULL;		// �e�N�X�`���̏��
RANKING_SCORE g_RScore;


//=====================================================================================================================================================================//
// �w�i�̏���������
//=====================================================================================================================================================================//
HRESULT InitRanking(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�|�C���^
	VERTEX_2D *pVtx;

	// �\���̂̕ϐ�������
	g_RScore.ChangScore = 0;
	g_RScore.NewScore = 0;
	g_RScore.OldScore = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\cunt00.png", &g_pTextureRanking);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL)))
	{
		return E_FAIL;
	}

	////���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	//g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	////���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	//pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

	////rhw�̐ݒ�		=	1.0f�Œ�
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	//// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
	//pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
	//pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

	////�e�N�X�`���̒��_���W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0, 1);
	//pVtx[1].tex = D3DXVECTOR2(0, 0);
	//pVtx[2].tex = D3DXVECTOR2(1, 1);
	//pVtx[3].tex = D3DXVECTOR2(1, 0);

	////���_�o�b�t�@���A�����b�N
	//g_pVtxBuffRanking->Unlock();

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunt = 0; nCunt < RANKING_TEX; nCunt++)
	{
		if (nCunt < RANKING_TEX_HERF)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(300.0f + (nCunt * 50), SCREEN_HEIGHT / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(300.0f + (nCunt * 50), 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(350.0f + (nCunt * 50), SCREEN_HEIGHT / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(350.0f + (nCunt * 50), 200.0f, 0.0f);
		}
		else if (nCunt >= RANKING_TEX_HERF)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 600.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 500.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 600.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 500.0f, 0.0f);
		}

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�E�ԁE�΁E�E�A���t�@
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		//�e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0, 1);
		pVtx[1].tex = D3DXVECTOR2(0, 0);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();

	// �ߋ��̋L�^�̕ۑ�
	OldRankingScore();

	//PlaySound(SOUND_LABEL_BGM004);

	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitRanking(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureRanking != NULL)
	{
		g_pTextureRanking->Release();
		g_pTextureRanking = NULL;
	}
	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffRanking != NULL)
	{
		g_pVtxBuffRanking->Release();
		g_pVtxBuffRanking = NULL;
	}

	StopSound(SOUND_LABEL_BGM004);	//BGM
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateRanking(void)
{
	//�|�C���^
	VERTEX_2D *pVtx;
	FADE pFade;
	pFade = GetFade();
	//�X�R�A�̃i���o�[
	int aNumber[RANKING_TEX];

	if (pFade == FADE_NONE)
	{//�t�F�C�h���I�������
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}

	//�o�b�t�@�̃��b�N
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//�X�R�A�v�Z
	int nMath = 1000000;

	// �ŋ߂̃X�R�A
	g_RScore.NewScore = GetScore();

	//�X�R�A�̕ύX
	for (int nCunNum = 0; nCunNum < 6; nCunNum++)
	{
		//�X�R�A�̌v�Z
		aNumber[nCunNum] = (g_RScore.NewScore % nMath / (nMath / 10));

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//����10�����Ď��̌���

		pVtx += 4;		//�|�C���^���W���l�i�߂�
	}

	nMath = 1000000;		//�X�R�A�v�Z

	//�X�R�A�̕ύX
	for (int nCunNum = 6; nCunNum < RANKING_TEX; nCunNum++)
	{

		//�X�R�A�̌v�Z
		aNumber[nCunNum] = (g_RScore.OldScore%nMath / (nMath / 10));

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[1].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[2].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//����10�����Ď��̌���

		pVtx += 4; 		//�|�C���^���W���l�i�߂�

	}

	//�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

	if (g_RScore.NewScore > g_RScore.OldScore)
	{// �V�L�^�X�V
		FILE *pFile;
		pFile = fopen("ranking.txt", "w");
		if (pFile != NULL)
		{// ��������
			fprintf(pFile, "%d", g_RScore.NewScore);
			fclose(pFile);
		}
	}
}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawRanking(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nScor = 0; nScor < RANKING_TEX; nScor++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRanking);
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nScor * 4, 2);
	}
}
// �ߋ��̃X�R�A�̓ǂݍ���
void OldRankingScore(void)
{
	// �t�@�C���̃|�C���^
	FILE *pFile;
	// �ǂݍ��݃��[�h
	pFile = fopen("ranking.txt", "r");

	if (pFile != NULL)
	{// �L�^��ǂݍ���
		fscanf(pFile, "%d", &g_RScore.OldScore);
		fclose(pFile);
	}
}
