//////////////////////////////////////////////////////////////////////////
/// @file		SPEffect.h the header file of SPPixelShader class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPPointer.h"
#include <map>
#include "ISPLoadable.h"
#include "SPTexture.h"
#include "SPString.h"
#include "SPStringMap.h"
#include "SPPixelShaderCore.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPPixelShader to represent a pixel shader.
	/// 
	//////////////////////////////////////////////////////////////////////
	class SPPixelShader 
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
		SamplerMap samplers;
		ValueMap values;
		SPPixelShaderCorePtr core;

	public:
		SPPixelShader(void);
		SPPixelShader(SPString path);
		virtual ~SPPixelShader(void);

		bool Load(SPString path);

	private:
		bool Load();

	public:
		bool Unload();
		bool Reload();
		bool SetSampler(int num, SPTexturePtr tex);
		bool SetSampler(string index, SPTexturePtr tex);
		//bool SetBool(int num, bool constant);
		bool SetBool(string index, bool constant);
		//bool SetInt(int num, int constant);
		bool SetInt(string index, int constant);
		//bool SetFloat(int num, float constant);
		bool SetFloat(string index, float constant);
		//bool SetVector(int num, D3DXVECTOR4 constant);
		bool SetVector(string index, D3DXVECTOR4 constant);
		//bool SetValue(int num, void* pData, DWORD length);
		bool SetValue(string index, void* pData, DWORD length);

	public:
		bool ApplyPixelShader();
		bool SetConstants();
		bool SetDefault();
		SamplerMap GetSampler();
	};

	typedef SPPointer<SPPixelShader> SPPixelShaderPtr;
}