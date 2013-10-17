#pragma once
#include "ISPLoadable.h"
#include "SPString.h"
#include "SPPointer.h"

namespace SPEngine
{
	class SPEffectCore : public ISPLoadable
	{
		SPString name;
		ID3DXEffect* effect;
		string techName;

	public:
		SPEffectCore(SPString path);
		SPEffectCore(void);
		virtual ~SPEffectCore(void);

		ID3DXEffect* GetEffect();

		bool Load(SPString path);
		
	private:
		bool Load();

	public:
		bool Unload();
		bool Reload();
		bool SetTechnique();
	};

	typedef SPPointer<SPEffectCore> SPEffectCorePtr;
}
