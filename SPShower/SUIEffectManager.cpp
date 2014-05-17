#include "StdAfx.h"
#include "SUIEffectManager.h"

using namespace SPEngine;

SUIEffectManager::SUIEffectManager(void)
{
}


SUIEffectManager::~SUIEffectManager(void)
{
}

SUIEffectPtr SUIEffectManager::CreateEffect( SPString path )
{
	SUIEffectPtr effect = new SUIEffect();
	effect->Load(path);
	return effect;
}

SUIEffectPtr SUIEffectManager::GetEffect( SPString name )
{
	SUIEffectPtr effect = new SUIEffect();

	SPString path;

	if (effectFileNameMap.IsSet(name))
	{
		path = effectFileNameMap[name];
	}
	else
	{
		path = name;
	}

	effect->Load(path);
	return effect;
}

void SUIEffectManager::Load()
{
	//SPWStringMapIterator<SPString> iter(&effectFileNameMap);

	//for (iter.First(); !iter.IsDone(); iter.Next())
	//{
	//	SPEffectManager::GetSingleton()->GetCore(iter.CurrentItem());
	//}
}

void SUIEffectManager::Initialize()
{
	effectFileNameMap.Set(L"Mask",			L"effect\\effect_mask.fxo");
	effectFileNameMap.Set(L"Gauss",			L"effect\\effect_frequency_gauss.fxo");
	effectFileNameMap.Set(L"Gray",			L"effect\\effect_grayvalue.fxo");
	effectFileNameMap.Set(L"Mosaic",		L"effect\\effect_mosaic.fxo");
	effectFileNameMap.Set(L"MosaicAll",		L"effect\\effect_mosaicAll.fxo");
	effectFileNameMap.Set(L"Posure",		L"effect\\effect_posure.fxo");
	effectFileNameMap.Set(L"Relievo",		L"effect\\effect_relievo.fxo");
	effectFileNameMap.Set(L"Average",		L"effect\\effect_spacial_average.fxo");
	effectFileNameMap.Set(L"Laplace",		L"effect\\effect_spacial_laplace.fxo");
	effectFileNameMap.Set(L"Pencil",		L"effect\\effect_spacial_pencilFilter.fxo");
	effectFileNameMap.Set(L"WaterColor",	L"effect\\effect_watercolor.fxo");
	effectFileNameMap.Set(L"ZigZag",		L"effect\\effect_zigzag.fxo");

	effectFileNameMap.Set(L"TextGlow",		L"effect\\effect_text_glow.fxo");
	effectFileNameMap.Set(L"TextStroke",	L"effect\\effect_text_stroke.fxo");
	effectFileNameMap.Set(L"TextShadow",	L"effect\\effect_text_shadow.fxo");
}
