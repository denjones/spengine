#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SPGameShow.h"

using namespace KScript;

class SSFLoadGameData : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = true;
		waiting = false;

		if (IsSet(L"file", args))
		{
			SPString fileName = args[L"file"].value;
			((SPPointer<SPGameShow>)SPGameManager::GetSingleton().GetGame())->LoadFromFile(fileName);

			args.erase(L"file");
		}

		OutLogUnusedProperties(args);

		return false;
	}
};

