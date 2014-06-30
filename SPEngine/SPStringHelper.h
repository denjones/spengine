//////////////////////////////////////////////////////////////////////////
/// @file		SPStringHelper.h the header file of SPStringHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-18
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>
#include <vector>
//#include <atlstr.h>

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPStringHelper static class to preform transformation to 
	///		std::string
	///
	//////////////////////////////////////////////////////////////////////
	class SPStringHelper
	{
	public:
		// ToString
		static string ToString(int intNum);
		static string ToString(float floatNum);
		static string ToString(float floatNum, int numOfDigit);
		static string ToString(double doubleNum, int numOfDigit);
		static string ToString(wstring str);
		static wstring ToWString(int intNum);
		static wstring ToWString(float floatNum);
		static wstring ToWString(float floatNum, int numOfDigit);
		static wstring ToWString(double doubleNum, int numOfDigit);
		static wstring ToWString(string s);

		// Transform between string and CString
		//LPSTR WideCharToMultiByteCString( const CString& strCS );
		//string WideCharToStdString(const CString& strcs);
		static LPOLESTR MultiByteCStringToWideChar( LPCSTR lpa );
		//CString MultiByteCStringToCString( LPCSTR lpa );
		//CString StdStringToCString( const std::string& stdStr );
		
		static LPCSTR StdStringToMultiByteCString(const std::string& stdStr);

		static int StringToInt(string str);
		static double StringToFloat(string str);
		static bool StringToBool(string str);

		static int StringToInt(wstring str);
		static double StringToFloat(wstring str);
		static bool StringToBool(wstring str);

		static wstring UTF8CStringToWString( LPCSTR lpa );
		static string WStringToUTF8String( wstring ws );

		static wstring XMLSurroundWith(wstring src, wstring surrounding);
		static string XMLSurroundWith(string src, string surrounding);

		static wstring XMLExcludeFrom(wstring src, wstring surrounding);
		static string XMLExcludeFrom(string src, string surrounding);

		static wstring XMLRemoveFirst(wstring src, wstring surrounding);
		static string XMLRemoveFirst(string src, string surrounding);

		static string Format(string str, ...);
		static wstring Format(wstring str, ...);

		static bool EqualsIgnoreCase(string str1, string str2);
		static bool EqualsIgnoreCase(wstring str1, wstring str2);

		static vector<wstring> Split(wstring str, wstring spliter);
	};
}


