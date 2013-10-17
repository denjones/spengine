#include "StdAfx.h"
#include "SPEffect.h"
#include "SPLogHelper.h"
#include "SPDevice.h"
#include "SPStringHelper.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPPixelShaderCore.h"

namespace SPEngine
{
	SPPixelShaderCore::SPPixelShaderCore(void):
		pixelShader(NULL),
		constantTable(NULL)
	{
	}

	SPPixelShaderCore::SPPixelShaderCore( SPString path ):
		pixelShader(NULL),
		constantTable(NULL)	
	{
		Load(path);
	}


	SPPixelShaderCore::~SPPixelShaderCore(void)
	{
	}

	bool SPPixelShaderCore::Load( SPString path )
	{
		name = path;

		SPFilePtr file = SPFileManager::GetSingleton().OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPShader] WARNING: Failed to open shader file: " + path);
			return false;
		}

		ID3DXBuffer* shaderBuffer = NULL;
		ID3DXBuffer* errorBuffer = NULL;
		LONGLONG length = file->GetFileLength();
		char* pData = new char[(UINT)length];

		if(!file->Read(pData, (DWORD)length))
		{
			SPLogHelper::WriteLog(L"[SPShader] WARNING: Failed to read shader file: " + path);
			return false;
		}

		// Compile shader files.
		HRESULT hr = D3DXCompileShader(
			pData, (UINT)length, 0, 0, "Main", "ps_2_0", D3DXSHADER_DEBUG,
			&shaderBuffer, &errorBuffer, &constantTable);

		delete [] pData;
		pData = NULL;
		SPFileManager::GetSingleton().CloseFile(path);

		if (errorBuffer)
		{
			SPLogHelper::WriteLog(L"[SPShader] WARNING: There is error in shader file: " + path);
			SPLogHelper::WriteLog("[SPShader] Message: " + string((char*)errorBuffer->GetBufferPointer()));
			errorBuffer->Release();
		}

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog(L"[SPShader] WARNING: Failed to compile shader file: " + path);
			return false;
		}

		// Create pixel shader.
		hr = SPDevice::GetSingleton().GetD3DDevice()->CreatePixelShader(
			(DWORD*)shaderBuffer->GetBufferPointer(), &pixelShader);

		if (FAILED(hr))
		{
			SPLogHelper::WriteLog(L"[SPShader] WARNING: Failed to create pixel shader");

			if (shaderBuffer)
			{
				shaderBuffer->Release();
				shaderBuffer = NULL;
			}

			return false;
		}

		shaderBuffer->Release();
		shaderBuffer = NULL;

		return true;
	}

	bool SPPixelShaderCore::Load()
	{
		return true;
	}

	bool SPPixelShaderCore::Unload()
	{
		if (pixelShader)
		{
			pixelShader->Release();
			pixelShader = NULL;
		}

		if (constantTable)
		{
			constantTable->Release();
			constantTable = NULL;
		}

		return true;
	}

	bool SPPixelShaderCore::Reload()
	{
		return Load(name);
	}

	ID3DXConstantTable* SPPixelShaderCore::GetConstantTable()
	{
		return constantTable;
	}

	IDirect3DPixelShader9* SPPixelShaderCore::GetPixelShader()
	{
		return pixelShader;
	}

}