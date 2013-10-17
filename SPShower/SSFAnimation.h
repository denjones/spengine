#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"

#pragma warning (disable:4244)

using namespace KScript;
class SSFAnimation : public SScriptFunction
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

		animation->SetStartPoint(component->GetTargetProperties());	

		if (IsSet(L"time", args))
		{
			float time = SPStringHelper::StringToFloat(args[L"time"].value);

			animation->SetTime(time);

			args.erase(L"time");
		}

		SUIProperties endPoint = component->GetTargetProperties();

		component->SetProperties(args);

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

		if (IsSet(L"x_delta", args))
		{
			int x = SPStringHelper::StringToInt(args[L"x_delta"].value);

			endPoint.rectangle.X += x;

			args.erase(L"x_delta");
		}	

		if (IsSet(L"y", args))
		{
			int y = SPStringHelper::StringToInt(args[L"y"].value);

			endPoint.rectangle.Y = y;

			args.erase(L"y");
		}

		if (IsSet(L"y_delta", args))
		{
			int y = SPStringHelper::StringToInt(args[L"y_delta"].value);

			endPoint.rectangle.Y += y;

			args.erase(L"y_delta");
		}

		if (IsSet(L"rotation", args))
		{
			float rotation = SPStringHelper::StringToFloat(args[L"rotation"].value);

			endPoint.rotation = rotation;

			args.erase(L"rotation");
		}

		if (IsSet(L"rotation_delta", args))
		{
			float rotation = SPStringHelper::StringToFloat(args[L"rotation_delta"].value);

			endPoint.rotation += rotation;

			args.erase(L"rotation_delta");
		}

		if (IsSet(L"rotation_center_x", args))
		{
			float x = SPStringHelper::StringToFloat(args[L"rotation_center_x"].value);

			endPoint.rotationCenter.x = x;

			args.erase(L"rotation_center_x");
		}

		if (IsSet(L"rotation_center_x_delta", args))
		{
			float x = SPStringHelper::StringToFloat(args[L"rotation_center_x_delta"].value);

			endPoint.rotationCenter.x += x;

			args.erase(L"rotation_center_x_delta");
		}

		if (IsSet(L"rotation_center_y", args))
		{
			float y = SPStringHelper::StringToFloat(args[L"rotation_center_y"].value);

			endPoint.rotationCenter.y = y;

			args.erase(L"rotation_center_y");
		}

		if (IsSet(L"rotation_center_y_delta", args))
		{
			float y = SPStringHelper::StringToFloat(args[L"rotation_center_y_delta"].value);

			endPoint.rotationCenter.y += y;

			args.erase(L"rotation_center_y_delta");
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

		if (IsSet(L"background_x", args))
		{
			endPoint.backgroundX = SPStringHelper::StringToInt(args[L"background_x"].value);

			args.erase(L"background_x");
		}

		if (IsSet(L"background_x_delta", args))
		{
			endPoint.backgroundX += SPStringHelper::StringToInt(args[L"background_x_delta"].value);

			args.erase(L"background_x_delta");
		}

		if (IsSet(L"background_y", args))
		{
			endPoint.backgroundY = SPStringHelper::StringToInt(args[L"background_y"].value);

			args.erase(L"background_y");
		}

		if (IsSet(L"background_y_delta", args))
		{
			endPoint.backgroundY += SPStringHelper::StringToInt(args[L"background_y_delta"].value);

			args.erase(L"background_y_delta");
		}

		if (IsSet(L"transparency", args))
		{
			endPoint.transparency = SPStringHelper::StringToFloat(args[L"transparency"].value);

			args.erase(L"transparency");
		}

		if (IsSet(L"transparency_delta", args))
		{
			endPoint.transparency += SPStringHelper::StringToFloat(args[L"transparency_delta"].value);

			args.erase(L"transparency_delta");
		}

		if (IsSet(L"can_skip", args))
		{
			animation->SetCanSkip(SPStringHelper::StringToBool(args[L"can_skip"].value));

			args.erase(L"can_skip");
		}

		if (IsSet(L"replay", args))
		{
			SPString style = args[L"replay"].value;

			if (style == L"SlowIn" || style == L"FastOut")
			{
				animation->SetType(SUITransition::SlowIn);
			}
			else if (style == L"SlowOut" || style == L"FastIn")
			{
				animation->SetType(SUITransition::SlowOut);
			}
			else if (style == L"SlowInOut")
			{
				animation->SetType(SUITransition::SlowInOut);
			}
			else if (style == L"FastInOut")
			{
				animation->SetType(SUITransition::FastInOut);
			}
			else
			{
				animation->SetType(SUITransition::Normal);
			}

			args.erase(L"replay");
		}

		animation->SetEndPoint(endPoint);

		if (IsSet(L"add_mode", args))
		{
			SPString style = args[L"add_mode"].value;

			if (style == L"Merge")
			{
				component->MergerAnimation(animation);
			}
			else if (style == L"Skip")
			{
				component->Skip();
				component->AddAnimation(animation);
			}
			else
			{
				component->AddAnimation(animation);
			}

			args.erase(L"add_mode");
		}
		else
		{
			// style == L"Normal"
			component->AddAnimation(animation);
		}

		component->PlayAnimation();

		OutLogUnusedProperties(args);

		return true;
	}
};

