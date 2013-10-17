//////////////////////////////////////////////////////////////////////////
/// @file		SPUpdatableTexture.h the header file of SPUpdatableTexture class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"
#include "ISPUpdatable.h"
#include "SPPointer.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPUpdatableTexture class to represent a dynamic texture which 
	/// can be updated.
	///
	//////////////////////////////////////////////////////////////////////
	class SPUpdatableTexture :
		public SPTexture,
		public ISPUpdatable
	{
	public:
		virtual bool Update(float timeDelta) = 0;
		virtual bool Play() = 0;
		virtual bool Pause() = 0;
		virtual bool Stop() = 0;
	};

	typedef SPPointer<SPUpdatableTexture> SPUpdatableTexturePtr;
}


