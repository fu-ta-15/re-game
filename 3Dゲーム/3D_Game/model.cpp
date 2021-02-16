//##################################################################################################################################################################//
//																																									//
// ���f������ [model.cpp]																																			//
// Author : SUZUKI FUUTA																																			//
//																																									//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�@�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "model.h"
#include "keyinput.h"
#include "camera.h"
#include "shadow.h"
#include "bullet.h"
#include "bulletptcl.h"
#include "memory.h"
#include "effect.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#define MODEL_SPEED			(0.3f)		// ���f���̃X�s�[�h
#define MAX_SIZE_MEMORY		(4000)		// �������̃T�C�Y


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�O���[�o���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
Player g_Player;							// �v���C���[�i���f���j�̍\����


//==================================================================================================================================================================//
// ����������
//==================================================================================================================================================================//
void InitModel(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	

	/* ���f�� */

	/* No.0 �� */
	g_Player.aModel[0].pos = D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_Player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[0].pMesh = NULL;
	g_Player.aModel[0].pBuffMat = NULL;
	g_Player.aModel[0].nIdxModelParent = -1;

	/* No.1 �� */
	g_Player.aModel[1].pos = D3DXVECTOR3(0.0f, 15.0f, 0.0f);
	g_Player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[1].pMesh = NULL;
	g_Player.aModel[1].pBuffMat = NULL;
	g_Player.aModel[1].nIdxModelParent = 0;

	/* No.2 �E�r */
	g_Player.aModel[2].pos = D3DXVECTOR3(-4.0f, 10.0f, 0.0f);
	g_Player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[2].pMesh = NULL;
	g_Player.aModel[2].pBuffMat = NULL;
	g_Player.aModel[2].nIdxModelParent = 0;

	/* No.3 ���r */
	g_Player.aModel[3].pos = D3DXVECTOR3(4.0f, 10.0f, 0.0f);
	g_Player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[3].pMesh = NULL;
	g_Player.aModel[3].pBuffMat = NULL;
	g_Player.aModel[3].nIdxModelParent = 0;

	/* No.4 �E�ڂP */
	g_Player.aModel[4].pos = D3DXVECTOR3(-4.5f, 0.0f, 3.0f);
	g_Player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[4].pMesh = NULL;
	g_Player.aModel[4].pBuffMat = NULL;
	g_Player.aModel[4].nIdxModelParent = 0;

	/* No.5 �E�ڂQ */
	g_Player.aModel[5].pos = D3DXVECTOR3(-4.5f, 0.0f, -3.0f);
	g_Player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[5].pMesh = NULL;
	g_Player.aModel[5].pBuffMat = NULL;
	g_Player.aModel[5].nIdxModelParent = 0;

	/* No.6 ���ڂP */
	g_Player.aModel[6].pos = D3DXVECTOR3(4.5f, 0.0f, 3.0f);
	g_Player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[6].pMesh = NULL;
	g_Player.aModel[6].pBuffMat = NULL;
	g_Player.aModel[6].nIdxModelParent = 0;

	/* No.7 ���ڂQ */
	g_Player.aModel[7].pos = D3DXVECTOR3(4.5f, 0.0f, -3.0f);
	g_Player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[7].pMesh = NULL;
	g_Player.aModel[7].pBuffMat = NULL;
	g_Player.aModel[7].nIdxModelParent = 0;

	/* No.8 �E�r�ɂȂ��镔�� */
	g_Player.aModel[8].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_Player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[8].pMesh = NULL;
	g_Player.aModel[8].pBuffMat = NULL;
	g_Player.aModel[8].nIdxModelParent = 2;

	/* No.9 �E��  */
	g_Player.aModel[9].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_Player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[9].pMesh = NULL;
	g_Player.aModel[9].pBuffMat = NULL;
	g_Player.aModel[9].nIdxModelParent = 8;

	/* No.10 ���r�ɂȂ��镔�� */
	g_Player.aModel[10].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_Player.aModel[10].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[10].pMesh = NULL;
	g_Player.aModel[10].pBuffMat = NULL;
	g_Player.aModel[10].nIdxModelParent = 3;

	/* No.11 ���� */
	g_Player.aModel[11].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_Player.aModel[11].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[11].pMesh = NULL;
	g_Player.aModel[11].pBuffMat = NULL;
	g_Player.aModel[11].nIdxModelParent = 10;

	/* No.12 �E�ڂP�ɂȂ��镔�� */
	g_Player.aModel[12].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);
	g_Player.aModel[12].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[12].pMesh = NULL;
	g_Player.aModel[12].pBuffMat = NULL;
	g_Player.aModel[12].nIdxModelParent = 4;

	/* No.13 �E�ڂQ�ɂȂ��镔�� */
	g_Player.aModel[13].pos = D3DXVECTOR3(-11.5f, 0.0f, 0.0f);
	g_Player.aModel[13].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[13].pMesh = NULL;
	g_Player.aModel[13].pBuffMat = NULL;
	g_Player.aModel[13].nIdxModelParent = 5;

	/* No.14 �E���P */
	g_Player.aModel[14].pos = D3DXVECTOR3(-18.0f, 0.0f, 0.0f);
	g_Player.aModel[14].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[14].pMesh = NULL;
	g_Player.aModel[14].pBuffMat = NULL;
	g_Player.aModel[14].nIdxModelParent = 12;

	/* No.15 �E���Q */
	g_Player.aModel[15].pos = D3DXVECTOR3(-18.0f, 0.0f, 0.0f);
	g_Player.aModel[15].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[15].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[15].pMesh = NULL;
	g_Player.aModel[15].pBuffMat = NULL;
	g_Player.aModel[15].nIdxModelParent = 13;

	/* No.16 ���ڂP�ɂȂ��镔�� */
	g_Player.aModel[16].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);
	g_Player.aModel[16].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[16].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[16].pMesh = NULL;
	g_Player.aModel[16].pBuffMat = NULL;
	g_Player.aModel[16].nIdxModelParent = 6;

	/* No.17 ���ڂQ�ɂȂ��镔�� */
	g_Player.aModel[17].pos = D3DXVECTOR3(11.5f, 0.0f, 0.0f);
	g_Player.aModel[17].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[17].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[17].pMesh = NULL;
	g_Player.aModel[17].pBuffMat = NULL;
	g_Player.aModel[17].nIdxModelParent = 7;

	/* No.18 �����P */
	g_Player.aModel[18].pos = D3DXVECTOR3(18.0f, 0.0f, 0.0f);
	g_Player.aModel[18].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[18].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[18].pMesh = NULL;
	g_Player.aModel[18].pBuffMat = NULL;
	g_Player.aModel[18].nIdxModelParent = 16;

	/* No.19 �����Q */
	g_Player.aModel[19].pos = D3DXVECTOR3(18.0f, 0.0f, 0.0f);
	g_Player.aModel[19].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[19].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.aModel[19].pMesh = NULL;
	g_Player.aModel[19].pBuffMat = NULL;
	g_Player.aModel[19].nIdxModelParent = 17;

	/* �v���C���[ */
	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.nNumShadow = 1;
	g_Player.nNumModel = 20;

	///* ���[�V���� */
	//g_Player.nNumMotion = 1;
	//g_Player.nNumKey = 2;
	//g_Player.nKey_No = 0;
	//g_Player.nCounterMotion = 0;
	//g_Player.bLoopMotion = false;

	//g_Player.aMotionInfo[0].bLoop = true;
	//g_Player.aMotionInfo[0].nNumKey = 2;

	//g_Player.aMotionInfo[0].aKeyInfo[0].nFrame = 60;
	//g_Player.aMotionInfo[0].aKeyInfo[1].nFrame = 60;

	///* �p�[�c�O */
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_X = 5.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[0].Rot_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_X = -5.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[0].Rot_Z = 0.0f;

	///* �p�[�c�P */
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[0].aKey[1].Rot_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Pos_Z = 0.0f;

	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_X = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Y = 0.0f;
	//g_Player.aMotionInfo[0].aKeyInfo[1].aKey[1].Rot_Z = 0.0f;

	// �t�@�C���̓ǂݍ���
	/* No.0 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\body.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[0].pBuffMat, NULL, &g_Player.aModel[0].NumMat, &g_Player.aModel[0].pMesh);
	/* No.1 �� */
	D3DXLoadMeshFromX("data\\suzuki_model\\hed.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[1].pBuffMat, NULL, &g_Player.aModel[1].NumMat, &g_Player.aModel[1].pMesh);
	/* No.2 �E�r */
	D3DXLoadMeshFromX("data\\suzuki_model\\armeR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[2].pBuffMat, NULL, &g_Player.aModel[2].NumMat, &g_Player.aModel[2].pMesh);
	/* No.3 ���r */
	D3DXLoadMeshFromX("data\\suzuki_model\\arme.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[3].pBuffMat, NULL, &g_Player.aModel[3].NumMat, &g_Player.aModel[3].pMesh);
	/* No.4 �E�ڂP */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[4].pBuffMat, NULL, &g_Player.aModel[4].NumMat, &g_Player.aModel[4].pMesh);
	/* No.5 �E�ڂQ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[5].pBuffMat, NULL, &g_Player.aModel[5].NumMat, &g_Player.aModel[5].pMesh);
	/* No.6 ���ڂP */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[6].pBuffMat, NULL, &g_Player.aModel[6].NumMat, &g_Player.aModel[6].pMesh);
	/* No.7 ���ڂQ */
	D3DXLoadMeshFromX("data\\suzuki_model\\legseLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[7].pBuffMat, NULL, &g_Player.aModel[7].NumMat, &g_Player.aModel[7].pMesh);
	/* No.8 �E�r�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\armeseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[8].pBuffMat, NULL, &g_Player.aModel[8].NumMat, &g_Player.aModel[8].pMesh);
	/* No.9 �E��  */
	D3DXLoadMeshFromX("data\\suzuki_model\\handR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[9].pBuffMat, NULL, &g_Player.aModel[9].NumMat, &g_Player.aModel[9].pMesh);
	/* No.10 ���r�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\armese.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[10].pBuffMat, NULL, &g_Player.aModel[10].NumMat, &g_Player.aModel[10].pMesh);
	/* No.11 ���� */
	D3DXLoadMeshFromX("data\\suzuki_model\\hand.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[11].pBuffMat, NULL, &g_Player.aModel[11].NumMat, &g_Player.aModel[11].pMesh);
	/* No.12 �E�ڂP�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\legR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[12].pBuffMat, NULL, &g_Player.aModel[12].NumMat, &g_Player.aModel[12].pMesh);
	/* No.13 �E�ڂQ�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\legRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[13].pBuffMat, NULL, &g_Player.aModel[13].NumMat, &g_Player.aModel[13].pMesh);
	/* No.14 �E���P */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[14].pBuffMat, NULL, &g_Player.aModel[14].NumMat, &g_Player.aModel[14].pMesh);
	/* No.15 �E���Q */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseRR.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[15].pBuffMat, NULL, &g_Player.aModel[15].NumMat, &g_Player.aModel[15].pMesh);
	/* No.16 ���ڂP�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\legL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[16].pBuffMat, NULL, &g_Player.aModel[16].NumMat, &g_Player.aModel[16].pMesh);
	/* No.17 ���ڂQ�ɂȂ��镔�� */
	D3DXLoadMeshFromX("data\\suzuki_model\\legLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[17].pBuffMat, NULL, &g_Player.aModel[17].NumMat, &g_Player.aModel[17].pMesh);
	/* No.18 �����P */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[18].pBuffMat, NULL, &g_Player.aModel[18].NumMat, &g_Player.aModel[18].pMesh);
	/* No.19 �����Q */
	D3DXLoadMeshFromX("data\\suzuki_model\\shuoseLL.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &g_Player.aModel[19].pBuffMat, NULL, &g_Player.aModel[19].NumMat, &g_Player.aModel[19].pMesh);

	for (int nCnt = 0; nCnt < g_Player.nNumModel; nCnt++)
	{
		if (g_Player.aModel[nCnt].pBuffMat == NULL)
		{
			printf("%s %d", "�f�[�^�ǂݍ��ݎ��s", nCnt);
		}
		else
		{
			printf("%s %d\n", "\n �f�[�^�ǂݍ��ݐ���", nCnt);
		}
	}


	g_Player.nNumShadow = SetShadow(g_Player.pos, 10.0f, 10.0f);


	/* ���f���̒��_��񔲂��o�� */
		int nNumVtx;								// ���_��
		DWORD sizeFVF;								// ���_�t�H�[�}�b�g�̃T�C�Y
		BYTE *pVtxBuff;								// ���_�o�b�t�@�ւ̃|�C���^
		float MinModel_X = 0.0f, MinModel_Z = 0.0f;
		float MaxModel_X = 0.0f, MaxModel_Z = 0.0f;

		// ���_�����擾
		nNumVtx = g_Player.aModel[0].pMesh->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFVF = D3DXGetFVFVertexSize(g_Player.aModel[0].pMesh->GetFVF());
		// ���_�o�b�t�@�����b�N
		g_Player.aModel[0].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 Vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��
			
			if (Vtx.x < MinModel_X)
			{/* �ŏ��l */
				MinModel_X = Vtx.x;
				g_Player.aModel[0].g_VtxMinModel.x = MinModel_X;
			}
			if (Vtx.z < MinModel_Z)
			{
				MinModel_Z = Vtx.z;
				g_Player.aModel[0].g_VtxMinModel.z = MinModel_Z;
			}
			if (Vtx.x > MaxModel_X)
			{/* �ő�l */
				MaxModel_X = Vtx.x;
				g_Player.aModel[0].g_VtxMaxModel.x = MaxModel_X;
			}
			if (Vtx.z > MaxModel_Z)
			{
				MaxModel_Z = Vtx.z;
				g_Player.aModel[0].g_VtxMaxModel.z = MaxModel_Z;
			}
			pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}
		// ���_�o�b�t�@�̃A�����b�N
		g_Player.aModel[0].pMesh->UnlockVertexBuffer();
}

//==================================================================================================================================================================//
// �I������
//==================================================================================================================================================================//
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < 20; nCntModel++)
	{
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{// ���b�V���̔j��
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{// �}�e���A���̔j��
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//==================================================================================================================================================================//
// �X�V����
//==================================================================================================================================================================//
void UpdateModel(void)
{
	Camera *pCamera = GetCamera();

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Player.pos, sinf(-g_Player.rot.y), cosf(g_Player.rot.y), 50);
		SetBulletPT(g_Player.pos, sinf(-g_Player.rot.y), cosf(g_Player.rot.y), 50);
	}

	MoveModel();

	// �ʒu�̍X�V
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// �ړI��]����
	if ((g_Player.rotDest.y - g_Player.rot.y) > D3DX_PI)
	{
		g_Player.rotDest.y -= D3DX_PI * 2.0f;
	}
	if ((g_Player.rotDest.y - g_Player.rot.y) < (-D3DX_PI))
	{
		g_Player.rotDest.y += D3DX_PI * 2.0f;
	}

	// �����Ă����
	g_Player.rot.y += (g_Player.rotDest.y - g_Player.rot.y) * 0.1f;

	// ��]����
	if (g_Player.rot.y < (-D3DX_PI))
	{
		g_Player.rot.y += D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y > D3DX_PI)
	{
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}

	// �ړ��E��]�ʂ̌���
	g_Player.move.x += (0 - g_Player.move.x) * 0.3f;
	g_Player.move.y += (0 - g_Player.move.y) * 0.3f;
	g_Player.move.z += (0 - g_Player.move.z) * 0.3f;

	// ���[�V����
	if (GetKeyboardTrigger(DIK_1) == true)
	{
		MotionModel();
	}

	// �e�̐ݒ�
	SetPositionShadow(g_Player.nNumShadow, g_Player.pos);
}

//==================================================================================================================================================================//
// �`�揈��
//==================================================================================================================================================================//
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							// �}�e���A���f�[�^�ւ̃|�C���^

	/* �v���C���[�i�����Ȃ����_�j�̐ݒ� */
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < g_Player.nNumModel; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	// �v�Z�p
		D3DXMATRIX mtxParent;					// �e�̃}�g���b�N�X

		// �e�p�[�c�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// �e�p�[�c�̌���
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		// �e�p�[�c�̈ʒu
		D3DXMatrixTranslation(&mtxTransModel, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		// �e�p�[�c�̐e�}�g���b�N�X��ݒ�
		if (g_Player.aModel[nCntModel].nIdxModelParent != -1)
		{// �e�̃C���f�b�N�X��ݒ�
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{// �v���C���[�}�g���b�N�X��ݒ�
			mtxParent = g_Player.mtxWorld;
		}

		// �Z�o�����e�p�[�c�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld,
							&g_Player.aModel[nCntModel].mtxWorld,
							&mtxParent);
		// �e�p�[�c�̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD,
			&g_Player.aModel[nCntModel].mtxWorld);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].NumMat; nCntMat++)
		{
			// �e���f���p�[�c�̕`��
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, NULL);
			// ���f���̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}
	// �ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//==================================================================================================================================================================//
