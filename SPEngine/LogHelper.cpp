#include "StdAfx.h"
#include "LogHelper.h"
#include "StringHelper.h"
#include <direct.h>

using namespace std;
namespace SPEngine
{
	LogHelper::LogHelper(void)
	{
	}


	LogHelper::~LogHelper(void)
	{

	}

	ofstream LogHelper::outLogFile;

	void LogHelper::WriteLog( string log, ... )
	{
		outLogFile.open("log\\log.txt", ios::app);

		if (!outLogFile)
		{
			CreatLogFile();
			if (!outLogFile)
				return;
		}

		CHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		const int LASTCHAR = NUMCHARS - 1;

		// Format the input string
		va_list pArgs;
		va_start(pArgs, log);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintfA(szBuffer, NUMCHARS - 1, log.c_str(), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		string str;

		outLogFile <<
			sys.wYear << "-" << 
			sys.wMonth << "-" << 
			sys.wDay << " "<< 
			sys.wHour << ":" <<
			sys.wMinute << ":" <<
			sys.wSecond << " : " <<
			str.append(szBuffer) << endl;

		outLogFile.close();
	}

	void LogHelper::WriteLog( TCHAR *szFormat, ... )
	{
		outLogFile.open("log\\log.txt", ios::app);

		if (!outLogFile)
		{
			CreatLogFile();
			if (!outLogFile)
				return;
		}

		TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		const int LASTCHAR = NUMCHARS - 1;

		// Format the input string
		va_list pArgs;
		va_start(pArgs, szFormat);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		outLogFile <<
			sys.wYear << "-" << 
			sys.wMonth << "-" << 
			sys.wDay << " "<< 
			sys.wHour << ":" <<
			sys.wMinute << ":" <<
			sys.wSecond << " : " <<
			szBuffer << endl;

		outLogFile.close();
	}

	void LogHelper::CreatLogFile()
	{
		// Create folder
		mkdir("log");
		outLogFile.open("log\\log.txt", ios::app);
	}

}