//////////////////////////////////////////////////////////////////////////
/// @file		SPPathHelper.h the header file of SPPathHelper class.
/// @author		Ken.J
/// @version	Beta 0.11
/// @date		2014-07-01
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include "SPPointer.h"
#include "SPString.h"


using namespace std;

namespace SPEngine
{
	class SPPathHelper
	{
	public:
		static SPPointer<SPStringList> SplitPath(SPString path);
		static void MakeSurePathExist(SPString path);
	};
}

