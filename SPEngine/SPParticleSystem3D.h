#pragma once
#include <d3dx9math.h>
#include <string>
#include <list>
#include "SPComponent.h"
#include "SPColorHelper.h"
#include "SPTexture.h"

using namespace std;

namespace SPEngine
{
	const float INFINITY = FLT_MAX;

	DWORD fToDw(float f);

	class SPGame;
	class SPParticleSystemTexture;

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
		float rotateSpeed;

		//after 2013-2-4
		float scale;
		//after 2013-2-26
		float scaleAcce;
	};

	struct BoundingBox
	{
		BoundingBox();

		bool isPointInside(D3DXVECTOR3& p);

		D3DXVECTOR3 minPoint;
		D3DXVECTOR3 maxPoint;
	};

	struct BoundingBox2D
	{
		BoundingBox2D();

		bool isPointInside(D3DXVECTOR3& p);
		D3DXVECTOR2 minPoint;
		D3DXVECTOR2 maxPoint;
	};

	class SPParticleSystem3D
	{

		SPParticleSystemTexture* renderTarget;

	public:
		SPParticleSystem3D(void);
		virtual ~SPParticleSystem3D(void);

		void LoadWith2D(
			BoundingBox2D positionBox = BoundingBox2D(),
			BoundingBox2D boundBox = BoundingBox2D(),
			float minVelocity = 0,
			float maxVelocity = 0,
			float minDegree = 0,
			float maxDegree = 0,
			float particleAge = 0,
			D3DXCOLOR particleColor = SPColor::White,
			float particleRate = 1,
			float particleSystemAge = 100,
			SPTexturePtr texPtr = NULL,
			int numParticle = 0,
			D3DXVECTOR2 systemAcceleration = D3DXVECTOR2(0, 0),
//			float particleSize = 0,
			bool if3D = false,
			float minStartAngle = 0,
			float maxStartAngle = 0,
			float degreePerSecondMin = 0,
			float degreePerSecondMax = 0,
			D3DXVECTOR3 rotateAxis = D3DXVECTOR3(0, 1, 0),
			bool ifSnowRotate = false,
			float fadeOutT = 0,
			float minScale = 1,
			float maxScale = 1,
			float scaleDeltaMin = 0,
			float scaleDeltaMax = 0);

		bool SetRenderTarget(SPParticleSystemTexture* target);
		bool Init(SPTexturePtr texPtr,bool if3D);
		void Reset();
		void ResetParticle(ParticleAttribute *attribute);
		void AddParticle();
		void Update(float timeDelta);
		void PreRender();
		void Draw(float timeDelta);
		void PostRender();

		bool isEmpty();
		bool isDead();
		bool IsPlaying();

		void Pause();
		void Play();
		void Stop();
		bool Unload();
		bool Reload();

		void SetAcceleration(D3DXVECTOR3 accelaration);
		D3DXVECTOR3 GetAcceleration();

		void SetSpecialRotation(bool setOn);
		bool GetSpecialRotation();

		void SetVelocity(float velocity);

		void SetVelocityMin(float velocity);
		float GetVelocityMin();

		void SetVelocityMax(float velocity);
		float GetVelocityMax();

		void SetShootAngleMin(float angle);
		float GetShootAngleMin();

		void SetShootAngleMax(float angle);
		float GetShootAngleMax();

		void SetTheParticleScale(float scale);
		float GetTheParticleScale();

		void SetTheParticleScaleDelta(float scaleDelta);
		float GetTheParticleScaleDelta();

		void SetTheOriginBox(D3DXVECTOR3 minPoint, D3DXVECTOR3 maxPoint);
		D3DXVECTOR3 GetTheOriginBoxMin();
		D3DXVECTOR3 GetTheOriginBoxMax();

		void SetTheBoundingBox(D3DXVECTOR3 minPoint, D3DXVECTOR3 maxPoint);
		D3DXVECTOR3 GetTheBoundingBoxMin();
		D3DXVECTOR3 GetTheBoundingBoxMax();

		void SetBornBoxMinX(int setX);
		int GetBornBoxMinX();

		void SetBornBoxMinY(int setY);
		int GetBornBoxMinY();

		void SetLiveBoxMinX(int setX);
		int GetLiveBoxMinX();

		void SetLiveBoxMinY(int setY);
		int GetLiveBoxMinY();

		void SetBornBoxMaxX(int setX);
		int GetBornBoxMaxX();

		void SetBornBoxMaxY(int setY);
		int GetBornBoxMaxY();

		void SetLiveBoxMaxX(int setX);
		int GetLiveBoxMaxX();

		void SetLiveBoxMaxY(int setY);
		int GetLiveBoxMaxY();

		void SetParticleAge(float age);
		float GetParticleAge();

		void SetColor(D3DXCOLOR color);
		D3DXCOLOR GetColor();

		void SetBornRate(float rate);
		float GetBornRate();

		void SetSystemAge(float systemAge);
		float GetSystemAge();

		void SetTexture(SPTexturePtr textureP);
		SPTexturePtr GetTexture();

		void SetMaxNumOfParticle(int maxNum);
		int GetMaxNumOfParticle();

		void SetIs3D(bool if3D);

		void SetBeginRotateMinAngle(float angle);
		float GetBeginRotateMinAngle();

		void SetBeginRotateMaxAngle(float angle);
		float GetBeginRotateMaxAngle();

		void SetRotateSpeedMin(float angle);
		float GetRotateSpeedMin();

		void SetRotateSpeedMax(float angle);
		float GetRotateSpeedMax();

		void SetRotateAxis(D3DXVECTOR3 axis);
		D3DXVECTOR3 GetRotateAxis();

		void SetIfRotateAboutTheVelocity(bool is);
		bool GetIfRotateAboutTheVelocity();

		void SetFadeOutTime(float time);
		float GetFadeOutTime();

		void SetParticleMinScale(float minScale);
		float GetParticleMinScale();

		void SetParticleMaxScale(float maxScale);
		float GetParticleMaxScale();

		void SetParticleScaleDelta(float minAcce, float maxAcce);
		float GetParticleScaleDeltaMin();
		float GetParticleScaleDeltaMax();

		void SetBackgroundColor(D3DCOLOR color);
		D3DCOLOR GetBackgroundColor();

	protected:
		void RemoveDeadParticles();
		void ResetDeadPariticle(float timeDelta);
	private:
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
		float particalVelocity;
		float originMinVelocity, originMaxVelocity;
		float originMinDegree, originMaxDegree;
		float maxAge;
		float systemAge;
		float currentAge;
		D3DXVECTOR3 particleAcceleration;
		int shootTime;
		D3DCOLOR backgroundColor;

		int width, height;

		float fadeOutTime; // 渐出的时间长度

		//旋转相关参数
		float minStartAngle;
		float maxStartAngle;
		float degreePerSecondMin;
		float degreePerSecondMax;
		D3DXVECTOR3 rotateAxis;
		bool ifSnowRotateWithV;
		//after 2013-2-4

		float scaleRange1;
		float scaleRange2;

		float GetRandomFloat(float lowBound, float highBound);
		void GetRandomVector(D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector);

		//适应新引擎
		SPTexturePtr texturePtr;
		float scaleDeltas;
		bool isPause;

		float renderWidth;
		float renderHeight;

		int bornPerSec;

		float scaleAcceMin;
		float scaleAcceMax;

		CCritSec modificationLock;
	};

	typedef SPPointer<SPParticleSystem3D> SPParticleSystem3DPtr;
}