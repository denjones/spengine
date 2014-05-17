#pragma once
#include "SV8CommandEvent.h"

using namespace SPEngine;

class SV8ScriptCommand
{
public:
	SPPointer<Persistent<Function>> v8Function;
	int line;
	int col;
	SPString file;
	SPString tag;

public:
	SV8ScriptCommand(Handle<Function> function, int line, int col, SPString file);
	SV8ScriptCommand(SPString tag, int line, int col, SPString file);
	virtual ~SV8ScriptCommand(void);

	void Call(SV8CommandEventPtr event);
	bool IsTag();
};

typedef SPPointer<SV8ScriptCommand> SV8ScriptCommandPtr;
