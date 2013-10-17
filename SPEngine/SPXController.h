//////////////////////////////////////////////////////////////////////////
/// @file		SPXController.h the header file of SPXController class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <XInput.h>
#include <d3dx9math.h>
#include "ISPInputDevice.h"
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPXController the class to represent a XBox360 controller.
	///
	//////////////////////////////////////////////////////////////////////
	class SPXController : public ISPInputDevice
	{
		/// @name State variables
		/// @{
		int num;
		bool isConnected;
		float magnitudeLeft;
		float magnitudeRight;
		float lX;
		float lY;
		float rX;
		float rY;

		XINPUT_STATE xState;
		XINPUT_STATE lastXState;
		/// @}

	public:
		SPXController(void);
		SPXController(int setNum);
		virtual ~SPXController(void);

		/// @name Implemented methods
		/// @{
		bool LoadDevice();
		bool UnloadDevice();
		bool UpdateDevice();		

		bool ButtonUp(unsigned int button);
		bool ButtonDown(unsigned int button);
		bool ButtonJustUp(unsigned int button);
		bool ButtonJustDown(unsigned int button);

		int GetPositionX() { return xState.Gamepad.sThumbLX; }		
		int GetPositionY() { return xState.Gamepad.sThumbLY; }
		int GetMaxPositionX() { return 32767;}
		int GetMaxPositionY() { return 32767; }

		int GetZPositionX(){ return xState.Gamepad.sThumbRX; }		
		int GetZPositionY(){ return xState.Gamepad.sThumbRY; }
		int GetMaxZPositionX() { return 32767; }
		int GetMaxZPositionY() { return 32767; }	
		/// @}

		/// @name Properties
		/// @{
		int Num() { return num; }
		bool IsConnected() { return isConnected; }

		float MagnitudeLeft() {	return magnitudeLeft; }
		float MagnitudeRight() { return magnitudeRight; }

		float LeftPositionX() { return lX; }
		float LeftPositionY() { return lY; }
		float RightPostionX() { return rX; }
		float RightPostionY() { return rY; }
		/// @}

		/// @brief Set Vibration. 32767 at max.
		bool SetVibration(int left, int right);

		/// @brief Reset state.
		bool Reset();
	};

	typedef SPPointer<SPXController> SPXControllerPtr;
}

