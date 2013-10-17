#pragma  once
#include "StdAfx.h"
#include "ParticleSystem.h"
#include "SPGame.h"
#include <cmath>
#include <d3dx9math.h>
#include <string>
#include <list>
#include <d3d9.h>
#include "Vertex.h"

using namespace SPEngine;
using namespace SPEngine::Vertex;

//LPDIRECT3DTEXTURE9 pTexture = NULL;

const DWORD Particle::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE ;

float angle2 = 0;

DWORD SPEngine::fToDw(float f)
{
	return *((DWORD*)&f);
}

SPEngine::BoundingBox::BoundingBox()
{
	maxPoint.x = SPEngine::INFINITY;
	maxPoint.y = SPEngine::INFINITY;
	maxPoint.z = SPEngine::INFINITY;

	minPoint.x = - SPEngine::INFINITY;
	minPoint.y = - SPEngine::INFINITY;
	minPoint.z = - SPEngine::INFINITY;
}

bool SPEngine::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if(p.x > maxPoint.x || p.x < minPoint.x) return false;
	if(p.y > maxPoint.y || p.y < minPoint.y) return false;
	if(p.z > maxPoint.z || p.z < minPoint.z) return false;
	return true;
}



SPEngine::ParticleSystem::ParticleSystem()
{
	vb = 0;
	tex = 0;
}

SPEngine::ParticleSystem::~ParticleSystem()
{
	particles.clear();

	if(vb)
		vb->Release();
	vb = NULL;

	if(tex)
		tex->Release();	
	tex = NULL;
}

void SPEngine::ParticleSystem::Load(
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
			float minStartAng,
			float maxStartAng,
			float degreePerSec,
			D3DXVECTOR3 rotateAx,
			bool isSnowRotate,
			float fadeOutT)
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
			minStartAngle = minStartAng;
			maxStartAngle = maxStartAng;
			degreePerSecond = degreePerSec;
			rotateAxis = rotateAx;
			ifSnowRotate = isSnowRotate;
			fadeOutTime = fadeOutT;

			currentAge = 0;
			vbSize = 2048;
			vbOffset = 0;
			vbBatchSize = 512;

			Init(device, texName, if3D);

			//for(int i = 0 ; i < numParticle ; i++)
			//	AddParticle();
}

bool SPEngine::ParticleSystem::Init(IDirect3DDevice9 *devicePtr, char* texFileName, bool if3D)
{
	D3DXIMAGE_INFO i;
	device = devicePtr;
	vb = 0;
	tex = 0;

	HRESULT hr = 0;
	
	hr = device->CreateVertexBuffer(
		vbSize * sizeof(NormalTexColorVertex) * 6,
		//D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
		NormalTexColorVertex::FVF,
		D3DPOOL_DEFAULT,
		&vb,
		0);

	if(FAILED(hr))
	{
		::MessageBoxA(0, "CreateVertexBuffer() - FAILED", "PSystem", 0);
		return false;
	}

	string fileName = texFileName;
	hr = D3DXCreateTextureFromFileExA(
		device, fileName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,	0,
		D3DFMT_A8B8G8R8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, 
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0,0,0,255),
		&i, NULL,
		&tex);


	height = i.Height;
	width = i.Width;

	if(FAILED(hr))
	{
		::MessageBoxA(0, "D3DXCreateTextureFromFile() - FAILED", "PSystem", 0);
		return false;
	}

	is3D = if3D;

	//FILE* file = NULL;
	//unsigned char* buffer;
	//if((file = fopen("snowball.png","rb"))==NULL)
	//	return false;
	//fseek(file, 0, SEEK_END);
	//long fileSize = ftell(file);
	//rewind(file);
	//buffer = new unsigned char[fileSize];
	//fileSize = (long)fread(buffer, 1, fileSize, file);
	//if(FAILED(D3DXCreateTextureFromFileInMemoryEx(device, buffer, fileSize, 0, 0, 0, 0, 
	//	D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, 0, 0, 0, &pTexture)))
	//{
	//	delete[] buffer;
	//	fclose(file);
	//	return E_FAIL;
	//}


	return true;
}

void SPEngine::ParticleSystem::Reset()
{
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		ResetParticle(&(*iter));
	}
}

void SPEngine::ParticleSystem::AddParticle()
{
	ParticleAttribute attribute;

	//Test
	attribute.lifeTime = maxAge;

	ResetParticle(&attribute);
	particles.push_back(attribute);
}

