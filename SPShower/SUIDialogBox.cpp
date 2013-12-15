#include "StdAfx.h"
#include "SUIDialogBox.h"

#pragma warning(disable:4244)
#pragma warning(disable:4129)

SUIDialogBox::SUIDialogBox(void)
{
	elapsedLastAddTime = 0;
	displaySpeed = 10;
	nextLine = false;
	waitingNextLine = false;
	isHasTextToAdd = false;
	isHasTextToClear = false;
}


SUIDialogBox::~SUIDialogBox(void)
{
}

bool SUIDialogBox::AddText( SUIText text )
{
	Clean();

	isHasTextToAdd = false;

	//if (textsToPush.size() == 0 && texts.size() != 0)
	//{
	//	textsToPush.push_back(SUIText(L"\t"));
	//}	

	if (texts.size() != 0)
	{
		Next();
	}	

	textsToPush.push_back(text);

	return true;
}

bool SUIDialogBox::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	Clean();

	elapsedLastAddTime += timeDelta;

	if (textsToPush.size() == 0)
	{
		waitingNextPage = true;

		if (nextLine)
		{
			nextLine = false;
		}

		return true;
	}

	if (elapsedLastAddTime > 1.0 / displaySpeed || nextLine)
	{
		if (!nextLine)
		{
			waitingNextLine = false;
			waitingNextPage = false;

			SUIText characterToPush = textsToPush.front();

			characterToPush.text = characterToPush.text.substr(0,1);	

			// Wait for next line signal.
			if (characterToPush.text == L"\n"
				|| characterToPush.text == L"\t")
			{
				waitingNextLine = true;
				return true;
			}

			if (characterToPush.text == L"\f")
			{
				waitingNextPage = true;
				return true;
			}

			// Push new character.
			texts.push_back(characterToPush);

			// Remove the character.
			textsToPush.front().text = textsToPush.front().text.substr(1);

			// Remove empty text.
			if (textsToPush.front().text.size() == 0)
			{
				textsToPush.pop_front();
			}
		}		
		else
		{
			if (!waitingNextLine && !waitingNextPage)
			{
				// Forward to line change or end of text.
				while(textsToPush.size() > 0)
				{
					SUIText characterToPush = textsToPush.front();

					characterToPush.text = characterToPush.text.substr(0,1);	

					if (characterToPush.text == L"\n"
						|| characterToPush.text == L"\t")
					{
						waitingNextLine = true;
						break;
					}

					if (characterToPush.text == L"\f")
					{
						waitingNextPage = true;
						break;
					}

					// Push new character.
					texts.push_back(characterToPush);

					// Remove the character.
					textsToPush.front().text = textsToPush.front().text.substr(1);

					// Remove empty text.
					if (textsToPush.front().text.size() == 0)
					{
						textsToPush.pop_front();
					}
				}
			}
			else
			{
				waitingNextLine = false;
				waitingNextPage = false;

				SUIText characterToPush = textsToPush.front();

				characterToPush.text = characterToPush.text.substr(0,1);	

				if (characterToPush.text == L"\f")
				{
					// Next page
					texts.clear();
				}
				else if (characterToPush.text == L"\t")
				{
					// Nothing
				}
				else
				{
					// Push new character.
					texts.push_back(characterToPush);
				}				

				// Remove the character.
				textsToPush.front().text = textsToPush.front().text.substr(1);

				// Remove empty text.
				if (textsToPush.front().text.size() == 0)
				{
					textsToPush.pop_front();
				}				
			}
		}

		if (nextLine)
		{
			nextLine = false;
		}

		// Apply.
		ApplyText();		

		elapsedLastAddTime = 0;
	}

	return true;
}

bool SUIDialogBox::SetSpeed( float setSpeed )
{
	displaySpeed = setSpeed;

	return true;
}

float SUIDialogBox::GetSpeed()
{
	return displaySpeed;
}

bool SUIDialogBox::Next()
{
	nextLine = true;

	return true;
}

