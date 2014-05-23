#pragma once
#include "ISV8Serializable.h"

using namespace SPEngine;

class SPGameShow : 
	public SPGame,
	public ISV8Serializable
{
	SPAnimatedTexturePtr loading;
public:
	SPGameShow(HINSTANCE hInstance): SPGame(hInstance){}
	virtual ~SPGameShow(void);

	bool Initialize();
	bool Load();
	bool UnloadContent();

	bool SaveAsFile(SPString path, SPString screens);
	bool LoadFromFile(SPString path);

	bool DrawWhileLoading(float timeDelta);
	bool Draw(float timeDelta);

	bool SaveSystemData();
	bool LoadSystemData();

	virtual Handle<Object> SaveAsObj();
	virtual Handle<Object> SaveAsObj(SPString screens);
	virtual void LoadFromObj( Handle<Object> obj );

	virtual void OnExit();

};

