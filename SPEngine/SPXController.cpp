//////////////////////////////////////////////////////////////////////////
/// @file		SPXController.cpp the implement file of SPXController class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPXController.h"

namespace SPEngine
{
	SPXController::SPXController(void)
	{
		num = 0;
		LoadDevice();
	}

	SPXController::SPXController(int setNum)
	{
		num = setNum;
		LoadDevice();		
	}

	SPXController::~SPXController(void)
	{
	}

	bool SPXController::UpdateDevice()
	{
		if (!isConnected)
		{
			return false;
		}

		lastXState = xState;

		if (SUCCEEDED(XInputGetState(num, &xState)))
		{
			float LX = xState.Gamepad.sThumbLX;
			float LY = xState.Gamepad.sThumbLY;

			//determine how far the controller is pushed
			float magnitudeL = sqrt(LX*LX + LY*LY);

			//determine the direction the controller is pushed
			lX = LX / magnitudeL;
			lY = LY / magnitudeL;


			//check if the controller is outside a circular dead zone
			if (magnitudeL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				//clip the magnitude at its expected maximum value
				if (magnitudeL > 32767) magnitudeL = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitudeL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				magnitudeLeft = magnitudeL / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitudeL = 0.0;
				magnitudeLeft = 0.0;
			}


			// Do the same for the right
			float RX = xState.Gamepad.sThumbRX;
			float RY = xState.Gamepad.sThumbRY;

			//determine how far the controller is pushed
			float magnitudeR = sqrt(RX*RX + RY*RY);

			//determine the direction the controller is pushed
			rX = RX / magnitudeR;
			rY = RY / magnitudeR;


			//check if the controller is outside a circular dead zone
			if (magnitudeR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				//clip the magnitude at its expected maximum value
				if (magnitudeR > 32767) magnitudeR = 32767;

				//adjust magnitude relative to the end of the dead zone
				magnitudeR -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

				//optionally normalize the magnitude with respect to its expected range
				//giving a magnitude value of 0.0 to 1.0
				magnitudeRight = magnitudeR / (32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE);
			}
			else //if the controller is in the deadzone zero out the magnitude
			{
				magnitudeR = 0.0;
				magnitudeRight = 0.0;
			}		
		}
		else
		{
			isConnected = false;
			magnitudeLeft = 0;
			magnitudeRight = 0;
			lX = 0;
			lY = 0;
			rX = 0;
			rY = 0;
		}	

		return true;
	}

	bool SPXController::ButtonJustDown(unsigned int button)
	{
		if (((lastXState.Gamepad.wButtons | button)
			!= lastXState.Gamepad.wButtons) &&
			ButtonDown(button))
		{
			return true;
		}

		return false;
	}

	bool SPXController::ButtonJustUp(unsigned int button)
	{
		if (((lastXState.Gamepad.wButtons | button)
			== lastXState.Gamepad.wButtons) &&
			ButtonUp(button))
		{
			return true;
		}
		return false;
	}

	bool SPXController::ButtonUp( unsigned int button )
	{
		if (!isConnected)
		{
			return false;
		}

		return !ButtonDown(button);
	}

	bool SPXController::ButtonDown(unsigned int button )
	{
		if (!isConnected)
		{
			return false;
		}

		if ((xState.Gamepad.wButtons | button) == xState.Gamepad.wButtons)
		{
			return true;
		}

		return false;
	}

	bool SPXController::SetVibration(int left, int right)
	{
		// use any value between 0-65535 here
		left = max(0, left);
		left = min(65535, left);

		right = max(0, right);
		right = min(65535, right);

		XINPUT_VIBRATION vibration;
		ZeroMemory( &vibration, sizeof(XINPUT_VIBRATION) );
		vibration.wLeftMotorSpeed = left;
		vibration.wRightMotorSpeed = right; 
		XInputSetState( num, &vibration );

		return true;
	}

	bool SPXController::Reset()
	{
		ZeroMemory( &xState, sizeof(XINPUT_STATE) );
		ZeroMemory( &lastXState, sizeof(XINPUT_STATE) );

		isConnected = false;
		magnitudeLeft = 0;
		magnitudeRight = 0;
		lX = 0;
		lY = 0;
		rX = 0;
		rY = 0;

		return true;
	}

	bool SPXController::LoadDevice()
	{
		Reset();

		if(ERROR_DEVICE_NOT_CONNECTED == XInputGetState(num, &xState))
		{			
			return false;
		}

		isConnected = true;

		return true;
	}

	bool SPXController::UnloadDevice()
	{
		isConnected = false;

		return true;
	}

}