bool SUIDialogBox::Draw( float timeDelta )
{
	D3DXVECTOR2 pos = Position();

	if (IsShowNextLineTex() && nextLineTex)
	{
		//SPSpriteManager::GetSingleton().Render(nextLineTex, NULL, texPosX, texPosY, Alpha() * SPColor::White, CalDepth(1), childTarget);
		SPSpriteManager::GetSingleton().RenderWithMatrix(nextLineTex,
			NULL, TransformMatrixNext(), D3DXVECTOR3(0,0,0), PositionNext(),
			Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}
	else if (IsShowNextPageTex() && nextPageTex)
	{
		//SPSpriteManager::GetSingleton().Render(nextPageTex, NULL, texPosX, texPosY, Alpha() * SPColor::White, CalDepth(1), childTarget);
		SPSpriteManager::GetSingleton().RenderWithMatrix(nextPageTex,
			NULL, TransformMatrixNext(), D3DXVECTOR3(0,0,0), PositionNext(), 
			Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}


	return SUITextBox::Draw(timeDelta);
}

bool SUIDialogBox::SetNextLineTex( SPTexturePtr setTex )
{
	nextLineTex = setTex;
	
	return true;
}

bool SUIDialogBox::SetNextPageTex( SPTexturePtr setTex )
{
	nextPageTex = setTex;

	return true;
}

bool SUIDialogBox::Clear()
{
	Clean();

	isHasTextToClear = false;

	if (textsToPush.size() == 0 && texts.size() == 0)
	{
		return true;
	}

	textsToPush.push_back(SUIText(L"\f"));	

	return true;
}

bool SUIDialogBox::IsDisplaying()
{
	return (!waitingNextLine && !waitingNextPage);
}

bool SUIDialogBox::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUIDialogBox::SaveAsString()
{
	SPString currentContent;

	SUITextVector::iterator  iter = texts.begin();

	while(iter != texts.end())
	{
		currentContent += iter->text;

		iter++;
	}

	SUITextList::iterator tIter = textsToPush.begin();

	while (tIter != textsToPush.end())
	{
		currentContent += tIter->text;

		tIter++;
	}

	propertiesMap[L"content"] = Value(currentContent, 70);

	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIDB");

	return result;
}

bool SUIDialogBox::ForceClear()
{
	texts.clear();
	textsToPush.clear();
	linesResult.clear();

	return true;
}

bool SUIDialogBox::ForceAddText( SUIText text )
{
	texts.push_back(text);

	return true;
}

bool SUIDialogBox::Skip()
{
	SUIComponentComposite::Skip();

	// Forward to line change or end of text.
	while(textsToPush.size() > 0)
	{
		SUIText characterToPush = textsToPush.front();

		characterToPush.text = characterToPush.text.substr(0,1);	

		if (characterToPush.text == L"\f")
		{
			texts.clear();
			characterToPush.text = L"";
			waitingNextPage = true;			
		}
		else
		{
			// Push new character.
			texts.push_back(characterToPush);
		}	

		// Remove the character.
		if (textsToPush.front().text.size() > 0)
		{
			textsToPush.front().text = textsToPush.front().text.substr(1);
		}		

		// Remove empty text.
		if (textsToPush.front().text.size() == 0)
		{
			textsToPush.pop_front();
		}
	}

	ApplyText();

	return true;
}

bool SUIDialogBox::Clean()
{
	if(texts.size() == 1 && texts.front().text.size() == 0)
	{
		texts.clear();
	}

	if(textsToPush.size() == 1 && textsToPush.front().text.size() == 0)
	{
		textsToPush.clear();
	}

	return true;
}

bool SUIDialogBox::MarkTextToAdd()
{
	isHasTextToAdd = true;
	isHasTextToClear = false;
	return true;
}

bool SUIDialogBox::MarkTextToClear()
{
	isHasTextToClear = true;
	isHasTextToAdd = false;
	return true;
}

bool SUIDialogBox::IsShowNextLineTex()
{
	return (waitingNextLine && textsToPush.size() > 0)  || (textsToPush.size() == 0 && isHasTextToAdd);
}

bool SUIDialogBox::IsShowNextPageTex()
{
	return (waitingNextPage && textsToPush.size() > 0) || (textsToPush.size() == 0 && isHasTextToClear);
}

bool SUIDialogBox::IsDisplayAllDone()
{
	return (textsToPush.size() == 0) && !IsDisplaying();
}

D3DXMATRIX SUIDialogBox::TransformMatrixNext()
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionNext().x , PositionNext().y),
		0, 
		&D3DXVECTOR2(1, 1),
		&D3DXVECTOR2(0, 0),
		0, 
		&D3DXVECTOR2(0, 0));

	if (isAbsoluteRender && father)
	{
		D3DXMATRIX fMatrix = TransformMatrix();
		D3DXMATRIX result = transformMatrix * fMatrix;
		return result;
	}

	return transformMatrix;
}

D3DXVECTOR3 SUIDialogBox::PositionNext()
{
	SRectangle lastRect =  linesResult.back().rect;
	int texPosX = lastRect.CRect().right + lastRect.Height * wordSpace;
	int texPosY = lastRect.CRect().top;	

	if(linesResult.size() == 0)
	{
		texPosY = 0;
		texPosX = 0;
	}

	if (isAbsoluteRender && father)
	{
		D3DXVECTOR3 pos = Position();
		texPosX	+= pos.x;
		texPosY += pos.y;
	}

	return D3DXVECTOR3(texPosX, texPosY, CalDepth(0.1f));
}
