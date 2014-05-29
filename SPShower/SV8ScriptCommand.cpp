#include "StdAfx.h"
#include "SV8ScriptCommand.h"


SV8ScriptCommand::SV8ScriptCommand(Handle<Function> function, int line, int col, SPString file)
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	this->v8Function = new Persistent<Function>(isolate, function);
	this->line = line;
	this->col = col;
	this->file = file;
	this->tag = L"";
}

SV8ScriptCommand::SV8ScriptCommand( SPString tag, int line, int col, SPString file )
{
	this->line = line;
	this->col = col;
	this->file = file;
	this->tag = tag;
}


SV8ScriptCommand::~SV8ScriptCommand(void)
{
	if (v8Function)
	{
		v8Function->ClearAndLeak();
		v8Function = NULL;
	}
}

void SV8ScriptCommand::Call( SV8CommandEventPtr event )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	HandleScope handleScope(isolate);
	Handle<v8::Function> function = Handle<v8::Function>::New(isolate, (*v8Function));
	Handle<Object> eventObj = event->GetV8Obj();
	Handle<Value> argv[1];
	argv[0] = eventObj;

	Handle<Value> result = function->Call(isolate->GetCurrentContext()->Global(), 1, argv);
	if (!result->IsUndefined())
	{
		event->repeat = result->BooleanValue();
	}
}

bool SV8ScriptCommand::IsTag()
{
	return tag != L"";
}
