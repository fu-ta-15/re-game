//*****************************************************************************
//
// �p�[�e�B�N������ [particle.cpp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "particle.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �p�[�e�B�N���̐���
//=============================================================================
void Particle::SetParticle(const D3DXVECTOR3 & pos, const D3DXVECTOR3 & size, int EfeectNum, ParticleType type, const LPCSTR pSrcFile)
{
	D3DXVECTOR3			move = ZeroVector3;		// �ړ���
	LPDIRECT3DTEXTURE9	pTex = NULL;			// �e�N�X�`���ւ̃|�C���g
	float				fAngle = 0.0f;			// �p�x

	// �e�N�X�`���̐���
	pTex = Particle::TextureCreate(pSrcFile, pTex);

	for (int nCnt = 0; nCnt < EfeectNum; nCnt++)
	{// �w�肳�ꂽ���Ő���
		switch (type)
		{// ��ނŊp�x�ݒ�

			// �S��
		case Particle::TYPE_EXPLOSION:
			fAngle = (float)((rand() % 628) - 628) / 100.f;
			break;

			// �E����
		case Particle::TYPE_RIGHT_FAN:
			fAngle = (float)(rand() % 314) / 100.f;
			break;

			// ������
		case Particle::TYPE_LEFT_FAN:
			fAngle = (float)-(rand() % 314) / 100.f;
			break;

		case Particle::TYPE_DOWN_FAN:
			fAngle = (float)((rand() % 120) + 260) / 100.f;
			break;
			
		case Particle::TYPE_UP_FAN:
			fAngle = (float)((rand() % 90) + 157) / 100.f;

		default:
			break;
		}

		// �ړ��ʑ��
		move.x = sinf(fAngle + D3DX_PI) * 3.0f;
		move.y = cosf(fAngle - D3DX_PI) * 3.0f;
		move.z = 0.0f;

		// �|���S������
		CEffect::Create(pos, size, move, pTex);
	}
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
LPDIRECT3DTEXTURE9 Particle::TextureCreate(LPCSTR pSrcFile, LPDIRECT3DTEXTURE9 pTex)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pSrcFile, &pTex);

	return pTex;
}
