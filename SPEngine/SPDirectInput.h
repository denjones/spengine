//////////////////////////////////////////////////////////////////////////
/// @file		SPDirectInput.h the header file of SPDirectInput class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <dinput.h>
#include "SPSingleton.h"
#include "SPDInputDevice.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPDirectInput to represent DirectInput object.
	///
	//////////////////////////////////////////////////////////////////////
	class SPDirectInput : public SPSingleton<SPDirectInput>
	{
		enum DInputDeviceType
		{
			Mouse,
			Keyboard,
			Joystick1,
			Joystick2,
		};

		LPDIRECTINPUT8 directInput; ///< DirectInput object.

	public:
		const LPDIRECTINPUT8 GetDirectInput() const {return directInput;}

	public:
		SPDirectInput(void);
		virtual ~SPDirectInput(void);

	private:
		bool CreateDirectInput();
		bool ReleaseDirectInput();

	public:
		SPDInputDevicePtr CreateDevice(DInputDeviceType type);

		static BOOL CALLBACK gJSEnumDeviceCallBack(const DIDEVICEINSTANCE *inst, void* pData);
		BOOL IsXInputDevice( const GUID* pGuidProductFromDirectInput );
	};
}


