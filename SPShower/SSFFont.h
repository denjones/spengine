#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include <KScriptParser.h>

using namespace KScript;

class SSFFont : public SScriptFunction
{
public:
	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"name", args))
		{
			int		size = 20;
			int		weight = FW_NORMAL;
			bool	italic = false;
			SPString fontName = L"default";

			SPFontPtr font;

			SPString name = args[L"name"].value;

			if (IsSet(L"size", args))
			{
				size = SPStringHelper::StringToInt(args[L"size"].value);

				args.erase(L"size");
			}

			if (IsSet(L"font", args))
			{
				fontName = args[L"font"].value;

				args.erase(L"font");
			}

			if (IsSet(L"weight", args))
			{
				if (args[L"weight"].type == STRING)
				{
					KString weightType = args[L"weight"].value;

					if (weightType == L"DontCare")
					{
						weight = FW_DONTCARE;
					}

					if (weightType == L"Thin")
					{
						weight = FW_THIN;
					}

					if (weightType == L"ExtraLight"
						|| weightType == L"UltraLight")
					{
						weight = FW_EXTRALIGHT;
					}

					if (weightType == L"Light")
					{
						weight = FW_LIGHT;
					}

					if (weightType == L"Normal"
						|| weightType == L"Regular")
					{
						weight = FW_NORMAL;
					}

					if (weightType == L"Medium")
					{
						weight = FW_MEDIUM;
					}

					if (weightType == L"SemiBold"
						|| weightType == L"DemiBold")
					{
						weight = FW_SEMIBOLD;
					}

					if (weightType == L"Bold")
					{
						weight = FW_BOLD;
					}

					if (weightType == L"ExtraBold"
						|| weightType == L"UltraBold")
					{
						weight = FW_EXTRABOLD;
					}

					if (weightType == L"Heavy"
						|| weightType == L"Black")
					{
						weight = FW_HEAVY;
					}
				}
				else
				{
					weight = SPStringHelper::StringToInt(args[L"weight"].value);

					weight *= 100;
				}

				args.erase(L"weight");
			}

			if (IsSet(L"italic", args))
			{
				italic = SPStringHelper::StringToInt(args[L"italic"].value) != 0;

				args.erase(L"italic");
			}

			SPFontManager::GetSingleton().CreateFont(name, size, 0, weight, 10, italic, fontName);

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

