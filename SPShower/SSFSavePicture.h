#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SPGameShow.h"
#include "SUIPictureManager.h"

using namespace KScript;

class SSFSavePicture : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		refreshScreen = false;
		waiting = false;

		if (IsSet(L"component", args))
		{
			SUIComponentPtr component = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"component"].value);

			if (!component)
			{
				return true;
			}

			if (IsSet(L"file", args))
			{
				SPString fileName = args[L"file"].value;

				component->SaveAsImage(fileName);

				args.erase(L"file");
			}

			if (IsSet(L"picture", args))
			{
				SUIPictureListPtr picture = SUIPictureManager::GetSingleton().GetPicture(args[L"picture"].value);

				if (!picture)
				{
					return true;
				}

				picture->SetBaseImage(component->SaveAsTexture());

				args.erase(L"picture");
			}

			args.erase(L"component");
		}

		OutLogUnusedProperties(args);

		return false;
	}
};

