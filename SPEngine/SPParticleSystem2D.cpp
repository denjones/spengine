#pragma  once
#include "StdAfx.h"
#include "SPParticleSystem2D.h"
#include "SPTextureManager.h"
#include "SPSpriteManager.h"
#include "SPColorHelper.h"
#include <cmath>
#include <d3dx9math.h>
#include <list>

using namespace SPEngine;

const DWORD SPParticle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE ;

DWORD SPEngine::SPfToDw(float f)
{
	return *((DWORD*)&f);
}

SPEngine::SPBoundingBox::SPBoundingBox()
{
	maxPoint.x = SPEngine::SPINFINITY;
	maxPoint.y = SPEngine::SPINFINITY;
	maxPoint.z = SPEngine::SPINFINITY;

	minPoint.x = - SPEngine::SPINFINITY;
	minPoint.y = - SPEngine::SPINFINITY;
	minPoint.z = - SPEngine::SPINFINITY;
}

bool SPEngine::SPBoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if(p.x > maxPoint.x || p.x < minPoint.x) return false;
	if(p.y > maxPoint.y || p.y < minPoint.y) return false;
	if(p.z > maxPoint.z || p.z < minPoint.z) return false;
	return true;
}



SPEngine::SPParticleSystem2D::SPParticleSystem2D()
{
	vb = 0;
	tex = 0;
	particleTexture = NULL;
}

SPEngine::SPParticleSystem2D::~SPParticleSystem2D()
{
	if(vb)
		vb->Release();
	if(tex)
		tex->Release();
	vb = NULL;
	tex = NULL;
}

void SPEngine::SPParticleSystem2D::Load(
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
			int setShootTime)
{
			originBox = positionBox;
			boundingBox = boundBox;
			originMinVelocity = minVelocity;
			originMaxVelocity = maxVelocity;
			originMinDegree = minDegree;
			originMaxDegree = maxDegree;
			maxAge = particleAge;
			originColor = particleColor;
			maxParticles = numParticle;
			emitRate = particleRate;
			systemAge = particleSystemAge;
			particleAcceleration = systemAcceleration;
			size = particleSize;
			shootTime = setShootTime;

			currentAge = 0;
			vbSize = 2048;
			vbOffset = 0;
			vbBatchSize = 512;

			Init(device, texName, if3D);

			//for(int i = 0 ; i < numParticle ; i++)
			//	AddParticle();
}

bool SPEngine::SPParticleSystem2D::Init(IDirect3DDevice9 *devicePtr, WCHAR* texFileName, bool if3D)
{
	device = devicePtr;
	vb = 0;
	tex = 0;

	HRESULT hr = 0;
	/*
	hr = device->CreateVertexBuffer(
		vbSize * sizeof(Particle),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		Particle::FVF,
		D3DPOOL_DEFAULT,
		&vb,
		0);

	if(FAILED(hr))
	{
		::MessageBoxA(0, "CreateVertexBuffer() - FAILED", "PSystem", 0);
		return false;
	}

	string fileName = texFileName;
	hr = D3DXCreateTextureFromFileA(
		device,
		fileName.c_str(),
		&tex);

	if(FAILED(hr))
	{
		::MessageBoxA(0, "D3DXCreateTextureFromFile() - FAILED", "PSystem", 0);
		return false;
	}

	is3D = if3D;
	*/
	particleTexture = SPTextureManager::GetSingleton()->GetTexture(texFileName);
	return true;
}

void SPEngine::SPParticleSystem2D::Reset()
{
	std::list<SPParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		ResetParticle(&(*iter));
	}
}

void SPEngine::SPParticleSystem2D::AddParticle()
{
	SPParticleAttribute attribute;

	//Test
	attribute.lifeTime = maxAge;

	ResetParticle(&attribute);
	particles.push_back(attribute);
}

void SPEngine::SPParticleSystem2D::PreRender()
{
	//if(is3D)
	//{
	//	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//	device->SetRenderState(D3DRS_POINTSCALEENABLE, true); 
	//}

	//device->SetRenderState(D3DRS_LIGHTING, false);
	//device->SetRenderState(D3DRS_POINTSIZE, SPEngine::fToDw(size));
	//device->SetRenderState(D3DRS_POINTSIZE_MIN, SPEngine::fToDw(0.2f));
	//device->SetRenderState(D3DRS_POINTSCALE_A, SPEngine::fToDw(0));
	//device->SetRenderState(D3DRS_POINTSCALE_B, SPEngine::fToDw(0));
	//device->SetRenderState(D3DRS_POINTSCALE_C, SPEngine::fToDw(1));
	////alpha
	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	//device->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
	//device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	//device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	//device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
	//device->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
	//device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
}

