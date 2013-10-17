#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIPictureList.h"
#include "SUIPictureManager.h"
#include "SUIPictureBox.h"

using namespace KScript;
using namespace SPEngine;

class SSFPictureBox : public SScriptFunction
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
			SUIPictureBoxPtr pictureBox;

			SPString name = args[L"name"].value;

			pictureBox = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(name);

			if (!pictureBox)
			{
				pictureBox = new SUIPictureBox();
				pictureBox->SetName(name);
				
				SUIManager::GetSingleton().GetCurrentScreen()->AddComponent(pictureBox);
			}

			SetComponentProperties(pictureBox, args);

			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentPictureBox(pictureBox);
			SUIManager::GetSingleton().GetCurrentScreen()->SetCurrentComponent(pictureBox);

			if (IsSet(L"picture", args))
			{
				pictureBox->SetPicture(SUIPictureManager::GetSingleton().GetPicture(args[L"picture"].value));

				args.erase(L"picture");
			}

			if (IsSet(L"fill_mode", args))
			{
				SPString fillMode = args[L"fill_mode"].value;
				
				if (fillMode == L"Positioning")
				{
					pictureBox->SetFillMode(SUIPictureBox::Positioning);
				}

				if (fillMode == L"Fill")
				{
					pictureBox->SetFillMode(SUIPictureBox::Fill);
				}

				if (fillMode == L"FitWidth")
				{
					pictureBox->SetFillMode(SUIPictureBox::FitWidth);
				}

				if (fillMode == L"FitHeight")
				{
					pictureBox->SetFillMode(SUIPictureBox::FitHeight);
				}

				if (fillMode == L"FitMin")
				{
					pictureBox->SetFillMode(SUIPictureBox::FitMin);
				}

				if (fillMode == L"FitMax")
				{
					pictureBox->SetFillMode(SUIPictureBox::FitMax);
				}

				if (fillMode == L"ResizeBox")
				{
					pictureBox->SetFillMode(SUIPictureBox::ResizeBox);
				}

				args.erase(L"fill_mode");
			}

			if (IsSet(L"position_mode", args))
			{
				SPString positionMode = args[L"position_mode"].value;

				if (positionMode == L"Normal")
				{
					pictureBox->SetPositionMode(SUIPictureBox::Normal);
				}

				if (positionMode == L"TopLeft")
				{
					pictureBox->SetPositionMode(SUIPictureBox::TopLeft);
				}

				if (positionMode == L"TopRight")
				{
					pictureBox->SetPositionMode(SUIPictureBox::TopRight);
				}

				if (positionMode == L"TopCenter")
				{
					pictureBox->SetPositionMode(SUIPictureBox::TopCenter);
				}

				if (positionMode == L"BottomLeft")
				{
					pictureBox->SetPositionMode(SUIPictureBox::BottomLeft);
				}

				if (positionMode == L"BottomRight")
				{
					pictureBox->SetPositionMode(SUIPictureBox::BottomRight);
				}

				if (positionMode == L"BottomCenter")
				{
					pictureBox->SetPositionMode(SUIPictureBox::BottomCenter);
				}

				if (positionMode == L"CenterLeft")
				{
					pictureBox->SetPositionMode(SUIPictureBox::CenterLeft);
				}

				if (positionMode == L"CengerRight")
				{
					pictureBox->SetPositionMode(SUIPictureBox::CengerRight);
				}

				if (positionMode == L"CenterAll")
				{
					pictureBox->SetPositionMode(SUIPictureBox::CenterAll);
				}

				args.erase(L"position_mode");
			}

			if (IsSet(L"position_x", args))
			{
				pictureBox->SetImagePositionX(SPStringHelper::StringToInt(args[L"position_x"].value));

				args.erase(L"position_x");
			}

			if (IsSet(L"position_y", args))
			{
				pictureBox->SetImagePositionY(SPStringHelper::StringToInt(args[L"position_y"].value));

				args.erase(L"position_y");
			}

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

