//##################################################################################################################################################################//
//
// UI���� [ui.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "ui.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define COLOR_RED			(255)			// �ԐF
#define COLOR_BULUE			(255)			// �F
#define COLOR_GREEN			(255)			// �ΐF
#define COLOR_ALPHA			(255)			// �A���t�@�l

#define UI_HEIGHT_UP		(0)				// UI�w�i��POS
#define UI_HEIGHT_DOWN		(350)			// UI�w�i��POS
#define UI_WIDTH_RIGHT		(SCREEN_WIDTH)	// UI�w�i��POS
#define UI_WIDTH_LEFT		(980)			// UI�w�i��POS

#define P_HEIGHT_UP			(10)			// Perfect��UI��POS
#define P_HEIGHT_DOWN		(55)			// Perfect��UI��POS
#define P_WIDTH_RIGHT		(1160)			// Perfect��UI��POS
#define P_WIDTH_LEFT		(1000)			// Perfect��UI��POS

#define G_HEIGHT_UP			(90)			// Good��UI��POS
#define G_HEIGHT_DOWN		(130)			// Good��UI��POS
#define G_WIDTH_RIGHT		(1150)			// Good��UI��POS
#define G_WIDTH_LEFT		(1000)			// Good��UI��POS

#define B_HEIGHT_UP			(170)			// Bad��UI��POS
#define B_HEIGHT_DOWN		(200)			// Bad��UI��POS
#define B_WIDTH_RIGHT		(1180)			// Bad��UI��POS
#define B_WIDTH_LEFT		(1000)			// Bad��UI��POS

#define S_HEIGHT_UP			(270)			// Score��UI��POS
#define S_HEIGHT_DOWN		(295)			// Score��UI��POS
#define S_WIDTH_RIGHT		(1080)			// Score��UI��POS
#define S_WIDTH_LEFT		(1030)			// Score��UI��POS

#define MAX_UI_NUM			(5)				// UI�̐�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffUi = NULL;		// ���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureUi = NULL;				// �e�N�X�`���̏��
LPDIRECT3DTEXTURE9 g_pTextureUiPerfect = NULL;		// �e�N�X�`���̏��
LPDIRECT3DTEXTURE9 g_pTextureUiGood = NULL;			// �e�N�X�`���̏��
LPDIRECT3DTEXTURE9 g_pTextureUiBad = NULL;			// �e�N�X�`���̏��
LPDIRECT3DTEXTURE9 g_pTextureUiScore = NULL;		// �e�N�X�`���̏��

//=====================================================================================================================================================================//
// �w�i�̏���������
//=====================================================================================================================================================================//
HRESULT InitUi(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	// ���_�|�C���^
	VERTEX_2D *pVtx;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\UI.png", &g_pTextureUi);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi02.png", &g_pTextureUiPerfect);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi01.png", &g_pTextureUiGood);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\mozi00.png", &g_pTextureUiBad);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\Score00.png", &g_pTextureUiScore);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_UI_NUM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffUi, NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N�E���_���ւ̃|�C���^���擾
	g_pVtxBuffUi->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�(X���W�EY���W�EZ���W(2D��0�Œ�)�E���ŕ`��j
	/* UI�̔w�i */
	pVtx[0].pos = D3DXVECTOR3(UI_WIDTH_LEFT, UI_HEIGHT_DOWN, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(UI_WIDTH_LEFT, UI_HEIGHT_UP, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(UI_WIDTH_RIGHT, UI_HEIGHT_DOWN, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(UI_WIDTH_RIGHT, UI_HEIGHT_UP, 0.0f);
	/* Perfect�̕��� */
	pVtx[4].pos = D3DXVECTOR3(P_WIDTH_LEFT, P_HEIGHT_DOWN, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(P_WIDTH_LEFT, P_HEIGHT_UP, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(P_WIDTH_RIGHT, P_HEIGHT_DOWN, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(P_WIDTH_RIGHT, P_HEIGHT_UP, 0.0f);
	/* Good�̕��� */
	pVtx[8].pos = D3DXVECTOR3(G_WIDTH_LEFT, G_HEIGHT_DOWN, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(G_WIDTH_LEFT, G_HEIGHT_UP, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(G_WIDTH_RIGHT, G_HEIGHT_DOWN, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(G_WIDTH_RIGHT, G_HEIGHT_UP, 0.0f);
	/* Bad�̕��� */
	pVtx[12].pos = D3DXVECTOR3(B_WIDTH_LEFT, B_HEIGHT_DOWN, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(B_WIDTH_LEFT, B_HEIGHT_UP, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(B_WIDTH_RIGHT, B_HEIGHT_DOWN, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(B_WIDTH_RIGHT, B_HEIGHT_UP, 0.0f);
	/* Score�̕��� */
	pVtx[16].pos = D3DXVECTOR3(S_WIDTH_LEFT, S_HEIGHT_DOWN, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(S_WIDTH_LEFT, S_HEIGHT_UP, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(S_WIDTH_RIGHT, S_HEIGHT_DOWN, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(S_WIDTH_RIGHT, S_HEIGHT_UP, 0.0f);

	for (int nCnt = 0; nCnt < MAX_UI_NUM; nCnt++)
	{
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
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_���X�V
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffUi->Unlock();

	// ��������
	return S_OK;
}

//=====================================================================================================================================================================//
// �|���S���̏I������
//=====================================================================================================================================================================//
void UninitUi(void)
{
	if (g_pTextureUi != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureUi->Release();
		g_pTextureUi = NULL;
	}
	if (g_pTextureUiPerfect != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureUiPerfect->Release();
		g_pTextureUiPerfect = NULL;
	}
	if (g_pTextureUiGood != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureUiGood->Release();
		g_pTextureUiGood = NULL;
	}
	if (g_pTextureUiBad != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureUiBad->Release();
		g_pTextureUiBad = NULL;
	}
	if (g_pTextureUiScore != NULL)
	{// �e�N�X�`���̊J��
		g_pTextureUiScore->Release();
		g_pTextureUiScore = NULL;
	}

	if (g_pVtxBuffUi != NULL)
	{// ���_�o�b�t�@�̊J��
		g_pVtxBuffUi->Release();
		g_pVtxBuffUi = NULL;
	}
}

//=====================================================================================================================================================================//
// �|���S���̍X�V����
//=====================================================================================================================================================================//
void UpdateUi(void)
{

}

//=====================================================================================================================================================================//
// �|���S���̕`�揈��
//=====================================================================================================================================================================//
void DrawUi(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffUi, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUi);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUiPerfect);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUiGood);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 8, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUiBad);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 12, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureUiScore);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 16, 2);
}