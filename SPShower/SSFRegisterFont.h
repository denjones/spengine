#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include <KScriptParser.h>

using namespace KScript;

class SSFRegisterFont : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"src", args))
		{
			SPFontManager::GetSingleton().AddExtendedFont(args[L"src"].value);
			args.erase(L"src");
		}

		if (IsSet(L"file", args))
		{
			SPFontManager::GetSingleton().AddExtendedFont(args[L"file"].value);
			args.erase(L"file");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

