#include "StdAfx.h"
#include "SPEffectCore.h"
#include "SPLogHelper.h"
#include "SPFileManager.h"
#include "SPDevice.h"
#include "SPStringHelper.h"
#include "SPGameManager.h"

namespace SPEngine
{
	SPEffectCore::SPEffectCore(void) :
		effect(NULL)
	{
	}

	SPEffectCore::SPEffectCore( SPString path ) :
		effect(NULL)
	{
		Load(path);
	}

	SPEffectCore::~SPEffectCore(void)
	{
	}

	bool SPEffectCore::Load( SPString path )
	{
		name = path;

		SPFilePtr file = SPFileManager::GetSingleton()->OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPEffect] WARNING: Failed to open effect file: " + path);
			return false;
		}

		ID3DXBuffer* errorBuffer = NULL;
		LONGLONG length = file->GetFileLength();
		char* pData = new char[(UINT)length];

		if(!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPEffect] WARNING: Failed to read effect file: " + path);
			return false;
		}

		// Create effect.
		HRESULT hr = D3DXCreateEffect(
			SPDevice::GetSingleton()->GetD3DDevice(), 
			pData, (UINT)length, 0, 0, D3DXSHADER_DEBUG, 0, 
			&effect, &errorBuffer);

		delete [] pData;
		pData = NULL;
		SPFileManager::GetSingleton()->CloseFile(path);

		if (errorBuffer)
		{
			SPLogHelper::WriteLog(L"[SPEffect] WARNING: There is error in shader file: " + path);
			SPLogHelper::WriteLog("[SPEffect] Message: " + string((char*)errorBuffer->GetBufferPointer()));
			errorBuffer->Release();
		}

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog(L"[SPEffect] WARNING: Failed to create effect: " + path);

			return false;
		}

		SPGameManager::GetSingleton()->GetGame()->LockDrawingWhileLoading();

		for (int num = 9; num >= 0; num--)
		{
			string currentTechName = "T" + SPStringHelper::ToString(num);
			D3DXHANDLE handle = effect->GetTechniqueByName(currentTechName.c_str());

			if (handle)
			{
				
				if(SUCCEEDED(effect->ValidateTechnique(handle)))
				{
					techName = currentTechName;
					break;
				}				
			}
		}

		SPGameManager::GetSingleton()->GetGame()->UnlockDrawingWhileLoading();

		return true;
	}

	bool SPEffectCore::Load()
	{
		return true;
	}

	ID3DXEffect* SPEffectCore::GetEffect()
	{
		return effect;
	}

	bool SPEffectCore::Unload()
	{
		if (effect)
		{
			effect->Release();
			effect = NULL;
		}

		return true;
	}

	bool SPEffectCore::Reload()
	{
		return Load(name);
	}

	bool SPEffectCore::SetTechnique()
	{
		D3DXHANDLE handle = effect->GetTechniqueByName(techName.c_str());

		HRESULT hr;

		if (handle)
		{
			hr = effect->SetTechnique(handle);
		}
		
		return true;
	}

}