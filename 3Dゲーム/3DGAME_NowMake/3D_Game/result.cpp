//##################################################################################################################################################################//
//
// �v���C���[���� [player.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "Keyinput.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "Dinput.h"
#include "meshfield.h"
#include "meshwall.h"
#include "camera.h"
#include "light.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define RESULT_MAX_MODEL			(1)


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;	//���_�o�b�t�@�̏��
LPDIRECT3DTEXTURE9 g_pTextureResult = NULL;		//�e�N�X�`���̏��
ResultModel g_aResult[RESULT_MAX_MODEL];

//=====================================================================================================================================================================//
// ���U���g�̏���������
//=====================================================================================================================================================================//
HRESULT InitResult(void)
{
	InitCamera();
	InitResultModel();
	Initlight();
	InitMeshfield();
	InitMeshWall();
	// �ǂ̔z�u
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, WALL_POS), D3DXVECTOR3(0.0f, 0.0f, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(0.0f, 0.0f, -WALL_POS), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);
	SetMeshWall(D3DXVECTOR3(-WALL_POS, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -PI_HAFE, 0.0f), WALL_WIGTH, WALL_HEIGHHT);

	//PlaySound(SOUND_LABEL_BGM003);

	return S_OK;

}

//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitResult(void)
{
	UninitCamera();
	UninitResultModel();
	Uninitlight();
	UninitMeshfield();
	UninitMeshWall();

	//StopSound(SOUND_LABEL_BGM003);

}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateResult(void)
{
	FADE pFade;
	pFade = GetFade();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeypadTrigger(3) == true)
		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
	UpdateResultModel();
	UpdateCamera();
	Updatelight();
	UpdateMeshfield();
	UpdateMeshWall();

}

//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawResult(void)
{
	SetCamera();
	DrawMeshfield();
	DrawMeshWall();
	DrawResultModel();
}


//=====================================================================================================================================================================//
// ����������
//=====================================================================================================================================================================//
void InitResultModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	/* ���f�� */
	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{
		/* No.0 �� */
		g_aResult[nNumCnt].pos = D3DXVECTOR3(0.0f + (nNumCnt * 50), 100.0f, 0.0f);
		g_aResult[nNumCnt].oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aResult[nNumCnt].pMesh = NULL;
		g_aResult[nNumCnt].pBuffMat = NULL;
		g_aResult[nNumCnt].pTexture = NULL;
		g_aResult[nNumCnt].rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		// �t�@�C���̓ǂݍ���
		/* No.0 �� */
		D3DXLoadMeshFromX("data\\MODEL\\Title.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_aResult[nNumCnt].pBuffMat, NULL, &g_aResult[nNumCnt].NumMat, &g_aResult[nNumCnt].pMesh);

		g_aResult[nNumCnt].pMat = (D3DXMATERIAL*)g_aResult[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aResult[nNumCnt].NumMat; nCntMat++)
		{
			if (g_aResult[nNumCnt].pMat[nCntMat].pTextureFilename != NULL)
			{
				// �e�N�X�`���̓ǂݍ���
				D3DXCreateTextureFromFile(pDevice, g_aResult[nNumCnt].pMat[nCntMat].pTextureFilename, &g_aResult[nNumCnt].pTexture);
			}
		}

		//g_Mob.nNumShadow = SetShadow(g_Mob.pos, 10.0f, 10.0f);

		/* ���f���̒��_��񔲂��o�� */
		int nNumVtx;												// ���_��
		DWORD sizeFVF;												// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;												// ���_�o�b�t�@�ւ̃|�C���^
		float MinMob_X = 0.0f, MinMob_Z = 0.0f, MinMob_Y = 0.0f;	// �ŏ��l�ۊǗp
		float MaxMob_X = 0.0f, MaxMob_Z = 0.0f, MaxMob_Y = 0.0f;	// �ő�l�ۊǗp

		// ���_�����擾
		nNumVtx = g_aResult[nNumCnt].pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_aResult[nNumCnt].pMesh->GetFVF());
		// ���_�o�b�t�@�����b�N
		g_aResult[nNumCnt].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
														// �ő�l�E�ŏ��l�̑������
			if (Vtx.x < MinMob_X)
			{/* �ŏ��l */
				MinMob_X = Vtx.x;
				g_aResult[nNumCnt].g_VtxMinTitle.x = MinMob_X;
			}
			if (Vtx.y < MinMob_Y)
			{
				MinMob_Y = Vtx.y;
				g_aResult[nNumCnt].g_VtxMinTitle.y = MinMob_Y;
			}
			if (Vtx.z < MinMob_Z)
			{
				MinMob_Z = Vtx.z;
				g_aResult[nNumCnt].g_VtxMinTitle.z = MinMob_Z;
			}

			if (Vtx.x > MaxMob_X)
			{/* �ő�l */
				MaxMob_X = Vtx.x;
				g_aResult[nNumCnt].g_VtxMaxTitle.x = MaxMob_X;
			}
			if (Vtx.y > MaxMob_Y)
			{
				MaxMob_Y = Vtx.y;
				g_aResult[nNumCnt].g_VtxMaxTitle.y = MaxMob_Y;
			}
			if (Vtx.z > MaxMob_Z)
			{
				MaxMob_Z = Vtx.z;
				g_aResult[nNumCnt].g_VtxMaxTitle.z = MaxMob_Z;
			}
			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@�̃A�����b�N
		g_aResult[nNumCnt].pMesh->UnlockVertexBuffer();
	}
}


