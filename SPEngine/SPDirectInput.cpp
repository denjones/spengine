//////////////////////////////////////////////////////////////////////////
/// @file		SPDirectInput.h the implement file of SPDirectInput class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPDirectInput.h"
#include "SPWindow.h"
#include "SPXInput.h"
#include "SPJoystick.h"

namespace SPEngine
{
	SPDirectInput::SPDirectInput(void)
	{
		directInput = NULL;
		CreateDirectInput();
	}


	SPDirectInput::~SPDirectInput(void)
	{
		ReleaseDirectInput();
	}

	bool SPDirectInput::CreateDirectInput()
	{
		if (FAILED(DirectInput8Create(SPWindow::GetSingleton().GetHInstance(), 
			DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, NULL)))
		{
			return false;
		}

		return true;
	}

	bool SPDirectInput::ReleaseDirectInput()
	{
		if (!directInput)
		{
			SPLogHelper::WriteLog("[DInput] WARNING: Trying to release empty DInput object!");
			return false;
		}

		directInput->Release();
		directInput = NULL;
		return true;
	}

	BOOL CALLBACK SPDirectInput::gJSEnumDeviceCallBack( const DIDEVICEINSTANCE *inst, void* pData )
	{
		SPJoystick* joy = (SPJoystick*)pData;

		if( SPXInput::IsXInputDevice( &inst->guidProduct ) )
			return DIENUM_CONTINUE;

		// Set to the first device found.
		if(SUCCEEDED(SPDirectInput::GetSingleton().GetDirectInput()->CreateDevice(inst->guidInstance, 
			&joy->device, NULL)))
		{
			if(SUCCEEDED(joy->device->SetDataFormat(&c_dfDIJoystick2)))
			{
				if(SUCCEEDED(joy->device->SetCooperativeLevel(SPWindow::GetSingleton().GetHWnd(),
					DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
				{
					if(SUCCEEDED(joy->device->Acquire()))
					{
						strcpy_s(joy->m_name, (char*)inst->tszProductName);
						return DIENUM_STOP;
					}
				}
			}
		}

		// Return continue to try to init other connected devices.
		return DIENUM_CONTINUE;	
	}	
}

