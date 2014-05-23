#include "StdAfx.h"
#include "SPRandomHelper.h"

namespace SPEngine
{
	int SPRandomHelper::seed = timeGetTime();
	bool SPRandomHelper::isInitialized = false;

	int SPRandomHelper::NextInt(int range)
	{
		Initialize();
		long long randomInt = 0;
		for(int i = 0; i < 10; i++)
		{
			int newDigit = (double)rand() / RAND_MAX * 10;
			randomInt = randomInt * 10 + newDigit;
		}
		double randomDouble = (double)randomInt / 10000000000.0;
		return randomDouble * range;
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