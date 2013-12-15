//////////////////////////////////////////////////////////////////////////
/// @file		SPFileSourceFilter.h the header file of SPFileSourceFilter class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <initguid.h>
#include "SPFileStream.h"
#include "asyncrdr.h"

DEFINE_GUID(CLSID_AsyncSample,
	0xc553f2c0, 0x1529, 0x11d0, 0xb4, 0xd1, 0x00, 0x80, 0x5f, 0x6c, 0xbb, 0xea);

class __declspec(uuid("{6B6D0801-9ADA-11D0-A520-00A0D10129C0}")) _MEDIASUBTYPE_ASF;
#define MEDIASUBTYPE_ASF __uuidof(_MEDIASUBTYPE_ASF)


namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFileSourceFilter class to represent the file source filter 
	/// which can pass a file source stream to other filter.
	///
	//////////////////////////////////////////////////////////////////////
	class SPFileSourceFilter : public CAsyncReader, public IFileSourceFilter
	{
	private:
		LPWSTR			m_pFileName;
		LONGLONG		m_llSize;
		PBYTE			m_pbData;
		SPFileStream	m_Stream;

	public:
		SPFileSourceFilter(LPUNKNOWN pUnk, HRESULT *phr) :
		  CAsyncReader(NAME("Mem Reader"), pUnk, &m_Stream, phr),
			  m_pFileName(NULL),
			  m_pbData(NULL)
		{
		}

		~SPFileSourceFilter()
		{
			delete [] m_pbData;
			m_pbData = NULL;
			delete [] m_pFileName;
			m_pFileName = NULL;
		}

		static CUnknown * WINAPI CreateInstance(LPUNKNOWN, HRESULT *);

		DECLARE_IUNKNOWN 
		STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void **ppv)
		{
			if (riid == IID_IFileSourceFilter)
			{
				return GetInterface((IFileSourceFilter *)this, ppv);
			}
			else 
			{
				return CAsyncReader::NonDelegatingQueryInterface(riid, ppv);
			}
		}

		/*  IFileSourceFilter methods */

		//  Load a (new) file
		STDMETHODIMP Load(LPCOLESTR lpwszFileName, const AM_MEDIA_TYPE *pmt)
		{
			CheckPointer(lpwszFileName, E_POINTER);

			// lstrlenW is one of the few Unicode functions that works on win95
			int cch = lstrlenW(lpwszFileName) + 1;

#ifndef UNICODE

			TCHAR *lpszFileName=0;
			lpszFileName = new char[cch * 2];
			if (!lpszFileName) 
			{
				return E_OUTOFMEMORY;
			}
			WideCharToMultiByte(GetACP(), 0, lpwszFileName, -1,
				lpszFileName, cch, NULL, NULL);


#else
			TCHAR lpszFileName[MAX_PATH]={0};
			(void)StringCchCopy(lpszFileName, NUMELMS(lpszFileName), lpwszFileName);
#endif

			CAutoLock lck(&m_csFilter);

			/*  Check the file type */
			CMediaType cmt;
			if (NULL == pmt) 
			{
				cmt.SetType(&MEDIATYPE_Stream);
				cmt.SetSubtype(&MEDIASUBTYPE_NULL);

				//std::wstring lpType = lpszFileName;
				//size_t dotPos = lpType.find_last_of(L".");
				//lpType = lpType.substr(dotPos + 1);
				//
				//if (lstrcmpi(lpType.c_str(), TEXT("avi")) == 0) 
				//{
				//	cmt.SetSubtype(&MEDIASUBTYPE_Avi);
				//}

				//if (lstrcmpi(lpType.c_str(), TEXT("wmv")) == 0) 
				//{
				//	cmt.SetSubtype(&MEDIASUBTYPE_ASF);
				//}
			} 
			else 
			{
				cmt = *pmt;
			}

			if (!ReadTheFile(lpszFileName)) 
			{

#ifndef UNICODE

				delete [] lpszFileName;

#endif

				return E_FAIL;
			}

			m_Stream.Init(m_pbData, m_llSize);

			m_pFileName = new WCHAR[cch];

			if (m_pFileName!=NULL)
			{
				CopyMemory(m_pFileName, lpwszFileName, cch*sizeof(WCHAR));
			}

			// this is not a simple assignment... pointers and format
			// block (if any) are intelligently copied
			//m_mt = cmt;

			/*  Work out file type */
			cmt.bTemporalCompression = TRUE;	       //???
			cmt.lSampleSize = 1;

			m_mt = cmt;

			return S_OK;
		}

		// Modeled on IPersistFile::Load
		// Caller needs to CoTaskMemFree or equivalent.

		STDMETHODIMP GetCurFile(LPOLESTR * ppszFileName, AM_MEDIA_TYPE *pmt)
		{
			CheckPointer(ppszFileName, E_POINTER);
			*ppszFileName = NULL;

			if (m_pFileName!=NULL)
			{
				DWORD n = sizeof(WCHAR)*(1+lstrlenW(m_pFileName));

				*ppszFileName = (LPOLESTR) CoTaskMemAlloc( n );
				if (*ppszFileName!=NULL) 
				{
					CopyMemory(*ppszFileName, m_pFileName, n);
				}
			}

			if (pmt!=NULL)
			{
				CopyMediaType(pmt, &m_mt);
			}

			return NOERROR;
		}

	private:
		BOOL ReadTheFile(LPCTSTR lpszFileName);
	};
}



