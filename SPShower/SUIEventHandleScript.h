#pragma once
#include <SPEngine.h>
#include "SUIEventHandler.h"

using namespace SPEngine;

class SUIEventHandleScript : public SUIEventHandler
{
	SPString stringScript;
	KScript::ScriptPtr script;

public:
	SUIEventHandleScript(SPString setScript);
	virtual ~SUIEventHandleScript(){}
	virtual bool Function(SUIEventPtr e);
	bool SetStringScript(SPString setScript);
};

typedef SPPointer<SUIEventHandleScript> SUIEventHandleScriptPtr;