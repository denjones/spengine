#include "StdAfx.h"
#include "SUIEventHandleScript.h"
#include "SScriptManager.h"

bool SUIEventHandleScript::SetStringScript( SPString setScript )
{
	stringScript = setScript;
	script = new KScript::KSScript();
	script->LoadStringScript(setScript, L"SUIEvent");
	return true;
}

bool SUIEventHandleScript::Function( SUIEventPtr e )
{
	if (stringScript.size() <= 1)
	{
		return false;
	}

	//SScriptManager::GetSingleton().SetInsertPosFront(0);
	SScriptManager::GetSingleton().ImmediateModeOn();
	SScriptManager::GetSingleton().ExecuteInnerScript(script);
	SScriptManager::GetSingleton().ImmediateModeOff();
	//SScriptManager::GetSingleton().SetInsertPosBack();

	return true;
}

SUIEventHandleScript::SUIEventHandleScript( SPString setScript )
{
	SetStringScript(setScript);
}

