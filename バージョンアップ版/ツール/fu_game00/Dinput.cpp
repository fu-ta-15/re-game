//*****************************************************************************
//
// �Q�[���p�b�h���͏��� [input.hp]
// Author : SUZUKI FUUTA
//
//*****************************************************************************
#include "Dinput.h"

//-------------------------------------------------------------------
// �}�N����`
//-------------------------------------------------------------------
#define DEADZONE        2500            // �e����25%�𖳌��]�[���Ƃ���
#define RANGE_MAX       3000           // �L���͈͂̍ő�l
#define RANGE_MIN       -3000          // �L���͈͂̍ŏ��l

//-------------------------------------------------------------------
// �\���̂̒�`
//-------------------------------------------------------------------
typedef struct
{
	LPDIRECTINPUTDEVICE8 g_lpDIDevice = NULL;	// �W���C�p�b�h�̃f�o�C�X���
	DIJOYSTATE2 State;						// �v���X
	DIJOYSTATE2 Trigger;					// �g���K�[
	DIJOYSTATE2 Release;					// �����[�X
}CONTROLLER;								// �R���g���[���[�̏��


//-------------------------------------------------------------------
// �O���[�o���ϐ�
//-------------------------------------------------------------------
LPDIRECTINPUT8 g_lpDI = NULL;				// Dinput�̃|�C���^
CONTROLLER g_Controller;					// �R���g���[���[���̃|�C���^
bool g_bPress[JPPRESS_MAX];					// �v���X���
bool g_bTrigger[JPTRIGGER_MAX];				// �X�e�B�b�N��|������
bool g_bStick[JPTRIGGER_MAX];


//=====================================================================================================================================================================//
//����������
//=====================================================================================================================================================================//
HRESULT InitKeypad(HINSTANCE hInstance, HWND hWnd)
{
	// ������
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bPress[nCuntPress] = false;
	}

	//DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_lpDI, NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_lpDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	// �R���g���[���[���̏�����
	if (!g_Controller.g_lpDIDevice)
	{
		return E_FAIL;
	}

	// �{�^���̏�����
	for (int nCntButton = 0; nCntButton < 13; nCntButton++)
	{
		g_Controller.State.rgbButtons[nCntButton] = '\0';
		g_Controller.Trigger.rgbButtons[nCntButton] = '\0';
		g_Controller.Release.rgbButtons[nCntButton] = '\0';
	}

	// �L���l�`�F�b�N
	if (g_Controller.State.rgdwPOV[0] != 0xFFFFFFFF)
	{
		// �L��
	}

	//�f�[�^�t�H�[�}�b�g�̐ݒ�
	if (FAILED(g_Controller.g_lpDIDevice->SetDataFormat(&c_dfDIJoystick2)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_Controller.g_lpDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// ���X�e�B�b�N�̏�����
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMin = RANGE_MIN;
	diprg.lMax = RANGE_MAX;

	// X���͈̔͂�ݒ�
	diprg.diph.dwObj = DIJOFS_X;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	// Y���͈̔͂�ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	// Z���͈̔͂�ݒ�
	diprg.diph.dwObj = DIJOFS_Z;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	// Z��]�͈̔͂�ݒ�
	diprg.diph.dwObj = DIJOFS_RZ;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

	// �E�X�e�B�b�N�̏�����
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize = sizeof(dipdw);
	dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
	dipdw.diph.dwHow = DIPH_BYOFFSET;
	dipdw.dwData = DEADZONE;

	// X���͈̔͂�ݒ�
	dipdw.diph.dwObj = DIJOFS_X;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	// Y���͈̔͂�ݒ�
	dipdw.diph.dwObj = DIJOFS_Y;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	// Z���͈̔͂�ݒ�
	dipdw.diph.dwObj = DIJOFS_Z;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);
	// Z��]�͈̔͂�ݒ�
	dipdw.diph.dwObj = DIJOFS_RZ;
	g_Controller.g_lpDIDevice->SetProperty(DIPROP_DEADZONE, &dipdw.diph);

	//�A�N�Z�X���̎擾
	g_Controller.g_lpDIDevice->Acquire();

	return S_OK;
}

