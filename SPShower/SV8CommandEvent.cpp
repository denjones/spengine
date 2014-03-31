#include "StdAfx.h"
#include "SV8CommandEvent.h"
#include "SV8ScriptManager.h"


SV8CommandEvent::SV8CommandEvent(void)
{
	refresh = true;
	repeat = false;
	read = false;
}

SV8CommandEvent::~SV8CommandEvent(void)
{
	if (v8Obj)
	{
		v8Obj->ClearAndLeak();
		v8Obj = NULL;
	}
}

Handle<Object> SV8CommandEvent::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetCommandEventTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}
