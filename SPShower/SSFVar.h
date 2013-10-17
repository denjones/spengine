#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"

using namespace KScript;

class SSFVar : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		SScriptManager::GetSingleton().InitializeSystemVariables(args);

		return false;
	}
};

