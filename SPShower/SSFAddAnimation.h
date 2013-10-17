#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

using namespace KScript;
class SSFAddAnimation : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		SUIComponentPtr component;

		if (IsSet(L"component", args))
		{
			component = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"component"].value);

			args.erase(L"component");
		}
		else
		{
			component = SUIManager::GetSingleton().GetCurrentScreen()->GetCurrentComponent();
		}

		if (!component)
		{
			return true;
		}

		SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(component);

		SUIAnimationPtr animation = new SUIAnimation();

		animation->SetStartPoint(component->GetProperties());	

		if (IsSet(L"time", args))
		{
			float time = SPStringHelper::StringToFloat(args[L"time"].value);

			animation->SetTime(time);

			args.erase(L"time");
		}

		SUIProperties endPoint = component->GetProperties();

		if (IsSet(L"layer", args))
		{
			endPoint.layer = SPStringHelper::StringToFloat(args[L"layer"].value);

			args.erase(L"layer");
		}

		if (IsSet(L"width", args))
		{
			int width = SPStringHelper::StringToInt(args[L"width"].value);

			endPoint.rectangle.Width = width;

			args.erase(L"width");
		}

		if (IsSet(L"height", args))
		{
			int height = SPStringHelper::StringToInt(args[L"height"].value);

			endPoint.rectangle.Height = height;

			args.erase(L"height");
		}

		if (IsSet(L"x", args))
		{
			int x = SPStringHelper::StringToInt(args[L"x"].value);

			endPoint.rectangle.X = x;

			args.erase(L"x");
		}			

		if (IsSet(L"y", args))
		{
			int y = SPStringHelper::StringToInt(args[L"y"].value);

			endPoint.rectangle.Y = y;

			args.erase(L"y");
		}

		if (IsSet(L"rotation", args))
		{
			float rotation = SPStringHelper::StringToFloat(args[L"rotation"].value);

			endPoint.rotation = rotation;

			args.erase(L"rotation");
		}

		if (IsSet(L"rotation_center_x", args))
		{
			float x = SPStringHelper::StringToFloat(args[L"rotation_center_x"].value);

			endPoint.rotationCenter.x = x;

			args.erase(L"rotation_center_x");
		}

		if (IsSet(L"rotation_center_y", args))
		{
			float y = SPStringHelper::StringToFloat(args[L"rotation_center_y"].value);

			endPoint.rotationCenter.y = y;

			args.erase(L"rotation_center_y");
		}

		if (IsSet(L"background_image", args))
		{
			endPoint.backgroundImage = SPTextureManager::GetSingleton().
				GetTexture(args[L"background_image"].value);

			args.erase(L"background_image");
		}

		if (IsSet(L"background_color", args))
		{
			endPoint.backgroundColor = SPStringHelper::StringToInt(args[L"background_color"].value);

			args.erase(L"background_color");
		}

		if (IsSet(L"transparency", args))
		{
			endPoint.transparency = SPStringHelper::StringToFloat(args[L"transparency"].value);

			args.erase(L"transparency");
		}

		if (IsSet(L"background_x", args))
		{
			endPoint.backgroundX = SPStringHelper::StringToInt(args[L"background_x"].value);

			args.erase(L"background_x");
		}

		if (IsSet(L"background_y", args))
		{
			endPoint.backgroundY = SPStringHelper::StringToInt(args[L"background_y"].value);

			args.erase(L"background_y");
		}

		if (IsSet(L"background_fill_mode", args))
		{
			SPString fillMode = args[L"background_fill_mode"].value;

			if (fillMode == L"Positioning")
			{
				endPoint.backgroundMode = SUIProperties::Positioning;
			}

			if (fillMode == L"Fill")
			{
				endPoint.backgroundMode = SUIProperties::Fill;
			}

			if (fillMode == L"FitWidth")
			{
				endPoint.backgroundMode = SUIProperties::FitWidth;
			}

			if (fillMode == L"FitHeight")
			{
				endPoint.backgroundMode = SUIProperties::FitHeight;
			}

			if (fillMode == L"FitMin")
			{
				endPoint.backgroundMode = SUIProperties::FitMin;
			}

			if (fillMode == L"FitMax")
			{
				endPoint.backgroundMode = SUIProperties::FitMax;
			}

			args.erase(L"background_fill_mode");
		}

		if (IsSet(L"background_position_mode", args))
		{
			SPString positionMode = args[L"background_position_mode"].value;

			if (positionMode == L"Normal")
			{
				endPoint.backgroundPosition = SUIProperties::Normal;
			}

			if (positionMode == L"TopLeft")
			{
				endPoint.backgroundPosition = SUIProperties::TopLeft;
			}

			if (positionMode == L"TopRight")
			{
				endPoint.backgroundPosition = SUIProperties::TopRight;
			}

			if (positionMode == L"TopCenter")
			{
				endPoint.backgroundPosition = SUIProperties::TopCenter;
			}

			if (positionMode == L"BottomLeft")
			{
				endPoint.backgroundPosition = SUIProperties::BottomLeft;
			}

			if (positionMode == L"BottomRight")
			{
				endPoint.backgroundPosition = SUIProperties::BottomRight;
			}

			if (positionMode == L"BottomCenter")
			{
				endPoint.backgroundPosition = SUIProperties::BottomCenter;
			}

			if (positionMode == L"CenterLeft")
			{
				endPoint.backgroundPosition = SUIProperties::CenterLeft;
			}

			if (positionMode == L"CengerRight")
			{
				endPoint.backgroundPosition = SUIProperties::CengerRight;
			}

			if (positionMode == L"CenterAll")
			{
				endPoint.backgroundPosition = SUIProperties::CenterAll;
			}

			args.erase(L"background_position_mode");
		}

		if (IsSet(L"can_skip", args))
		{
			animation->SetCanSkip(SPStringHelper::StringToBool(args[L"can_skip"].value));

			args.erase(L"can_skip");
		}

		animation->SetEndPoint(endPoint);

		component->AddAnimation(animation);

		component->PlayAnimation();

		OutLogUnusedProperties(args);

		return true;
	}
};

