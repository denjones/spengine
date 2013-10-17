#pragma once
#include <d3dx9math.h>
#include "SPComponent.h"

namespace SPEngine
{
	class SPGame;

	class Camera : public SPComponent
	{
	public:
		enum CameraType { LANDOBJECT, AIRCRAFT }; 

	private: 
		CameraType	cameraType; 
		D3DXVECTOR3 right; 
		D3DXVECTOR3 up; 
		D3DXVECTOR3 look; 
		D3DXVECTOR3 position;
		float		viewAngle;
		float		aspectRation;
		float		frontPlaneDistance;
		float		backPlaneDistance;

	public:
		Camera(); 
		Camera(CameraType cameraType); 
		~Camera(); 

		bool Initialize();

		void Strafe(float units);	// left/right 
		void Fly(float units);		// up/down 
		void Walk(float units);		// forward/backward   
		void Pitch(float angle);	// rotate on right vector 
		void Yaw(float angle);		// rotate on up vector 
		void Roll(float angle);		// rotate on look vector 
		  
		void SetCameraType(CameraType setType); 
		void SetPosition(D3DXVECTOR3 pos);  
		bool SetProjection(
			float setViewAngle, 
			float setAspectRation,
			float setFront, 
			float setBack);
		bool SetViewport(
			int x, 
			int y, 
			int width, 
			int height);

		D3DXMATRIX	ViewMatrix();
		D3DXMATRIX	ProjectionMatrix();
		D3DXVECTOR3 Position(); 
		D3DXVECTOR3 Right(); 
		D3DXVECTOR3 Up(); 
		D3DXVECTOR3 Look(); 		

		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		bool Load();
		bool Unload();
	};
}


