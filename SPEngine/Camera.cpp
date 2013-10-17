#include "StdAfx.h"
#include "Camera.h"
#include "SPGame.h"

using namespace SPEngine;

Camera::Camera(void)
{
	currentGame = NULL;
}


Camera::~Camera(void)
{
}

bool Camera::Initialize()
{
	cameraType = AIRCRAFT;
	position = D3DXVECTOR3(0, 0, 0);
	right = D3DXVECTOR3(1, 0, 0);
	up = D3DXVECTOR3(0, 0, 1);
	look = D3DXVECTOR3(0, 1, 0);

	viewAngle = D3DX_PI  * 0.5f;
	aspectRation = (float)CurrentGame()->GetWidth() /
		(float)CurrentGame()->GetHeight();
	frontPlaneDistance = 0.2f;
	backPlaneDistance = 10.0f;

	// default
	SetPosition(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
	SetProjection(viewAngle, aspectRation, frontPlaneDistance, backPlaneDistance);

	return true;
}

void Camera::SetCameraType(CameraType setType)
{
	cameraType = setType;

	return;
}

void Camera::SetPosition(D3DXVECTOR3 pos)
{
	position = pos;

	return;
}

bool Camera::SetProjection(
	float setViewAngle, 
	float setAspectRation,
	float setFront, 
	float setBack)
{
	if (!currentGame)
	{
		return false;
	}

	viewAngle = setViewAngle;
	aspectRation = setAspectRation;
	frontPlaneDistance = setFront;
	backPlaneDistance = setBack;

	D3DXMATRIX proj; 
	D3DXMatrixPerspectiveFovLH( &proj, 	viewAngle,	
		aspectRation,	frontPlaneDistance,	backPlaneDistance);
	currentGame->GetDevice()->SetTransform(D3DTS_PROJECTION, &proj); 

	return true;
}

bool Camera::SetViewport(
	int x, 
	int y, 
	int width, 
	int height)
{
	if (!currentGame)
	{
		return false;
	}

	D3DVIEWPORT9 vp = {x, y, width, height, 0, 1}; 
	currentGame->GetDevice()->SetViewport(&vp); 

	return true;
}

D3DXVECTOR3 Camera::Position()
{
	return position;
}

D3DXVECTOR3 Camera::Right()
{
	return right;
}

D3DXVECTOR3 Camera::Up()
{
	return up;
}

D3DXVECTOR3 Camera::Look()
{
	return look;
}

D3DXMATRIX Camera::ViewMatrix()
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

void Camera::Pitch( float angle )
{
	D3DXMATRIX T; 
	D3DXMatrixRotationAxis(&T, &right,  angle); 

	// rotate up and look around right vector 
	D3DXVec3TransformCoord(&up,&up, &T); 
	D3DXVec3TransformCoord(&look,&look, &T);

	return;
}

void Camera::Yaw( float angle )
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

void Camera::Roll( float angle )
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

void Camera::Walk(float units) 
{ 
	// move only on x-z plane for land object 
	if( cameraType == LANDOBJECT ) 
		position += D3DXVECTOR3(look.x, 0.0f, look.z) * units; 
	if( cameraType == AIRCRAFT ) 
		position += look * units; 

	return;
} 
void Camera::Strafe(float units) 
{ 
	// move only on x-z plane for land object 
	if( cameraType == LANDOBJECT ) 
		position += D3DXVECTOR3(right.x, 0.0f, right.z) * units; 
	if( cameraType == AIRCRAFT ) 
		position += right * units; 

	return;
} 
void Camera::Fly(float units) 
{ 
	// move only on y-axis for land object 
	if( cameraType == LANDOBJECT ) 
		position.y += units; 
	if( cameraType == AIRCRAFT ) 
		position += up * units; 

	return;
} 

bool Camera::Update(float timeDelta)
{ 
	return true;
}

bool Camera::Draw(float timeDelta)
{
	currentGame->GetDevice()->SetTransform(D3DTS_VIEW, &ViewMatrix()); 
	
	currentGame->GetDevice()->SetTransform(D3DTS_PROJECTION, &ProjectionMatrix());	

	return true;
}

bool Camera::Load()
{
	aspectRation = (float)CurrentGame()->GetWidth() /
		(float)CurrentGame()->GetHeight();

	return true;
}

bool Camera::Unload()
{
	return true;
}

D3DXMATRIX SPEngine::Camera::ProjectionMatrix()
{
	D3DXMATRIX proj;

	D3DXMatrixPerspectiveFovLH( &proj, viewAngle,	
		aspectRation, frontPlaneDistance, backPlaneDistance);

	return proj;
}
