//*****************************************************************************
//
// �����_���[���� [renderer.h]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#ifndef _RENDERER_H_
#define _RENDERER_H_

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"


class CPause;
class CFade;

//-----------------------------------------------------------------------------
// �N���X
//-----------------------------------------------------------------------------
class CRenderer		// �����_���[�N���X
{
public:
	CRenderer();
	~CRenderer();

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�g�֐�
	LPDIRECT3DDEVICE9 GetDevice(void);

private:

	// FPS�`��֐�
	void DrawFPS(void);

	// �����o�ϐ�
	LPDIRECT3D9					m_pD3D			= NULL;		// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_pD3DDevice	= NULL;		// Device�I�u�W�F�N�g(�`��ɕK�v)
	LPD3DXFONT					m_pFont			= NULL;		// �t�H���g�ւ̃|�C���^
	D3DFILLMODE m_fillMode = D3DFILL_SOLID;				// ���C���[�t���[��	
};


#endif