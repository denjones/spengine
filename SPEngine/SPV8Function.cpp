#include "StdAfx.h"
#include "SPV8Function.h"
#include "SPV8ScriptEngine.h"

namespace SPEngine
{
	SPV8Function::SPV8Function(void)
	{
	}


	SPV8Function::~SPV8Function(void)
	{
	}

	Handle<Value> SPV8Function::Call(const FunctionCallbackInfo<Value>& args)
	{
		return Undefined(SPV8ScriptEngine::GetSingleton().GetIsolate());
	}

}