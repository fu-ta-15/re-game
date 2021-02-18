//##################################################################################################################################################################//
//
// �G�t�F�N�g���� [effect.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "effect.h"
#include "model.h"
#include <time.h>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N����`
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define EFFECT_SIZE						(4.0f)						// �e�̃T�C�Y
#define COLOR_RED						(255)						// �ԐF
#define COLOR_BULUE						(255)						// �F
#define COLOR_GREEN						(255)						// �ΐF
#define COLOR_ALPHA						(255)						// �A���t�@�l
#define PVTEX_MAX						(4)							// pVtx
#define MAX_EFFECT						(1000)						// �e�̍ő吔


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DTEXTURE9 g_apTextureEffect = NULL;		// �e�N�X�`���̏��
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�̏��
Effect g_aEffect[MAX_EFFECT];			// �e�̏��


//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
HRESULT InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̃|�C���^
	VERTEX_3D *pVtx;							// ���_�|�C���^
	Effect *pEffect = &g_aEffect[0];

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\shadow000.jpg", &g_apTextureEffect);

	if (g_apTextureEffect == NULL)
	{
		printf("%s", "�f�[�^�ǂݍ��ݎ��s");
	}
	else
	{
		printf("%s", "\n �f�[�^�ǂݍ��ݐ��� \n data\\TEXTURE\\bullet000.png");
	}

	// �e�̏������ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		pEffect->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pEffect->color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 255.0f);
		pEffect->BulletSize = EFFECT_SIZE;
		pEffect->fAngle = 0.0f;
		pEffect->fRadius = 0.0f;
		pEffect->nIdx = 0;
		pEffect->nLife = 0;
		pEffect->bUse = false;
	}

	// ���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * PVTEX_MAX * MAX_EFFECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL)))
	{
		return E_FAIL;
	}

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	pEffect = &g_aEffect[0];

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		// �e���_���W
		pVtx[0].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->BulletSize, pEffect->pos.y + pEffect->BulletSize, pEffect->pos.z);
		pVtx[1].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->BulletSize, pEffect->pos.y + pEffect->BulletSize, pEffect->pos.z);
		pVtx[2].pos = D3DXVECTOR3(pEffect->pos.x - pEffect->BulletSize, pEffect->pos.y - pEffect->BulletSize, pEffect->pos.z);
		pVtx[3].pos = D3DXVECTOR3(pEffect->pos.x + pEffect->BulletSize, pEffect->pos.y - pEffect->BulletSize, pEffect->pos.z);

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
	g_pVtxBuffEffect->Unlock();

	// ����������
	return S_OK;
}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitEffect(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
	if (g_apTextureEffect != NULL)
	{
		g_apTextureEffect->Release();
		g_apTextureEffect = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateEffect(void)
{
	// �\���̂̃|�C���^
	VERTEX_3D *pVtx;

	// �\���̂̏��擾
	Effect *pEffect;
	Player *pPlayer;
	pPlayer = GetPlayer();
	pEffect = &g_aEffect[0];

	// ���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{
			// �ߋ��̈ʒu��ۑ�
			pEffect->oldpos = pEffect->pos;

			// �ʒu�̍X�V
			pEffect->move.y -= 1.3f;
			pEffect->pos.z += pEffect->move.z;
			pEffect->pos.x += pEffect->move.x;
			pEffect->pos.y += pEffect->move.y;

			// �ړ��ʂ̌���
			pEffect->move.z += (0.0f - pEffect->move.z) * 0.4f;
			pEffect->move.x += (0.0f - pEffect->move.x) * 0.4f;
			pEffect->move.y += (0.0f - pEffect->move.y) * 0.013f;

			if (pEffect->oldpos.y - EFFECT_SIZE < 0)
			{// �O��̈ʒu������艺�ɍs������

				// �ړ��̐ݒ�
				float fAngle = (float)((rand() % 628) - 628) / 100.f;

				pEffect->move.z = cosf(fAngle + D3DX_PI) * 8.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 8.0f;

				pEffect->pos.y = 0 + EFFECT_SIZE;
				pEffect->move.y += 20.0f;
			}

			// ���C�t�̌���
			pEffect->nLife -= 2;

			// �����`�F�b�N
			if (pEffect->nLife == 0)
			{
				// 0�ɂȂ�����t�H���X�ɕς���
				pEffect->bUse = false;
			}
		}
		// 4���_�������
		pVtx += PVTEX_MAX;
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawEffect(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;
	// �r���[�}�g���b�N�X�擾�p
	D3DXMATRIX mtxView;
	// �\���̂̏��擾
	Effect *pEffect;
	pEffect = &g_aEffect[0];

	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���C�g���I�t�ɂ���

	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
		if (pEffect->bUse == true)
		{

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&pEffect->mtxWorld);

			// �r���[�}�g���b�N�X�̎擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			// �|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&pEffect->mtxWorld, NULL, &mtxView); // �t�s������߂�

			pEffect->mtxWorld._41 = 0.0f;
			pEffect->mtxWorld._42 = 0.0f;
			pEffect->mtxWorld._43 = 0.0f;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pEffect->pos.x, pEffect->pos.y, pEffect->pos.z);
			D3DXMatrixMultiply(&pEffect->mtxWorld, &pEffect->mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &pEffect->mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));
			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEffect);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * PVTEX_MAX, 2);


		}
	}
	//���C�g���I�t�ɂ���														
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

//=====================================================================================================================================================================//
// �G�t�F�N�g�̐ݒ菈��
//=====================================================================================================================================================================//
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col,float movex, float movez, float movey, int nIdx, int nLife)
{
	//�|�C���^
	VERTEX_3D *pVtx;

	// �\���̂̏��擾
	Effect *pEffect;
	Player *pPlayer = GetPlayer();
	pEffect = &g_aEffect[0];


	//���_�o�b�t�@�̃��b�N
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�e�̐ݒ�
	for (int nCntBullet = 0; nCntBullet < MAX_EFFECT; nCntBullet++, pEffect++)
	{
			if (pEffect->bUse == false)
			{//�g�p����Ă��Ȃ��e


			 // �ʒu�̐ݒ�
				pEffect->pos.x = pos.x;
				pEffect->pos.z = pos.z;
				pEffect->pos.y = pos.y + 100;

				// �ړ��̐ݒ�
				float fAngle = (float)((rand() % 628) - 628) / 100.f;

				pEffect->move.z = cosf(fAngle + D3DX_PI) * 7.0f;
				pEffect->move.x = sinf(fAngle - D3DX_PI) * 7.0f;
				pEffect->move.y = -movey ;

				float fColorR = (float)((rand()%2));
				float fColorB = (float)((rand()%3));
				float fColorG = (float)((rand()%5));

				pEffect->color.r = fColorR;
				pEffect->color.b = fColorB;
				pEffect->color.g = fColorG;
				pEffect->color.a = col.a;

				pVtx[0].col = pEffect->color;
				pVtx[1].col = pEffect->color;
				pVtx[2].col = pEffect->color;
				pVtx[3].col = pEffect->color;


				// �����̐ݒ�
				pEffect->nLife = nLife;

				// �e�𔭎�
				pEffect->bUse = true;

				break;
			}
		pVtx += PVTEX_MAX;	// ���_����4�i�߂�
	}
	// ���_�o�b�t�@�̃A�����b�N
	g_pVtxBuffEffect->Unlock();


}


Effect * GetEffect(void)
{
	return &g_aEffect[0];
}

