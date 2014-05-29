#pragma once
#include "SUIComponent.h"
#include "SPStringMap.h"
#include "SUIScreen.h"
#include "SUIEvent.h"
#include "ISV8Serializable.h"

class SUIManager :
	public SPComponent,
	public ISV8Serializable,
	public SPSingleton<SUIManager>	
{
	typedef SPWStringMap<SUIScreenPtr> ScreenMap;
	typedef SPWStringMapIterator<SUIScreenPtr> ScreenIterator;
	typedef list<SUIScreenPtr> ScreenStack;
	typedef SPPointer<ScreenStack> ScreenStackPtr;
	typedef ScreenStack::reverse_iterator ScreenStackIterator;
	typedef list<SUIEventPtr> EventQueue;
	typedef SPPointer<EventQueue> EventQueuePtr;
	typedef map<SUIScreen*, SUIScreenPtr> PersistentScreenMap;

	ScreenMap screenMap;
	PersistentScreenMap persistentScreenMap;
	ScreenStackPtr dispalyStack;
	EventQueuePtr eventQueue;
	float elapsedMouseDownTime[3];
	int elapsedMouseDownMovementX[3];
	int elapsedMouseDownMovementY[3];
	float elapsedMouseClickTime[3];
	int elapsedMouseClickMovementX[3];
	int elapsedMouseClickMovementY[3];
	float maxClickTime;
	float maxDClickTime;
	int interceptMouseButtonEvent[3];
	int interceptKeyboardKeyEvent[256];

	void* asyncEvent;
	CCritSec eventLock;
	CCritSec displayLock;

public:
	SUIManager(void);
	virtual ~SUIManager(void);

	ScreenStackPtr GetDisplayStack();
	EventQueuePtr GetEventQueue();
	void LockEventQueue();
	void UnlockEventQueue();

	void SetPersistentScreen(SUIScreenPtr screen);
	SUIScreenPtr GetPersistentScreen(SUIScreen* screenPtr);

	SUIScreenPtr GetScreen(SPString name);
	void AddScreen(SUIScreenPtr newComponent);
	void CreateScreen(SPString name, SUIScreenPtr newComponent);
	SUIScreenPtr GetCurrentScreen();
	void FocusScreen(SPString name);
	void FocusScreen(SUIScreenPtr screen);
	void SwitchToScreen(SPString name, SUITransformationPtr trans);
	bool IsScreenValid(SPString name);

	void GenerateEvent(float timeDelta);
	void InterceptMouseBotton(int button);
	void InterceptKeyboardKey(int key);

	void Initialize();
	void Load();
	void Unload();
	void Reload();
	void Update(float timeDelta);
	void Draw(float timeDelta);
	void HandleAllEvent();

	SPString SaveAsString();
	void LoadFromString(SPString path);

	// V8
	Handle<Object> SaveAsObj();
	Handle<Object> SaveScreenAsObj(SPString screensStr);
	void LoadFromObj(Handle<Object> obj);

	static void HandleAllEventCallback( uv_async_t *handle, int status );
};

