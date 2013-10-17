#include "StdAfx.h"
#include "Keyboard.h"
#include "InputManager.h"
#include "SPGame.h"
#include "CEGUI.h"

using namespace SPEngine;

Keyboard::Keyboard(void)
{
	memset(keyState, 0, sizeof(keyState));
	memset(lastKeyState, 0, sizeof(lastKeyState));
}

Keyboard::~Keyboard(void)
{
}

bool Keyboard::LoadDevice(InputManager* manager, bool exclusive)
{
	currentManager = manager;

	// Create input device1
	if(FAILED(currentManager->DirectInput()->CreateDevice(
		GUID_SysKeyboard, &device, NULL)))
	{
		return false;
	}


	// Set data format
	if(FAILED(device->SetDataFormat(&c_dfDIKeyboard)))
	{
		return false;
	}

	// Set exclusive flags for cooperative level
	DWORD flags;

	if(exclusive) 
	{
		flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	}
	else
	{
		flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	}

	// Set cooperative level
	if(FAILED(device->SetCooperativeLevel(
		currentManager->CurrentGame()->GetWindow()->GetHWnd(), 
		flags)))
	{
		return false;
	}

	// Acquire device
	device->Acquire();

	return true;
}
bool Keyboard::Shutdown()
{
	if (device)
	{
		device->Unacquire();
		device->Release();
		device = NULL;
	}

	return true;
}

bool Keyboard::UpdateDevice()
{
	if(device)
	{
		// Save old state for input comparing.
		memcpy(lastKeyState, keyState, sizeof(keyState));

		// If error getting device state, reacquire.
		if(FAILED(device->GetDeviceState(sizeof(keyState), (LPVOID)keyState)))
		{
			if(FAILED(device->Acquire()))
			{
				return false;
			}

			if(FAILED(device->GetDeviceState(sizeof(keyState), (LPVOID)keyState)))
			{
				return false;
			}
		}

		for (UINT key = DIK_ESCAPE; key <= DIK_DELETE; key++)
		{
			if (ButtonJustDown(key))
			{
				CEGUI::System::getSingleton().injectKeyDown(key);
			}

			if (ButtonJustUp(key))
			{
				CEGUI::System::getSingleton().injectKeyUp(key);
			}
		}
	}

   return true;
}

int Keyboard::ButtonJustUp(unsigned int key)
{
	if(ButtonUp(key) && (keyState[key] != lastKeyState[key]))
	{
		return true;
	}

	return false;
}

int Keyboard::ButtonJustDown(unsigned int key)
{
	if(ButtonDown(key) && (keyState[key] != lastKeyState[key]))
	{
		return true;
	}

	return false;
}

int SPEngine::Keyboard::ButtonUp( unsigned int key )
{
	// If the key in the variable is not pressed then return false.
	return (!(keyState[key] & 0x80) && keyState[key] != lastKeyState[key]);
}

int SPEngine::Keyboard::ButtonDown( unsigned int key )
{
	// If the key in the variable is not pressed then return false.
	return keyState[key] & 0x80;
}

POINT SPEngine::Keyboard::GetPosition()
{
	// Doesn't have position.
	POINT p = { 0, 0 };
	return p;
}

POINT SPEngine::Keyboard::GetZPosition()
{
	// Doesn't have position.
	POINT p = { 0, 0 };
	return p;
}