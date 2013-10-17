//////////////////////////////////////////////////////////////////////////
/// @file		SPJoystick.cpp the implement file of SPJoystick class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPJoystick.h"
#include "SPInputManager.h"
#include <wbemidl.h>
#include <oleauto.h>
#include "SPDirectInput.h"
#include "SPXInput.h"

namespace SPEngine
{
	SPJoystick::SPJoystick(void)
	{	
		device = NULL;
	}

	SPJoystick::~SPJoystick(void)
	{
	}

	BOOL SPJoystick::EnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData)
	{
		if( SPXInput::IsXInputDevice( &inst->guidProduct ) )
			return DIENUM_CONTINUE;

		// Set to the first device found.
		if(SUCCEEDED(SPDirectInput::GetSingleton().GetDirectInput()->CreateDevice(inst->guidInstance, 
			&device, NULL)))
		{
			if(SUCCEEDED(device->SetDataFormat(&c_dfDIJoystick2)))
			{
				if(SUCCEEDED(device->SetCooperativeLevel(hwnd,
					DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					if(SUCCEEDED(device->Acquire()))
					{
						strcpy_s(m_name, (char*)inst->tszProductName);
						return DIENUM_STOP;
					}
				}
			}
		}

		// Return continue to try to init other connected devices.
		return DIENUM_CONTINUE;		
	}

	bool SPJoystick::LoadDevice()
	{
		// Initialize the game controller.
		DIPROPRANGE range;
		DIDEVCAPS caps;

		SPDirectInput::GetSingleton().GetDirectInput()->EnumDevices(DI8DEVCLASS_GAMECTRL, 
			(LPDIENUMDEVICESCALLBACK)SPDirectInput::gJSEnumDeviceCallBack,
			NULL, DIEDFL_ATTACHEDONLY);

		if(!device)
		{
			return false;
		}

		range.diph.dwSize = sizeof(DIPROPRANGE);
		range.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		range.diph.dwHow = DIPH_BYOFFSET;
		range.lMin = -1000;
		range.lMax = 1000;
		range.diph.dwObj = DIJOFS_X;
		device->SetProperty(DIPROP_RANGE, &range.diph);
		range.diph.dwObj = DIJOFS_Y;
		device->SetProperty(DIPROP_RANGE, &range.diph);

		if(SUCCEEDED(device->GetCapabilities(&caps)))
		{
			numOfButton = caps.dwButtons;
		}
		else
		{
			numOfButton = 4;
		}

		return true;
	}

	bool SPJoystick::UnloadDevice()
	{
		if (device)
		{
			device->Unacquire();
			device->Release();
			device = NULL;
		}

		return true;
	}

	bool SPJoystick::UpdateDevice()
	{
		if(!device)
		{
			return false;
		}

		device->Poll();

		// Save old state for input comparing.
		memcpy(&lastJoyState, &joyState, sizeof(joyState));

		// If error getting device state, reacquire.
		if(FAILED(device->GetDeviceState(sizeof(DIJOYSTATE2), &joyState)))
		{
			if(FAILED(device->Acquire()))
			{
				return false;
			}

			if(FAILED(device->GetDeviceState(sizeof(DIJOYSTATE2), &joyState)))
			{
				return false;
			}
		}

		xPos1 = joyState.lX;
		yPos1 = joyState.lY;

		xPos2 = joyState.lZ;
		yPos2 = joyState.lRz;

		return true;
	}

	bool SPJoystick::ButtonUp(unsigned int button)
	{
		return !ButtonDown(button);
	}

	bool SPJoystick::ButtonDown(unsigned int button)
	{
		if (!device)
		{
			return false;
		}

		if(button < 0 || button >= m_numButtons)
		{
			return false;
		}

		return (joyState.rgbButtons[button] & 0x80) > 0;
	}

	bool SPJoystick::ButtonJustUp(unsigned int button)
	{
		if (!device)
		{
			return false;
		}

		if(button < 0 || button >= m_numButtons) 
		{
			return 0;
		}

		return (!(joyState.rgbButtons[button] & 0x80) &&
			joyState.rgbButtons[button] != lastJoyState.rgbButtons[button]);
	}

	bool SPJoystick::ButtonJustDown(unsigned int button)
	{
		if (!device)
		{
			return false;
		}

		if(button < 0 || button >= m_numButtons) 
		{
			return false;
		}

		return ((joyState.rgbButtons[button] & 0x80) &&
			joyState.rgbButtons[button] != lastJoyState.rgbButtons[button]);
	}
}