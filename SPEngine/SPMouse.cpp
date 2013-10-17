//////////////////////////////////////////////////////////////////////////
/// @file		SPMouse.cpp the implement file of SPMouse class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPMouse.h"
#include "SPInputManager.h"
#include "SPWindow.h"
#include "SPDirectInput.h"
#include "SPConfigManager.h"

#ifdef CEGUI
#include "CEGUI.h"
#endif

namespace SPEngine
{
	SPMouse::SPMouse(void)
	{
		LoadDevice();
	}

	SPMouse::~SPMouse(void)
	{
		UnloadDevice();
	}

	bool SPMouse::LoadDevice()
	{
		// Reset states.
		xPos = 0;
		yPos = 0;
		lastXPos = 0;
		lastYPos = 0;
		wheelPos = 0;
		maxWidth = SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
		maxHeight = SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;
		memset(&lastMouseState, 0, sizeof(mouseState));
		memset(&mouseState, 0, sizeof(mouseState));		

		// Create input device1
		if(FAILED(SPDirectInput::GetSingleton().GetDirectInput()->CreateDevice(
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

		// Always non-exclusive.
		if(false) 
		{
			flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
		}
		else
		{
			flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		}

		// Set cooperative level
		if(FAILED(device->SetCooperativeLevel(
			SPWindow::GetSingleton().GetHWnd(), 
			flags)))
		{
			return false;
		}

		// Acquire device
		device->Acquire();

		return true;
	}

	bool SPMouse::UnloadDevice()
	{
		if (device)
		{
			device->Unacquire();
			device->Release();
			device = NULL;
		}

		return true;
	}

	bool SPMouse::UpdateDevice()
	{
		// Get the device state.
		if(!device)
		{
			return false;
		}

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

		// Get absolute mouse position.

		POINT mousePos;
		GetCursorPos(&mousePos);
		ScreenToClient(SPWindow::GetSingleton().GetHWnd(), 
			&mousePos);

		// Change the mouse position into relative position.

		RECT winRect;
		GetClientRect(SPWindow::GetSingleton().GetHWnd(), &winRect);

		float xRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth / 
			SPConfigManager::GetSingleton().GetCurrentConfig().windowWidth;
		float yRate = (float) SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight /
			SPConfigManager::GetSingleton().GetCurrentConfig().windowHeight ;

		lastXPos = xPos;
		lastYPos = yPos;

		if (winRect.right - winRect.left == 0)
		{
			xPos = 0;
		}
		else
		{
			xPos = mousePos.x * SPWindow::GetSingleton().GetWidth() 
				/ (winRect.right - winRect.left) * xRate;
		}

		if (winRect.bottom - winRect.top == 0)
		{
			yPos = 0;
		}
		else
		{
			yPos = mousePos.y * SPWindow::GetSingleton().GetHeight()
				/ (winRect.bottom - winRect.top) * yRate;
		}		

		// Update wheel position.

		wheelPos = mouseState.lZ;

#ifdef CEGUI
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

		if (ScrollUp())
		{
			CEGUI::System::getSingleton().injectMouseWheelChange(1);
		}

		if (ScrollDown())
		{
			CEGUI::System::getSingleton().injectMouseWheelChange(-1);
		}
#endif

		return true;
	}

	bool SPMouse::ButtonJustUp(unsigned int key)
	{
		if (!IsWithinWindow())
		{
			return true;
		}

		if(ButtonUp(key) && (mouseState.rgbButtons[key] !=
			lastMouseState.rgbButtons[key]))
		{
			return true;
		}

		return false;
	}

	bool  SPMouse::ButtonJustDown(unsigned int key)
	{
		if(ButtonDown(key) && (mouseState.rgbButtons[key] != 
			lastMouseState.rgbButtons[key]))
		{
			return true;
		}

		return false;
	}

	bool SPMouse::ButtonUp(unsigned int button)
	{
		if (!device)
		{
			return false;
		}

		if (!IsWithinWindow())
		{
			return true;
		}

		// If the button is not clicked we return false.
		return (!(mouseState.rgbButtons[button] & 0x80) &&
			mouseState.rgbButtons[button] != lastMouseState.rgbButtons[button]);
	}

	bool SPMouse::ButtonDown(unsigned int button)
	{
		if (!device || !IsWithinWindow())
		{
			return 0;
		}

		// If the button is clicked we return true.
		return (mouseState.rgbButtons[button] & 0x80) > 0;
	}

	bool SPMouse::IsWithinWindow()
	{
		return !(GetPositionX() < 0 
			|| GetPositionY() < 0 
			|| GetPositionX() >= SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth
			|| GetPositionY() >= SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight);
	}

	int SPMouse::GetMovementX()
	{
		//float xRate = (float)SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth / 
		//	SPConfigManager::GetSingleton().GetCurrentConfig().windowWidth;
		return xPos - lastXPos;
	}

	int SPMouse::GetMovementY()
	{
		//float yRate = (float) SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight /
		//	SPConfigManager::GetSingleton().GetCurrentConfig().windowHeight ;
		return yPos - lastYPos; 
	}

}