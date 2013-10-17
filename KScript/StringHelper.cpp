#include "StdAfx.h"
#include "StringHelper.h"
#include <vector>

#pragma warning(disable:4244)

using namespace std;

namespace KScript
{
	namespace StringHelper
	{
		string ReplaceAll(string str,const string old_value,
			const string new_value)     
		{     
			int curPos = 0;
			int   pos;
			while((pos = str.find(old_value, curPos)) != -1)
			{
				str.replace(pos, old_value.size(), new_value);
				curPos = pos + new_value.size();
			} 

			return str;     
		} 

		wstring ReplaceAll(wstring str,const wstring old_value,
			const wstring new_value)     
		{     
			int curPos = 0;
			int   pos;
			while((pos = str.find(old_value, curPos)) != -1)
			{
				str.replace(pos, old_value.size(), new_value);
				curPos = pos + new_value.size();
			} 

			return str;     
		} 

		string ToString( double doubleNum, int numOfDigit )
		{
			char c[256];
			_gcvt_s(c, 256, doubleNum, numOfDigit);

			return string(c);
		}

		string ToString( double doubleNum )
		{
			return ToString(doubleNum, 48);
		}

		string ToString( float floatNum, int numOfDigit )
		{
			char c[256];
			_gcvt_s(c, 256, floatNum, numOfDigit);

			return string(c);
		}

		string ToString( float floatNum )
		{
			return ToString(floatNum, 48);
		}

		string ToString( int intNum )
		{
			char c[256];
			_itoa_s(intNum, c, 10);

			return string(c);
		}

		wstring ToWString( float floatNum, int numOfDigit )
		{
			wchar_t c[256];
			swprintf_s(c, (size_t)256, L"%f", floatNum);

			bool dot = false;
			int num = 0;
			int currentDigit = 0;

			while(c[num] != L'\0' && num < 256)
			{
				if (currentDigit == numOfDigit)
				{
					c[num] = L'\0';
					break;
				}

				if (dot == true)
				{
					currentDigit++;
				}

				if (c[num] == L'.')
				{
					dot = true;
				}

				num++;
			}

			return wstring(c);
		}

		wstring ToWString( float floatNum )
		{
			return ToWString(floatNum, 48);
		}

		wstring ToWString( int intNum )
		{
			wchar_t c[256];
			_itow_s(intNum, c, 10);

			return wstring(c);
		}

		int StringToInt(string str)
		{
			return atoi(str.c_str());
		}

		int StringToInt( wstring str )
		{
			return _wtoi(str.c_str());
		}

		float StringToFloat(string str)
		{
			return atof(str.c_str());
		}

		float StringToFloat( wstring str )
		{
			return _wtof(str.c_str());
		}

		bool StringToBool( string str )
		{
			if (str == "true" || str == "ец")
			{
				return true;
			}

			return false;
		}

		bool StringToBool( wstring str )
		{
			if (str == L"true" || str == L"ец")
			{
				return true;
			}

			return false;
		}

		wstring UTF8CStringToWString( LPCSTR lpa )
		{
			int len = ::MultiByteToWideChar(CP_UTF8, 0, lpa, -1, NULL, 0);  
			if (len == 0) return L"";  

			wchar_t* unicode = new wchar_t[len];  
			::MultiByteToWideChar(CP_UTF8, 0, lpa, -1, unicode, len);  

			wstring result = unicode;

			delete [] unicode;

			return result;  
		}

		string WStringToUTF8String( wstring ws )
		{
			int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, NULL, 0, NULL, NULL);  
			if (utf8size == 0)  
			{  
				return "";  
			}  

			std::vector<char> resultstring(utf8size);  
			int convresult = ::WideCharToMultiByte(CP_UTF8, 0, ws.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);  

			return std::string(&resultstring[0]);  
		}

	}
}