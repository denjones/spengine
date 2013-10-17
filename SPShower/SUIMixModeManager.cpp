#include "StdAfx.h"
#include "SUIMixModeManager.h"


SUIMixModeManager::SUIMixModeManager(void)
{
}


SUIMixModeManager::~SUIMixModeManager(void)
{
}

SUIMixModePtr SUIMixModeManager::GetMixMode( SPString name )
{
	if (mixModeFileNames.IsSet(name))
	{
		return new SUIMixMode(mixModeFileNames[name]);
	}
	else
	{
		SUIMixModePtr mode = new SUIMixMode();

		if (mode->Load(name))
		{
			return mode;
		}
	}

	return NULL;
}

SUIMixModePtr SUIMixModeManager::CreateMixMode( SPString path )
{
	SUIMixModePtr mode = new SUIMixMode();

	if (mode->Load(path))
	{
		return mode;
	}

	return NULL;
}

bool SUIMixModeManager::Load()
{
	mixModeFileNames.Set(L"Mask",		L"mix\\mix_mask.fxo");
	mixModeFileNames.Set(L"ColorBurn",	L"mix\\mix_color_burn.fxo");
	mixModeFileNames.Set(L"ColorDodge", L"mix\\mix_color_dodge.fxo");
	mixModeFileNames.Set(L"Darken",		L"mix\\mix_darken.fxo");
	mixModeFileNames.Set(L"Difference",	L"mix\\mix_difference.fxo");
	mixModeFileNames.Set(L"Exclusion",	L"mix\\mix_exclusion.fxo");
	mixModeFileNames.Set(L"Hard",		L"mix\\mix_hard.fxo");
	mixModeFileNames.Set(L"HardLight",	L"mix\\mix_hard_light.fxo");
	mixModeFileNames.Set(L"Lighten",	L"mix\\mix_lighten.fxo");
	mixModeFileNames.Set(L"LinearBurn", L"mix\\mix_linear_burn.fxo");
	mixModeFileNames.Set(L"LinearDodge",L"mix\\mix_linear_dodge.fxo");
	mixModeFileNames.Set(L"LinearLight",L"mix\\mix_linear_light.fxo");
	mixModeFileNames.Set(L"Multiply",	L"mix\\mix_multiply.fxo");
	mixModeFileNames.Set(L"Normal",		L"mix\\mix_normal.fxo");
	mixModeFileNames.Set(L"Overlay",	L"mix\\mix_overlay.fxo");
	mixModeFileNames.Set(L"PinLight",	L"mix\\mix_pin_light.fxo");
	mixModeFileNames.Set(L"Screen",		L"mix\\mix_screen.fxo");
	mixModeFileNames.Set(L"SoftLight",	L"mix\\mix_soft_light.fxo");
	mixModeFileNames.Set(L"VividLight",	L"mix\\mix_vivid_light.fxo");

	return true;
}
