//////////////////////////////////////////////////////////////////////////
/// @file		SPJoystick.h the header file of SPJoystick class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPDInputDevice.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPJoystick the class to represent a joystick controller.
	///
	//////////////////////////////////////////////////////////////////////
	class SPJoystick : public SPDInputDevice
	{
		friend class SPDirectInput;

		// Game controller device.
		DIJOYSTATE2 joyState;
		DIJOYSTATE2 lastJoyState;
		char m_name[256];
		unsigned long m_numButtons;

		// Left and right stick x and y positions.
		long xPos1;
		long yPos1;
		long xPos2;
		long yPos2;

		// Window handled (needed for game controllers).
		HWND hwnd;

	public:
		SPJoystick(void);
		virtual ~SPJoystick(void);

		bool UpdateDevice();
		bool LoadDevice();
		bool UnloadDevice();

		bool ButtonUp(unsigned int key);
		bool ButtonDown(unsigned int key);
		bool ButtonJustUp(unsigned int key);
		bool ButtonJustDown(unsigned int key);

		int GetPositionX() { return xPos1; }
		int GetPositionY() { return yPos1; }
		int GetMaxPositionX() { return 1000; }
		int GetMaxPositionY() { return 1000; }

		int GetZPositionX() { return xPos2; }		
		int GetZPositionY() { return yPos2; }
		int GetMaxZPositionX() { return 1000; }
		int GetMaxZPositionY() { return 1000; }

	protected:
		// Used to create the game controllers.
		BOOL EnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData);
		BOOL IsXInputDevice( const GUID* pGuidProductFromDirectInput );
	};

	typedef SPPointer<SPJoystick> SPJoystickPtr;
}

