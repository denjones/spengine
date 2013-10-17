#include "StdAfx.h"
#include "AnimatedTexture.h"
#include "SpriteManager.h"
#include "SPGame.h"
#include "ColorHelper.h"

using namespace SPEngine;

AnimatedTexture::AnimatedTexture(void)
{
	this->spriteManager = NULL;
	this->texture = NULL;
	this->origin = D3DXVECTOR2(0, 0);
	this->row = 0;
	this->column = 0;
	this->frameCount = 0;
	this->timePerFrame = 0;
	this->frame = 0;
	this->totalElapsed = 0;
	this->paused = true;
	this->isToBeRemoved = true;
	this->Width = 0;
	this->Height = 0;
}

//AnimatedTexture::AnimatedTexture( const AnimatedTexture& anime)
//{
//	//this->spriteManager = anime.spriteManager;
//	//this->origin = anime.origin;
//	//this->row = anime.row;
//	//this->column = anime.column;
//	//this->frameCount = anime.frameCount;
//	//this->timePerFrame = anime.timePerFrame;
//	//this->frame = anime.frame;
//	//this->totalElapsed = anime.totalElapsed;
//	//this->paused = anime.paused;
//	//this->isToBeRemoved = anime.isToBeRemoved;
//	//this->Width = anime.Width;
//	//this->Height = anime.Height;
//}

bool AnimatedTexture::Load(
	SpriteManager* manager, 
	string path,
	int setRow,
	int setColumn, 
	int setFPS)
{
	return Load(manager, path, setRow, setColumn,
		setRow * setColumn, setFPS, D3DXVECTOR2(0,0));
}

bool AnimatedTexture::Load(
	SpriteManager* manager, 
	string path,
	int setRow,
	int setColumn, 
	int setFPS, 
	D3DXVECTOR2 setOrigin)
{
	return Load(manager, path, setRow, setColumn,
		setRow * setColumn, setFPS, setOrigin);
}

bool AnimatedTexture::Load(
	SpriteManager* manager, 
	string path,
	int setRow,
	int setColumn,
	int setFrame,
	int setFPS, 
	D3DXVECTOR2 setOrigin)
{
	row = setRow;
	column = setColumn;

	if (row <= 0)
	{
		row = 1;
	}

	if (column <= 0)
	{
		column = 1;
	}

	frameCount = setFrame;
	timePerFrame = (float)1 / setFPS;
	isToBeRemoved = false;
	spriteManager = manager;

	frame = 0;
	totalElapsed = 0;
	paused = false;	

	D3DXIMAGE_INFO i;
	//PALETTEENTRY p; Don't know why we cannot make use of both palette and info.
	// Ether of them is used.

	D3DXCreateTextureFromFileExA(manager->GetDevice(),
		path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_FROM_FILE,	0,
		D3DFMT_A8B8G8R8,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE, 
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0,0,0,255),
		&i, NULL,
		&texture); 

	Height = i.Height;
	Width = i.Width;
	Width = Width / column;
	Height = Height / row;
	origin = setOrigin;

	spriteManager->AddAnime(this);

	return true;
}

AnimatedTexture::~AnimatedTexture(void)
{
}

AnimatedTexture::AnimatedTexture(
	SpriteManager* setManager, 
	string		setFilename, 
	int			setRow, 
	int			setColumn, 
	int			setFPS, 
	D3DXVECTOR2 setOrigin )
{
	Load(setManager, setFilename, setRow, 
		setColumn, setFPS, setOrigin);
}

AnimatedTexture::AnimatedTexture( 
	SpriteManager* setManager, 
	string setFilename, 
	int setRow, 
	int setColumn, 
	int setFPS )
{
	Load(setManager, setFilename, setRow, 
		setColumn, setFPS);
}

AnimatedTexture::AnimatedTexture( 
	SpriteManager* setManager, 
	string setFilename, 
	int setRow, 
	int setColumn, 
	int setFrame, 
	int setFPS )
{
	Load(setManager, setFilename, setRow, 
		setColumn, setFrame, setFPS, D3DXVECTOR2(0,0));
}

AnimatedTexture::AnimatedTexture( 
	SpriteManager* setManager, 
	Texture setTex, 
	int setRow, 
	int setColumn, 
	int setFrame, 
	int setFPS )
{
	texture = setTex.texture;
	row = setRow;
	column = setColumn;
	frameCount = setFrame;
	timePerFrame = (float)1 / setFPS;
	spriteManager = setManager;

	frame = 0;
	totalElapsed = 0;
	paused = false;

	spriteManager->AddAnime(this);
}

