#include "StdAfx.h"
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIEventHandleScript.h"

#pragma warning (disable:4244)

bool SScriptFunction::SetComponentProperties(SUIComponentPtr component, VariableMap  &args )
{
	if (!component)
	{
		return false;
	}

	component->SetProperties(args);

	component->Skip();

	if (IsSet(L"display",args))
	{
		SPString display = args[L"display"].value;

		if (display == L"hidden")
		{
			component->Hide();
		}
		else if (display == L"unhidden")
		{
			component->Unhide();
		}
		else
		{
			if(component->IsDisplay())
			{
				component->Hide();
			}
			else
			{
				component->Unhide();
			}
		}

		args.erase(L"display");
	}

	if (IsSet(L"absolute", args))
	{
		component->SetAbsoluteRender(SPStringHelper::StringToInt(args[L"absolute"].value) != 0);

		args.erase(L"absolute");
	}

	if (IsSet(L"layer", args))
	{
		component->SetLayer(SPStringHelper::StringToFloat(args[L"layer"].value));

		args.erase(L"layer");
	}

	if (IsSet(L"width", args))
	{
		int width = SPStringHelper::StringToInt(args[L"width"].value);
		component->SetWidth(width);

		args.erase(L"width");
	}

	if (IsSet(L"height", args))
	{
		int height = SPStringHelper::StringToInt(args[L"height"].value);
		component->SetHeight(height);

		args.erase(L"height");
	}

	if (IsSet(L"x", args))
	{
		int x = SPStringHelper::StringToInt(args[L"x"].value);
		component->SetPositionX(x);

		args.erase(L"x");
	}			

	if (IsSet(L"y", args))
	{
		int y = SPStringHelper::StringToInt(args[L"y"].value);
		component->SetPositionY(y);

		args.erase(L"y");
	}

	if (IsSet(L"rotation", args))
	{
		float rotation = SPStringHelper::StringToFloat(args[L"rotation"].value);
		component->SetRotation(rotation);

		args.erase(L"rotation");
	}

	if (IsSet(L"rotation_center_x", args))
	{
		float x = SPStringHelper::StringToFloat(args[L"rotation_center_x"].value);
		component->SetRotationCenterX(x);

		args.erase(L"rotation_center_x");
	}

	if (IsSet(L"rotation_center_y", args))
	{
		float y = SPStringHelper::StringToFloat(args[L"rotation_center_y"].value);
		component->SetRotationCenterY(y);

		args.erase(L"rotation_center_y");
	}

	if (IsSet(L"background_image", args))
	{
		Value arg = args[L"background_image"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->SetBackgroundImage(NULL);
		}
		else
		{
			component->SetBackgroundImage(SPTextureManager::GetSingleton().GetTexture(args[L"background_image"].value));
		}

		args.erase(L"background_image");
	}

	if (IsSet(L"background_color", args))
	{
		component->SetBackgroundColor(SPStringHelper::StringToInt(args[L"background_color"].value));

		args.erase(L"background_color");
	}

	if (IsSet(L"transparency", args))
	{
		component->SetTransparency(SPStringHelper::StringToFloat(args[L"transparency"].value));

		args.erase(L"transparency");
	}

	if (IsSet(L"background_x", args))
	{
		component->SetBackgroundX(SPStringHelper::StringToInt(args[L"background_x"].value));

		args.erase(L"background_x");
	}

	if (IsSet(L"background_y", args))
	{
		component->SetBackgroundY(SPStringHelper::StringToInt(args[L"background_y"].value));

		args.erase(L"background_y");
	}

	if (IsSet(L"background_fill_mode", args))
	{
		SPString fillMode = args[L"background_fill_mode"].value;

		if (fillMode == L"Positioning")
		{
			component->SetBackgroundMode(SUIProperties::Positioning);
		}

		if (fillMode == L"Fill")
		{
			component->SetBackgroundMode(SUIProperties::Fill);
		}

		if (fillMode == L"FitWidth")
		{
			component->SetBackgroundMode(SUIProperties::FitWidth);
		}

		if (fillMode == L"FitHeight")
		{
			component->SetBackgroundMode(SUIProperties::FitHeight);
		}

		if (fillMode == L"FitMin")
		{
			component->SetBackgroundMode(SUIProperties::FitMin);
		}

		if (fillMode == L"FitMax")
		{
			component->SetBackgroundMode(SUIProperties::FitMax);
		}

		args.erase(L"background_fill_mode");
	}

	if (IsSet(L"background_position_mode", args))
	{
		SPString positionMode = args[L"background_position_mode"].value;

		if (positionMode == L"Normal")
		{
			component->SetBackgroundPositionMode(SUIProperties::Normal);
		}

		if (positionMode == L"TopLeft")
		{
			component->SetBackgroundPositionMode(SUIProperties::TopLeft);
		}

		if (positionMode == L"TopRight")
		{
			component->SetBackgroundPositionMode(SUIProperties::TopRight);
		}

		if (positionMode == L"TopCenter")
		{
			component->SetBackgroundPositionMode(SUIProperties::TopCenter);
		}

		if (positionMode == L"BottomLeft")
		{
			component->SetBackgroundPositionMode(SUIProperties::BottomLeft);
		}

		if (positionMode == L"BottomRight")
		{
			component->SetBackgroundPositionMode(SUIProperties::BottomRight);
		}

		if (positionMode == L"BottomCenter")
		{
			component->SetBackgroundPositionMode(SUIProperties::BottomCenter);
		}

		if (positionMode == L"CenterLeft")
		{
			component->SetBackgroundPositionMode(SUIProperties::CenterLeft);
		}

		if (positionMode == L"CengerRight")
		{
			component->SetBackgroundPositionMode(SUIProperties::CengerRight);
		}

		if (positionMode == L"CenterAll")
		{
			component->SetBackgroundPositionMode(SUIProperties::CenterAll);
		}

		args.erase(L"background_position_mode");
	}

	if (IsSet(L"on_click", args))
	{
		Value arg = args[L"on_click"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseLeftClick = NULL;
		}
		else
		{
			component->onMouseLeftClick = new SUIEventHandleScript(args[L"on_click"].value);
		}
		
		args.erase(L"on_click");
	}

	if (IsSet(L"on_dclick", args))
	{
		Value arg = args[L"on_dclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseLeftDClick = NULL;
		}
		else
		{
			component->onMouseLeftDClick = new SUIEventHandleScript(args[L"on_dclick"].value);
		}

		args.erase(L"on_dclick");
	}

	if (IsSet(L"on_up", args))
	{
		Value arg = args[L"on_up"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseLeftUp = NULL;
		}
		else
		{
			component->onMouseLeftUp = new SUIEventHandleScript(args[L"on_up"].value);
		}

		args.erase(L"on_up");
	}

	if (IsSet(L"on_down", args))
	{
		Value arg = args[L"on_down"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseLeftDown = NULL;
		}
		else
		{
			component->onMouseLeftDown = new SUIEventHandleScript(args[L"on_down"].value);
		}

		args.erase(L"on_down");
	}

	if (IsSet(L"on_rclick", args))
	{
		Value arg = args[L"on_rclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseRightClick = NULL;
		}
		else
		{
			component->onMouseRightClick = new SUIEventHandleScript(args[L"on_rclick"].value);
		}

		args.erase(L"on_rclick");
	}

	if (IsSet(L"on_rdclick", args))
	{
		Value arg = args[L"on_rdclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseRightDClick = NULL;
		}
		else
		{
			component->onMouseRightDClick = new SUIEventHandleScript(args[L"on_rdclick"].value);
		}
			
		args.erase(L"on_rdclick");
	}

	if (IsSet(L"on_rup", args))
	{
		Value arg = args[L"on_rup"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseRightUp = NULL;
		}
		else
		{
			component->onMouseRightUp = new SUIEventHandleScript(args[L"on_rup"].value);
		}

		args.erase(L"on_rup");
	}

	if (IsSet(L"on_rdown", args))
	{
		Value arg = args[L"on_rdown"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseRightDown = NULL;
		}
		else
		{
			component->onMouseRightDown = new SUIEventHandleScript(args[L"on_rdown"].value);
		}

		args.erase(L"on_rdown");
	}

	if (IsSet(L"on_mclick", args))
	{
		Value arg = args[L"on_mclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseMiddleClick = NULL;
		}
		else
		{
			component->onMouseMiddleClick = new SUIEventHandleScript(args[L"on_mclick"].value);
		}

		args.erase(L"on_mclick");
	}

	if (IsSet(L"on_mdclick", args))
	{
		Value arg = args[L"on_mdclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseMiddleDClick = NULL;
		}
		else
		{
			component->onMouseMiddleDClick = new SUIEventHandleScript(args[L"on_mdclick"].value);
		}

		args.erase(L"on_mdclick");
	}

	if (IsSet(L"on_mup", args))
	{
		Value arg = args[L"on_mup"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseMiddleUp = NULL;
		}
		else
		{
			component->onMouseMiddleUp = new SUIEventHandleScript(args[L"on_mup"].value);
		}

		args.erase(L"on_mup");
	}

	if (IsSet(L"on_mdown", args))
	{
		Value arg = args[L"on_mdown"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseMiddleDown = NULL;
		}
		else
		{
			component->onMouseMiddleDown = new SUIEventHandleScript(args[L"on_mdown"].value);
		}

		args.erase(L"on_mdown");
	}

	if (IsSet(L"on_scroll_up", args))
	{
		Value arg = args[L"on_scroll_up"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseScrollUp = NULL;
		}
		else
		{
			component->onMouseScrollUp = new SUIEventHandleScript(args[L"on_scroll_up"].value);
		}

		args.erase(L"on_scroll_up");
	}

	if (IsSet(L"on_scroll_down", args))
	{
		Value arg = args[L"on_scroll_down"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseScrollDown = NULL;
		}
		else
		{
			component->onMouseScrollDown = new SUIEventHandleScript(args[L"on_scroll_down"].value);
		}

		args.erase(L"on_scroll_down");
	}

	if (IsSet(L"on_mouse", args))
	{
		Value arg = args[L"on_mouse"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouse = NULL;
		}
		else
		{
			component->onMouse = new SUIEventHandleScript(args[L"on_mouse"].value);
		}

		args.erase(L"on_mouse");
	}

	if (IsSet(L"on_mouse_in", args))
	{
		Value arg = args[L"on_mouse_in"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseIn = NULL;
		}
		else
		{
			component->onMouseIn = new SUIEventHandleScript(args[L"on_mouse_in"].value);
		}

		args.erase(L"on_mouse_in");
	}

	if (IsSet(L"on_mouse_out", args))
	{
		Value arg = args[L"on_mouse_out"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->onMouseOut = NULL;
		}
		else
		{
			component->onMouseOut = new SUIEventHandleScript(args[L"on_mouse_out"].value);
		}

		args.erase(L"on_mouse_out");
	}

	if (IsSet(L"catch_click", args))
	{
		Value arg = args[L"catch_click"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseLeftClick = NULL;
		}
		else
		{
			component->catchMouseLeftClick = new SUIEventHandleScript(args[L"catch_click"].value);
		}

		args.erase(L"catch_click");
	}

	if (IsSet(L"catch_dclick", args))
	{
		Value arg = args[L"catch_dclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseLeftDClick = NULL;
		}
		else
		{
			component->catchMouseLeftDClick = new SUIEventHandleScript(args[L"catch_dclick"].value);
		}

		args.erase(L"catch_dclick");
	}

	if (IsSet(L"catch_up", args))
	{
		Value arg = args[L"catch_up"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseLeftUp = NULL;
		}
		else
		{
			component->catchMouseLeftUp = new SUIEventHandleScript(args[L"catch_up"].value);
		}

		args.erase(L"catch_up");
	}

	if (IsSet(L"catch_down", args))
	{
		Value arg = args[L"catch_down"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseLeftDown = NULL;
		}
		else
		{
			component->catchMouseLeftDown = new SUIEventHandleScript(args[L"catch_down"].value);
		}

		args.erase(L"catch_down");
	}

	if (IsSet(L"catch_rclick", args))
	{
		Value arg = args[L"catch_rclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseRightClick = NULL;
		}
		else
		{
			component->catchMouseRightClick = new SUIEventHandleScript(args[L"catch_rclick"].value);
		}

		args.erase(L"catch_rclick");
	}

	if (IsSet(L"catch_rdclick", args))
	{
		Value arg = args[L"catch_rdclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseRightDClick = NULL;
		}
		else
		{
			component->catchMouseRightDClick = new SUIEventHandleScript(args[L"catch_rdclick"].value);
		}

		args.erase(L"catch_rdclick");
	}

	if (IsSet(L"catch_rup", args))
	{
		Value arg = args[L"catch_rup"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseRightUp = NULL;
		}
		else
		{
			component->catchMouseRightUp = new SUIEventHandleScript(args[L"catch_rup"].value);
		}

		args.erase(L"catch_rup");
	}

	if (IsSet(L"catch_rdown", args))
	{
		Value arg = args[L"catch_rdown"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseRightDown = NULL;
		}
		else
		{
			component->catchMouseRightDown = new SUIEventHandleScript(args[L"catch_rdown"].value);
		}

		args.erase(L"catch_rdown");
	}

	if (IsSet(L"catch_mclick", args))
	{
		Value arg = args[L"catch_mclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseMiddleClick = NULL;
		}
		else
		{
			component->catchMouseMiddleClick = new SUIEventHandleScript(args[L"catch_mclick"].value);
		}

		args.erase(L"catch_mclick");
	}

	if (IsSet(L"catch_mdclick", args))
	{
		Value arg = args[L"catch_mdclick"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseMiddleDClick = NULL;
		}
		else
		{
			component->catchMouseMiddleDClick = new SUIEventHandleScript(args[L"catch_mdclick"].value);
		}

		args.erase(L"catch_mdclick");
	}

	if (IsSet(L"catch_mup", args))
	{
		Value arg = args[L"catch_mup"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseMiddleUp = NULL;
		}
		else
		{
			component->catchMouseMiddleUp = new SUIEventHandleScript(args[L"catch_mup"].value);
		}

		args.erase(L"catch_mup");
	}

	if (IsSet(L"catch_mdown", args))
	{
		Value arg = args[L"catch_mdown"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseMiddleDown = NULL;
		}
		else
		{
			component->catchMouseMiddleDown = new SUIEventHandleScript(args[L"catch_mdown"].value);
		}

		args.erase(L"catch_mdown");
	}

	if (IsSet(L"catch_scroll_up", args))
	{
		Value arg = args[L"catch_scroll_up"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseScrollUp = NULL;
		}
		else
		{
			component->catchMouseScrollUp = new SUIEventHandleScript(args[L"catch_scroll_up"].value);
		}

		args.erase(L"catch_scroll_up");
	}

	if (IsSet(L"catch_scroll_down", args))
	{
		Value arg = args[L"catch_scroll_down"];

		if ( arg.type == 39 && arg.value == L"0")
		{
			component->catchMouseScrollDown = NULL;
		}
		else
		{
			component->catchMouseScrollDown = new SUIEventHandleScript(args[L"catch_scroll_down"].value);
		}

		args.erase(L"catch_scroll_down");
	}

	VariableMap::iterator iter = args.begin();
	while (iter != args.end())
	{
		if (iter->first.find(L"on_key_press_") != iter->first.npos)
		{
			Value arg = iter->second;
			SPString keyName = iter->first.substr(13);
			UINT key = SPInputManager::GetSingleton().GetKeyboard()->KeyNameToKey(keyName);

			if ( arg.type == 39 && arg.value == L"0")
			{
				component->onKeyPress[key] = NULL;
			}
			else
			{
				component->onKeyPress[key] = new SUIEventHandleScript(arg.value);
			}

			args.erase((iter++)->first);
		}
		else if (iter->first.find(L"on_key_down_") != iter->first.npos)
		{
			Value arg = iter->second;
			SPString keyName = iter->first.substr(12);
			UINT key = SPInputManager::GetSingleton().GetKeyboard()->KeyNameToKey(keyName);

			if ( arg.type == 39 && arg.value == L"0")
			{
				component->onKeyDown[key] = NULL;
			}
			else
			{
				component->onKeyDown[key] = new SUIEventHandleScript(arg.value);
			}

			args.erase((iter++)->first);
		}
		else if (iter->first.find(L"on_key_up_") != iter->first.npos)
		{
			Value arg = iter->second;
			SPString keyName = iter->first.substr(10);
			UINT key = SPInputManager::GetSingleton().GetKeyboard()->KeyNameToKey(keyName);

			if ( arg.type == 39 && arg.value == L"0")
			{
				component->onKeyUp[key] = NULL;
			}
			else
			{
				component->onKeyUp[key] = new SUIEventHandleScript(arg.value);
			}

			args.erase((iter++)->first);
		}
		else
		{
			iter++;
		}	
	}

	if (IsSet(L"father", args))
	{
		SUIComponentPtr father = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(args[L"father"].value);

		if (father)
		{
			if (component->GetFather())
			{
				component->GetFather()->RemoveChild(component);
			}

			component->SetFather(father);
			father->AddChild(component);
		}

		args.erase(L"father");
	}
	else
	{
		if (!component->GetFather() && component->GetName() != L"global_root")
		{
			SUIComponentPtr father = SUIManager::GetSingleton().GetCurrentScreen()->GetComponent(L"global_root");

			if (father)
			{
				component->SetFather(father);
				father->AddChild(component);
			}
		}		
	}

	return true;
}

bool SScriptFunction::OutLogUnusedProperties( VariableMap args )
{
	VariableMap::iterator iter = args.begin();

	while(iter != args.end())
	{
		SPLogHelper::WriteLog(L"[SPShower] WARNING: Invalid script function argument in function : " + name);
		SPLogHelper::WriteLog(L"[SPShower] WARNING: Invalid script function argument : " + iter->first);
		iter++;
	}

	return true;
}

bool SScriptFunction::IsWaiting()
{
	return waiting;
}

bool SScriptFunction::IsNeedToRefresh()
{
	return refreshScreen;
}
