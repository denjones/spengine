#include "StdAfx.h"
#include "SUITextBox.h"
#include <vector>
#include "SV8ScriptManager.h"

#pragma warning(disable:4305)
#pragma warning(disable:4018)
#pragma warning(disable:4244)

SUITextBox::SUITextBox(SUIScreen* screen) : SUIComponent(screen)
{
	lineSpace = 0.2;
	wordSpace = 0.3;
	punctuations = L"/.,\';][=-)(*&^%$#@!~`\"?><:}{£¿¡·¡¶¡°£º}{|+¡ª¡ª£©£¨*&¡­¡­%£¤#@£¡~¡¿¡¾¡¯£»¡¢¡££¬";
	defaultColor = SPColor::White;
	defaultBackEffect = NULL;
	defaultFont = SPFontManager::GetSingleton()->GetFont(L"text_box_default");
	isAutoHeight = false;
	isAnonymousFont = false;
	
	if (!defaultFont)
	{
		defaultFont = SPFontManager::GetSingleton()->CreateFont(L"text_box_default",
			20, 0, FW_NORMAL, 10, false, L"ºÚÌå");
	}	

	Clear();
}


SUITextBox::~SUITextBox(void)
{
}

void SUITextBox::AddText( SUIText text )
{
	//
	// Put all texts into one list
	//

	SUITextList characterList;

	if (!text.font)
	{
		text.font = defaultFont;
	}

	for(int i = 0; i < text.text.size(); i++)
	{
		SUIText character = text; // Copy
		character.text = text.text.substr(i, 1).c_str(); 
		characterList.push_back(character);
	}

	if (characterList.size() == 0)
	{
		return;
	}

	SUITextList::iterator currentCharIter = characterList.begin();
	SUITextList::iterator nextCharIter = currentCharIter;
	nextCharIter++;

	//
	// First char of the line exceeded ?!
	//

	if(CurrentLine()->size() == 0 && WillExceeded(CurrentLine()->TestPush(*currentCharIter)) || GetTextRect().Width < 14)
	{
		return;
	}

	modificationLock.Lock();

	try
	{
		//
		// Loop through all characters.
		//

		while(nextCharIter != characterList.end())
		{
			SPString currentChar = currentCharIter->text;
			SPString nextChar = nextCharIter->text;

			SUIText currentAndNext = *currentCharIter;
			currentAndNext.text += nextCharIter->text;

			bool willCurrentExceeded = WillExceeded(CurrentLine()->TestPush(*currentCharIter));
			bool willNextExceeded = WillExceeded(CurrentLine()->TestPush(currentAndNext));
			bool isCurrentPun = IsPunctuation(currentChar);
			bool isNextPun = IsPunctuation(nextChar);
			bool isCurrentAlphabet = IsAlphabet(currentChar);
			bool isNextAlphabet = IsAlphabet(nextChar);

			if (currentChar == L"\n")
			{
				//
				// If next character is punctuation, go to new line
				//

				NewLine();
			}
			else if(
				!willCurrentExceeded && willNextExceeded &&		 
				!isCurrentPun && isNextPun &&
				!isCurrentAlphabet &&
				currentCharIter != characterList.begin())	// Not the first char.
			{
				//
				// Next is exceeded punctuation, go to new line.
				//

				NewLine();
				continue;
			}
			else if(!willCurrentExceeded) 
			{
				// Line width not exceeded. Push new text span into line.
				CurrentLine()->Push(*currentCharIter);

				// Add "-" into English words.

				if(	willNextExceeded &&	isCurrentAlphabet && isNextAlphabet ) 
				{
					SUIText connector = *currentCharIter; // Copy
					connector.text = L"-";
					CurrentLine()->Push(connector);

					NewLine();
				}
			}		
			else if(currentCharIter != characterList.begin())
			{
				//
				// Meets the edge of the rectangle, go to new line
				//

				NewLine();
				continue;
			}		

			nextCharIter++;
			currentCharIter++;
		}

		//
		// Last character.
		//

		if (WillExceeded(CurrentLine()->TestPush(*currentCharIter)) || currentCharIter->text == L"\n")
		{
			NewLine();	
		}

		if(currentCharIter->text != L"\n")
		{
			CurrentLine()->Push(*currentCharIter);
		}

		if (isAutoHeight)
		{
			properties.rectangle.Height = currentPosition.y + CurrentLine()->height + padding.top + padding.bottom;
		}
	}
	catch(exception e)
	{
		modificationLock.Unlock();
		throw e;
	}

	modificationLock.Unlock();
}

