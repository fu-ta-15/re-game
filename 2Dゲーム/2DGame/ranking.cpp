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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// �ԐF
#define COLOR_BULUE			(255)			// �F
#define COLOR_GREEN			(255)			// �ΐF
#define COLOR_ALPHA			(255)			// �A���t�@�l
#define RANKING_TEX			(8)				// �����L���O�̐�

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRanking = NULL;			// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureRankingBg = NULL;		// �e�N�X�`���̏��
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
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\scor.png", &g_pTextureRankingBg);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\number003.png", &g_pTextureRanking);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKING_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffRanking, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);

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
	pVtx[2].tex = D3DXVECTOR2(1, 1);
	pVtx[3].tex = D3DXVECTOR2(1, 0);

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCunt = 0; nCunt < 7; nCunt++)
	{
		pVtx += 4;
		
		if (nCunt < 3)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(200.0f + (nCunt * 50), SCREEN_HEIGHT / 3, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(200.0f + (nCunt * 50), 200.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(250.0f + (nCunt * 50), SCREEN_HEIGHT / 3, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(250.0f + (nCunt * 50), 200.0f, 0.0f);
		}
		else if (nCunt >= 3 && nCunt < 7)
		{
			//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
			pVtx[0].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 580.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(50.0f + (nCunt * 50), 460.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 580.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(100.0f + (nCunt * 50), 460.0f, 0.0f);
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
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffRanking->Unlock();

	// �ߋ��̋L�^�̕ۑ�
	OldRankingScore();

	PlaySound(SOUND_LABEL_BGM002);



	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitRanking(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureRankingBg != NULL)
	{
		g_pTextureRankingBg->Release();
		g_pTextureRankingBg = NULL;
	}
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
	StopSound(SOUND_LABEL_BGM002);	//BGM
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
	int aNumber[7];			
	if (pFade == FADE_NONE)
	{//�t�F�C�h���I�������
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			SetFade(FADE_OUT, MODE_RESULT);
		}
	}
	//�o�b�t�@�̃��b�N
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);
	//�X�R�A�v�Z
	int nMath = 1000;		
	// �ŋ߂̃X�R�A
	g_RScore.NewScore = GetScore();
	//�X�R�A�̕ύX
	for (int nCunNum = 1; nCunNum < 4; nCunNum++)
	{
		//�X�R�A�̌v�Z
		aNumber[nCunNum] = (g_RScore.NewScore%nMath / (nMath / 10));
		//�e�N�X�`�����W
		pVtx[4].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[5].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[6].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//����10�����Ď��̌���

		pVtx += 4;		//�|�C���^���W���l�i�߂�
	}

	//�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

	//�o�b�t�@�̃��b�N
	g_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

	nMath = 1000;		//�X�R�A�v�Z

	//�X�R�A�̕ύX
	for (int nCunNum = 4; nCunNum < 7; nCunNum++)
	{
		//�X�R�A�̌v�Z
		aNumber[nCunNum] = (g_RScore.OldScore%nMath / (nMath / 10));

		//�e�N�X�`�����W
		pVtx[16].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 1.0f);
		pVtx[17].tex = D3DXVECTOR2((float)aNumber[nCunNum] / 10, 0);
		pVtx[18].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 1.0f);
		pVtx[19].tex = D3DXVECTOR2(((float)aNumber[nCunNum] / 10) + 0.1f, 0);

		nMath /= 10;	//����10�����Ď��̌���

		pVtx += 4;		//�|�C���^���W���l�i�߂�
	}

	//�o�b�t�@�̃A�����b�N
	g_pVtxBuffRanking->Unlock();

	if (g_RScore.NewScore > g_RScore.OldScore)
	{
		FILE *pFile;
		pFile = fopen("ranking.txt", "w");
		if (pFile != NULL)
		{
			fprintf(pFile, "%d", g_RScore.NewScore);
			fclose(pFile);
		}
		else
		{

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

	for (int nCunt = 0; nCunt < 2; nCunt++)
	{
		if (nCunt == 0)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureRankingBg);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
		else if (nCunt == 1)
		{
			for (int nScor = nCunt; nScor < 7; nScor++)
			{
				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureRanking);
				//�|���S���̕`��
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nScor * 4, 2);
			}
		}
	}
}

void OldRankingScore(void)
{
	FILE *pFile;
	pFile = fopen("ranking.txt", "r");
	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &g_RScore.OldScore);
		fclose(pFile);
	}
	else
	{

	}
}