void SPEngine::SPParticleSystem2D::PostRender()
{
	//device->SetRenderState(D3DRS_LIGHTING, true);
	//device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//alpha
	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

void SPEngine::SPParticleSystem2D::Draw(float timeDelta)
{
	// Set rotation
	D3DXMATRIX Rx, Ry; 
	static float x = 0.0f;
	D3DXMatrixRotationX(&Rx, x); 
	x = 0;
	static float y = 0.0f; 
	D3DXMatrixRotationY(&Ry, y); 
	y = 0; 

	// Reset
	if( y >= 6.28f ) 
		y = 0.0f; 
	if( x >= 6.28f ) 
		x = 0.0f; 

	// Construct rotation matrix
	D3DXMATRIX p = Rx * Ry; 

	if(particles.empty()) return;

	PreRender();
	
	//device->SetTexture(0, tex);
	//device->SetFVF(Particle::FVF);
	//device->SetStreamSource(0, vb, 0, sizeof(Particle));

	if(vbOffset > vbSize)
		vbOffset = 0;

	SPParticle* v = 0;

	//vb->Lock(
	//	vbOffset * sizeof(Particle),
	//	vbBatchSize * sizeof(Particle),
	//	(void**)&v,
	//	vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
		
	DWORD numParticlesInBatch = 0;

	std::list<SPParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		SPRectangle rect = SPRectangle(0, 0, particleTexture->GetWidth(), particleTexture->GetHeight());
		SPSpriteManager::GetSingleton()->RenderCentered(particleTexture, NULL, rect, iter->position, 1
			,D3DXVECTOR2(0, 0), iter->rotation, SPColor::White, NULL);

		//SPSpriteManager::GetSingleton()->RenderCentered(particleTexture, NULL, iter->position.x, iter->position.y, NULL);
		//if(iter->isAlive)// && v != NULL)
		//{
		//	v->position = iter->position;
		//	v->color = (D3DCOLOR)iter->color;
		//	v++;

		//	numParticlesInBatch++;

		//	if(numParticlesInBatch == vbBatchSize)
		//	{
		//		vb->Unlock();

		//		device->SetTransform(D3DTS_WORLD, &p);

		//		device->DrawPrimitive(
		//			D3DPT_POINTLIST,
		//			vbOffset,
		//			vbBatchSize);

		//		vbOffset += vbBatchSize;

		//		if(vbOffset >= vbSize)
		//		{
		//			vbOffset = 0;
		//		}

		//		v = NULL;

		//		vb->Lock(
		//			vbOffset * sizeof(Particle),
		//			vbBatchSize * sizeof(Particle),
		//			(void**)&v,
		//			vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
		//		numParticlesInBatch = 0;
		//	}
		//}
	}
	//vb->Unlock();
	//if(numParticlesInBatch)
	//{
	//	device->SetTransform(D3DTS_WORLD, &p);

	//	device->DrawPrimitive(
	//		D3DPT_POINTLIST,
	//		vbOffset,
	//		numParticlesInBatch);
	//}

	//vbOffset += vbBatchSize;
	//if(vbOffset >= vbSize)
	//{
	//	vbOffset = 0;
	//}

	//PostRender();
}

bool SPEngine::SPParticleSystem2D::isEmpty()
{
	return particles.empty();
}

bool SPEngine::SPParticleSystem2D::isDead()
{
	std::list<SPParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
			return false;
	}
	return true;
}

void SPEngine::SPParticleSystem2D::RemoveDeadParticles()
{
	std::list<SPParticleAttribute>::iterator iter;
	iter = particles.begin();
	while(iter != particles.end())
	{
		if(iter->isAlive == false)
		{
			iter = particles.erase(iter);
		}
		else{
			iter++;
		}
	}
}

void SPEngine::SPParticleSystem2D::Update(float timeDelta)
{
	std::list<SPParticleAttribute>::iterator iter;
	currentAge += timeDelta;
	for(iter = particles.begin() ; iter != particles.end(); iter++)
	{
		if(iter->isAlive)
		{
			iter->position += iter->velocity * timeDelta;
			iter->age += timeDelta;
			iter->velocity += iter->acceleration * timeDelta;
			if(iter->age > iter->lifeTime)
				iter->isAlive = false;
			if(!boundingBox.isPointInside(iter->position))
				iter->isAlive = false;
		}
	}

	if(shootTime <= systemAge)
		for(int i = 0 ; i < emitRate * timeDelta ; i++)
		{
			if((int)particles.size() >= maxParticles)
				break;
			AddParticle();
		}

	//RemoveDeadParticles();
	ResetDeadPariticle();
}

void SPEngine::SPParticleSystem2D::ResetDeadPariticle()
{
	std::list<SPParticleAttribute>::iterator iter;
	SPParticleAttribute tempAttribute;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(!iter->isAlive)
		{
			ResetParticle(&(*iter));
		}
	}
}

void SPEngine::SPParticleSystem2D::ResetParticle(SPParticleAttribute* attribute)
{
	attribute->isAlive = true;
	attribute->age = 0;
	GetRandomVector(&(attribute->position), &(originBox.minPoint), &(originBox.maxPoint));
	float velocityMo = GetRandomFloat(originMinVelocity, originMaxVelocity);
	float degree = GetRandomFloat(originMinDegree, originMaxDegree);
	attribute->velocity.x = velocityMo * cos(degree);
	//attribute->velocity.z = velocityMo * sin(degree);
	//attribute->velocity.y = 0;
	attribute->velocity.y = velocityMo * sin(degree);
	attribute->velocity.z = 0;
	attribute->color = originColor;
	attribute->acceleration = particleAcceleration;
}

float SPEngine::SPParticleSystem2D::GetRandomFloat(float lowBound, float highBound)
{
	if(lowBound > highBound)
		return lowBound;
	float f = (rand() % 10000) * 0.0001f;
	return f * (highBound - lowBound) + lowBound;
}

void SPEngine::SPParticleSystem2D::GetRandomVector(
	D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector)
{
	outVector->x = GetRandomFloat(minVector->x, maxVector->x);
	outVector->y = GetRandomFloat(minVector->y, maxVector->y);
	outVector->z = GetRandomFloat(minVector->z, maxVector->z);
}

