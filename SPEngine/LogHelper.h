#pragma once
#include <fstream>

using namespace std;
namespace SPEngine
{
	class LogHelper
	{
		static ofstream outLogFile;

	private:
		LogHelper(void);
		~LogHelper(void);

		static void CreatLogFile();
	public:
		static void WriteLog(string log, ...);
		static void WriteLog(TCHAR *szFormat, ...);		
	};
}
