#pragma once
#include "SPEngine.h"
#include <map>
#include "ISV8Serializable.h"

using namespace std;
using namespace SPEngine;

typedef int SV8FunctionHandle;

class SV8FunctionManager : 
	public ISV8Serializable
{
	typedef SPPointer<Persistent<v8::Function>> FunctionPtr;
	typedef map<SV8FunctionHandle, FunctionPtr> FunctionDict;
	typedef pair<FunctionPtr, SV8FunctionHandle> HandlePair;
	typedef vector<HandlePair> ObjectList;
	typedef SPPointer<ObjectList> ObjectListPtr;
	typedef map<SV8FunctionHandle, ObjectListPtr> ObjectDict;
	FunctionDict functionDict;
	ObjectDict objectDict;

public:
	SV8FunctionManager(void);
	~SV8FunctionManager(void);

	Handle<Value> GetFunction(SV8FunctionHandle handle);
	SV8FunctionHandle RegisterFunction(Handle<v8::Function> origin);

	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );

};

