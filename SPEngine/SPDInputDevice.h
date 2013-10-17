//////////////////////////////////////////////////////////////////////////
/// @file		ISPInputDevice.h the header file of ISPInputDevice interface.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <dinput.h>
#include "ISPInputDevice.h"
#include "SPPointer.h"
#include "SPLogHelper.h"

#pragma comment(lib, "dinput8.lib")

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPDInputDevice the abstract class of DirectInput device.
	///
	//////////////////////////////////////////////////////////////////////
	class SPDInputDevice : public ISPInputDevice
	{
	protected:
		//InputDeviceType type;
		LPDIRECTINPUTDEVICE8 device;
		//InputManager* currentManager;
		int numOfButton;

	public:
		SPDInputDevice() : device(NULL){}
		virtual ~SPDInputDevice(void){}

		virtual bool LoadDevice() = 0;
		virtual bool UpdateDevice() = 0;
		virtual bool UnloadDevice() = 0;

		virtual bool ButtonUp(unsigned int key) = 0;
		virtual bool ButtonDown(unsigned int key) = 0;
		virtual bool ButtonJustUp(unsigned int key) = 0;
		virtual bool ButtonJustDown(unsigned int key) = 0;

		virtual int GetPositionX() = 0;		
		virtual int GetPositionY() = 0;
		virtual int GetMaxPositionX() = 0;
		virtual int GetMaxPositionY() = 0;
		virtual int GetZPositionX() = 0;		
		virtual int GetZPositionY() = 0;
		virtual int GetMaxZPositionX() = 0;
		virtual int GetMaxZPositionY() = 0;	
	};

	typedef SPPointer<SPDInputDevice> SPDInputDevicePtr;
}


