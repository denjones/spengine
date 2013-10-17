//////////////////////////////////////////////////////////////////////////
/// @file		SPRectangle.cpp the implement file of SPRectangle class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPRectangle.h"

namespace SPEngine
{
	SPRectangle::SPRectangle(void)
	{
		X = 0;
		Y = 0;
		Width = 0;
		Height = 0;
	}

	SPRectangle::SPRectangle(int setX, int setY,
		int setWidth, int setHeight)
	{
		X = setX;
		Y = setY;
		Width = setWidth;
		Height = setHeight;
	}

	SPRectangle::SPRectangle(const SPRectangle& rect)
	{
		X = rect.X;
		Y = rect.Y;
		Width = rect.Width;
		Height = rect.Height;
	}

	SPRectangle::~SPRectangle(void)
	{
	}

	RECT SPRectangle::CRect()
	{
		RECT rect;
		SetRect(&rect, X, Y, X + Width, Y + Height);

		return rect;
	}

	bool SPRectangle::IsPointInRect( int x, int y )
	{
		if (x >= X && y >= Y  && x < X + Width  && y < Y + Height)
		{
			return true;
		}

		return false;
	}

}