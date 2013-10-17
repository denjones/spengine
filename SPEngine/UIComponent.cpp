#include "StdAfx.h"
#include "UIComponent.h"

using namespace SPEngine;

UIComponent::UIComponent(void)
{
	transitionOnTime = 0.2f;
	transitionOffTime = 0.2f;
	transitionPosition = 0;
	state = Hidden;
}


UIComponent::~UIComponent(void)
{

}

float UIComponent::TransitionOnTime()
{
	return transitionOnTime;
}

float UIComponent::TransitionPosition()
{
	return transitionPosition;
}

float UIComponent::TransitionOffTime()
{
	return transitionOffTime;
}

bool UIComponent::UpdateTransition(float timeDelta, int direction)
{
	// How much should we move by?
	float transitionDelta;

	// If time is 0, turn to 0 immediately, else count delta
	if (timeDelta == 0)
	{
		transitionDelta = 0;
	}
	else
	{
		transitionDelta =
		(float)(timeDelta / (direction > 0? transitionOnTime : transitionOffTime));
	}

	// Update the transition position.
	transitionPosition += transitionDelta * direction;

	// Transition finished?
	if (((transitionPosition <= 0) && (state == TransitionOff  || state == Hidden))||
		((transitionPosition >= 1) && (state == TransitionOn || state == Active)))
	{
		transitionPosition = min(1, transitionPosition);
		transitionPosition = max(0, transitionPosition);
		return true;
	}

	// Otherwise we are still busy transitioning.
	return false;
}

bool UIComponent::Update( float timeDelta )
{
	if (isDisplay &&
		(state == Hidden ||
		state == TransitionOff))
	{
		state = TransitionOn;
	}
	else if (!isDisplay &&
		(state == Active ||
		state == TransitionOn))
	{
		state = TransitionOff;
	}

	if (state == TransitionOn)
	{
		if (UpdateTransition(timeDelta, 1))
		{
			// Transition finished!
			state = Active;
		}
	}

	if (state == TransitionOff)
	{
		if (UpdateTransition(timeDelta, -1))
		{
			// When the transition finishes, remove the screen.
			state = Hidden;
		}
	}

	return true;
}

UIState UIComponent::State()
{
	return state;
}
