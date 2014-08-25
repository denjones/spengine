#include "StdAfx.h"
#include "SPEffect.h"
#include "SPEffectManager.h"
#include "SPDevice.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPEffect::SPEffect(void)
	{
	}

	SPEffect::SPEffect( SPString path )
	{
		Load(path);
	}

	SPEffect::~SPEffect(void)
	{
	}

	void SPEffect::Load( SPString path )
	{
		core = SPEffectManager::GetSingleton()->GetCore(path);

		if (!core)
		{
			return;
		}
	}

	void SPEffect::Load()
	{
	}

	void SPEffect::Unload()
	{
	}

	void SPEffect::SetBool( string index, bool constant )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(bool)));
	}

	void SPEffect::SetInt( string index, int constant )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(int)));
	}

	void SPEffect::SetFloat( string index, float constant )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(float)));
	}

	void SPEffect::SetVector( string index, D3DXVECTOR4 constant )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(D3DXVECTOR4)));
	}

	void SPEffect::SetValue( string index, void* pData, DWORD length )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair(pData, length));
	}

	void SPEffect::SetMatrix( string index, D3DXMATRIX constant )
	{
		if (!core)
		{
			return;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(D3DXMATRIX)));
	}

	void SPEffect::ApplyEffect()
	{
		if (!core)
		{
			return;
		}

		core->SetTechnique();
		SetConstants();

		SamplerMap::iterator iter = textures.begin();

		while(iter!= textures.end())
		{
			if(iter->second)
			{
				string texName = "Tex" + SPStringHelper::ToString(iter->first);
				D3DXHANDLE handle = core->GetEffect()->GetParameterByName(0, texName.c_str());

				if (handle)
				{
					core->GetEffect()->SetTexture(handle, iter->second->GetD3DTexture());
				}	
			}

			iter++;
		}		
	}

	void SPEffect::SetConstants()
	{
		SPStringMapIterator<ValuePairPtr> valueIter(&values);
		valueIter.First();

		while(!valueIter.IsDone())
		{
			D3DXHANDLE handle = NULL;
			handle = core->GetEffect()->GetParameterByName(0, valueIter.CurrentIndex().c_str());

			if (!handle)
			{
				valueIter.Next();
				continue;
			}

			HRESULT hr = S_OK;

			hr = core->GetEffect()->SetValue(handle, valueIter.CurrentItem()->pData, valueIter.CurrentItem()->length);

			if (FAILED(hr))
			{
				SPLogHelper::WriteLog(L"[SPEffect] WARNING: Failed to set effect constant! file: " +
					name + L", constant index:" + SPStringHelper::ToWString(valueIter.CurrentIndex()));
			}

			valueIter.Next();
		}
	}

	SPEngine::SPEffectCorePtr SPEffect::GetCore()
	{
		return core;
	}

	SPEffect::SamplerMap SPEffect::GetSampler()
	{
		return textures;
	}

	void SPEffect::Reload()
	{
		Load(name);
	}

	void SPEffect::SetTexture( int num, SPTexturePtr tex )
	{
		textures[num] = tex;
	}

	SPEffect::ValueMap SPEffect::GetValues()
	{
		return values;
	}

	SPEffect::ValuePair::ValuePair( void* setData, DWORD setLength )
	{
		pData = NULL;
		length = setLength;
		pData = new char[length];
		memcpy(pData, setData, length);
	}

	SPEffect::ValuePair::~ValuePair()
	{
		if (pData)
		{
			delete [] pData;
			pData = NULL;
		}		
	}



}