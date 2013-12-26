#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIDialogBox.h"
#include "SUIEffectManager.h"

#pragma warning(disable:4305)
#pragma warning(disable:4244)

using namespace KScript;
using namespace SPEngine;

class SSFDialogBox : public SScriptFunction
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
			SUIDialogBoxPtr dialogBox;

			SPString name = args[L"name"].value;

			dialogBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (!dialogBox)
			{
				dialogBox = new SUIDialogBox();
				dialogBox->SetName(name);

				SUIManager::GetSingleton().GetCurrentScreen()->AddComponent(dialogBox);
			}

			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentTextBox(dialogBox);
			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(dialogBox);

			SetComponentProperties(dialogBox, args);

			if (IsSet(L"padding", args))
			{
				float padding = SPStringHelper::StringToFloat(args[L"padding"].value);

				dialogBox->SetPadding(SUIPadding(padding, padding, padding, padding));

				args.erase(L"padding");
			}

			if (IsSet(L"line_space", args))
			{
				float space = SPStringHelper::StringToFloat(args[L"line_space"].value);

				dialogBox->SetLineSpace(space);

				args.erase(L"line_space");
			}

			if (IsSet(L"word_space", args))
			{
				float space = SPStringHelper::StringToFloat(args[L"word_space"].value);

				dialogBox->SetWordSpace(space);

				args.erase(L"word_space");
			}

			if (IsSet(L"font", args))
			{
				SPFontPtr font = SPFontManager::GetSingleton().GetFont(args[L"font"].value);

				if (font)
				{
					dialogBox->SetDefaultFont(font);
				}

				args.erase(L"font");
			}

			if (IsSet(L"color", args))
			{
				D3DCOLOR color = SPStringHelper::StringToInt(args[L"color"].value);

				dialogBox->SetDefaultColor(color);

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

				dialogBox->SetDefaultBackEffect(effect);

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

				dialogBox->SetDefaultFrontEffect(effect);

				args.erase(L"text_effect_front");
			}

			if (IsSet(L"speed", args))
			{
				float speed = SPStringHelper::StringToFloat(args[L"speed"].value);

				dialogBox->SetSpeed(speed);

				args.erase(L"speed");
			}

			if (IsSet(L"next_line_src", args))
			{
				bool isAnime = false;

				int row = 1;
				int col = 1;
				int fps = 14;

				if (IsSet(L"next_line_row", args))
				{
					isAnime = true;

					row = SPStringHelper::StringToInt(args[L"next_line_row"].value);

					args.erase(L"next_line_row");
				}

				if (IsSet(L"next_line_col", args))
				{
					isAnime = true;

					col = SPStringHelper::StringToInt(args[L"next_line_col"].value);

					args.erase(L"next_line_col");
				}

				if (IsSet(L"next_line_fps", args))
				{
					isAnime = true;

					fps = SPStringHelper::StringToInt(args[L"next_line_fps"].value);

					args.erase(L"next_line_fps");
				}

				SPTexturePtr nextLineTex;

				if (isAnime)
				{
					nextLineTex = SPTextureManager::GetSingleton().GetAnime(args[L"next_line_src"].value, row, col, fps);
				}
				else
				{
					nextLineTex = SPTextureManager::GetSingleton().GetTexture(args[L"next_line_src"].value);
				}

				dialogBox->SetNextLineTex(nextLineTex);

				args.erase(L"next_line_src");
			}

			if (IsSet(L"next_page_src", args))
			{
				bool isAnime = false;

				int row = 1;
				int col = 1;
				int fps = 14;

				if (IsSet(L"next_page_row", args))
				{
					isAnime = true;

					row = SPStringHelper::StringToInt(args[L"next_page_row"].value);

					args.erase(L"next_page_row");
				}

				if (IsSet(L"next_page_col", args))
				{
					isAnime = true;

					col = SPStringHelper::StringToInt(args[L"next_page_col"].value);

					args.erase(L"next_page_col");
				}

				if (IsSet(L"next_page_fps", args))
				{
					isAnime = true;

					fps = SPStringHelper::StringToInt(args[L"next_page_fps"].value);

					args.erase(L"next_page_fps");
				}

				SPTexturePtr nextPageTex;

				if (isAnime)
				{
					nextPageTex = SPTextureManager::GetSingleton().GetAnime(args[L"next_page_src"].value, row, col, fps);
				}
				else
				{
					nextPageTex = SPTextureManager::GetSingleton().GetTexture(args[L"next_page_src"].value);
				}

				dialogBox->SetNextPageTex(nextPageTex);

				args.erase(L"next_page_src");
			}

			if (IsSet(L"content", args))
			{
				dialogBox->ForceClear();
				SUIText text;
				text.text = args[L"content"].value;
				text.color = dialogBox->GetDefaultColor();
				dialogBox->ForceAddText(text);

				args.erase(L"content");
			}

			dialogBox->RefreshText();

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

