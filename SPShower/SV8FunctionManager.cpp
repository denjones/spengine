#include "StdAfx.h"
#include "SV8FunctionManager.h"
#include "SV8Function.h"


SV8FunctionManager::SV8FunctionManager(void)
{
}


SV8FunctionManager::~SV8FunctionManager(void)
{
}

Handle<v8::Value> SV8FunctionManager::GetFunction( SV8FunctionHandle handle )
{
	if(functionDict.find(handle) == functionDict.end()){
		return v8::Undefined();
	}
	return Handle<v8::Function>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*functionDict[handle]));
}

SV8FunctionHandle SV8FunctionManager::RegisterFunction( Handle<v8::Function> origin )
{
	SV8FunctionHandle originHandle = origin->GetIdentityHash();
	ObjectListPtr objectList;
	if (objectDict.find(originHandle) != objectDict.end())
	{
		objectList = objectDict[originHandle];
		ObjectList::iterator objectIter = objectList->begin();
		while (objectIter != objectList->end())
		{
			if ((*(objectIter->first)) == origin)
			{
				return objectIter->second;
			}
			objectIter++;
		}
	}

	SV8FunctionHandle handle = SPRandomHelper::NextInt(1000000);
	while(functionDict.find(handle) != functionDict.end()){
		handle = SPRandomHelper::NextInt(1000000);
	}

	FunctionPtr persistentFunc = new Persistent<v8::Function>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), origin);
	functionDict[handle] = persistentFunc;

	if (!objectList)
	{
		objectList = new ObjectList();
		objectDict[originHandle] = objectList;
	}

	objectList->push_back(HandlePair(persistentFunc, handle));

	return handle;
}

Handle<Object> SV8FunctionManager::SaveAsObj()
{
	Handle<Object> result = Object::New();
	Handle<Object> functions = Object::New();
	FunctionDict::iterator funcIter = functionDict.begin();
	while(funcIter != functionDict.end())
	{
		Handle<String> handle = SPV8ScriptEngine::SPStringToString(SPStringHelper::ToWString(funcIter->first));
		Handle<String> funcStr = Handle<v8::Function>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*funcIter->second))->ToString();
		functions->Set(handle, funcStr);
		funcIter++;
	}
	result->Set(SPV8ScriptEngine::SPStringToString(L"functions"), functions);
	return result;
}

void SV8FunctionManager::LoadFromObj( Handle<Object> obj )
{
	functionDict.clear();
	Handle<Object> funcs = Handle<Object>::Cast(SV8Function::GetProperty(L"functions", obj));
	const Local<Array> props = funcs->GetPropertyNames();
	const uint32_t length = props->Length();
	for (uint32_t i = 0; i < length; i++)
	{
		const Local<Value> key = props->Get(i);
		const Local<Value> value = funcs->Get(key);

		Handle<v8::Function> func = SPV8ScriptEngine::ParseFunction(value->ToString());
		int handle = key->ToInt32()->Int32Value();
		functionDict[handle] = new Persistent<v8::Function>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), func);
	}

	return;
}
