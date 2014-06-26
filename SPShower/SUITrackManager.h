#pragma once
#include "ISV8Serializable.h"

using namespace SPEngine;

typedef SPSoundTrack* SUISoundTrackHandle;

class SUITrackManager : 
	public SPComponent,
	public ISV8Serializable,
	public SPSingleton<SUITrackManager>
{
	map<SUISoundTrackHandle, SPPointer<Persistent<Object>>> trackHandleManager;
	SPPointer<Persistent<ObjectTemplate>> trackTempl;

public:
	SUITrackManager(void);
	virtual ~SUITrackManager(void);

	Handle<Object> GetTrack(SUISoundTrackHandle handle);
	Handle<Object> CreateTrack(Handle<Object> argObj);
	Handle<ObjectTemplate> GetTrackTemplate();

	virtual void Initialize();

	virtual Handle<Object> SaveAsObj();
	virtual void LoadFromObj( Handle<Object> obj );
};



