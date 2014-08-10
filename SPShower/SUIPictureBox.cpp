#include "StdAfx.h"
#include "SUIPictureBox.h"
#include "SV8ScriptManager.h"

#pragma warning(disable : 4244)

SUIPictureBox::SUIPictureBox(SUIScreen* screen) : SUIComponent(screen)
{
	imagePos = D3DXVECTOR2(0,0);
	fillMode = Positioning;
	positionMode = Normal;
	picture = new SUIPictureList();
}


SUIPictureBox::~SUIPictureBox(void)
{
}

void SUIPictureBox::SetMixImage(SUIMixImage image)
{
	modificationLock.Lock();
	picture->SetMixImage(image);
	modificationLock.Unlock();
}

void SUIPictureBox::Draw( float timeDelta )
{
	SRectangle texRect = GetTexRect();

	picture->Draw(timeDelta);

	if (transformation && transformation->State() != Hidden)
	{
		if (targetPicture)
		{
			targetPicture->Draw(timeDelta);
			transformation->SetTarget(targetPicture->GetTarget());
		}		

		//SPSpriteManager::GetSingleton()->RenderOnScreen(picture->GetTarget(),
		//	transformation, texRect, SPColor::White, 1, childTarget );
		SPSpriteManager::GetSingleton()->RenderWithMatrix(picture->GetTarget(),
			transformation, TransformMatrixImage(), ImageSrcRect().CRect(),
			D3DXVECTOR3(0,0,0), PositionImage(), Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}
	else
	{
		//SPSpriteManager::GetSingleton()->RenderOnScreen(picture->GetTarget(),
		//	NULL, texRect, SPColor::White, 1, childTarget );
		SPSpriteManager::GetSingleton()->RenderWithMatrix(picture->GetTarget(),
			NULL, TransformMatrixImage(), ImageSrcRect().CRect(),
			D3DXVECTOR3(0,0,0), PositionImage(), Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}
}

void SUIPictureBox::SetBaseImage( SPTexturePtr base )
{
	modificationLock.Lock();
	picture->SetBaseImage(base);
	modificationLock.Unlock();
}

void SUIPictureBox::SetImagePosition( D3DXVECTOR2 setPos )
{
	modificationLock.Lock();
	imagePos = setPos;
	modificationLock.Unlock();
}

SRectangle SUIPictureBox::GetTexRect()
{
	if (!picture)
	{
		return properties.rectangle;
	}

	SRectangle rect;
	int imageWidth = picture->GetWidth();
	int imageHeight = picture->GetHeight();
	int boxWidth = properties.rectangle.Width;
	int boxHeight = properties.rectangle.Height;

	if (fillMode == Positioning)
	{
		rect.Width = imageWidth;
		rect.Height = imageHeight;

		switch(positionMode)
		{
		case TopLeft:
			rect.X = 0;
			rect.Y = 0;
			break;

		case TopRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = 0;
			break;

		case TopCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = 0;
			break;

		case BottomLeft:
			rect.X = 0;
			rect.Y = boxHeight - imageHeight;
			break;

		case BottomRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = boxHeight - imageHeight;
			break;

		case BottomCenter:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = boxHeight - imageHeight;
			break;

		case CenterLeft:
			rect.X = 0;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case CenterRight:
			rect.X = boxWidth - imageWidth;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		case CenterAll:
			rect.X = (boxWidth - imageWidth) / 2;
			rect.Y = (boxHeight - imageHeight) / 2;
			break;

		default:
			rect.X = imagePos.x;
			rect.Y = imagePos.y;
			break;
		}
		
		return rect;
	}

	switch(fillMode)
	{
	case Fill:
		rect = properties.rectangle;
		rect.X = 0;
		rect.Y = 0;
		break;

	case FitWidth:
		rect.Width = boxWidth;
		rect.Height = (float)boxWidth / imageWidth * imageHeight;
		rect.X = 0;
		rect.Y = (boxHeight - rect.Height) / 2;
		break;

	case FitHeight:
		rect.Width = (float)boxHeight / imageHeight * imageWidth;
		rect.Height = boxHeight;
		rect.X = (boxWidth - rect.Width) / 2;
		rect.Y = 0;
		break;

	case FitMin:
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

	case FitMax:
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

	case ResizeBox:
		properties.rectangle.Width = imageWidth;
		properties.rectangle.Height = imageHeight;
		rect = properties.rectangle;
		rect.X = 0;
		rect.Y = 0;
		break;
	}

	return rect;
} 

void SUIPictureBox::PreDraw()
{
	GetTexRect();
	SUIComponent::PreDraw();
}

void SUIPictureBox::SetPositionMode( ImagePosition setMode )
{
	modificationLock.Lock();
	positionMode = setMode;
	modificationLock.Unlock();
}

void SUIPictureBox::SetFillMode( ImageMode setMode )
{
	modificationLock.Lock();
	fillMode = setMode;
	modificationLock.Unlock();
}

void SUIPictureBox::Transform()
{
	if (transformation)
	{
		transformation->Play();
	}
}

void SUIPictureBox::SetTransformation( SUITransformationPtr setTrans )
{
	transformation = setTrans;
}

void SUIPictureBox::SetTransformationTarget( SUIPictureListPtr setTarget )
{
	targetPicture = setTarget;
}

void SUIPictureBox::Update( float timeDelta )
{
	if(transformation)
	{
		transformation->Update(timeDelta);
		if (transformation->TransitionPosition() >= 1)
		{
			picture = targetPicture;
			transformation = NULL;
			targetPicture = NULL;
		}
	}

	return SUIComponent::Update(timeDelta);
}

void SUIPictureBox::SetPicture( SUIPictureListPtr setPicture )
{
	modificationLock.Lock();
	picture = setPicture;
	modificationLock.Unlock();
}

void SUIPictureBox::Reload()
{
	Load();
}

void SUIPictureBox::Load()
{
	if (targetPicture)
	{
		targetPicture->Load();
	}

	if (picture)
	{
		picture->Load();
	}
}

void SUIPictureBox::Unload()
{
	renderTarget = NULL;
	childTarget = NULL;

	if (targetPicture)
	{
		targetPicture->Unload();
	}

	if (picture)
	{
		picture->Unload();
	}
}

void SUIPictureBox::LoadFromString( SPString stringStream )
{
}

SPString SUIPictureBox::SaveAsString()
{
	//SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIPB");

	//return result;

	return L"";
}

void SUIPictureBox::SetImagePositionX( int setX )
{
	modificationLock.Lock();
	imagePos.x = setX;
	modificationLock.Unlock();
}

void SUIPictureBox::SetImagePositionY( int setY )
{
	modificationLock.Lock();
	imagePos.y = setY;
	modificationLock.Unlock();
}

D3DXMATRIX SUIPictureBox::TransformMatrixImage()
{
	D3DXMATRIX transformMatrix;

	if(picture->GetTarget())
	{
		D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionImage().x, PositionImage().y),
		0, 
		&D3DXVECTOR2((float)GetTexRect().Width / picture->GetTarget()->GetWidth(), 
			(float)GetTexRect().Height / picture->GetTarget()->GetHeight()),
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(0, 0));
	}
	else
	{
		D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionImage().x, PositionImage().y),
		0, 
		&D3DXVECTOR2(1, 1),
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(0, 0));
	}	

	if (isAbsoluteRender && father)
	{
		D3DXMATRIX fMatrix = TransformMatrix();
		D3DXMATRIX result = transformMatrix * fMatrix;
		return result;
	}

	return transformMatrix;
}