void SPEngine::ParticleSystem::PreRender()
{
	//if(is3D)
	//{
	//	device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	//	device->SetRenderState(D3DRS_POINTSCALEENABLE, true); 
	//}
	//} 
	//device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	//device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	//device->SetRenderState(D3DRS_LIGHTING, false);
	//device->SetRenderState(D3DRS_POINTSIZE, SPEngine::fToDw(size));
	//device->SetRenderState(D3DRS_POINTSIZE_MIN, SPEngine::fToDw(0.2f));
	//device->SetRenderState(D3DRS_POINTSCALE_A, SPEngine::fToDw(0));
	//device->SetRenderState(D3DRS_POINTSCALE_B, SPEngine::fToDw(0));
	//device->SetRenderState(D3DRS_POINTSCALE_C, SPEngine::fToDw(1));
	//alpha
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
	device->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
	device->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	//device->SetTextureStageState(0, D3DTSS_ALPHAOP,D3DTOP_SELECTARG1); 
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_DIFFUSE); 
	device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);


	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	device->SetRenderState(D3DRS_ALPHAREF, 0x10);
	device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);



	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

void SPEngine::ParticleSystem::PostRender()
{
	//device->SetRenderState(D3DRS_LIGHTING, true);
	//device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//alpha
	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

void SPEngine::ParticleSystem::Draw(float timeDelta)
{
	angle2 += 0.1f;
	D3DXMATRIX transMatrix;
	D3DXVECTOR3 rotationCenter(0, -1, 0);
	D3DXVECTOR3 trans(0, 0, 0);
	D3DXQUATERNION rotation(0, sin(angle2 / 2), 0, cos(angle2 / 2));
	D3DXMatrixAffineTransformation(&transMatrix, 1, &rotationCenter,
		&rotation, &trans);

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
	p = p * transMatrix;

	if(particles.empty()) return;

	PreRender();
	

	device->SetTexture(0, tex);
	device->SetFVF(NormalTexColorVertex::FVF);
	device->SetStreamSource(0, vb, 0, sizeof(NormalTexColorVertex));

	if(vbOffset > vbSize)
		vbOffset = 0;

	NormalTexColorVertex* v = 0;

	//vb->Lock(
	//	vbOffset * sizeof(Particle),
	//	vbBatchSize * sizeof(Particle),
	//	(void**)&v,
	//	vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
	//		
	//NormalTexColorVertex *vex;
	vb->Lock(
		vbOffset * sizeof(NormalTexColorVertex) * 6,
		vbBatchSize * sizeof(NormalTexColorVertex) * 6,
		(void**)&v,
		vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
		
	float halfWidth, halfHeight;			
	halfWidth = (float)(width) / 600.0f;
	halfHeight = (float)(height) / 600.0f;

	// VertexBuffer built from two , note texture coordinates: 
	//v[0] = NormalTexColorVertex(halfWidth, 0.0f, -halfHeight,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f); 
	//v[1] = NormalTexColorVertex(halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f); 
	//v[2] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f); 

	//v[3] = NormalTexColorVertex(halfWidth,  0.0f,-halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f); 
	//v[4] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f); 
	//v[5] = NormalTexColorVertex(-halfWidth, 0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f); 

	DWORD numParticlesInBatch = 0;

	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{		
		if(iter->isAlive)// && v != NULL)
		{
			v[0] = NormalTexColorVertex(halfWidth, 0.0f, -halfHeight,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, iter->color); 
			v[1] = NormalTexColorVertex(halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, iter->color);
			v[2] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, iter->color);

			v[3] = NormalTexColorVertex(halfWidth,  0.0f,-halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, iter->color);
			v[4] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, iter->color); 
			v[5] = NormalTexColorVertex(-halfWidth, 0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, iter->color);
			

			for (int num = 0;num < 6;num++)
			{
				D3DXMATRIX rotationMatrix;
				D3DXQUATERNION quaternion;
				D3DXVECTOR3 rotationCenter(0, 0, 0);
				D3DXMATRIX vecMatrix;
				if(ifSnowRotate)
				{
					rotateAxis = iter->velocity;
					float mold = sqrt(iter->velocity.x * iter->velocity.x +
						iter->velocity.y * iter->velocity.y +
						iter->velocity.z * iter->velocity.z);
					rotateAxis.x /= mold;
					rotateAxis.y /= mold;
					rotateAxis.z /= mold;
					//if(iter->rotateAngle > D3DX_PI / 2)
					//	iter->rotateAngle -= D3DX_PI;
				}
				float s = sin(iter->rotateAngle / 2);
				quaternion.x = s * rotateAxis.x;
				quaternion.y = s * rotateAxis.y;
				quaternion.z = s * rotateAxis.z;
				quaternion.w = cos(iter->rotateAngle / 2);
				D3DXMatrixAffineTransformation(&rotationMatrix, 
					1, &rotationCenter, &quaternion, NULL);

				vecMatrix._11 = v[num].x;
				vecMatrix._21 = v[num].y;
				vecMatrix._31 = v[num].z;
				vecMatrix._41 = 1;
				vecMatrix =rotationMatrix * vecMatrix;
				v[num].x = vecMatrix._11;
				v[num].y = vecMatrix._21;
				v[num].z = vecMatrix._31;

				v[num].x += (iter->position).x ;
				v[num].y += (iter->position).y ;
				v[num].z += (iter->position).z ;
			}
			
			//v->color = (D3DCOLOR)iter->color;
			
			v += 6;

			numParticlesInBatch++;

			if(numParticlesInBatch == vbBatchSize)
			{
				vb->Unlock();

				//device->SetTransform(D3DTS_WORLD2, &transMatrix);
				//device->SetTransform(D3DTS_WORLD1, &p);

				device->DrawPrimitive(
					//D3DPT_POINTLIST,
					D3DPT_TRIANGLELIST,
					vbOffset * 6 ,
					vbBatchSize * 2);

				vbOffset += vbBatchSize;

				if(vbOffset >= vbSize)
				{
					vbOffset = 0;
				}

				v = NULL;

				vb->Lock(
					vbOffset * sizeof(NormalTexColorVertex) * 6,
					vbBatchSize * sizeof(NormalTexColorVertex) * 6,
					(void**)&v,
					vbOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
				numParticlesInBatch = 0;
			}
		}
	}
	vb->Unlock();
	if(numParticlesInBatch)
	{
		//device->SetTransform(D3DTS_WORLD2, &transMatrix);
		//device->SetTransform(D3DTS_WORLD1, &p);

		device->DrawPrimitive(
			//D3DPT_POINTLIST,
			D3DPT_TRIANGLELIST,
			vbOffset * 6 ,
			numParticlesInBatch * 2);
	}

	vbOffset += vbBatchSize;
	if(vbOffset >= vbSize)
	{
		vbOffset = 0;
	}

	PostRender();
}

bool SPEngine::ParticleSystem::isEmpty()
{
	return particles.empty();
}

bool SPEngine::ParticleSystem::isDead()
{
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
			return false;
	}
	return true;
}

