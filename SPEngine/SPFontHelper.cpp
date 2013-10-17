#include "StdAfx.h"
#include "SPFontHelper.h"
#include "SPFile.h"
#include "SPFileManager.h"
#include "SPStringHelper.h"

#pragma warning(disable:4244)
#pragma warning(disable:4996)

namespace SPEngine
{
	typedef struct _tagTT_OFFSET_TABLE{
		USHORT	uMajorVersion;
		USHORT	uMinorVersion;
		USHORT	uNumOfTables;
		USHORT	uSearchRange;
		USHORT	uEntrySelector;
		USHORT	uRangeShift;
	}TT_OFFSET_TABLE;

	typedef struct _tagTT_TABLE_DIRECTORY{
		char	szTag[4];			//table name
		ULONG	uCheckSum;			//Check sum
		ULONG	uOffset;			//Offset from beginning of file
		ULONG	uLength;			//length of the table in bytes
	}TT_TABLE_DIRECTORY;

	typedef struct _tagTT_NAME_TABLE_HEADER{
		USHORT	uFSelector;			//format selector. Always 0
		USHORT	uNRCount;			//Name Records count
		USHORT	uStorageOffset;		//Offset for strings storage, from start of the table
	}TT_NAME_TABLE_HEADER;

	typedef struct _tagTT_NAME_RECORD{
		USHORT	uPlatformID;
		USHORT	uEncodingID;
		USHORT	uLanguageID;
		USHORT	uNameID;
		USHORT	uStringLength;
		USHORT	uStringOffset;	//from start of storage area
	}TT_NAME_RECORD;

#define SWAPWORD(x)		MAKEWORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x)		MAKELONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))

	SPString SPFontHelper::GetFontNameFromFile(SPString path)
	{
		SPFilePtr file;
		SPString result;

		file = SPFileManager::GetSingleton().OpenFile(path);

		if (file)
		{
			TT_OFFSET_TABLE ttOffsetTable;
			file->Read(&ttOffsetTable, sizeof(TT_OFFSET_TABLE));
			ttOffsetTable.uNumOfTables = SWAPWORD(ttOffsetTable.uNumOfTables);
			ttOffsetTable.uMajorVersion = SWAPWORD(ttOffsetTable.uMajorVersion);
			ttOffsetTable.uMinorVersion = SWAPWORD(ttOffsetTable.uMinorVersion);

			//check is this is a true type font and the version is 1.0
			if(ttOffsetTable.uMajorVersion != 1 || ttOffsetTable.uMinorVersion != 0)
			{
				return result;
			}

			TT_TABLE_DIRECTORY tblDir;
			BOOL bFound = FALSE;
			SPString tempString;

			for(int i = 0; i < ttOffsetTable.uNumOfTables; i++)
			{
				file->Read(&tblDir, sizeof(TT_TABLE_DIRECTORY));

				char* buffer = new char[5];
				strncpy(buffer, tblDir.szTag, 4);
				string s = buffer;
				delete [] buffer;
				buffer = NULL;
				if(s == "name")
				{
					bFound = TRUE;
					tblDir.uLength = SWAPLONG(tblDir.uLength);
					tblDir.uOffset = SWAPLONG(tblDir.uOffset);
					break;
				}
			}

			if(bFound)
			{
				file->SetPosition(tblDir.uOffset);
				TT_NAME_TABLE_HEADER ttNTHeader;
				file->Read(&ttNTHeader, sizeof(TT_NAME_TABLE_HEADER));
				ttNTHeader.uNRCount = SWAPWORD(ttNTHeader.uNRCount);
				ttNTHeader.uStorageOffset = SWAPWORD(ttNTHeader.uStorageOffset);
				TT_NAME_RECORD ttRecord;
				bFound = FALSE;

				for(int i=0; i<ttNTHeader.uNRCount; i++)
				{
					file->Read(&ttRecord, sizeof(TT_NAME_RECORD));
					ttRecord.uNameID = SWAPWORD(ttRecord.uNameID);
					if(ttRecord.uNameID == 1)
					{
						ttRecord.uStringLength = SWAPWORD(ttRecord.uStringLength);
						ttRecord.uStringOffset = SWAPWORD(ttRecord.uStringOffset);
						int nPos = file->GetPosition();
						file->SetPosition(tblDir.uOffset + ttRecord.uStringOffset + ttNTHeader.uStorageOffset);

						char* buffer = new char[ttRecord.uStringLength + 1];
						file->Read(buffer, ttRecord.uStringLength);
						string s = buffer;
						delete [] buffer;
						buffer = NULL;
						if(s.size() > 0)
						{
							result = SPStringHelper::ToWString(s);
							break;
						}
						file->SetPosition(nPos);
					}
				}			
			}
			
			SPFileManager::GetSingleton().CloseFile(path);
		}

		return result;
	}
}