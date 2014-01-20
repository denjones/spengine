#include "StdAfx.h"
#include "SV8Window.h"



Handle<ObjectTemplate> SV8Window::GetTemplate()
{
	Handle<ObjectTemplate> templWindow = ObjectTemplate::New();

	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"title"), TitleGetter, TitleSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"width"), WidthGetter, WidthSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"height"), HeightGetter, HeightSetter);
	templWindow->SetAccessor(SPV8ScriptEngine::SPStringToString(L"fullScreen"), FullScreenGetter, FullScreenSetter);

	// Methods

	templWindow->Set(SPV8ScriptEngine::SPStringToString(L"resize"), 
		FunctionTemplate::New(Resize)->GetFunction());

	return templWindow;
}

void SV8Window::WindowGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	
}

void SV8Window::WindowSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{

}

void SV8Window::TitleGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	info.GetReturnValue().Set(SPV8ScriptEngine::SPStringToString(SPWindow::GetSingleton().GetTitle()));
}

void SV8Window::TitleSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	SPWindow::GetSingleton().SetTitle(SPV8ScriptEngine::StringToSPString(value->ToString()));
}

void SV8Window::WidthGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton().GetWidth()));
}

void SV8Window::WidthSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	SPConfig newConfig = SPConfigManager::GetSingleton().GetCurrentConfig();
	newConfig.windowWidth = value->Int32Value();
	SPGameManager::GetSingleton().GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8Window::HeightGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton().GetHeight()));
}

void SV8Window::HeightSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	SPConfig newConfig = SPConfigManager::GetSingleton().GetCurrentConfig();
	newConfig.windowHeight = value->Int32Value();
	SPGameManager::GetSingleton().GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8Window::FullScreenGetter( Local<String> property, const PropertyCallbackInfo<Value>& info )
{
	info.GetReturnValue().Set(Number::New(SPWindow::GetSingleton().IsFullScreen()));
}

void SV8Window::FullScreenSetter( Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info )
{
	SPConfig newConfig = SPConfigManager::GetSingleton().GetCurrentConfig();
	newConfig.windowed = !value->Int32Value();
	SPGameManager::GetSingleton().GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

void SV8Window::Resize( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();

	if(args.Length() < 2)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	SPConfig newConfig = SPConfigManager::GetSingleton().GetCurrentConfig();
	newConfig.windowWidth = args[0]->Int32Value();
	newConfig.windowHeight = args[1]->Int32Value();
	
	if (args.Length() > 2)
	{
		newConfig.windowed = !args[2]->BooleanValue();
	}

	SPGameManager::GetSingleton().GetGame()->ApplyConfigWhenCurrentDrawFinished(newConfig);
}

