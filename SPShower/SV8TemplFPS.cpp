#include "StdAfx.h"
#include "SV8TemplFPS.h"
#include <FPSDisplayer.h>


Handle<ObjectTemplate> SV8TemplFPS::GetTemplate()
{
	Handle<ObjectTemplate> templFPS = ObjectTemplate::New();

	templFPS->SetAccessor(SPV8ScriptEngine::SPStringToString(L"display"), DisplayGetter, DisplaySetter);
	templFPS->SetAccessor(SPV8ScriptEngine::SPStringToString(L"position"), PositionGetter, PositionSetter);
	templFPS->SetAccessor(SPV8ScriptEngine::SPStringToString(L"lock"), LockGetter, LockSetter);

	return templFPS;
}

void SV8TemplFPS::DisplayGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	FPSDisplayerPtr displayer = SPComponentManager::GetSingleton()->GetComponent(L"fps");

	info.GetReturnValue().Set(displayer->IsEnabled());
}

void SV8TemplFPS::DisplaySetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	FPSDisplayerPtr displayer = SPComponentManager::GetSingleton()->GetComponent(L"fps");

	if (value->BooleanValue())
	{
		displayer->Enable();
	}
	else
	{
		displayer->Disable();
	}
}

void SV8TemplFPS::PositionGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	FPSDisplayerPtr displayer = SPComponentManager::GetSingleton()->GetComponent(L"fps");

	SPString position;
	FPSLocation location = displayer->GetLocation();

	if (location == LeftTop)
	{
		position = L"LeftTop";
	} 
	else if(location == RightTop)
	{
		position = L"RightTop";
	}
	else if(location == LeftBottom)
	{
		position = L"LeftBottom";
	}
	else if(location == RightBottom)
	{
		position = L"RightBottom";
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(position));
}

void SV8TemplFPS::PositionSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	FPSDisplayerPtr displayer = SPComponentManager::GetSingleton()->GetComponent(L"fps");

	SPString position = SPV8ScriptEngine::StringToSPString(value->ToString());

	if (SPStringHelper::EqualsIgnoreCase(position, L"LeftTop") ||
		SPStringHelper::EqualsIgnoreCase(position, L"TopLeft"))
	{
		displayer->SetLocation(LeftTop);
	}
	else if (SPStringHelper::EqualsIgnoreCase(position, L"RightTop") ||
		SPStringHelper::EqualsIgnoreCase(position, L"TopRight"))
	{
		displayer->SetLocation(RightTop);
	}
	else if (SPStringHelper::EqualsIgnoreCase(position, L"LeftBottom") ||
		SPStringHelper::EqualsIgnoreCase(position, L"BottomLeft"))
	{
		displayer->SetLocation(LeftBottom);
	}
	else if (SPStringHelper::EqualsIgnoreCase(position, L"RightBottom") ||
		SPStringHelper::EqualsIgnoreCase(position, L"BottomRight"))
	{
		displayer->SetLocation(RightBottom);
	}
}

void SV8TemplFPS::LockGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	if(SPGameManager::GetSingleton()->GetGame()->IsLockFPS())
	{
		info.GetReturnValue().Set(SPGameManager::GetSingleton()->GetGame()->GetLockedFPS());
	}
	else
	{
		info.GetReturnValue().Set(0);
	}
}

void SV8TemplFPS::LockSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	int fps = value->Int32Value();

	if (fps <= 0)
	{
		SPGameManager::GetSingleton()->GetGame()->UnlockFPS();
	}
	else if (fps > 0)
	{
		SPGameManager::GetSingleton()->GetGame()->LockFPSAt(fps);
	}
}
