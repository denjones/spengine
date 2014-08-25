#pragma once
#include "SUITransformation.h"
#include "SUIComponent.h"
#include "SUITextBox.h"
#include "SUIPictureBox.h"
#include "SUIEvent.h"
#include "ISV8Serializable.h"
#include "SV8FunctionManager.h"

using namespace SPEngine;

class SUIScreen;

typedef SPPointer<SUIScreen> SUIScreenPtr;

class SUIScreen : 
	public SPBaseScreen,
	public ISV8Serializable
{
	// V8 Object
	SPPointer<Persistent<Object>> v8Obj;

	SPTexturePtr screenTexture;
	SUITransformationPtr transformation;
	SUIScreenPtr targetScreen;
	D3DCOLOR backgroundColor;

	typedef SPWStringMap<SUIComponentPtr> ComponentMap;
	typedef SPWStringMapIterator<SUIComponentPtr> ComponentIterator; 
	typedef map<SUIComponent*, SUIComponentPtr> PersistentComponentMap;

	ComponentMap componentMap;
	PersistentComponentMap persistentComponentMap;
	SPString name;

	SV8FunctionManager eventHandlerManager;

	SUIComponentPtr topComponent;
	SUIComponentPtr currentComponent;
	SUITextBoxPtr currentTextBox;
	SUIPictureBoxPtr currentPictureBox;	

	CCritSec modificationLock;

public:
	SPString GetName();
	bool SetName(SPString setName);

	Handle<Object> GetV8Obj();

public:
	SUIScreen(void);
	virtual ~SUIScreen(void);

	void SetPersistentComponent( SUIComponentPtr pointer );
	SUIComponentPtr GetPersistentComponent( SUIComponent* component );
	void DeletePersistentComponent( SUIComponent* component );
	SPTexturePtr GetRenderTarget();
	SUIComponentPtr GetComponent(SPString name);
	void AddComponent(SUIComponentPtr newComponent);
	void CreateComponent(SPString name, SUIComponentPtr newComponent);
	void RemoveComponent(SPString name);
	void AddChildComponent(SPString fatherName, SPString childName);
	void SetTargetScreen(SUIScreenPtr setTarget);
	SUIScreenPtr GetTargetScreen();
	void SetTransformation(SUITransformationPtr setTrans);
	void SetBackgroundColor(D3DCOLOR setColor);
	D3DCOLOR GetBackgroundColor();
	void SetCurrentComponent(SUIComponentPtr setComponent);
	void SetCurrentTextBox(SUITextBoxPtr setTextBox);
	void SetCurrentPictureBox(SUIPictureBoxPtr setPictureBox);
	SUIComponentPtr GetCurrentComponent();
	SUITextBoxPtr GetCurrentTextBox();
	SUIPictureBoxPtr GetCurrentPictureBox();
	void SetPopUp(bool setPopUp);

	SV8FunctionHandle RegisterHandler(Handle<v8::Function> func);
	Handle<v8::Value> GetHandler(SV8FunctionHandle handle);
	

	void Focus();

	void HandleEvent(SUIEventPtr e);

	void Initialize();
	void Load();
	void Unload();
	void Reload();
	void Update(float timeDelta);
	void Draw(float timeDelta);
	void DrawOffScreen(float timeDelta);
	void Clear();

	SPString SaveAsString();
	void LoadFromString(SPString stringStrema);

	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );

};



