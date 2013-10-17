//////////////////////////////////////////////////////////////////////////
/// @file		ISPInputDevice.h the header file of ISPInputDevice interface.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief ISPInputDevice the interface of input device.
	///
	//////////////////////////////////////////////////////////////////////
	class ISPInputDevice
	{
	public:
		/// @name Loading
		/// @{
		virtual bool LoadDevice() = 0;
		virtual bool UpdateDevice() = 0;
		virtual bool UnloadDevice() = 0;
		/// @}

		/// @name Buttons
		/// @{
		virtual bool ButtonUp(unsigned int key) = 0;
		virtual bool ButtonJustUp(unsigned int key) = 0;
		virtual bool ButtonDown(unsigned int key) = 0;
		virtual bool ButtonJustDown(unsigned int key) = 0;
		/// @}

		/// @name Feedback
		/// @{
		virtual int GetPositionX() = 0;		
		virtual int GetPositionY() = 0;
		virtual int GetMaxPositionX() = 0;
		virtual int GetMaxPositionY() = 0;

		virtual int GetZPositionX() = 0;		
		virtual int GetZPositionY() = 0;
		virtual int GetMaxZPositionX() = 0;
		virtual int GetMaxZPositionY() = 0;		
		/// @}
	};

	typedef SPPointer<ISPInputDevice> SPInputDevicePtr;
}


