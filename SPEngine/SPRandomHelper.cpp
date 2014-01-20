#include "StdAfx.h"
#include "SPRandomHelper.h"

namespace SPEngine
{
	int SPRandomHelper::seed = timeGetTime();
	bool SPRandomHelper::isInitialized = false;

	int SPRandomHelper::NextInt(int range)
	{
		Initialize();
		return rand() % range;
	}

	void SPRandomHelper::Initialize()
	{
		if (!isInitialized)
		{
			srand(seed);
			isInitialized = true;
		}
	}

}