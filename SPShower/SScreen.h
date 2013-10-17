#pragma once
#include "SUIComponentComposite.h"

using namespace SPEngine;

class SScreen : public SPBaseScreen
{
	SUIComponentCompositePtr sampleComponent;
	SPString name;


	SUIEffectPtr LoadSetEffect( SUIEffectPtr effect );


public:
	SScreen(void);
	~SScreen(void);

	bool Load();

	bool Unload();
	bool Initialize();
	bool Update(float timeDelta);
	bool Draw(float timeDelta);
};

