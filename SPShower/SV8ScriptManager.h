#pragma once
#include "SV8ScriptCommand.h"
#include "ISV8Serializable.h"

using namespace SPEngine;

class SV8ScriptManager :
	public SPComponent,
	public ISV8Serializable,
	public SPSingleton<SV8ScriptManager>
{

public:
	enum SkipMode
	{
		SkipRead,
		SkipAll,
		SkipAuto,
	};

	struct ReadRegion
	{
		int startLine;
		int startCol;
		int endLine;
		int endCol;
	};

	typedef SPPointer<ReadRegion> ReadRegionPtr;
	typedef list<ReadRegionPtr> ReadList;
	typedef SPPointer<ReadList> ReadListPtr;

private:
	typedef list<SV8ScriptCommandPtr> CommandList;
	typedef CommandList::iterator CommandIterator;
	//typedef pair<int,int> Region;
	//typedef SPPointer<Region> RegionPtr;
	//typedef list<RegionPtr> RegionList;
	//typedef RegionList::iterator RegionListIterator;
	//typedef SPPointer<RegionList> RegionListPtr;
	//typedef SPWStringMap<RegionListPtr> ReadCommands;

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
	SPPointer<Persistent<v8::Function>> onExit;
	SPPointer<Persistent<v8::Object>> systemVariables;
	SPPointer<Persistent<v8::Object>> variables;

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
	Handle<v8::Value> GetOnExitFunc();
	void SetOnExitFunc(Handle<v8::Function> func);
	Handle<v8::Value> GetSystemVariable();
	Handle<v8::Value> GetVariable();

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
	void* exitAsync;
	
	SPWStringMap<ReadListPtr> readCommands;
	ReadRegionPtr currentRegion;
	SPString gotoFile;
	SPString gotoTag;

public:
	SV8ScriptManager(void);
	virtual ~SV8ScriptManager(void);

	void LockCommandQueue();
	void UnlockCommandQueue();

	void Initialize();
	void Update(float timeDelta);
	void Load();
	void Reload();
	void Unload();

	void AddCommand(SV8ScriptCommandPtr command);
	void HandleCommands();
	bool IsCommandRead(SV8ScriptCommandPtr command);
	void SetCommandRead(SV8ScriptCommandPtr command);
	void Goto(SPString file, SPString tag);
	void Exit();

	static void HandleCommandCallback( uv_async_t *handle, int status );
	static void OnExit( uv_async_t *handle, int status );
	static void InitModule(Handle<Object> exports);

	Handle<Object> SaveReadAsObj();
	void LoadReadFromObj(Handle<Object> obj);
	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );

};

