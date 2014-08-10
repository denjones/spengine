#include "StdAfx.h"
#include "SUIComponent.h"
#include "SV8ScriptManager.h"
#include "SUIManager.h"
#include "SUIV8FunctionEventHandler.h"
#include "SV8Function.h"
#include <shlobj.h>
#include <shlwapi.h>
#include "SUITextBox.h"
#include "SUIDialogBox.h"
#include "SUIPictureBox.h"
#include "SUIList.h"

#pragma warning (disable:4244)

//#define PI 3.1415926536

SUIComponent::SUIComponent(SUIScreen* screen)
{
	isDisplay = true;
	isAbsoluteRender = true;
	screenBelongsTo = screen;
}


SUIComponent::~SUIComponent(void)
{
}

int SUIComponent::GetWidth() 
{ 
	return properties.rectangle.Width; 
}

void SUIComponent::SetWidth(int setWidth)
{
	if (setWidth < 0)
	{
		return;
	}

	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.rectangle.Width = setWidth;
	}
	else
	{
		properties.rectangle.Width = setWidth;
	}	
}

int SUIComponent::GetHeight()
{
	return properties.rectangle.Height;
}

void SUIComponent::SetHeight(int setHeight)
{
	if (setHeight < 0)
	{
		return;
	}

	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.rectangle.Height = setHeight;
	}
	else
	{
		properties.rectangle.Height = setHeight;
	}
}

D3DXVECTOR2 SUIComponent::GetPosition() 
{ 
	return D3DXVECTOR2(properties.rectangle.X, properties.rectangle.Y); 
}

void SUIComponent::SetPosition(D3DXVECTOR2 pos)
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.rectangle.X = pos.x;
		targetProperties.rectangle.Y = pos.y;
	}
	else
	{
		properties.rectangle.X = pos.x;
		properties.rectangle.Y = pos.y;
	}
}

D3DXVECTOR2 SUIComponent::GetRotationCenter() 
{ 
	return properties.rotationCenter;
}

void SUIComponent::SetRotationCenter(D3DXVECTOR2 pos)
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.rotationCenter.x = pos.x;
		targetProperties.rotationCenter.y = pos.y;
	}
	else
	{
		properties.rotationCenter.x = pos.x;
		properties.rotationCenter.y = pos.y;
	}
}

float SUIComponent::GetRotation()
{
	return properties.rotation;
}

void SUIComponent::SetRotation( float setRotation )
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.rotation = setRotation;
	}
	else
	{
		properties.rotation = setRotation;
	}	
}

SPEngine::SPTexturePtr SUIComponent::GetBackgroundImage()
{
	return properties.backgroundImage;
}

void SUIComponent::SetBackgroundImage( SPTexturePtr setImage )
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.backgroundImage = setImage;
	}

	properties.backgroundImage = setImage;
}

D3DCOLOR SUIComponent::GetBackgroundColor()
{
	return properties.backgroundColor;
}

void SUIComponent::SetBackgroundColor( D3DCOLOR setColor )
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.backgroundColor = setColor;
	}
	else
	{
		properties.backgroundColor = setColor;
	}
}


SPString SUIComponent::GetName()
{
	return name;
}

void SUIComponent::SetName( SPString setName )
{
	modificationLock.Lock();
	name = setName;
	modificationLock.Unlock();
}

void SUIComponent::UpdateAnimation( float timeDelta )
{
	// Update animation position.
	if (animations.size() > 0)
	{
		animations.front()->Update(timeDelta);
		bool isUpdateCompleted = animations.front()->TransitionPosition() >= 1;	
		properties = animations.front()->GetCurrentPoint();

		if (isUpdateCompleted)
		{
			SUIAnimationPtr lastAnimation = animations.front();
			animations.pop_front();

			// Set current state as the start point of next animation.
			if (animations.size() > 0)
			{
				animations.front()->SetStartPoint(properties);
				animations.front()->Play();
			}
		}
	}
}

void SUIComponent::SetRenderTarget( SPTexturePtr setTarget )
{
	modificationLock.Lock();
	renderTarget = setTarget;
	modificationLock.Unlock();
}

void SUIComponent::AddEffect( SUIEffectPtr setEffect )
{
	modificationLock.Lock();
	effects.push_back(setEffect);
	modificationLock.Unlock();
}

void SUIComponent::AddAnimation( SUIAnimationPtr setAnimation )
{
	modificationLock.Lock();
	animations.push_back(setAnimation);
	modificationLock.Unlock();
}

float SUIComponent::GetTransparency()
{
	return properties.transparency;
}

void SUIComponent::SetTransparency( float setTrans )
{
	modificationLock.Lock();
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.transparency = setTrans;
	}
	else
	{
		properties.transparency = setTrans;
	}	
	modificationLock.Unlock();
}

