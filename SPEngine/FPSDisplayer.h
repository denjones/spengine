//////////////////////////////////////////////////////////////////////////
/// @file		FPSDisplayer.h the header file of FPSDisplayer class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPComponent.h"
#include "SPFont.h"
#include "SPPointer.h"

namespace SPEngine
{
	enum FPSLocation
	{
		RightTop,
		RightBottom,
		LeftTop,
		LeftBottom,
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief FPSDisplayer to display FPS on the screen.
	///
	//////////////////////////////////////////////////////////////////////
	class FPSDisplayer : public SPComponent
	{
		float	fps;
		int		frameCount;
		float	elapsedCountTime;
		FPSLocation location;
		SPFontPtr font;

	public:
		FPSDisplayer(void);
		virtual ~FPSDisplayer(void);

		virtual bool Load();
		virtual bool Update(float timeElapsed);
		virtual bool Draw(float timeElapsed);
		virtual bool Initialize();
		virtual bool Unload();

		bool SetLocation(FPSLocation setLocation);

	};

	typedef SPPointer<FPSDisplayer> FPSDisplayerPtr;
}

