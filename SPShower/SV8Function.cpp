#include "StdAfx.h"
#include "SV8Function.h"
#include "SUIEffectManager.h"

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

		effect = SUIEffectManager::GetSingleton().GetEffect(type);

		if (!effect)
		{
			return NULL;
		}

		effect->SetTime(0);
		effect->SetLevel(5);
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
			SPString texName = SPV8ScriptEngine::StringToSPString(val->ToString());
			effect->SetEffectTexture(SPTextureManager::GetSingleton().GetTexture(texName));
		}
		else if (name == L"time")
		{
			effect->SetTime(val->NumberValue());
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
			tex = SPTextureManager::GetSingleton().GetAnime(src, row, col, fps);
		}
		else
		{
			tex = SPTextureManager::GetSingleton().GetTexture(src);
		}

		return tex;
	}

	return NULL;
}

void SV8Function::RegisterFont( const FunctionCallbackInfo<Value>& args )
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();
	HandleScope handleScope(isolate);

	if(args.Length() == 0)
	{
		isolate->ThrowException(Exception::TypeError(
			SPV8ScriptEngine::SPStringToString(L"Invalid Argument")));
		return;
	}

	Handle<Object> argObj = Handle<Object>::Cast(args[0]);

	if (HasProperty(L"file", argObj))
	{
		SPString fileName = SPV8ScriptEngine::StringToSPString(GetProperty(L"file", argObj)->ToString());
		SPFontManager::GetSingleton().AddExtendedFont(fileName);
	}
}



