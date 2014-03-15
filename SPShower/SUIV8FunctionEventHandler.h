#pragma once
#include "SUIEventHandler.h"

using namespace v8;

class SUIV8FunctionEventHandler : public SUIEventHandler
{
	SPPointer<Persistent<v8::Function>> v8Func;
	SPPointer<Persistent<Object>> v8Self;

public:
	SUIV8FunctionEventHandler(Handle<v8::Function> v8Func, Handle<Object> v8Self);
	~SUIV8FunctionEventHandler(void);

	virtual bool Function( SUIEventPtr e );
	Handle<v8::Function> GetFunction();

};

typedef SPPointer<SUIV8FunctionEventHandler> SUIV8FunctionEventHandlerPtr;