void SUIComponent::UpdateEffect( float timeDelta )
{
	// Update animation position.
	if (effects.size() > 0)
	{
		while(effects.size() > 0 && !effects.front())
		{
			modificationLock.Lock();
			effects.pop_front();
			modificationLock.Unlock();
		}

		if (effects.size() > 0)
		{
			effects.front()->Play();
			effects.front()->Update(timeDelta);

			bool isUpdateCompleted = effects.front()->TransitionPosition() >= 1;

			if (isUpdateCompleted)
			{
				SUIEffectPtr lastEffect = effects.front();			

				// Set current state as the start point of next animation.
				if (effects.size() > 1)
				{
					modificationLock.Lock();
					effects.pop_front();
					modificationLock.Unlock();
				}
			}
		}
		
	}
}

SUIProperties SUIComponent::GetProperties()
{
	return properties;
}

void SUIComponent::PlayAnimation()
{
	if (animations.size() > 0)
	{
		animations.front()->Play();
	}
}

float SUIComponent::GetLayer()
{
	return properties.layer;
}

void SUIComponent::SetLayer( float setLayer )
{
	if(setLayer > MaxLayer)
	{
		setLayer = MaxLayer;
	}

	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.layer = setLayer;
	}

	modificationLock.Lock();
	properties.layer = setLayer;
	modificationLock.Unlock();
}

void SUIComponent::SetProperties( SUIProperties setProperties )
{
	modificationLock.Lock();
	properties = setProperties;
	modificationLock.Unlock();
}

void SUIComponent::AddChild( SUIComponentPtr newChild )
{
	ChildIterator iter = children.begin();

	if (iter == children.end())
	{
		children.push_back(newChild);
		return;
	}

	ChildIterator iterNext = iter;
	iterNext++;

	if (newChild->GetLayer() < (*iter)->GetLayer())
	{
		children.push_front(newChild);
	}
	else
	{
		while(iterNext != children.end())
		{
			if ((*iter)->GetLayer() <= newChild->GetLayer()	&& newChild->GetLayer() < (*iterNext)->GetLayer())
			{
				break;
			}

			iter++;
			iterNext++;
		}

		children.insert(iterNext, newChild);
	}
}

void SUIComponent::InsertBefore( SUIComponentPtr newChild, SUIComponentPtr child )
{
	ChildIterator iter = children.begin();
	while(iter != children.end())
	{
		if (*iter == child)
		{
			break;
		}
		iter++;
	}
	children.insert(iter, newChild);
}

void SUIComponent::RemoveChild( SUIComponentPtr setChild )
{
	children.remove(setChild);
}

void SUIComponent::PlayEffect()
{
	if (effects.size() > 0)
	{
		while(effects.size() > 0 && !effects.front())
		{
			modificationLock.Lock();
			effects.pop_front();
			modificationLock.Unlock();
		}
		
		if (effects.size() > 0)
		{
			effects.front()->Play();
		}
	}	
}

SPEngine::SPTexturePtr SUIComponent::GetComponentTexture()
{
	return renderTarget;
}

SUIEffectPtr SUIComponent::GetCurrentEffect()
{
	if (effects.size() == 0)
	{
		modificationLock.Lock();
		effects.push_back(NULL);
		modificationLock.Unlock();
	}

	return effects.front();
}

void SUIComponent::Render( float timeDelta )
{
	if (State() == Hidden)
	{
		return;
	}

	PreDraw();
	Draw(timeDelta);
	PostDraw();
}

void SUIComponent::SetPositionX( int setX )
{
	modificationLock.Lock();
	properties.rectangle.X = setX;
	modificationLock.Unlock();
}

void SUIComponent::SetPositionY( int setY )
{
	modificationLock.Lock();
	properties.rectangle.Y = setY;
	modificationLock.Unlock();
}

void SUIComponent::SetRotationCenterX( int setX )
{
	modificationLock.Lock();
	properties.rotationCenter.x = setX;
	modificationLock.Unlock();
}

void SUIComponent::SetRotationCenterY( int setY )
{
	modificationLock.Lock();
	properties.rotationCenter.y = setY;
	modificationLock.Unlock();
}

SUIProperties SUIComponent::GetTargetProperties()
{
	if (animations.size() == 0)
	{
		return GetProperties();
	}

	return animations.back()->GetTargetPoint();
}

void SUIComponent::SetFather( SUIComponentPtr setFather )
{
	modificationLock.Lock();
	father = setFather;
	modificationLock.Unlock();
}

SUIComponentPtr SUIComponent::GetFather()
{
	return father;
}

