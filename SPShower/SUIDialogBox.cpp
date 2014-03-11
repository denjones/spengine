#include "StdAfx.h"
#include "SUIDialogBox.h"
#include "SV8ScriptManager.h"

#pragma warning(disable:4244)
#pragma warning(disable:4129)

SUIDialogBox::SUIDialogBox(SUIScreen* screen) : SUITextBox(screen)
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

	modificationLock.Lock();
	isHasTextToAdd = false;
	modificationLock.Unlock();

	if (CurrentLine()->size() != 0)
	{
		Next();
	}	

	modificationLock.Lock();
	textsToPush.push_back(text);
	modificationLock.Unlock();

	return true;
}

bool SUIDialogBox::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	Clean();

	elapsedLastAddTime += timeDelta;

	if (textsToPush.size() == 0)
	{
		modificationLock.Lock();

		waitingNextPage = true;

		if (nextLine)
		{
			nextLine = false;
		}

		modificationLock.Unlock();

		return true;
	}

	if (elapsedLastAddTime > 1.0 / displaySpeed || nextLine)
	{
		if (!nextLine)
		{
			modificationLock.Lock();

			waitingNextLine = false;
			waitingNextPage = false;

			SUIText characterToPush = textsToPush.front();

			characterToPush.text = characterToPush.text.substr(0,1);	

			// Wait for next line signal.
			if (characterToPush.text == L"\n"
				|| characterToPush.text == L"\t")
			{
				waitingNextLine = true;
				modificationLock.Unlock();
				return true;
			}

			if (characterToPush.text == L"\f")
			{
				waitingNextPage = true;
				modificationLock.Unlock();
				return true;
			}

			modificationLock.Unlock();

			// Push new character.
			//texts.push_back(characterToPush);
			SUITextBox::AddText(characterToPush);

			modificationLock.Lock();

			// Remove the character.
			textsToPush.front().text = textsToPush.front().text.substr(1);

			// Remove empty text.
			if (textsToPush.front().text.size() == 0)
			{
				textsToPush.pop_front();
			}

			modificationLock.Unlock();
		}		
		else
		{
			if (!waitingNextLine && !waitingNextPage)
			{
				// Forward to line change or end of text.
				while(textsToPush.size() > 0)
				{
					modificationLock.Lock();

					SUIText characterToPush = textsToPush.front();

					characterToPush.text = characterToPush.text.substr(0,1);	

					if (characterToPush.text == L"\n" || characterToPush.text == L"\t")
					{
						waitingNextLine = true;
						modificationLock.Unlock();
						break;
					}

					if (characterToPush.text == L"\f")
					{
						waitingNextPage = true;
						modificationLock.Unlock();
						break;
					}

					modificationLock.Unlock();

					// Push new character.
					//texts.push_back(characterToPush);
					SUITextBox::AddText(characterToPush);

					modificationLock.Lock();

					// Remove the character.
					textsToPush.front().text = textsToPush.front().text.substr(1);

					// Remove empty text.
					if (textsToPush.front().text.size() == 0)
					{
						textsToPush.pop_front();
					}

					modificationLock.Unlock();
				}
			}
			else
			{
				modificationLock.Lock();

				waitingNextLine = false;
				waitingNextPage = false;

				modificationLock.Unlock();

				SUIText characterToPush = textsToPush.front();

				characterToPush.text = characterToPush.text.substr(0,1);	

				if (characterToPush.text == L"\f")
				{
					// Next page
					SUITextBox::Clear();
				}
				else if (characterToPush.text == L"\t")
				{
					// Nothing
				}
				else
				{
					// Push new character.
					//texts.push_back(characterToPush);
					SUITextBox::AddText(characterToPush);
				}				

				modificationLock.Lock();

				// Remove the character.
				textsToPush.front().text = textsToPush.front().text.substr(1);

				// Remove empty text.
				if (textsToPush.front().text.size() == 0)
				{
					textsToPush.pop_front();
				}				

				modificationLock.Unlock();
			}
		}

		if (nextLine)
		{
			modificationLock.Lock();
			nextLine = false;
			modificationLock.Unlock();
		}

		elapsedLastAddTime = 0;
	}

	return true;
}

