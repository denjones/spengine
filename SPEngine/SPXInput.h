//////////////////////////////////////////////////////////////////////////
/// @file		SPXInput.h the header file of base SPXInput class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#include "SPSingleton.h"
#include <XInput.h>

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////////
	/// @brief SPXInput to represent a XInput object.
	///
	/// In fact, there is no XInput object for now. The class just provide a
	/// check method to recognize if an input device is an XInput device.
	//////////////////////////////////////////////////////////////////////////
	class SPXInput : SPSingleton<SPXInput>
	{
	public:
		//-----------------------------------------------------------------------------
		// Enum each PNP device using WMI and check each device ID to see if it contains 
		// "IG_" (ex. "VID_045E&PID_028E&IG_00").  If it does, then it's an XInput device
		// Unfortunately this information can not be found by just using DirectInput 
		//-----------------------------------------------------------------------------
		static BOOL IsXInputDevice( const GUID* pGuidProductFromDirectInput );
	};
}