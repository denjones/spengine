#pragma once
#include "SV8ScriptCommand.h"

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
	typedef list<SV8ScriptCommandPtr> CommandList;
	typedef CommandList::iterator CommandIterator;
	typedef pair<int,int> Region;
	typedef SPPointer<Region> RegionPtr;
	typedef list<RegionPtr> RegionList;
	typedef RegionList::iterator RegionListIterator;
	typedef SPPointer<RegionList> RegionListPtr;
	typedef SPWStringMap<RegionListPtr> ReadCommands;

private:
	SPPointer<SPV8ScriptEngine> requireEngine;
	SPPointer<Persistent<ObjectTemplate>> screenTempl;
	SPPointer<Persistent<ObjectTemplate>> componentTempl;
	SPPointer<Persistent<ObjectTemplate>> windowTempl;
	SPPointer<Persistent<ObjectTemplate>> textBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> dialogBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> pictureBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> scrollTempl;
	SPPointer<Persistent<ObjectTemplate>> eventTempl;
	SPPointer<Persistent<ObjectTemplate>> commandEventTempl;
	SPPointer<Persistent<ObjectTemplate>> fpsTempl;

public:
	Handle<ObjectTemplate> GetScreenTemplate();
	Handle<ObjectTemplate> GetComponentTemplate();
	Handle<ObjectTemplate> GetWindowTemplate();
	Handle<ObjectTemplate> GetTextBoxTemplate();
	Handle<ObjectTemplate> GetDialogBoxTemplate();
	Handle<ObjectTemplate> GetPictureBoxTemplate();
	Handle<ObjectTemplate> GetScrollTemplate();
	Handle<ObjectTemplate> GetEventTemplate();
	Handle<ObjectTemplate> GetCommandEventTemplate();
	Handle<ObjectTemplate> GetFPSTemplate();

private:
	static bool HasProperty(SPString propertyName, Handle<Object> obj);
	static Handle<Value> GetProperty(SPString propertyName, Handle<Object> obj);

public:

	// Skip mode
	CommandList commands;
	bool isSkipModeOn;
	bool isImmediateModeOn;
	SkipMode skipMode;
	float autoWaitTimeS;
	bool isScriptRunning;
	CCritSec commandLock;
	void* async;

public:
	SV8ScriptManager(void);
	virtual ~SV8ScriptManager(void);

	void LockCommandQueue();
	void UnlockCommandQueue();

	bool Initialize();
	bool Update(float timeDelta);
	bool Load();
	bool Reload();
	bool Unload();

	void AddCommand(SV8ScriptCommandPtr command);
	void HandleCommands();

	static void HandleCommandCallback( uv_async_t *handle, int status );
	static void InitModule(Handle<Object> exports);
};

