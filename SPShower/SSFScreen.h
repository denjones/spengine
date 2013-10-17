#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;

class SSFScreen : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"name", args))
		{
			SUIScreenPtr screen;

			wstring name = args[L"name"].value;

			if (SUIManager::GetSingleton().IsScreenValid(name))
			{
				screen = SUIManager::GetSingleton().GetScreen(name);
			}
			else
			{
				screen = new SUIScreen();
				screen->SetName(name);
				SUIManager::GetSingleton().AddScreen(screen);
			}

			if (IsSet(L"pop_up", args))
			{
				if (SPStringHelper::StringToInt(args[L"pop_up"].value) == 0)
				{
					screen->SetPopUp(false);
				}
				else
				{
					screen->SetPopUp(true);
				}

				args.erase(L"pop_up");
			}

			if (IsSet(L"background_color", args))
			{
				screen->SetBackgroundColor(SPStringHelper::StringToInt(args[L"background_color"].value));

				args.erase(L"background_color");
			}

			SUIManager::GetSingleton().FocusScreen(name);

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

