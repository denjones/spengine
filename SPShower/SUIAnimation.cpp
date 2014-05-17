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

	currentPoint.rectangle.X = 
		(endPoint.rectangle.X - startPoint.rectangle.X) * 
		GetTransition() + startPoint.rectangle.X;
	currentPoint.rectangle.Y =
		(endPoint.rectangle.Y - startPoint.rectangle.Y) * 
		GetTransition() + startPoint.rectangle.Y;
	currentPoint.rectangle.Width =
		(endPoint.rectangle.Width - startPoint.rectangle.Width) * 
		GetTransition() + startPoint.rectangle.Width;
	currentPoint.rectangle.Height =
		(endPoint.rectangle.Height - startPoint.rectangle.Height) * 
		GetTransition() + startPoint.rectangle.Height;

	currentPoint.rotation = 
		(endPoint.rotation - startPoint.rotation) * 
		GetTransition() + startPoint.rotation;
	currentPoint.rotationCenter = 
		(endPoint.rotationCenter - startPoint.rotationCenter) *
		GetTransition() + startPoint.rotationCenter;

	currentPoint.transparency = 
		(endPoint.transparency - startPoint.transparency) *
		GetTransition() + startPoint.transparency;

	currentPoint.backgroundX = 
		(endPoint.backgroundX - startPoint.backgroundX) *
		GetTransition() + startPoint.backgroundX;
	currentPoint.backgroundY = 
		(endPoint.backgroundY - startPoint.backgroundY) *
		GetTransition() + startPoint.backgroundY;


	//float startH, startS, startV;
	//float endH, endS, endV;

	//SPColorHelper::RGBtoHSV(
	//	startPoint.backgroundColor.r,
	//	startPoint.backgroundColor.g,
	//	startPoint.backgroundColor.b,
	//	&startH,
	//	&startS,
	//	&startV);

	//SPColorHelper::RGBtoHSV(
	//	endPoint.backgroundColor.r,
	//	endPoint.backgroundColor.g,
	//	endPoint.backgroundColor.b,
	//	&endH,
	//	&endS,
	//	&endV);

	//SPColorHelper::HSVtoRGB(
	//	&currentPoint.backgroundColor.r,
	//	&currentPoint.backgroundColor.g,
	//	&currentPoint.backgroundColor.b,
	//	GetTransition() * (endH - startH) + startH,
	//	GetTransition() * (endS - startS) + startS,
	//	GetTransition() * (endV - startV) + startV);

	//currentPoint.backgroundColor.a = 
	//	GetTransition() * (endPoint.backgroundColor.a - 
	//	startPoint.backgroundColor.a) + startPoint.backgroundColor.a;

	//currentPoint.backgroundColor.r = 
	//	GetTransition() * (endPoint.backgroundColor.r - 
	//	startPoint.backgroundColor.r) + startPoint.backgroundColor.r;

	//currentPoint.backgroundColor.g = 
	//	GetTransition() * (endPoint.backgroundColor.g - 
	//	startPoint.backgroundColor.g) + startPoint.backgroundColor.g;

	//currentPoint.backgroundColor.b = 
	//	GetTransition() * (endPoint.backgroundColor.b - 
	//	startPoint.backgroundColor.b) + startPoint.backgroundColor.b;

	currentPoint.backgroundColor = GetTransition() * (endPoint.backgroundColor -startPoint.backgroundColor) + startPoint.backgroundColor;

	currentPoint.layer = GetTransition() * (endPoint.layer - startPoint.layer)
		+ startPoint.layer;	

	if (state == Active)
	{
		currentPoint.backgroundImage = endPoint.backgroundImage;
		currentPoint.backgroundMode = endPoint.backgroundMode;
		currentPoint.backgroundPosition = endPoint.backgroundPosition;
		return;
	}
	else
	{
		currentPoint.backgroundImage = startPoint.backgroundImage;
		currentPoint.backgroundMode = startPoint.backgroundMode;
		currentPoint.backgroundPosition = startPoint.backgroundPosition;
	}
}

SUIProperties SUIAnimation::GetTargetPoint()
{
	return endPoint;
}
