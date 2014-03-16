//////////////////////////////////////////////////////////////////////////
/// @file		SPMouse.h the header file of SPMouse class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPDInputDevice.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPMouse the class to represent a mouse device.
	///
	//////////////////////////////////////////////////////////////////////
	class SPMouse : public SPDInputDevice
	{
		/// @name Mouse state
		/// @{
		DIMOUSESTATE mouseState;
		DIMOUSESTATE lastMouseState;

		int xPos;
		int yPos;
		int lastXPos;
		int lastYPos;
		int wheelPos;

		int maxWidth;
		int maxHeight;
		/// @}

	public:
		SPMouse(void);
		virtual ~SPMouse(void);

		/// @name Input device methods
		/// @{
		bool UpdateDevice();
		bool LoadDevice();
		bool UnloadDevice();

		bool ButtonUp(unsigned int key);
		bool ButtonDown(unsigned int key);
		bool ButtonJustUp(unsigned int key);
		bool ButtonJustDown(unsigned int key);	

		int GetPositionX() { return xPos; }
		int GetPositionY() { return yPos; }
		int GetMaxPositionX() { return maxWidth; }
		int GetMaxPositionY() { return maxHeight; }

		int GetZPositionX() { return wheelPos; }		
		int GetZPositionY() { return wheelPos; }
		int GetMaxZPositionX() { return 255; }
		int GetMaxZPositionY() { return 255; }
		/// @}

		/// @name Properties
		/// @{
		bool IsWithinWindow();

		bool IsScrolledUp() { return (wheelPos > 0); }
		bool IsScrolledDown() { return (wheelPos < 0); }	
		int ScrolledPos() { return wheelPos; }

		int GetMovementX();
		int GetMovementY();
		/// @}
	};

	typedef SPPointer<SPMouse> SPMousePtr;
}
