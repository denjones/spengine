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

		virtual void Load();
		virtual void Update(float timeElapsed);
		virtual void Draw(float timeElapsed);
		virtual void Initialize();
		virtual void Unload();

		void SetLocation(FPSLocation setLocation);
		FPSLocation GetLocation();

	};

	typedef SPPointer<FPSDisplayer> FPSDisplayerPtr;
}

