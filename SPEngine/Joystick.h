#pragma once
#include "InputDevice.h"

namespace SPEngine
{
	class InputManager;

	class Joystick : public InputDevice
	{
	public:
		Joystick(void);
		~Joystick(void);

		bool UpdateDevice();

		// Used to create the game controllers.
		BOOL EnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData);
		BOOL IsXInputDevice( const GUID* pGuidProductFromDirectInput );

		bool LoadDevice(InputManager* manager, bool exclusive);
		bool Shutdown();

		int ButtonUp(unsigned int key);
		int ButtonDown(unsigned int key);

		POINT GetPosition();
		POINT GetZPosition();

		// Game controller device.
		DIJOYSTATE2 joyState;
		DIJOYSTATE2 lastJoyState;
		char m_name[256];
		unsigned long m_numButtons;

		// Left and right stick x and y positions.
		long xPos1;
		long yPos1;
		long xPos2;
		long yPos2;

		// Window handled (needed for game controllers).
		HWND hwnd;
	};
}

