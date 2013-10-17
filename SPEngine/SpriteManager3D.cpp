#include "StdAfx.h"
#include "SpriteManager3D.h"
#include "SPGame.h"
#include "ColorHelper.h"
#include <d3d9.h>
#include "Vertex.h"

using namespace SPEngine;
using namespace SPEngine::Vertex;

SpriteManager3D::SpriteManager3D(void)
{
	currentGame = NULL;
}

SpriteManager3D::SpriteManager3D(SPGame* game)
{
	Register(game);
}

SpriteManager3D::~SpriteManager3D()
{
	Unload();
}

bool SpriteManager3D::Initialize()
{
	return true;
}

bool SpriteManager3D::Draw(float timeDelta)
{
	foreach(Sprite3D, sprite, list<Sprite3D>, sprites)
	{
		DrawSprite(sprite);
	}
	sprites.clear();
	return true;
}

void SpriteManager3D::SetFilter()
{
	GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);

	//alpha

	GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,   TRUE );
	GetDevice()->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
	GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); 
	GetDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE );
	GetDevice()->SetRenderState(D3DRS_ALPHAREF,        0x0f ); 
	GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
	//set blend
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GetDevice()->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	GetDevice()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GetDevice()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
}

bool SpriteManager3D::DrawSprite(Sprite3D sprite)
{
	IDirect3DVertexBuffer9* Quad = 0;

	GetDevice()->SetTexture(0,sprite.texture->texture);

	SetFilter();

	GetDevice()->CreateVertexBuffer(
		6 * sizeof(NormalTexColorVertex), 
		D3DUSAGE_WRITEONLY,
		NormalTexColorVertex::FVF,
		D3DPOOL_MANAGED,
		&Quad,
		0);
	//Vertex3D* v;
	NormalTexColorVertex *v;
	Quad->Lock(0, 0, (void**)&v, 0);
	//v[0] = Vertex3D(0.0f, (float)sprite.texture->height, 
	//	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	//v[1] = Vertex3D(0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	//v[2] = Vertex3D((float)sprite.texture->width,
	//	0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	//v[3] = Vertex3D(0.0f, (float)sprite.texture->height,
	//	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	//v[4] = Vertex3D((float)sprite.texture->width,
	//	0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	//v[5] = Vertex3D((float)sprite.texture->width, 
	//	(float)sprite.texture->height, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

	float halfWidth, halfHeight;
	halfWidth = (float)(sprite.texture->width) / 600.0f;
	halfHeight = (float)(sprite.texture->height) / 600.0f;

	// VertexBuffer built from two triangles, note texture coordinates: 
	v[0] = NormalTexColorVertex(halfWidth, 0.0f, -halfHeight,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f, sprite.color); 
	v[1] = NormalTexColorVertex(halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, sprite.color); 
	v[2] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, sprite.color); 

	v[3] = NormalTexColorVertex(halfWidth,  0.0f,-halfHeight, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, sprite.color); 
	v[4] = NormalTexColorVertex(-halfWidth, 0.0f, halfHeight,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f, sprite.color); 
	v[5] = NormalTexColorVertex(-halfWidth, 0.0f, -halfHeight, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, sprite.color); 

	Quad->Unlock();

	GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

	//D3DXMATRIX proj;
	//D3DXMatrixPerspectiveFovLH(
	//	&proj,
	//	D3DX_PI * 0.5f,
	//	(float)sprite.texture->width / sprite.texture->height,
	//	1.0f,
	//	1000.0f
	//	);

	//GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);

	GetDevice()->SetTransform(D3DTS_WORLD, &sprite.transformMatrix);

	GetDevice()->SetStreamSource(0, Quad, 0, sizeof(NormalTexColorVertex));
	GetDevice()->SetFVF(NormalTexColorVertex::FVF);
	GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	if(Quad)
		Quad->Release();

	return true;
}

bool SpriteManager3D::Update(float timeDelta)
{
	return true;
}

bool SpriteManager3D::addSprite3D(Texture3D* tex)
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation(&transformMatrix, 
		NULL, NULL, NULL, NULL, NULL, NULL);

	Sprite3D sprite(tex, transformMatrix, D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0), Color::White, 
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	sprites.push_back(sprite);
	return true;
}

bool SpriteManager3D::addSprite3D(Texture3D* tex, 
	D3DXVECTOR3 scalingCenter, D3DXQUATERNION scalingRotation,
	D3DXVECTOR3 scaling, D3DXVECTOR3 rotationCenter,
	D3DXQUATERNION rotation, D3DXVECTOR3 translation)
{
	D3DXMATRIX transformMatrix;
	//D3DXMatrixTransformation(&transformMatrix, &scalingCenter,
	//	&scalingRotation, &scaling, &rotationCenter,
	//	&rotation, &translation);
	D3DXMatrixAffineTransformation(&transformMatrix, 1, 
		&rotationCenter, &rotation, &translation);

	Sprite3D sprite(tex, transformMatrix, D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0), Color::White, 
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	
	sprites.push_back(sprite);
	return true;
}

bool SpriteManager3D::addSprite3D(
	Texture3D* setTexture,
	D3DXVECTOR3 scalingCenter,
	D3DXQUATERNION scalingRotation,
	D3DXVECTOR3 scaling, 
	D3DXVECTOR3 rotationCenter,
	D3DXQUATERNION rotation,
	D3DXVECTOR3 translation,
	D3DXVECTOR3 center, 
	D3DXVECTOR3 position,
	D3DCOLOR color, 
	D3DXVECTOR3 normal, 
	D3DXVECTOR2 addressFind)
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation(&transformMatrix,
		&scalingCenter,
		&scalingRotation,
		&scaling,
		&rotationCenter,
		&rotation,
		&translation);
	Sprite3D sprite3D(setTexture,
		transformMatrix,
		position,
		center,
		color,
		normal,
		addressFind);
	sprites.push_back(sprite3D);
	return true;
}

bool SpriteManager3D::addSprite3D(Texture3D* tex, D3DXMATRIX transformMatrix)
{
	Sprite3D sprite3D(tex, transformMatrix, D3DXVECTOR3(0, 0, 0),
		D3DXVECTOR3(0, 0, 0), Color::White, 
		D3DXVECTOR3(0, 0, 0), D3DXVECTOR2(0, 0));
	return true;
}

bool SpriteManager3D::Load()
{
	return true;
}

bool SpriteManager3D::Unload()
{
	return true;
}

LPDIRECT3DDEVICE9 SpriteManager3D::GetDevice()
{
	return currentGame->GetDevice();
}
