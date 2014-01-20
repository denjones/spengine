#pragma once

using namespace SPEngine;

class SV8Function
{
	//static void Import(const FunctionCallbackInfo<Value>& args);
	//static void Include(const FunctionCallbackInfo<Value>& args);

private:
	SV8Function(void);
	~SV8Function(void);

public:

	//
	// Global Function
	//

	static void CreateScreen(const FunctionCallbackInfo<Value>& args);

	//
	// SpeShow Command
	//

	
	
	//
	// Helper
	//

	static bool HasProperty(SPString propertyName, Handle<Object> obj);
	static Handle<Value> GetProperty(SPString propertyName, Handle<Object> obj);
};

