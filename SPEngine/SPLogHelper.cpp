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

using namespace std;
namespace SPEngine
{
	bool SPLogHelper::isLoggingOn = true;
	bool SPLogHelper::isDebug = true;
	CCritSec SPLogHelper::logLock;

	SPLogHelper::SPLogHelper(void)
	{
		
	}

	SPLogHelper::~SPLogHelper(void)
	{

	}	

	void SPLogHelper::WriteLog( string log )
	{
		if (!isLoggingOn)
		{
			return;
		}

		logLock.Lock();

		ofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

		if (!outLogFile)
		{
			CreatLogFile();
			if (!outLogFile)
			{
				logLock.Unlock();
				return;
			}
		}

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		outLogFile << "[" <<
			sys.wYear << "-" << 
			setw(2) <<  setfill('0') << sys.wMonth << "-" << 
			setw(2) <<  setfill('0') << sys.wDay << " "<< 
			setw(2) <<  setfill('0') << sys.wHour << ":" <<
			setw(2) <<  setfill('0') << sys.wMinute << ":" <<
			setw(2) <<  setfill('0') << sys.wSecond << "] " <<
			log << endl;

		outLogFile.close();

		logLock.Unlock();
	}

	void SPLogHelper::WriteLog( wstring log )
	{
		if (!isLoggingOn)
		{
			return;
		}

		logLock.Lock();

		wofstream outLogFile;

		outLogFile.open("log\\spengine.log", ios::app);

		if (!outLogFile)
		{
			CreatLogFile();
			if (!outLogFile)
			{
				logLock.Unlock();
				return;
			}
		}

		SYSTEMTIME sys; 
		GetLocalTime( &sys ); 

		outLogFile << "[" <<
			sys.wYear << "-" << 
			setw(2) <<  setfill(L'0') << sys.wMonth << "-" << 
			setw(2) <<  setfill(L'0') << sys.wDay << " "<< 
			setw(2) <<  setfill(L'0') << sys.wHour << ":" <<
			setw(2) <<  setfill(L'0') << sys.wMinute << ":" <<
			setw(2) <<  setfill(L'0') << sys.wSecond << "] " <<
			log << endl;

		outLogFile.close();

		logLock.Unlock();
	}

	void SPLogHelper::CreatLogFile()
	{
		ofstream outLogFile;
		// Create folder
		_mkdir("log");
		outLogFile.open("log\\spengine.log", ios::app);
	}

	void SPLogHelper::TurnOnLogging()
	{
		isLoggingOn = true;
	}

	void SPLogHelper::TurnOffLogging()
	{
		isLoggingOn = false;
	}

	void SPLogHelper::WriteDebug(string log)
	{
		if (isDebug)
		{
			WriteLog(log);
		}
	}

	void SPLogHelper::WriteDebug(wstring log)
	{
		if (isDebug)
		{
			WriteLog(log);
		}
	}

}