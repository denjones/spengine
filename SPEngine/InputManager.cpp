#include "StdAfx.h"
#include "InputManager.h"
#include "SPGame.h"

using namespace SPEngine;

InputManager::InputManager(void)
{
	directInput = NULL;	

	keyboard = new Keyboard();
	mouse = new Mouse();
	joystick = new Joystick();

	maxXController = 1;

	for (int num = 0; num < 4;num++ )
	{
		xControllers.push_back(new XController(num));
	}
}

Keyboard*	InputManager::keyboard = NULL;
Joystick*	InputManager::joystick = NULL;
Mouse*		InputManager::mouse = NULL;

InputManager::~InputManager(void)
{
	Unload();
}

bool InputManager::Load()
{
	if (FAILED(DirectInput8Create(currentGame->GetWindow()->GetHInstance(), 
		DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL)))
	{
		return false;
	}

	if (keyboard == NULL)
	{
		keyboard = new Keyboard();
	}
	
	if (mouse == NULL)
	{
		mouse = new Mouse();
	}
	
	if (joystick == NULL)
	{
		joystick = new Joystick();
	}

	for(int num = 0; num < 4; num++)
	{
		if (xControllers[num] == NULL)
		{
			xControllers[num] = new XController(num);
		}		
	}

	keyboard->LoadDevice(this, false);
	mouse->LoadDevice(this, false);
	joystick->LoadDevice(this, true);

	return true;
}

bool InputManager::Unload()
{
	if (directInput)
	{
		directInput->Release();
		directInput = NULL;
	}
	
	if(keyboard)
	{
		keyboard->Shutdown();
		delete keyboard;
		keyboard = NULL;
	}

	if (mouse)
	{
		mouse->Shutdown();
		delete mouse;
		mouse = NULL;
	}

	if (joystick)
	{
		joystick->Shutdown();
		delete joystick;
		joystick = NULL;
	}	

	for (int num = 0; num < 4;num++ )
	{
		if (xControllers[num])
		{
			delete xControllers[num];
			xControllers[num] = NULL;
		}		 
	}

	return true;
}

bool InputManager::Update( float timeElapsed )
{
	// Get the device state.
	if(mouse)
	{
		mouse->UpdateDevice();
	}

	if(keyboard)
	{
		keyboard->UpdateDevice();
	}

	if(joystick)
	{
		joystick->UpdateDevice();
	}

	for (int num = 0; num < maxXController;num++ )
	{
		xControllers[num]->UpdateDevice();
	}

	return true;
}

bool InputManager::Draw(float timeElapsed)
{
	return true;
}

bool InputManager::Initialize()
{
	// Everything took place in the constructor.
	// Force keyboard and mouse before considering the
	// system initialized.
	return (keyboard && mouse);
}


int InputManager::KeyUp(unsigned int key)
{
	if(!keyboard) return 0;
	return keyboard->ButtonUp(key);
}


int InputManager::KeyDown(unsigned int key)
{
	if(!keyboard) return 0;
	return keyboard->ButtonDown(key);
}


int InputManager::MouseButtonUp(unsigned int button)
{
	if(!mouse) return 0;
	return mouse->ButtonUp(button);
}


int InputManager::MouseButtonDown(unsigned int button)
{
	if(!mouse) return 0;
	return mouse->ButtonDown(button);
}


int InputManager::ControllerButtonUp(unsigned int button)
{
	if(!joystick) return 0;
	return joystick->ButtonUp(button);
}


int InputManager::ControllerButtonDown(unsigned int button)
{
	if(!joystick) return 0;
	return joystick->ButtonDown(button);
}


POINT InputManager::GetMousePos()
{
	POINT null = {0, 0};
	if(!mouse) return null;

	return mouse->GetPosition();
}


long InputManager::GetMouseWheelPos()
{
	if(!mouse) return 0;

	POINT wheel =  mouse->GetZPosition();
	return wheel.y;
}


POINT InputManager::GetLeftStickPos()
{
	POINT null = {0, 0};
	if(!joystick) return null;

	return joystick->GetPosition();
}


POINT InputManager::GetRightStickPos()
{
	POINT null = {0, 0};
	if(!joystick) return null;

	return joystick->GetZPosition();
}

BOOL InputManager::gJSEnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData)
{
	return joystick->EnumDeviceCallBack(inst, pData);
}

LPDIRECTINPUT8 InputManager::DirectInput()
{
	return directInput;
}

bool InputManager::SetMaxXController( int max )
{
	max = min(max, 4);

	maxXController = max;

	return true;
}

XController* InputManager::GetXController( int num )
{
	return xControllers[num];
}
