#pragma once
#include "SPPointer.h"
#include <map>
#include "SPTexture.h"
#include "SPStringMap.h"
#include "SPEffectCore.h"
#include "ISPLoadable.h"

namespace SPEngine
{
	class SPEffect : public ISPLoadable
	{
		class ValuePair
		{
		public:
			void* pData;
			DWORD length;

		public:
			ValuePair(void* setData, DWORD setLength);
			~ValuePair();
		};

	public:
		typedef SPPointer<ValuePair> ValuePairPtr;
		typedef map<int,SPTexturePtr> SamplerMap;
		typedef SPStringMap<ValuePairPtr> ValueMap;

	protected:
		SPString name;
		SamplerMap textures;
		ValueMap values;
		SPEffectCorePtr core;

	public:
		SPEffect(void);
		SPEffect(SPString path);
		virtual ~SPEffect(void);

		bool Load(SPString path);

	private:
		bool Load();

	public:
		bool Unload();
		bool Reload();
		bool SetTexture(int num, SPTexturePtr tex);
		bool SetBool(string index, bool constant);
		bool SetInt(string index, int constant);
		bool SetFloat(string index, float constant);
		bool SetVector(string index, D3DXVECTOR4 constant);
		bool SetMatrix( string index, D3DXMATRIX constant );
		bool SetValue(string index, void* pData, DWORD length);

	public:
		bool ApplyEffect();
		SPEffectCorePtr GetCore();
		bool SetConstants();
		SamplerMap GetSampler();
	};

	typedef SPPointer<SPEffect> SPEffectPtr;
}
