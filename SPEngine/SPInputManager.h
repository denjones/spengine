//////////////////////////////////////////////////////////////////////////
/// @file		SPInputManager.h the header file of SPInputManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-17
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPComponent.h"
#include "SPDInputDevice.h"
#include "SPKeyboard.h"
#include "SPJoystick.h"
#include "SPMouse.h"
#include "SPXController.h"
#include "SPSingleton.h"
#include <vector>
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPInputManager the class to hold and manage input devices.
	///
	//////////////////////////////////////////////////////////////////////
	class SPInputManager : 
		public SPComponent,
		public SPSingleton<SPInputManager>
	{
		vector<SPInputDevicePtr> inputDevices;
		vector<SPXControllerPtr> xControllers;
		int numXController;

	protected:
		SPKeyboardPtr	keyboard;
		SPJoystickPtr	joystick;
		SPMousePtr		mouse;

	public:
		/// @name Get input devices
		/// @{
		SPKeyboardPtr	GetKeyboard() { return keyboard; }
		SPJoystickPtr	GetJoystickPtr() { return joystick; }
		SPMousePtr		GetMouse() { return mouse; }
		SPXControllerPtr GetXController(int num) { return xControllers[num]; }
		bool			SetCursor(SPString path);
		/// @}

	public:
		SPInputManager(void);
		virtual ~SPInputManager(void);

		/// @name Component methods
		/// @{
		bool Load();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();
		bool Unload();
		/// @}

		/// @brief Set the maximum number of XControllers.
		bool SetMaxXController(int max);		
	};
}

