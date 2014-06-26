#pragma once

using namespace SPEngine;

typedef SPVideo* SUIVideoHandle;

class SUIVideoManager : 
	public SPComponent,
	public SPSingleton<SUIVideoManager>
{
	SPWStringMap<SPString> videoPaths;
	map<SUIVideoHandle, SPPointer<Persistent<Object>>> videoHandleManager;
	map<SUIVideoHandle, SPString> videoIdManager;
	SPPointer<Persistent<ObjectTemplate>> videoTempl;

public:
	SUIVideoManager(void);
	virtual ~SUIVideoManager(void);

	//SPVideoPtr GetVideo(SPString name);
	//SPVideoTexturePtr GetVideoTexture(SPString name);
	//bool SetVideoPath(SPString name, SPString path);

	SPVideoTexturePtr GetVideoTexture(SUIVideoHandle handle);
	Handle<Object> GetVideo(SUIVideoHandle handle);
	Handle<Object> CreateVideo(Handle<Object> argObj);
	Handle<ObjectTemplate> GetVideoTemplate();

	virtual void Initialize();
};

