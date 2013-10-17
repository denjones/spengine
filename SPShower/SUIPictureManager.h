#pragma once
#include "SUIPictureList.h"

using namespace SPEngine;

class SUIPictureManager:
	public SPSingleton<SUIPictureManager>
{
	SPWStringMap<SUIPictureListPtr> pictures;
	SUIPictureListPtr currentPicture;

public:
	SUIPictureManager(void);
	virtual ~SUIPictureManager(void);

	SUIPictureListPtr GetPicture(SPString name);
	bool SetPicture(SPString setName, SUIPictureListPtr setPicture);
	bool IsPictureVaild(SPString name);
	bool SetCurrentPicture(SUIPictureListPtr setPicture);
	SUIPictureListPtr GetCurrentPicture();
	virtual bool LoadFromString(SPString stringStream);
	virtual SPString SaveAsString();
};

