//////////////////////////////////////////////////////////////////////////
/// @file		SPV8ScriptEngine.h the header file of SPV8ScriptEngine class.
/// @author		Ken.J from SPRabbit
/// @version	Beta 0.9
/// @date		2013-12-31
//////////////////////////////////////////////////////////////////////////

#pragma once

#include <v8.h>
#include "SPComponent.h"
#include "SPSingleton.h"
#include <list>
#include "SPPointer.h"
#include <map>
#include "SPV8Function.h"

using namespace v8;
using namespace std;

namespace SPEngine
{
	enum ScriptType
	{
		ScriptString,
		ScriptFile,
	};

	class ScriptToRun
	{
	public:
		ScriptType type;
		SPString value;
	
		ScriptToRun(ScriptType type, SPString value)
		{
			this->type = type;
			this->value = value;
		}
	};

	typedef SPPointer<ScriptToRun> ScriptToRunPtr;

	//////////////////////////////////////////////////////////////////////
	/// @brief class SPV8ScriptEngine
	/// Allow user to use javascript as engine script.
	///
	//////////////////////////////////////////////////////////////////////
	class SPV8ScriptEngine : 
		public SPComponent, 
		public SPSingleton<SPV8ScriptEngine>
	{
		Isolate* isolate;
		SPPointer<Persistent<Context>> persistentContext;
		SPPointer<Locker> locker;
		SPPointer<Locker> threadLocker;

		CCritSec scriptToRunLock;
		typedef list<ScriptToRunPtr> ScriptList;
		ScriptList scriptToRun;

		CCritSec timingScriptToRunLock;
		typedef map<int, ScriptList> TimeingScriptMap;
		TimeingScriptMap timingScriptToRun;

		CCritSec threadRunningLock;
		bool isThreadRunning;

		CCritSec stoppingLock;
		bool isStopping;

		HANDLE hExit;

	public:
		bool IsStopping();
		Isolate* GetIsolate();
		Handle<Context> GetContext();

		SPV8ScriptEngine(void);
		~SPV8ScriptEngine(void);

		// Inheritance

		bool Initialize();
		bool Load();
		bool Unload();
		bool Update( float timeElapsed );
		bool Draw( float timeElapsed );

		// Script Related

		void AddFunction(SPString funcName, FunctionCallback function);
		void AddTimingScript(ScriptToRunPtr script, int timeoutMS);
		ScriptToRunPtr NextScriptToRun();
		bool RunNextScript();
		void RunScript(SPString script);
		void RunScriptFromFile(SPString path);
		Handle<Value> Eval(SPString script, bool isInScope = false);
		Handle<Value> EvalFile(SPString path, bool isInScope = false);

		// Thread Related

		void Enter();
		void Exit();
		void ThreadEnter();
		void ThreadExit();
		void StartThread();
		void StopThread();
		void ThreadExited();

		static SPString StringToSPString(Handle<String> str);
		static DWORD WINAPI ScriptRunningThread(void* context);
		static Handle<String> SPStringToString(SPString str);

	private:
		void LogMessage(Handle<Message>& msg);
	};
}

