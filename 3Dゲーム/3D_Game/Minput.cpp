//##################################################################################################################################################################//
//
// �}�E�X���͏��� [mouseinput.cpp]
// Author : SUZUKI FUUTA
//
//##################################################################################################################################################################//
#include "Minput.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define DEADZONE        2500            // �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX       10000           // �L���͈͂̍ő�l
#define RANGE_MIN       -10000          // �L���͈͂̍ŏ��l

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	LPDIRECTINPUTDEVICE8 g_lpMIDevice = NULL;	// �W���C�p�b�h�̃f�o�C�X���
	DIMOUSESTATE State;						// �v���X
	DIMOUSESTATE Trigger;					// �g���K�[
	DIMOUSESTATE Release;					// �����[�X
}MOUSE;								// �R���g���[���[�̏��


//-------------------------------------------------------------------
// �O���[�o���ϐ�
//-------------------------------------------------------------------
LPDIRECTINPUT8 g_lpMI = NULL;				// Dinput�̃|�C���^
MOUSE g_Mouse;					// �R���g���[���[���̃|�C���^
bool g_bMPress[JPPRESS_MAX];					// �v���X���
bool g_bMTrigger[JPTRIGGER_MAX];				// �X�e�B�b�N��|������


//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{

	// ������
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bMPress[nCuntPress] = false;
	}

	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_lpMI, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_lpMI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumMouseCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// �R���g���[���[���̏�����
	if (!g_Mouse.g_lpMIDevice)
	{
		return E_FAIL;
	}

	// �{�^���̏�����
	for (int nCntButton = 0; nCntButton < 4; nCntButton++)
	{
		g_Mouse.State.rgbButtons[nCntButton] = '\0';
		g_Mouse.Trigger.rgbButtons[nCntButton] = '\0';
		g_Mouse.Release.rgbButtons[nCntButton] = '\0';
	}


	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_Mouse.g_lpMIDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_Mouse.g_lpMIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}


	//�A�N�Z�X���̎擾
	g_Mouse.g_lpMIDevice->Acquire();

	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void UninitMouse(void)
{
	//�f�[�^�t�H�[�}�b�g�̊J��
	if (g_Mouse.g_lpMIDevice != NULL)
	{
		//�A�N�Z�X���̔j��
		g_Mouse.g_lpMIDevice->Unacquire();
		g_Mouse.g_lpMIDevice->Release();
		g_Mouse.g_lpMIDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_lpMI != NULL)
	{
		g_lpMI->Release();
		g_lpMI = NULL;
	}
}

//=====================================================================================================================================================================//
//�X�V����
//=====================================================================================================================================================================//
void UpdateMouse(void)
{
	// �ϐ��錾
	DIMOUSESTATE MouseState;	// �R���g���[���[�̃{�^�����
	HRESULT hr;						// ��������������
	int nCntButton;					// �{�^���̌�

	if (g_Mouse.g_lpMIDevice != NULL)
	{// �W���C�p�b�h���ڑ�����Ă�����|�[�����O�J�n
		hr = g_Mouse.g_lpMIDevice->Poll();

		// �f�o�C�X����f�[�^���擾
		if (SUCCEEDED(hr = g_Mouse.g_lpMIDevice->GetDeviceState(sizeof(DIMOUSESTATE), &MouseState)))
		{// �X�e�B�b�N�ɏ�����
			MousePressInfo(MouseState);			// �v���X
			MouseTriggerInfo(MouseState);			// �g���K�[

														// ���X�e�B�b�N�̏��
			g_Mouse.State.lY = MouseState.lY;			// lY�̃v���X
			g_Mouse.State.lX = MouseState.lX;			// lX�̃v���X
			g_Mouse.State.lZ = MouseState.lZ;

			for (int nCnt = 0; nCnt < 4; nCnt++)
			{// �v���X���̕ۑ�
				g_Mouse.State.rgbButtons[nCnt] = MouseState.rgbButtons[nCnt];
			}

			for (nCntButton = 0; nCntButton < 13; nCntButton++)
			{// �g���K�[���̕ۑ�
				g_Mouse.Trigger.rgbButtons[nCntButton] =
					(g_Mouse.State.rgbButtons[nCntButton] ^ MouseState.rgbButtons[nCntButton]) & MouseState.rgbButtons[nCntButton];

				// �����[�X���̕ۑ�
				g_Mouse.Release.rgbButtons[nCntButton] =
					(MouseState.rgbButtons[nCntButton] ^ g_Mouse.State.rgbButtons[nCntButton]) & MouseState.rgbButtons[nCntButton];

				// �v���X���̕ۑ�
				g_Mouse.State.rgbButtons[nCntButton] = MouseState.rgbButtons[nCntButton];
			}
		}
		else
		{// �A�N�Z�X���̎擾
			g_Mouse.g_lpMIDevice->Acquire();
		}
	}
}

//=====================================================================================================================================================================//
// �{�^�����̎擾
//=====================================================================================================================================================================//
bool GetMouseTrigger(int nKey)
{// �g���K�[���̊m�F
	return (g_Mouse.Trigger.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetMousePresse(int nKey)
{// �v���X���̊m�F
	return (g_Mouse.State.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetMouseReleace(int nKey)
{// �����[�X���̊m�F
	return (g_Mouse.Release.rgbButtons[nKey] & 0x80) ? true : false;
}

//=====================================================================================================================================================================//
// �R�[���o�b�N�֐�
//=====================================================================================================================================================================//
BOOL CALLBACK EnumMouseCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	hr = g_lpMI->CreateDevice(pdidInstance->guidInstance, &g_Mouse.g_lpMIDevice, NULL);

	return DIENUM_CONTINUE;
}

//=====================================================================================================================================================================//
// �X�e�B�b�N���̎擾
//=====================================================================================================================================================================//
void MousePressInfo(DIMOUSESTATE State)
{
	bool bPress[JPPRESS_MAX] = { false,false,false,false };

	if (State.lX >= 7000)
	{// �E
		bPress[JPPRESS_RIGTH] = true;
	}
	else if (State.lX <= -7000)
	{// ��
		bPress[JPPRESS_LEFT] = true;
	}
	else if (State.lY >= 7000)
	{
		bPress[JPPRESS_DOWN] = true;
	}
	else if (State.lY <= -7000)
	{
		bPress[JPPRESS_UP] = true;
	}

	// ���
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bMPress[nCuntPress] = bPress[nCuntPress];
	}
}

void MouseTriggerInfo(DIMOUSESTATE State)
{
	bool bTrigger[JPTRIGGER_MAX] = { false,false,false,false };

	if (State.lX >= 7000)
	{// �E
		bTrigger[JPTRIGGER_RIGTH] = true;
	}
	else if (State.lX <= -7000)
	{// ��
		bTrigger[JPTRIGGER_LEFT] = true;
	}
	else if (State.lY >= 7000)
	{
		bTrigger[JPTRIGGER_UP] = true;
	}
	else if (State.lY <= -7000)
	{
		bTrigger[JPTRIGGER_DOWN] = true;
	}


}


//=====================================================================================================================================================================//
// �X�e�B�b�N���̎擾
//=====================================================================================================================================================================//
bool *GetMousePlress(void)
{
	return &g_bMPress[0];
}
bool *GetMouseTrigger(void)
{
	return &g_bMTrigger[0];
}