SRectangle SUIComponent::GetBackgroundRect()
{
	if (!properties.backgroundImage)
	{
		return properties.rectangle;
	}

	SRectangle rect;
	int imageWidth = properties.backgroundImage->GetWidth();
	int imageHeight = properties.backgroundImage->GetHeight();
	int boxWidth = properties.rectangle.Width;
	int boxHeight = properties.rectangle.Height;

	if (properties.backgroundMode == SUIProperties::Positioning)
	{
		rect.Width = imageWidth;
		rect.Height = imageHeight;

		switch(properties.backgroundPosition)
		{
		case SUIProperties::TopLeft:
			rect.X = 0;
			rect.Y = 0;
			break;

		case SUIProperties::TopRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = 0;
			break;

		case SUIProperties::TopCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = 0;
			break;

		case SUIProperties::BottomLeft:
			rect.X = 0;
			rect.Y = boxHeight - imageHeight;
			break;

		case SUIProperties::BottomRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = boxHeight - imageHeight;
			break;

		case SUIProperties::BottomCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = boxHeight - imageHeight;
			break;

		case SUIProperties::CenterLeft:
			rect.X = 0;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case SUIProperties::CenterRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case SUIProperties::CenterAll:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		default:
			rect.X = properties.backgroundX;
			rect.Y = properties.backgroundY;
			break;
		}

		return rect;
	}

	switch(properties.backgroundMode)
	{
	case SUIProperties::Fill:
		rect = properties.rectangle;
		rect.X = 0;
		rect.Y = 0;
		break;

	case SUIProperties::FitWidth:
		rect.Width = boxWidth;
		rect.Height = (float)boxWidth / imageWidth * imageHeight;
		rect.X = 0;
		rect.Y = (boxHeight - rect.Height) / 2;
		break;

	case SUIProperties::FitHeight:
		rect.Width = (float)boxHeight / imageHeight * imageWidth;
		rect.Height = boxHeight;
		rect.X = (boxWidth - rect.Width) / 2;
		rect.Y = 0;
		break;

	case SUIProperties::FitMin:
		if ((float)boxWidth / imageWidth < 
			(float)boxHeight / imageHeight)
		{
			rect.Width = boxWidth;
			rect.Height = (float)boxWidth / imageWidth * imageHeight;
			rect.X = 0;
			rect.Y = (boxHeight - rect.Height) / 2;
		}
		else
		{
			rect.Width = (float)boxHeight / imageHeight * imageWidth;
			rect.Height = boxHeight;
			rect.X = (boxWidth - rect.Width) / 2;
			rect.Y = 0;
		}
		break;

	case SUIProperties::FitMax:
		if ((float)boxWidth / imageWidth > 
			(float)boxHeight / imageHeight)
		{
			rect.Width = boxWidth;
			rect.Height = (float)boxWidth / imageWidth * imageHeight;
			rect.X = 0;
			rect.Y = (boxHeight - rect.Height) / 2;
		}
		else
		{
			rect.Width = (float)boxHeight / imageHeight * imageWidth;
			rect.Height = boxHeight;
			rect.X = (boxWidth - rect.Width) / 2;
			rect.Y = 0;
		}
		break;
	}

	return rect;
}

void SUIComponent::SetBackgroundX( int setX )
{
	modificationLock.Lock();
	properties.backgroundX = setX;
	modificationLock.Unlock();
}

void SUIComponent::SetBackgroundY( int setY )
{
	modificationLock.Lock();
	properties.backgroundY = setY;
	modificationLock.Unlock();
}

int SUIComponent::GetBackgroundX()
{
	return properties.backgroundX;
}

int SUIComponent::GetBackgroundY()
{
	return properties.backgroundY;
}

void SUIComponent::SetBackgroundMode( SUIProperties::BackgroundMode setMode )
{
	modificationLock.Lock();
	properties.backgroundMode = setMode;
	modificationLock.Unlock();
}

void SUIComponent::SetBackgroundPositionMode( SUIProperties::BackgroundPosition setMode )
{
	modificationLock.Lock();
	properties.backgroundPosition = setMode;
	modificationLock.Unlock();
}

void SUIComponent::Hide()
{
	modificationLock.Lock();
	isDisplay = false;
	modificationLock.Unlock();
}

void SUIComponent::Unhide()
{
	modificationLock.Lock();
	isDisplay = true;
	state = TransitionOn;
	modificationLock.Unlock();
}

void SUIComponent::SaveAsImage( SPString path )
{
	if (!childTarget)
	{
		return;
	}

	D3DXIMAGE_FILEFORMAT format = D3DXIFF_BMP;

	if (path.substr(path.size() - 4) == L".bmp")
	{
		format = D3DXIFF_BMP;
	}
	else if (path.substr(path.size() - 4) == L".jpg")
	{
		format = D3DXIFF_JPG;
	}
	else if (path.substr(path.size() - 4) == L".pfm")
	{
		format = D3DXIFF_PFM;
	}
	else if (path.substr(path.size() - 4) == L".png")
	{
		format = D3DXIFF_PNG;
	}
	else if (path.substr(path.size() - 4) == L".png")
	{
		format = D3DXIFF_PNG;
	}
	else if (path.substr(path.size() - 4) == L".tga")
	{
		format = D3DXIFF_TGA;
	}
	else if (path.substr(path.size() - 4) == L".dds")
	{
		format = D3DXIFF_DDS;
	}
	else if (path.substr(path.size() - 4) == L".ppm")
	{
		format = D3DXIFF_PPM;
	}
	else if (path.substr(path.size() - 4) == L".dib")
	{
		format = D3DXIFF_DIB;
	}
	else if (path.substr(path.size() - 4) == L".hdr")
	{
		format = D3DXIFF_HDR;
	}
	else
	{		
		path += L".bmp";
	}

	SPPathHelper::MakeSurePathExist(path);

	HRESULT hr = D3DXSaveTextureToFile(path.c_str(), format, childTarget->GetD3DTexture(), NULL);
	if (FAILED(hr))
	{
		SPLogHelper::WriteLog(SPStringHelper::Format("[SUIComponent] ERROR %d: Failed to save component as image.", GetLastError()));
	}
}

