#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;

class SSFDisplay : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		bool changed = false;

		SPConfig newConfig = SPConfigManager::GetSingleton().GetCurrentConfig();

		if(IsSet(L"fullscreen", args))
		{
			newConfig.windowed = SPStringHelper::StringToInt(args[L"fullscreen"].value) <= 0;
			args.erase(L"fullscreen");

			changed = true;
		}

		if (IsSet(L"resolution_width", args))
		{
			newConfig.windowWidth = SPStringHelper::StringToInt(args[L"resolution_width"].value);
			args.erase(L"resolution_width");

			changed = true;
		}

		if (IsSet(L"resolution_height", args))
		{
			newConfig.windowHeight = SPStringHelper::StringToInt(args[L"resolution_height"].value);
			args.erase(L"resolution_height");

			changed = true;
		}

		if (changed)
		{
			SPGameManager::GetSingleton().ApplyConfig(newConfig);
		}		

		return false;
	}
};

