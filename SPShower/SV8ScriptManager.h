#pragma once
#include <SPV8ScriptEngine.h>
#include "SScriptCommand.h"

using namespace SPEngine;

class SV8ScriptManager :
	public SPComponent,
	public SPSingleton<SV8ScriptManager>
{
public:
	enum SkipMode{
		SkipRead,
		SkipAll,
		SkipAuto,
	};

private:
	SPPointer<Persistent<ObjectTemplate>> screenTempl;
	SPPointer<Persistent<ObjectTemplate>> componentTempl;
	SPPointer<Persistent<ObjectTemplate>> textBoxTempl;

	static void ScreenGetter(Local<String> property, const PropertyCallbackInfo<Value>& info);
	static void ScreenSetter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
	static void GetScreenProperty(Local<String> property, const PropertyCallbackInfo<Value>& info);
	static void SetScreenProperty(Local<String> property, Local<Value> value, const PropertyCallbackInfo<Value>& info);

public:
	Handle<ObjectTemplate> GetScreenTemplate();


	typedef list<SScriptCommand> CommandList;
	typedef CommandList::iterator CommandIterator;
	typedef pair<int,int> Region;
	typedef SPPointer<Region> RegionPtr;
	typedef list<RegionPtr> RegionList;
	typedef RegionList::iterator RegionListIterator;
	typedef SPPointer<RegionList> RegionListPtr;
	typedef SPWStringMap<RegionListPtr> ReadCommands;

	ReadCommands readCommands;
	CommandList commands;
	CommandList immediateCommands;
	CommandIterator currentPosition;
	ScriptPtr innerScript;
	VariableMap systemVariables;
	SPString firstName;
	int currentOrder;

	// Skip mode
	bool isSkipModeOn;
	bool isImmediateModeOn;
	SkipMode skipMode;
	float autoWaitTimeS;

public:
	SV8ScriptManager(void);
	virtual ~SV8ScriptManager(void);

	bool Initialize();
	bool Update(float timeDelta);
	bool Load();
	bool Reload();
	bool Unload();
};

