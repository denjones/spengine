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

	LoadSystemData();

	return SPGame::Load();
}

bool SPGameShow::UnloadContent()
{
	SaveSystemData();

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

bool SPGameShow::SaveAsFile( SPString path )
{
	SPFileHelper::CreatePath(SPFileHelper::GetUpperPath(path));

	HANDLE handle = CreateFile(path.c_str(),
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		return false;
	}
//
//	SPString result = L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
//
//	result += SPStringHelper::XMLSurroundWith(
//		SPVideoManager::GetSingleton()->SaveAsString()
//		+ SPFontManager::GetSingleton()->SaveAsString()
//		+ SPSoundManager::GetSingleton()->SaveAsString()
////		+ SScriptManager::GetSingleton()->SaveAsString()
//		//+ SUIParticleSystemManager::GetSingleton()->SaveAsString()
//		+ SUIPictureManager::GetSingleton()->SaveAsString()		
//		+ SUIManager::GetSingleton()->SaveAsString(),L"SaveData");
//
	SPString result = SPV8ScriptEngine::StringToSPString(SPV8ScriptEngine::ToJson(SaveAsObj()));

	string shortResult = SPStringHelper::WStringToUTF8String(result);

	DWORD numOfByteWritten;

	WriteFile(handle, shortResult.c_str(), shortResult.size(), &numOfByteWritten, NULL);

	CloseHandle(handle);

	return true;
}

bool SPGameShow::LoadFromFile( SPString path )
{
	//HANDLE handle = CreateFile(path.c_str(),
	//	GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);

	//if (handle == INVALID_HANDLE_VALUE)
	//{
	//	return false;
	//}

	//ULARGE_INTEGER fileLength = {0};
	//fileLength.LowPart = GetFileSize(handle, &fileLength.HighPart);

	//char* pBuffer = new char[fileLength.QuadPart];

	//DWORD numOfByteRead;

	//ReadFile(handle, pBuffer, fileLength.QuadPart, &numOfByteRead, NULL);

	//CloseHandle(handle);

	//SPString result = SPStringHelper::UTF8CStringToWString(pBuffer);

	//delete [] pBuffer;
	//pBuffer = NULL;

	//SPVideoManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SPVideoManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SPVideoManager");

	//SPFontManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SPFontManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SPFontManager");

	//SPSoundManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SPSoundManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SPSoundManager");

	//SScriptManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SScriptManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SScriptManager");

	////SUIParticleSystemManager::GetSingleton()->LoadFromString(
	////	SPStringHelper::XMLExcludeFrom(result, L"SUIParticleSys"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SUIParticleSys");

	//SUIPictureManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SUIPictureManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SUIPictureManager");

	//SUIManager::GetSingleton()->LoadFromString(
	//	SPStringHelper::XMLExcludeFrom(result, L"SUIManager"));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SUIManager");

	return true;
}

bool SPGameShow::SaveSystemData()
{
	//SPString path = L"system.dat";

	//HANDLE handle = CreateFile(path.c_str(),
	//	GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);

	//SPString result = L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";

	//result += SPStringHelper::XMLSurroundWith(	SScriptHelper::VariablesToString(
	//	SScriptManager::GetSingleton()->GetSystemVariables()), L"SysData");

	//result += SScriptManager::GetSingleton()->ReadCommandsToString() ;

	//string shortResult = SPStringHelper::WStringToUTF8String(result);

	//DWORD numOfByteWritten;

	//WriteFile(handle, shortResult.c_str(), shortResult.size(), &numOfByteWritten, NULL);

	//CloseHandle(handle);

	return true;
}

bool SPGameShow::LoadSystemData()
{
	//SPString path = L"system.dat";

	//HANDLE handle = CreateFile(path.c_str(),
	//	GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);

	//if (!handle)
	//{
	//	return false;
	//}

	//ULARGE_INTEGER fileLength = {0};
	//fileLength.LowPart = GetFileSize(handle, &fileLength.HighPart);

	//char* pBuffer = new char[fileLength.QuadPart];

	//DWORD numOfByteRead;

	//ReadFile(handle, pBuffer, fileLength.QuadPart, &numOfByteRead, NULL);

	//CloseHandle(handle);

	//SPString result = SPStringHelper::UTF8CStringToWString(pBuffer);

	//SScriptManager::GetSingleton()->SetSystemVariables(
	//	SScriptHelper::StringToVariables(
	//	SPStringHelper::XMLExcludeFrom(result, L"SysData")));

	//result = SPStringHelper::XMLRemoveFirst(result, L"SysData");

	//SScriptManager::GetSingleton()->ReadCommandsFromString(result);

	//delete [] pBuffer;
	//pBuffer = NULL;

	return true;
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
	result->Set(SPV8ScriptEngine::SPStringToString(L"SV8Func"), SV8FunctionManager::GetSingleton()->SaveAsObj());
	return result;
}

void SPGameShow::LoadFromObj( Handle<Object> obj )
{
	throw std::exception("The method or operation is not implemented.");
}

void SPGameShow::OnExit()
{
	SV8ScriptManager::GetSingleton()->Exit();
}
