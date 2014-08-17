#include "StdAfx.h"
#include "SUIScreen.h"
#include "SUIComponent.h"
#include "SScriptHelper.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SV8Function.h"

#pragma warning (disable:4244)

using namespace SPEngine;

SUIScreen::SUIScreen(void)
{
	backgroundColor = 0x00000000;
}


SUIScreen::~SUIScreen(void)
{
	Clear();
	v8Obj->ClearAndLeak();
}

SPString SUIScreen::GetName()
{
	return name;
}

bool SUIScreen::SetName( SPString setName )
{
	modificationLock.Lock();
	name = setName;
	modificationLock.Unlock();
	return true;
}

SPEngine::SPTexturePtr SUIScreen::GetRenderTarget()
{
	return screenTexture;
}

SUIComponentPtr SUIScreen::GetComponent( SPString name )
{
	if (componentMap.IsSet(name))
	{
		return componentMap[name];
	}

	return NULL;
}

void SUIScreen::AddComponent( SUIComponentPtr newComponent )
{
	modificationLock.Lock();
	componentMap.Set(newComponent->GetName(), newComponent);
	SetPersistentComponent(newComponent);
	modificationLock.Unlock();
}

void SUIScreen::Initialize()
{
	topComponent = new SUIComponent(this);

	SUIProperties topProperties;

	topProperties.Init();
	*topProperties.layer = 0;
	*topProperties.backgroundColor = (DWORD)0x00000000;
	*topProperties.x = 0;
	*topProperties.y = 0;
	*topProperties.width = SPConfigManager::GetSingleton()->GetCurrentConfig()->workingWidth;
	*topProperties.height = SPConfigManager::GetSingleton()->GetCurrentConfig()->workingHeight;
	*topProperties.rotation = 0;
	*topProperties.rotationCenterX = SPConfigManager::GetSingleton()->GetCurrentConfig()->workingWidth / 2;
	*topProperties.rotationCenterY = SPConfigManager::GetSingleton()->GetCurrentConfig()->workingHeight / 2;
	*topProperties.transparency = 1;
	topProperties.backgroundImage = NULL;

	topComponent->SetProperties(topProperties);
	topComponent->AddEffect(NULL);
	topComponent->SetRenderTarget(NULL);
	topComponent->SetName(L"global_root");
	topComponent->SetAbsoluteRender(false);

	AddComponent(topComponent);
}

void SUIScreen::Load()
{
	PersistentComponentMap::iterator iter = persistentComponentMap.begin();
	while (iter!= persistentComponentMap.end())
	{
		iter->second->Load();
		iter++;
	}
}

void SUIScreen::Unload()
{
	screenTexture = NULL;

	PersistentComponentMap::iterator iter = persistentComponentMap.begin();
	while (iter!= persistentComponentMap.end())
	{
		iter->second->Unload();
		iter++;
	}
}

void SUIScreen::Reload()
{
	PersistentComponentMap::iterator iter = persistentComponentMap.begin();
	while (iter!= persistentComponentMap.end())
	{
		iter->second->Reload();
		iter++;
	}
}

void SUIScreen::Update( float timeDelta )
{
	if (transformation && targetScreen)
	{
		targetScreen->Update(timeDelta);
		transformation->Update(timeDelta);
		if (transformation->TransitionPosition() >= 1)
		{
			transformation = NULL;
			targetScreen = NULL;
			return;
		}
	}
	else if (targetScreen && !transformation)
	{
		return;
	}

	topComponent->Update(timeDelta);
}

void SUIScreen::Draw( float timeDelta )
{
	if (!isDisplay)
	{
		return;
	}	

	if (transformation && targetScreen)
	{
		targetScreen->DrawOffScreen(timeDelta);
		transformation->SetTarget(targetScreen->GetRenderTarget());
	}

	DrawOffScreen(timeDelta);	

	SPSpriteManager::GetSingleton()->RenderOnScreen(
		screenTexture, transformation, SRectangle(0,0,
		SPConfigManager::GetSingleton()->GetCurrentConfig()->workingWidth,
		SPConfigManager::GetSingleton()->GetCurrentConfig()->workingHeight),
		SPColor::White, 0.5, NULL);

	PersistentComponentMap::iterator iter = persistentComponentMap.begin();

	// Clear Cache

	while (iter!= persistentComponentMap.end())
	{
		iter->second->ClearAbsoluteCache();
		iter++;
	}
}

void SUIScreen::CreateComponent( SPString name, SUIComponentPtr newComponent )
{
	newComponent->SetName(name);
	modificationLock.Lock();
	componentMap.Set(name, newComponent);
	modificationLock.Unlock();
}

void SUIScreen::AddChildComponent( SPString fatherName, SPString childName )
{
	if (componentMap.IsSet(fatherName) && componentMap.IsSet(childName))
	{
		SUIComponentPtr father = componentMap[fatherName];
		SUIComponentPtr child	= componentMap[childName];

		if(father && child)
		{
			father->AddChild(child);
		}
	}
}

void SUIScreen::SetTargetScreen( SUIScreenPtr setTarget )
{
	modificationLock.Lock();
	targetScreen = setTarget;
	modificationLock.Unlock();
}

void SUIScreen::SetTransformation( SUITransformationPtr setTrans )
{
	modificationLock.Lock();
	transformation = setTrans;
	modificationLock.Unlock();
}

SUIScreenPtr SUIScreen::GetTargetScreen()
{
	return targetScreen;
}