bool SUIDialogBox::SetSpeed( float setSpeed )
{
	modificationLock.Lock();
	displaySpeed = setSpeed;
	modificationLock.Unlock();
	return true;
}

float SUIDialogBox::GetSpeed()
{
	return displaySpeed;
}

bool SUIDialogBox::Next()
{
	modificationLock.Lock();
	nextLine = true;
	modificationLock.Unlock();
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
	modificationLock.Lock();
	nextLineTex = setTex;
	modificationLock.Unlock();
	return true;
}

bool SUIDialogBox::SetNextPageTex( SPTexturePtr setTex )
{
	modificationLock.Lock();
	nextPageTex = setTex;
	modificationLock.Unlock();
	return true;
}

bool SUIDialogBox::Clear()
{
	Clean();
	SUITextBox::Clear();

	modificationLock.Lock();
	isHasTextToClear = false;
	modificationLock.Unlock();

	if (textsToPush.size() == 0 && CurrentLine()->size() == 0)
	{
		return true;
	}

	modificationLock.Lock();
	textsToPush.push_back(SUIText(L"\f"));	
	modificationLock.Unlock();

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
	SPString currentContent = GetContent();

	SUITextList::iterator tIter = textsToPush.begin();

	while (tIter != textsToPush.end())
	{
		currentContent += tIter->text;

		tIter++;
	}

	propertiesMap[L"content"] = KSValue(currentContent, 70);

	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIDB");

	return result;
}

bool SUIDialogBox::ForceClear()
{
	modificationLock.Lock();
	textsToPush.clear();
	modificationLock.Unlock();

	Clear();

	return true;
}

bool SUIDialogBox::ForceAddText( SUIText text )
{
	SUITextBox::AddText(text);

	return true;
}

bool SUIDialogBox::Skip()
{
	SUIComponent::Skip();

	modificationLock.Lock();

	// Forward to line change or end of text.
	while(textsToPush.size() > 0)
	{
		SUIText characterToPush = textsToPush.front();

		characterToPush.text = characterToPush.text.substr(0,1);	

		if (characterToPush.text == L"\f")
		{
			SUITextBox::Clear();
			characterToPush.text = L"";
			waitingNextPage = true;			
		}
		else
		{
			// Push new character.
			//texts.push_back(characterToPush);
			SUITextBox::AddText(characterToPush);
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

	modificationLock.Unlock();

	return true;
}

bool SUIDialogBox::Clean()
{
	if(lines.size() == 1 && CurrentLine()->size() == 1 && CurrentLine()->front()->text.text.size() == 0)
	{
		SUITextBox::Clear();
	}

	if(textsToPush.size() == 1 && textsToPush.front().text.size() == 0)
	{
		modificationLock.Lock();
		textsToPush.clear();
		modificationLock.Unlock();
	}

	return true;
}

bool SUIDialogBox::MarkTextToAdd()
{
	modificationLock.Lock();
	isHasTextToAdd = true;
	isHasTextToClear = false;
	modificationLock.Unlock();
	return true;
}

bool SUIDialogBox::MarkTextToClear()
{
	modificationLock.Lock();
	isHasTextToClear = true;
	isHasTextToAdd = false;
	modificationLock.Unlock();
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
	D3DXVECTOR2 position = CurrentPosition();
	int texPosX = position.x; //  + lastRect.Height * wordSpace;
	int texPosY = position.y;	

	//if(lines.size() == 1 && CurrentLine()->size() == 0)
	//{
	//	texPosY = 0;
	//	texPosX = 0;
	//}

	if (isAbsoluteRender && father)
	{
		D3DXVECTOR3 pos = Position();
		texPosX	+= pos.x;
		texPosY += pos.y;
	}

	return D3DXVECTOR3(texPosX, texPosY, CalDepth(0.1f));
}

Handle<Object> SUIDialogBox::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton().GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton().GetDialogBoxTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}
