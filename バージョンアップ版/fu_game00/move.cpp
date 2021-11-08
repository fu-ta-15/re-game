//#############################################################################
//
// �ړ��\�[�X�t�@�C�� [move.cpp]
// Author : SUZUKI FUUTA
//
//#############################################################################
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "move.h"

//=============================================================================
// �ړ��ʂ̐���
//=============================================================================
D3DXVECTOR3 Move::MoveControl(D3DXVECTOR3& move, D3DXVECTOR3& deceleration)
{
	move.x += (0 - move.x) * deceleration.x;
	move.y += (0 - move.y) * deceleration.y;
	move.z += (0 - move.z) * deceleration.z;

	return move;
}

//=============================================================================
// �����t���E�ڕW�̈ʒu�܂ł̈ړ�
//=============================================================================
D3DXVECTOR3 Move::TargetPosMove(D3DXVECTOR3& tagpos, D3DXVECTOR3& mypos, float Decele)
{
	mypos.x += (tagpos.x - mypos.x) * Decele;
	mypos.y += (tagpos.y - mypos.y) * Decele;
	mypos.z += (tagpos.z - mypos.z) * Decele;

	return mypos;
}

//=============================================================================
// �����ړ�
//=============================================================================
float Move::MoveSnake(float pos, float move, float Uplimit, float Downlimit, float Speed)
{
	if (pos > Downlimit)
	{
		move = -move;
	}
	else if (pos < Uplimit)
	{
		move = (move) * -1;
	}
	return move;
}

//=============================================================================
// ���̈ʒu�����Sin�g�𗘗p�����ړ�
//=============================================================================
float Move::SinWave(float CenterPos, float nHeight, float nCycle, float nTime)
{
	return (CenterPos + sinf((D3DX_PI * 2) / nCycle * (nTime)) * nHeight);
}

//=============================================================================
// ���̈ʒu�����Cos�g�𗘗p�����ړ�
//=============================================================================
float Move::CosWave( float CenterPos,  float nHeight,  float nCycle,  float nTime)
{
	return (CenterPos + cosf((D3DX_PI * 2) / nCycle * (nTime)) * nHeight);
}

float Move::SinMove(float nHeight, float nCycle, float nTime)
{
	return (sinf((D3DX_PI * 2) / nCycle * (nTime)) * nHeight);
}

float Move::CosMove(float nHeight, float nCycle, float nTime)
{
	return (cosf((D3DX_PI * 2) / nCycle * (nTime)) * nHeight);
}

//=============================================================================
// �w�肳�ꂽ�p�x�Ɉړ�
//=============================================================================
float Move::HomingMove(float Angle, float fSpeed)
{
	return Angle * fSpeed;
}

//=============================================================================
// �p�x�̌v�Z
//=============================================================================
float Move::AnglePoint(float PointX, float PointY)
{
	return atan2f(PointX, PointY);
}
