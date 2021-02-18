#include "xpad.h"
#include "player.h"


void UpdateXpad(void)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	PLAYER *pPlayer = GetPlayer();

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
	}
	else
	{
		// Controller is not connected
	}

	// Zero value if thumbsticks are within the dead zone

	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		// A �{�^���������ꂽ
		if (pPlayer->Junp == false)
		{// �󒆂ɂ��Ȃ��Ƃ�
			pPlayer->move.y -= 20.0f;						// �W�����v��
			pPlayer->Junp = true;							// �W�����v��
		}

	}
}