void SPEngine::ParticleSystem::RemoveDeadParticles()
{
	std::list<ParticleAttribute>::iterator iter;
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

void SPEngine::ParticleSystem::Update(float timeDelta)
{
	std::list<ParticleAttribute>::iterator iter;
	currentAge += timeDelta;
	for(iter = particles.begin() ; iter != particles.end(); iter++)
	{
		if(iter->isAlive)
		{
			iter->rotateAngle += degreePerSecond * timeDelta;
			iter->position += iter->velocity * timeDelta;
			iter->age += timeDelta;
			iter->velocity += iter->acceleration * timeDelta;
			if(iter->age > iter->lifeTime)
				iter->isAlive = false;
			if(!boundingBox.isPointInside(iter->position))
				iter->isAlive = false;
			//¼ÆËã½¥³öalphaÖµ
			if(iter->lifeTime - iter->age < fadeOutTime)
			{
				float alphaNum = iter->color.a;
				alphaNum *=
					(1 - timeDelta / (iter->lifeTime - iter->age));
				iter->color.a = alphaNum;
			}
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

void SPEngine::ParticleSystem::ResetDeadPariticle()
{
	std::list<ParticleAttribute>::iterator iter;
	ParticleAttribute tempAttribute;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(!iter->isAlive)
		{
			ResetParticle(&(*iter));
		}
	}
}

void SPEngine::ParticleSystem::ResetParticle(ParticleAttribute* attribute)
{
	attribute->isAlive = true;
	attribute->age = 0;
	GetRandomVector(&(attribute->position), &(originBox.minPoint), &(originBox.maxPoint));
	float velocityMo = GetRandomFloat(originMinVelocity, originMaxVelocity);
	float degree = GetRandomFloat(originMinDegree, originMaxDegree);
	attribute->rotateAngle = GetRandomFloat(minStartAngle, maxStartAngle);
	attribute->velocity.x = velocityMo * cos(degree);
	attribute->velocity.z = velocityMo * sin(degree);
	attribute->velocity.y = 0;
	attribute->color = originColor;
	attribute->acceleration = particleAcceleration;
}

float SPEngine::ParticleSystem::GetRandomFloat(float lowBound, float highBound)
{
	if(lowBound > highBound)
		return lowBound;
	float f = (rand() % 10000) * 0.0001f;
	return f * (highBound - lowBound) + lowBound;
}

void SPEngine::ParticleSystem::GetRandomVector(
	D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector)
{
	outVector->x = GetRandomFloat(minVector->x, maxVector->x);
	outVector->y = GetRandomFloat(minVector->y, maxVector->y);
	outVector->z = GetRandomFloat(minVector->z, maxVector->z);
}

