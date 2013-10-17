#pragma once
#include <d3dx9math.h>
#include <string>
#include <list>
#include "SPComponent.h"

using namespace std;

namespace SPEngine
{
	const float INFINITY = FLT_MAX;

	DWORD fToDw(float f);

	class SPGame;

	struct Particle
	{
		D3DXVECTOR3 position;
		D3DCOLOR color;
		static const DWORD FVF;
	};

	struct ParticleAttribute
	{
		ParticleAttribute()
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

		float rotateAngle;
	};

	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 minPoint;
		D3DXVECTOR3 maxPoint;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem(void);
		~ParticleSystem(void);
		void Load(
			IDirect3DDevice9* device,
			BoundingBox positionBox,
			BoundingBox boundBox,
			float minVelocity,
			float maxVelocity,
			float minDegree,
			float maxDegree,
			float particleAge,
			D3DXCOLOR particleColor,
			float particleRate,
			float particleSystemAge,
			char* texName,
			int numParticle,
			D3DXVECTOR3 systemAcceleration,
			float particleSize,
			bool if3D,
			int setShootTime,
			float minStartAngle,
			float maxStartAngle,
			float degreePerSecond,
			D3DXVECTOR3 rotateAxis,
			bool ifSnowRotate,
			float fadeOutT);
		bool Init(IDirect3DDevice9 *device, char* texFileName,bool if3D);
		void Reset();
		void ResetParticle(ParticleAttribute *attribute);
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
		BoundingBox originBox;
		BoundingBox boundingBox;
		float emitRate;
		float size;
		IDirect3DTexture9 *tex;
		IDirect3DVertexBuffer9 *vb;
		list<ParticleAttribute> particles;
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

		int width, height;

		float fadeOutTime; // 渐出的时间长度

		//旋转相关参数
		float minStartAngle;
		float maxStartAngle;
		float degreePerSecond;
		D3DXVECTOR3 rotateAxis;
		bool ifSnowRotate;

		float GetRandomFloat(float lowBound, float highBound);
		void GetRandomVector(D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector);
	};
}