#pragma once
#include "SUITransformation.h"
#include "SUIComponent.h"
#include "SUITextBox.h"
#include "SUIPictureBox.h"
#include "SUIEvent.h"

using namespace SPEngine;

class SUIScreen;

typedef SPPointer<SUIScreen> SUIScreenPtr;

class SUIScreen : public SPBaseScreen
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
	SPTexturePtr GetRenderTarget();
	SUIComponentPtr GetComponent(SPString name);
	bool AddComponent(SUIComponentPtr newComponent);
	bool CreateComponent(SPString name, SUIComponentPtr newComponent);
	bool RemoveComponent(SPString name);
	bool AddChildComponent(SPString fatherName, SPString childName);
	bool SetTargetScreen(SUIScreenPtr setTarget);
	SUIScreenPtr GetTargetScreen();
	bool SetTransformation(SUITransformationPtr setTrans);
	bool SetBackgroundColor(D3DCOLOR setColor);
	D3DCOLOR GetBackgroundColor();
	bool SetCurrentComponent(SUIComponentPtr setComponent);
	bool SetCurrentTextBox(SUITextBoxPtr setTextBox);
	bool SetCurrentPictureBox(SUIPictureBoxPtr setPictureBox);
	SUIComponentPtr GetCurrentComponent();
	SUITextBoxPtr GetCurrentTextBox();
	SUIPictureBoxPtr GetCurrentPictureBox();

	bool SetPopUp(bool setPopUp);

	void Focus();

	bool HandleEvent(SUIEventPtr e);

	bool Initialize();
	bool Load();
	bool Unload();
	bool Reload();
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
	bool DrawOffScreen(float timeDelta);
	bool Clear();

	SPString SaveAsString();
	bool LoadFromString(SPString stringStrema);
};



