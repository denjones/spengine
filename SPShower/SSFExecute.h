#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"
#include <windows.h>

using namespace KScript;

class SSFExecute : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"file", args))
		{
			ShellExecute(NULL, L"open", args[L"file"].value.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}

		return false;
	}
};

