#pragma once
#include <string>
#include <WTypes.h>

using namespace std;

namespace KScript
{
	namespace StringHelper
	{
		string ReplaceAll(string str,const string old_value,const string new_value);
		wstring ReplaceAll(wstring str,const wstring old_value,const wstring new_value);

		string ToString( double doubleNum, int numOfDigit );
		string ToString( double doubleNum );
		string ToString( float floatNum, int numOfDigit );
		string ToString( float floatNum );
		string ToString( int intNum );

		wstring ToWString(int intNum);
		wstring ToWString(float floatNum);
		wstring ToWString(float floatNum, int numOfDigit);

		int StringToInt(string str);

		float StringToFloat(string str);

		bool StringToBool(string str);

		int StringToInt(wstring str);

		float StringToFloat(wstring str);

		bool StringToBool(wstring str);

		wstring UTF8CStringToWString( LPCSTR lpa );
		string WStringToUTF8String( wstring ws );
	}
}


