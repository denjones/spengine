//////////////////////////////////////////////////////////////////////////
/// @file		SPLogHelper.h the header file of SPLogHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <fstream>

using namespace std;
namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPLogHelper static class to provide helper function for
	/// recording logs.
	///
	//////////////////////////////////////////////////////////////////////
	class SPLogHelper
	{
	private:
		SPLogHelper(void);
		~SPLogHelper(void);

		static void CreatLogFile();
	public:
		static void WriteLog(string log, ...);
		static void WriteLog(wstring log, ...);
		static void WriteLog(TCHAR *szFormat, ...);		
	};
}
