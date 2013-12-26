#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUITextBox.h"
#include "SUIEffectManager.h"

#pragma warning(disable:4305)
#pragma warning(disable:4244)

using namespace KScript;
using namespace SPEngine;

class SSFTextBox : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (!SUIManager::GetSingleton().GetCurrentScreen())
		{
			return false;
		}

		if (IsSet(L"name", args))
		{
			SUITextBoxPtr textBox;

			SPString name = args[L"name"].value;

			textBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (!textBox)
			{
				textBox = new SUITextBox();
				textBox->SetName(name);

				SUIManager::GetSingleton().GetCurrentScreen()->AddComponent(textBox);
			}

			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentTextBox(textBox);
			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(textBox);

			SetComponentProperties(textBox, args);

			if (IsSet(L"padding", args))
			{
				float padding = SPStringHelper::StringToFloat(args[L"padding"].value);

				textBox->SetPadding(SUIPadding(padding, padding, padding, padding));

				args.erase(L"padding");
			}

			if (IsSet(L"line_space", args))
			{
				float space = SPStringHelper::StringToFloat(args[L"line_space"].value);

				textBox->SetLineSpace(space);

				args.erase(L"line_space");
			}

			if (IsSet(L"word_space", args))
			{
				float space = SPStringHelper::StringToFloat(args[L"word_space"].value);

				textBox->SetWordSpace(space);

				args.erase(L"word_space");
			}

			if (IsSet(L"font", args))
			{
				SPFontPtr font = SPFontManager::GetSingleton().GetFont(args[L"font"].value);

				if (font)
				{
					textBox->SetDefaultFont(font);
				}

				args.erase(L"font");
			}

			if (IsSet(L"color", args))
			{
				D3DCOLOR color = SPStringHelper::StringToInt(args[L"color"].value);

				textBox->SetDefaultColor(color);

				args.erase(L"color");
			}

			if (IsSet(L"text_effect_back", args))
			{
				SUIEffectPtr effect = SUIEffectManager::GetSingleton().GetEffect(args[L"text_effect_back"].value);

				if (effect)
				{
					if (IsSet(L"text_effect_back_tex", args))
					{
						effect->SetEffectTexture(SPTextureManager::GetSingleton().GetTexture(args[L"text_effect_back_tex"].value));

						args.erase(L"text_effect_back_tex");
					}

					if (IsSet(L"text_effect_back_level", args))
					{
						effect->SetLevel(SPStringHelper::StringToFloat(args[L"text_effect_back_level"].value));

						args.erase(L"text_effect_back_level");
					}
					else
					{
						effect->SetLevel(5);
					}

					VariableMap::iterator iter = args.begin();

					while(iter != args.end())
					{
						KString argName = iter->first;
						if (argName.find(L"text_effect_back_") == 0)
						{
							argName = argName.replace(0, 17, L"");

							effect->SetFloat(SPStringHelper::ToString(argName), 
								SPStringHelper::StringToFloat(args[iter->first].value));

							iter = args.erase(iter);
						}
						else
						{
							iter++;
						}						
					}

					effect->SetTime(0);
					effect->Play();
					effect->Update(1.0/60);
				}

				textBox->SetDefaultBackEffect(effect);

				args.erase(L"text_effect_back");
			}

			if (IsSet(L"text_effect_front", args))
			{
				SUIEffectPtr effect = SUIEffectManager::GetSingleton().GetEffect(args[L"text_effect_front"].value);

				if (effect)
				{
					if (IsSet(L"text_effect_front_tex", args))
					{
						effect->SetEffectTexture(SPTextureManager::GetSingleton().GetTexture(args[L"text_effect_front_tex"].value));

						args.erase(L"text_effect_front_tex");
					}

					if (IsSet(L"text_effect_front_level", args))
					{
						effect->SetLevel(SPStringHelper::StringToFloat(args[L"text_effect_front_level"].value));

						args.erase(L"text_effect_front_level");
					}
					else
					{
						effect->SetLevel(5);
					}

					VariableMap::iterator iter = args.begin();

					while(iter != args.end())
					{
						KString argName = iter->first;
						if (argName.find(L"text_effect_front_") == 0)
						{
							argName = argName.replace(0, 18, L"");

							effect->SetFloat(SPStringHelper::ToString(argName), 
								SPStringHelper::StringToFloat(args[iter->first].value));

							iter = args.erase(iter);
						}
						else
						{
							iter++;
						}						
					}

					effect->SetTime(0);
					effect->Play();
					effect->Update(1.0/60);
				}

				textBox->SetDefaultFrontEffect(effect);

				args.erase(L"text_effect_front");
			}

			if (IsSet(L"content", args))
			{
				textBox->Clear();
				SUIText text;
				text.text = args[L"content"].value;
				text.color = textBox->GetDefaultColor();
				textBox->AddText(text);

				args.erase(L"content");
			}

			textBox->RefreshText();

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

