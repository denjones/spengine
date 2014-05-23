#include "StdAfx.h"
#include "SUIV8FunctionEventHandler.h"
#include "SUIComponent.h"
#include "SUIScreen.h"


SUIV8FunctionEventHandler::SUIV8FunctionEventHandler(Handle<v8::Function> v8Func, SUIComponentPtr self)
{
	this->v8Func = self->GetScreen()->RegisterHandler(v8Func);
	this->self = self;
}


SUIV8FunctionEventHandler::~SUIV8FunctionEventHandler(void)
{

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

	Handle<Object> event = e->GetV8Obj();
	Handle<Value> argv[1];
	argv[0] = event;

	Handle<Value> result = Handle<v8::Function>::Cast(function)->Call(self->GetV8Obj(), 1, argv);
	if (result->IsNull())
	{
		return e->returnValue;
	}

	return result->BooleanValue();
}

Handle<Value> SUIV8FunctionEventHandler::GetFunction()
{
	return self->GetScreen()->GetHandler(v8Func);
}

SV8FunctionHandle SUIV8FunctionEventHandler::GetHandle()
{
	return v8Func;
}
