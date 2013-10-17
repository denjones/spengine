#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SScriptManager.h"

using namespace KScript;

class SSFGoTo : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		bool goToNewFile = false;

		if (IsSet(L"file", args))
		{
			SScriptManager::GetSingleton().ReplaceCommandsFromFile(args[L"file"].value);

			waiting = true;

			goToNewFile = true;

			args.erase(L"file");
		}

		if (IsSet(L"tag", args))
		{
			if (!goToNewFile)
			{
				SScriptManager::GetSingleton().ReloadCommands();
			}

			// Set up target command.
			VariableMap tagArgs;
			tagArgs[L"name"] = args[L"tag"];
			SScriptCommand target(L"tag", tagArgs, L"", 0);

			SScriptManager::GetSingleton().LocateCommands(target);

			waiting = true;

			args.erase(L"tag");
		}

		OutLogUnusedProperties(args);

		return false;
	}
};

