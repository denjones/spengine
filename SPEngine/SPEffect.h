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

		void Load(SPString path);

	private:
		void Load();

	public:
		void Unload();
		void Reload();
		void SetTexture(int num, SPTexturePtr tex);
		void SetBool(string index, bool constant);
		void SetInt(string index, int constant);
		void SetFloat(string index, float constant);
		void SetVector(string index, D3DXVECTOR4 constant);
		void SetMatrix( string index, D3DXMATRIX constant );
		void SetValue(string index, void* pData, DWORD length);
		ValueMap GetValues();

	public:
		void ApplyEffect();
		SPEffectCorePtr GetCore();
		void SetConstants();
		SamplerMap GetSampler();
	};

	typedef SPPointer<SPEffect> SPEffectPtr;
}
