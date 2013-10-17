//////////////////////////////////////////////////////////////////////////
/// @file		SPCamera.h the header file of SPCamera class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-16
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9math.h>
#include "SPComponent.h"
#include "SPSingleton.h"

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief class SPCamera 
	/// A class to represent a camera in the game.
	///
	//////////////////////////////////////////////////////////////////////
	class SPCamera : 
		public SPComponent,
		public SPSingleton<SPCamera>
	{
	public:
		enum CameraType { LANDOBJECT, AIRCRAFT };  ///< Camera type.

	private: 
		CameraType	cameraType; 
		D3DXVECTOR3 right;				///< Right direction in the world.
		D3DXVECTOR3 up;					///< Up direction in the world.
		D3DXVECTOR3 look;				///< Direction looking at
		D3DXVECTOR3 position;			///< Position of the camera.
		float		viewAngle;			///< The angle of viewport.
		float		aspectRation;		///< The value of width / height.
		float		frontPlaneDistance;	///< The distance between front plane and viewpoint.
		float		backPlaneDistance;	///< The distance between back plane and viewpoint.

	public:
		SPCamera(); 
		SPCamera(CameraType cameraType); 
		virtual ~SPCamera(); 

		/// @name Actions
		/// @{
		void Strafe(float units);	///< left/right 
		void Fly(float units);		///< up/down 
		void Walk(float units);		///< forward/backward   
		void Pitch(float angle);	///< rotate on right vector 
		void Yaw(float angle);		///< rotate on up vector 
		void Roll(float angle);		///< rotate on look vector 
		/// @}
		  
		/// @name Set Functions
		/// @{
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
		/// @}

		/// @name Get Properties
		/// @{
		D3DXMATRIX	ViewMatrix();
		D3DXMATRIX	ProjectionMatrix();
		D3DXVECTOR3 Position(); 
		D3DXVECTOR3 Right(); 
		D3DXVECTOR3 Up(); 
		D3DXVECTOR3 Look(); 
		/// @}

		/// @name Component Methods
		/// @{
		bool Initialize();
		bool Update(float timeDelta);
		bool Draw(float timeDelta);
		bool Load();
		bool Unload();
		/// @}
	};
}


