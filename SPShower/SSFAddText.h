#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIEffectManager.h"

#pragma warning (disable:4244)
#pragma warning(disable:4305)

using namespace KScript;
class SSFAddText : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		SUITextBoxPtr textBox;

		if (IsSet(L"box", args))
		{
			textBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"box"].value);

			args.erase(L"box");
		}
		else
		{
			textBox = SUIManager::GetSingleton().GetCurrentScreen()->GetCurrentTextBox();
		}

		if (!textBox)
		{
			return true;
		}

		SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentTextBox(textBox);

		SUIText text;

		if (IsSet(L"font", args))
		{
			text.font = SPFontManager::GetSingleton().GetFont(args[L"font"].value);

			args.erase(L"font");
		}

		if (IsSet(L"color", args))
		{
			text.color = SPStringHelper::StringToInt(args[L"color"].value);

			args.erase(L"color");
		}
		else
		{
			text.color = textBox->GetDefaultColor();
		}

		if (IsSet(L"effect_front", args))
		{
			text.frontEffect = SUIEffectManager::GetSingleton().GetEffect(args[L"effect_front"].value);

			if (text.frontEffect)
			{
				if (IsSet(L"effect_front_tex", args))
				{
					text.frontEffect->SetEffectTexture(SPTextureManager::GetSingleton().GetTexture(args[L"effect_front_tex"].value));

					args.erase(L"effect_front_tex");
				}

				if (IsSet(L"effect_front_level", args))
				{
					text.frontEffect->SetLevel(SPStringHelper::StringToFloat(args[L"effect_front_level"].value));

					args.erase(L"effect_front_level");
				}
				else
				{
					text.frontEffect->SetLevel(5);
				}

				VariableMap::iterator iter = args.begin();

				while(iter != args.end())
				{
					KString argName = iter->first;
					if (argName.find(L"effect_front_") == 0)
					{
						argName = argName.replace(0, 13, L"");

						text.frontEffect->SetFloat(SPStringHelper::ToString(argName), 
							SPStringHelper::StringToFloat(args[iter->first].value));

						iter = args.erase(iter);
					}
					else
					{
						iter++;
					}
				}

				text.frontEffect->SetTime(0);
				text.frontEffect->Play();
				text.frontEffect->Update(1.0/60);
			}

			args.erase(L"effect_front");
		}	

		if (IsSet(L"effect_back", args))
		{
			text.backEffect = SUIEffectManager::GetSingleton().GetEffect(args[L"effect_back"].value);

			if (text.backEffect)
			{
				if (IsSet(L"effect_back_tex", args))
				{
					text.backEffect->SetEffectTexture(SPTextureManager::GetSingleton().GetTexture(args[L"effect_back_tex"].value));

					args.erase(L"effect_back_tex");
				}

				if (IsSet(L"effect_back_level", args))
				{
					text.backEffect->SetLevel(SPStringHelper::StringToFloat(args[L"effect_back_level"].value));

					args.erase(L"effect_back_level");
				}
				else
				{
					text.backEffect->SetLevel(5);
				}

				VariableMap::iterator iter = args.begin();

				while(iter != args.end())
				{
					KString argName = iter->first;
					if (argName.find(L"effect_back_") == 0)
					{
						argName = argName.replace(0, 12, L"");

						text.backEffect->SetFloat(SPStringHelper::ToString(argName), 
							SPStringHelper::StringToFloat(args[iter->first].value));

						iter = args.erase(iter);
					}
					else
					{
						iter++;
					}
				}

				text.backEffect->SetTime(0);
				text.backEffect->Play();
				text.backEffect->Update(1.0/60);
			}

			args.erase(L"effect_back");
		}			

		if (IsSet(L"content", args))
		{
			text.text = args[L"content"].value;

			args.erase(L"content");
		}

		textBox->AddText(text);		

		textBox->ApplyText();

		OutLogUnusedProperties(args);

		return true;
	}
};

