//////////////////////////////////////////////////////////////////////////
/// @file		SPKeyboard.h the header file of SPKeyboard class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPDInputDevice.h"
#include "SPPointer.h"
#include "SPString.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPXController the class to represent a XBox360 controller.
	///
	//////////////////////////////////////////////////////////////////////
	class SPKeyboard : public SPDInputDevice
	{
		/// @name Keyboard state.
		/// @{
		char keyState[256];
		char lastKeyState[256];
		/// @}

	public:
		SPKeyboard(void);
		virtual ~SPKeyboard(void);

		/// @name Input device methods
		/// @{
		bool UpdateDevice();
		bool LoadDevice();
		bool UnloadDevice();

		bool ButtonUp(unsigned int key);
		bool ButtonDown(unsigned int key);
		bool ButtonJustUp(unsigned int key);
		bool ButtonJustDown(unsigned int key);

		int GetPositionX() { return 0; }
		int GetPositionY() { return 0; }
		int GetMaxPositionX() { return 0; }
		int GetMaxPositionY() { return 0; }

		int GetZPositionX() { return 0; }		
		int GetZPositionY() { return 0; }
		int GetMaxZPositionX() { return 0; }
		int GetMaxZPositionY() { return 0; }
		/// @}

		int KeyNameToKey(SPString keyName);
	};

	typedef SPPointer<SPKeyboard> SPKeyboardPtr;
}


