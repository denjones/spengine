#include "StdAfx.h"
#include "SPPathHelper.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPPointer<SPStringList> SPPathHelper::SplitPath( SPString path )
	{
		SPPointer<SPStringList> parts1 = SPStringHelper::Split(path, L"\\");
		SPPointer<SPStringList> parts2 = SPStringHelper::Split(path, L"/");
		if(parts1->size() < parts2->size())
		{
			return parts2;
		}

		return parts1;
	}

	void SPPathHelper::MakeSurePathExist( SPString path )
	{
		SPPointer<SPStringList> parts = SplitPath(path);
		SPString currentDir = (*parts)[0];
		for (int i = 0; i < parts->size() - 1; i++)
		{
			CreateDirectory(currentDir.c_str(), NULL);
			currentDir = currentDir + L"\\" + (*parts)[i + 1];
		}
	}
}