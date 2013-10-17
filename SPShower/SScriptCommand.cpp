#include "StdAfx.h"
#include "SScriptCommand.h"

using namespace SPEngine;

SScriptCommand::SScriptCommand( SPString setName, VariableMap setArgs, SPString setFile, int setOrder )
{
	commandName = setName;
	args = setArgs;
	fileName = setFile;
	order = setOrder;
}

SScriptCommand::~SScriptCommand(void)
{
}

bool SScriptCommand::LoadFromString( SPString stringStream )
{
	if (stringStream.size() == 0)
	{
		return false;
	}

	commandName = SPStringHelper::XMLExcludeFrom(stringStream, L"CN");
	SPString propertiesString = SPStringHelper::XMLExcludeFrom(stringStream, L"Properties");
	args = StringToArgs(propertiesString);

	return true;
}

SPString SScriptCommand::SaveAsString()
{
	SPString result;

	result += SPStringHelper::XMLSurroundWith(commandName, L"CN");
	result += SPStringHelper::XMLSurroundWith(ArgsToString(), L"Properties");
	result += SPStringHelper::XMLSurroundWith(fileName, L"FN");
	result += SPStringHelper::XMLSurroundWith(SPStringHelper::ToWString(order), L"OD");

	result = SPStringHelper::XMLSurroundWith(result, L"SSC");

	return result;
}

SPString SScriptCommand::ArgsToString()
{
	SPString result = L"";

	VariableMap::iterator iter = args.begin();

	while(iter != args.end())
	{
		if (iter->first.size() < 5 
			|| iter->first.find(L"delta") == SPString::npos)
		{
			result += L"<P>";

			result += L"<N>";
			result += iter->first;
			result += L"</N>";

			result += L"<T>";
			result += SPStringHelper::ToWString((int)iter->second.type);
			result += L"</T>";

			result += L"<V>";
			result += iter->second.value;
			result += L"</V>";

			result += L"</P>";
		}

		iter++;
	}

	return result;
}

KScript::VariableMap SScriptCommand::StringToArgs( SPString stringStream )
{
	VariableMap argsMap;

	while(stringStream.size() > 0)
	{
		SPString propertyString = SPStringHelper::XMLExcludeFrom(stringStream, L"P");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"P");

		SPString argName = SPStringHelper::XMLExcludeFrom(propertyString, L"N");
		SPString argType = SPStringHelper::XMLExcludeFrom(propertyString, L"T");
		SPString argValue = SPStringHelper::XMLExcludeFrom(propertyString, L"V");

		argsMap[argName] = Value(argValue, SPStringHelper::StringToInt(argType));
	}

	return argsMap;
}
