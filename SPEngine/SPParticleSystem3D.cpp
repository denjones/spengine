#pragma  once
#include "StdAfx.h"
#include "SPParticleSystem3D.h"
#include "SPGame.h"
#include <cmath>
#include <d3dx9math.h>
#include <string>
#include <list>
#include <d3d9.h>
#include "SPVertex.h"
#include "SPDevice.h"
#include "SPConfigManager.h"
#include "SPParticleSystemTexture.h"

using namespace SPEngine;
using namespace SPEngine::SPVertex;

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

SPEngine::BoundingBox2D::BoundingBox2D()
{
	maxPoint.x = SPEngine::INFINITY;
	maxPoint.y = SPEngine::INFINITY;

	minPoint.x = - SPEngine::INFINITY;
	minPoint.y = - SPEngine::INFINITY;
}

bool SPEngine::BoundingBox::isPointInside(D3DXVECTOR3& p)
{
	if(p.x > maxPoint.x || p.x < minPoint.x) return false;
	if(p.y > maxPoint.y || p.y < minPoint.y) return false;
	if(p.z > maxPoint.z || p.z < minPoint.z) return false;
	return true;
}

bool SPEngine::BoundingBox2D::isPointInside(D3DXVECTOR3& p)
{
	if(p.x > maxPoint.x || p.x < minPoint.x) return false;
	if(p.z > maxPoint.y || p.z < minPoint.y) return false;
	return true;
}



SPEngine::SPParticleSystem3D::SPParticleSystem3D()
{
	vb = 0;
	tex = 0;
	renderTarget = NULL;
	isPause = false;
	backgroundColor = 0x00000000;
}

SPEngine::SPParticleSystem3D::~SPParticleSystem3D()
{
	particles.clear();

	if(vb)
		vb->Release();
	vb = NULL;

	if(tex)
		tex->Release();	
	tex = NULL;
}


//////////////////////////////////////////////////////////////////////
/// @brief LoadWith2D function to construct a 2D particle system
/// argument
/// IDirect3DDevice9    particle system device
/// BoundingBox2D       particles born position
/// BoundingBox2D       particles fly box
/// float               min particle's velocity
/// float               max particle's velocity
/// float               min particle's move angle
/// float               max particle's move angle
/// float               particle's age
/// float               particle's color
/// float               particle's born rate
/// float               entail particle system age
/// SPTexturePtr        texture name
/// int                 max number of particles
/// D3DXVECTOR2         acceleration of particle system
/// bool				is open the 3D apply colors to a drawing
/// float				开始绕轴旋转的角度最小值
/// float				开始绕轴旋转的角度最大值
/// float				每秒绕轴旋转的速率的最小值
/// float				每秒绕轴旋转的速率的最大值
/// D3DXVECTOR3			rotate axis
/// bool				is particle rotate about the velocity
/// float				fade out time
/// float				min scale
/// float				max scale
/// float				scale delta min
/// float				scale delta max
//////////////////////////////////////////////////////////////////////