SPEngine::SPTexturePtr SUIComponent::SaveAsTexture()
{
	if (!childTarget)
	{
		return NULL;
	}

	SPTexturePtr tex = SPTextureManager::GetSingleton()->CreateRenderTarget(
		childTarget->GetWidth(), childTarget->GetHeight(), properties.backgroundColor);

	SPSpriteManager::GetSingleton()->Render(childTarget, NULL, 0, 0, tex);

	return tex;
}

bool SUIComponent::IsDisplay()
{
	return isDisplay;
}

void SUIComponent::MergerAnimation( SUIAnimationPtr setAnimation )
{
	if (!setAnimation)
	{
		return;
	}

	setAnimation->SetStartPoint(properties);

	modificationLock.Lock();
	animations.clear();
	animations.push_back(setAnimation);
	modificationLock.Unlock();
}

void SUIComponent::ClearEffect()
{
	modificationLock.Lock();
	effects.clear();
	modificationLock.Unlock();
}

float SUIComponent::Depth()
{
	if (isAbsoluteRender && father)
	{
		if (!_depth)
		{
			float base = MaxLayer + 1;
			SUIComponentPtr com = father;

			while(com && com->isAbsoluteRender)
			{
				com = com->father;
				base *= MaxLayer + 2;
			}

			float fatherDepth = father->Depth();

			float depth = fatherDepth  - (properties.layer + 1) / base;

			_depth = new float(depth);
		}

		return *_depth;
	}

	float depth =  (MaxLayer - properties.layer) / MaxLayer;
	return depth;
}

D3DXMATRIX SUIComponent::TransformMatrix()
{
	if (_transformMatrix)
	{
		return *_transformMatrix;
	}

	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(1, 1),
		&properties.rotationCenter,
		properties.rotation, 
		&D3DXVECTOR2(0, 0));

	if (isAbsoluteRender && father)
	{
		if (!_transformMatrix)
		{
			_transformMatrix = new D3DXMATRIX(transformMatrix * father->TransformMatrix());
		}

		return *_transformMatrix;
	}

	return transformMatrix;
}

D3DXMATRIX SUIComponent::TransformMatrixBG()
{
	if (_transformMatrixBG)
	{
		return *_transformMatrixBG;
	}

	D3DXMATRIX transformMatrix;
	SPRectangle bRect = GetBackgroundRect();
	D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionBG().x, PositionBG().y),
		0, 
		&D3DXVECTOR2((float)bRect.Width / properties.backgroundImage->GetWidth(), 
			(float)bRect.Height / properties.backgroundImage->GetHeight()),
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(0, 0));

	if (isAbsoluteRender && father)
	{
		if (!_transformMatrixBG)
		{
			_transformMatrixBG = new D3DXMATRIX(transformMatrix * TransformMatrix());
		}

		return *_transformMatrixBG;
	}

	return transformMatrix;
}

D3DXVECTOR3 SUIComponent::Position()
{
	if (isAbsoluteRender && father)
	{
		if (!_position)
		{
			D3DXVECTOR2 pos = GetPosition();
			D3DXVECTOR2 fatherPos = father->Position();
			_position = new D3DXVECTOR3( pos.x + fatherPos.x, pos.y + fatherPos.y, Depth());
		}
		
		return *_position;
	}

	return D3DXVECTOR3(properties.rectangle.X, properties.rectangle.Y, Depth());
}

D3DXVECTOR3 SUIComponent::PositionBG()
{
	if (isAbsoluteRender && father)
	{
		if (!_positionBG)
		{
			_positionBG = new D3DXVECTOR3(Position().x,	Position().y, CalDepth(0));
		}
		
		return *_positionBG;
	}
	return D3DXVECTOR3(properties.backgroundX, properties.backgroundY, 1);
}

SPTexturePtr SUIComponent::ChildTarget()
{
	if (isAbsoluteRender && father)
	{
		if (!_childTarget)
		{
			_childTarget = father->ChildTarget();
		}
		
		return _childTarget;
	}

	return childTarget;
}

void SUIComponent::SetAbsoluteRender( bool setOn )
{
	modificationLock.Lock();
	isAbsoluteRender = setOn;
	modificationLock.Unlock();
}

float SUIComponent::Alpha()
{
	if (isAbsoluteRender && father)
	{
		if (!_alpha)
		{
			_alpha = new float(father->Alpha() * properties.transparency);
		}

		return *_alpha;
	}

	return 1;
}

