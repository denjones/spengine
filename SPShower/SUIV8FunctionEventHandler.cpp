#include "StdAfx.h"
#include "SUIV8FunctionEventHandler.h"


SUIV8FunctionEventHandler::SUIV8FunctionEventHandler(Handle<v8::Function> v8Func, Handle<Object> v8Self)
{
	this->v8Func = SV8FunctionManager::GetSingleton()->RegisterFunction(v8Func);
	this->v8Self = new Persistent<Object>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), v8Self);
}


SUIV8FunctionEventHandler::~SUIV8FunctionEventHandler(void)
{
	if (v8Self)
	{
		v8Self->ClearAndLeak();
		v8Self = NULL;
	}
}

bool SUIV8FunctionEventHandler::Function( SUIEventPtr e )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);
	Handle<Value> function = GetFunction();
	if (!function->IsFunction())
	{
		return true;
	}

	Handle<Object> self = Handle<Object>::New(isolate, (*v8Self));
	Handle<Object> event = e->GetV8Obj();
	Handle<Value> argv[1];
	argv[0] = event;

	Handle<Value> result = Handle<v8::Function>::Cast(function)->Call(self, 1, argv);
	if (result->IsNull())
	{
		return e->returnValue;
	}

	return result->BooleanValue();
}

Handle<Value> SUIV8FunctionEventHandler::GetFunction()
{
	return SV8FunctionManager::GetSingleton()->GetFunction(v8Func);
}

SV8FunctionHandle SUIV8FunctionEventHandler::GetHandle()
{
	return v8Func;
}