// ���f���̈ړ�
//==================================================================================================================================================================//
void MoveModel(void)
{
	Camera *pCamera = GetCamera();

	/*���f������*/
	// �O�ړ��E��ړ�
	if (GetKeyboardPresse(DIK_UP) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 3 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 3 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_DOWN) == true)
	{
		if (GetKeyboardPresse(DIK_RIGHT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = -D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else if (GetKeyboardPresse(DIK_LEFT) == true)
		{
			g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 1 / 4) * MODEL_SPEED;
			g_Player.rotDest.y = D3DX_PI * 1 / 4 - pCamera->rot.y;
		}
		else
		{
			g_Player.move.x -= sinf(pCamera->rot.y + D3DX_PI) * MODEL_SPEED;
			g_Player.move.z += cosf(pCamera->rot.y - D3DX_PI) * MODEL_SPEED;
			g_Player.rotDest.y = 0.0f - pCamera->rot.y;
		}
	}
	else if (GetKeyboardPresse(DIK_RIGHT) == true)
	{// �E�ړ��E���ړ�
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y + D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = -D3DX_PI * 2 / 4 - pCamera->rot.y ;
	}
	else if (GetKeyboardPresse(DIK_LEFT) == true)
	{
		g_Player.move.x += sinf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.move.z -= cosf(pCamera->rot.y - D3DX_PI * 2 / 4) * MODEL_SPEED;
		g_Player.rotDest.y = D3DX_PI * 2 / 4 - pCamera->rot.y;
	}

	// ��ړ��E���ړ�
	if (GetKeyboardPresse(DIK_O) == true)
	{
		g_Player.move.y += 0.5f;
	}
	if (GetKeyboardPresse(DIK_L) == true)
	{
		g_Player.move.y -= 0.5f;
	}
	// �E����E������
	if (GetKeyboardPresse(DIK_9) == true)
	{
		g_Player.rotDest.y += 0.08f;
	}
	if (GetKeyboardPresse(DIK_0) == true)
	{
		g_Player.rotDest.y -= 0.08f;
	}
}

