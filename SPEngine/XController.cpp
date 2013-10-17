#include "StdAfx.h"
#include "XController.h"

using namespace SPEngine;

XController::XController(void)
{
	ZeroMemory( &xState, sizeof(XINPUT_STATE) );
	ZeroMemory( &lastXState, sizeof(XINPUT_STATE) );
}

XController::XController(int setNum)
{
	ZeroMemory( &xState, sizeof(XINPUT_STATE) );
	ZeroMemory( &lastXState, sizeof(XINPUT_STATE) );
	num = setNum;
}

XController::~XController(void)
{
}

bool XController::UpdateDevice()
{
	lastXState = xState;
	if (SUCCEEDED(XInputGetState(num, &xState)))
	{
		isConnected = true;

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

int XController::Num()
{
	return num;
}

bool XController::IsConnected()
{
	return isConnected;
}

float XController::MagnitudeLeft()
{
	return magnitudeLeft;
}

float XController::MagnitudeRight()
{
	return magnitudeRight;
}

D3DXVECTOR2 XController::LeftPosition()
{
	return D3DXVECTOR2(lX,lY);
}

D3DXVECTOR2 XController::RightPostion()
{
	return D3DXVECTOR2(rX,rY);
}

bool XController::ButtonJustDown(WORD button)
{
	if (((lastXState.Gamepad.wButtons | button)
		!= lastXState.Gamepad.wButtons) &&
		ButtonDown(button))
	{
		return true;
	}

	return false;
}

bool XController::ButtonJustUp(WORD button)
{
	if (((lastXState.Gamepad.wButtons | button)
		== lastXState.Gamepad.wButtons) &&
		ButtonUp(button))
	{
		return true;
	}
	return false;
}

bool XController::ButtonUp( WORD button )
{
	return !ButtonDown(button);
}

bool XController::ButtonDown(WORD button )
{
	if ((xState.Gamepad.wButtons | button) == xState.Gamepad.wButtons)
	{
		return true;
	}

	return false;
}

bool XController::SetVibration(int left, int right)
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

bool SPEngine::XController::Reset()
{
	ZeroMemory( &xState, sizeof(XINPUT_STATE) );
	ZeroMemory( &lastXState, sizeof(XINPUT_STATE) );

	return true;
}
