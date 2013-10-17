//////////////////////////////////////////////////////////////////////////
/// @file		SPFileStream.h the header file of SPFileStream class.
/// @author		Ken.J from SPRabbit
/// @version	Alpha 0.7
/// @date		2012-08-06
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <asyncio.h>

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPFileStream class to represent file stream which contain 
	/// the source of a video.
	///
	//////////////////////////////////////////////////////////////////////
	class SPFileStream : public CAsyncStream
	{
	private:
		CCritSec       m_csLock;
		PBYTE          m_pbData;
		LONGLONG       m_llLength;
		LONGLONG       m_llPosition;
		DWORD          m_dwKBPerSec;
		DWORD          m_dwTimeStart;

	public:
		SPFileStream(void) : m_llPosition(0) {}

		/*  Initialization */
		void Init(LPBYTE pbData, LONGLONG llLength, DWORD dwKBPerSec = INFINITE)
		{
			m_pbData = pbData;
			m_llLength = llLength;
			m_dwKBPerSec = dwKBPerSec;
			m_dwTimeStart = timeGetTime();
		}

		HRESULT SetPointer(LONGLONG llPos)
		{
			if (llPos < 0 || llPos > m_llLength) {
				return S_FALSE;
			} 
			else 
			{
				m_llPosition = llPos;
				return S_OK;
			}
		}

		HRESULT Read(
			PBYTE pbBuffer,
			DWORD dwBytesToRead,
			BOOL bAlign,
			LPDWORD pdwBytesRead)
		{
			CAutoLock lck(&m_csLock);
			DWORD dwReadLength;

			/*  Wait until the bytes are here! */
			DWORD dwTime = timeGetTime();

			if (m_llPosition + dwBytesToRead > m_llLength) 
			{
				dwReadLength = (DWORD)(m_llLength - m_llPosition);
			} 
			else 
			{
				dwReadLength = dwBytesToRead;
			}

			DWORD dwTimeToArrive =
				((DWORD)m_llPosition + dwReadLength) / m_dwKBPerSec;

			if (dwTime - m_dwTimeStart < dwTimeToArrive) 
			{
				Sleep(dwTimeToArrive - dwTime + m_dwTimeStart);
			}

			CopyMemory((PVOID)pbBuffer, (PVOID)(m_pbData + m_llPosition),
				dwReadLength);

			m_llPosition += dwReadLength;
			*pdwBytesRead = dwReadLength;
			return S_OK;
		}

		 LONGLONG Size(LONGLONG *pSizeAvailable)
		 {
			 LONGLONG llCurrentAvailable =
				 static_cast <LONGLONG> (UInt32x32To64((timeGetTime() - m_dwTimeStart),m_dwKBPerSec));

			 *pSizeAvailable =  min(m_llLength, llCurrentAvailable);
			 return m_llLength;
		 }

		 DWORD Alignment()
		 {
			 return 1;
		 }

		 void Lock()
		 {
			 m_csLock.Lock();
		 }

		 void Unlock()
		 {
			 m_csLock.Unlock();
		 }
	};
}
