#include "StdAfx.h"
#include "SScriptHelper.h"

using namespace SPEngine;

SScriptHelper::SScriptHelper(void)
{
}


SScriptHelper::~SScriptHelper(void)
{
}

SPString SScriptHelper::VariablesToString( VariableMap variables )
{
	SPString result = L"";

	VariableMap::iterator iter = variables.begin();

	while(iter != variables.end())
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

KScript::VariableMap SScriptHelper::StringToVariables( SPString stringStream )
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
