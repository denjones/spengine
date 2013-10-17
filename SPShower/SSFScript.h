#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"

using namespace KScript;

class SSFScript : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		if (IsSet(L"content", args))
		{
			//SScriptManager::GetSingleton().SetInsertPosFront(1);
			SScriptManager::GetSingleton().ImmediateModeOn();
			SScriptManager::GetSingleton().ExecuteInnerScript(args[L"content"].value);
			SScriptManager::GetSingleton().ImmediateModeOff();
			//SScriptManager::GetSingleton().SetInsertPosBack();
			args.erase(L"content");
		}	

		return false;
	}
};

