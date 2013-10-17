#include "StdAfx.h"
#include "MessageHelper.h"
#include "StringHelper.h"

namespace SPEngine
{
	MessageHelper::MessageHelper(void)
	{
	}


	MessageHelper::~MessageHelper(void)
	{
	}

	void MessageHelper::Msg(TCHAR *szFormat, ...)
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

	void MessageHelper::Msg( std::string msg, ... )
	{
		TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
		const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
		const int LASTCHAR = NUMCHARS - 1;

		// Format the input string
		va_list pArgs;
		va_start(pArgs, msg);

		// Use a bounded buffer size to prevent buffer overruns.  Limit count to
		// character size minus one to allow for a NULL terminating character.
		(void)StringCchVPrintf(szBuffer, NUMCHARS - 1, StringHelper::MultiByteCStringToWideChar(msg.c_str()), pArgs);
		va_end(pArgs);

		// Ensure that the formatted string is NULL-terminated
		szBuffer[LASTCHAR] = TEXT('\0');

		MessageBox(NULL, szBuffer, TEXT("SPEngine"),
			MB_OK | MB_ICONERROR);
	}

}
