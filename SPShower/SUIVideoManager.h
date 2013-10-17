#pragma once

using namespace SPEngine;

class SUIVideoManager : 
	public SPComponent,
	public SPSingleton<SUIVideoManager>
{
	SPWStringMap<SPString> videoPaths;

public:
	SUIVideoManager(void);
	virtual ~SUIVideoManager(void);

	SPVideoPtr GetVideo(SPString name);
	SPVideoTexturePtr GetVideoTexture(SPString name);
	bool SetVideoPath(SPString name, SPString path);

};

