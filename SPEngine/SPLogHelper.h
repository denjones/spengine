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
		static CCritSec logLock;
		static bool isLoggingOn;
		static bool isDebug;
		static void CreatLogFile();
	public:
		static void TurnOnLogging();
		static void TurnOffLogging();
		static void TurnOnDebug();
		static void TurnOffDebug();
		static void WriteDebug(string log);
		static void WriteDebug(wstring log);
		static void WriteLog(string log);
		static void WriteLog(wstring log);
		static bool IsDebug();
	};
}
