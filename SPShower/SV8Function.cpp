#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIEffectManager.h"
#include "SUIVideoManager.h"
#include "SUIParticleSystemManager.h"
#include "SUITrackManager.h"

SV8Function::SV8Function(void)
{
}


SV8Function::~SV8Function(void)
{
}

bool SV8Function::HasProperty( SPString propertyName, Handle<Object> obj )
{
	Handle<String> nameStr = SPV8ScriptEngine::SPStringToString(propertyName);
	return obj->HasRealNamedProperty(nameStr);
}

Handle<Value> SV8Function::GetProperty( SPString propertyName, Handle<Object> obj )
{
	Handle<String> nameStr = SPV8ScriptEngine::SPStringToString(propertyName);
	return obj->GetRealNamedProperty(nameStr);
}

SUIEffectPtr SV8Function::GetEffectFromObj( Handle<Object> argObj, SUIEffectPtr effect )
{
	if (SV8Function::HasProperty(L"type", argObj))
	{
		SPString type = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"type", argObj)->ToString());

		effect = SUIEffectManager::GetSingleton()->GetEffect(type);

		if (!effect)
		{
			return NULL;
		}

		effect->SetTime(0);
		effect->SetLevel(5);
	} else {
		return NULL;
	}

	if (!effect)
	{
		return NULL;
	}

	Handle<Array> names = argObj->GetOwnPropertyNames();

	for (int i = 0; i < names->Length(); i++)
	{
		Handle<String> nameStr = names->Get(i)->ToString();
		SPString name = SPV8ScriptEngine::StringToSPString(nameStr);
		Handle<Value> val = argObj->Get(nameStr);

		if (name == L"level")
		{
			effect->SetLevel(val->NumberValue());
		}
		else if (name == L"texture")
		{
			SPTexturePtr tex;
			if(val->IsString())
			{
				SPString texName = SPV8ScriptEngine::StringToSPString(val->ToString());
				tex = SPTextureManager::GetSingleton()->GetTexture(texName);
			}
			else if(val->IsObject())
			{
				tex = SV8Function::GetTextureFromObj(val->ToObject());
			}
			effect->SetEffectTexture(tex);
		}
		else if (name == L"time" && val->IsNumber())
		{
			float time = val->NumberValue();
			effect->SetTime(time);
		}
		else if (name == L"canSkip")
		{
			effect->SetCanSkip(val->BooleanValue());
		}
		else if (name == L"replay")
		{
			SPString style = SPV8ScriptEngine::StringToSPString(val->ToString());

			if (SPStringHelper::EqualsIgnoreCase(style, L"SlowIn") || 
				SPStringHelper::EqualsIgnoreCase(style, L"FastOut"))
			{
				effect->SetType(SUITransition::SlowIn);
			}
			else if (SPStringHelper::EqualsIgnoreCase(style, L"SlowOut") || 
				SPStringHelper::EqualsIgnoreCase(style, L"FastIn"))
			{
				effect->SetType(SUITransition::SlowOut);
			}
			else if (SPStringHelper::EqualsIgnoreCase(style, L"SlowInOut"))
			{
				effect->SetType(SUITransition::SlowInOut);
			}
			else if (SPStringHelper::EqualsIgnoreCase(style, L"FastInOut"))
			{
				effect->SetType(SUITransition::FastInOut);
			}
			else
			{
				effect->SetType(SUITransition::Normal);
			}
		}
		else if (name == L"control")
		{
			SPString valString = SPV8ScriptEngine::StringToSPString(val->ToString());

			if (SPStringHelper::EqualsIgnoreCase(valString, L"play"))
			{
				effect->Play();
			}
			else if (SPStringHelper::EqualsIgnoreCase(valString, L"stop"))
			{
				effect->Stop();
			}
			else if (SPStringHelper::EqualsIgnoreCase(valString, L"skip"))
			{
				effect->Skip();
			}
		}
		else if (name == L"type")
		{
			continue;
		}
		else
		{
			effect->SetFloat(SPStringHelper::ToString(name), val->NumberValue());
		}
	}

	return effect;
}

