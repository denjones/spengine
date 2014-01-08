#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIPictureBox.h"
#include "SUITransformationManager.h"
#include "SUIEffectManager.h"

#pragma warning (disable:4244)

using namespace KScript;
class SSFEffect : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		SUIComponentPtr component;

		SUIEffectPtr effect;
		
		if (IsSet(L"component", args))
		{
			component = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"component"].value);

			args.erase(L"component");
		}
		else
		{
			component =  SUIManager::GetSingleton().GetCurrentScreen()->GetCurrentComponent();
		}

		if (!component)
		{
			return true;
		}

		if (IsSet(L"effect", args))
		{
			KSValue arg = args[L"effect"];

			if ( arg.type == 39 && arg.value == L"0")
			{
				effect = NULL;
			}
			else
			{
				effect = SUIEffectManager::GetSingleton().GetEffect(args[L"effect"].value);
			}

			args.erase(L"effect");
		}

		if (IsSet(L"effect_src", args))
		{
			KSValue arg = args[L"effect_src"];

			if ( arg.type == 39 && arg.value == L"0")
			{
				effect = NULL;
			}
			else
			{
				effect = SUIEffectManager::GetSingleton().CreateEffect(args[L"effect_src"].value);
			}

			args.erase(L"effect_src");
		}

		if (effect)
		{
			if (IsSet(L"time", args))
			{
				effect->SetTime(SPStringHelper::StringToFloat(args[L"time"].value));

				args.erase(L"time");
			}

			if (IsSet(L"can_skip", args))
			{
				effect->SetCanSkip(SPStringHelper::StringToBool(args[L"can_skip"].value));

				args.erase(L"can_skip");
			}

			if (IsSet(L"effect_tex", args))
			{
				effect->SetEffectTexture(SPTextureManager::GetSingleton().
					GetTexture(args[L"effect_tex"].value));

				args.erase(L"effect_tex");
			}

			if (IsSet(L"level", args))
			{
				effect->SetLevel(SPStringHelper::StringToFloat(args[L"level"].value));

				args.erase(L"level");
			}

			if (IsSet(L"replay", args))
			{
				SPString style = args[L"replay"].value;

				if (style == L"SlowIn" || style == L"FastOut")
				{
					effect->SetType(SUITransition::SlowIn);
				}
				else if (style == L"SlowOut" || style == L"FastIn")
				{
					effect->SetType(SUITransition::SlowOut);
				}
				else if (style == L"SlowInOut")
				{
					effect->SetType(SUITransition::SlowInOut);
				}
				else if (style == L"FastInOut")
				{
					effect->SetType(SUITransition::FastInOut);
				}
				else
				{
					effect->SetType(SUITransition::Normal);
				}

				args.erase(L"replay");
			}
		}

		if (IsSet(L"add_mode", args))
		{
			SPString style = args[L"add_mode"].value;

			if (style == L"Skip")
			{
				component->ClearEffect();
				component->AddEffect(effect);
			}
			else
			{
				component->AddEffect(effect);
			}

			args.erase(L"add_mode");
		}
		else
		{
			// style == L"Normal"
			component->AddEffect(effect);
		}

		component->PlayEffect();

		refreshScreen = true;

		OutLogUnusedProperties(args);

		return true;
	}
};

