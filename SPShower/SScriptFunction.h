#pragma once
#include <KScript.h>
#include <SPEngine.h>
#include "SUIComponent.h"

using namespace SPEngine;
using namespace KScript;

class SScriptFunction
{
protected:
	bool refreshScreen;
	bool waiting;
	SPString name;

public:
	SScriptFunction():refreshScreen(false), waiting(false), name(L"Unknown"){}
	virtual ~SScriptFunction(){}
	virtual bool Function(VariableMap args, bool isRead) = 0;

	bool SetName(SPString setName)
	{
		name = setName;

		return true;
	}

	bool IsSet(wstring name, VariableMap args)
	{
		if(args.find(name) == args.end())
		{
			return false;
		}

		return true;
	}

	bool SetComponentProperties(SUIComponentPtr component, VariableMap &args);
	bool OutLogUnusedProperties(VariableMap args);
	bool IsWaiting();
	bool IsNeedToRefresh();
};

typedef SPPointer<SScriptFunction> SScriptFunctionPtr;
