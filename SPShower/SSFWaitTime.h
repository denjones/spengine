#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;

class SSFWaitTime : public SScriptFunction
{
	float totalTimeS;

public:
	virtual ~SSFWaitTime(){}

	bool Function(VariableMap args, bool isRead)
	{
		float waitTimeS = 0;

		//
		// If skip mode on and not auto mode, just skip waiting.
		// 

		if (SScriptManager::GetSingleton().IsSkipModeOn()
			&& (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipAll
			|| (SScriptManager::GetSingleton().GetSkipMode() == SScriptManager::SkipRead && isRead )))
		{
			refreshScreen = true;
			waiting = false;
			return true;
		}

		if (IsSet(L"time", args))
		{
			waitTimeS = SPStringHelper::StringToFloat(args[L"time"].value);

			args.erase(L"time");
		}

		if (!waiting)
		{
			waiting = true;
			totalTimeS = 0;
		}

		totalTimeS += SPGameManager::GetSingleton().GetGame()->GetLastTimeS();

		refreshScreen = true;

		if (totalTimeS > waitTimeS)
		{
			totalTimeS = 0;
			waiting = false;
			return true;
		}

		waiting = true;
		return false;
	}
};