SPRectangle SUIComponent::BackgroundSrcRect()
{
	if (isAbsoluteRender)
	{
		if (!_backgroudSrcRect)
		{
			SPRectangle rect = properties.rectangle;
			rect.X = -properties.backgroundX;
			rect.Y = -properties.backgroundY;
			if (rect.Width > properties.backgroundImage->GetWidth())
			{
				rect.Width = properties.backgroundImage->GetWidth();
			}
			if (rect.Height > properties.backgroundImage->GetHeight())
			{
				rect.Height = properties.backgroundImage->GetHeight();
			}

			_backgroudSrcRect = new SPRectangle(rect);
		}
		
		return *_backgroudSrcRect;
	}

	return properties.backgroundImage->SourceRectangle();
}

float SUIComponent::CalDepth( float depth )
{
	if (isAbsoluteRender && father)
	{
		if (!_calDepthBase)
		{
			float base = MaxLayer + 1;
			SUIComponentPtr com = father;

			while(com && com->isAbsoluteRender)
			{
				com = com->father;
				base *= MaxLayer + 2;
			}

			float base2 = base * (MaxLayer + 2);

			_calDepthBase = new float(base2);
		}

		float result = Depth() - ((1 - depth) * (MaxLayer + 1) + 1) / (MaxLayer + 2) / (*_calDepthBase);

		return result;
	}

	return depth;
}

D3DXMATRIX SUIComponent::TransformMatrixColor()
{
	if (_transformMatrixColor)
	{
		return *_transformMatrixColor;
	}

	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionColor().x, PositionColor().y),
		0, 
		&D3DXVECTOR2((float)GetWidth() / 2, (float)GetHeight() / 2),
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(0, 0));

	if (isAbsoluteRender && father)
	{
		if (!_transformMatrixColor)
		{
			D3DXMATRIX fMatrix = TransformMatrix();
			_transformMatrixColor = new D3DXMATRIX(transformMatrix * fMatrix);
		}
		
		return *_transformMatrixColor;
	}

	return transformMatrix;
}

D3DXVECTOR3 SUIComponent::PositionColor()
{
	if (isAbsoluteRender && father)
	{
		if (!_postionColor)
		{
			D3DXVECTOR3 pos = Position();
			_postionColor = new D3DXVECTOR3(pos.x, pos.y, Depth());
		}

		return *_postionColor;
	}
	return D3DXVECTOR3(properties.rectangle.X, properties.rectangle.Y, Depth());
}

void SUIComponent::ClearAbsoluteCache()
{
	_position = NULL;
	_positionBG = NULL;
	_postionColor = NULL;
	_transformMatrix = NULL;
	_transformMatrixColor = NULL;
	_transformMatrixBG = NULL;
	_alpha = NULL;
	_depth = NULL;
	_childTarget = NULL;
	_backgroudSrcRect = NULL;
	_calDepthBase = NULL;
}

bool SUIComponent::IsAbsoluteRender()
{
	return isAbsoluteRender;
}

SUIProperties::BackgroundPosition SUIComponent::GetBackgroundPositionMode()
{
	return properties.backgroundPosition;
}

SUIProperties::BackgroundMode SUIComponent::GetBackgroundMode()
{
	return properties.backgroundMode;
}

Handle<Object> SUIComponent::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetComponentTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}


Handle<Array> SUIComponent::GetV8ChildComponents()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	Handle<Array> array = Array::New();

	ChildIterator iter = children.begin();
	while(iter != children.end())
	{
		array->Set(array->Length(), (*iter)->GetV8Obj());
		iter++;
	}

	return array;
}

void SUIComponent::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	UpdateAnimation(timeDelta);

	UpdateEffect(timeDelta);

	SUIComponent::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		(*iter)->Update(timeDelta);

		iter++;
	}
}

void SUIComponent::PreDraw()
{
	// Create render target to be rendered by children.
	if (!isAbsoluteRender)
	{
		childTarget = SPTextureManager::GetSingleton()->
			CreateRenderTarget(GetWidth(), GetHeight(), properties.backgroundColor);
	}
	else
	{
		childTarget = ChildTarget();
	}

	// A card problem ?
	//childTarget->Fill(properties.backgroundColor);

	SPRectangle destRect = properties.rectangle;
	destRect.X = 0;
	destRect.Y = 0;

	// Render background color and image.
	SPTexturePtr backgroundColorTex = SPTextureManager::GetSingleton()->GetBlankWhiteTexture();	

	//SPSpriteManager::GetSingleton()->RenderOnScreen(backgroundColorTex,
	//	NULL, destRect, properties.backgroundColor, 1, childTarget);
	float alpha = Alpha();
	D3DCOLOR realColor = alpha * (D3DXCOLOR)properties.backgroundColor;

	SPSpriteManager::GetSingleton()->RenderWithMatrix(backgroundColorTex,
		isAbsoluteRender ? GetCurrentEffect() : NULL, TransformMatrixColor(), 
		D3DXVECTOR3(0,0,0), PositionColor(), realColor, childTarget);

	if (properties.backgroundImage)
	{
		D3DXVECTOR3 positionBG = PositionBG();
		//SPSpriteManager::GetSingleton()->RenderOnScreen(properties.backgroundImage,
		//	NULL, GetBackgroundRect(), SPColor::White, 1, childTarget);
		SPSpriteManager::GetSingleton()->RenderWithMatrix(properties.backgroundImage,
			isAbsoluteRender?GetCurrentEffect():NULL, TransformMatrixBG(),
			BackgroundSrcRect().CRect(), D3DXVECTOR3(0,0,0), positionBG, 
			alpha * (D3DXCOLOR)SPColor::White, childTarget);
	}	

	SUIComponent::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->SetRenderTarget(childTarget);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}
}