bool AnimatedTexture::UpdateFrame( float timeElapsed )
{
	if (isToBeRemoved)
	{
		return true;
	}

	if (paused)
	{
		return false;
	}

	totalElapsed += timeElapsed;

	if (totalElapsed > timePerFrame)
	{
		frame++;
		// Keep the Frame between 0 and the total frames, minus one.
		frame = frame % frameCount;
		totalElapsed -= timePerFrame;
	}

	return false;
}

bool AnimatedTexture::DrawFrame()
{
	return true;
}

SPRectangle AnimatedTexture::SourceRectangle()
{
	if (column == 0)
	{
		return SPRectangle(0,0,0,0);
	}
	return SPRectangle(
		frame % column * Width,
		frame / column * Height,
		Width, Height);
}

bool AnimatedTexture::Remove()
{
	Stop();
	isToBeRemoved = true;
	return true;
}

bool AnimatedTexture::IsToBeRemoved()
{
	return isToBeRemoved;
}

bool AnimatedTexture::IsPause()
{
	return paused;
}

bool AnimatedTexture::Reset()
{
	frame = 0;
	totalElapsed = 0.0f;
	return true;
}

bool AnimatedTexture::Stop()
{
	Pause();
	Reset();
	return true;
}

bool AnimatedTexture::Play()
{
	paused = false;
	return true;
}

bool AnimatedTexture::Pause()
{
	paused = true;
	return true;
}

bool AnimatedTexture::ARender()
{
	return	ARender(D3DXVECTOR3(0, 0, 0));
}

bool AnimatedTexture::ARender(
	float		x,
	float		y)
{
	return ARender(x, y, Color::White);
}

bool AnimatedTexture::ARender(
	D3DXVECTOR3 position)
{
	return ARender(position, Color::White);
}

bool AnimatedTexture::ARender(
	float		x,
	float		y,
	D3DCOLOR	color)
{
	return ARender(x, y, color, 0);
}

bool AnimatedTexture::ARender(
	float		x,
	float		y,
	D3DCOLOR	color,
	float		depth)
{
	return ARender(D3DXVECTOR3(x, y, depth), color);
}

bool AnimatedTexture::ARender(
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	return ARender(D3DXVECTOR3(0, 0, 0), position, color);
}

bool AnimatedTexture::ARender( 
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color )
{
	return ARenderBasic(center, position, color, 
		D3DXVECTOR2(position.x, position.y), 
		0, D3DXVECTOR2(1, 1),
		D3DXVECTOR2(position.x, position.y),
		0, D3DXVECTOR2(0, 0));
}

bool AnimatedTexture::ARender(
	float		x,
	float		y,
	float		scale,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return ARender(D3DXVECTOR3(x, y, depth),
		D3DXVECTOR2(scale, scale), rotation, color);
}

bool AnimatedTexture::ARender(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	float		rotation,
	D3DCOLOR	color)
{
	return ARender(position, D3DXVECTOR2(position.x, position.y), 0, 
		scaling, D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool AnimatedTexture::ARender(
	D3DXVECTOR3 position,			
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderBasic(D3DXVECTOR3(0, 0, 0), position, color, 
		scalingCenter, scalingRotation, scaling,
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

// Render on screen with rectangle
bool AnimatedTexture::ARenderOnScreen(
	SPRectangle	destRect,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderBasic( D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3((float)destRect.X, (float)destRect.Y, depth),
		color, D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
		D3DXVECTOR2((float)destRect.Width / SourceRectangle().Width, 
		(float)destRect.Height / SourceRectangle().Height), 
		D3DXVECTOR2((float)destRect.X, (float)destRect.Y), 0,
		D3DXVECTOR2(0,0));
}

// Render animation with scaling
bool AnimatedTexture::ARenderWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color)
{
	return ARenderWithScaling(x, y, scale, color, 0);
}

bool AnimatedTexture::ARenderWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderWithScaling(D3DXVECTOR3(x, y, depth), scale, color);
}

bool AnimatedTexture::ARenderWithScaling(
	D3DXVECTOR3 position,
	float		scale,
	D3DCOLOR	color)
{
	return	ARenderWithScaling(position, 
		D3DXVECTOR2(scale, scale),	color);
}

bool AnimatedTexture::ARenderWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return ARenderWithScaling(position,
		D3DXVECTOR2(position.x, position.y), 0, scaling, color);
}

bool AnimatedTexture::ARenderWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return ARenderBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, scalingCenter, scalingRotation, scaling,
		D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0));
}

// Render with rotation
bool AnimatedTexture::ARenderWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderWithRotation(x, y, rotation, color, 0);
}

bool AnimatedTexture::ARenderWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderWithRotation(D3DXVECTOR3(x,y,depth), rotation, color);
}

