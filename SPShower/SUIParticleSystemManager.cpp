#include "StdAfx.h"
#include "SUIParticleSystemManager.h"
#include "SScriptHelper.h"
#include "SSFParticleSystem.h"


SUIParticleSystemManager::SUIParticleSystemManager(void)
{
}


SUIParticleSystemManager::~SUIParticleSystemManager(void)
{
}

bool SUIParticleSystemManager::SetParticleSystemProperties( SPString name, VariableMap properties )
{
	if (!particleSystemPropertiesMap.IsSet(name))
	{
		particleSystemPropertiesMap.Add(name);
	}

	for(VariableMap::iterator iter = properties.begin();
		iter != properties.end(); iter++)
	{
		particleSystemPropertiesMap[name][iter->first] = iter->second;
	}

	return true;
}

SPString SUIParticleSystemManager::SaveAsString()
{
	SPString result = L"";

	SPWStringMapIterator<VariableMap> iter(&particleSystemPropertiesMap);

	for(iter.First(); !iter.IsDone(); iter.Next())
	{
		result += SPStringHelper::XMLSurroundWith(iter.CurrentIndex(), L"PN");
		result += SPStringHelper::XMLSurroundWith(SScriptHelper::VariablesToString(iter.CurrentItem()), L"PS");
	}

	return SPStringHelper::XMLSurroundWith(result, L"SUIParticleSys");
}

bool SUIParticleSystemManager::LoadFromString( SPString stringStream )
{
	particleSystemPropertiesMap.Clear();

	while(stringStream.size() > 0)
	{
		SPString nameString = SPStringHelper::XMLExcludeFrom(stringStream, L"PN");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"PN");

		SPString propertiesString = SPStringHelper::XMLExcludeFrom(stringStream, L"PS");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"PS");

		SSFParticleSystem().Function(SScriptHelper::StringToVariables(propertiesString), false);
	}

	return true;
}
