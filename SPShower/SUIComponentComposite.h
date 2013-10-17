#pragma once
#include "SUIComponent.h"

using namespace SPEngine;

class SUIComponentComposite :
	public SPComposite<SUIComponent>
{
public:
	SUIComponentComposite(void);
	virtual ~SUIComponentComposite(void);

	virtual bool Update(float timeDelta);
	virtual bool PreDraw();
	virtual bool Draw(float timeDelta);
	virtual bool PostDraw();
	virtual bool AddChild(SUIComponentPtr newChild);
	virtual bool Load();
	virtual bool Unload();
	virtual bool Reload();
	virtual bool Skip();
	virtual bool HandleEvent(SUIEventPtr e);
	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

typedef SPPointer<SUIComponentComposite> SUIComponentCompositePtr;