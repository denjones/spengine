#pragma once

using namespace KScript;

class SScriptCommand
{
public:
	SPString commandName;
	SPString fileName;
	int order;

	VariableMap args;

public:
	SScriptCommand(SPString setName, VariableMap setArgs, SPString setFile, int setOrder);
	virtual ~SScriptCommand(void);

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
	SPString ArgsToString();
	VariableMap StringToArgs(SPString stringStream);
};

