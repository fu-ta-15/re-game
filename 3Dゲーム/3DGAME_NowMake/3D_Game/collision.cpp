//##################################################################################################################################################################//
//
// �����蔻�菈�� [Collision.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "model.h"
#include "meshwall.h"
#include "meshfield.h"
#include "collision.h"
#include "mob.h"
#include "fade.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�v���g�^�C�v�錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
CollPlayer g_cPlayer;	 // �v���C���[
CollMob g_cMob;			 // ��
CollCircle g_cCircle;	 // �~�̓����蔻��p


//=====================================================================================================================================================================//
// �����蔻��̏�����
//=====================================================================================================================================================================//
void InitCollision(void)
{
	g_cMob.nNumMobMax = MOB_MAX;

}

//=====================================================================================================================================================================//
// ���̎擾
//=====================================================================================================================================================================//
void UpdatePos(void)
{
	// �\���̂̏��擾
	Player *pPlayer = GetPlayer();

	// �v���C���[�̓����蔻��̈�
	g_cPlayer.CollPlayerMax = D3DXVECTOR3(pPlayer->pos.x + pPlayer->aModel[0].g_VtxMaxModel.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMaxModel.y, pPlayer->pos.z + pPlayer->aModel[0].g_VtxMaxModel.z);
	g_cPlayer.CollPlayerMin = D3DXVECTOR3(pPlayer->pos.x + pPlayer->aModel[0].g_VtxMinModel.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMinModel.y, pPlayer->pos.z + pPlayer->aModel[0].g_VtxMinModel.z);



}

//=====================================================================================================================================================================//
// �����蔻��̏���
//=====================================================================================================================================================================//
void PlayerCollision(void)
{
	// �e�\���̂̃|�C���^
	Player *pPlayer = GetPlayer();			 // �v���C���[
	MeshWall *pMeshWall = GetMeshWall();	 // ��
	Moblayer *pMob = GetMoblayer();			 // ���u�i��j

	// �v���C���[�̒��S���W
	g_cPlayer.rPlayer = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMaxModel.y + pPlayer->aModel[1].g_VtxMaxModel.y, pPlayer->pos.z);

	pPlayer->oldpos = g_cPlayer.rPlayer;	  // �ߋ��̈ʒu��ۑ�

	g_cPlayer.PlayerHight = g_cPlayer.rPlayer.y + 40.0f + pPlayer->aModel[1].g_VtxMaxModel.y;	   // �v���C���[�̈�ԍ������W
	g_cPlayer.PlayerLow = g_cPlayer.rPlayer.y - pPlayer->aModel[0].g_VtxMaxModel.y;	   // �v���C���[�̈�ԒႢ���W

	// �v���C���[�̔��a�i���f���̍ő�l�j
	g_cPlayer.PlayerRadWidth = pPlayer->aModel[0].g_VtxMaxModel.x;
	g_cPlayer.PlayerRadHight = pPlayer->aModel[0].g_VtxMaxModel.y;

	for (int nColl = 0; nColl < MOB_MAX; nColl++, pMob++)
	{
		if (pMob->bUse == true)
		{// �₪���݂��Ă��鎞

				// ��5���̒��S���W
				D3DXVECTOR3 rMob = D3DXVECTOR3(pMob->pos.x, pMob->pos.y + pMob->g_VtxMaxMob.y, pMob->pos.z);

				// ��܌��̔��a�i���f���̍ő�l�j
				g_cCircle.MobRadWidth = pMob->g_VtxMaxMob.x;
				g_cCircle.MobRadHight = pMob->g_VtxMaxMob.y;

				// ��_�̋������Z�o
				g_cCircle.wAa = g_cPlayer.rPlayer.x - rMob.x;
				g_cCircle.wBb = g_cPlayer.rPlayer.z - rMob.z;
				g_cCircle.wCc = (float)sqrt(g_cCircle.wAa * g_cCircle.wAa + g_cCircle.wBb * g_cCircle.wBb);

				g_cCircle.hAa = g_cPlayer.rPlayer.x - rMob.x;
				g_cCircle.hBb = g_cPlayer.rPlayer.y - rMob.y;
				g_cCircle.hCc = (float)sqrt(g_cCircle.hAa * g_cCircle.hAa + g_cCircle.hBb * g_cCircle.hBb);


				// ��̔��a�̘a
				g_cCircle.wSumRad = g_cPlayer.PlayerRadWidth + g_cCircle.MobRadWidth;
				g_cCircle.hSumRad = g_cPlayer.PlayerRadHight + g_cCircle.MobRadHight;


				D3DXVECTOR3 MobCollMax = D3DXVECTOR3(pMob->pos.x + pMob->g_VtxMaxMob.x, pMob->pos.y + pMob->g_VtxMaxMob.y, pMob->pos.z + pMob->g_VtxMaxMob.z);
				D3DXVECTOR3 MobCollMin = D3DXVECTOR3(pMob->pos.x + pMob->g_VtxMinMob.x, pMob->pos.y + pMob->g_VtxMinMob.y, pMob->pos.z + pMob->g_VtxMinMob.z);

				// ��̔���
				if (MobCollMax.x > LENGTH_POLYGON_X)
				{
					pMob->move.x = pMob->move.x * (-1);
				}
				if (MobCollMin.x < -LENGTH_POLYGON_X)
				{
					pMob->move.x = pMob->move.x * (-1);
				}
				if (MobCollMax.z > LENGTH_POLYGON_Z)
				{
					pMob->move.z = pMob->move.z * (-1);
				}
				if (MobCollMin.z < -LENGTH_POLYGON_Z)
				{
					pMob->move.z = pMob->move.z * (-1);
				}

				if (g_cPlayer.PlayerHight < rMob.y - pMob->g_VtxMaxMob.y || g_cPlayer.PlayerLow > rMob.y)
				{
				}
				else
				{
					if (g_cCircle.wCc <= g_cCircle.wSumRad)
					{// �����蔻��̋����ɂȂ�����
						printf("������܂����B");
						g_cMob.nNumMobMax -= 1;
						pMob->bUse = false;
					}
				}
				// ���ς̓����蔻��
				InnerProduct(nColl);
			}
	}

	if (g_cMob.nNumMobMax == 0)
	{// �₪�S���Ȃ��Ȃ�����
		SetFade(FADE_OUT, MODE_RESULT);
	}

	// �v���C���[�̈ړ��͈�
	if (g_cPlayer.CollPlayerMax.x > LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMaxModel.x;
	}
	if (g_cPlayer.CollPlayerMin.x < -LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = -LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMinModel.x;
	}
	if (g_cPlayer.CollPlayerMax.z > LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMaxModel.z;
	}
	if (g_cPlayer.CollPlayerMin.z < -LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = -LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMinModel.z;
	}
}


