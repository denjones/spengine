#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;

class SSFTag : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		// Just a tag, nothing to do.
		return false;
	}
};

