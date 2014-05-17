//////////////////////////////////////////////////////////////////////////
/// @file		SPV8ScriptEngine.h the header file of SPV8ScriptEngine class.
/// @author		Ken.J from SPRabbit
/// @version	Beta 0.9
/// @date		2013-12-31
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "SPComponent.h"
#include "SPSingleton.h"
#include <list>
#include "SPPointer.h"
#include <map>
#include "SPStringMap.h"
#include <node.h>

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
		typedef list<ScriptToRunPtr> ScriptList;
		typedef list<int> FunctionList;
		typedef map<int, FunctionList> TimeOutFunctionMap;
		typedef map<int, SPPointer<Persistent<Function>>> TimeOutMap;

		Isolate* isolate;
		SPPointer<Persistent<Context>> persistentContext;
		SPPointer<Locker> locker;
		SPPointer<Locker> threadLocker;

		CCritSec scriptToRunLock;		
		ScriptList scriptToRun;

		CCritSec timingScriptToRunLock;		
		TimeOutMap	timeOutMap;
		TimeOutFunctionMap timeOutFunctionToRun;

		CCritSec threadRunningLock;
		bool isThreadRunning;

		CCritSec stoppingLock;
		bool isStopping;

		void* pAsync;

	public:
		bool IsStopping();
		Isolate* GetIsolate();
		Handle<Context> GetContext();
		void* GetAsync();

		SPV8ScriptEngine(void);
		virtual ~SPV8ScriptEngine(void);

		// Inheritance

		void Initialize();
		void Load();
		void Unload();
		void Update( float timeElapsed );
		void Draw( float timeElapsed );

		// Script Related

		void AddFunction(SPString funcName, FunctionCallback function);
		Handle<Number> SetTimeOutFunction( Handle<Function> func, int timeoutMS );
		void ClearTimeOutFunction( Handle<Number> id);

		ScriptToRunPtr NextScriptToRun();
		void RunNextScript();
		void RunTimeOutFunc();
		void RunScript(SPString script);
		void RunScriptFromFile(SPString path);
		Handle<Value> Eval(SPString script, bool isInScope = false);
		Handle<Value> EvalFile(SPString path, bool isInScope = false);

		static void EvalFunc( const FunctionCallbackInfo<Value>& args );
		static void EvalFileFunc( const FunctionCallbackInfo<Value>& args );

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
		static Handle<String> ToJson(Handle<Value> object);
		static Handle<Object> CopyObject(Handle<Object> object);

	public:
		static void Import(const FunctionCallbackInfo<Value>& args);
		static void Include(const FunctionCallbackInfo<Value>& args);
		static void SleepFunc(const FunctionCallbackInfo<Value>& args);
		static void SetTimeOut(const FunctionCallbackInfo<Value>& args);
		static void ClearTimeOut(const FunctionCallbackInfo<Value>& args);

	private:
		void LogMessage(Handle<Message>& msg);
	};
}

