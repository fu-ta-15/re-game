//##################################################################################################################################################################//
//
// ���f���w�b�_�t�@�C�� [model.h]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#ifndef _MODEL_H_
#define _MODEL_H_


#include "main.h"

//=====================================================================================================================================================================//
// �\����
//=====================================================================================================================================================================//
typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 move;				// �ړ���
	D3DXVECTOR3 rot;				// ��]
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	LPD3DXMESH pMesh;				// ���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;			// �}�e���A���ւ̃|�C���^
	DWORD NumMat;					// �}�e���A���̐�
	int nIdxModelParent;			// �e���f���̃C���f�b�N�X
	D3DXVECTOR3 g_VtxMinModel;		// ���f���̍ŏ��l�iMIN�j
	D3DXVECTOR3	g_VtxMaxModel;		// ���f���̍ő�l�iMAX�j

}Model;		// ���f��

typedef struct
{
	/* �ʒu */
	float Pos_X;
	float Pos_Y;
	float Pos_Z;

	/* ��] */
	float Rot_X;
	float Rot_Y;
	float Rot_Z;
}KEY;	// �L�[

typedef struct
{
	int nFrame;						// �Đ��t���[��
	KEY aKey[2];					// �e���f���̃L�[�v�f[�p�[�c�̑���]
}KEY_INFO;	// �L�[�̏��̍\����

typedef struct
{
	bool bLoop;				// ���[�v�̗L�E��
	int nNumKey;			// �L�[�̑���
	KEY_INFO aKeyInfo[2];	// �L�[���[�L�[�̍ő吔]
}MOTION_INFO;	// ���[�V�������\����

typedef struct
{
	/* �v���C���[��� */
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ��]
	D3DXVECTOR3 rotDest;			// ��]�ړI
	D3DXVECTOR3 move;				// �ړ���
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X

	/* ���f����� */
	Model aModel[20];				// ���f���p�[�c[��]
	int nNumModel;					// ���f���p�[�c��

	/* �e */
	int nNumShadow;					// �e

	/* ���[�V���� */
	MOTION_INFO aMotionInfo[1];		// ���[�V�������[���[�V�����ő吔]
	int nNumMotion;					// ���[�V������
	bool bLoopMotion;				// ���[�v�L�E��
	int nNumKey;					// �L�[��
	int nKey_No;					// �L�[No
	int nCounterMotion;				// ���[�V�����J�E���^�[
}Player;	// �v���C���[(�����Ȃ����f��)

//=====================================================================================================================================================================//
// �v���g�^�C�v�錾
//=====================================================================================================================================================================//
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void MoveModel(void);
void MotionModel(void);
void FileLoad(void);
Player *GetPlayer(void);

#endif // !_MODEL_H_
