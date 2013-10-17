// HLSLCompiler.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <afx.h>
#include <iostream>
#include <string>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(L"*.fx");
	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		wcout << wstring(finder.GetFileName()) << endl;

		_wsystem(L"fxc.exe /Gec /T fx_2_0 /Fc " 
			+ finder.GetFileName() + "a /Fo" 
			+ finder.GetFileName() + "o "
			+ finder.GetFileName());
	}

	return 0;
}

