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

void SUITransition::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);
}

void SUITransition::Play()
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
}

void SUITransition::Stop()
{
	transitionPosition = 0;
	state = Hidden;
}

void SUITransition::Skip()
{
	if (CanSkip())
	{
		transitionPosition = 1;
		state = Active;
		return;
	}
}

void SUITransition::SetTime( float time )
{
	transitionOnTime = time;
	transitionOffTime = time;
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

void SUITransition::SetType( TransitionType setType )
{
	type = setType;
}

void SUITransition::SetCanSkip( bool setSkip )
{
	canSkip = setSkip; 
}

float SUITransition::GetTime()
{
	return transitionOnTime;
}

SUITransition::TransitionType SUITransition::GetType()
{
	return type;
}

