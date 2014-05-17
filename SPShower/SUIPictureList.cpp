#include "StdAfx.h"
#include "SUIPictureList.h"
#include "SScriptHelper.h"


SUIPictureList::SUIPictureList(void)
{
	baseImage = NULL;
	target = NULL;
	mixImages.clear();
}


SUIPictureList::~SUIPictureList(void)
{
}

void SUIPictureList::Draw( float timeDelta )
{
	target = NULL;

	if (!baseImage)
	{
		return;
	}	

	SRectangle texRect;
	texRect.X = 0;
	texRect.Y = 0;
	texRect.Width = baseImage->GetWidth();
	texRect.Height = baseImage->GetHeight();

	if (mixImages.size() == 0)
	{
		target = baseImage;

		return;
	}

	ImageIterator iter = mixImages.begin();	
	
	SPTexturePtr lastTarget = baseImage;

	while(iter != mixImages.end())
	{	
		if (iter->MixMode)
		{
			iter->MixMode->SetTarget(lastTarget);
		}		

		if (iter->Image)
		{
			SPTexturePtr currentTarget = SPTextureManager::GetSingleton()->CreateRenderTarget(
				baseImage->GetWidth(), baseImage->GetHeight(), 0x00000000);

			if (iter->MixMode)
			{
				SPSpriteManager::GetSingleton()->RenderOnScreen(iter->Image,
					iter->MixMode, texRect, SPColor::White, 1, currentTarget );
			}
			else
			{
				SPSpriteManager::GetSingleton()->RenderOnScreen(lastTarget,
					NULL, texRect, SPColor::White, 1, currentTarget );

				SPSpriteManager::GetSingleton()->RenderOnScreen(iter->Image,
					NULL, texRect, SPColor::White, 0, currentTarget );
			}			

			lastTarget = currentTarget;
		}	

		iter++;
	}

	target = lastTarget;
}

void SUIPictureList::SetMixImage( SUIMixImage image)
{
	ImageIterator iter = mixImages.begin();	

	if (mixImages.size() == 0)
	{
		mixImages.push_back(image);
		return;
	}

	ImageIterator nextIter = iter;
	nextIter++;

	while(nextIter != mixImages.end())
	{
		if (image.Layer >= iter->Layer 
			&& image.Layer < nextIter->Layer)
		{
			break;
		}

		iter++;
		nextIter++;
	}

	if (image.Layer == iter->Layer)
	{
		nextIter = mixImages.erase(iter);
	}

	mixImages.insert(nextIter, image);
}

void SUIPictureList::SetBaseImage( SPTexturePtr base )
{
	baseImage = base;
}

SPEngine::SPTexturePtr SUIPictureList::GetTarget()
{
	return target;
}

int SUIPictureList::GetHeight()
{
	if (!baseImage)
	{
		return 0;
	}

	return baseImage->GetHeight();
}

int SUIPictureList::GetWidth()
{
	if (!baseImage)
	{
		return 0;
	}

	return baseImage->GetWidth();
}

void SUIPictureList::SetName( SPString setName )
{
	name = setName;
}

void SUIPictureList::Reload()
{
	Load();
}

void SUIPictureList::Load()
{
}

void SUIPictureList::Unload()
{
	target = NULL;
}

void SUIPictureList::SaveBaseAsFile( SPString path )
{
	D3DXSaveTextureToFile((path+L".bmp").c_str(), D3DXIFF_BMP, baseImage->GetD3DTexture(), NULL);
}

SPString SUIPictureList::GetName()
{
	return name;
}

void SUIPictureList::LoadFromString( SPString stringStream )
{
}

SPString SUIPictureList::SaveAsString()
{
	//SPString result;

	//result += SPStringHelper::XMLSurroundWith(SScriptHelper::VariablesToString(properties), L"Properties");

	//result += L"<MPS>";

	//ImageIterator iter = mixImages.begin();

	//while(iter != mixImages.end())
	//{
	//	result += iter->SaveAsString();

	//	iter++;
	//}

	//result += L"</MPS>";

	//result = SPStringHelper::XMLSurroundWith(result, L"SUIPL");

	//return result;

	return L"";
}

