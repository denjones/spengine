#pragma once
#include <d3dx9math.h>
#include <list>
#include "SPComponent.h"
#include "SPTexture.h"

using namespace std;

namespace SPEngine
{
	const float SPINFINITY = FLT_MAX;

	DWORD SPfToDw(float f);

	class SPGame;

	struct SPParticle
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
		static const DWORD FVF;
	};

	struct SPParticleAttribute
	{
		SPParticleAttribute()
		{
			lifeTime = 0;
			age = 0;
			isAlive = true;
		}

		D3DXVECTOR3 position;
		D3DXVECTOR3 velocity;
		float degree;
		D3DXVECTOR3 acceleration;
		float lifeTime;
		float age;
		D3DXCOLOR color;
		D3DXCOLOR colorFate;
		bool isAlive;
		float scale;
		float rotation;
	};

	struct SPBoundingBox
	{
		SPBoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 minPoint;
		D3DXVECTOR3 maxPoint;
	};

	class SPParticleSystem2D
	{
	public:
		SPParticleSystem2D(void);
		~SPParticleSystem2D(void);
		void Load(
			IDirect3DDevice9* device,
			SPBoundingBox positionBox,
			SPBoundingBox boundBox,
			float minVelocity,
			float maxVelocity,
			float minDegree,
			float maxDegree,
			float particleAge,
			D3DXCOLOR particleColor,
			float particleRate,
			float particleSystemAge,
			WCHAR* texName,
			int numParticle,
			D3DXVECTOR3 systemAcceleration,
			float particleSize,
			bool if3D,
			int shootTime);
		bool Init(IDirect3DDevice9 *device, WCHAR* texFileName,bool if3D);
		void Reset();
		void ResetParticle(SPParticleAttribute *attribute);
		void AddParticle();
		void Update(float timeDelta);
		void PreRender();
		void Draw(float timeDelta);
		void PostRender();

		bool isEmpty();
		bool isDead();
	protected:
		void RemoveDeadParticles();
		void ResetDeadPariticle();
	private:
		IDirect3DDevice9 *device;
		D3DXVECTOR3 origin;
		SPBoundingBox originBox;
		SPBoundingBox boundingBox;
		float emitRate;
		float size;
		IDirect3DTexture9 *tex;
		IDirect3DVertexBuffer9 *vb;
		list<SPParticleAttribute> particles;
		int maxParticles;
		DWORD vbSize;
		DWORD vbOffset;
		DWORD vbBatchSize;
		bool is3D;

		D3DCOLOR originColor;
		float originMinVelocity, originMaxVelocity;
		float originMinDegree, originMaxDegree;
		float maxAge;
		float systemAge;
		float currentAge;
		D3DXVECTOR3 particleAcceleration;
		int shootTime;

		float GetRandomFloat(float lowBound, float highBound);
		void GetRandomVector(D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector);

		////////////////new for sprite2D
		SPTexturePtr particleTexture;
		SPRectangle rec;

	};
	////////////∂®“Â÷∏’Î
	typedef SPPointer<SPParticleSystem2D> SPParticleSystem2DPtr;
}