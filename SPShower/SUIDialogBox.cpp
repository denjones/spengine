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

void SUIDialogBox::AddText( SUIText text )
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
}

void SUIDialogBox::Update( float timeDelta )
{
	SPTransition::Update(timeDelta);

	Clean();

	elapsedLastAddTime += timeDelta;

	modificationLock.Lock();

	if (textsToPush.size() == 0)
	{
		waitingNextPage = true;

		if (nextLine)
		{
			nextLine = false;
		}

		modificationLock.Unlock();

		return;
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
				modificationLock.Unlock();
				return;
			}

			if (characterToPush.text == L"\f")
			{
				waitingNextPage = true;
				modificationLock.Unlock();
				return;
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
				}
			}
			else
			{
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
			}
		}

		if (nextLine)
		{
			nextLine = false;
		}

		elapsedLastAddTime = 0;
	}

	modificationLock.Unlock();
}

void SUIDialogBox::SetSpeed( float setSpeed )
{
	modificationLock.Lock();
	displaySpeed = setSpeed;
	modificationLock.Unlock();
}

float SUIDialogBox::GetSpeed()
{
	return displaySpeed;
}

void SUIDialogBox::Next()
{
	modificationLock.Lock();
	nextLine = true;
	modificationLock.Unlock();
}

void SUIDialogBox::Draw( float timeDelta )
{
	D3DXVECTOR2 pos = Position();

	if (IsShowNextLineTex() && nextLineTex)
	{
		//SPSpriteManager::GetSingleton()->Render(nextLineTex, NULL, texPosX, texPosY, Alpha() * SPColor::White, CalDepth(1), childTarget);
		SPSpriteManager::GetSingleton()->RenderWithMatrix(nextLineTex,
			NULL, TransformMatrixNext(), D3DXVECTOR3(0,0,0), PositionNext(),
			Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}
	else if (IsShowNextPageTex() && nextPageTex)
	{
		//SPSpriteManager::GetSingleton()->Render(nextPageTex, NULL, texPosX, texPosY, Alpha() * SPColor::White, CalDepth(1), childTarget);
		SPSpriteManager::GetSingleton()->RenderWithMatrix(nextPageTex,
			NULL, TransformMatrixNext(), D3DXVECTOR3(0,0,0), PositionNext(), 
			Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}


	SUITextBox::Draw(timeDelta);
}

void SUIDialogBox::SetNextLineTex( SPTexturePtr setTex )
{
	modificationLock.Lock();
	nextLineTex = setTex;
	modificationLock.Unlock();
}

void SUIDialogBox::SetNextPageTex( SPTexturePtr setTex )
{
	modificationLock.Lock();
	nextPageTex = setTex;
	modificationLock.Unlock();
}

void SUIDialogBox::Clear()
{
	Clean();
	SUITextBox::Clear();

	modificationLock.Lock();
	isHasTextToClear = false;
	modificationLock.Unlock();

	if (textsToPush.size() == 0 && CurrentLine()->size() == 0)
	{
		return;
	}

	modificationLock.Lock();
	textsToPush.push_back(SUIText(L"\f"));	
	modificationLock.Unlock();
}

bool SUIDialogBox::IsDisplaying()
{
	return (!waitingNextLine && !waitingNextPage);
}

void SUIDialogBox::LoadFromString( SPString stringStream )
{

}

SPString SUIDialogBox::SaveAsString()
{
	//SPString currentContent = GetContent();

	//SUITextList::iterator tIter = textsToPush.begin();

	//while (tIter != textsToPush.end())
	//{
	//	currentContent += tIter->text;

	//	tIter++;
	//}

	//propertiesMap[L"content"] = KSValue(currentContent, 70);

	//SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUIDB");

	//return result;

	return L"";
}

void SUIDialogBox::ForceClear()
{
	modificationLock.Lock();
	textsToPush.clear();
	modificationLock.Unlock();

	Clear();
}

void SUIDialogBox::ForceAddText( SUIText text )
{
	SUITextBox::AddText(text);
}

void SUIDialogBox::Skip()
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
}

void SUIDialogBox::Clean()
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
}

void SUIDialogBox::MarkTextToAdd()
{
	modificationLock.Lock();
	isHasTextToAdd = true;
	isHasTextToClear = false;
	modificationLock.Unlock();
}

void SUIDialogBox::MarkTextToClear()
{
	modificationLock.Lock();
	isHasTextToClear = true;
	isHasTextToAdd = false;
	modificationLock.Unlock();
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
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetDialogBoxTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}
