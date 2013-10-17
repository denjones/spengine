#pragma once
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")

namespace SPEngine
{
	class InputManager;

	enum InputDeviceType;

	class InputDevice
	{
	protected:
		//InputDeviceType type;
		LPDIRECTINPUTDEVICE8 device;
		InputManager* currentManager;
		int numOfButton;

	public:
		InputDevice();
		~InputDevice(void);

		virtual bool LoadDevice(InputManager* manager, bool exclusive) = 0;

		virtual bool UpdateDevice() = 0;

		virtual int ButtonUp(unsigned int key) = 0;
		virtual int ButtonDown(unsigned int key) = 0;

		virtual POINT GetPosition() = 0;
		virtual POINT GetZPosition() = 0;

		virtual bool Shutdown() = 0;
	};
}