SPEngine::SPTexturePtr SV8Function::GetTextureFromObj( Handle<Object> argObj )
{
	if (SV8Function::HasProperty(L"src", argObj))
	{
		SPString src = SPV8ScriptEngine::StringToSPString(
			SV8Function::GetProperty(L"src", argObj)->ToString());

		bool isAnime = false;

		int row = 1;
		int col = 1;
		int fps = 14;

		if (SV8Function::HasProperty(L"row", argObj))
		{
			isAnime = true;
			row = SV8Function::GetProperty(L"row", argObj)->Int32Value();
		}

		if (SV8Function::HasProperty(L"col", argObj))
		{
			isAnime = true;
			col = SV8Function::GetProperty(L"col", argObj)->Int32Value();
		}

		if (SV8Function::HasProperty(L"fps", argObj))
		{
			isAnime = true;
			fps = SV8Function::GetProperty(L"fps", argObj)->Int32Value();
		}

		SPTexturePtr tex;

		if (isAnime)
		{
			tex = SPTextureManager::GetSingleton()->GetAnime(src, row, col, fps);
		}
		else
		{
			tex = SPTextureManager::GetSingleton()->GetTexture(src);
		}

		return tex;
	}
	else if (SV8Function::HasProperty(L"video", argObj))
	{
		Handle<Value> videoArg = SV8Function::GetProperty(L"video", argObj);

		if (videoArg->IsString())
		{
			return SPTextureManager::GetSingleton()->GetVideo(
				SPV8ScriptEngine::StringToSPString(videoArg->ToString()));
		}
		else if(videoArg->IsObject())
		{
			Handle<Object> videoObj = videoArg->ToObject();

			if (videoObj->InternalFieldCount() != 1)
			{
				videoObj = SUIVideoManager::GetSingleton()->CreateVideo(videoObj);
			}
			
			Handle<External> field = Handle<External>::Cast(videoObj->GetInternalField(0));
			SUIVideoHandle handle = (SUIVideoHandle)field->Value();
			if (handle == NULL)
			{
				return NULL;
			}

			return SUIVideoManager::GetSingleton()->GetVideoTexture(handle);
		}
	}
	else if (SV8Function::HasProperty(L"particleSystem", argObj))
	{

		Handle<Value> psArg = SV8Function::GetProperty(L"particleSystem", argObj);

		if (psArg->IsString())
		{
			return SPTextureManager::GetSingleton()->GetParticleSystem(
				SPV8ScriptEngine::StringToSPString(psArg->ToString()));
		}
		else if(psArg->IsObject())
		{
			Handle<Object> psObj = psArg->ToObject();

			if (psObj->InternalFieldCount() != 1)
			{
				psObj = SUIParticleSystemManager::GetSingleton()->CreateParticleSystem(psObj);
			}

			Handle<External> field = Handle<External>::Cast(psObj->GetInternalField(0));
			SUIParticleSystemHandle handle = (SUIParticleSystemHandle)field->Value();
			if (handle == NULL)
			{
				return NULL;
			}

			return SUIParticleSystemManager::GetSingleton()->GetParticleSystemTexture(handle);
		}
	}

	return NULL;
}

Handle<Value> SV8Function::GetObjFromTexture( SPTexturePtr texture )
{
	SPString texType = texture->GetTextureType();

	if (SPStringHelper::EqualsIgnoreCase(texType, L"Texture"))
	{
		Handle<Object> texObj = Object::New();
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"src"), SPV8ScriptEngine::SPStringToString(texture->GetPath()));
		return texObj;
	}
	else if (SPStringHelper::EqualsIgnoreCase(texType, L"AnimatedTexture"))
	{
		Handle<Object> texObj = Object::New();
		SPAnimatedTexturePtr animatedTexture = (SPAnimatedTexturePtr)texture;
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"src"), SPV8ScriptEngine::SPStringToString(animatedTexture->GetPath()));
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"col"), Integer::New(animatedTexture->GetColumn()));
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"row"), Integer::New(animatedTexture->GetRow()));
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"fps"), Integer::New(animatedTexture->GetFPS()));
		return texObj;
	}
	else if (SPStringHelper::EqualsIgnoreCase(texType, L"VideoTexture"))
	{
		Handle<Object> texObj = Object::New();
		SPVideoTexturePtr videoTexture = (SPVideoTexturePtr)texture;
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"video"), SUIVideoManager::GetSingleton()->GetVideo(videoTexture->GetVideo().GetHandle()));
		return texObj;
	}
	else if (SPStringHelper::EqualsIgnoreCase(texType, L"ParticleSystemTexture"))
	{
		Handle<Object> texObj = Object::New();
		SPParticleSystemTexturePtr particleSystemTexture = (SPParticleSystemTexturePtr)texture;
		texObj->Set(SPV8ScriptEngine::SPStringToString(L"particleSystem"), SUIParticleSystemManager::GetSingleton()->GetParticleSystem(particleSystemTexture->GetParticleSystem().GetHandle()));
		return texObj;
	}
	return Undefined();
}

Handle<Value> SV8Function::GetObjFromEffect( SUIEffectPtr effect )
{
	Handle<Object> effectObj = Object::New();
	SPString effectType = effect->GetCore()->GetName();
	Handle<Value> texObj = GetObjFromTexture(effect->GetEffectTexture());
	float time = effect->GetTime();
	bool canSkip = effect->CanSkip();
	SUITransition::TransitionType type = effect->GetType();
	SPString replay;
	switch(type)
	{
	case SUITransition::SlowIn:
		replay = L"SlowIn";
		break;
	case SUITransition::SlowOut:
		replay = L"SlowOut";
		break;
	case SUITransition::SlowInOut:
		replay = L"SlowInOut";
		break;
	case SUITransition::FastInOut:
		replay = L"FastInOut";
		break;
	default:
		replay = L"Normal";
	}

	effectObj->Set(SPV8ScriptEngine::SPStringToString(L"type"), SPV8ScriptEngine::SPStringToString(effectType));
	effectObj->Set(SPV8ScriptEngine::SPStringToString(L"texture"), texObj);
	effectObj->Set(SPV8ScriptEngine::SPStringToString(L"time"), Number::New(time));
	effectObj->Set(SPV8ScriptEngine::SPStringToString(L"canSkip"), Boolean::New(canSkip));
	effectObj->Set(SPV8ScriptEngine::SPStringToString(L"replay"), SPV8ScriptEngine::SPStringToString(replay));
	
	SPEffect::ValueMap values = effect->GetValues();
	
	SPStringMapIterator<SPEffect::ValuePairPtr> iter(&values);

	for(iter.First(); !iter.IsDone(); iter.Next())
	{
		SPString name = SPStringHelper::ToWString(iter.CurrentIndex());
		SPEffect::ValuePairPtr valuePair = iter.CurrentItem();
		if(valuePair->length == sizeof(float))
		{
			float value = *(float*)(valuePair->pData);
			effectObj->Set(SPV8ScriptEngine::SPStringToString(name), Number::New(value));
		}
		
	}

	return effectObj;
}














