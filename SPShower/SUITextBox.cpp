#include "StdAfx.h"
#include "SUITextBox.h"
#include <vector>

#pragma warning(disable:4305)
#pragma warning(disable:4018)
#pragma warning(disable:4244)

SUITextBox::SUITextBox(void)
{
	lineSpace = 0.2;
	wordSpace = 0.3;
	texts.clear();
	padding = D3DXVECTOR4(0,0,0,0);
	punctuations = L"/.,\';][=-)(*&^%$#@!~`\"?><:}{£¿¡·¡¶¡°£º}{|+¡ª¡ª£©£¨*&¡­¡­%£¤#@£¡~¡¿¡¾¡¯£»¡¢¡££¬";
	linesResult.clear();
	defaultColor = SPColor::White;
	defaultBackEffect = NULL;
	defaultFont = SPFontManager::GetSingleton().GetFont(L"text_box_default");
	if (!defaultFont)
	{
		defaultFont = SPFontManager::GetSingleton().CreateFont(L"text_box_default",
			20, 0, FW_NORMAL, 10, false, L"ºÚÌå");
	}	
}


SUITextBox::~SUITextBox(void)
{
}

bool SUITextBox::AddText( SUIText text )
{
	texts.push_back(text);
	//TextWriter();
	return true;
}

bool SUITextBox::Clear()
{
	texts.clear();
	return true;
}

bool SUITextBox::SetLineSpace( float setSpace )
{
	lineSpace = setSpace;
	//TextWriter();
	return true;
}

bool SUITextBox::SetPadding( D3DXVECTOR4 setPadding )
{
	padding = setPadding;
	//TextWriter();
	return true;
}

bool SUITextBox::SetWordSpace( float setSpace )
{
	wordSpace = setSpace;
	//TextWriter();
	return true;
}

