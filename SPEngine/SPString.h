#pragma once
#include <string>
#include <vector>

namespace SPEngine
{
#ifdef UNICODE
#define SPString std::wstring
#else
#define	SPString std::string
#endif

	typedef std::vector<SPString> SPStringList;
	//typedef SPPointer<SPStringList> SPStringListPtr;
}