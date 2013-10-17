#include "StdAfx.h"
#include "StringHelper.h"

using namespace std;

namespace SPEngine
{
	namespace StringHelper
	{
		//LPSTR WideCharToMultiByteCString( const CString& strCS )
		//{
		//	const UINT wLen = strCS.GetLength() + 1;
		//	UINT aLen = WideCharToMultiByte(CP_ACP,0,strCS,wLen,NULL,0,NULL,NULL);
		//	LPSTR lpa = new char[aLen];
		//	WideCharToMultiByte(CP_ACP,0,strCS,wLen,lpa,aLen,NULL,NULL);
		//	return lpa;
		//}

		//std::string WideCharToStdString(const CString& strcs)
		//{
		//	LPSTR l = WideCharToMultiByteCString(strcs);
		//	std::string stdStr(l);
		//	delete [] l;
		//	return stdStr;
		//}

		LPOLESTR MultiByteCStringToWideChar( LPCSTR lpa )
		{
			size_t aLen = strlen(lpa) + 1;
			int wLen = MultiByteToWideChar(CP_ACP,0,lpa,aLen,NULL,0);
			LPOLESTR lpw = new WCHAR[wLen];
			MultiByteToWideChar(CP_ACP,0,lpa,aLen,lpw,wLen);
			return lpw;
		}

		//CString MultiByteCStringToCString( LPCSTR lpa )
		//{
		//	LPOLESTR lpw = MultiByteCStringToWideChar(lpa);
		//	CString cstring(lpw);
		//	delete [] lpw;
		//	return  cstring;
		//}

		//CString StdStringToCString( const std::string& stdStr )
		//{
		//	return MultiByteCStringToCString(stdStr.c_str());
		//}

		LPCSTR StdStringToMultiByteCString(const std::string& stdStr)
		{
			return stdStr.c_str();
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
	}
}