bool SUITextBox::ApplyText()
{
	// If no text to write.
	if (texts.size() == 0)
	{
		return true;
	}

	SPString pun = punctuations;
	SRectangle rect = SUITextBox::GetTextRect();	

	// Put the words into one list
	SUITextVector characterList;
	SUITextIterator iter;
	for(iter = texts.begin(); iter != texts.end(); iter++)
	{
		for(int i = 0; i < iter->text.size(); i++)
		{
			SUIText character = *iter;
			character.text = iter->text.substr(i,1).c_str(); 
			characterList.push_back(character);
		}
	}

	if (characterList.size() == 0)
	{
		return true;
	}

	SUITextIterator currentCharIter = characterList.begin();
	SUITextIterator nextCharIter = currentCharIter;
	nextCharIter++;
	SPFontPtr currentFont = currentCharIter->font? currentCharIter->font : defaultFont;

	// Add one line.
	vector<TextBlock> lines;
	vector<float> lineHeight;
	int lineCounter = 0;
	float currentLineWidth = 0;
	float wordSpaceInPixel = 0;
	lines.push_back(TextBlock());
	lineHeight.push_back(0);
	SRectangle currentPosition = rect;

	while(nextCharIter != characterList.end())
	{
		currentFont = currentCharIter->font? currentCharIter->font : defaultFont;

		// Create new line
		if (lines.size() <= lineCounter)
		{
			lines.push_back(TextBlock());
			lineHeight.push_back(0);
		}

		// Get word space.
		SPString currentText = currentCharIter->text;
		
		if(wordSpace != 0)
		{
			wordSpaceInPixel = currentFont->GetTextSize(currentText, wordSpace).y * wordSpace;
		}

		SPString nextText = nextCharIter->text;

		string shortNext = (char *) _bstr_t(nextText.c_str());
		string shortS = (char *) _bstr_t(currentText.c_str());
		setlocale(LC_ALL, "chs");

		// Get current character size.

		float currentCharWidth, currentCharHeight;
		SPString ss = L"a" + currentText + L"a";
		currentCharWidth = currentFont->GetTextSize(ss, wordSpace).x
			- 2 * currentFont->GetTextSize(L"a", wordSpace).x - 2 * wordSpaceInPixel;
		currentCharHeight = currentFont->GetTextSize(ss, wordSpace).y;
		D3DXVECTOR2 currentTextSize(currentCharWidth, currentCharHeight);

		// Get next character size.

		float nextCharWidth, nextCharHeight;
		ss = L"a" + nextText + L"a";
		SPFontPtr nextFont =  nextCharIter->font?  nextCharIter->font: defaultFont;
		nextCharWidth = nextFont->GetTextSize(ss, wordSpace).x
			-2 * currentFont->GetTextSize(L"a", wordSpace).x - 2 * wordSpaceInPixel;
		nextCharHeight = currentFont->GetTextSize(ss, wordSpace).y;
		D3DXVECTOR2 nextTextSize(nextCharWidth, nextCharHeight);

		// If next character is punctuation, go to new line

		if (currentText == L"\n")
		{
			// New line.
			currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
			currentLineWidth = 0;
			currentPosition.X = rect.X;

			// Backup.
			//currentCharIter--;
			//nextCharIter--;
		}
		else if(    currentLineWidth + wordSpaceInPixel + 
				currentCharWidth <= rect.Width				// Line width not exceeded.
			&& currentLineWidth + wordSpaceInPixel + 
				currentCharWidth + wordSpaceInPixel + 
				nextCharWidth > rect.Width					// Next char exceeded.
			&& pun.find_first_of(nextText) != wstring::npos	// Next char is not punctuation
			&& pun.find_first_of(currentText) == wstring::npos // Current char is punctuation
			&& shortS.size() != 1
			&& currentCharIter != characterList.begin())	// Not the first char.
		{
			// New line.
			currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
			currentLineWidth = 0;
			currentPosition.X = rect.X;

			// Backup.
			currentCharIter--;
			nextCharIter--;
		}
		else if(currentLineWidth + wordSpaceInPixel + currentCharWidth <= rect.Width) 
		{
			// Line width not exceeded.
			// Try to write in one line.
			TextSpan textSpan(*currentCharIter, currentPosition);

			// Push new text span into line.
			lines[lineCounter].push_back(textSpan);

			// Update line height.
			if(currentCharHeight > lineHeight[lineCounter])
			{
				lineHeight[lineCounter] = currentCharHeight;
			}

			// Update position and line width.
			currentPosition.X += (currentCharWidth + wordSpaceInPixel);
			currentLineWidth += (currentCharWidth + wordSpaceInPixel);

			// Add "-" into English words.
			int aa = rect.Width - 2 * currentCharWidth - wordSpaceInPixel;
			int bb = rect.Width - currentCharWidth - wordSpaceInPixel;

			if(    currentLineWidth + wordSpaceInPixel + currentCharWidth + wordSpaceInPixel + nextCharWidth > rect.Width // Next char exceeded. 
				&& shortNext.size() == 1
				&& shortS.size() == 1 
				&& currentLineWidth  + wordSpaceInPixel + nextCharWidth <= rect.Width) // Current not exceeded.
			{
				if( nextText != L" "
					&& currentText != L" "
					&& pun.find_first_of(nextText) == wstring::npos 
					&& pun.find_first_of(currentCharIter->text) == wstring::npos)
				{
					SUIText connector = *currentCharIter;
					connector.text = L"-";
					lines[lineCounter].push_back(TextSpan(connector, currentPosition));

					currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
					currentLineWidth = 0;
					currentPosition.X = rect.X;
				}
				else if(currentText == L" " )
				{
					currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
					currentLineWidth = 0;
					currentPosition.X = rect.X;
				}
			}
		}		
		else if(currentCharIter != characterList.begin())
		{
			//meets the edge of the rectagle, go to new line

			currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
			currentLineWidth = 0;
			currentPosition.X = rect.X;
			currentCharIter--;
			nextCharIter--;
		}		

		nextCharIter++;
		currentCharIter++;
	}

	// Last character.

	currentFont = currentCharIter->font? currentCharIter->font : defaultFont;
	SPString ss = L"a" + currentCharIter->text + L"a";
	float lastCharWidth = currentFont->GetTextSize(ss, wordSpace).x
		- 2 * currentFont->GetTextSize(L"a", wordSpace).x - 2 * wordSpaceInPixel;

	if (currentLineWidth + wordSpaceInPixel + lastCharWidth > GetTextRect().Width)
	{
		currentPosition.Y += lineHeight[lineCounter++] * (1 + lineSpace);
		currentPosition.X = rect.X;			
	}

	if(lineCounter >= lines.size())
	{
		lines.push_back(TextBlock());
		lineHeight.push_back(currentFont->GetTextSize(ss, wordSpace).y);		
	}

	lines[lineCounter].push_back(TextSpan(*currentCharIter, currentPosition));

	// Redefine the height of each line

	int maxHeight = 0;
	TextBlock newLines;

	for(int i = 0; i <= lineCounter; i++)
	{
		TextBlock::iterator textIter;
		maxHeight += lineHeight[i];

		int c = 0;
		SPString text = L"";
		SPFontPtr currentFont;
		D3DCOLOR currentColor;
		SUIEffectPtr currentBackEffect;
		SUIEffectPtr currentFrontEffect;
		SRectangle firstPos;

		for(textIter = lines[i].begin(); textIter != lines[i].end(); textIter++ )
		{
			wstring s = textIter->text.text;
			
			SPFontPtr font = textIter->text.font? textIter->text.font:defaultFont;

			if(textIter->rect.Y < maxHeight - font->GetTextSize(s, wordSpace).y)
			{
				textIter->rect.Y = maxHeight - font->GetTextSize(s, wordSpace).y;
			}

			c++;

			//push the words in the same line and font into one list

			if(text == L"")
			{
				text += textIter->text.text;
				currentFont = font;
				currentColor = textIter->text.color;
				currentBackEffect = textIter->text.backEffect;
				currentFrontEffect = textIter->text.frontEffect;
				firstPos = textIter->rect;
				TextBlock::iterator nextTextIter = textIter;
				nextTextIter++;

				// Only one character.
				if (nextTextIter == lines[i].end())
				{
					SUIText a = textIter->text;
					a.text = text;
					a.font = font;
					D3DXVECTOR2 textSize = currentFont->GetTextSize(text, wordSpace);
					firstPos.Height = textSize.y;
					firstPos.Width = textSize.x;
					TextSpan p(a, firstPos);
					newLines.push_back(p);
				}
			}
			else if(font == currentFont
				&& textIter->text.color == currentColor 
				&& textIter->text.backEffect == currentBackEffect 
				&& textIter->text.frontEffect == currentFrontEffect 
				&& c != lines[i].size())
			{
				text += textIter->text.text;
			}
			else if(c == lines[i].size() 
				&& font == currentFont 
				&& textIter->text.color == currentColor
				&& textIter->text.backEffect == currentBackEffect
				&& textIter->text.frontEffect == currentFrontEffect )
			{
				text += textIter->text.text;
				SUIText a = textIter->text;
				a.text = text;
				a.font = font;
				D3DXVECTOR2 textSize = currentFont->GetTextSize(text, wordSpace);				
				firstPos.Height = textSize.y;
				firstPos.Width = textSize.x;
				TextSpan p(a, firstPos);
				newLines.push_back(p);
			}
			else if(c == lines[i].size() && 
				(font != currentFont 
				|| textIter->text.color != currentColor
				|| textIter->text.backEffect != currentBackEffect 
				|| textIter->text.frontEffect != currentFrontEffect ))
			{
				SUIText a = textIter->text;
				a.text = text; 
				a.color = currentColor;
				a.font = currentFont;
				a.backEffect = currentBackEffect;
				a.frontEffect = currentFrontEffect;
				D3DXVECTOR2 textSize = currentFont->GetTextSize(text, wordSpace);				
				firstPos.Height = textSize.y;
				firstPos.Width = textSize.x;
				TextSpan p(a, firstPos);
				newLines.push_back(p);

				text = textIter->text.text;
				currentFont = font;
				currentColor = textIter->text.color;
				currentBackEffect = textIter->text.backEffect;
				currentFrontEffect = textIter->text.frontEffect;
				firstPos = textIter->rect;

				SUIText a1 = textIter->text;
				a1.text = text; 
				a1.font = font;
				textSize = currentFont->GetTextSize(text, wordSpace);				
				firstPos.Height = textSize.y;
				firstPos.Width = textSize.x;
				TextSpan p1(a1, firstPos);
				newLines.push_back(p1);
			}
			else
			{
				SUIText a = textIter->text;
				a.text = text;
				a.color = currentColor;
				a.font = currentFont;
				a.backEffect = currentBackEffect;
				a.frontEffect = currentFrontEffect;
				D3DXVECTOR2 textSize = currentFont->GetTextSize(text, wordSpace);				
				firstPos.Height = textSize.y;
				firstPos.Width = textSize.x;
				TextSpan p(a, firstPos);
				newLines.push_back(p);

				text = textIter->text.text;
				currentFont = font;
				currentColor = textIter->text.color;
				currentBackEffect = textIter->text.backEffect;
				currentFrontEffect = textIter->text.frontEffect;
				firstPos = textIter->rect;
			}
		}
	}

	//linesResult = lines;
	linesResult = newLines;

	return true;
}

