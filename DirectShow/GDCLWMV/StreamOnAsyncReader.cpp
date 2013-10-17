//
// Implements IStream as synch. source of data from an IAsyncReader interface
//
// Geraint Davies, January 2005

#include "StdAfx.h"
#include ".\streamonasyncreader.h"

StreamOnAsyncReader::StreamOnAsyncReader(IAsyncReader* pRdr, LONGLONG llPos)
: CUnknown(NAME("StreamOnAsyncReader"), NULL),
  m_pReader(pRdr),
  m_llPosition(llPos)
{
}

STDMETHODIMP 
StreamOnAsyncReader::NonDelegatingQueryInterface(REFIID iid, void** ppv)
{
    if ((iid == IID_IStream) || (iid == IID_ISequentialStream))
    {
        return GetInterface((IStream*)this, ppv);
    }
    return CUnknown::NonDelegatingQueryInterface(iid, ppv);
}

STDMETHODIMP
StreamOnAsyncReader::Read(void *pv, ULONG cb, ULONG *pcbRead)
{
    LONGLONG cLength, cAvail;
    HRESULT hr = m_pReader->Length(&cLength, &cAvail);
    if (FAILED(hr))
    {
        return hr;
    }
    if (m_llPosition >= cLength)
    {
        cb = 0;
    } else 
    {
        if ((m_llPosition + cb) > cLength)
        {
            cb = long(cLength - m_llPosition);
        }
        hr = m_pReader->SyncRead(m_llPosition, cb, (BYTE*)pv);
    }
    if (FAILED(hr))
    {
        cb = 0;
    }
    m_llPosition += cb;
    *pcbRead = cb;
    return hr;
}

STDMETHODIMP
StreamOnAsyncReader::Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition)
{
    switch(dwOrigin)
    {
    case STREAM_SEEK_SET:
        m_llPosition = dlibMove.QuadPart;
        break;

    case STREAM_SEEK_CUR:
        m_llPosition += dlibMove.QuadPart;
        break;

    case STREAM_SEEK_END:
        {
            LONGLONG cLength, cAvail;
            HRESULT hr = m_pReader->Length(&cLength, &cAvail);
            if (FAILED(hr))
            {
                return hr;
            }
            m_llPosition = cLength + dlibMove.QuadPart;
            break;
        }
    default:
        return E_INVALIDARG;
    }
    if (plibNewPosition != NULL)
    {
        plibNewPosition->QuadPart = m_llPosition;
    }
    return S_OK;
}

STDMETHODIMP
StreamOnAsyncReader::Clone(IStream **ppstm)
{
    IStreamPtr pClone = new StreamOnAsyncReader(m_pReader, m_llPosition);
    *ppstm = pClone.Detach();
    return S_OK;
}

STDMETHODIMP
StreamOnAsyncReader::Stat(STATSTG *pstatstg, DWORD grfStatFlag)
{
    LONGLONG cLength, cAvail;
    HRESULT hr = m_pReader->Length(&cLength, &cAvail);
    if (FAILED(hr))
    {
        return hr;
    }

    ZeroMemory(pstatstg, sizeof(STATSTG));
    pstatstg->type = STGTY_STREAM;
    pstatstg->cbSize.QuadPart = cLength;
    return S_OK;
}


STDMETHODIMP
StreamOnAsyncReader::Write(const void *pv, ULONG cb, ULONG *pcbWritten)
{
    DbgLog((LOG_ERROR, 0, "IStream::Write called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::SetSize(ULARGE_INTEGER libNewSize)
{
    DbgLog((LOG_ERROR, 0, "IStream::SetSize called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::CopyTo(IStream *pstm, ULARGE_INTEGER cb,
                    ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten)
{
    DbgLog((LOG_ERROR, 0, "IStream::CopyTo called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::Commit(DWORD grfCommitFlags)
{
    DbgLog((LOG_ERROR, 0, "IStream::Commit called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::Revert()
{
    DbgLog((LOG_ERROR, 0, "IStream::Revert called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::LockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    DbgLog((LOG_ERROR, 0, "IStream::LockRegion called"));
    return E_NOTIMPL;
}

STDMETHODIMP
StreamOnAsyncReader::UnlockRegion(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType)
{
    DbgLog((LOG_ERROR, 0, "IStream::UnlockRegion called"));
    return E_NOTIMPL;
}

