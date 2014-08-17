#include "StdAfx.h"
#include "SUIAnimation.h"

#pragma warning (disable:4244)

SUIAnimation::SUIAnimation(void)
{
	state = Hidden;
}


SUIAnimation::~SUIAnimation(void)
{
}

void SUIAnimation::SetStartPoint( SUIProperties setStart )
{
	startPoint = setStart;
}

void SUIAnimation::SetEndPoint( SUIProperties setEnd )
{
	endPoint = setEnd;
}

SUIProperties SUIAnimation::GetCurrentPoint()
{
	return currentPoint;
}

void SUIAnimation::Update( float timeDelta )
{
	SUITransition::Update(timeDelta);

	if (state == Hidden)
	{
		return;
	}

	if (endPoint.x)
	{
		if (!currentPoint.x)
		{
			currentPoint.x = new int(*startPoint.x);
		}
		*currentPoint.x = 
			(*endPoint.x - *startPoint.x) * 
			GetTransition() + *startPoint.x;
	}

	if (endPoint.y)
	{
		if (!currentPoint.y)
		{
			currentPoint.y = new int(*startPoint.y);
		}
		*currentPoint.y =
			(*endPoint.y - *startPoint.y) * 
			GetTransition() + *startPoint.y;
	}

	if (endPoint.width)
	{
		if (!currentPoint.width)
		{
			currentPoint.width = new int(*startPoint.width);
		}
		*currentPoint.width =
			(*endPoint.width - *startPoint.width) * 
			GetTransition() + *startPoint.width;
	}

	if (endPoint.height)
	{
		if (!currentPoint.height)
		{
			currentPoint.height = new int(*startPoint.height);
		}
		*currentPoint.height =
			(*endPoint.height - *startPoint.height) * 
			GetTransition() + *startPoint.height;
	}
	
	if (endPoint.rotation)
	{
		if (!currentPoint.rotation)
		{
			currentPoint.rotation = new float(*startPoint.rotation);
		}
		*currentPoint.rotation = 
			(*endPoint.rotation - *startPoint.rotation) * 
			GetTransition() + *startPoint.rotation;
	}

	if (endPoint.rotationCenterX)
	{
		if (!currentPoint.rotationCenterX)
		{
			currentPoint.rotationCenterX = new float(*startPoint.rotationCenterX);
		}
		*currentPoint.rotationCenterX = 
			(*endPoint.rotationCenterX - *startPoint.rotationCenterX) *
			GetTransition() + *startPoint.rotationCenterX;
	}

	if (endPoint.rotationCenterY)
	{
		if (!currentPoint.rotationCenterY)
		{
			currentPoint.rotationCenterY = new float(*startPoint.rotationCenterY);
		}
		*currentPoint.rotationCenterY = 
			(*endPoint.rotationCenterY - *startPoint.rotationCenterY) *
			GetTransition() + *startPoint.rotationCenterY;
	}
	
	if (endPoint.transparency)
	{
		if (!currentPoint.transparency)
		{
			currentPoint.transparency = new float(*startPoint.transparency);
		}
		*currentPoint.transparency = 
			(*endPoint.transparency - *startPoint.transparency) *
			GetTransition() + *startPoint.transparency;
	}

	if (endPoint.backgroundX)
	{
		if (!currentPoint.backgroundX)
		{
			currentPoint.backgroundX = new int(*startPoint.backgroundX);
		}
		*currentPoint.backgroundX = 
			(*endPoint.backgroundX - *startPoint.backgroundX) *
			GetTransition() + *startPoint.backgroundX;
	}

	if (endPoint.backgroundY)
	{
		if (!currentPoint.backgroundY)
		{
			currentPoint.backgroundY = new int(*startPoint.backgroundY);
		}
		*currentPoint.backgroundY = 
			(*endPoint.backgroundY - *startPoint.backgroundY) *
			GetTransition() + *startPoint.backgroundY;
	}

	if (endPoint.backgroundColor)
	{
		if (!currentPoint.backgroundColor)
		{
			currentPoint.backgroundColor = new D3DCOLOR(*startPoint.backgroundColor);
		}
		*currentPoint.backgroundColor = GetTransition() * 
			(*endPoint.backgroundColor - *startPoint.backgroundColor) + *startPoint.backgroundColor;
	}
	
	if (endPoint.layer)
	{
		if (!currentPoint.layer)
		{
			currentPoint.layer = new float(*startPoint.layer);
		}
		*currentPoint.layer = GetTransition() * (*endPoint.layer - *startPoint.layer)
			+ *startPoint.layer;	
	}
	

	if (state == Active)
	{
		//currentPoint.backgroundImage = endPoint.backgroundImage;
		//currentPoint.backgroundMode = endPoint.backgroundMode;
		//currentPoint.backgroundPosition = endPoint.backgroundPosition;
		return;
	}
	else
	{
		//currentPoint.backgroundImage = startPoint.backgroundImage;
		//currentPoint.backgroundMode = startPoint.backgroundMode;
		//currentPoint.backgroundPosition = startPoint.backgroundPosition;
	}
}

SUIProperties SUIAnimation::GetTargetPoint()
{
	return endPoint;
}
