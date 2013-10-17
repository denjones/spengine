//////////////////////////////////////////////////////////////////////////
/// @file		SPRectangle.h the header file of SPRectangle class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPRectangle to represent a rectangle.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPRectangle
	{
	public:
		int X;
		int Y;
		int Width;
		int Height;

	public:
		SPRectangle(void);
		SPRectangle(int setX, int setY, int setWidth, int setHeight);
		SPRectangle(const SPRectangle& rect);
		virtual ~SPRectangle(void);

		RECT CRect();
		bool IsPointInRect(int x, int y);
	};
}