bool SUITextBox::Draw( float timeDelta )
{	
	SPTexturePtr textTex = SPTextureManager::GetSingleton().
		CreateRenderTarget(properties.rectangle.Width,
		properties.rectangle.Height, properties.backgroundColor);

	// A card problem?
	textTex->Fill(SPColorHelper::AlphaColor(0, properties.backgroundColor));

	TextBlock::iterator iter;
	D3DXVECTOR2 pos = Position();

	for(iter = linesResult.begin(); iter != linesResult.end(); iter++ )
	{
		SUIEffectPtr backEffect = iter->text.backEffect;

		//if (!backEffect)
		//{
		//	backEffect = defaultBackEffect;
		//}

		if (backEffect)
		{
			SPFontWriter::GetSingleton().Write(
				iter->text.font, backEffect, iter->text.text,
				D3DXVECTOR2(iter->rect.X, iter->rect.Y), 
				iter->text.color, wordSpace, 0.1, textTex );
		}

		SUIEffectPtr frontEffect = iter->text.frontEffect;

		if (!frontEffect)
		{
			frontEffect = defaultFrontEffect;			
		}

		SPFontWriter::GetSingleton().Write(
			iter->text.font, frontEffect, iter->text.text,
			D3DXVECTOR2(iter->rect.X, iter->rect.Y), 
			iter->text.color, wordSpace, 0, textTex );
	}

	if (defaultBackEffect)
	{
		//SPSpriteManager::GetSingleton().Render(textTex,	defaultBackEffect, 
		//	PositionTextBG(), Alpha() * SPColor::White, childTarget );
		SPSpriteManager::GetSingleton().RenderWithMatrix(textTex,
			defaultBackEffect, TransformMatrixText(), D3DXVECTOR3(0,0,0), 
			PositionTextBG(), Alpha() * (D3DXCOLOR)SPColor::White, childTarget);
	}

	//SPSpriteManager::GetSingleton().Render(textTex, NULL,
	//	PositionText(), Alpha() * SPColor::White, childTarget );
	SPSpriteManager::GetSingleton().RenderWithMatrix(textTex,
		NULL, TransformMatrixText(), D3DXVECTOR3(0,0,0), PositionText(), 
		Alpha() * (D3DXCOLOR)SPColor::White, childTarget);

	return true;
}

