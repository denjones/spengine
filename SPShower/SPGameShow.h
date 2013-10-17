#pragma once

using namespace SPEngine;

class SPGameShow : public SPGame
{
	SPAnimatedTexturePtr loading;
public:
	SPGameShow(HINSTANCE hInstance): SPGame(hInstance){}
	virtual ~SPGameShow(void);

	bool Initialize();
	bool Load();
	bool UnloadContent();

	bool SaveAsFile(SPString path);
	bool LoadFromFile(SPString path);

	bool DrawWhileLoading(float timeDelta);
	bool Draw(float timeDelta);

	bool SaveSystemData();
	bool LoadSystemData();
};

