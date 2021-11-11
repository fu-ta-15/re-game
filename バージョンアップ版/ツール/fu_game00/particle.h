//*****************************************************************************
//
// �p�[�e�B�N������ [particle.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "effect.h"

//-----------------------------------------------------------------------------
// ���O���
//-----------------------------------------------------------------------------
namespace Particle
{
	// �p�[�e�B�N���̎��
	enum ParticleType
	{
		TYPE_NONE = 0,
		TYPE_EXPLOSION,
		TYPE_RIGHT_FAN,
		TYPE_LEFT_FAN,
		TYPE_UP_FAN,
		TYPE_DOWN_FAN,
		PARTICLE_MAX
	};

	// �p�[�e�B�N���̐���
	void SetParticle(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int EfeectNum, ParticleType type, const LPCSTR pSrcFile);

	// �e�N�X�`���̐ݒ�
	LPDIRECT3DTEXTURE9 TextureCreate(LPCSTR pSrcFile, LPDIRECT3DTEXTURE9 pTex);
}

#endif // !_PARTICLE_H_
