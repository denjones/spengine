#include "StdAfx.h"
#include "SPPixelShader.h"
#include "SPLogHelper.h"
#include "SPDevice.h"
#include "SPStringHelper.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPShaderManager.h"

namespace SPEngine
{
	SPPixelShader::SPPixelShader(void)
	{
		samplers.clear();
		values.Clear();
	}

	SPPixelShader::SPPixelShader( SPString path ) 
	{
		Load(path);
	}

	SPPixelShader::~SPPixelShader(void)
	{
		Unload();
	}

	bool SPPixelShader::Load( SPString path )
	{
		core = SPShaderManager::GetSingleton()->GetCore(path);

		if (!core)
		{
			return false;
		}

		core->GetConstantTable()->SetDefaults(SPDevice::GetSingleton()->GetD3DDevice());

		return true;


	}

	bool SPPixelShader::Load()
	{
		return true;
	}

	bool SPPixelShader::Unload()
	{
		return true;
	}

	bool SPPixelShader::Reload()
	{
		return true;
	}

	bool SPPixelShader::SetSampler( int num, SPTexturePtr tex )
	{
		if (!core)
		{
			return false;
		}

		samplers[num] = tex;

		return true;
	}

	bool SPPixelShader::SetSampler( string index, SPTexturePtr tex )
	{
		if (!core)
		{
			return false;
		}

		D3DXHANDLE handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if(!handle)
		{
			return false;
		}

		D3DXCONSTANT_DESC desc;
		core->GetConstantTable()->GetConstantDesc(handle, &desc, 0);
		int num = desc.RegisterIndex;

		samplers[num] = tex;
		return true;
	}

	bool SPPixelShader::ApplyPixelShader()
	{
		if (!core)
		{
			return false;
		}

		SPDevice::GetSingleton()->GetD3DDevice()->SetPixelShader(core->GetPixelShader());

		SamplerMap::iterator iter = samplers.begin();

		while(iter!= samplers.end())
		{
			if(iter->second)
			{
				SPDevice::GetSingleton()->GetD3DDevice()->SetTexture(iter->first, iter->second->GetD3DTexture());			
				SPDevice::GetSingleton()->GetD3DDevice()->SetSamplerState(iter->first, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);				
			}

			iter++;
		}		

		return true;
	}

	bool SPPixelShader::SetBool( string index, bool constant )
	{
		if (!core)
		{
			return false;
		}

		D3DXHANDLE handle;
		handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if (!handle)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(bool)));

		return true;
	}

	bool SPPixelShader::SetInt( string index, int constant )
	{
		if (!core)
		{
			return false;
		}

		D3DXHANDLE handle;
		handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if (!handle)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(int)));

		return true;
	}

	bool SPPixelShader::SetFloat( string index, float constant )
	{
		if (!core)
		{
			return false;
		}

		if (!core->GetConstantTable())
		{
			return false;
		}

		D3DXHANDLE handle;
		handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if (!handle)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(float)));

		return true;
	}

	bool SPPixelShader::SetValue( string index, void* pData, DWORD length )
	{
		if (!core)
		{
			return false;
		}

		D3DXHANDLE handle;
		handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if (!handle)
		{
			return false;
		}

		values.Set(index, new ValuePair(pData, length));

		return true;
	}

	bool SPPixelShader::SetVector( string index, D3DXVECTOR4 constant )
	{
		if (!core)
		{
			return false;
		}

		D3DXHANDLE handle;
		handle = core->GetConstantTable()->GetConstantByName(0, index.c_str());

		if (!handle)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(D3DXVECTOR4)));

		return true;
	}

	bool SPPixelShader::SetDefault()
	{
		core->GetConstantTable()->SetDefaults(SPDevice::GetSingleton()->GetD3DDevice());

		return true;
	}

	bool SPPixelShader::SetConstants()
	{
		SPStringMapIterator<ValuePairPtr> valueIter(&values);
		valueIter.First();

		while(!valueIter.IsDone())
		{
			D3DXHANDLE handle = NULL;
			handle = core->GetConstantTable()->GetConstantByName(0, valueIter.CurrentIndex().c_str());
			D3DXCONSTANT_DESC desc;
			core->GetConstantTable()->GetConstantDesc(handle, &desc, 0);	

			HRESULT hr = S_OK;

			hr = core->GetConstantTable()->SetValue(SPDevice::GetSingleton()->GetD3DDevice(), 
				handle, valueIter.CurrentItem()->pData, valueIter.CurrentItem()->length);

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog(L"[SPGraphics] WARNING: Failed to set pixel shader constant! file: " +
					name + L", constant index:" + SPStringHelper::ToWString(valueIter.CurrentIndex()));
			}

			valueIter.Next();
		}

		return true;
	}

	SPPixelShader::SamplerMap SPPixelShader::GetSampler()
	{
		return samplers;
	}

	SPPixelShader::ValuePair::ValuePair( void* setData, DWORD setLength )
	{
		pData = NULL;
		length = setLength;
		pData = new char[length];
		memcpy(pData, setData, length);
	}

	SPPixelShader::ValuePair::~ValuePair()
	{
		if (pData)
		{
			delete [] pData;
			pData = NULL;
		}		
	}

}

