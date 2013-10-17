#pragma once
#include "spcomponent.h"

namespace SPEngine
{
	class SPGUIManager : public SPComponent
	{
	public:
		SPGUIManager(void);
		~SPGUIManager(void);

		bool Initialize();
		bool Load();
		bool Unload();

		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		bool PostDraw();
	};

}