void SPEngine::SPParticleSystem3D::LoadWith2D(
	BoundingBox2D positionBox,
	BoundingBox2D boundBox,
	float minVelocity,
	float maxVelocity,
	float minDegree,
	float maxDegree,
	float particleAge,
	D3DXCOLOR particleColor,
	float particleRate,
	float particleSystemAge,
	SPTexturePtr texPtr,
	int numParticle,
	D3DXVECTOR2 systemAcceleration,
//	float particleSize,
	bool if3D,
	float minStartAng,
	float maxStartAng,
	float degreePerSecMin,
	float degreePerSecMax,
	D3DXVECTOR3 rotateAx,
	bool isSnowRotate,
	float fadeOutT,
	float minScale,
	float maxScale,
	float scaleDeltaMin,
	float scaleDeltaMax)
{
	//要做像素与绝对坐标间的转化
	BoundingBox tempBox;
	if(!renderTarget)
	{
		renderWidth = SPConfigManager::GetSingleton().GetCurrentConfig().workingWidth;
		renderHeight = SPConfigManager::GetSingleton().GetCurrentConfig().workingHeight;
	}else
	{
		renderWidth = renderTarget->GetWidth();
		renderHeight = renderTarget->GetHeight();
	}
	//tempBox.minPoint = D3DXVECTOR3(positionBox.minPoint.x / renderWidth * 2 - 1,
	//	0, 
	//	positionBox.minPoint.y / renderHeight * 2 - 1);
	//tempBox.maxPoint = D3DXVECTOR3(positionBox.maxPoint.x / renderWidth * 2 - 1, 
	//	0, 
	//	positionBox.maxPoint.y / renderHeight * 2 - 1);
	//originBox = tempBox;
	//tempBox.minPoint = D3DXVECTOR3(boundBox.minPoint.x / renderWidth * 2 - 1, 0, 
	//	boundBox.minPoint.y / renderHeight * 2 - 1);
	//tempBox.maxPoint = D3DXVECTOR3(boundBox.maxPoint.x / renderWidth * 2 - 1, 0, 
	//	boundBox.maxPoint.y / renderHeight * 2 - 1);
	tempBox.minPoint = D3DXVECTOR3(positionBox.minPoint.x,
		0, 
		positionBox.minPoint.y);
	tempBox.maxPoint = D3DXVECTOR3(positionBox.maxPoint.x, 
		0, 
		positionBox.maxPoint.y);
	originBox = tempBox;
	tempBox.minPoint = D3DXVECTOR3(boundBox.minPoint.x, 0,
		boundBox.minPoint.y);
	tempBox.maxPoint = D3DXVECTOR3(boundBox.maxPoint.x, 0,
		boundBox.maxPoint.y);
	boundingBox = tempBox;
	originMinVelocity = minVelocity;
	originMaxVelocity = maxVelocity;
	originMinDegree = minDegree;
	originMaxDegree = maxDegree;
	maxAge = particleAge;
	originColor = particleColor;
	maxParticles = numParticle;
	emitRate = particleRate;
	systemAge = particleSystemAge;
	particleAcceleration = D3DXVECTOR3(systemAcceleration.x / renderWidth, 
		0, systemAcceleration.y / renderHeight);
//	size = particleSize;
	minStartAngle = minStartAng;
	maxStartAngle = maxStartAng;
	degreePerSecondMin = degreePerSecMin;
	degreePerSecondMax = degreePerSecMax;
	rotateAxis = rotateAx;
	ifSnowRotateWithV = isSnowRotate;

	fadeOutTime = fadeOutT;

	scaleRange1 = minScale;
	scaleRange2 = maxScale;

	currentAge = 0;
	vbSize = 2048;
	vbOffset = 0;
	vbBatchSize = 512;

	texturePtr = texPtr;

	scaleAcceMin = scaleDeltaMin;
	scaleAcceMax = scaleDeltaMax;

	if(texPtr)
		Init(texPtr, if3D);

	//for(int i = 0 ; i < numParticle ; i++)
	//	AddParticle();
}


bool SPEngine::SPParticleSystem3D::Init(SPTexturePtr texPtr, bool if3D)
{
	vb = 0;
	tex = 0;

	HRESULT hr = 0;
	
	hr = SPDevice::GetSingleton().GetD3DDevice()->CreateVertexBuffer(
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

	//string fileName = texFileName;
	//hr = D3DXCreateTextureFromFileExA(
	//	device, fileName.c_str(),
	//	D3DX_DEFAULT_NONPOW2,
	//	D3DX_DEFAULT_NONPOW2,
	//	D3DX_FROM_FILE,	0,
	//	D3DFMT_A8B8G8R8,
	//	D3DPOOL_MANAGED,
	//	D3DX_FILTER_TRIANGLE, 
	//	D3DX_FILTER_TRIANGLE,
	//	D3DCOLOR_RGBA(0,0,0,255),
	//	&i, NULL,
	//	&tex);

	height = texturePtr->GetHeight();
	width = texturePtr->GetWidth();

	//height = i.Height;
	//width = i.Width;

	//if(FAILED(hr))
	//{
	//	::MessageBoxA(0, "D3DXCreateTextureFromFile() - FAILED", "PSystem", 0);
	//	return false;
	//}

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

void SPEngine::SPParticleSystem3D::Reset()
{
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		ResetParticle(&(*iter));
	}
}

void SPEngine::SPParticleSystem3D::AddParticle()
{
	ParticleAttribute attribute;

	//Test
	attribute.lifeTime = maxAge;

	ResetParticle(&attribute);
	particles.push_back(attribute);
}

void SPEngine::SPParticleSystem3D::PreRender()
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
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );

	//device->SetTextureStageState(0, D3DTSS_ALPHAOP,D3DTOP_SELECTARG1); 
	//device->SetTextureStageState(0, D3DTSS_ALPHAARG1,D3DTA_DIFFUSE); 
	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	SPDevice::GetSingleton().GetD3DDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);


	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHAREF, 0x10);
	SPDevice::GetSingleton().GetD3DDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	SPDevice::GetSingleton().GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	SPDevice::GetSingleton().GetD3DDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	SPDevice::GetSingleton().GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	SPDevice::GetSingleton().GetD3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	SPDevice::GetSingleton().GetD3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);



	//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

