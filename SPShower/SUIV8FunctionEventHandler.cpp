#include "StdAfx.h"
#include "SUIV8FunctionEventHandler.h"


SUIV8FunctionEventHandler::SUIV8FunctionEventHandler(Handle<v8::Function> v8Func, Handle<Object> v8Self)
{
	this->v8Func = new Persistent<v8::Function>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), v8Func);
	this->v8Self = new Persistent<Object>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), v8Self);
}


SUIV8FunctionEventHandler::~SUIV8FunctionEventHandler(void)
{
	if (v8Func)
	{
		v8Func->ClearAndLeak();
		v8Func = NULL;
	}

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
	Handle<v8::Function> function = GetFunction();
	Handle<Object> self = Handle<Object>::New(isolate, (*v8Self));
	Handle<Object> event = e->GetV8Obj();
	Handle<Value> argv[1];
	argv[0] = event;

	Handle<Value> result = function->Call(self, 1, argv);
	if (result->IsNull())
	{
		return e->returnValue;
	}

	return result->BooleanValue();
}

Handle<v8::Function> SUIV8FunctionEventHandler::GetFunction()
{
	return Handle<v8::Function>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*v8Func));
}
