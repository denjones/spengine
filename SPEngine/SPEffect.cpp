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

	bool SPEffect::Load( SPString path )
	{
		core = SPEffectManager::GetSingleton().GetCore(path);

		if (!core)
		{
			return false;
		}

		return true;
	}

	bool SPEffect::Load()
	{
		return true;
	}

	bool SPEffect::Unload()
	{
		return true;
	}

	bool SPEffect::SetBool( string index, bool constant )
	{
		if (!core)
		{
			return false;
		}


		values.Set(index, new ValuePair((void*)&constant, sizeof(bool)));

		return true;
	}

	bool SPEffect::SetInt( string index, int constant )
	{
		if (!core)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(int)));

		return true;
	}

	bool SPEffect::SetFloat( string index, float constant )
	{
		if (!core)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(float)));

		return true;
	}

	bool SPEffect::SetVector( string index, D3DXVECTOR4 constant )
	{
		if (!core)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(D3DXVECTOR4)));

		return true;
	}

	bool SPEffect::SetValue( string index, void* pData, DWORD length )
	{
		if (!core)
		{
			return false;
		}

		values.Set(index, new ValuePair(pData, length));

		return true;
	}

	bool SPEffect::SetMatrix( string index, D3DXMATRIX constant )
	{
		if (!core)
		{
			return false;
		}

		values.Set(index, new ValuePair((void*)&constant, sizeof(D3DXMATRIX)));

		return true;
	}

	bool SPEffect::ApplyEffect()
	{
		if (!core)
		{
			return false;
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

		return true;
	}

	bool SPEffect::SetConstants()
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

		return true;
	}

	SPEngine::SPEffectCorePtr SPEffect::GetCore()
	{
		return core;
	}

	SPEffect::SamplerMap SPEffect::GetSampler()
	{
		return textures;
	}

	bool SPEffect::Reload()
	{
		return Load(name);
	}

	bool SPEffect::SetTexture( int num, SPTexturePtr tex )
	{
		textures[num] = tex;

		return true;
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