void SPEngine::SPParticleSystem3D::PostRender()
{
	//device->SetRenderState(D3DRS_LIGHTING, true);
	//device->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	//device->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	//alpha
	//device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
}

void SPEngine::SPParticleSystem3D::Draw(float timeDelta)
{
	if (!texturePtr)
	{
		return;
	}

	modificationLock.Lock();

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


	// Off screen rendering variables
	HRESULT hr = S_OK;
	ID3DXRenderToSurface* renderToSurface = NULL;
	LPDIRECT3DSURFACE9 pRenderSurface = NULL;

	// Begin rendering off screen.
	if (renderTarget && renderTarget->IsRenderTarget())
	{
		hr = SPDevice::GetSingleton().GetD3DDevice()->EndScene();

		hr = renderTarget->GetD3DTexture()->GetSurfaceLevel(0, &pRenderSurface);

		D3DSURFACE_DESC desc;
		hr = pRenderSurface->GetDesc( &desc );

		hr = D3DXCreateRenderToSurface(
			SPDevice::GetSingleton().GetD3DDevice(), 
			desc.Width, 
			desc.Height,
			desc.Format,
			FALSE, 
			D3DFMT_A8R8G8B8,
			&renderToSurface);

		D3DXMATRIX viewMatrix;

		D3DXVECTOR3 right(1,0,0);
		D3DXVECTOR3 up(0,0,-1);
		D3DXVECTOR3 look(0,1,0);
		float x = 0;
		float y = 0;
		float z = 1;

		(viewMatrix)(0,0) = right.x; (viewMatrix)(0, 1) = up.x; (viewMatrix)(0, 2) = look.x; (viewMatrix)(0, 3) = 0.0f; 
		(viewMatrix)(1,0) = right.y; (viewMatrix)(1, 1) = up.y; (viewMatrix)(1, 2) = look.y; (viewMatrix)(1, 3) = 0.0f; 
		(viewMatrix)(2,0) = right.z; (viewMatrix)(2, 1) = up.z; (viewMatrix)(2, 2) = look.z; (viewMatrix)(2, 3) = 0.0f; 
		(viewMatrix)(3,0) = x;       (viewMatrix)(3, 1) = y;    (viewMatrix)(3, 2) = z;      (viewMatrix)(3, 3) = 1.0f;

		D3DXMATRIX projectionMatrix;

		D3DXMatrixPerspectiveFovLH( &projectionMatrix, D3DX_PI  * 0.5f,	
			(float)renderTarget->GetWidth() / (float)renderTarget->GetHeight(),	0.2f, 10.0f);		

		SPDevice::GetSingleton().GetD3DDevice()->SetTransform(D3DTS_VIEW, &viewMatrix); 
		SPDevice::GetSingleton().GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &projectionMatrix); 

		hr = renderToSurface->BeginScene(pRenderSurface, NULL);	

		SPDevice::GetSingleton().GetD3DDevice()->Clear(1, NULL, D3DCLEAR_TARGET, backgroundColor, 1.0, 0);
	}


	PreRender();
	

	SPDevice::GetSingleton().GetD3DDevice()->SetTexture(0, texturePtr->GetD3DTexture());
	SPDevice::GetSingleton().GetD3DDevice()->SetFVF(NormalTexColorVertex::FVF);
	SPDevice::GetSingleton().GetD3DDevice()->SetStreamSource(0, vb, 0, sizeof(NormalTexColorVertex));

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
	halfWidth = (float)(width) / renderHeight;
	halfHeight = (float)(height) / renderHeight;

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
			v[0] = NormalTexColorVertex(halfWidth * iter->scale, 0.0f, -halfHeight * iter->scale,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, iter->color); 
			v[1] = NormalTexColorVertex(halfWidth * iter->scale, 0.0f, halfHeight * iter->scale, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, iter->color);
			v[2] = NormalTexColorVertex(-halfWidth * iter->scale, 0.0f, halfHeight * iter->scale, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, iter->color);

			v[3] = NormalTexColorVertex(halfWidth * iter->scale,  0.0f,-halfHeight * iter->scale, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, iter->color);
			v[4] = NormalTexColorVertex(-halfWidth * iter->scale, 0.0f, halfHeight * iter->scale,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, iter->color); 
			v[5] = NormalTexColorVertex(-halfWidth * iter->scale, 0.0f, -halfHeight * iter->scale, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, iter->color);
			

			for (int num = 0;num < 6;num++)
			{
				D3DXMATRIX rotationMatrix;
				D3DXMATRIX selfRotationMatrix;
				D3DXQUATERNION quaternion;
				D3DXVECTOR3 rotationCenter(0, 0, 0);
				D3DXMATRIX vecMatrix;
				if(ifSnowRotateWithV)
				{
					float angle = atan2(iter->velocity.z, iter->velocity.x);
					float s = sin(angle / 2);
					quaternion.x = 0;
					quaternion.y = s;
					quaternion.z = 0;
					quaternion.w = cos(angle / 2);
					D3DXMatrixAffineTransformation(&selfRotationMatrix,
						1, &rotationCenter, &quaternion, NULL);
				}
				if(ifSnowRotateWithV)
				{
					rotateAxis = iter->velocity;
					float mold = sqrt(iter->velocity.x * iter->velocity.x +
						iter->velocity.y * iter->velocity.y +
						iter->velocity.z * iter->velocity.z);
					rotateAxis.x /= mold;
					rotateAxis.y /= mold;
					rotateAxis.z /= mold;
					if(iter->rotateAngle > D3DX_PI * 2)
						iter->rotateAngle -= D3DX_PI * 2;
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
				if(ifSnowRotateWithV)
					vecMatrix = rotationMatrix * selfRotationMatrix * vecMatrix;
				else
					vecMatrix = rotationMatrix * vecMatrix;
				v[num].x = vecMatrix._11;
				v[num].y = vecMatrix._21;
				v[num].z = vecMatrix._31;

				//v[num].x += (iter->position).x / renderWidth * 2 - 1;
				//v[num].y += (iter->position).y;
				//v[num].z += (iter->position).z / renderWidth * 2;


				v[num].x += (iter->position).x / renderHeight * 2 - renderWidth / renderHeight;
				v[num].y += (iter->position).y;
				v[num].z += (iter->position).z / renderHeight * 2 - 1;
			}
			
			//v->color = (D3DCOLOR)iter->color;
			
			v += 6;

			numParticlesInBatch++;

			if(numParticlesInBatch == vbBatchSize)
			{
				vb->Unlock();

				//device->SetTransform(D3DTS_WORLD2, &transMatrix);
				//device->SetTransform(D3DTS_WORLD1, &p);

				SPDevice::GetSingleton().GetD3DDevice()->DrawPrimitive(
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
		//SPDevice::GetSingleton().GetD3DDevice()->SetTransform(D3DTS_WORLD2, &transMatrix);
		//SPDevice::GetSingleton().GetD3DDevice()->SetTransform(D3DTS_WORLD1, &p);

		SPDevice::GetSingleton().GetD3DDevice()->DrawPrimitive(
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

	// End rendering off screen.
	if(renderTarget && renderTarget->IsRenderTarget())
	{
		hr = renderToSurface->EndScene(0);

		pRenderSurface->Release();
		renderToSurface->Release();
		pRenderSurface = NULL;
		renderToSurface = NULL;

		hr = SPDevice::GetSingleton().GetD3DDevice()->BeginScene();
	}

	modificationLock.Unlock();
}

bool SPEngine::SPParticleSystem3D::isEmpty()
{
	return particles.empty();
}

bool SPEngine::SPParticleSystem3D::isDead()
{
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
			return false;
	}
	return true;
}

void SPEngine::SPParticleSystem3D::RemoveDeadParticles()
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

void SPEngine::SPParticleSystem3D::Update(float timeDelta)
{
	if(isPause)
	{
		return;
	}

	//适应绘制Texture大小
	if(renderTarget)
	{
		if(renderTarget->GetWidth() != renderWidth || renderTarget->GetHeight() != renderHeight)
		{
			//originBox.minPoint.x = (originBox.minPoint.x + 1) / 2 * renderWidth / renderTarget->GetWidth() * 2 - 1;
			//originBox.minPoint.z = (originBox.minPoint.z + 1) / 2 * renderHeight / renderTarget->GetHeight() * 2 - 1;
			//originBox.maxPoint.x = (originBox.maxPoint.x + 1) / 2 * renderWidth / renderTarget->GetWidth() * 2 - 1;
			//originBox.maxPoint.z = (originBox.maxPoint.z + 1) / 2 * renderHeight / renderTarget->GetHeight() * 2 - 1;

			//boundingBox.minPoint.x = (boundingBox.minPoint.x + 1) / 2 * renderWidth / renderTarget->GetWidth() * 2 - 1;
			//boundingBox.minPoint.z = (boundingBox.minPoint.z + 1) / 2 * renderHeight / renderTarget->GetHeight() * 2 - 1;
			//boundingBox.maxPoint.x = (boundingBox.maxPoint.x + 1) / 2 * renderWidth / renderTarget->GetWidth() * 2 - 1;
			//boundingBox.maxPoint.z = (boundingBox.maxPoint.z + 1) / 2 * renderHeight / renderTarget->GetHeight() * 2 - 1;
			renderWidth = renderTarget->GetWidth();
			renderHeight = renderTarget->GetHeight();
		}
	}

	
	bornPerSec = 0;
	ResetDeadPariticle(timeDelta);

	std::list<ParticleAttribute>::iterator iter;
	currentAge += timeDelta;
	if(currentAge > systemAge && systemAge > 0)
	{
		Stop();
	}

	for(iter = particles.begin() ; iter != particles.end(); iter++)
	{
		if(iter->isAlive)
		{
			iter->rotateAngle += iter->rotateSpeed * timeDelta;
			iter->position += iter->velocity * timeDelta;
			iter->age += timeDelta;
			iter->velocity += iter->acceleration * timeDelta;
			if(iter->age > iter->lifeTime)
			{
				iter->isAlive = false;
			}
			if(!boundingBox.isPointInside(iter->position))
			{
				iter->isAlive = false;
			}
			//计算渐出alpha值
			if(iter->lifeTime - iter->age < fadeOutTime)
			{
				float alphaNum = iter->color.a;
				alphaNum *=
					(1 - timeDelta / (iter->lifeTime - iter->age));
				iter->color.a = alphaNum;
			}
			iter->scale += iter->scaleAcce * timeDelta;
			if(iter->scale < 0)
			{
				iter->isAlive = false;
			}
		}
	}

	//	if(shootTime <= systemAge)
	for(int i = 0 ; i < emitRate * timeDelta ; i++)
	{
		if(bornPerSec >= emitRate * timeDelta)
			break;
		if((int)particles.size() >= maxParticles)
			break;
		AddParticle();
		bornPerSec++;
	}

	//RemoveDeadParticles();
}

void SPEngine::SPParticleSystem3D::ResetDeadPariticle(float timeDelta)
{
	std::list<ParticleAttribute>::iterator iter;
	ParticleAttribute tempAttribute;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(!iter->isAlive)
		{
			ResetParticle(&(*iter));
			bornPerSec++;
			if(bornPerSec >= emitRate * timeDelta)
				return;
		}
	}
}

void SPEngine::SPParticleSystem3D::ResetParticle(ParticleAttribute* attribute)
{
	//转化绝对像素与-1 1位置
	attribute->isAlive = true;
	attribute->age = 0;
	GetRandomVector(&(attribute->position),
		&(originBox.minPoint), &(originBox.maxPoint));
	float velocityMo = GetRandomFloat(originMinVelocity, originMaxVelocity);
	float degree = GetRandomFloat(originMinDegree, originMaxDegree);
	attribute->rotateAngle = GetRandomFloat(minStartAngle, maxStartAngle);
	attribute->rotateSpeed = GetRandomFloat(degreePerSecondMin, degreePerSecondMax);
	attribute->velocity.x = velocityMo * cos(degree);
	attribute->velocity.z = velocityMo * sin(degree);
	attribute->velocity.y = 0;
	//attribute->velocity.y = velocityMo * sin(degree);
	//attribute->velocity.z = 0;
	attribute->color = originColor;
	attribute->acceleration = particleAcceleration;

	//after 2013-2-4
	attribute->scale = GetRandomFloat(scaleRange1, scaleRange2);
	attribute->scaleAcce = GetRandomFloat(scaleAcceMin, scaleAcceMax);
	//加入像素级的变化
//	attribute->velocity.x = attribute->velocity.x / renderWidth * 2 - 1;
//	attribute->velocity.z = attribute->velocity.z / renderHeight * 2 - 1;
}

float SPEngine::SPParticleSystem3D::GetRandomFloat(float lowBound, float highBound)
{
	if(lowBound > highBound)
		return lowBound;
	float f = (rand() % 10000) * 0.0001f;
	return f * (highBound - lowBound) + lowBound;
}

void SPEngine::SPParticleSystem3D::GetRandomVector(
	D3DXVECTOR3* outVector, D3DXVECTOR3* minVector, D3DXVECTOR3* maxVector)
{
	outVector->x = GetRandomFloat(minVector->x, maxVector->x);
	outVector->y = GetRandomFloat(minVector->y, maxVector->y);
	outVector->z = GetRandomFloat(minVector->z, maxVector->z);
}

bool SPEngine::SPParticleSystem3D::SetRenderTarget( SPParticleSystemTexture* target )
{
	modificationLock.Lock();
	//Main
	renderTarget = target;
	modificationLock.Unlock();
	return true;
}

void SPEngine::SPParticleSystem3D::Pause()
{
	modificationLock.Lock();
	isPause = true;
	modificationLock.Unlock();
}

void SPEngine::SPParticleSystem3D::SetAcceleration(D3DXVECTOR3 accelaration)
{
	modificationLock.Lock();

	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
		{
			iter->acceleration = accelaration;
		}
	}
	particleAcceleration = accelaration;

	modificationLock.Unlock();
}

