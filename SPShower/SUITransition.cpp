#include "StdAfx.h"
#include "SUITransition.h"


SUITransition::SUITransition(void) : SPTransition()
{
	state = Hidden;
	transitionOnTime = 0;
	transitionOffTime = 0;
	type = Normal;

	// Important!
	canSkip = true;
	isDisplay = true;
}


SUITransition::~SUITransition(void)
{
}

bool SUITransition::Update( float timeDelta )
{
	return SPTransition::Update(timeDelta);
}

bool SUITransition::Play()
{
	if (transitionOnTime == 0)
	{
		transitionPosition = 1;
		state = Active;
	}

	if (state == Hidden)
	{
		transitionPosition = 0;
		state = TransitionOn;
	}

	return true;
}

bool SUITransition::Stop()
{
	transitionPosition = 0;
	state = Hidden;
	return true;
}

bool SUITransition::Skip()
{
	if (CanSkip())
	{
		transitionPosition = 1;
		state = Active;
		return true;
	}
	
	return false;
}

bool SUITransition::SetTime( float time )
{
	transitionOnTime = time;
	transitionOffTime = time;

	return true;
}

float SUITransition::GetTransition()
{
	float position = transitionPosition;

	switch (type)
	{
	case Normal:
		position = transitionPosition;
		break;

	case SlowIn:
		position = transitionPosition * transitionPosition;
		break;

	case SlowOut:
		position = - (transitionPosition - 1) * (transitionPosition - 1) + 1;
		break;

	case SlowInOut:
		position = (3 - 2 * transitionPosition) * transitionPosition * transitionPosition ;
		break;

	case FastInOut:
		position = transitionPosition * ( transitionPosition * (transitionPosition * 2 + -3)  + 2);
		break;
	}

	return position;
}

bool SUITransition::SetType( TransitionType setType )
{
	type = setType;

	return true;
}

bool SUITransition::SetCanSkip( bool setSkip )
{
	canSkip = setSkip; 
	return true;
}

