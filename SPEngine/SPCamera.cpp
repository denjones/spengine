//////////////////////////////////////////////////////////////////////////
/// @file		SPCamera.cpp the implement file of SPCamera class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPCamera.h"
#include "SPGame.h"
#include "SPDevice.h"
#include "SPConfigManager.h"

using namespace SPEngine;

SPCamera::SPCamera(void)
{
}


SPCamera::~SPCamera(void)
{
}

void SPCamera::Initialize()
{
	cameraType = AIRCRAFT;
	position = D3DXVECTOR3(0, 0, 0);
	right = D3DXVECTOR3(1, 0, 0);
	up = D3DXVECTOR3(0, 0, 1);
	look = D3DXVECTOR3(0, 1, 0);

	viewAngle = D3DX_PI  * 0.5f;
	aspectRation = 
		(float)SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth /
		(float)SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight;
	frontPlaneDistance = 0.2f;
	backPlaneDistance = 10.0f;

	// default
	SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	SetProjection(viewAngle, aspectRation, frontPlaneDistance, backPlaneDistance);
	SetViewport( 0, 0,
		SPConfigManager::GetSingleton()->GetCurrentConfig().windowWidth,
		SPConfigManager::GetSingleton()->GetCurrentConfig().windowHeight);
}

void SPCamera::SetCameraType(CameraType setType)
{
	cameraType = setType;
}

void SPCamera::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;
}

void SPCamera::SetProjection(
	float setViewAngle, 
	float setAspectRation,
	float setFront, 
	float setBack)
{
	viewAngle = setViewAngle;
	aspectRation = setAspectRation;
	frontPlaneDistance = setFront;
	backPlaneDistance = setBack;

	D3DXMATRIX proj; 
	D3DXMatrixPerspectiveFovLH( &proj, 	viewAngle,	
		aspectRation,	frontPlaneDistance,	backPlaneDistance);
	SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &proj); 
}

void SPCamera::SetViewport(
	int x, 
	int y, 
	int width, 
	int height)
{
	D3DVIEWPORT9 vp = {x, y, width, height, 0, 1}; 
	SPDevice::GetSingleton()->GetD3DDevice()->SetViewport(&vp); 
}

D3DXVECTOR3 SPCamera::Position()
{
	return position;
}

D3DXVECTOR3 SPCamera::Right()
{
	return right;
}

D3DXVECTOR3 SPCamera::Up()
{
	return up;
}

D3DXVECTOR3 SPCamera::Look()
{
	return look;
}

D3DXMATRIX SPCamera::ViewMatrix()
{
	// Keep camera's axes orthogonal to each other 
	D3DXVec3Normalize(&look, &look); 
	D3DXVec3Cross(&up, &look, &right); 
	D3DXVec3Normalize(&up, &up); 
	D3DXVec3Cross(&right, &up, &look); 
	D3DXVec3Normalize(&right, &right); 

	// Build the view matrix: 
	float x = -D3DXVec3Dot(&right, &position); 
	float y = -D3DXVec3Dot(&up, &position); 
	float z = -D3DXVec3Dot(&look, &position); 

	D3DXMATRIX V;

	(V)(0,0) = right.x; (V)(0, 1) = up.x; (V)(0, 2) = look.x; (V)(0, 3) = 0.0f; 
	(V)(1,0) = right.y; (V)(1, 1) = up.y; (V)(1, 2) = look.y; (V)(1, 3) = 0.0f; 
	(V)(2,0) = right.z; (V)(2, 1) = up.z; (V)(2, 2) = look.z; (V)(2, 3) = 0.0f; 
	(V)(3,0) = x;       (V)(3, 1) = y;    (V)(3, 2) = z;      (V)(3, 3) = 1.0f;

	return V;
}

void SPCamera::Pitch( float angle )
{
	D3DXMATRIX T; 
	D3DXMatrixRotationAxis(&T, &right,  angle); 

	// rotate up and look around right vector 
	D3DXVec3TransformCoord(&up,&up, &T); 
	D3DXVec3TransformCoord(&look,&look, &T);

	return;
}

void SPCamera::Yaw( float angle )
{
	D3DXMATRIX T; 

	// rotate around world y (0, 1, 0) always for land object 
	if( cameraType == LANDOBJECT ) 
		D3DXMatrixRotationY(&T, angle); 

	// rotate around own up vector for aircraft 
	if( cameraType == AIRCRAFT ) 
		D3DXMatrixRotationAxis(&T, &up, angle); 

	// rotate right and look around up or y-axis 
	D3DXVec3TransformCoord(&right,&right, &T); 
	D3DXVec3TransformCoord(&look,&look, &T);

	return;
}

void SPCamera::Roll( float angle )
{
	// only roll for aircraft type 
	if( cameraType == AIRCRAFT ) 
	{ 
		D3DXMATRIX T; 
		D3DXMatrixRotationAxis(&T, &look,  angle); 

		// rotate up and right around look vector 
		D3DXVec3TransformCoord(&right,&right, &T); 
		D3DXVec3TransformCoord(&up,&up, &T); 
	}

	return;
}

void SPCamera::Walk(float units) 
{ 
	// move only on x-z plane for land object 
	if( cameraType == LANDOBJECT ) 
		position += D3DXVECTOR3(look.x, 0.0f, look.z) * units; 
	if( cameraType == AIRCRAFT ) 
		position += look * units; 

	return;
} 
void SPCamera::Strafe(float units) 
{ 
	// move only on x-z plane for land object 
	if( cameraType == LANDOBJECT ) 
		position += D3DXVECTOR3(right.x, 0.0f, right.z) * units; 
	if( cameraType == AIRCRAFT ) 
		position += right * units; 

	return;
} 
void SPCamera::Fly(float units) 
{ 
	// move only on y-axis for land object 
	if( cameraType == LANDOBJECT ) 
		position.y += units; 
	if( cameraType == AIRCRAFT ) 
		position += up * units; 

	return;
} 

void SPCamera::Update(float timeDelta)
{ 
}

void SPCamera::Draw(float timeDelta)
{
	SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_VIEW, &ViewMatrix()); 
	SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix());	
}

void SPCamera::Load()
{
	aspectRation = 
		(float)SPConfigManager::GetSingleton()->GetCurrentConfig().workingWidth /
		(float)SPConfigManager::GetSingleton()->GetCurrentConfig().workingHeight;

	SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_VIEW, &ViewMatrix()); 
	SPDevice::GetSingleton()->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix());
}

void SPCamera::Unload()
{
}

D3DXMATRIX SPEngine::SPCamera::ProjectionMatrix()
{
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH( &proj, viewAngle,	
		aspectRation, frontPlaneDistance, backPlaneDistance);

	return proj;
}
