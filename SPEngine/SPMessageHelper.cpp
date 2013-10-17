//////////////////////////////////////////////////////////////////////////
/// @file		SPMessageHelper.cpp the implement file of SPMessageHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPMessageHelper.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPMessageHelper::SPMessageHelper(void)
	{
	}


	SPMessageHelper::~SPMessageHelper(void)
	{
	}

	void SPMessageHelper::Msg(TCHAR *szFormat, ...)
	{
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

		MessageBox(NULL, szBuffer, TEXT("SPEngine"),
			MB_OK | MB_ICONERROR);
	}

	void SPMessageHelper::Msg( std::string msg, ... )
	{
		TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		const int LASTCHAR = NUMCHARS - 1;

		// Format the input string
		va_list pArgs;
		va_start(pArgs, msg);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintf(szBuffer, NUMCHARS - 1, SPStringHelper::MultiByteCStringToWideChar(msg.c_str()), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		MessageBox(NULL, szBuffer, TEXT("SPEngine"),
			MB_OK | MB_ICONERROR);
	}

}