void SUIScreen::DrawOffScreen( float timeDelta )
{
	screenTexture = SPTextureManager::GetSingleton()->CreateRenderTarget(
		SPConfigManager::GetSingleton()->GetCurrentConfig()->workingWidth, 
		SPConfigManager::GetSingleton()->GetCurrentConfig()->workingHeight,
		backgroundColor);

	topComponent->SetRenderTarget(screenTexture);
	topComponent->Render(timeDelta);
}

void SUIScreen::SetCurrentTextBox( SUITextBoxPtr setTextBox )
{
	modificationLock.Lock();
	currentTextBox = setTextBox;
	modificationLock.Unlock();
}

void SUIScreen::SetCurrentPictureBox( SUIPictureBoxPtr setPictureBox )
{
	modificationLock.Lock();
	currentPictureBox = setPictureBox;
	modificationLock.Unlock();
}

SUITextBoxPtr SUIScreen::GetCurrentTextBox()
{
	return currentTextBox;
}

SUIPictureBoxPtr SUIScreen::GetCurrentPictureBox()
{
	return currentPictureBox;
}

void SUIScreen::SetCurrentComponent( SUIComponentPtr setComponent )
{
	modificationLock.Lock();
	currentComponent = setComponent;
	modificationLock.Unlock();
}

SUIComponentPtr SUIScreen::GetCurrentComponent()
{
	return currentComponent;
}


void SUIScreen::HandleEvent( SUIEventPtr e )
{
	if (!e)
	{
		return;
	}

	topComponent->HandleEvent(e);
}

SPString SUIScreen::SaveAsString()
{
	SPString result = L"<SUIScreen></SUIScreen>";

	return result;
}

void SUIScreen::LoadFromString( SPString stringStream )
{

}

void SUIScreen::SetPopUp( bool setPopUp )
{
	modificationLock.Lock();
	isPopup = setPopUp;
	modificationLock.Unlock();
}

void SUIScreen::RemoveComponent( SPString name )
{
	modificationLock.Lock();
	componentMap.Remove(name);
	modificationLock.Unlock();
}

void SUIScreen::SetBackgroundColor( D3DCOLOR setColor )
{
	modificationLock.Lock();
	backgroundColor = setColor;
	modificationLock.Unlock();
}

void SUIScreen::Clear()
{
	modificationLock.Lock();

	//
	// Clear the circle references.
	//

	PersistentComponentMap::iterator iter = persistentComponentMap.begin();

	// Clear Cache

	while (iter!= persistentComponentMap.end())
	{
		iter->second->SetFather(NULL);
		iter++;
	}

	persistentComponentMap.clear();
	componentMap.Clear();

	topComponent = NULL;
	currentComponent = NULL;
	currentTextBox = NULL;
	currentPictureBox = NULL;	

	modificationLock.Unlock();
}

D3DCOLOR SUIScreen::GetBackgroundColor()
{
	return backgroundColor;
}

Handle<Object> SUIScreen::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetScreenTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}

void SUIScreen::SetPersistentComponent( SUIComponentPtr pointer )
{
	SUIComponent* realPointer = pointer.get();
	persistentComponentMap[realPointer] = pointer;
}

SUIComponentPtr SUIScreen::GetPersistentComponent( SUIComponent* component )
{
	if (persistentComponentMap.find(component) != persistentComponentMap.end())
	{
		return persistentComponentMap[component];
	}
	
	return NULL;
}

void SUIScreen::DeletePersistentComponent( SUIComponent* component )
{
	if (persistentComponentMap.find(component) != persistentComponentMap.end())
	{
		persistentComponentMap.erase(component);
	}
}

void SUIScreen::Focus()
{
	SUIManager::GetSingleton()->FocusScreen(SUIManager::GetSingleton()->GetPersistentScreen(this));
}

Handle<Object> SUIScreen::SaveAsObj()
{
	Handle<Object> result = SPV8ScriptEngine::CopyObject(GetV8Obj());
	result->Set(SPV8ScriptEngine::SPStringToString(L"root"), topComponent->SaveAsObj());
	result->Set(SPV8ScriptEngine::SPStringToString(L"_eventHandlerManager"), eventHandlerManager.SaveAsObj());
	return result;
}

void SUIScreen::LoadFromObj( Handle<Object> obj )
{
	Handle<Object> rootObj = Handle<Object>::Cast(SV8Function::GetProperty(L"root", obj));
	obj->Delete(SPV8ScriptEngine::SPStringToString(L"root"));
	
	Handle<Object> eventHandlerManagerObj = Handle<Object>::Cast(SV8Function::GetProperty(L"_eventHandlerManager", obj));
	obj->Delete(SPV8ScriptEngine::SPStringToString(L"_eventHandlerManager"));

	componentMap.Clear();
	persistentComponentMap.clear();
	eventHandlerManager.Clear();

	SPV8ScriptEngine::CoverObject(GetV8Obj(), obj);

	// Build function manager before root component built.
	eventHandlerManager.LoadFromObj(eventHandlerManagerObj);

	// Register component before loaded.
	topComponent = new SUIComponent(this);
	SetPersistentComponent(topComponent);
	topComponent->LoadFromObj(rootObj);

	componentMap[L"global_root"] = topComponent;
	
	return;
}

SV8FunctionHandle SUIScreen::RegisterHandler( Handle<v8::Function> func )
{
	return eventHandlerManager.RegisterFunction(func);
}

Handle<v8::Value> SUIScreen::GetHandler( SV8FunctionHandle handle )
{
	return eventHandlerManager.GetFunction(handle);
}