//==================================================================================================================================================================//
// ���[�V�����Ǘ�
//==================================================================================================================================================================//
void MotionModel(void)
{
	D3DXVECTOR3 fNowPos = g_Player.aModel[1].pos;

	// ���̃��[�V������
	// ���[�v�͂���̂�
	if (g_Player.aMotionInfo[0].bLoop == true)
	{
		// �J�E���^�[�X�^�[�g
		g_Player.nCounterMotion++;
		// ���f����
		for (int nModel = 0; nModel < g_Player.nNumModel; nModel++)
		{
			// �L�[�̐���
			for (int nKey = 0; nKey < g_Player.nNumKey; nKey++)
			{
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_X = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_X - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_X;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Y = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Y - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_Y;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Z = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Pos_Z - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Pos_Z;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_X = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_X - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_X;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Y = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Y - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_Y;
				g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Z = g_Player.aMotionInfo[0].aKeyInfo[0].aKey[nModel].Rot_Z - g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].aKey[nModel].Rot_Z;


				g_Player.aModel[0].pos.x = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_X * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].pos.y = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_Y * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].pos.z = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Pos_Z * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.x = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_X * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.y = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_Y * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
				g_Player.aModel[0].rot.z = g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No+1].aKey[nModel].Rot_Z * ((float)g_Player.nCounterMotion / (float)g_Player.aMotionInfo[0].aKeyInfo[g_Player.nKey_No].nFrame);
			}
		}
	}
}


//==================================================================================================================================================================//
// �e�L�X�g�̓ǂݍ���
//==================================================================================================================================================================//
void FileLoad(void)
{
	// ������̃|�C���g
	char *str;
	// ������̒���
	int length = 1000;

	// �������m��
	str = (char*)malloc(sizeof(char) * length);

	memset(str, 0, sizeof(char) * 1000);

	if (!str)
	{// �������m�ۂɎ��s
		printf("%s", "\n�������m�ۂɎ��s");
		exit(0);
	}


}



//==================================================================================================================================================================//
// �v���C���[�̏��
//==================================================================================================================================================================//
Player * GetPlayer(void)
{
	return &g_Player;
}