//##################################################################################################################################################################//
//
// �e���� [bullet.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bullet.h"
#include "model.h"
#include "particle.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define BULLET_SIZE						(2.0f)							// �e�̃T�C�Y
#define COLOR_RED						(255)						// �ԐF
#define COLOR_BULUE						(255)						// �F
#define COLOR_GREEN						(255)						// �ΐF
#define COLOR_ALPHA						(255)						// �A���t�@�l
#define RHW								(10/10)						// rhw�̐��l1.0�Œ�
#define HALF_MATH						(2)							// ����
#define PVTEX_MAX						(4)							// pVtx

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureBullet = NULL;		// �e�N�X�`���̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�̏��
BULLET g_aBullet[MAX_BULLET];						// �e�̏��


//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^
	BULLET *pBullet = &g_aBullet[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureBullet);

	if (g_apTextureBullet == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\bullet000.png");
	}

	// �e�̏������ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		pBullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pBullet->BulletSize = BULLET_SIZE;
		pBullet->nLife = 0;
		pBullet->bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		// �e���_���W
		pVtx[0].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->BulletSize, pBullet->pos.y + pBullet->BulletSize, pBullet->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->BulletSize, pBullet->pos.y + pBullet->BulletSize, pBullet->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pBullet->pos.x - pBullet->BulletSize, pBullet->pos.y - pBullet->BulletSize, pBullet->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pBullet->pos.x + pBullet->BulletSize, pBullet->pos.y - pBullet->BulletSize, pBullet->pos.z);

		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�̐ݒ�E�ԁE�΁E��
		pVtx[0].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[1].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[2].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);
		pVtx[3].col = D3DCOLOR_RGBA(COLOR_RED, COLOR_GREEN, COLOR_BULUE, COLOR_ALPHA);

		// �e�N�X�`���̒��_���W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// �v���X4�i�߂�
		pVtx += PVTEX_MAX;
	}

	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	if (g_apTextureBullet != NULL)
	{
		g_apTextureBullet->Release();
		g_apTextureBullet = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateBullet(void)
{
	// �\���̂̃|�C���^
	VERTEX_3D *pVtx;
	BULLET *pBullet;
	Player *pPlayer = GetPlayer();


	// �\���̂̏��擾
	pBullet = &g_aBullet[0];

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			// �ʒu�̍X�V
			pBullet->pos.z -= pBullet->move.z * 2.5f;
			pBullet->pos.x += pBullet->move.x * 2.5f;
			pBullet->pos.y = pPlayer->aModel[0].pos.y + pPlayer->pos.y;

			// ���C�t�̌���
			pBullet->nLife -= 2;

			// �����`�F�b�N
			if (pBullet->nLife == 0)
			{
				// 0�ɂȂ�����t�H���X�ɕς���
				pBullet->bUse = false;
			}
		}
		// 4���_�������
		pVtx += PVTEX_MAX;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawBullet(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;

	BULLET *pBullet = &g_aBullet[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == true)
		{
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pBullet->mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pBullet->mtxWorld, NULL, &mtxView); // �t�s������߂�

			pBullet->mtxWorld._41 = 0.0f;
			pBullet->mtxWorld._42 = 0.0f;
			pBullet->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pBullet->pos.x, pBullet->pos.y, pBullet->pos.z);
			D3DXMatrixMultiply(&pBullet->mtxWorld, &pBullet->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBullet->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBullet);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

		}
	}
}

//=====================================================================================================================================================================//
// �e�̐ݒ菈��
//=====================================================================================================================================================================//
void SetBullet(D3DXVECTOR3 pos, float movex, float movez, int nLife)
{
	//�|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	BULLET *pBullet = &g_aBullet[0];
	Player *pPlayer = GetPlayer();


	//�e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{//�g�p����Ă��Ȃ��e

			// �ʒu�̐ݒ�
			pBullet->pos.x = pos.x - sinf(pPlayer->rot.y) * 10.0f;
			pBullet->pos.z = pos.z - cosf(pPlayer->rot.y) * 10.0f;
			pBullet->pos.y = pos.y + 2.0f;

			// �ړ��̐ݒ�
			pBullet->move.z = movez;
			pBullet->move.x = movex;

			// �����̐ݒ�
			pBullet->nLife = nLife;

			// �e�𔭎�
			pBullet->bUse = true;

			SetParticle(pos, D3DXVECTOR3(movex,0.0f, movez), 10, 50, D3DXCOLOR(0.37f, 0.28f, 0.78f, 1.0f));

			break;
		}
		pVtx += PVTEX_MAX;	// ���_����4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBullet->Unlock();


}

BULLET * GetBullet(void)
{
	return &g_aBullet[0];
}
