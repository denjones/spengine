#include "StdAfx.h"
#include "SV8TemplWindow.h"
#include "SV8ScriptManager.h"



Handle<ObjectTemplate> SV8TemplWindow::GetTemplate()
{
	Handle<ObjectTemplate> templWindow = ObjectTemplate::New();

	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"title"), TitleGetter, TitleSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"width"), WidthGetter, WidthSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"height"), HeightGetter, HeightSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"fullScreen"), FullScreenGetter, FullScreenSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"cursor"), CursorGetter, CursorSetter);

	// Methods

	templWindow->Set(SPV8ScriptEngine::SPStringToString(L"resize"), 
		FunctionTemplate::New(Resize)->GetFunction());

	templWindow->Set(SPV8ScriptEngine::SPStringToString(L"fps"), 
		SV8ScriptManager::GetSingleton()->GetFPSTemplate()->NewInstance());

	return templWindow;
}

void SV8TemplWindow::WindowGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	
}

void SV8TemplWindow::WindowSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8TemplWindow::TitleGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(SPWindow::GetSingleton()->GetTitle()));
}

void SV8TemplWindow::TitleSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	SPWindow::GetSingleton()->SetTitle(SPV8ScriptEngine::StringToSPString(value->ToString()));
}

void SV8TemplWindow::WidthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton()->GetWidth()));
}

void SV8TemplWindow::WidthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	SPConfig newConfig = SPConfigManager::GetSingleton()->GetCurrentConfig();
	newConfig.windowWidth = value->Int32Value();
	SPGameManager::GetSingleton()->GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8TemplWindow::HeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton()->GetHeight()));
}

void SV8TemplWindow::HeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	SPConfig newConfig = SPConfigManager::GetSingleton()->GetCurrentConfig();
	newConfig.windowHeight = value->Int32Value();
	SPGameManager::GetSingleton()->GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8TemplWindow::FullScreenGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton()->IsFullScreen()));
}

void SV8TemplWindow::FullScreenSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	SPConfig newConfig = SPConfigManager::GetSingleton()->GetCurrentConfig();
	newConfig.windowed = !value->Int32Value();
	SPGameManager::GetSingleton()->GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8TemplWindow::Resize( const FunctionCallbackInfo<Value>& args )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if(args.Length() < 2)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	SPConfig newConfig = SPConfigManager::GetSingleton()->GetCurrentConfig();
	newConfig.windowWidth = args[0]->Int32Value();
	newConfig.windowHeight = args[1]->Int32Value();
	
	if (args.Length() > 2)
	{
		newConfig.windowed = !args[2]->BooleanValue();
	}

	SPGameManager::GetSingleton()->GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8TemplWindow::CursorGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(SPInputManager::GetSingleton()->GetCursor()));
}

void SV8TemplWindow::CursorSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	if(!SPV8ScriptEngine::GetSingleton())
	{
		return;
	}

	SPInputManager::GetSingleton()->SetCursor(SPV8ScriptEngine::StringToSPString(value->ToString()));
}

