#include "StdAfx.h"
#include "SUIParticleSystemManager.h"
#include "SScriptHelper.h"
#include "SV8Function.h"
#include "SV8TemplParticleSystem.h"


SUIParticleSystemManager::SUIParticleSystemManager(void)
{
}


SUIParticleSystemManager::~SUIParticleSystemManager(void)
{
	if (particleSystemTempl)
	{
		particleSystemTempl->ClearAndLeak();
		particleSystemTempl = NULL;
	}
}

SPEngine::SPParticleSystemTexturePtr SUIParticleSystemManager::GetParticleSystemTexture( SUIParticleSystemHandle handle )
{
	return SPTextureManager::GetSingleton()->GetParticleSystem(particleSystemIdManager[handle]);
}

Handle<Object> SUIParticleSystemManager::GetParticleSystem( SUIParticleSystemHandle handle )
{
	return particleSystemHandleManager[handle];
}

Handle<Object> SUIParticleSystemManager::CreateParticleSystem( Handle<Object> argObj )
{
	SPParticleSystem3DPtr particleSystem;

	bool isNameSet = false;
	SPString id = L"";

	if (SV8Function::HasProperty(L"id", argObj))
	{
		id = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"id", argObj)->ToString());
		particleSystem = SPParticleSystemManager::GetSingleton()->GetParticleSystem(id);

		if (!particleSystem)
		{
			SPParticleSystemManager::GetSingleton()->CreateParticleSystem(id);
			particleSystem =  SPParticleSystemManager::GetSingleton()->GetParticleSystem(id);
		}
	}
	else
	{
		id = SPStringHelper::ToWString(SPRandomHelper::NextInt(100000000));
		while(SPVideoManager::GetSingleton()->GetVideo(id))
		{
			id = SPStringHelper::ToWString(SPRandomHelper::NextInt(100000000));
		}
		SPParticleSystemManager::GetSingleton()->CreateParticleSystem(id);
		particleSystem = SPParticleSystemManager::GetSingleton()->GetParticleSystem(id);
	}

	SUIParticleSystemHandle handle = particleSystem.GetHandle();
	particleSystemIdManager[handle] = id;


	Local<Object> obj = Handle<Object>();

	Handle<ObjectTemplate> handleTempl = GetParticleSystemTemplate();
	obj = handleTempl->NewInstance();

	if(!obj.IsEmpty())
	{
		obj->SetInternalField(0, External::New(particleSystem.GetHandle()));

		const Local<Array> props = argObj->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = argObj->Get(key);

			obj->Set(key, value);
		}
	}

	particleSystemHandleManager[handle] = obj;
	

	return obj;
}

Handle<ObjectTemplate> SUIParticleSystemManager::GetParticleSystemTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*particleSystemTempl));
}

bool SUIParticleSystemManager::Initialize()
{
	//
	// Enter
	//

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton()->GetContext();
	Context::Scope contextScope(context);

	particleSystemTempl = new Persistent<ObjectTemplate>(isolate, 
		SV8TemplParticleSystem::GetTemplate());

	return true;
}

SPString SUIParticleSystemManager::GetParticleSystemName( SUIParticleSystemHandle handle )
{
	return particleSystemIdManager[handle];
}

//bool SUIParticleSystemManager::SetParticleSystemProperties( SPString name, VariableMap properties )
//{
//	if (!particleSystemPropertiesMap.IsSet(name))
//	{
//		particleSystemPropertiesMap.Add(name);
//	}
//
//	for(VariableMap::iterator iter = properties.begin();
//		iter != properties.end(); iter++)
//	{
//		particleSystemPropertiesMap[name][iter->first] = iter->second;
//	}
//
//	return true;
//}
//
//SPString SUIParticleSystemManager::SaveAsString()
//{
//	SPString result = L"";
//
//	SPWStringMapIterator<VariableMap> iter(&particleSystemPropertiesMap);
//
//	for(iter.First(); !iter.IsDone(); iter.Next())
//	{
//		result += SPStringHelper::XMLSurroundWith(iter.CurrentIndex(), L"PN");
//		result += SPStringHelper::XMLSurroundWith(SScriptHelper::VariablesToString(iter.CurrentItem()), L"PS");
//	}
//
//	return SPStringHelper::XMLSurroundWith(result, L"SUIParticleSys");
//}
//
//bool SUIParticleSystemManager::LoadFromString( SPString stringStream )
//{
//	particleSystemPropertiesMap.Clear();
//
//	while(stringStream.size() > 0)
//	{
//		SPString nameString = SPStringHelper::XMLExcludeFrom(stringStream, L"PN");
//		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"PN");
//
//		SPString propertiesString = SPStringHelper::XMLExcludeFrom(stringStream, L"PS");
//		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"PS");
//
//		SSFParticleSystem().Function(SScriptHelper::StringToVariables(propertiesString), false);
//	}
//
//	return true;
//}