void SUIComponent::Draw( float timeDelta )
{
	// Render children UI component.
	SUIComponent::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->Render(timeDelta);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}
}

void SUIComponent::PostDraw()
{
	SUIComponent::ChildIterator iter = children.begin();

	while(iter != children.end())
	{
		if (*iter)
		{
			(*iter)->SetRenderTarget(NULL);
			iter++;
		}
		else
		{
			iter = children.erase(iter);
		}
	}

	if (childTarget && !isAbsoluteRender)
	{
		SPSpriteManager::GetSingleton()->RenderWithRotation(
			childTarget, 
			GetCurrentEffect(), 
			D3DXVECTOR3(GetPosition().x, GetPosition().y, Depth()),
			properties.rotationCenter,
			properties.rotation,
			properties.transparency * SPColor::White,
			renderTarget);
	}

	//childTarget = NULL;
}

void SUIComponent::Load()
{
}

void SUIComponent::Unload()
{
	childTarget = NULL;
	renderTarget = NULL;
}

void SUIComponent::Reload()
{
	Load();
}

void SUIComponent::HandleEvent( SUIEventPtr e )
{
	if (!e)
	{
		return;
	}

	if (e->type == SUIEvent::None || !e->returnValue)
	{
		return;
	}

	if(!isDisplay)// || !properties.transparency)
	{
		return;
	}

	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool lastInRect =  properties.rectangle.IsPointInRect(
		e->positionX - e->movementX, e->positionY - e->movementY);

	if (e->type == SUIEvent::MouseMove)
	{
		HandleMouseOut(e);
		HandleMouseOver(e);
		HandleMouseIn(e);
	}
	else
	{
		if (e->type == SUIEvent::KeyDown)
		{
			if (catchKeyDown)
			{
				if(!catchKeyDown->Function(e))
				{
					return;
				}
			}
		}
		else if (e->type == SUIEvent::KeyPress)
		{
			if (catchKeyPress)
			{
				if(!catchKeyPress->Function(e))
				{
					return;
				}
			}
		}
		else if(e->type == SUIEvent::KeyUp)
		{
			if (catchKeyUp)
			{
				if(!catchKeyUp->Function(e))
				{
					return;
				}
			}
		}
		else if (inRect)
		{
			if (e->type == SUIEvent::MouseClick)
			{
				if (catchMouseClick)
				{
					if(!catchMouseClick->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseDClick)
			{
				if (catchMouseDClick)
				{
					if(!catchMouseDClick->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseDown)
			{
				if (catchMouseDown)
				{
					if(!catchMouseDown->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseUp)
			{
				if (catchMouseUp)
				{
					if(!catchMouseUp->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseScroll)
			{
				if (catchMouseScroll)
				{
					if(!catchMouseScroll->Function(e))
					{
						return;
					}
				}
			}
		}
		
		e->positionX -= properties.rectangle.X;
		e->positionY -= properties.rectangle.Y;

		Children::reverse_iterator iter = children.rbegin();

		while(iter != children.rend())
		{
			if (*iter)
			{
				(*iter)->HandleEvent(e);
				if (!e->returnValue)
				{
					return;
				}
			}
			iter++;
		}

		e->positionX += properties.rectangle.X;
		e->positionY += properties.rectangle.Y;

		// On Event

		if (e->type == SUIEvent::KeyDown)
		{
			if (onKeyDown)
			{
				if(!onKeyDown->Function(e))
				{
					return;
				}
			}
		}
		else if (e->type == SUIEvent::KeyPress)
		{
			if (onKeyPress)
			{
				if(!onKeyPress->Function(e))
				{
					return;
				}
			}
		}
		else if(e->type == SUIEvent::KeyUp)
		{
			if (onKeyUp)
			{
				if(!onKeyUp->Function(e))
				{
					return;
				}
			}
		}
		else if (inRect)
		{			
			if (e->type == SUIEvent::MouseClick)
			{
				if (onMouseClick)
				{
					if(!onMouseClick->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseDClick)
			{
				if (onMouseDClick)
				{
					if(!onMouseDClick->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseDown)
			{
				if (onMouseDown)
				{
					if(!onMouseDown->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseUp)
			{
				if (onMouseUp)
				{
					if(!onMouseUp->Function(e))
					{
						return;
					}
				}
			}
			else if (e->type == SUIEvent::MouseScroll)
			{
				if (onMouseScroll)
				{
					if(!onMouseScroll->Function(e))
					{
						return;
					}
				}
			}
		}		
	}
}

void SUIComponent::Skip()
{
	while (animations.size() > 0)
	{
		if (animations.front() && !animations.front()->CanSkip())
		{
			break;
		}
		else if (animations.front() && animations.size() == 1)
		{
			properties = animations.front()->GetTargetPoint();
		}

		animations.pop_front();
	}

	while (effects.size() > 1)
	{
		effects.pop_front();
	}

	if (effects.size() > 0)
	{
		if (effects.back())
		{
			effects.back()->Skip();
		}
		else
		{
			effects.pop_front();
		}		
	}
}

void SUIComponent::LoadFromString( SPString stringStream )
{
}

SPString SUIComponent::SaveAsString()
{
	//SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(), L"SUICC");

	//return result;

	return L"";
}

SUIScreen* SUIComponent::GetScreen()
{
	return screenBelongsTo;
}

Handle<Object> SUIComponent::SaveAsObj()
{
	Handle<Object> result = SPV8ScriptEngine::CopyObject(GetV8Obj());
	Handle<Array> childList = Array::New();

	result->Delete(SPV8ScriptEngine::SPStringToString(L"parent"));

	if(onMouseClick)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onClick"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseClick)->GetHandle()));
	}
	if(onMouseDClick)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onDClick"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseDClick)->GetHandle()));
	}
	if(onMouseDown)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseDown"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseDown)->GetHandle()));
	}
	if(onMouseUp)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseUp"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseUp)->GetHandle()));
	}
	if(onMouseScroll)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseScroll"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseScroll)->GetHandle()));
	}
	if(onMouse)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseOver"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouse)->GetHandle()));
	}
	if(onMouseIn)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseIn"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseIn)->GetHandle()));
	}
	if(onMouseOut)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onMouseOut"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onMouseOut)->GetHandle()));
	}
	if(onKeyPress)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onKeyPress"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onKeyPress)->GetHandle()));
	}
	if(onKeyDown)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onKeyDown"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onKeyDown)->GetHandle()));
	}
	if(onKeyUp)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"onKeyUp"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)onKeyUp)->GetHandle()));
	}

	if(catchMouseClick)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchClick"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseClick)->GetHandle()));
	}
	if(catchMouseDClick)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchDClick"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseDClick)->GetHandle()));
	}
	if(catchMouseDown)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseDown"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseDown)->GetHandle()));
	}
	if(catchMouseUp)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseUp"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseUp)->GetHandle()));
	}
	if(catchMouseScroll)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseScroll"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseScroll)->GetHandle()));
	}
	if(catchMouse)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseOver"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouse)->GetHandle()));
	}
	if(catchMouseIn)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseIn"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseIn)->GetHandle()));
	}
	if(catchMouseOut)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseOut"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchMouseOut)->GetHandle()));
	}
	if(catchKeyPress)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyPress"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchKeyPress)->GetHandle()));
	}
	if(catchKeyDown)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyDown"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchKeyDown)->GetHandle()));
	}
	if(catchKeyUp)
	{
		result->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyUp"), 
			Integer::New(((SUIV8FunctionEventHandlerPtr)catchKeyUp)->GetHandle()));
	}

	ChildIterator iter = children.begin();
	while(iter != children.end())
	{
		childList->Set(childList->Length(), (*iter)->SaveAsObj());
		iter++;
	}
	result->Set(SPV8ScriptEngine::SPStringToString(L"childComponents"), childList);

	return result;
}

