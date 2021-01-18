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
		// A ボタンが押された
		if (pPlayer->Junp == false)
		{// 空中にいないとき
			pPlayer->move.y -= 20.0f;						// ジャンプ力
			pPlayer->Junp = true;							// ジャンプ中
		}

	}
}


