#include "StdAfx.h"
#include "SUIComponent.h"

#pragma warning (disable:4244)

//#define PI 3.1415926536

SUIComponent::SUIComponent(void)
{
	isDisplay = true;
	isAbsoluteRender = true;
}


SUIComponent::~SUIComponent(void)
{
}

int SUIComponent::GetWidth() 
{ 
	return properties.rectangle.Width; 
}

bool SUIComponent::SetWidth(int setWidth)
{
	if (setWidth < 0)
	{
		return false;
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

	return true;
}

int SUIComponent::GetHeight()
{
	return properties.rectangle.Height;
}

bool SUIComponent::SetHeight(int setHeight)
{
	if (setHeight < 0)
	{
		return false;
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

	return true;
}

D3DXVECTOR2 SUIComponent::GetPosition() 
{ 
	return D3DXVECTOR2(properties.rectangle.X, properties.rectangle.Y); 
}

bool SUIComponent::SetPosition(D3DXVECTOR2 pos)
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

	return true;
}

D3DXVECTOR2 SUIComponent::GetRotationCenter() 
{ 
	return properties.rotationCenter;
}

bool SUIComponent::SetRotationCenter(D3DXVECTOR2 pos)
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

	return true;
}

float SUIComponent::GetRotation()
{
	return properties.rotation;
}

bool SUIComponent::SetRotation( float setRotation )
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

	return true;
}

SPEngine::SPTexturePtr SUIComponent::GetBackgroundImage()
{
	return properties.backgroundImage;
}

bool SUIComponent::SetBackgroundImage( SPTexturePtr setImage )
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.backgroundImage = setImage;
	}

	properties.backgroundImage = setImage;

	return true;
}

D3DCOLOR SUIComponent::GetBackgroundColor()
{
	return properties.backgroundColor;
}

bool SUIComponent::SetBackgroundColor( D3DCOLOR setColor )
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

	return true;
}


SPString SUIComponent::GetName()
{
	return name;
}

bool SUIComponent::SetName( SPString setName )
{
	name = setName;

	return true;
}

bool SUIComponent::UpdateAnimation( float timeDelta )
{
	// Update animation position.
	if (animations.size() > 0)
	{
		bool isUpdateCompleted =  !animations.front()->Update(timeDelta);	
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

	return true;
}

bool SUIComponent::SetRenderTarget( SPTexturePtr setTarget )
{
	renderTarget = setTarget;

	return true;
}

bool SUIComponent::AddEffect( SUIEffectPtr setEffect )
{
	effects.push_back(setEffect);

	return true;
}

bool SUIComponent::AddAnimation( SUIAnimationPtr setAnimation )
{
	animations.push_back(setAnimation);

	return true;
}

float SUIComponent::GetTransparency()
{
	return properties.transparency;
}

bool SUIComponent::SetTransparency( float setTrans )
{
	if (animations.size() > 0 && animations.back())
	{
		SUIProperties targetProperties = animations.back()->GetTargetPoint();
		targetProperties.transparency = setTrans;
	}
	else
	{
		properties.transparency = setTrans;
	}	

	return true;
}

bool SUIComponent::UpdateEffect( float timeDelta )
{
	// Update animation position.
	if (effects.size() > 0)
	{
		while(effects.size() > 0 && !effects.front())
		{
			effects.pop_front();
		}

		if (effects.size() > 0)
		{
			effects.front()->Play();

			bool isUpdateCompleted =  !effects.front()->Update(timeDelta);

			if (isUpdateCompleted)
			{
				SUIEffectPtr lastEffect = effects.front();			

				// Set current state as the start point of next animation.
				if (effects.size() > 1)
				{
					effects.pop_front();
				}
			}
		}
		
	}

	return true;
}

SUIProperties SUIComponent::GetProperties()
{
	return properties;
}

bool SUIComponent::PlayAnimation()
{
	if (animations.size() > 0)
	{
		animations.front()->Play();
	}

	return true;	
}

float SUIComponent::GetLayer()
{
	return properties.layer;
}

bool SUIComponent::SetLayer( float setLayer )
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

	properties.layer = setLayer;

	return true;
}

bool SUIComponent::SetProperties( SUIProperties setProperties )
{
	properties = setProperties;

	return true;
}

bool SUIComponent::AddChild( SUIComponentPtr setChild )
{
	return true;
}

bool SUIComponent::RemoveChild( SUIComponentPtr setChild )
{
	return true;
}

