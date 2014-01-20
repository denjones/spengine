#include "StdAfx.h"
#include "SV8Function.h"

SV8Function::SV8Function(void)
{
}


SV8Function::~SV8Function(void)
{
}

bool SV8Function::HasProperty( SPString propertyName, Handle<Object> obj )
{
	Handle<String> nameStr = SPV8ScriptEngine::SPStringToString(propertyName);
	return obj->HasRealNamedProperty(nameStr);
}

Handle<Value> SV8Function::GetProperty( SPString propertyName, Handle<Object> obj )
{
	Handle<String> nameStr = SPV8ScriptEngine::SPStringToString(propertyName);
	return obj->GetRealNamedProperty(nameStr);
}



