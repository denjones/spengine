#include "StdAfx.h"
#include "SPGameShow.h"
#include "SUIManager.h"
#include "SUIEffectManager.h"
#include "SUIMixModeManager.h"
#include "SUITransformationManager.h"
#include "SUIPictureManager.h"
#include "SScriptHelper.h"
#include "SUIParticleSystemManager.h"
#include "SV8ScriptManager.h"
#include "SUITrackManager.h"
#include "SUIVideoManager.h"
#include "SV8FunctionManager.h"
#include "SV8Function.h"

#pragma warning(disable:4244)

SPGameShow::~SPGameShow(void)
{
	//if (SPV8ScriptEngine::GetSingleton())
	//{
	//	SPV8ScriptEngine::GetSingleton()->StopThread();
	//}
}

bool SPGameShow::Load()
{
	//SPScreenManager::GetSingleton()->CreateScreen(L"shower", new SScreen());
	//SPScreenManager::GetSingleton()->Register(L"shower");
	loading = SPTextureManager::GetSingleton()->GetAnime(L"data/images/loading.png", 2, 4, 20);

	//LoadSystemData();

	return SPGame::Load();
}

bool SPGameShow::UnloadContent()
{
	//SaveSystemData();

	return SPGame::UnloadContent();
}

bool SPGameShow::Initialize()
{	
	
	SPComponentManager::GetSingleton()->RegisterComponent(L"STrack", SUITrackManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"SVideo", SUIVideoManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"SParticleSystem", SUIParticleSystemManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"SUI", SUIManager::GetSingleton());		
	SPComponentManager::GetSingleton()->RegisterComponent(L"SEffect", SUIEffectManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"SMixMode", SUIMixModeManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"STransformation", SUITransformationManager::GetSingleton());
	SPComponentManager::GetSingleton()->RegisterComponent(L"SScript", SV8ScriptManager::GetSingleton());

	SV8ScriptManager::GetSingleton()->Enable();
	SUIManager::GetSingleton()->Enable();
	
	return true;	
}