SRectangle SUITextBox::GetTextRect()
{
	SRectangle rect = properties.rectangle;
	rect.X = padding.w;
	rect.Y = padding.x;
	rect.Width -= (padding.w + padding.y);
	rect.Height -= (padding.x + padding.z);

	return rect;
}

bool SUITextBox::SetDefaultFont( SPFontPtr setFont )
{
	defaultFont = setFont;
	//TextWriter();
	return true;
}

bool SUITextBox::SetDefaultColor( D3DCOLOR setColor )
{
	defaultColor = setColor;
	//TextWriter();
	return true;
}

D3DCOLOR SUITextBox::GetDefaultColor()
{
	return defaultColor;
}

bool SUITextBox::SetPunctuations( SPString setPun )
{
	punctuations = setPun;
	//TextWriter();
	return true;
}

bool SUITextBox::SetDefaultBackEffect(SUIEffectPtr setEffect)
{
	defaultBackEffect = setEffect;
	//TextWriter();
	return true;
}

bool SUITextBox::SetDefaultFrontEffect( SUIEffectPtr setEffect )
{
	defaultFrontEffect = setEffect;
	//TextWriter();
	return true;
}

SPEngine::SPFontPtr SUITextBox::GetDefaultFont()
{
	return defaultFont;
}

bool SUITextBox::Update( float timeDelta )
{
	if (animations.size() > 0)
	{
		ApplyText();
	}

	return SUIComponentComposite::Update(timeDelta);
}

bool SUITextBox::LoadFromString( SPString stringStream )
{
	return true;
}

SPString SUITextBox::SaveAsString()
{
	SPString currentContent;

	SUITextVector::iterator  iter = texts.begin();

	while(iter != texts.end())
	{
		currentContent += iter->text;

		iter++;
	}

	propertiesMap[L"content"] = Value(currentContent, 70);

	SPString result = SPStringHelper::XMLSurroundWith(PropertiesToString(),L"SUITB");

	return result;
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

