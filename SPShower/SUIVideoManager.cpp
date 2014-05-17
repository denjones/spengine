#include "StdAfx.h"
#include "SUIVideoManager.h"
#include "SV8TemplVideo.h"
#include "SV8Function.h"


SUIVideoManager::SUIVideoManager(void)
{
}


SUIVideoManager::~SUIVideoManager(void)
{
	if (videoTempl)
	{
		videoTempl->ClearAndLeak();
		videoTempl = NULL;
	}
}

//SPEngine::SPVideoPtr SUIVideoManager::GetVideo( SPString name )
//{
//	if (videoPaths.IsSet(name))
//	{
//		return SPVideoManager::GetSingleton()->GetVideo(videoPaths[name]);
//	}
//
//	return NULL;
//}
//
//bool SUIVideoManager::SetVideoPath( SPString name, SPString path )
//{
//	videoPaths.Set(name, path);
//	return true;
//}
//
//SPEngine::SPVideoTexturePtr SUIVideoManager::GetVideoTexture( SPString name )
//{
//	if (videoPaths.IsSet(name))
//	{
//		return SPTextureManager::GetSingleton()->GetVideo(videoPaths[name]);
//	}
//
//	return NULL;
//}

SPEngine::SPVideoTexturePtr SUIVideoManager::GetVideoTexture( SUIVideoHandle handle )
{
	return SPTextureManager::GetSingleton()->GetVideo(videoIdManager[handle]);
}

Handle<Object> SUIVideoManager::GetVideo( SUIVideoHandle handle )
{
	return videoHandleManager[handle];
}

Handle<Object> SUIVideoManager::CreateVideo( Handle<Object> argObj )
{
	SPVideoPtr video;

	bool isNameSet = false;
	SPString id = L"";

	if (SV8Function::HasProperty(L"id", argObj))
	{
		id = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"id", argObj)->ToString());
		video = SPVideoManager::GetSingleton()->GetVideo(id);

		if (!video)
		{
			SPVideoManager::GetSingleton()->CreateVideo(id);
			video =  SPVideoManager::GetSingleton()->GetVideo(id);
		}
	}
	else
	{
		id = SPStringHelper::ToWString(SPRandomHelper::NextInt(100000000));
		while(SPVideoManager::GetSingleton()->GetVideo(id))
		{
			id = SPStringHelper::ToWString(SPRandomHelper::NextInt(100000000));
		}
		SPVideoManager::GetSingleton()->CreateVideo(id);
		video = SPVideoManager::GetSingleton()->GetVideo(id);
	}

	SUIVideoHandle handle = video.GetHandle();

	Local<Object> obj = Handle<Object>();

	Handle<ObjectTemplate> handleTempl = GetVideoTemplate();
	obj = handleTempl->NewInstance();

	if(!obj.IsEmpty())
	{
		obj->SetInternalField(0, External::New(video.GetHandle()));

		const Local<Array> props = argObj->GetPropertyNames();
		const uint32_t length = props->Length();
		for (uint32_t i = 0; i < length; i++)
		{
			const Local<Value> key = props->Get(i);
			const Local<Value> value = argObj->Get(key);

			obj->Set(key, value);
		}
	}

	videoHandleManager[handle] = obj;
	videoIdManager[handle] = id;

	return obj;
}

Handle<ObjectTemplate> SUIVideoManager::GetVideoTemplate()
{
	return Handle<ObjectTemplate>::New(SPV8ScriptEngine::GetSingleton()->GetIsolate(), (*videoTempl));
}

void SUIVideoManager::Initialize()
{
	//
	// Enter
	//

	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();
	Locker locker(isolate); 
	Isolate::Scope isolateScope(isolate);
	HandleScope handleScope(isolate);
	Handle<Context> context = SPV8ScriptEngine::GetSingleton()->GetContext();
	Context::Scope contextScope(context);

	videoTempl = new Persistent<ObjectTemplate>(SPV8ScriptEngine::GetSingleton()->GetIsolate(), 
		SV8TemplVideo::GetTemplate());
}
