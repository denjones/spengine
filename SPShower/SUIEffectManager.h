#pragma once
#include "SUIEffect.h"

using namespace SPEngine;

class SUIEffectManager : 
	public SPComponent,
	public SPSingleton<SUIEffectManager>
{
	typedef SPWStringMap<SPString> EffectFileNameMap;

	EffectFileNameMap effectFileNameMap;

public:
	SUIEffectManager(void);
	virtual ~SUIEffectManager(void);

	bool Load();
	bool Initialize();

	SUIEffectPtr CreateEffect(SPString path );
	SUIEffectPtr GetEffect(SPString name);
};