void SUIComponent::LoadFromObj( Handle<Object> obj )
{
	if(SV8Function::HasProperty(L"onClick", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onClick", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onClick"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onDClick", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onDClick", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onDClick"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseDown", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseDown", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseDown"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseUp", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseUp", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseUp"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseScroll", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseScroll", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseScroll"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseOver", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseOver", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseOver"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseIn", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseIn", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseIn"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onMouseOut", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onMouseOut", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onMouseOut"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onKeyPress", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onKeyPress", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onKeyPress"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onKeyDown", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onKeyDown", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onKeyDown"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"onKeyUp", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"onKeyUp", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"onKeyUp"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}

	if(SV8Function::HasProperty(L"catchClick", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchClick", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchClick"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchDClick", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchDClick", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchDClick"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseDown", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseDown", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseDown"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseUp", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseUp", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseUp"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseScroll", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseScroll", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseScroll"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseOver", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseOver", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseOver"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseIn", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseIn", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseIn"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchMouseOut", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchMouseOut", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchMouseOut"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchKeyPress", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchKeyPress", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyPress"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchKeyDown", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchKeyDown", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyDown"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}
	if(SV8Function::HasProperty(L"catchKeyUp", obj))
	{
		SV8FunctionHandle handle = SV8Function::GetProperty(L"catchKeyUp", obj)->Int32Value();
		obj->Set(SPV8ScriptEngine::SPStringToString(L"catchKeyUp"), Handle<v8::Function>::Cast(GetScreen()->GetHandler(handle)));
	}

	Handle<Array> childList = Handle<Array>::Cast(obj->Get(SPV8ScriptEngine::SPStringToString(L"childComponents")));

	obj->Delete(SPV8ScriptEngine::SPStringToString(L"childComponents"));

	SPV8ScriptEngine::CoverObject(GetV8Obj(), obj);

	for (int i = 0; i < childList->Length(); i++)
	{
		Handle<Object> childObj = Handle<Object>::Cast(childList->Get(i));

		// Register component before loaded.
		SUIComponentPtr child;
		if(SV8Function::HasProperty(L"type", childObj))
		{
			SPString type = SPV8ScriptEngine::StringToSPString(SV8Function::GetProperty(L"type", childObj)->ToString());

			if (SPStringHelper::EqualsIgnoreCase(type, L"textBox"))
			{
				child = new SUITextBox(GetScreen());
			}
			else if (SPStringHelper::EqualsIgnoreCase(type, L"dialogBox"))
			{
				child = new SUIDialogBox(GetScreen());
			}
			else if (SPStringHelper::EqualsIgnoreCase(type, L"pictureBox"))
			{
				child = new SUIPictureBox(GetScreen());
			}
			else if (SPStringHelper::EqualsIgnoreCase(type, L"scroll"))
			{
				child = new SUIList(GetScreen());
			}
			else
			{
				child = new SUIComponent(GetScreen());
			}
		}
		else
		{
			child = new SUIComponent(GetScreen());
		}
		
		GetScreen()->SetPersistentComponent(child);
		child->LoadFromObj(childObj);

		AddChild(child);
		child->SetFather(GetScreen()->GetPersistentComponent(this));
	}

	return;
}

void SUIComponent::HandleMouseOut( SUIEventPtr e )
{
	if(!isDisplay)
	{
		return;
	}

	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool lastInRect =  properties.rectangle.IsPointInRect(
		e->positionX - e->movementX, e->positionY - e->movementY);

	if ((!inRect || !SPInputManager::GetSingleton()->GetMouse()->IsWithinWindow()) 
			&& lastInRect)
	{
		if (catchMouseOut)
		{
			if(!catchMouseOut->Function(e))
			{
				return;
			}
		}
	}

	// For Children

	e->positionX -= properties.rectangle.X;
	e->positionY -= properties.rectangle.Y;

	Children::reverse_iterator iter = children.rbegin();

	while(iter != children.rend())
	{
		if (*iter)
		{
			(*iter)->HandleMouseOut(e);
			if (!e->returnValue)
			{
				e->positionX += properties.rectangle.X;
				e->positionY += properties.rectangle.Y;
				return;
			}
		}
		iter++;
	}

	e->positionX += properties.rectangle.X;
	e->positionY += properties.rectangle.Y;

	// On Event

	if ((!inRect || !SPInputManager::GetSingleton()->GetMouse()->IsWithinWindow()) 
		&& lastInRect)
	{
		if (onMouseOut)
		{
			if(!onMouseOut->Function(e))
			{
				return;
			}
		}
	}
}

void SUIComponent::HandleMouseOver( SUIEventPtr e )
{
	if(!isDisplay)
	{
		return;
	}

	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool lastInRect =  properties.rectangle.IsPointInRect(
		e->positionX - e->movementX, e->positionY - e->movementY);

	if (inRect && lastInRect)
	{
		if (catchMouse)
		{
			if(!catchMouse->Function(e))
			{
				return;
			}
		}
	}

	// For Children

	e->positionX -= properties.rectangle.X;
	e->positionY -= properties.rectangle.Y;

	Children::reverse_iterator iter = children.rbegin();

	while(iter != children.rend())
	{
		if (*iter)
		{
			(*iter)->HandleMouseOver(e);
			if (!e->returnValue)
			{
				e->positionX += properties.rectangle.X;
				e->positionY += properties.rectangle.Y;
				return;
			}
		}
		iter++;
	}

	e->positionX += properties.rectangle.X;
	e->positionY += properties.rectangle.Y;

	// On Event

	if (inRect && lastInRect)
	{
		if (onMouse)
		{
			if(!onMouse->Function(e))
			{
				return;
			}
		}
	}
}

void SUIComponent::HandleMouseIn( SUIEventPtr e )
{
	if(!isDisplay)
	{
		return;
	}

	bool inRect = properties.rectangle.IsPointInRect(e->positionX, e->positionY);
	bool lastInRect =  properties.rectangle.IsPointInRect(
		e->positionX - e->movementX, e->positionY - e->movementY);

	if (inRect && !lastInRect)
	{
		if (catchMouseIn)
		{
			if(!catchMouseIn->Function(e))
			{
				return;
			}
		}
	}

	// For Children

	e->positionX -= properties.rectangle.X;
	e->positionY -= properties.rectangle.Y;

	Children::reverse_iterator iter = children.rbegin();

	while(iter != children.rend())
	{
		if (*iter)
		{
			(*iter)->HandleMouseIn(e);
			if (!e->returnValue)
			{
				e->positionX += properties.rectangle.X;
				e->positionY += properties.rectangle.Y;
				return;
			}
		}
		iter++;
	}

	e->positionX += properties.rectangle.X;
	e->positionY += properties.rectangle.Y;

	// On Event

	if (inRect && !lastInRect)
	{
		if (onMouseIn)
		{
			if(!onMouseIn->Function(e))
			{
				return;
			}
		}
	}
}


