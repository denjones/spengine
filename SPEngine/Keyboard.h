#pragma once
#include "InputDevice.h"

namespace SPEngine
{
	class InputManager;

	class Keyboard : public InputDevice
	{
	public:
		Keyboard(void);
		~Keyboard(void);

		bool UpdateDevice();

		bool LoadDevice(InputManager* manager, bool exclusive);
		bool Shutdown();

		int ButtonUp(unsigned int key);
		int ButtonDown(unsigned int key);

		int ButtonJustUp(unsigned int key);
		int ButtonJustDown(unsigned int key);

		POINT GetPosition();
		POINT GetZPosition();

		// Keyboard state.
		char keyState[256];
		char lastKeyState[256];
	};
}