bool SUIComponent::PlayEffect()
{
	if (effects.size() > 0)
	{
		while(effects.size() > 0 && !effects.front())
		{
			effects.pop_front();
		}
		
		if (effects.size() > 0)
		{
			effects.front()->Play();
		}
	}	

	return true;
}

SPEngine::SPTexturePtr SUIComponent::GetComponentTexture()
{
	return renderTarget;
}

SUIEffectPtr SUIComponent::GetCurrentEffect()
{
	if (effects.size() == 0)
	{
		effects.push_back(NULL);
	}

	return effects.front();
}

bool SUIComponent::Render( float timeDelta )
{
	if (State() == Hidden)
	{
		return false;
	}

	PreDraw();
	Draw(timeDelta);
	PostDraw();

	return true;
}

bool SUIComponent::SetPositionX( int setX )
{
	properties.rectangle.X = setX;

	return true;
}

bool SUIComponent::SetPositionY( int setY )
{
	properties.rectangle.Y = setY;

	return true;
}

bool SUIComponent::SetRotationCenterX( int setX )
{
	properties.rotationCenter.x = setX;

	return true;
}

bool SUIComponent::SetRotationCenterY( int setY )
{
	properties.rotationCenter.y = setY;

	return true;
}

SUIProperties SUIComponent::GetTargetProperties()
{
	if (animations.size() == 0)
	{
		return GetProperties();
	}

	return animations.back()->GetTargetPoint();
}

bool SUIComponent::SetFather( SUIComponentPtr setFather )
{
	father = setFather;

	return true;
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

		case SUIProperties::CengerRight:
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

bool SUIComponent::SetBackgroundX( int setX )
{
	properties.backgroundX = setX;

	return true;
}

bool SUIComponent::SetBackgroundY( int setY )
{
	properties.backgroundY = setY;

	return true;
}

int SUIComponent::GetBackgroundX()
{
	return properties.backgroundX;
}

int SUIComponent::GetBackgroundY()
{
	return properties.backgroundY;
}

bool SUIComponent::SetBackgroundMode( SUIProperties::BackgroundMode setMode )
{
	properties.backgroundMode = setMode;

	return true;
}

bool SUIComponent::SetBackgroundPositionMode( SUIProperties::BackgroundPosition setMode )
{
	properties.backgroundPosition = setMode;

	return true;
}

bool SUIComponent::Hide()
{
	isDisplay = false;

	return true;
}

bool SUIComponent::Unhide()
{
	isDisplay = true;

	state = TransitionOn;

	return true;
}

bool SUIComponent::SetProperties( VariableMap args )
{
	for(VariableMap::iterator iter = args.begin();
		iter != args.end(); iter++)
	{
		propertiesMap[iter->first] = iter->second;
	}

	return true;
}

SPString SUIComponent::PropertiesToString()
{
	SPString result = L"";

	VariableMap::iterator iter = propertiesMap.begin();

	while(iter != propertiesMap.end())
	{
		if (iter->first.size() < 5 
			|| iter->first.find(L"delta") == SPString::npos)
		{
			result += L"<P>";

			result += L"<N>";
			result += iter->first;
			result += L"</N>";

			result += L"<T>";
			result += SPStringHelper::ToWString((int)iter->second.type);
			result += L"</T>";

			result += L"<V>";
			result += iter->second.value;
			result += L"</V>";

			result += L"</P>";
		}
		
		iter++;
	}

	return result;
}

bool SUIComponent::SaveAsImage( SPString path )
{
	if (!childTarget)
	{
		return true;
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

	D3DXSaveTextureToFile(path.c_str(), format, childTarget->GetD3DTexture(), NULL);

	return true;
}

SPEngine::SPTexturePtr SUIComponent::SaveAsTexture()
{
	if (!childTarget)
	{
		return NULL;
	}

	SPTexturePtr tex = SPTextureManager::GetSingleton().CreateRenderTarget(
		childTarget->GetWidth(), childTarget->GetHeight(), properties.backgroundColor);

	SPSpriteManager::GetSingleton().Render(childTarget, NULL, 0, 0, tex);

	return tex;
}

bool SUIComponent::IsDisplay()
{
	return isDisplay;
}

bool SUIComponent::MergerAnimation( SUIAnimationPtr setAnimation )
{
	if (!setAnimation)
	{
		return false;
	}

	setAnimation->SetStartPoint(properties);

	animations.clear();

	animations.push_back(setAnimation);

	return true;
}

bool SUIComponent::ClearEffect()
{
	effects.clear();

	return true;
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

bool SUIComponent::SetAbsoluteRender( bool setOn )
{
	isAbsoluteRender = setOn;

	return true;
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
