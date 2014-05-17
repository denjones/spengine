#pragma once
#include "SPString.h"
#include "ISPLoadable.h"
#include "SPPointer.h"

namespace SPEngine
{
	class SPPixelShaderCore : public ISPLoadable
	{
		SPString name;
		IDirect3DPixelShader9* pixelShader;
		ID3DXConstantTable* constantTable;

	public:
		SPPixelShaderCore(SPString path);
		SPPixelShaderCore(void);
		virtual ~SPPixelShaderCore(void);

		ID3DXConstantTable* GetConstantTable();
		IDirect3DPixelShader9* GetPixelShader();

		void Load(SPString path);

	private:
		void Load();

	public:
		void Unload();
		void Reload();
	};

	typedef SPPointer<SPPixelShaderCore> SPPixelShaderCorePtr;
}