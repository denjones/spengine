#include "StdAfx.h"
#include "SUIAnimationManager.h"


SUIAnimationManager::SUIAnimationManager(void)
{
}


SUIAnimationManager::~SUIAnimationManager(void)
{
}

bool SUIAnimationManager::Update( float timeDelta )
{
	AnimationIterator iter = animations.begin();

	while(iter != animations.end())
	{
		if(!(*iter)->Update(timeDelta))
		{
			AnimationIterator currentIter = iter;
			iter--;

			*currentIter = NULL;
			animations.erase(currentIter);
		}

		iter++;
	}

	return true;
}