void SUITextBox::Clear()
{
	modificationLock.Lock();
	lines.clear();
	currentPosition = D3DXVECTOR2(GetTextRect().X, GetTextRect().Y);
	lines.push_back(new SUITextLine(this->wordSpace, this->defaultFont, currentPosition));
	modificationLock.Unlock();
	//texts.clear();
}


float SUITextBox::GetLineSpace()
{
	return lineSpace;
}

void SUITextBox::SetLineSpace( float setSpace )
{
	modificationLock.Lock();
	lineSpace = setSpace;
	modificationLock.Unlock();
}


SUIPadding SUITextBox::GetPadding()
{
	return padding;
}

void SUITextBox::SetPadding( SUIPadding setPadding )
{
	modificationLock.Lock();
	padding = setPadding;
	modificationLock.Unlock();
}

float SUITextBox::GetPaddingTop()
{
	return padding.top;
}

void SUITextBox::SetPaddingTop( float setTop )
{
	modificationLock.Lock();
	padding.top = setTop;
	modificationLock.Unlock();
}

float SUITextBox::GetPaddingRight()
{
	return padding.right;
}

void SUITextBox::SetPaddingRight( float setRight )
{
	modificationLock.Lock();
	padding.right = setRight;
	modificationLock.Unlock();
}

float SUITextBox::GetPaddingBottom()
{
	return padding.bottom;
}

void SUITextBox::SetPaddingBottom( float setBottom )
{
	modificationLock.Lock();
	padding.bottom = setBottom;
	modificationLock.Unlock();
}

float SUITextBox::GetPaddingLeft()
{
	return padding.left;
}

void SUITextBox::SetPaddingLeft( float setLeft )
{
	modificationLock.Lock();
	padding.left = setLeft;
	modificationLock.Unlock();
}

float SUITextBox::GetWordSpace()
{
	return wordSpace;
}

void SUITextBox::SetWordSpace( float setSpace )
{
	modificationLock.Lock();
	wordSpace = setSpace;
	modificationLock.Unlock();
}

