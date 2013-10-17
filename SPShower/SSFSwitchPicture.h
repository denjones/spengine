#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIPictureBox.h"
#include "SUITransformationManager.h"

using namespace KScript;
class SSFSwitchPicture : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		SUIPictureBoxPtr pictureBox;

		if (IsSet(L"box", args))
		{
			pictureBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"box"].value);
			args.erase(L"box");
		}
		
		if (!pictureBox)
		{
			return true;
		}
		
		if (IsSet(L"target", args))
		{
			SUIPictureListPtr target = SUIPictureManager::GetSingleton().GetPicture(args[L"target"].value);

			if (target)
			{
				pictureBox->SetTransformationTarget(target);
			}
			
			args.erase(L"target");
		}

		if (IsSet(L"trans", args))
		{
			SUITransformationPtr transformation = 
				SUITransformationManager::GetSingleton().GetTransformation(args[L"trans"].value);

			if (transformation)
			{
				pictureBox->SetTransformation(transformation);

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

			args.erase(L"trans");
		}

		if (IsSet(L"trans_src", args))
		{
			SUITransformationPtr transformation = 
				SUITransformationManager::GetSingleton().CreateTransformation(args[L"trans_src"].value);

			if (transformation)
			{
				pictureBox->SetTransformation(transformation);

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

				args.erase(L"can_skip");
			}

			args.erase(L"trans_src");
		}

		

		pictureBox->Transform();

		refreshScreen = true;

		OutLogUnusedProperties(args);

		return true;
	}
};

