#pragma once
#include "SUIComponent.h"
#include "SPStringMap.h"
#include "SUIComponentComposite.h"
#include "SUIScreen.h"
#include "SUIEvent.h"

class SUIManager :
	public SPComponent,
	public SPSingleton<SUIManager>
{
	typedef SPWStringMap<SUIScreenPtr> ScreenMap;
	typedef SPWStringMapIterator<SUIScreenPtr> ScreenIterator;
	typedef list<SUIScreenPtr> ScreenStack;
	typedef ScreenStack::reverse_iterator ScreenStackIterator;
	typedef list<SUIEventPtr> EventQueue;

	SUIScreenPtr topScreen;
	ScreenMap screenMap;
	ScreenStack dispalyStack;
	EventQueue eventQueue;
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

public:
	SUIManager(void);
	virtual ~SUIManager(void);

	SUIScreenPtr GetScreen(SPString name);
	bool AddScreen(SUIScreenPtr newComponent);
	bool CreateScreen(SPString name, SUIScreenPtr newComponent);
	SUIScreenPtr GetCurrentScreen();
	bool FocusScreen(SPString name);
	bool SwitchToScreen(SPString name, SUITransformationPtr trans);
	bool IsScreenValid(SPString name);

	bool GenerateEvent(float timeDelta);
	bool InterceptMouseBotton(int button);
	bool InterceptKeyboardKey(int key);

	bool Initialize();
	bool Load();
	bool Unload();
	bool Update(float timeDelta);
	bool Draw(float timeDelta);

	SPString SaveAsString();
	bool LoadFromString(SPString path);
};

