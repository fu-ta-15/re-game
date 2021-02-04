//##################################################################################################################################################################//
//
// �L�[�{�[�h���͏��� [input.hp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//

#include "input.h"

//�O���[�o���ϐ�
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;
BYTE g_aKeyState[256];
BYTE g_aKeyStatePresse[256];
BYTE g_aKeyStateTrigger[256];
BYTE g_aKeyStateRelease[256];
BYTE g_aKeyStateRepeat[256];
BYTE g_aCountRepeat[256];


//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{// DirectInput�I�u�W�F�N�g�̐���
		return E_FAIL;
	}
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{// ���̓f�o�C�X�̐���
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{// �f�[�^�t�H�[�}�b�g�̐ݒ�
		return E_FAIL;
	}
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{// �������[�h�̐ݒ�
		return E_FAIL;
	}

	// �A�N�Z�X���̎擾
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void UninitKeyboard(void)
{
	if (g_pDevKeyboard != NULL)
	{// �f�[�^�t�H�[�}�b�g�̊J��
	 // �A�N�Z�X���̔j��
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}
	if (g_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=====================================================================================================================================================================//
// �X�V����
//=====================================================================================================================================================================//
void UpdateKeyboard(void)
{
	BYTE aKeyState[256];

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nKey = 0; nKey < 256; nKey++)
		{
			g_aKeyStatePresse[nKey] = aKeyState[nKey];								// �v���X
			g_aKeyStateTrigger[nKey] = (~g_aKeyState[nKey])&(aKeyState[nKey]);		// �g���K�[
			g_aKeyStateRelease[nKey] = (g_aKeyState[nKey])&(~aKeyState[nKey]);		// �����[�X
			g_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		//�A�N�Z�X���̎擾
		g_pDevKeyboard->Acquire();
	}
}

//=====================================================================================================================================================================//
// �L�[�{�[�h���̎擾
//=====================================================================================================================================================================//
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
bool GetKeyboardPresse(int nKey)
{
	return(g_aKeyStatePresse[nKey] & 0x80) ? true : false;
}