D3DXVECTOR3 SUIPictureBox::PositionImage()
{
	if (isAbsoluteRender && father)
	{
		return D3DXVECTOR3(
			Position().x,
			Position().y,
			CalDepth(0));
	}
	return D3DXVECTOR3(GetTexRect().X, GetTexRect().Y, 1);
}

SPEngine::SPRectangle SUIPictureBox::ImageSrcRect()
{
	if (isAbsoluteRender)
	{
		SPRectangle rect = properties.rectangle;
		rect.X = -properties.backgroundX;
		rect.Y = -properties.backgroundY;
		return rect;
	}

	return picture->GetTarget()->SourceRectangle();
}

SPString SUIPictureBox::FillModeToString( ImageMode mode )
{
	if(mode == Positioning)
	{
		return L"position";
	}
	else if (mode == Fill)
	{
		return L"fill";
	}
	else if (mode == FitWidth)
	{
		return L"fitWidth";
	}
	else if (mode == FitHeight)
	{
		return L"fitHeight";
	}
	else if (mode == FitMin)
	{
		return L"fitMin";
	}
	else if (mode == FitMax)
	{
		return L"fitMax";
	}
	else if (mode == ResizeBox)
	{
		return L"resize";
	}

	return L"undefined";
}

SPString SUIPictureBox::PositionModeToString( ImagePosition mode )
{
	if(mode == Normal)
	{
		return L"normal";
	}
	else if (mode == TopLeft)
	{
		return L"topLeft";
	}
	else if (mode == TopRight)
	{
		return L"topRight";
	}
	else if (mode == BottomLeft)
	{
		return L"bottomLeft";
	}
	else if (mode == BottomRight)
	{
		return L"bottomRight";
	}
	else if (mode == BottomCenter)
	{
		return L"bottomCenter";
	}
	else if (mode == CenterLeft)
	{
		return L"centerLeft";
	}
	else if (mode == CenterRight)
	{
		return L"centerRight";
	}
	else if (mode == CenterAll)
	{
		return L"centerAll";
	}

	return L"undefined";
}

