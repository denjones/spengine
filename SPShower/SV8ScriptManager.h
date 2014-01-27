#pragma once
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
	SPPointer<SPV8ScriptEngine> requireEngine;
	SPPointer<Persistent<ObjectTemplate>> screenTempl;
	SPPointer<Persistent<ObjectTemplate>> componentTempl;
	SPPointer<Persistent<ObjectTemplate>> windowTempl;
	SPPointer<Persistent<ObjectTemplate>> textBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> dialogBoxTempl;

public:
	Handle<ObjectTemplate> GetScreenTemplate();
	Handle<ObjectTemplate> GetComponentTemplate();
	Handle<ObjectTemplate> GetWindowTemplate();
	Handle<ObjectTemplate> GetTextBoxTemplate();
	Handle<ObjectTemplate> GetDialogBoxTemplate();

private:
	static bool HasProperty(SPString propertyName, Handle<Object> obj);
	static Handle<Value> GetProperty(SPString propertyName, Handle<Object> obj);

public:
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

