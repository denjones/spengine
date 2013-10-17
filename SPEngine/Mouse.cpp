#include "StdAfx.h"
#include "Mouse.h"
#include "InputManager.h"
#include "SPGame.h"
#include "CEGUI.h"

using namespace SPEngine;

Mouse::Mouse(void)
{
	int xPos = 0;
	int yPos = 0;
	int wheelPos = 0;
}

Mouse::~Mouse(void)
{
}

bool Mouse::LoadDevice(InputManager* manager, bool exclusive)
{
	currentManager = manager;

	// Create input device1
	if(FAILED(currentManager->DirectInput()->CreateDevice(
		GUID_SysMouse, &device, NULL)))
	{
		return false;
	}


	// Set data format
	if(FAILED(device->SetDataFormat(&c_dfDIMouse)))
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

	// Initialize
	//UpdateDevice();

	return true;
}

bool Mouse::Shutdown()
{
	if (device)
	{
		device->Unacquire();
		device->Release();
		device = NULL;
	}

	return true;
}

int Mouse::ButtonJustUp(unsigned int key)
{
	if(ButtonUp(key) && (mouseState.rgbButtons[key] !=
		lastMouseState.rgbButtons[key]))
	{
		return true;
	}

	return false;
}

int  Mouse::ButtonJustDown(unsigned int key)
{
	if(ButtonDown(key) && (mouseState.rgbButtons[key] != 
		lastMouseState.rgbButtons[key]))
	{
		return true;
	}

	return false;
}

int Mouse::ButtonUp(unsigned int button)
{
	if (!device)
	{
		return 0;
	}

	// If the button is not clicked we return false.
	return (!(mouseState.rgbButtons[button] & 0x80) &&
		mouseState.rgbButtons[button] != lastMouseState.rgbButtons[button]);
}

int Mouse::ButtonDown(unsigned int button)
{
	if (!device || GetPosition().x < 0 || GetPosition().y < 0 ||
		GetPosition().x > currentManager->CurrentGame()->GetWindow()->GetWidth() ||
		GetPosition().y > currentManager->CurrentGame()->GetWindow()->GetWidth())
	{
		return 0;
	}

	// If the button is clicked we return true.
	return mouseState.rgbButtons[button] & 0x80;
}

bool Mouse::UpdateDevice()
{
	// Get the device state.
	if(device)
	{
		// Save old state for input comparing.
		memcpy(&lastMouseState, &mouseState, sizeof(mouseState));

		// If error getting device state, reacquire.
		if(FAILED(device->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)))
		{
			if(FAILED(device->Acquire()))
			{
				return false;
			}

			if(FAILED(device->GetDeviceState(sizeof(DIMOUSESTATE), &mouseState)))
			{
				return false;
			}
		}

		xPos += mouseState.lX;
		yPos += mouseState.lY;
		wheelPos = mouseState.lZ;

		// Handle UI input
		CEGUI::System::getSingleton().injectMousePosition(GetPosition().x, GetPosition().y);

		if (ButtonJustDown(CEGUI::LeftButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
		}

		if (ButtonJustUp(CEGUI::LeftButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
		}
		
		if (ButtonJustDown(CEGUI::RightButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
		}

		if (ButtonJustUp(CEGUI::RightButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
		}
		
		if (ButtonJustDown(CEGUI::MiddleButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
		}

		if (ButtonJustUp(CEGUI::MiddleButton))
		{
			CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
		}

		if (ScollUp())
		{
			CEGUI::System::getSingleton().injectMouseWheelChange(1);
		}

		if (ScollDown())
		{
			CEGUI::System::getSingleton().injectMouseWheelChange(-1);
		}

	}

	return true;
}

POINT Mouse::GetPosition()
{
	POINT mousePos;
	GetCursorPos(&mousePos);
	ScreenToClient(currentManager->CurrentGame()->GetWindow()->GetHWnd(), 
		&mousePos);

	// Change the mouse position into relative position.

	RECT winRect;
	GetClientRect(currentManager->CurrentGame()->GetWindow()->GetHWnd(), &winRect);

	mousePos.x = (float)mousePos.x / (winRect.right - winRect.left) * 
		currentManager->CurrentGame()->GetWindow()->GetWidth();

	mousePos.y = (float)mousePos.y / (winRect.bottom - winRect.top) * 
		currentManager->CurrentGame()->GetWindow()->GetHeight();

	return mousePos;
}

POINT Mouse::GetZPosition()
{
	POINT p = {wheelPos, wheelPos };
	return p;
}

bool Mouse::ScollUp()
{
	return (wheelPos > 0);
}

bool Mouse::ScollDown()
{
	return (wheelPos < 0);
}

POINT Mouse::GetMovement()
{
	POINT  p = {xPos, yPos};
	return p;
}