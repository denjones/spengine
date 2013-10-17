#pragma once
#include "SPComponent.h"
#include "BaseScreen.h"
#include <vector>

using namespace std;

namespace SPEngine
{
	class ScreenManager : public SPComponent
	{
	protected:
		vector<BaseScreen*> screens;

	public:
		ScreenManager(void);
		~ScreenManager(void);

		bool Load();
		bool Unload();
		bool Update(float timeElapsed);
		bool Draw(float timeElapsed);
		bool Initialize();

		bool AddScreen(BaseScreen* screen);
		bool RemoveScreen(BaseScreen* screen);
	};
}


