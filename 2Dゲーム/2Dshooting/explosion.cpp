//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#include "explosion.h"
#include "player.h"
#include "input.h"
#include "enemy.h"

//�}�N����`
#define MAX_EXPLOSION		(256)
#define EXPLOSION_SIZE_XY	(50)
#define EXPLOSION_ANINM		(1/8)
#define COLOR_RED		(100)
#define COLOR_BULUE		(130)
#define COLOR_GREEN		(10)

//�e�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXCOLOR color;
	bool bUse;			//�g�p���Ă��邩�ǂ���
}EXPLOSION;

//�O���[�o���錾
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;
EXPLOSION g_aExplosion[MAX_EXPLOSION];
int g_fAnim = 0;
int g_fPaternAnim[MAX_EXPLOSION];
float g_fSizeExp;

//����������
HRESULT InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\explosion000.png", &g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].bUse = false;
		g_fPaternAnim[nCntExplosion] = 0;
	}
	g_fSizeExp = EXPLOSION_SIZE_XY;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffExplosion, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//�e���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp / 2, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp / 2, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp / 2, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp / 2, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp / 2, 0.0f);

		//rhw�̐ݒ�		=	1.0f�Œ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 225);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 225);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 225);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, 225);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f / 8, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f / 8, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();


	return S_OK;
}

//�I������
void UninitExplosion(void)
{
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}

	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//�X�V����
void UpdateExplosion(void)
{
	EXPLOSION *pExplosion;
	PLAYER *pPlayer;
	ENEMY *pEnemy;
	VERTEX_2D *pVtx;
	pExplosion = &g_aExplosion[0];
	pEnemy = GetEnemy();
	pPlayer = GetPlayer();

	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	g_fAnim++;


	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			if ((g_fAnim % 4) == 0)
			{
				if ((g_fPaternAnim[nCntExplosion] + 1) % 7 == 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
				g_fPaternAnim[nCntExplosion] = (g_fPaternAnim[nCntExplosion] + 1) % 8;
			}
				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp, 0.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion])), 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + (1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion])), 0);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion] + 1), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion] + 1), 0);
		}
		//��ʊO�`�F�b�N
		if (g_aExplosion[nCntExplosion].pos.y - EXPLOSION_SIZE_XY / 2 < 0)
		{//�e���������̉�ʊO�ɏo���ꍇ
			g_aExplosion[nCntExplosion].bUse = false;
		}
		pVtx += 4;	//4���_�������
	}
	g_pVtxBuffExplosion->Unlock();
}

//�`�揈��
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntExplosion * 4, 2);
		}
	}
}

//�e�̐ݒ菈��
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR color)
{
	VERTEX_2D *pVtx;
	PLAYER *pPlayer;
	ENEMY *pEnemy;
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	pEnemy = GetEnemy();
	pPlayer = GetPlayer();
	g_aExplosion[0];
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			//�ʒu�̐ݒ�
			g_aExplosion[nCntExplosion].pos.x = pos.x;
			g_aExplosion[nCntExplosion].pos.y = pos.y;
			//�F�̐ݒ�
			g_aExplosion[nCntExplosion].color = color;

			if (pPlayer->bSkills != true)
			{
				g_fSizeExp = 25;

				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - g_fSizeExp, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp, g_aExplosion[nCntExplosion].pos.y + g_fSizeExp, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + g_fSizeExp, g_aExplosion[nCntExplosion].pos.y - g_fSizeExp, 0.0f);

				//�e�N�X�`�����W
				pVtx[0].tex = D3DXVECTOR2(0.0f + (1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion])), 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f + (1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion])), 0);
				pVtx[2].tex = D3DXVECTOR2(1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion] + 1), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f / 8 * ((float)g_fPaternAnim[nCntExplosion] + 1), 0);

			}

			pVtx[0].col = g_aExplosion[nCntExplosion].color;
			pVtx[1].col = g_aExplosion[nCntExplosion].color;
			pVtx[2].col = g_aExplosion[nCntExplosion].color;
			pVtx[3].col = g_aExplosion[nCntExplosion].color;
			
			g_aExplosion[nCntExplosion].bUse = true;
			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffExplosion->Unlock();
}