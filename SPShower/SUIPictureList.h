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

	void Draw(float timeDelta);
	void SetBaseImage(SPTexturePtr base);
	void SetMixImage(SUIMixImage image);
	SPTexturePtr GetTarget();
	void SetName(SPString setName);
	SPString GetName();
	void Load();
	void Unload();
	void Reload();
	void SaveBaseAsFile(SPString path);

	int GetHeight();
	int GetWidth();

	SPString SaveAsString();
	void LoadFromString(SPString stringStream);
};

typedef SPPointer<SUIPictureList> SUIPictureListPtr;

