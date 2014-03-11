#pragma once

using namespace SPEngine;

typedef SPParticleSystem3D* SUIParticleSystemHandle;

class SUIParticleSystemManager :
	public SPComponent,
	public SPSingleton<SUIParticleSystemManager>
{
	//SPWStringMap<VariableMap> particleSystemPropertiesMap;

	map<SUIParticleSystemHandle, Handle<Object>> particleSystemHandleManager;
	map<SUIParticleSystemHandle, SPString> particleSystemIdManager;
	SPPointer<Persistent<ObjectTemplate>> particleSystemTempl;

public:
	SUIParticleSystemManager(void);
	virtual ~SUIParticleSystemManager(void);

	//bool SetParticleSystemProperties(SPString name, VariableMap properties);
	//SPString SaveAsString();
	//bool LoadFromString(SPString stringStream);

	SPParticleSystemTexturePtr GetParticleSystemTexture(SUIParticleSystemHandle handle);
	Handle<Object> GetParticleSystem(SUIParticleSystemHandle handle);
	SPString GetParticleSystemName(SUIParticleSystemHandle handle);
	Handle<Object> CreateParticleSystem(Handle<Object> argObj);
	Handle<ObjectTemplate> GetParticleSystemTemplate();

	virtual bool Initialize();
};

