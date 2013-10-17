#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIDialogBox.h"
#include <KScriptRunner.h>
#include <KScript.h>

using namespace KScript;

class SSFNext : public ExtendedMapArgsFunction
{
public:
	Value Function(KScript::Script* currentScript, VariableMap args)
	{
		SUIDialogBoxPtr dialogBox;

		if (args.find(L"box") == args.end())
		{
			return Value();
		}

		SPString name = args[L"box"].value;
		dialogBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

		if (dialogBox)
		{
			dialogBox->Next();
		}

		return Value();
	}
};

