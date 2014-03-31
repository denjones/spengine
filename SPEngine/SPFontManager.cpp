//////////////////////////////////////////////////////////////////////////
/// @file		SPFontManager.cpp the header file of SPFontManager class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPFontManager.h"
#include "SPGame.h"
#include "SPDevice.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPFontManager::SPFontManager(void)
	{
		sizeRate = 1.0;
		marginRate = 0.5;
	}

	SPFontManager::~SPFontManager(void)
	{
		vector<HANDLE>::iterator iter = extendedFont.begin();

		while (iter != extendedFont.end())
		{
			RemoveFontMemResourceEx(*iter);
			iter++;
		}
	}

	bool SPFontManager::Reload()
	{
		SPWStringMapIterator<SPFontPtr> iterFont(&fonts);
		for(iterFont.First(); !iterFont.IsDone(); iterFont.Next())
		{
			iterFont.CurrentItem()->Reload();
		}

		return true;
	}

	bool SPFontManager::Unload()
	{
		SPWStringMapIterator<SPFontPtr> iterFont(&fonts);
		for(iterFont.First(); !iterFont.IsDone(); iterFont.Next())
		{
			iterFont.CurrentItem()->Unload();
		}
		return true;
	}

	bool SPFontManager::Initialize()
	{	
		return true;
	}

	SPFontPtr SPFontManager::AddFont(SPString name, SPFontPtr font)
	{
		fonts.Set(name, font);

		return font;
	}

	SPFontPtr SPFontManager::AddFont(
		INT Height,
		UINT Width, 
		UINT Weight,
		UINT MipLevels,
		BOOL Italic,
		SPString pFaceName )
	{
		SPFontPtr newFont = new SPFont(Height, Width, Weight, MipLevels, Italic == TRUE, pFaceName);

		fonts.Set(pFaceName, newFont);

		return newFont;
	}

	SPFontPtr SPFontManager::GetFont(SPString name)
	{
		if (fonts.IsSet(name))
		{
			return fonts[name];
		}

		return NULL;
	}

	SPFontPtr SPFontManager::CreateFont( 
		SPString	name, 
		int		Height, 
		int		Width, 
		int		Weight, 
		int		MipLevels, 
		bool	Italic, 
		SPString	pFaceName )
	{
		SPFontPtr font = new SPFont(Height, Width, Weight,
			MipLevels, Italic, pFaceName);

		fonts.Set(name, font);

		return font;
	}

	bool SPFontManager::SetUpFont( wstring path )
	{
		AddFontResource(path.c_str());
		return true;
	}

	float SPFontManager::GetSizeRate()
	{
		return sizeRate;
	}

	bool SPFontManager::SetSizeRate(float setRate)
	{
		if (setRate <= 0 )
		{
			return false;
		}

		sizeRate = setRate;
		return true;
	}

	float SPFontManager::GetMarginRate()
	{
		return marginRate;
	}

	bool SPFontManager::SetMarginRate( float setRate )
	{
		if (setRate < 0)
		{
			return false;
		}

		marginRate = setRate;

		return true;
	}

	bool SPFontManager::AddExtendedFont( SPString path )
	{
		SPFilePtr file = SPFileManager::GetSingleton()->OpenFile(path);

		if (!file)
		{
			SPLogHelper::WriteLog(L"[SPFont] Warning: Failed to open font file: " + path);
			return false;
		}

		file = SPFileManager::GetSingleton()->OpenFile(path);

		LONGLONG length = file->GetFileLength();
		char* pData = new char[length];
		file->Read(pData, length);

		SPFileManager::GetSingleton()->CloseFile(path);

		DWORD numOfFont;
		HANDLE handle = AddFontMemResourceEx(pData, length, NULL, &numOfFont);

		delete [] pData;
		pData = NULL;

		if (!handle)
		{
			SPLogHelper::WriteLog(L"[SPFont] Warning: Failed to add font: " + path);
			return false;
		}		

		extendedFont.push_back(handle);
		extendedFontPath.push_back(path);

		return true;
	}

	bool SPFontManager::LoadFromString( SPString stringStream )
	{
		SPString sizeRateString = SPStringHelper::XMLExcludeFrom(stringStream, L"SizeRate");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"SizeRate");
		sizeRate = SPStringHelper::StringToFloat(sizeRateString);

		SPString marginRateString = SPStringHelper::XMLExcludeFrom(stringStream, L"MarginRate");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"MarginRate");
		marginRate = SPStringHelper::StringToFloat(marginRateString);

		SPString eFontsString = SPStringHelper::XMLExcludeFrom(stringStream, L"ExtendedFonts");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"ExtendedFonts");
		while(eFontsString.size() > 0)
		{
			SPString eFontString = SPStringHelper::XMLExcludeFrom(eFontsString, L"P");
			eFontsString = SPStringHelper::XMLRemoveFirst(eFontsString, L"P");

			AddExtendedFont(eFontString);
		}

		SPString fontsString = SPStringHelper::XMLExcludeFrom(stringStream, L"Fonts");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Fonts");
		while(fontsString.size() > 0)
		{
			SPString fontString = SPStringHelper::XMLExcludeFrom(fontsString, L"F");
			fontsString = SPStringHelper::XMLRemoveFirst(fontsString, L"F");

			SPString name = SPStringHelper::XMLExcludeFrom(fontString, L"N");
			SPString fontName = SPStringHelper::XMLExcludeFrom(fontString, L"FN");
			SPString fontWidth = SPStringHelper::XMLExcludeFrom(fontString, L"W");
			SPString fontHeight = SPStringHelper::XMLExcludeFrom(fontString, L"H");
			SPString fontWeight = SPStringHelper::XMLExcludeFrom(fontString, L"WT");
			SPString fontItalic = SPStringHelper::XMLExcludeFrom(fontString, L"I");
			SPString fontMipLevel = SPStringHelper::XMLExcludeFrom(fontString, L"L");

			CreateFont(name, SPStringHelper::StringToInt(fontHeight), 
				SPStringHelper::StringToInt(fontWidth),
				SPStringHelper::StringToInt(fontWeight),
				SPStringHelper::StringToInt(fontMipLevel),
				SPStringHelper::StringToInt(fontItalic) > 0, fontName);
		}

		return true;
	}

	SPString SPFontManager::SaveAsString()
	{
		SPString result;

		result += SPStringHelper::XMLSurroundWith(SPStringHelper::ToWString(sizeRate), L"SizeRate");
		result += SPStringHelper::XMLSurroundWith(SPStringHelper::ToWString(marginRate), L"MarginRate");

		result += L"<ExtendedFonts>";

		vector<SPString>::iterator iter = extendedFontPath.begin();

		while(iter != extendedFontPath.end())
		{
			result += L"<P>";
			result += *iter;
			result += L"</P>";

			iter++;
		}

		result += L"</ExtendedFonts>";

		result += L"<Fonts>";

		SPWStringMapIterator<SPFontPtr> fIter(&fonts);

		for(fIter.First(); !fIter.IsDone(); fIter.Next())
		{
			result += L"<F>";

			result += L"<N>";
			result += fIter.CurrentIndex();
			result += L"</N>";

			result += L"<FN>";
			result += fIter.CurrentItem()->GetFontName();
			result += L"</FN>";

			result += L"<H>";
			result += SPStringHelper::ToWString(fIter.CurrentItem()->GetHeight());
			result += L"</H>";

			result += L"<W>";
			result += SPStringHelper::ToWString(fIter.CurrentItem()->GetWidth());
			result += L"</W>";

			result += L"<WT>";
			result += SPStringHelper::ToWString(fIter.CurrentItem()->GetWeight());
			result += L"</WT>";

			result += L"<M>";
			result += SPStringHelper::ToWString(fIter.CurrentItem()->GetMipLevel());
			result += L"</M>";

			result += L"<I>";
			result += SPStringHelper::ToWString(fIter.CurrentItem()->GetItalic());
			result += L"</I>";

			result += L"</F>";
		}

		result += L"</Fonts>";

		result = SPStringHelper::XMLSurroundWith(result, L"SPFontManager");

		return result;
	}
}