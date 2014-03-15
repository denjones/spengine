#pragma once
#include "SUIMixImage.h"

using namespace SPEngine;

class SUIPictureList : 
	public ISPDrawable,
	public ISPLoadable
{
	typedef list<SUIMixImage> MixImages;
	typedef MixImages::iterator ImageIterator;

	MixImages	mixImages;
	SPTexturePtr baseImage;
	SPTexturePtr target;
	SPString	name;

public:
	SUIPictureList(void);
	virtual ~SUIPictureList(void);

	bool Draw(float timeDelta);
	bool SetBaseImage(SPTexturePtr base);
	bool SetMixImage(SUIMixImage image);
	SPTexturePtr GetTarget();
	bool SetName(SPString setName);
	SPString GetName();
	bool Load();
	bool Unload();
	bool Reload();
	bool SaveBaseAsFile(SPString path);

	int GetHeight();
	int GetWidth();

	SPString SaveAsString();
	bool LoadFromString(SPString stringStream);
};

typedef SPPointer<SUIPictureList> SUIPictureListPtr;

