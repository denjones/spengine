#pragma once
#include "SPComponent.h"
#include <dinput.h>
#include "InputDevice.h"
#include <vector>
#include "Keyboard.h"
#include "Joystick.h"
#include "Mouse.h"
#include <XInput.h>
#include "XController.h"

using namespace std;

namespace SPEngine
{
	enum InputDeviceType
	{
		TypeMouse,
		TypeKeyboard,
		Joystick1,
		Joystick2,
	};

	class InputManager : public SPComponent
	{
		LPDIRECTINPUT8 directInput;
		vector<InputDevice*> inputDevices;
		vector<XController*> xControllers;
		int maxXController;

	public:
		static Keyboard*	keyboard;
		static Joystick*	joystick;
		static Mouse*		mouse;

	public:
		InputManager(void);
		~InputManager(void);

		bool Load();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();
		bool Unload();
		bool SetMaxXController(int max);

		LPDIRECTINPUT8 DirectInput();
		static BOOL CALLBACK gJSEnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData);

		int KeyUp(unsigned int key);
		int KeyDown(unsigned int key);

		int MouseButtonUp(unsigned int button);
		int MouseButtonDown(unsigned int button);

		POINT GetMousePos();
		long GetMouseWheelPos();

		int XControllerButtonUp(unsigned int button);
		int XControllerButtonDown(unsigned int button);

		POINT XGetLeftStickPos();
		POINT XGetRightStickPos();

		int ControllerButtonUp(unsigned int button);
		int ControllerButtonDown(unsigned int button);

		POINT GetLeftStickPos();
		POINT GetRightStickPos();

		XController* GetXController(int num);
	};
}