D3DXVECTOR3 SPEngine::SPParticleSystem3D::GetAcceleration()
{
	return particleAcceleration;
}

void SPEngine::SPParticleSystem3D::SetVelocity(float velocity)
{
	modificationLock.Lock();
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
		{
			float hypotenuse = sqrt(iter->velocity.x * iter->velocity.x + iter->velocity.z * iter->velocity.z);
			float Prop = velocity / hypotenuse;
			iter->velocity.x *= Prop;
			iter->velocity.z *= Prop;
		}
	}
	particalVelocity = velocity;
	modificationLock.Unlock();
}


void SPEngine::SPParticleSystem3D::SetTheParticleScale(float scale)
{
	modificationLock.Lock();
	std::list<ParticleAttribute>::iterator iter;
	for(iter = particles.begin() ; iter != particles.end() ; iter++)
	{
		if(iter->isAlive)
		{
			iter->scale = scale;
		}
	}
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetTheParticleScale()
{
	return 0;
}


void SPEngine::SPParticleSystem3D::SetTheParticleScaleDelta(float scaleDelta)
{
	modificationLock.Lock();
	scaleDeltas = scaleDelta;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetTheParticleScaleDelta()
{
	return 0;
}



void SPEngine::SPParticleSystem3D::Play()
{
	modificationLock.Lock();
	isPause = false;
	modificationLock.Unlock();
}

void SPEngine::SPParticleSystem3D::Stop()
{
	modificationLock.Lock();
	particles.clear();
	currentAge = 0;
	isPause = true;
	modificationLock.Unlock();
}

void SPEngine::SPParticleSystem3D::SetTheOriginBox(D3DXVECTOR3 minPoint, D3DXVECTOR3 maxPoint)
{
	modificationLock.Lock();
	originBox.minPoint = minPoint;
	originBox.maxPoint = maxPoint;
	modificationLock.Unlock();
}

void SPEngine::SPParticleSystem3D::SetTheBoundingBox(D3DXVECTOR3 minPoint, D3DXVECTOR3 maxPoint)
{
	modificationLock.Lock();
	boundingBox.minPoint = minPoint;
	boundingBox.maxPoint = maxPoint;
	modificationLock.Unlock();
}



void SPEngine::SPParticleSystem3D::SetParticleAge(float age)
{
	modificationLock.Lock();
	maxAge = age;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetParticleAge()
{
	return maxAge;
}



void SPEngine::SPParticleSystem3D::SetColor(D3DXCOLOR color)
{
	modificationLock.Lock();
	originColor = color;
	modificationLock.Unlock();
}
D3DXCOLOR SPEngine::SPParticleSystem3D::GetColor()
{
	return originColor;
}



void SPEngine::SPParticleSystem3D::SetVelocityMin(float velocity)
{
	modificationLock.Lock();
	originMinVelocity = velocity;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetVelocityMin()
{
	return originMinVelocity;
}


void SPEngine::SPParticleSystem3D::SetVelocityMax(float velocity)
{
	modificationLock.Lock();
	originMaxVelocity = velocity;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetVelocityMax()
{
	return originMaxVelocity;
}


void SPEngine::SPParticleSystem3D::SetShootAngleMin(float angle)
{
	modificationLock.Lock();
	originMinDegree = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetShootAngleMin()
{
	return originMinDegree;
}


void SPEngine::SPParticleSystem3D::SetShootAngleMax(float angle)
{
	modificationLock.Lock();
	originMaxDegree = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetShootAngleMax()
{
	return originMaxDegree;
}


void SPEngine::SPParticleSystem3D::SetBornRate(float rate)
{
	modificationLock.Lock();
	emitRate = rate;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetBornRate()
{
	return emitRate;
}


void SPEngine::SPParticleSystem3D::SetSystemAge(float systemAge)
{
	modificationLock.Lock();
	this->systemAge = systemAge;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetSystemAge()
{
	return systemAge;
}



void SPEngine::SPParticleSystem3D::SetTexture(SPTexturePtr textureP)
{
	modificationLock.Lock();
	texturePtr = textureP;
	Init(textureP,is3D);
	modificationLock.Unlock();
}
SPEngine::SPTexturePtr SPEngine::SPParticleSystem3D::GetTexture()
{
	return texturePtr;
}



void SPEngine::SPParticleSystem3D::SetMaxNumOfParticle(int maxNum)
{
	modificationLock.Lock();
	maxParticles = maxNum;
	modificationLock.Unlock();
}
int SPEngine::SPParticleSystem3D::GetMaxNumOfParticle()
{
	return maxParticles;
}


void SPEngine::SPParticleSystem3D::SetIs3D(bool if3D)
{
	modificationLock.Lock();
	is3D = if3D;
	modificationLock.Unlock();
}


void SPEngine::SPParticleSystem3D::SetBeginRotateMinAngle(float angle)
{
	modificationLock.Lock();
	minStartAngle = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetBeginRotateMinAngle()
{
	return minStartAngle;
}



void SPEngine::SPParticleSystem3D::SetBeginRotateMaxAngle(float angle)
{
	modificationLock.Lock();
	maxStartAngle = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetBeginRotateMaxAngle()
{
	return maxStartAngle;
}



void SPEngine::SPParticleSystem3D::SetRotateSpeedMin(float angle)
{
	modificationLock.Lock();
	degreePerSecondMin = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetRotateSpeedMin()
{
	return degreePerSecondMin;
}



void SPEngine::SPParticleSystem3D::SetRotateSpeedMax(float angle)
{
	modificationLock.Lock();
	degreePerSecondMax = angle;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetRotateSpeedMax()
{
	return degreePerSecondMax;
}



void SPEngine::SPParticleSystem3D::SetRotateAxis(D3DXVECTOR3 axis)
{
	modificationLock.Lock();
	rotateAxis = axis;
	modificationLock.Unlock();
}
D3DXVECTOR3 SPEngine::SPParticleSystem3D::GetRotateAxis()
{
	return rotateAxis;
}



void SPEngine::SPParticleSystem3D::SetIfRotateAboutTheVelocity(bool is)
{
	modificationLock.Lock();
	ifSnowRotateWithV = is;
	modificationLock.Unlock();
}
bool SPEngine::SPParticleSystem3D::GetIfRotateAboutTheVelocity()
{
	return ifSnowRotateWithV;
}



void SPEngine::SPParticleSystem3D::SetFadeOutTime(float time)
{
	modificationLock.Lock();
	fadeOutTime = time;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetFadeOutTime()
{
	return fadeOutTime;
}



void SPEngine::SPParticleSystem3D::SetParticleMinScale(float minScale)
{
	modificationLock.Lock();
	scaleRange1 = minScale;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetParticleMinScale()
{
	return scaleRange1;
}


void SPEngine::SPParticleSystem3D::SetParticleMaxScale(float maxScale)
{
	modificationLock.Lock();
	scaleRange2 = maxScale;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetParticleMaxScale()
{
	return scaleRange2;
}



void SPEngine::SPParticleSystem3D::SetParticleScaleDelta(float minAcce, float maxAcce)
{
	modificationLock.Lock();
	scaleAcceMin = minAcce;
	scaleAcceMax = maxAcce;
	modificationLock.Unlock();
}
float SPEngine::SPParticleSystem3D::GetParticleScaleDeltaMin()
{
	return scaleAcceMin;
}
float SPEngine::SPParticleSystem3D::GetParticleScaleDeltaMax()
{
	return scaleAcceMax;
}


void SPEngine::SPParticleSystem3D::SetBornBoxMinX( int setX )
{
	D3DXVECTOR3 setMin = originBox.minPoint;
	setMin.x = setX;
	SetTheOriginBox(setMin, originBox.maxPoint);
}
int SPEngine::SPParticleSystem3D::GetBornBoxMinX()
{
	return originBox.minPoint.x;
}



void SPEngine::SPParticleSystem3D::SetBornBoxMinY( int setY )
{
	D3DXVECTOR3 setMin = originBox.minPoint;
	setMin.z = setY;
	SetTheOriginBox(setMin, originBox.maxPoint);
}
int SPEngine::SPParticleSystem3D::GetBornBoxMinY()
{
	return originBox.minPoint.y;
}


void SPEngine::SPParticleSystem3D::SetLiveBoxMinX( int setX )
{
	D3DXVECTOR3 setMin = boundingBox.minPoint;
	setMin.x = setX;
	SetTheBoundingBox(setMin, boundingBox.maxPoint);
}
int SPEngine::SPParticleSystem3D::GetLiveBoxMinX()
{
	return boundingBox.minPoint.x;
}


void SPEngine::SPParticleSystem3D::SetLiveBoxMinY( int setY )
{
	D3DXVECTOR3 setMin = boundingBox.minPoint;
	setMin.z = setY;
	SetTheBoundingBox(setMin, boundingBox.maxPoint);
}
int SPEngine::SPParticleSystem3D::GetLiveBoxMinY()
{
	return boundingBox.minPoint.y;
}


void SPEngine::SPParticleSystem3D::SetBornBoxMaxX( int setX )
{
	D3DXVECTOR3 setMax = originBox.maxPoint;
	setMax.x = setX;
	SetTheOriginBox(originBox.minPoint, setMax);
}
int SPEngine::SPParticleSystem3D::GetBornBoxMaxX()
{
	return originBox.maxPoint.x;
}



void SPEngine::SPParticleSystem3D::SetBornBoxMaxY( int setY )
{
	D3DXVECTOR3 setMax = originBox.maxPoint;
	setMax.z = -setY;
	SetTheOriginBox(originBox.minPoint, setMax);
}
int SPEngine::SPParticleSystem3D::GetBornBoxMaxY()
{
	return originBox.maxPoint.y;
}



void SPEngine::SPParticleSystem3D::SetLiveBoxMaxX( int setX )
{
	D3DXVECTOR3 setMax = boundingBox.maxPoint;
	setMax.x = setX;
	SetTheBoundingBox(boundingBox.minPoint, setMax);
}
int SPEngine::SPParticleSystem3D::GetLiveBoxMaxX()
{
	return boundingBox.maxPoint.x;
}



void SPEngine::SPParticleSystem3D::SetLiveBoxMaxY( int setY )
{
	D3DXVECTOR3 setMax = boundingBox.maxPoint;
	setMax.z = setY;
	SetTheBoundingBox(boundingBox.minPoint, setMax);
}
int SPEngine::SPParticleSystem3D::GetLiveBoxMaxY()
{
	return boundingBox.maxPoint.y;
}



void SPEngine::SPParticleSystem3D::SetSpecialRotation( bool setOn )
{
	modificationLock.Lock();
	ifSnowRotateWithV = setOn;
	modificationLock.Unlock();
}
bool SPEngine::SPParticleSystem3D::GetSpecialRotation()
{
	return ifSnowRotateWithV;
}



void SPEngine::SPParticleSystem3D::SetBackgroundColor( D3DCOLOR color )
{
	modificationLock.Lock();
	backgroundColor = color;
	modificationLock.Unlock();
}
D3DCOLOR SPEngine::SPParticleSystem3D::GetBackgroundColor()
{
	return backgroundColor;
}


bool SPEngine::SPParticleSystem3D::IsPlaying()
{
	return !isPause;
}

bool SPEngine::SPParticleSystem3D::Unload()
{
	if(vb)
	{
		vb->Release();
	}

	vb = NULL;

	return true;
}

bool SPEngine::SPParticleSystem3D::Reload()
{
	HRESULT hr = SPDevice::GetSingleton().GetD3DDevice()->CreateVertexBuffer(
		vbSize * sizeof(NormalTexColorVertex) * 6,
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

	return true;
}






