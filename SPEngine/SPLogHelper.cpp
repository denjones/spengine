//////////////////////////////////////////////////////////////////////////
/// @file		SPLogHelper.cpp the implement file of SPLogHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPLogHelper.h"
#include "SPStringHelper.h"
#include <direct.h>
#include <iomanip>

#pragma warning(disable:4996)

using namespace std;
namespace SPEngine
{
	SPLogHelper::SPLogHelper(void)
	{
	}


	SPLogHelper::~SPLogHelper(void)
	{

	}

	

	void SPLogHelper::WriteLog( string log, ... )
	{
		ofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

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
			setw(2) <<  setfill('0') << sys.wMonth << "-" << 
			setw(2) <<  setfill('0') << sys.wDay << " "<< 
			setw(2) <<  setfill('0') << sys.wHour << ":" <<
			setw(2) <<  setfill('0') << sys.wMinute << ":" <<
			setw(2) <<  setfill('0') << sys.wSecond << " : " <<
			str.append(szBuffer) << endl;

		outLogFile.close();
	}

	void SPLogHelper::WriteLog( TCHAR *szFormat, ... )
	{
		wstring log = wstring(szFormat);

		wofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

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
		va_start(pArgs, log);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintfW(szBuffer, NUMCHARS - 1, log.c_str(), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		wstring str;

		outLogFile <<
			sys.wYear << "-" << 
			setw(2) <<  setfill(L'0') << sys.wMonth << "-" << 
			setw(2) <<  setfill(L'0') << sys.wDay << " "<< 
			setw(2) <<  setfill(L'0') << sys.wHour << ":" <<
			setw(2) <<  setfill(L'0') << sys.wMinute << ":" <<
			setw(2) <<  setfill(L'0') << sys.wSecond << " : " <<
			str.append(szBuffer) << endl;

		outLogFile.close();

		//ofstream outLogFile;

		//outLogFile.open("log\\spengine.log", ios::app);

		//if (!outLogFile)
		//{
		//	CreatLogFile();
		//	if (!outLogFile)
		//		return;
		//}

		//TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		//const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		//const int LASTCHAR = NUMCHARS - 1;

		//// Format the input string
		//va_list pArgs;
		//va_start(pArgs, szFormat);

		//// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		//// character size minus one to allow for a NULL terminating character.
		//(void)StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
		//va_end(pArgs);

		//// Ensure that the formatted string is NULL-terminated
		//szBuffer[LASTCHAR] = TEXT('\0');

		//SYSTEMTIME sys; 
		//GetLocalTime( &sys ); 

		//outLogFile <<
		//	sys.wYear << "-" << 
		//	setw(2) <<  setfill('0') << sys.wMonth << "-" << 
		//	setw(2) <<  setfill('0') << sys.wDay << " "<< 
		//	setw(2) <<  setfill('0') << sys.wHour << ":" <<
		//	setw(2) <<  setfill('0') << sys.wMinute << ":" <<
		//	setw(2) <<  setfill('0') << sys.wSecond << " : " <<
		//	szBuffer << endl;

		//outLogFile.close();
	}

	void SPLogHelper::WriteLog( wstring log, ... )
	{
		wofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

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
		va_start(pArgs, log);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintfW(szBuffer, NUMCHARS - 1, log.c_str(), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		wstring str;

		outLogFile <<
			sys.wYear << "-" << 
			setw(2) <<  setfill(L'0') << sys.wMonth << "-" << 
			setw(2) <<  setfill(L'0') << sys.wDay << " "<< 
			setw(2) <<  setfill(L'0') << sys.wHour << ":" <<
			setw(2) <<  setfill(L'0') << sys.wMinute << ":" <<
			setw(2) <<  setfill(L'0') << sys.wSecond << " : " <<
			str.append(szBuffer) << endl;

		outLogFile.close();
	}

	void SPLogHelper::CreatLogFile()
	{
		ofstream outLogFile;
		// Create folder
		mkdir("log");
		outLogFile.open("log\\spengine.log", ios::app);
	}

}