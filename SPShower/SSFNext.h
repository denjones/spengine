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
	KSValue Function(KScript::KSScript* currentScript, VariableMap args)
	{
		SUIDialogBoxPtr dialogBox;

		if (args.find(L"box") == args.end())
		{
			return KSValue();
		}

		SPString name = args[L"box"].value;
		dialogBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

		if (dialogBox)
		{
			dialogBox->Next();
		}

		return KSValue();
	}
};

