#include "StdAfx.h"
#include "SUIAnimationManager.h"


SUIAnimationManager::SUIAnimationManager(void)
{
}


SUIAnimationManager::~SUIAnimationManager(void)
{
}

void SUIAnimationManager::Update( float timeDelta )
{
	AnimationIterator iter = animations.begin();

	while(iter != animations.end())
	{
		(*iter)->Update(timeDelta);
		if ((*iter)->TransitionPosition() >= 1)
		{
			AnimationIterator currentIter = iter;
			iter--;
			*currentIter = NULL;
			animations.erase(currentIter);
		}

		iter++;
	}
}
