//*****************************************************************************
//
// �L�[�{�[�h���͏��� [input.hp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "keyinput.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKey::CKey()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKey::~CKey()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CKey::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���͏����N���X�̏����������Ăяo��
	CInput::Init(hInstance, hWnd);

	if (FAILED(m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDDevice, NULL)))
	{// ���̓f�o�C�X�̐���
		return E_FAIL;
	}
	if (FAILED(m_pDDevice->SetDataFormat(&c_dfDIKeyboard)))
	{// �f�[�^�t�H�[�}�b�g�̐ݒ�
		return E_FAIL;
	}
	if (FAILED(m_pDDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{// �������[�h�̐ݒ�
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	m_pDDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CKey::Uninit(void)
{
	//���͏����N���X�̏I�������Ăяo��
	CInput::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CKey::Update(void)
{
	BYTE aKeyState[KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < KEY_MAX; nKey++)
		{
			m_aKeyState[STATE_PRESSE] [nKey]	=	 aKeyState[nKey];											// �v���X

			m_aKeyState[STATE_TRIGGER][nKey]	=	 (~m_aKeyState[STATE_NONE][nKey])& (aKeyState[nKey]);		// �g���K�[

			m_aKeyState[STATE_RELEASE][nKey]	=	 (m_aKeyState[STATE_NONE][nKey]) & (~aKeyState[nKey]);		// �����[�X

			m_aKeyState[STATE_NONE]   [nKey]	=	 aKeyState[nKey];
		}
	}
	else
	{// �A�N�Z�X���̎擾
		m_pDDevice->Acquire();
	}
}

//=============================================================================
// ���͔���		[ ��ԁE�L�[�i���o�[ ]
//=============================================================================
bool CKey::GetState(STATE state, int nKey)
{
	return (m_aKeyState[state][nKey] & 0x80) != 0;
}
