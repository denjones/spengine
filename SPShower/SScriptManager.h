#pragma once
#include "SScriptCommand.h"
#include "SScriptFunction.h"
#include <list>

using namespace SPEngine;
using namespace KScript;

class SScriptManager : 	
	public SPScriptManager,
	public SPComponent,
	public SPSingleton<SScriptManager>
{
public:
	enum SkipMode{
		SkipRead,
		SkipAll,
		SkipAuto,
	};

private:
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
	SPWStringMap<SScriptFunctionPtr> functions;
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
	SScriptManager(void);
	virtual ~SScriptManager(void);

	bool AddCommand(SScriptCommand newCommand, KScript::Script* currentScript = NULL );
	bool AddFunction(SPString name, SScriptFunctionPtr function);

	bool ExecuteInnerScript(SPString stringScript);
	bool ExecuteInnerScript(KScript::ScriptPtr script);
	bool ImmediateModeOn();
	bool ImmediateModeOff();

	SScriptCommand NextCommand();
	bool Initialize();
	bool Update(float timeDelta);
	bool Load();
	bool Reload();

	// Change insertion.
	bool SetInsertPosFront(int offset);
	bool SetInsertPosBack();

	// Command replacement.
	bool ReplaceCommandsFromFile(KString path);
	bool ReloadCommands();
	bool ClearCommands();
	bool LocateCommands(SScriptCommand target);

	// System variables
	bool UpdateSystemVariables(VariableMap setVars);
	bool InitializeSystemVariables(VariableMap setVars);	
	bool ReadCommandsFromString(SPString str);
	VariableMap GetSystemVariables();

	// Set first script.
	bool SetFirst(SPString setPath);

	bool SetSystemVariables(VariableMap setVars);
	SPString ReadCommandsToString();

	// Skip mode.
	void SkipModeOn(){ isSkipModeOn = true; }
	void SkipModeOff(){ isSkipModeOn = false; }
	void SetSkipMode(SkipMode mode){ skipMode = mode; }
	bool IsSkipModeOn(){ return isSkipModeOn; }
	SkipMode GetSkipMode(){ return skipMode; }
	float GetAutoWaitTimeS(){ return autoWaitTimeS; }
	void SetAutoWaitTimeS(float setTimeS){ autoWaitTimeS = setTimeS; }

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();

	virtual Value Execute();

private:
	bool IsCommandRead(SScriptCommand command);
	bool SetCommandRead(SScriptCommand command);

};

class AddCommandToCommandList : public ExtendedMapArgsFunction
{	
	SPString name;

public:
	AddCommandToCommandList(SPString setName){ name = setName;}
	virtual ~AddCommandToCommandList(){}

	virtual Value Function(KScript::Script* currentScript, VariableMap args )
	{
		SScriptManager::GetSingleton().AddCommand(SScriptCommand(name, args, currentScript->fileName, 0), currentScript);
		return Value();
	}
};

class IncludeMapArgsFunc : public ExtendedMapArgsFunction
{	
	KScriptRunner* runner;

public:
	IncludeMapArgsFunc(KScriptRunner* setRunner){ runner = setRunner;}
	virtual ~IncludeMapArgsFunc(){}
	virtual Value Function(KScript::Script* currentScript, VariableMap args )
	{
		if (args.size() == 0)
		{
			return Value();
		}

		bool inherit = true;
		bool rewrite = true;

		if (args.find(L"inherit") != args.end() && args[L"inherit"].value == L"0")
		{
			inherit = false;
		}

		if (args.find(L"rewrite") != args.end() && args[L"rewrite"].value == L"0")
		{
			rewrite = false;
		}

		if (args.find(L"file") == args.end())
		{
			return Value();
		}

		KString path = args[L"file"].value;

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			return Value();
		}

		LONGLONG length = file->GetFileLength();
		char* pBuffer = new char[(UINT)length];

		if(!file->Read(pBuffer, (DWORD)length))
		{
			return Value();
		}

		SPFileManager::GetSingleton().CloseFile(path);

		Script innerScript(runner);

		if(!innerScript.LoadScriptStream(pBuffer, (DWORD)length, path))
		{
			delete [] pBuffer;
			return Value();
		}

		delete [] pBuffer;
		pBuffer = NULL;

		if (inherit)
		{
			innerScript.SetVariableMap(currentScript->GetVariableMap());
		}		

		Value result = innerScript.Execute();

		if (rewrite)
		{
			currentScript->SetVariableMap(innerScript.GetVariableMap());
		}

		return result;
	}
};