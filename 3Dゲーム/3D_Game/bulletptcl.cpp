//##################################################################################################################################################################//
//
// �e���� [bullet.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "bulletptcl.h"
#include "model.h"


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define BULLET_SIZE						(4.0f)						// �e�̃T�C�Y
#define COLOR_RED						(255)						// �ԐF
#define COLOR_BULUE						(255)						// �F
#define COLOR_GREEN						(255)						// �ΐF
#define COLOR_ALPHA						(255)						// �A���t�@�l
#define PVTEX_MAX						(4)							// pVtx
#define MAX_BULLETPTCL					(1000)						// �e�̍ő吔


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureBulletp = NULL;		// �e�N�X�`���̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBulletp = NULL;	// ���_�o�b�t�@�̏��
BParticle g_aBulletPtcl[MAX_BULLETPTCL];			// �e�̏��


//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitBulletPT(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^
	BParticle *pBulletPtcl = &g_aBulletPtcl[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_apTextureBulletp);

	if (g_apTextureBulletp == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\bullet000.png");
	}

	// �e�̏������ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		pBulletPtcl->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBulletPtcl->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBulletPtcl->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		pBulletPtcl->BulletSize = BULLET_SIZE;
		pBulletPtcl->nLife = 0;
		pBulletPtcl->bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_BULLETPTCL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBulletp,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	pBulletPtcl = &g_aBulletPtcl[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		// �e���_���W
		pVtx[0].pos = D3DXVECTOR3(pBulletPtcl->pos.x - pBulletPtcl->BulletSize, pBulletPtcl->pos.y + pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pBulletPtcl->pos.x + pBulletPtcl->BulletSize, pBulletPtcl->pos.y + pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pBulletPtcl->pos.x - pBulletPtcl->BulletSize, pBulletPtcl->pos.y - pBulletPtcl->BulletSize, pBulletPtcl->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pBulletPtcl->pos.x + pBulletPtcl->BulletSize, pBulletPtcl->pos.y - pBulletPtcl->BulletSize, pBulletPtcl->pos.z);

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
	g_pVtxBuffBulletp->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitBulletPT(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBulletp != NULL)
	{
		g_pVtxBuffBulletp->Release();
		g_pVtxBuffBulletp = NULL;
	}
	if (g_apTextureBulletp != NULL)
	{
		g_apTextureBulletp->Release();
		g_apTextureBulletp = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateBulletPT(void)
{
	// �\���̂̃|�C���^
	VERTEX_3D *pVtx;

	// �\���̂̏��擾
	BParticle *pBulletPtcl;
	Player *pPlayer;
	pPlayer = GetPlayer();
	pBulletPtcl = &g_aBulletPtcl[0];

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		if (pBulletPtcl->bUse == true)
		{
			// �ʒu�̍X�V
			pBulletPtcl->pos.z -= pBulletPtcl->move.z * 2.5f;
			pBulletPtcl->pos.x += pBulletPtcl->move.x * 2.5f;
			pBulletPtcl->pos.y = pPlayer->aModel[0].pos.y + pPlayer->pos.y;

			// ���C�t�̌���
			pBulletPtcl->nLife -= 2;

			// �����`�F�b�N
			if (pBulletPtcl->nLife == 0)
			{
				// 0�ɂȂ�����t�H���X�ɕς���
				pBulletPtcl->bUse = false;
			}
		}
		// 4���_�������
		pVtx += PVTEX_MAX;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBulletp->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawBulletPT(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;
	// �\���̂̏��擾
	BParticle *pBulletPtcl;
	pBulletPtcl = &g_aBulletPtcl[0];

	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{
		if (pBulletPtcl->bUse == true)
		{
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pBulletPtcl->mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pBulletPtcl->mtxWorld, NULL, &mtxView); // �t�s������߂�

			pBulletPtcl->mtxWorld._41 = 0.0f;
			pBulletPtcl->mtxWorld._42 = 0.0f;
			pBulletPtcl->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pBulletPtcl->pos.x, pBulletPtcl->pos.y, pBulletPtcl->pos.z);
			D3DXMatrixMultiply(&pBulletPtcl->mtxWorld, &pBulletPtcl->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pBulletPtcl->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBulletp, 0, sizeof(VERTEX_3D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBulletp);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);

			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		}
	}
}

//=====================================================================================================================================================================//
// �e�̐ݒ菈��
//=====================================================================================================================================================================//
void SetBulletPT(D3DXVECTOR3 pos, float movex, float movez, int nLife)
{
	//�|�C���^
	VERTEX_3D *pVtx;

	// �\���̂̏��擾
	BParticle *pBulletPtcl;
	Player *pPlayer = GetPlayer();
	pBulletPtcl = &g_aBulletPtcl[0];

	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffBulletp->Lock(0, 0, (void**)&pVtx, 0);

	//�e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_BULLETPTCL; nCntBullet++, pBulletPtcl++)
	{

			if (pBulletPtcl->bUse == false)
			{//�g�p����Ă��Ȃ��e

			 // �ʒu�̐ݒ�
				pBulletPtcl->pos.x = pos.x - sinf(pPlayer->rot.y) * 10.0f;
				pBulletPtcl->pos.z = pos.z - cosf(pPlayer->rot.y) * 10.0f;
				pBulletPtcl->pos.y = pos.y + 2.0f;

				// �ړ��̐ݒ�
				float fAngle = (float)((rand() % 628) - 628) / 100.f;
				pBulletPtcl->move.z = movez - sinf(fAngle);
				pBulletPtcl->move.x = movex - cosf(fAngle);

				// �����̐ݒ�
				pBulletPtcl->nLife = nLife;

				// �e�𔭎�
				pBulletPtcl->bUse = true;

				break;
		}
		pVtx += PVTEX_MAX;	// ���_����4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffBulletp->Unlock();
}

BParticle * GetBulletPT(void)
{
	return &g_aBulletPtcl[0];
}
