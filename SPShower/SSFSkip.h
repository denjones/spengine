#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"

using namespace KScript;

class SSFSkip : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		if (IsSet(L"mode", args))
		{			
			SScriptManager::SkipMode mode;
			SPString modeString = args[L"mode"].value;

			if(modeString == L"Auto")
			{
				mode = SScriptManager::SkipAuto;
			}
			else if (modeString == L"All")
			{
				mode = SScriptManager::SkipAll;
			}
			else if (modeString == L"Read")
			{
				mode = SScriptManager::SkipRead;
			}

			SScriptManager::GetSingleton().SetSkipMode(mode);

			args.erase(L"mode");
		}

		if (IsSet(L"auto_time", args))
		{
			float timeS = SPStringHelper::StringToFloat(args[L"auto_time"].value);

			if (timeS >= 0)
			{
				SScriptManager::GetSingleton().SetAutoWaitTimeS(timeS);
			}

			args.erase(L"auto_time");
		}

		if (IsSet(L"set_on", args))
		{
			SScriptManager::SkipMode mode;
			//SPString setOnString = args[L"set_on"].value;
			bool on = SPStringHelper::StringToInt(args[L"set_on"].value) > 0;

			if(on)
			{
				SScriptManager::GetSingleton().SkipModeOn();
			}
			else
			{
				SScriptManager::GetSingleton().SkipModeOff();
			}

			args.erase(L"set_on");
		}

		return false;
	}
};

