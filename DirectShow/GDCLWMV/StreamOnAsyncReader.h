//
// Implements IStream as synch. source of data from an IAsyncReader interface
//
// Geraint Davies, January 2005
#pragma once

#include <streams.h>
#include <wmsdk.h>
#include <comdef.h>

_COM_SMARTPTR_TYPEDEF(IAsyncReader, IID_IAsyncReader);
_COM_SMARTPTR_TYPEDEF(IMediaSample, IID_IMediaSample);
_COM_SMARTPTR_TYPEDEF(IWMReader, IID_IWMReader);
_COM_SMARTPTR_TYPEDEF(IWMReaderAdvanced2, IID_IWMReaderAdvanced2);
_COM_SMARTPTR_TYPEDEF(IWMMediaProps, IID_IWMMediaProps);
_COM_SMARTPTR_TYPEDEF(IWMProfile, IID_IWMProfile);
_COM_SMARTPTR_TYPEDEF(IWMStreamConfig, IID_IWMStreamConfig);
_COM_SMARTPTR_TYPEDEF(INSSBuffer, IID_INSSBuffer);
_COM_SMARTPTR_TYPEDEF(IWMHeaderInfo, IID_IWMHeaderInfo);
_COM_SMARTPTR_TYPEDEF(IPin, IID_IPin);

#include <map>
#include <string>

#include <smart_ptr.h>

class StreamOnAsyncReader 
: public CUnknown,
  public IStream
{
public:
    StreamOnAsyncReader(IAsyncReader* pRdr, LONGLONG llPos);

    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID iid, void** ppv);

// IStream methods
    STDMETHOD(Read)(void *pv, ULONG cb, ULONG *pcbRead);
    STDMETHOD(Write)(const void *pv, ULONG cb, ULONG *pcbWritten);
    STDMETHOD(Seek)(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER *plibNewPosition);
    STDMETHOD(SetSize)(ULARGE_INTEGER libNewSize);
    STDMETHOD(CopyTo)(IStream *pstm, ULARGE_INTEGER cb,
                        ULARGE_INTEGER *pcbRead, ULARGE_INTEGER *pcbWritten);
    STDMETHOD(Commit)(DWORD grfCommitFlags);
    STDMETHOD(Revert)();
    STDMETHOD(LockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    STDMETHOD(UnlockRegion)(ULARGE_INTEGER libOffset, ULARGE_INTEGER cb, DWORD dwLockType);
    STDMETHOD(Stat)(STATSTG *pstatstg, DWORD grfStatFlag);
    STDMETHOD(Clone)(IStream **ppstm);
        
private:
    IAsyncReaderPtr m_pReader;
    LONGLONG m_llPosition;
};
