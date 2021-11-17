//*****************************************************************************
//																																								
// ���C�g���� [light.cpp]																																		
// Author : SUZUKI FUUTA																																		
//																																								
//*****************************************************************************
//-----------------------------------------------------------------------------
//�@�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "light.h"
#include "renderer.h"
#include "fade.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ����������
//=============================================================================
void CLight::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GET_DEVICE;	

	// �ݒ�p�����x�N�g��
	D3DXVECTOR3 vecDir[MAX_LIGHT];			

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A�ɂ���
		ZeroMemory(&m_Light[nCntLight], sizeof(D3DLIGHT9));

		switch (nCntLight)
		{
		case 0:
			// ���C�g�̎�ނ�ݒ�
			m_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_Light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.2f, -0.8f, 0.4f);

			// ���K������
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);

			// ���ۑ�
			m_vecDir[nCntLight] = vecDir[nCntLight];

			// ���K���������𔽉f
			m_Light[nCntLight].Direction = vecDir[nCntLight];
			break;

		case 1:
			// ���C�g�̎�ނ�ݒ�
			m_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_Light[nCntLight].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);

			// ���K������
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);	

			// ���ۑ�
			m_vecDir[nCntLight] = vecDir[nCntLight];

			// ���K���������𔽉f
			m_Light[nCntLight].Direction = vecDir[nCntLight];
			break;

		case 2:
			// ���C�g�̎�ނ�ݒ�
			m_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

			// ���C�g�̊g�U����ݒ�
			m_Light[nCntLight].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

			// ���C�g�̕�����ݒ�
			vecDir[nCntLight] = D3DXVECTOR3(0.9f, -0.1f, 0.4f);

			// ���K������
			D3DXVec3Normalize(&vecDir[nCntLight], &vecDir[nCntLight]);

			// ���ۑ�
			m_vecDir[nCntLight] = vecDir[nCntLight];

			// ���K���������𔽉f
			m_Light[nCntLight].Direction = vecDir[nCntLight];
				break;

		default:
			break;
		}

		// ���C�g��ݒ肷��
		pDevice->SetLight(nCntLight, &m_Light[nCntLight]);

		// ���C�g��L���ɂ���
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

//=============================================================================
// �I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CLight::Update(void)
{
}
