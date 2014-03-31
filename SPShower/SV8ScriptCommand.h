#pragma once
#include "SV8CommandEvent.h"

using namespace SPEngine;

class SV8ScriptCommand
{
	SPPointer<Persistent<Function>> v8Function;

public:
	SV8ScriptCommand(Handle<Function> function);
	virtual ~SV8ScriptCommand(void);

	void Call(SV8CommandEventPtr event);
};

typedef SPPointer<SV8ScriptCommand> SV8ScriptCommandPtr;
