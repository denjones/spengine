#include "StdAfx.h"
#include "SUIEvent.h"
#include "SV8ScriptManager.h"

SUIEvent::SUIEvent():
	type(None),
	button(0),
	positionX(0),
	positionY(0),
	movementX(0),
	movementY(0),
	absoluteX(0),
	absoluteY(0)
{}

	Handle<Object> SUIEvent::GetV8Obj()
	{
		Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();

		if (!v8Obj)
		{
			Local<Object> obj = Handle<Object>();

			Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton().GetEventTemplate();
			obj = handleTempl->NewInstance();

			if(!obj.IsEmpty())
			{
				obj->SetInternalField(0, External::New(this));
				v8Obj = new Persistent<Object>(isolate, obj);
			}
		}

		return Handle<Object>::New(isolate, *v8Obj);
	}
