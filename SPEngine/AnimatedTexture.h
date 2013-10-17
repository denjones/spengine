#pragma once
#include "texture.h"

namespace SPEngine
{
	class SpriteManager;

	class AnimatedTexture :	public SPEngine::Texture
	{
	public:
		int		frameCount;
		float	timePerFrame;
		int		frame;
		float	totalElapsed;
		bool	paused;
		int		row, column;
		bool	isToBeRemoved;
		D3DXVECTOR2 origin;

	public:
		AnimatedTexture(void);
		AnimatedTexture(
			SpriteManager* setManager, 
			string setFilename, 
			int setRow,
			int setColumn, 
			int setFPS, 
			D3DXVECTOR2 setOrigin);
		AnimatedTexture(
			SpriteManager* setManager,
			string setFilename, 
			int setRow, 
			int setColumn,
			int setFPS);
		AnimatedTexture(
			SpriteManager* setManager,
			string setFilename,
			int setRow, 
			int setColumn,
			int setFrame, 
			int setFPS);
		AnimatedTexture(
			SpriteManager* setManager, 
			Texture setTex,
			int setRow, 
			int setColumn, 
			int setFrame, 
			int setFPS);
		AnimatedTexture(
			SpriteManager* setManager, 
			string	setFilename,
			int		setRow, 
			int		setColumn, 
			int		setFrame, 
			int		setFPS,
			D3DXVECTOR2 setOrigin);
		~AnimatedTexture(void);

		bool Load(
			SpriteManager* manager, 
			string path,
			int setRow,
			int setColumn, 
			int setFPS);
		bool Load(
			SpriteManager* manager, 
			string path,
			int setRow,
			int setColumn, 
			int setFPS, 
			D3DXVECTOR2 setOrigin);		
		bool Load(
			SpriteManager* manager, 
			string path,
			int setRow,
			int setColumn, 
			int setFrame,
			int setFPS, 
			D3DXVECTOR2 setOrigin);

		bool UpdateFrame(float timeElapsed);
		bool DrawFrame();
		SPRectangle SourceRectangle();
		bool Remove();
		bool IsToBeRemoved();
		bool IsPause();
		bool Reset();
		bool Stop();
		bool Play();
		bool Pause();


		bool ARender();
		bool ARender(
			float		x,
			float		y);
		bool ARender(
			float		x,
			float		y,
			D3DCOLOR	color);
		bool ARender(
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth);
		bool ARender(
			D3DXVECTOR3 position);
		bool ARender(
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool ARender(
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool ARender(
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool ARender(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color);
		bool ARender(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render animation on screen with rectangle
		bool ARenderOnScreen(
			SPRectangle destRect,
			D3DCOLOR	color,
			float		depth);	

		// Render animation with scaling 
		bool ARenderWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color);
		bool ARenderWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth);
		bool ARenderWithScaling(
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color);
		bool ARenderWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);
		bool ARenderWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);

		// Render animation with rotation
		bool ARenderWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool ARenderWithRotation(
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderWithRotation(
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);
		
	
		bool ARenderBasic(
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);

		// Render animation centered
		bool ARenderCentered();
		bool ARenderCentered(
			float		x,
			float		y);
		bool ARenderCentered(
			float		x,
			float		y,
			D3DCOLOR	color);
		bool ARenderCentered(
			float		x,
			float		y,
			D3DCOLOR	color,
			float		depth);
		bool ARenderCentered(
			D3DXVECTOR3 position);
		bool ARenderCentered(
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool ARenderCentered(
			D3DXVECTOR3 center,
			D3DXVECTOR3 position,
			D3DCOLOR	color);
		bool ARenderCentered(
			float		x,
			float		y,
			float		scale,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool ARenderCentered(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderCentered(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderCentered(
			D3DXVECTOR3 position,
			float		scale,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderCentered(
			D3DXVECTOR3 position,
			float		scale,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render centered with scaling
		bool ARenderCenteredWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color);
		bool ARenderCenteredWithScaling(
			float		x,
			float		y,
			float		scale,
			D3DCOLOR	color,
			float		depth);
		bool ARenderCenteredWithScaling(
			D3DXVECTOR3 position,
			float		scale,
			D3DCOLOR	color);
		bool ARenderCenteredWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);
		bool ARenderCenteredWithScaling(
			D3DXVECTOR3 position,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DCOLOR	color);

		// Render centered with rotation
		bool ARenderCenteredWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderCenteredWithRotation(
			float		x,
			float		y,
			float		rotation,
			D3DCOLOR	color,
			float		depth);
		bool ARenderCenteredWithRotation(
			D3DXVECTOR3 position,
			float		rotation,
			D3DCOLOR	color);
		bool ARenderCenteredWithRotation(
			D3DXVECTOR3 position,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DCOLOR	color);

		// Render centered basic
		bool ARenderCenteredBasic(
			D3DXVECTOR3 center, 
			D3DXVECTOR3 position,
			D3DCOLOR	color,
			D3DXVECTOR2 scalingCenter,
			float		scalingRotation,
			D3DXVECTOR2 scaling,
			D3DXVECTOR2 rotationCenter,
			float		rotation,
			D3DXVECTOR2 translation);
	};
}

