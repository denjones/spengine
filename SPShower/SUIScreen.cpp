#include "StdAfx.h"
#include "SUIScreen.h"
#include "SUIComponent.h"
#include "SScriptHelper.h"
#include "SSFComponent.h"
#include "SSFList.h"
#include "SSFPictureBox.h"
#include "SSFTextBox.h"
#include "SSFDialogBox.h"
#include "SV8ScriptManager.h"

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

bool SUIScreen::AddComponent( SUIComponentPtr newComponent )
{
	modificationLock.Lock();
	componentMap.Set(newComponent->GetName(), newComponent);
	SetPersistentComponent(newComponent);
	modificationLock.Unlock();
	return true;
}

bool SUIScreen::Initialize()
{
	topComponent = new SUIComponent(this);

	SUIProperties topProperties;

	topProperties.layer = 0;
	topProperties.backgroundColor = (DWORD)0x00000000;
	topProperties.rectangle = 
		SRectangle(0, 0, 
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight);
	topProperties.rotation = 0;
	topProperties.rotationCenter = D3DXVECTOR2(
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth / 2,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight / 2);
	topProperties.transparency = 1;
	topProperties.backgroundImage = NULL;

	topComponent->SetProperties(topProperties);
	topComponent->AddEffect(NULL);
	topComponent->SetRenderTarget(NULL);
	topComponent->SetName(L"global_root");
	topComponent->SetAbsoluteRender(false);

	AddComponent(topComponent);

	return true;
}

bool SUIScreen::Load()
{
	ComponentIterator iter(&componentMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Load();
		}		
	}

	return true;
}

bool SUIScreen::Unload()
{
	screenTexture = NULL;

	ComponentIterator iter(&componentMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Unload();
		}		
	}

	return true;
}

bool SUIScreen::Reload()
{
	ComponentIterator iter(&componentMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->Reload();
		}		
	}

	return true;
}

bool SUIScreen::Update( float timeDelta )
{
	if (transformation && targetScreen)
	{
		targetScreen->Update(timeDelta);

		if(!transformation->Update(timeDelta))
		{
			transformation = NULL;
			targetScreen = NULL;
			return false;
		}
	}
	else if (targetScreen && !transformation)
	{
		return false;
	}

	topComponent->Update(timeDelta);

	return true;
}

bool SUIScreen::Draw( float timeDelta )
{
	if (!isDisplay)
	{
		return true;
	}	

	if (transformation && targetScreen)
	{
		targetScreen->DrawOffScreen(timeDelta);
		transformation->SetTarget(targetScreen->GetRenderTarget());
	}

	DrawOffScreen(timeDelta);	

	SPSpriteManager::GetSingleton().RenderOnScreen(
		screenTexture, transformation, SRectangle(0,0,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth,
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight),
		SPColor::White, 0.5, NULL);

	PersistentComponentMap::iterator iter = persistentComponentMap.begin();

	// Clear Cache

	while (iter!= persistentComponentMap.end())
	{
		iter->second->ClearAbsoluteCache();
		iter++;
	}

	return true;
}

bool SUIScreen::CreateComponent( SPString name, SUIComponentPtr newComponent )
{
	newComponent->SetName(name);
	modificationLock.Lock();
	componentMap.Set(name, newComponent);
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::AddChildComponent( SPString fatherName, SPString childName )
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

	return true;
}