void SUITextBox::Draw( float timeDelta )
{	
	SPTexturePtr textTex = SPTextureManager::GetSingleton()->
		CreateRenderTarget(properties.rectangle.Width,
		properties.rectangle.Height, properties.backgroundColor);

	// A card problem?
	textTex->Fill(SPColorHelper::AlphaColor(0, properties.backgroundColor));

	modificationLock.Lock();

	SUITextBlock::iterator iter;
	D3DXVECTOR2 pos = Position();

	for(iter = lines.begin(); iter != lines.end(); iter++ )
	{
		for (SUITextLine::iterator innerIter = (*iter)->begin(); innerIter != (*iter)->end(); innerIter++ )
		{
			SUIEffectPtr backEffect = (*innerIter)->text.backEffect;

			//if (!backEffect)
			//{
			//	backEffect = defaultBackEffect;
			//}

			if (backEffect)
			{
				SPFontWriter::GetSingleton()->Write(
					(*innerIter)->text.font, backEffect, (*innerIter)->text.text,
					(*innerIter)->position, 
					(*innerIter)->text.color, wordSpace, 0.1, textTex );
			}

			SUIEffectPtr frontEffect = (*innerIter)->text.frontEffect;

			if (!frontEffect)
			{
				frontEffect = defaultFrontEffect;			
			}

			SPFontWriter::GetSingleton()->Write(
				(*innerIter)->text.font, frontEffect, (*innerIter)->text.text,
				(*innerIter)->position, 
				(*innerIter)->text.color, wordSpace, 0, textTex );
		}
	}

	if (defaultBackEffect)
	{
		//SPSpriteManager::GetSingleton()->Render(textTex,	defaultBackEffect, 
		//	PositionTextBG(), Alpha() * SPColor::White, childTarget );
		SPSpriteManager::GetSingleton()->RenderWithMatrix(textTex,
			defaultBackEffect, TransformMatrixText(), D3DXVECTOR3(0,0,0), 
			PositionTextBG(), Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}

	//SPSpriteManager::GetSingleton()->Render(textTex, NULL,
	//	PositionText(), Alpha() * SPColor::White, childTarget );
	SPSpriteManager::GetSingleton()->RenderWithMatrix(textTex,
		NULL, TransformMatrixText(), D3DXVECTOR3(0,0,0), PositionText(), 
		Alpha() * (D3DXCOLOR)SPColor::White, childTarget);

	modificationLock.Unlock();
}

SRectangle SUITextBox::GetTextRect()
{
	SRectangle rect = properties.rectangle;
	rect.X = padding.left;
	rect.Y = padding.top;
	rect.Width -= (padding.left + padding.right);
	rect.Height -= (padding.top + padding.bottom);

	return rect;
}

void SUITextBox::SetDefaultFont( SPFontPtr setFont, bool isAnonymous)
{
	modificationLock.Lock();
	defaultFont = setFont;
	isAnonymousFont = isAnonymous;
	modificationLock.Unlock();
}

void SUITextBox::SetDefaultColor( D3DCOLOR setColor )
{
	modificationLock.Lock();
	defaultColor = setColor;
	modificationLock.Unlock();
}

D3DCOLOR SUITextBox::GetDefaultColor()
{
	return defaultColor;
}

void SUITextBox::SetPunctuations( SPString setPun )
{
	modificationLock.Lock();
	punctuations = setPun;
	modificationLock.Unlock();
}

void SUITextBox::SetDefaultBackEffect(SUIEffectPtr setEffect)
{
	modificationLock.Lock();
	defaultBackEffect = setEffect;
	modificationLock.Unlock();
}

SUIEffectPtr SUITextBox::GetDefaultBackEffect()
{
	return defaultBackEffect;
}

void SUITextBox::SetDefaultFrontEffect( SUIEffectPtr setEffect )
{
	modificationLock.Lock();
	defaultFrontEffect = setEffect;
	modificationLock.Unlock();
}

SUIEffectPtr SUITextBox::GetDefaultFrontEffect()
{
	return defaultFrontEffect;
}

SPEngine::SPFontPtr SUITextBox::GetDefaultFont()
{
	return defaultFont;
}

void SUITextBox::Update( float timeDelta )
{
	SUIComponent::Update(timeDelta);

	if (animations.size() > 0)
	{
		RefreshText();
	}
}

void SUITextBox::LoadFromString( SPString stringStream )
{
}

SPString SUITextBox::SaveAsString()
{
	//SPString currentContent = GetContent();

	//propertiesMap[L"content"] = KSValue(currentContent, 70);

	//SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUITB");

	//return result;

	return L"";
}

D3DXVECTOR3 SUITextBox::PositionText()
{
	if (isAbsoluteRender && father)
	{
		D3DXVECTOR3 pos = Position();
		return D3DXVECTOR3(
			pos.x,
			pos.y,
			CalDepth(0));
	}
	return D3DXVECTOR3(0, 0, 0);
}

D3DXVECTOR3 SUITextBox::PositionTextBG()
{
	if (isAbsoluteRender && father)
	{
		D3DXVECTOR3 pos = Position();
		return D3DXVECTOR3(
			pos.x,
			pos.y,
			CalDepth(0.1));
	}
	return D3DXVECTOR3(0, 0, 1);
}

D3DXMATRIX SUITextBox::TransformMatrixText()
{
	D3DXMATRIX transformMatrix;
	D3DXMatrixTransformation2D(
		&transformMatrix, 
		&D3DXVECTOR2(PositionText().x, PositionText().y),
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

void SUITextBox::NewLine()
{
	currentPosition.y += lines.back()->height * (1 + lineSpace);
	currentPosition.x = GetTextRect().X;
	lines.push_back(new SUITextLine(this->wordSpace, this->defaultFont, currentPosition));
}

D3DXVECTOR2 SUITextBox::CurrentPosition()
{
	return D3DXVECTOR2(CurrentLine()->CurrentPosition().x, currentPosition.y);
}

SUITextLinePtr SUITextBox::CurrentLine()
{
	return lines.back();
}

bool SUITextBox::WillCurrentLineExceeded( float addedLength )
{
	return CurrentLine()->width + addedLength > GetTextRect().Width;
}

bool SUITextBox::WillExceeded(float length)
{
	return length > GetTextRect().Width;
}

bool SUITextBox::IsPunctuation( SPString character )
{
	return punctuations.find_first_of(character) != wstring::npos;
}

bool SUITextBox::IsAlphabet( SPString character )
{
	//string shortStr = (char *) _bstr_t(character.c_str());
	//return shortStr.size() == 1;

	wchar_t wChar = character.front();
	return (wChar >= L'a' && wChar <= L'z' ) || (wChar >= L'A' && wChar <= L'Z');
}

SPString SUITextBox::GetContent()
{
	SPString currentContent;

	for(SUITextBlock::iterator iter = lines.begin(); iter != lines.end(); iter++)
	{
		for (SUITextLine::iterator innerIter = (*iter)->begin(); innerIter != (*iter)->end(); innerIter++)
		{
			currentContent += (*innerIter)->text.text;
		}

		currentContent += L"\n";
	}

	currentContent.pop_back();

	return currentContent;
}

void SUITextBox::RefreshText()
{
	SUITextVector texts;
	for(SUITextBlock::iterator iter = lines.begin(); iter != lines.end(); iter++)
	{
		for (SUITextLine::iterator innerIter = (*iter)->begin(); innerIter != (*iter)->end(); innerIter++)
		{
			texts.push_back((*innerIter)->text);
		}
	}

	SUITextBox::Clear();

	for(SUITextVector::iterator iter = texts.begin(); iter != texts.end(); iter++)
	{
		SUITextBox::AddText((*iter));
	}
}

Handle<Object> SUITextBox::GetV8Obj()
{
	Isolate* isolate = SPV8ScriptEngine::GetSingleton()->GetIsolate();

	if (!v8Obj)
	{
		Local<Object> obj = Handle<Object>();

		Handle<ObjectTemplate> handleTempl = SV8ScriptManager::GetSingleton()->GetTextBoxTemplate();
		obj = handleTempl->NewInstance();

		if(!obj.IsEmpty())
		{
			obj->SetInternalField(0, External::New(this));
			v8Obj = new Persistent<Object>(isolate, obj);
		}
	}

	return Handle<Object>::New(isolate, *v8Obj);
}

bool SUITextBox::IsAutoHeight()
{
	return isAutoHeight;
}

void SUITextBox::SetAutoHeight( bool on )
{
	bool needRefresh = on != isAutoHeight;

	modificationLock.Lock();
	isAutoHeight = on;
	modificationLock.Unlock();

	if (needRefresh)
	{
		RefreshText();
	}
}

void SUITextBox::Unload()
{
	if (isAnonymousFont)
	{
		defaultFont->Unload();
	}
	
	SUIComponent::Unload();
}

void SUITextBox::Reload()
{
	if (isAnonymousFont)
	{
		defaultFont->Reload();
	}

	SUIComponent::Reload();
}

bool SUITextBox::IsAnonymousFont()
{
	return isAnonymousFont;
}

Handle<Object> SUITextBox::SaveAsObj()
{
	Handle<Object> result = SUIComponent::SaveAsObj();
	result->Set(SPV8ScriptEngine::SPStringToString(L"type"), SPV8ScriptEngine::SPStringToString(L"textBox"));
	return result;
}