//=====================================================================================================================================================================//
// �I������
//=====================================================================================================================================================================//
void UninitResultModel(void)
{
	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{
		if (g_aResult[nNumCnt].pMesh != NULL)
		{// ���b�V���̔j��
			g_aResult[nNumCnt].pMesh->Release();
			g_aResult[nNumCnt].pMesh = NULL;
		}
		if (g_aResult[nNumCnt].pBuffMat != NULL)
		{// �}�e���A���̔j��
			g_aResult[nNumCnt].pBuffMat->Release();
			g_aResult[nNumCnt].pBuffMat = NULL;
		}
		if (g_aResult[nNumCnt].pTexture != NULL)
		{
			g_aResult[nNumCnt].pTexture->Release();
			g_aResult[nNumCnt].pTexture = NULL;
		}
	}
}


//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateResultModel(void)
{
}


//=====================================================================================================================================================================//
// �`�揈��
//=====================================================================================================================================================================//
void DrawResultModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	for (int nNumCnt = 0; nNumCnt < RESULT_MAX_MODEL; nNumCnt++)
	{

		D3DXMatrixIdentity(&g_aResult[nNumCnt].mtxWorld);

		// �����̔��f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aResult[nNumCnt].rot.y, g_aResult[nNumCnt].rot.x, g_aResult[nNumCnt].rot.z);
		D3DXMatrixMultiply(&g_aResult[nNumCnt].mtxWorld, &g_aResult[nNumCnt].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aResult[nNumCnt].pos.x, g_aResult[nNumCnt].pos.y, g_aResult[nNumCnt].pos.z);
		D3DXMatrixMultiply(&g_aResult[nNumCnt].mtxWorld, &g_aResult[nNumCnt].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aResult[nNumCnt].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_aResult[nNumCnt].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aResult[nNumCnt].NumMat; nCntMat++)
		{
			// �e���f���p�[�c�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���f���̕`��
			g_aResult[nNumCnt].pMesh->DrawSubset(nCntMat);
		}
		// �ۑ����Ă����}�e���A����߂�
		pDevice->SetMaterial(&matDef);
	}
}


//=====================================================================================================================================================================//
// �Z�b�g����
//=====================================================================================================================================================================//
void SetResultModel(void)
{
}
