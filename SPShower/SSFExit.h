#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;

class SSFExit : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = true;

		SPGameManager::GetSingleton().Exit();

		return false;
	}
};

