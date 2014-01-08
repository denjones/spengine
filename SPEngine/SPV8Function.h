//////////////////////////////////////////////////////////////////////////
/// @file		SPV8Function.h the header file of SPV8Function class.
/// @author		Ken.J from SPRabbit
/// @version	Beta 0.9
/// @date		2014-01-08
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <v8.h>
#include "SPPointer.h"

using namespace v8;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPV8Function
	/// Represent an engine function in global context.
	///
	//////////////////////////////////////////////////////////////////////
	class SPV8Function
	{
	public:
		SPV8Function(void);
		virtual ~SPV8Function(void);
		virtual Handle<Value> Call(const FunctionCallbackInfo<Value>& args);
	};

	typedef SPPointer<SPV8Function> SPV8FunctionPtr;
}


