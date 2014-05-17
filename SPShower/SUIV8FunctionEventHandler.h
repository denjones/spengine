#pragma once
#include "SUIEventHandler.h"
#include "SV8FunctionManager.h"

using namespace v8;

class SUIV8FunctionEventHandler : public SUIEventHandler
{
	SV8FunctionHandle v8Func;
	SPPointer<Persistent<Object>> v8Self;

public:
	SUIV8FunctionEventHandler(Handle<v8::Function> v8Func, Handle<Object> v8Self);
	~SUIV8FunctionEventHandler(void);

	virtual bool Function( SUIEventPtr e );
	Handle<Value> GetFunction();
	SV8FunctionHandle GetHandle();
};

typedef SPPointer<SUIV8FunctionEventHandler> SUIV8FunctionEventHandlerPtr;