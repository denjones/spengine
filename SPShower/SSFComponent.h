#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"

using namespace KScript;
class SSFComponent : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (!SUIManager::GetSingleton().GetCurrentScreen())
		{
			return true;
		}

		if (IsSet(L"name", args))
		{
			SUIComponentPtr component;

			SPString name = args[L"name"].value;			

			component = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (!component)
			{
				component = new SUIComponent(SUIManager::GetSingleton().GetCurrentScreen().get());
				component->SetName(name);

				SUIManager::GetSingleton().GetCurrentScreen()->AddComponent(component);
			}

			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(component);

			SetComponentProperties(component, args);

			args.erase(L"name");
		}

		return true;
	}
};