//=====================================================================================================================================================================//
//�I������
//=====================================================================================================================================================================//
void UninitKeypad(void)
{
	//�f�[�^�t�H�[�}�b�g�̊J��
	if (g_Controller.g_lpDIDevice != NULL)
	{
		//�A�N�Z�X���̔j��
		g_Controller.g_lpDIDevice->Unacquire();
		g_Controller.g_lpDIDevice->Release();
		g_Controller.g_lpDIDevice = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̊J��
	if (g_lpDI != NULL)
	{
		g_lpDI->Release();
		g_lpDI = NULL;
	}
}

//=====================================================================================================================================================================//
//�X�V����
//=====================================================================================================================================================================//
void UpdateKeypad(void)
{
	// �ϐ��錾
	DIJOYSTATE2 ControllerState;	// �R���g���[���[�̃{�^�����
	HRESULT hr;						// ��������������
	int nCntButton;					// �{�^���̌�

	if (g_Controller.g_lpDIDevice != NULL)
	{// �W���C�p�b�h���ڑ�����Ă�����|�[�����O�J�n
		hr = g_Controller.g_lpDIDevice->Poll();

		// �f�o�C�X����f�[�^���擾
		if (SUCCEEDED(hr = g_Controller.g_lpDIDevice->GetDeviceState(sizeof(DIJOYSTATE2), &ControllerState)))
		{// �X�e�B�b�N�ɏ�����
			JoypadPressInfo(ControllerState);			// �v���X
			JoypadTriggerInfo(ControllerState);			// �g���K�[

			// ���X�e�B�b�N�̏��
			g_Controller.State.lY = ControllerState.lY;			// lY�̃v���X
			g_Controller.State.lX = ControllerState.lX;			// lX�̃v���X
			g_Controller.State.lZ = ControllerState.lZ;			// lZ�̃v���X
			g_Controller.State.lRz = ControllerState.lRz;		// lRz�̃v���X

			CrossKeyPressInfo(ControllerState);

			// �v���X���̕ۑ�
			g_Controller.State.rgdwPOV[0] = ControllerState.rgdwPOV[0];

			for (nCntButton = 0; nCntButton < 13; nCntButton++)
			{
				// �g���K�[���̕ۑ�
				g_Controller.Trigger.rgbButtons[nCntButton] =
					(g_Controller.State.rgbButtons[nCntButton] ^ ControllerState.rgbButtons[nCntButton]) & ControllerState.rgbButtons[nCntButton];

				// �����[�X���̕ۑ�
				g_Controller.Release.rgbButtons[nCntButton] =
					(ControllerState.rgbButtons[nCntButton] ^ g_Controller.State.rgbButtons[nCntButton]) & ControllerState.rgbButtons[nCntButton];

				// �v���X���̕ۑ�
				g_Controller.State.rgbButtons[nCntButton] = ControllerState.rgbButtons[nCntButton];
			}
		}
		else
		{// �A�N�Z�X���̎擾
			g_Controller.g_lpDIDevice->Acquire();
		}
	}
}

//=====================================================================================================================================================================//
// �{�^�����̎擾
//=====================================================================================================================================================================//
bool GetKeypadTrigger(int nKey)
{// �g���K�[���̊m�F
	return (g_Controller.Trigger.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetKeypadPresse(int nKey)
{// �v���X���̊m�F
	return (g_Controller.State.rgbButtons[nKey] & 0x80) ? true : false;
}
bool GetKeypadReleace(int nKey)
{// �����[�X���̊m�F
	return (g_Controller.Release.rgbButtons[nKey] & 0x80) ? true : false;
}


//=====================================================================================================================================================================//
// �R�[���o�b�N�֐�
//=====================================================================================================================================================================//
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	HRESULT hr;

	hr = g_lpDI->CreateDevice(pdidInstance->guidInstance, &g_Controller.g_lpDIDevice, NULL);

	return DIENUM_CONTINUE;
}

//=====================================================================================================================================================================//
// �X�e�B�b�N���̎擾
//=====================================================================================================================================================================//
void JoypadPressInfo(DIJOYSTATE2 State)
{// �v���X
	bool bPress[JPPRESS_MAX] = { false,false,false,false };

	if (State.lX >= 3000)
	{// �E
		bPress[JPPRESS_RIGTH] = true;
	}
	else if (State.lX <= -3000)
	{// ��
		bPress[JPPRESS_LEFT] = true;
	}
	else if (State.lY >= 3000)
	{// ��
		bPress[JPPRESS_DOWN] = true;
	}
	else if (State.lY <= -3000)
	{// ��
		bPress[JPPRESS_UP] = true;
	}

	// ���
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bPress[nCuntPress] = bPress[nCuntPress];
	}
}
void JoypadTriggerInfo(DIJOYSTATE2 State)
{// �g���K�[
	bool bTrigger[JPTRIGGER_MAX] = { false,false,false,false };

	if (State.lX >= 3000)
	{// �E
		bTrigger[JPTRIGGER_RIGTH] = true;
	}
	else if (State.lX <= -3000)
	{// ��
		bTrigger[JPTRIGGER_LEFT] = true;
	}
	else if (State.lY >= 3000)
	{// ��
		bTrigger[JPPRESS_DOWN] = true;
	}
	else if (State.lY <= -3000)
	{// ��
		bTrigger[JPTRIGGER_UP] = true;
	}

	// ���
	for (int nCuntTrigger = 0; nCuntTrigger < JPPRESS_MAX; nCuntTrigger++)
	{
		g_bTrigger[nCuntTrigger] = g_bStick[nCuntTrigger] | !bTrigger[nCuntTrigger];
		g_bTrigger[nCuntTrigger] = !g_bTrigger[nCuntTrigger];

		g_bStick[nCuntTrigger] = bTrigger[nCuntTrigger];
	}
}

//=====================================================================================================================================================================//
// �X�e�B�b�N���̎擾
//=====================================================================================================================================================================//
bool *GetPadPlress(void)
{
	return &g_bPress[0];
}
bool *GetPadTrigger(void)
{
	return &g_bTrigger[0];
}

//=====================================================================================================================================================================//
// �\���L�[���̎擾
//=====================================================================================================================================================================//
void CrossKeyPressInfo(DIJOYSTATE2 State)
{
	bool bIsPush[D_CROSS_MAX] = { false,false,false,false };

	switch (State.rgdwPOV[0])
	{
		// ��
	case 0:
		bIsPush[D_CROSS_UP] = true;
		break;
		// �E��
	case 4500:
		bIsPush[D_CROSS_UP] = true;
		bIsPush[D_CROSS_RIGHT] = true;
		break;
		// �E
	case 9000:
		bIsPush[D_CROSS_RIGHT] = true;
		break;
		// �E��
	case 13500:
		bIsPush[D_CROSS_DOWN] = true;
		bIsPush[D_CROSS_RIGHT] = true;
		break;
		// ��
	case 18000:
		bIsPush[D_CROSS_DOWN] = true;
		break;
		// ����
	case 22500:
		bIsPush[D_CROSS_DOWN] = true;
		bIsPush[D_CROSS_LEFT] = true;
		break;
		// ��
	case 27000:
		bIsPush[D_CROSS_LEFT] = true;
		break;
		// ����
	case 31500:
		bIsPush[D_CROSS_UP] = true;
		bIsPush[D_CROSS_LEFT] = true;
		break;
	}
	// ���
	for (int nCuntPress = 0; nCuntPress < JPPRESS_MAX; nCuntPress++)
	{
		g_bPress[nCuntPress] = bIsPush[nCuntPress];
	}
}

void CrossKeyTriggerInfo(DIJOYSTATE2 State)
{
}

//=====================================================================================================================================================================//
// �R���g���[���[���̃|�C���^
//=====================================================================================================================================================================//
DIJOYSTATE2 *pGetPadCont(void)
{
	return &g_Controller.State;
}