SUIPictureBox::ImageMode SUIPictureBox::StringToFillMode( SPString modeName )
{
	if(SPStringHelper::EqualsIgnoreCase(modeName, L"Position"))
	{
		return Positioning;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"Fill"))
	{
		return Fill;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"FitWidth"))
	{
		return FitWidth;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"FitHeight"))
	{
		return FitHeight;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"FitMin"))
	{
		return FitMin;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"FitMax"))
	{
		return FitMax;
	}
	else if (SPStringHelper::EqualsIgnoreCase(modeName, L"Resize"))
	{
		return ResizeBox;
	}

	SPLogHelper::WriteLog(L"[SpeShow] Invalid Image Mode: " + modeName + L". Defaulting to 'Position'.");

	return Positioning;
}

SUIPictureBox::ImagePosition SUIPictureBox::StringToPositionMode( SPString modeName )
{
	if(modeName ==  L"Normal")
	{
		return Normal;
	}
	else if (modeName == L"TopLeft")
	{
		return TopLeft;
	}
	else if (modeName == L"TopRight")
	{
		return TopRight;
	}
	else if (modeName == L"BottomLeft")
	{
		return BottomLeft;
	}
	else if (modeName == L"BottomRight")
	{
		return BottomRight;
	}
	else if (modeName == L"BottomCenter")
	{
		return BottomCenter;
	}
	else if (modeName == L"CenterLeft")
	{
		return CenterLeft;
	}
	else if (modeName == L"CenterRight")
	{
		return CenterRight;
	}
	else if (modeName == L"CenterAll")
	{
		return CenterAll;
	}

	SPLogHelper::WriteLog(L"[SpeShow] Invalid Image Position: " + modeName + L". Defaulting to 'Normal'.");

	return Normal;
}

int SUIPictureBox::GetImagePositionX()
{
	return imagePos.x;
}

int SUIPictureBox::GetImagePositionY()
{
	return imagePos.y;
}

SUIPictureBox::ImagePosition SUIPictureBox::GetPositionMode()
{
	return positionMode;
}

SUIPictureBox::ImageMode SUIPictureBox::GetFillMode()
{
	return fillMode;
}

Handle<Object> SUIPictureBox::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetPictureBoxTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}

Handle<Object> SUIPictureBox::SaveAsObj()
{
	Handle<Object> result = SUIComponent::SaveAsObj();
	result->Set(SPV8ScriptEngine::SPStringToString(L"type"), SPV8ScriptEngine::SPStringToString(L"pictureBox"));
	return result;
}
