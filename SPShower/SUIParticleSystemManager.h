#pragma once

using namespace SPEngine;

class SUIParticleSystemManager :
	public SPComponent,
	public SPSingleton<SUIParticleSystemManager>
{
	SPWStringMap<VariableMap> particleSystemPropertiesMap;

public:
	SUIParticleSystemManager(void);
	virtual ~SUIParticleSystemManager(void);

	bool SetParticleSystemProperties(SPString name, VariableMap properties);
	SPString SaveAsString();
	bool LoadFromString(SPString stringStream);

};

