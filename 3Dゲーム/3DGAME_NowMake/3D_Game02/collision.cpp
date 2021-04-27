//##################################################################################################################################################################//
//
// �����蔻�菈�� [Collision.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "player.h"
#include "meshwall.h"
#include "meshfield.h"
#include "collision.h"
#include "mob.h"
#include "fade.h"
#include "modelparticl.h"

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�}�N���ϐ�
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//


//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�v���g�^�C�v�錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
CollPlayer g_cPlayer;	 // �v���C���[
CollMob g_cMob;			 // ��
CollCircle g_cCircle;	 // �~�̓����蔻��p

//------------------------------------------------------------------------------------------------------------------------------------------------------------------//
//�v���g�^�C�v�錾
//------------------------------------------------------------------------------------------------------------------------------------------------------------------//



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
	Rock *pMob = GetRock();			 // ���u�i��j

	// �v���C���[�̒��S���W
	g_cPlayer.rPlayer = D3DXVECTOR3(pPlayer->pos.x, pPlayer->pos.y + pPlayer->aModel[0].g_VtxMaxModel.y + pPlayer->aModel[1].g_VtxMaxModel.y, pPlayer->pos.z);

	pPlayer->oldpos = g_cPlayer.rPlayer;	  // �ߋ��̈ʒu��ۑ�

	g_cPlayer.PlayerHight = g_cPlayer.rPlayer.y + 40.0f + pPlayer->aModel[1].g_VtxMaxModel.y;	 // �v���C���[�̈�ԍ������W
	g_cPlayer.PlayerLow = g_cPlayer.rPlayer.y - pPlayer->aModel[0].g_VtxMaxModel.y;				 // �v���C���[�̈�ԒႢ���W

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

			// ��_�̉��̋������Z�o
			g_cCircle.wAa = g_cPlayer.rPlayer.x - rMob.x;
			g_cCircle.wBb = g_cPlayer.rPlayer.z - rMob.z;
			g_cCircle.wCc = (float)sqrt(g_cCircle.wAa * g_cCircle.wAa + g_cCircle.wBb * g_cCircle.wBb);

			// ��_�̍����̋������Z�o
			g_cCircle.hAa = g_cPlayer.rPlayer.x - rMob.x;
			g_cCircle.hBb = g_cPlayer.rPlayer.y - rMob.y;
			g_cCircle.hCc = (float)sqrt(g_cCircle.hAa * g_cCircle.hAa + g_cCircle.hBb * g_cCircle.hBb);

			// ��̔��a�̘a
			g_cCircle.wSumRad = g_cPlayer.PlayerRadWidth + g_cCircle.MobRadWidth;
			g_cCircle.hSumRad = g_cPlayer.PlayerRadHight + g_cCircle.MobRadHight;

			// ���ς̓����蔻��
			WallCollRock(nColl);

			if (g_cPlayer.PlayerHight < rMob.y - pMob->g_VtxMaxMob.y || g_cPlayer.PlayerLow > rMob.y)
			{// Y�̍��W�Ƀv���C���[�����Ȃ���
			}
			else
			{// Y�̍��W�Ƀv���C���[�����鎞
				if (g_cCircle.wCc <= g_cCircle.wSumRad)
				{// �����蔻��̋����ɂȂ�����
					printf("������܂����B");
					g_cMob.nNumMobMax -= 1;
					SetModelP(rMob, 3.0f, 0.5f, -2.0f, 100, 50);
					pMob->bUse = false;
				}
			}
		}
	}
	// �t�F�C�h�A�E�g�i���U���g��ʂցj
	if (g_cMob.nNumMobMax == 0)
	{// �₪�S���Ȃ��Ȃ�����
		SetFade(FADE_OUT, MODE_RESULT);	// ���U���g��
	}

	// �v���C���[�̈ړ��͈�
	// ���̍s���͈͂܂ōs������
	if (g_cPlayer.CollPlayerMax.x > LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMaxModel.x;
	}
	else if (g_cPlayer.CollPlayerMin.x < -LENGTH_POLYGON_X)
	{
		pPlayer->pos.x = -LENGTH_POLYGON_X - pPlayer->aModel[0].g_VtxMinModel.x;
	}
	// ���Ǝ�O�̍s���͈͂܂ōs������
	if (g_cPlayer.CollPlayerMax.z > LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMaxModel.z;
	}
	else if (g_cPlayer.CollPlayerMin.z < -LENGTH_POLYGON_Z)
	{
		pPlayer->pos.z = -LENGTH_POLYGON_Z - pPlayer->aModel[0].g_VtxMinModel.z;
	}
}

//=====================================================================================================================================================================//
// �O�ς̓����蔻��
//=====================================================================================================================================================================//
void OuterProduct(void)
{
	// �X�e�[�W�̃x�N�g���i���ォ�玞�v���j
	//D3DXVECTOR3 VecA


}


//=====================================================================================================================================================================//
// ���ς̓����蔻��
//=====================================================================================================================================================================//
void WallCollRock(int nmobIdx)
{
	Rock *pRock = GetRock();				// ���u�i��j

	pRock += nmobIdx;						// �Ώۂ̃��u�̃|�C���^�֐i��

	D3DXVECTOR3 VecF;						// �i�s�x�N�g��
	float VecN;								// �ǂ̖@���x�N�g��(�@���̂���1�Œ�j

	float VecAX;							// ���m�̒l�i���ςŎg���l�jX
	float VecAZ;							// ���m�̒l�i���ςŎg���l�jZ
	
	float VecPX;							// �ǂɕ��s�ȃx�N�g�� X
	float VecPZ;							// �ǂɕ��s�ȃx�N�g�� Z
	
	float VecRX;							// ���˃x�N�g�� X
	float VecRZ;							// ���˃x�N�g�� Z

	// �i�s�x�N�g���̑��
	VecF = pRock->move;

	// �����x�N�g��
	VecN = -1.0f;

	// ���ςŎg�p���関�m�̐��l�����߂�
	VecAX = -VecF.x * VecN;
	VecAZ = -VecF.z * VecN;

	// �����������̂Ƃ̕��s�x�N�g�������߂�
	VecPX = VecF.x + VecAX * VecN;
	VecPZ = VecF.z + VecAZ * VecN;

	// ���˃x�N�g�������߂�
	VecRX = VecF.x + (VecAX * 2) * VecN;
	VecRZ = VecF.z + (VecAZ * 2) * VecN;

	// ���f���̍ő�E�ŏ��̍��W
	D3DXVECTOR3 MobCollMax = D3DXVECTOR3(pRock->pos.x + pRock->g_VtxMaxMob.x, pRock->pos.y + pRock->g_VtxMaxMob.y, pRock->pos.z + pRock->g_VtxMaxMob.z);
	D3DXVECTOR3 MobCollMin = D3DXVECTOR3(pRock->pos.x + pRock->g_VtxMinMob.x, pRock->pos.y + pRock->g_VtxMinMob.y, pRock->pos.z + pRock->g_VtxMinMob.z);

	// ��̔���
	if (MobCollMax.x > LENGTH_POLYGON_X)
	{
		pRock->move.x = VecRX;
	}
	if (MobCollMin.x < -LENGTH_POLYGON_X)
	{
		pRock->move.x = VecRX;
	}
	if (MobCollMax.z > LENGTH_POLYGON_Z)
	{
		pRock->move.z = VecRZ;
	}
	if (MobCollMin.z < -LENGTH_POLYGON_Z)
	{
		pRock->move.z = VecRZ;
	}
}

