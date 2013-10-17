#pragma once
#include "SUIComponent.h"


class SUIBlankComponent :
	public SUIComponent
{
public:
	SUIBlankComponent(void);
	virtual ~SUIBlankComponent(void);

	virtual bool PreDraw();
	virtual bool Draw(float timeDelta);
	virtual bool PostDraw();
	bool Update(float timeDelta);
	virtual bool Skip();
	virtual bool HandleEvent(SUIEventPtr e);

	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

