#pragma once
#include "SPComponent.h"
#include <vmr9.h>
#include "SpriteManager3D.h"


namespace SPEngine
{
	class VideoManager : public SpriteManager3D
	{
	public:
		VideoManager(void);
		~VideoManager(void);

		bool Initialize();
		//bool Load();
		//bool Draw(float timeElapsed);
		//bool Update(float timeElapsed);
		//bool Unload();
		bool VerifyVMR9(void);
	};
}

