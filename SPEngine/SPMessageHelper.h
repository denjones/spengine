//////////////////////////////////////////////////////////////////////////
/// @file		SPMessageHelper.h the header file of SPMessageHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPMessageHelper static class to provide helper function for
	/// message box displaying.
	///
	//////////////////////////////////////////////////////////////////////
	class SPMessageHelper
	{
	private:
		SPMessageHelper(void);
		~SPMessageHelper(void);
	public:
		static void Msg(TCHAR *szFormat, ...);
		static void Msg(std::string msg, ...);
	};
}


