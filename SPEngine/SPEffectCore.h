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

		SPString GetName();
		void Load(SPString path);
		
	private:
		void Load();

	public:
		void Unload();
		void Reload();
		void SetTechnique();
	};

	typedef SPPointer<SPEffectCore> SPEffectCorePtr;
}