bool SPGameShow::SaveAsFile( SPString path , SPString screens)
{
	SPFileHelper::CreatePath(SPFileHelper::GetUpperPath(path));

	HANDLE handle = CreateFile(path.c_str(),
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	SPString result = SPV8ScriptEngine::StringToSPString(SPV8ScriptEngine::ToJson(SaveAsObj(screens)));

	string shortResult = SPStringHelper::WStringToUTF8String(result);

	DWORD numOfByteWritten;

	WriteFile(handle, shortResult.c_str(), shortResult.size(), &numOfByteWritten, NULL);

	CloseHandle(handle);

	return true;
}

bool SPGameShow::LoadFromFile( SPString path )
{
	HANDLE handle = CreateFile(path.c_str(),
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	ULARGE_INTEGER fileLength = {0};
	fileLength.LowPart = GetFileSize(handle, &fileLength.HighPart);

	char* pBuffer = new char[fileLength.QuadPart + 1];

	DWORD numOfByteRead;

	ReadFile(handle, pBuffer, fileLength.QuadPart, &numOfByteRead, NULL);
	pBuffer[fileLength.QuadPart] = 0;

	CloseHandle(handle);

	SPString result = SPStringHelper::UTF8CStringToWString(pBuffer);

	delete [] pBuffer;
	pBuffer = NULL;

	Handle<Object> obj = SPV8ScriptEngine::JsonParse(SPV8ScriptEngine::SPStringToString(result));

	LoadFromObj(obj);

	return true;
}

void SPGameShow::SaveSystemData(SPString fileName)
{
	HANDLE handle = CreateFile(fileName.c_str(),
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		SPLogHelper::WriteLog(L"Failed to create file: " + fileName);
		return;
	}

	Handle<Object> systemObj = Object::New();
	systemObj->Set(SPV8ScriptEngine::SPStringToString(L"read"), SV8ScriptManager::GetSingleton()->SaveReadAsObj());
	systemObj->Set(SPV8ScriptEngine::SPStringToString(L"sysVar"), SV8ScriptManager::GetSingleton()->GetSystemVariable());

	SPString result = SPV8ScriptEngine::StringToSPString(SPV8ScriptEngine::ToJson(systemObj));

	string shortResult = SPStringHelper::WStringToUTF8String(result);

	DWORD numOfByteWritten;

	WriteFile(handle, shortResult.c_str(), shortResult.size(), &numOfByteWritten, NULL);

	CloseHandle(handle);
}

void SPGameShow::LoadSystemData(SPString fileName)
{
	HANDLE handle = CreateFile(fileName.c_str(),
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		SPLogHelper::WriteLog(L"Failed to open file: " + fileName);
		return;
	}

	ULARGE_INTEGER fileLength = {0};
	fileLength.LowPart = GetFileSize(handle, &fileLength.HighPart);

	char* pBuffer = new char[fileLength.QuadPart + 1];

	DWORD numOfByteRead;

	ReadFile(handle, pBuffer, fileLength.QuadPart, &numOfByteRead, NULL);
	pBuffer[fileLength.QuadPart] = 0;

	CloseHandle(handle);

	SPString result = SPStringHelper::UTF8CStringToWString(pBuffer);

	delete [] pBuffer;
	pBuffer = NULL;

	Handle<Object> obj = SPV8ScriptEngine::JsonParse(SPV8ScriptEngine::SPStringToString(result));
	if (obj.IsEmpty())
	{
		SPLogHelper::WriteLog(L"[SScript] Failed to load system data.");
		return;
	}
	Handle<Object> readObj = Handle<Object>::Cast(obj->Get(SPV8ScriptEngine::SPStringToString(L"read")));
	Handle<Object> sysVar = Handle<Object>::Cast(obj->Get(SPV8ScriptEngine::SPStringToString(L"sysVar")));
	
	SV8ScriptManager::GetSingleton()->LoadReadFromObj(readObj);
	SPV8ScriptEngine::CoverObject(SV8ScriptManager::GetSingleton()->GetSystemVariable(), sysVar);
}

bool SPGameShow::DrawWhileLoading( float timeDelta )
{
	SPSpriteManager::GetSingleton()->RenderOnScreen(SPTextureManager::GetSingleton()->GetBlankWhiteTexture(), NULL,
		SPRectangle(0,0,SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth,
		SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight), SPColor::Black, 1, NULL);

	SPSpriteManager::GetSingleton()->Render(loading, NULL, 
		SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth - loading->GetWidth() - 20,
		SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight- loading->GetHeight() - 20, SPColor::White, 0, NULL);

	return SPGame::DrawWhileLoading(timeDelta);
}

bool SPGameShow::Draw( float timeDelta )
{
	SPSpriteManager::GetSingleton()->RenderOnScreen(SPTextureManager::GetSingleton()->GetBlankWhiteTexture(), NULL,
		SPRectangle(0,0,SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth,
		SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight), SPColor::Black, 1, NULL);

	return SPGame::Draw(timeDelta);
}

Handle<Object> SPGameShow::SaveAsObj()
{
	Handle<Object> result = Object::New();
	result->Set(SPV8ScriptEngine::SPStringToString(L"SUI"), SUIManager::GetSingleton()->SaveAsObj());
	result->Set(SPV8ScriptEngine::SPStringToString(L"SScript"), SV8ScriptManager::GetSingleton()->SaveAsObj());
	result->Set(SPV8ScriptEngine::SPStringToString(L"SSound"), SUITrackManager::GetSingleton()->SaveAsObj());
	return result;
}

Handle<Object> SPGameShow::SaveAsObj(SPString screens)
{
	Handle<Object> result = Object::New();
	result->Set(SPV8ScriptEngine::SPStringToString(L"SUI"), SUIManager::GetSingleton()->SaveScreenAsObj(screens));
	result->Set(SPV8ScriptEngine::SPStringToString(L"SScript"), SV8ScriptManager::GetSingleton()->SaveAsObj());
	result->Set(SPV8ScriptEngine::SPStringToString(L"SSound"), SUITrackManager::GetSingleton()->SaveAsObj());
	return result;
}

void SPGameShow::LoadFromObj( Handle<Object> obj )
{
	LockDrawing();

	if(SV8Function::HasProperty(L"SScript", obj))
	{
		SV8ScriptManager::GetSingleton()->LoadFromObj(Handle<Object>::Cast(SV8Function::GetProperty(L"SScript", obj)));
	}

	if(SV8Function::HasProperty(L"SUI", obj))
	{
		SUIManager::GetSingleton()->LoadFromObj(Handle<Object>::Cast(SV8Function::GetProperty(L"SUI", obj)));
	}

	if(SV8Function::HasProperty(L"SSound", obj))
	{
		SUITrackManager::GetSingleton()->LoadFromObj(Handle<Object>::Cast(SV8Function::GetProperty(L"SSound", obj)));
	}

	UnlockDrawing();
}

void SPGameShow::OnExit()
{
	SV8ScriptManager::GetSingleton()->Exit();
}