bool AnimatedTexture::ARenderWithRotation(
	D3DXVECTOR3 position,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderWithRotation(position, 
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool AnimatedTexture::ARenderWithRotation(
	D3DXVECTOR3 position,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool AnimatedTexture::ARenderBasic(
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR	color,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DXVECTOR2 translation)
{
	return RenderBasic(SourceRectangle().CRect(), 
		center, position, color,	scalingCenter, scalingRotation, 
		scaling, rotationCenter,	rotation, translation);
}

// Render centered
bool AnimatedTexture::ARenderCentered()
{
	return	ARenderCentered(D3DXVECTOR3(0, 0, 0));
}

bool AnimatedTexture::ARenderCentered(
	float		x,
	float		y)
{
	return ARenderCentered(x, y, Color::White);
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position)
{
	return ARenderCentered(position, Color::White);
}

bool AnimatedTexture::ARenderCentered(
	float		x,
	float		y,
	D3DCOLOR	color)
{
	return ARenderCentered(x, y, color, 0);
}

bool AnimatedTexture::ARenderCentered(
	float		x,
	float		y,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderCentered(D3DXVECTOR3(x, y, depth), color);
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position,
	D3DCOLOR	color)
{
	return ARenderCentered(D3DXVECTOR3(0, 0, 0), position, color);
}

bool AnimatedTexture::ARenderCentered( 
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position, 
	D3DCOLOR	color )
{
	return ARender(center, D3DXVECTOR3(
		position.x - SourceRectangle().Width / 2, 
		position.y - SourceRectangle().Height / 2,
		position.z), color);
	return true;
}

bool AnimatedTexture::ARenderCentered(
	float		x,
	float		y,
	float		scale,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderCentered(D3DXVECTOR3(x, y, depth),
		D3DXVECTOR2(scale, scale), rotation, color);
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCentered(position, D3DXVECTOR2(position.x, position.y), 0, 
		scaling, D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position,			
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, color, 
		scalingCenter, scalingRotation, scaling,
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position,
	float		scale,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCentered(position, scale,
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool AnimatedTexture::ARenderCentered(
	D3DXVECTOR3 position,
	float		scale,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderBasic(D3DXVECTOR3(0, 0, 0), 
		D3DXVECTOR3(position.x - SourceRectangle().Width / 2,
		position.y - SourceRectangle().Height / 2, position.z),
		color, D3DXVECTOR2(position.x, position.y), 
		0, D3DXVECTOR2(scale, scale),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

// Render with scaling
bool AnimatedTexture::ARenderCenteredWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color)
{
	return ARenderCenteredWithScaling(x, y, scale, color, 0);
}

bool AnimatedTexture::ARenderCenteredWithScaling(
	float		x,
	float		y,
	float		scale,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderCenteredWithScaling(D3DXVECTOR3(x, y, depth), scale, color);
}

bool AnimatedTexture::ARenderCenteredWithScaling(
	D3DXVECTOR3 position,
	float		scale,
	D3DCOLOR	color)
{
	return	ARenderCenteredWithScaling(position, 
		D3DXVECTOR2(scale, scale),	color);
}

bool AnimatedTexture::ARenderCenteredWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return ARenderCenteredWithScaling(position,
		D3DXVECTOR2(position.x, position.y), 0, scaling, color);
}

bool AnimatedTexture::ARenderCenteredWithScaling(
	D3DXVECTOR3 position,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DCOLOR	color)
{
	return ARenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, scalingCenter, scalingRotation, scaling,
		D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(0, 0));
}

// Render with rotation
bool AnimatedTexture::ARenderCenteredWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCenteredWithRotation(x, y, rotation, color, 0);
}

bool AnimatedTexture::ARenderCenteredWithRotation(
	float		x,
	float		y,
	float		rotation,
	D3DCOLOR	color,
	float		depth)
{
	return ARenderCenteredWithRotation(D3DXVECTOR3(x,y,depth), rotation, color);
}

bool AnimatedTexture::ARenderCenteredWithRotation(
	D3DXVECTOR3 position,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCenteredWithRotation(position, 
		D3DXVECTOR2(position.x, position.y), rotation, color);
}

bool AnimatedTexture::ARenderCenteredWithRotation(
	D3DXVECTOR3 position,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DCOLOR	color)
{
	return ARenderCenteredBasic(D3DXVECTOR3(0, 0, 0), position, 
		color, D3DXVECTOR2(position.x, position.y), 0, D3DXVECTOR2(1, 1),
		rotationCenter, rotation, D3DXVECTOR2(0, 0));
}

bool AnimatedTexture::ARenderCenteredBasic(
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR	color,
	D3DXVECTOR2 scalingCenter,
	float		scalingRotation,
	D3DXVECTOR2 scaling,
	D3DXVECTOR2 rotationCenter,
	float		rotation,
	D3DXVECTOR2 translation)
{
	return RenderCenteredBasic(SourceRectangle().CRect(), center, position, 
		color, scalingCenter, scalingRotation, scaling, 
		rotationCenter, rotation,translation);
}