//=====================================================================================================================================================================//
// ���ς̓����蔻��
//=====================================================================================================================================================================//
void InnerProduct(int nmobIdx)
{
	Moblayer *pMob = GetMoblayer();			// ���u�i��j

	D3DXVECTOR3 VecF[MOB_MAX];				// �i�s�x�N�g��
	float VecN;								// �ǂ̖@���x�N�g��(�@���̂���1�Œ�j

	float VecAX[MOB_MAX];					// ���m�̒l�i���ςŎg���l�jX
	float VecAZ[MOB_MAX];					// ���m�̒l�i���ςŎg���l�jZ
	
	float VecPX[MOB_MAX];					// �ǂɕ��s�ȃx�N�g�� X
	float VecPZ[MOB_MAX];					// �ǂɕ��s�ȃx�N�g�� Z
	
	float VecRX[MOB_MAX];					// ���˃x�N�g�� X
	float VecRZ[MOB_MAX];					// ���˃x�N�g�� Z

	for (int nCntMob = 0; nCntMob < MOB_MAX; nCntMob++, pMob++)
	{
		if (pMob->bUse == true)
		{
			VecF[nCntMob] = pMob->move;

			VecN = -1.0f;

			VecAX[nCntMob] = -VecF[nCntMob].x * VecN;
			VecAZ[nCntMob] = -VecF[nCntMob].z * VecN;

			VecPX[nCntMob] = VecF[nCntMob].x + VecAX[nCntMob] * VecN;
			VecPZ[nCntMob] = VecF[nCntMob].z + VecAZ[nCntMob] * VecN;

			VecRX[nCntMob] = VecF[nCntMob].x + (VecAX[nCntMob] * 2) * VecN;
			VecRZ[nCntMob] = VecF[nCntMob].z + (VecAZ[nCntMob] * 2) * VecN;
		}
	}
}

