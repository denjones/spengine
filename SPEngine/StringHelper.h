#pragma once
#include <string>
//#include <atlstr.h>

using namespace std;

namespace SPEngine
{
	namespace StringHelper
	{
		// ToString
		string ToString(int intNum);
		string ToString(float floatNum);
		string ToString(float floatNum, int numOfDigit);
		string ToString(double doubleNum, int numOfDigit);

		// Transform between string and cstring
		//LPSTR WideCharToMultiByteCString( const CString& strCS );
		//string WideCharToStdString(const CString& strcs);
		LPOLESTR MultiByteCStringToWideChar( LPCSTR lpa );
		//CString MultiByteCStringToCString( LPCSTR lpa );
		//CString StdStringToCString( const std::string& stdStr );
		LPCSTR StdStringToMultiByteCString(const std::string& stdStr);
	}
}


