#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIPictureBox.h"
#include "SUITransformationManager.h"

#pragma warning (disable:4244)

using namespace KScript;
class SSFSwitchScreen : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		SUITransformationPtr transformation;

		SPString targetName = L"";

		if (IsSet(L"target", args))
		{
			targetName = args[L"target"].value;

			args.erase(L"target");
		}

		if (IsSet(L"trans", args))
		{
			transformation = SUITransformationManager::GetSingleton().
				GetTransformation(args[L"trans"].value);

			args.erase(L"trans");
		}

		if (IsSet(L"trans_src", args))
		{
			transformation = SUITransformationManager::GetSingleton().
				CreateTransformation(args[L"trans_src"].value);

			args.erase(L"trans_src");
		}

		if (transformation)
		{
			if (IsSet(L"time", args))
			{
				transformation->SetTime(SPStringHelper::StringToFloat(args[L"time"].value));

				args.erase(L"time");
			}

			if (IsSet(L"can_skip", args))
			{
				transformation->SetCanSkip(SPStringHelper::StringToBool(args[L"can_skip"].value));

				args.erase(L"can_skip");
			}
		}

		SUIManager::GetSingleton().SwitchToScreen(targetName, transformation);

		refreshScreen = true;

		OutLogUnusedProperties(args);

		return true;
	}
};

