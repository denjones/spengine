#pragma once

using namespace SPEngine;

typedef SPSoundTrack* SUISoundTrackHandle;

class SUITrackManager : 
	public SPComponent,
	public SPSingleton<SUITrackManager>
{
	map<SUISoundTrackHandle, Handle<Object>> trackHandleManager;
	SPPointer<Persistent<ObjectTemplate>> trackTempl;

public:
	SUITrackManager(void);
	virtual ~SUITrackManager(void);

	Handle<Object> GetTrack(SUISoundTrackHandle handle);
	Handle<Object> CreateTrack(Handle<Object> argObj);
	Handle<ObjectTemplate> GetTrackTemplate();

	virtual void Initialize();
};