bool SUIScreen::SetTargetScreen( SUIScreenPtr setTarget )
{
	modificationLock.Lock();
	targetScreen = setTarget;
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::SetTransformation( SUITransformationPtr setTrans )
{
	modificationLock.Lock();
	transformation = setTrans;
	modificationLock.Unlock();

	return true;
}

SUIScreenPtr SUIScreen::GetTargetScreen()
{
	return targetScreen;
}

bool SUIScreen::DrawOffScreen( float timeDelta )
{
	screenTexture = SPTextureManager::GetSingleton().CreateRenderTarget(
		SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth, 
		SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight,
		backgroundColor);

	topComponent->SetRenderTarget(screenTexture);
	topComponent->Render(timeDelta);

	return true;
}

bool SUIScreen::SetCurrentTextBox( SUITextBoxPtr setTextBox )
{
	modificationLock.Lock();
	currentTextBox = setTextBox;
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::SetCurrentPictureBox( SUIPictureBoxPtr setPictureBox )
{
	modificationLock.Lock();
	currentPictureBox = setPictureBox;
	modificationLock.Unlock();
	
	return true;
}

SUITextBoxPtr SUIScreen::GetCurrentTextBox()
{
	return currentTextBox;
}

SUIPictureBoxPtr SUIScreen::GetCurrentPictureBox()
{
	return currentPictureBox;
}

bool SUIScreen::SetCurrentComponent( SUIComponentPtr setComponent )
{
	modificationLock.Lock();
	currentComponent = setComponent;
	modificationLock.Unlock();

	return true;
}

SUIComponentPtr SUIScreen::GetCurrentComponent()
{
	return currentComponent;
}


bool SUIScreen::HandleEvent( SUIEventPtr e )
{
	if (!e)
	{
		return true;
	}

	return topComponent->HandleEvent(e);
}

SPString SUIScreen::SaveAsString()
{
	SPString result = L"<SUIScreen>";

	result += L"<Name>";
	result += name;
	result += L"</Name>";

	result += L"<ComponentMap>";

	ComponentIterator iter(&componentMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			result += iter.CurrentItem()->SaveAsString();
		}
	}

	result += L"</ComponentMap>";

	if (topComponent)
	{
		result += L"<TopComponentName>";
		result += topComponent->GetName();
		result += L"</TopComponentName>";
	}

	if (currentComponent)
	{
		result += L"<CurrentComponentName>";
		result += currentComponent->GetName();
		result += L"</CurrentComponentName>";
	}

	if (currentTextBox)
	{
		result += L"<CurrentTextBoxName>";
		result += currentTextBox->GetName();
		result += L"</CurrentTextBoxName>";
	}

	if (currentPictureBox)
	{
		result += L"<CurrentPictureBoxName>";
		result += currentPictureBox->GetName();
		result += L"</CurrentPictureBoxName>";
	}

	result += L"</SUIScreen>";

	return result;
}

bool SUIScreen::LoadFromString( SPString stringStream )
{
	SPString nameString = SPStringHelper::XMLExcludeFrom(stringStream, L"Name");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Name");
	SetName(nameString);

	SPString componentsString = SPStringHelper::XMLExcludeFrom(stringStream, L"ComponentMap");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"ComponentMap");
	SPString componentsStringCopy = componentsString;
	while(componentsString.size() > 0)
	{		
		if (componentsString.find(L"<SUICC>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUICC");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUICC");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFComponent().Function(properties, false);
		}

		if (componentsString.find(L"<SUIL>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIL");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIL");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFList().Function(properties, false);
		}

		if (componentsString.find(L"<SUIPB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIPB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIPB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFPictureBox().Function(properties, false);
		}

		if (componentsString.find(L"<SUITB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUITB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUITB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFTextBox().Function(properties, false);
		}

		if (componentsString.find(L"<SUIDB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIDB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIDB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFDialogBox().Function(properties, false);
		}
	}

	componentsString = componentsStringCopy;
	while(componentsString.size() > 0)
	{		
		if (componentsString.find(L"<SUICC>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUICC");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUICC");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFComponent().Function(properties, false);
		}

		if (componentsString.find(L"<SUIL>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIL");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIL");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFList().Function(properties, false);
		}

		if (componentsString.find(L"<SUIPB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIPB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIPB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFPictureBox().Function(properties, false);
		}

		if (componentsString.find(L"<SUITB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUITB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUITB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFTextBox().Function(properties, false);
		}

		if (componentsString.find(L"<SUIDB>") == 0)
		{
			SPString componentString = SPStringHelper::XMLExcludeFrom(componentsString, L"SUIDB");
			componentsString = SPStringHelper::XMLRemoveFirst(componentsString, L"SUIDB");
			VariableMap properties = SScriptHelper::StringToVariables(componentString);
			SSFDialogBox().Function(properties, false);
		}
	}

	SPString topNameString = SPStringHelper::XMLExcludeFrom(stringStream, L"TopComponentName");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"TopComponentName");
	topComponent = GetComponent(topNameString);

	SPString currentNameString = SPStringHelper::XMLExcludeFrom(stringStream, L"CurrentComponentName");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"TopComponentName");
	currentComponent = GetComponent(currentNameString);

	SPString currentTextBoxNameString = SPStringHelper::XMLExcludeFrom(stringStream, L"CurrentTextBoxName");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"CurrentTextBoxName");
	currentTextBox = GetComponent(currentTextBoxNameString);

	SPString currentPictureBoxNameString = SPStringHelper::XMLExcludeFrom(stringStream, L"CurrentPictureBoxName");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"CurrentPictureBoxName");
	currentPictureBox = GetComponent(currentPictureBoxNameString);

	return true;
}

bool SUIScreen::SetPopUp( bool setPopUp )
{
	modificationLock.Lock();
	isPopup = setPopUp;
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::RemoveComponent( SPString name )
{
	modificationLock.Lock();
	componentMap.Remove(name);
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::SetBackgroundColor( D3DCOLOR setColor )
{
	modificationLock.Lock();
	backgroundColor = setColor;
	modificationLock.Unlock();

	return true;
}

bool SUIScreen::Clear()
{
	modificationLock.Lock();

	//
	// Clear the circle references.
	//

	ComponentIterator iter(&componentMap);

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentItem())
		{
			iter.CurrentItem()->SetFather(NULL);
		}
	}

	componentMap.Clear();

	topComponent = NULL;
	currentComponent = NULL;
	currentTextBox = NULL;
	currentPictureBox = NULL;	

	modificationLock.Unlock();

	return true;
}

D3DCOLOR SUIScreen::GetBackgroundColor()
{
	return backgroundColor;
}

Handle<Object> SUIScreen::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton().GetScreenTemplate();
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

void SUIScreen::Focus()
{
	SUIManager::GetSingleton().FocusScreen(SUIManager::GetSingleton().GetPersistentScreen(this));
}


