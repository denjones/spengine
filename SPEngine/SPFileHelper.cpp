#include "StdAfx.h"
#include "SPFileHelper.h"
#include <shlwapi.h>

#pragma comment(lib,"shlwapi.lib")

namespace SPEngine
{
	SPFileHelper::SPFileHelper(void)
	{
	}


	SPFileHelper::~SPFileHelper(void)
	{
	}

	bool SPFileHelper::IsPathExists( SPString path )
	{
		return TRUE == PathFileExists(path.c_str());
	}

	bool SPFileHelper::CreatePath( SPString path )
	{
		if (path.size() == 0 || path == L"/" || path == L"\\")
		{
			return true;
		}

		if(IsPathExists(path.c_str()))
		{
			return true;
		}

		if(!CreatePath(GetUpperPath(path)))
		{
			return false;
		}

		if( FALSE == CreateDirectory(path.c_str(), NULL))
		{
			return false;
		}

		return true;
	}

	SPString SPFileHelper::GetUpperPath( SPString path )
	{
		SPString result1 = L"";
		SPString result2 = L"";

		if (path.find_last_of(L"\\") != wstring::npos)
		{
			result2 = path.substr(0, path.find_last_of(L"\\"));
		}

		if (path.find_last_of(L"/") != wstring::npos)
		{
			result1 = path.substr(0, path.find_last_of(L"/"));
		}

		return result1.size() > result2.size() ? result1 : result2;
	}

}