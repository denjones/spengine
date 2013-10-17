// WMF Demux filter
//
// Declaration of filter and pin classes
//
// Geraint Davies, January 2005

#include "StdAfx.h"
#include "filter.h"
#include "StreamOnAsyncReader.h"
#include <wmsdkidl.h>

using namespace std;

// this is the (undocumented) media type that is registered for WMV/WMA files
class DECLSPEC_UUID("6B6D0801-9ADA-11D0-A520-00A0D10129C0") MEDIASUBTYPE_ASF;

// filter registration tables
//static 
const AMOVIESETUP_MEDIATYPE 
WMFDemuxFilter::m_sudType[] = 
{
    {
        &MEDIATYPE_Stream,
        &__uuidof(MEDIASUBTYPE_ASF),
    },
    {
        &MEDIATYPE_Video,
        &MEDIASUBTYPE_NULL
    },
    {
        &MEDIATYPE_Audio,
        &MEDIASUBTYPE_NULL
    }
};

//static 
const AMOVIESETUP_PIN 
WMFDemuxFilter::m_sudPin[] = 
{
    {
        L"Input",          // pin name
        FALSE,              // is rendered?    
        FALSE,              // is output?
        FALSE,              // zero instances allowed?
        FALSE,              // many instances allowed?
        &CLSID_NULL,        // connects to filter (for bridge pins)
        NULL,               // connects to pin (for bridge pins)
        1,                  // count of registered media types
        &m_sudType[0]       // list of registered media types    
    },
    {
        L"Video Output",    // pin name
        FALSE,              // is rendered?    
        TRUE,               // is output?
        FALSE,              // zero instances allowed?
        FALSE,              // many instances allowed?
        &CLSID_NULL,        // connects to filter (for bridge pins)
        NULL,               // connects to pin (for bridge pins)
        1,                  // count of registered media types
        &m_sudType[1]       // list of registered media types    
    },
    {
        L"Audio Output",    // pin name
        FALSE,              // is rendered?    
        TRUE,               // is output?
        FALSE,              // zero instances allowed?
        FALSE,              // many instances allowed?
        &CLSID_NULL,        // connects to filter (for bridge pins)
        NULL,               // connects to pin (for bridge pins)
        1,                  // count of registered media types
        &m_sudType[2]       // list of registered media types    
    },
};

//static 
const AMOVIESETUP_FILTER 
WMFDemuxFilter::m_sudFilter =
{
    &__uuidof(WMFDemuxFilter),      // filter clsid
    L"GDCL WMV/WMA Parser",         // filter name
    MERIT_NORMAL,                   
    3,                              // count of registered pins
    m_sudPin                        // list of pins to register
};

//static 
CUnknown* WINAPI 
WMFDemuxFilter::CreateInstance(LPUNKNOWN pUnk, HRESULT* phr)
{
    return new WMFDemuxFilter(pUnk, phr);
}

WMFDemuxFilter::WMFDemuxFilter(LPUNKNOWN pUnk, HRESULT* phr)
: CBaseFilter(NAME("WMFDemuxFilter"), pUnk, &m_csFilter, *m_sudFilter.clsID),
  m_evStatus(true),         // manual reset
  m_Op(eNoop),
  m_bEOF(false),
  m_cPins(0),
  m_duration(0),
  m_tStart(0),
  m_tStop(-1),
  m_dRate(1.0),
  m_pSeekingPin(NULL)
{
    HRESULT hr = S_OK;
    m_pInput = new StreamInput(this, &m_csFilter, &hr);
}

STDMETHODIMP 
WMFDemuxFilter::NonDelegatingQueryInterface(REFIID iid, void** ppv)
{
    if ((iid == IID_IWMReaderCallback) || 
        (iid == IID_IWMStatusCallback))
    {
        return GetInterface((IWMReaderCallback*)this, ppv);
    }
    if (iid == IID_IWMReaderCallbackAdvanced)
    {
        return GetInterface((IWMReaderCallbackAdvanced*)this, ppv);
    }
    return CBaseFilter::NonDelegatingQueryInterface(iid, ppv);
}


int 
WMFDemuxFilter::GetPinCount()
{
    return 1 + m_cPins;
}

CBasePin *
WMFDemuxFilter::GetPin(int n)
{
    if (n == 0)
    {
        return m_pInput;
    } else if (n <= m_cPins)
    {
        return Pin(n-1);
    }
    return NULL;
}

HRESULT 
WMFDemuxFilter::CompleteConnect()
{
    IStreamPtr pStream;
    HRESULT hr = m_pInput->GetStream(&pStream);
    if (FAILED(hr))
    {
        return hr;
    }

    // create the WMF reader object
    hr = WMCreateReader(NULL, 0, &m_pWMFReader);
    if (FAILED(hr) || (m_pWMFReader == NULL))
    {
        return E_FAIL;
    }
    IWMReaderAdvanced2Ptr pRdr2 = m_pWMFReader;
    if (pRdr2 == NULL)
    {
        return E_NOINTERFACE;
    }

    // prepare for async completion
    {
        CAutoLock lock(&m_csStatus);
        m_Op = eOpen;
        m_evStatus.Reset();
    }

    // open the stream, using the IStream wrapper on IAsyncReader
    hr = pRdr2->OpenStream(pStream, this, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    // wait for async completion
    m_evStatus.Wait();
    
    {
        CAutoLock lock(&m_csStatus);
        if (FAILED(m_hrAsync))
        {
            m_pWMFReader = NULL;
            return m_hrAsync;
        }
    }

    IWMProfilePtr pProfile = m_pWMFReader;
    if (pProfile == NULL)
    {
        return E_NOINTERFACE;
    }

    // some streams are disabled and some stream numbers are not present,
    // so we need to count active pins first
    DWORD nStreams;
    hr = pProfile->GetStreamCount(&nStreams);
    if (FAILED(hr) || (nStreams == 0))
    {
        return E_INVALIDARG;
    }

    m_cPins = 0;
    for (UINT i = 0; i < nStreams; i++)
    {
        IWMStreamConfigPtr pStream;
        hr = pProfile->GetStream(i, &pStream);

        WORD wStream;
        pStream->GetStreamNumber(&wStream);

        WMT_STREAM_SELECTION IsOn;
        pRdr2->GetStreamSelected(wStream, &IsOn);
        if (IsOn == WMT_OFF)
        {
            continue;
        }
        m_cPins++;

        // get compressed, not uncompressed data
        hr = pRdr2->SetReceiveStreamSamples(wStream, true);
        if (FAILED(hr))
        {
            DbgLog((LOG_ERROR, 0, "ReceiveStreamSamples failed 0x%x", hr));
        }

        // use our allocator
        hr = pRdr2->SetAllocateForStream(wStream, true);
        if (FAILED(hr))
        {
            DbgLog((LOG_ERROR, 0, "SetAllocateForStreamfailed 0x%x", hr));
        }

        // create the pin with a unique name
        WORD wStrLen = 0;
        pStream->GetStreamName(NULL, &wStrLen);
        smart_array<WCHAR>awch = new WCHAR[wStrLen];
        pStream->GetStreamName(awch, &wStrLen);
        WMFOutputPinPtr pin = new WMFOutputPin(this, &m_csFilter, &hr, awch);

        // insert in map, using wStream as index
        m_Outputs.insert(pair<WORD, WMFOutputPinPtr>(wStream, pin));

        // get the compressed media type from the profile for this stream
        IWMMediaPropsPtr pProps = pStream;
        if (pProps == NULL)
        {
            return E_NOINTERFACE;
        }
        DWORD cType = 0;
        pProps->GetMediaType(NULL, &cType);
        smart_array<BYTE> abType = new BYTE[cType];
        pProps->GetMediaType((WM_MEDIA_TYPE*)(BYTE*)abType, &cType);
        CMediaType mt(* (AM_MEDIA_TYPE*)(BYTE*)abType);

        // check max buffer size
        DWORD cbMax= 0;
        pRdr2->GetMaxStreamSampleSize(wStream, &cbMax);

        // set type that this pin should offer
        WMFOutputPin* pOutput = Pin(m_cPins-1);
        pOutput->OfferMediaTypes(&mt, cbMax);
    }

    // prevent the WMF code from timing the delivery by providing
    // a clock (in the OnTime callbacks) that ensures delivery to us
    // as fast as possible, with timing at the renderer filters.
    pRdr2->SetUserProvidedClock(true);

    // get the duration from the header attributes
    m_duration = 0;
    IWMHeaderInfoPtr pHdr = m_pWMFReader;
    if (pHdr != NULL)
    {
        WMT_ATTR_DATATYPE type;
        LONGLONG duration;
        WORD wBytes = sizeof(duration);
        WORD wStream = 0;
        HRESULT hr = pHdr->GetAttributeByName(&wStream, g_wszWMDuration, &type, (BYTE*)&duration, &wBytes);
        if (SUCCEEDED(hr) && (wBytes == sizeof(duration)))
        {
            
            m_duration = duration;
        }
    }

    return S_OK;
}

HRESULT
WMFDemuxFilter::BreakConnect()
{
    if (m_pWMFReader != NULL)
    {
        // prepare for async completion
        {
            CAutoLock lock(&m_csStatus);
            m_Op = eClose;
            m_evStatus.Reset();
        }

        HRESULT hr = m_pWMFReader->Close();
        if (SUCCEEDED(hr))
        {
            // wait for async completion
            m_evStatus.Wait();
        }
        m_pWMFReader = NULL;

        // disconnect output pins
        PinMap::iterator it;
        for (it = m_Outputs.begin(); it != m_Outputs.end(); it++)
        {
            WMFOutputPin* pOutput = PinFromMap(it);
            IPinPtr pPeer;
            pOutput->ConnectedTo(&pPeer);
            if (pPeer != NULL)
            {
                pOutput->Disconnect();
                pPeer->Disconnect();
            }
        }
    }
    m_cPins = 0;
    m_Outputs.clear();

    return S_OK;
}

STDMETHODIMP 
WMFDemuxFilter::Stop()
{
    if (m_State != State_Stopped)
    {
        StopWMF();
    }

    return CBaseFilter::Stop();
}

STDMETHODIMP 
WMFDemuxFilter::Pause()
{
    m_bEOF = false;
    bool bStart = (m_State == State_Stopped);
    HRESULT hr = CBaseFilter::Pause();
    if (SUCCEEDED(hr) && bStart)
    {
        hr = StartWMF();
    }
    return hr;
}

HRESULT
WMFDemuxFilter::StartWMF()
{
    // rate: for rates between -1 and +1, we can just adjust the timestamps
    float dRate = float(m_dRate);
    if (dRate < 0)
    {
        if (dRate > -1)
        {
            dRate = -1;
        } else if (dRate < -10)
        {
            dRate = -10;
        }
    } else if (dRate < 10)
    {
        dRate = 1;
    } else if (dRate > 10)
    {
        dRate = 10;
    }
    // duration must be zero for user-supplied clock: we check for end time in
    // the OnTime callback
	HRESULT hr = S_OK;

	if (m_pWMFReader)
	{
		hr = m_pWMFReader->Start(m_tStart, 0, dRate, NULL);
	}
    
    return hr;
}

HRESULT
WMFDemuxFilter::StopWMF()
{
    // prepare for async completion
    {
        CAutoLock lock(&m_csStatus);
        m_Op = eStop;
        m_evStatus.Reset();
    }

    HRESULT hr = m_pWMFReader->Stop();
    if (SUCCEEDED(hr))
    {
        // wait for async completion
        m_evStatus.Wait();
    
        {
            CAutoLock lock(&m_csStatus);
            hr = m_hrAsync;
            if (FAILED(hr))
            {
                DbgLog((LOG_ERROR, 0, "WMFReader Stop async failure 0x%x", hr));
            }
        }
    } else 
    {
        DbgLog((LOG_ERROR, 0, "WMFReader Stop failed 0x%x", hr));
    }
    return hr;
}

// --- Seeking support ------------------------------

bool 
WMFDemuxFilter::SelectSeekingPin(WMFOutputPin* pPin)
{
    CAutoLock lock(&m_csSeeking);
    if (m_pSeekingPin == NULL)
    {
        m_pSeekingPin = pPin;
    }
    return (m_pSeekingPin == pPin);
}

void 
WMFDemuxFilter::DeselectSeekingPin(WMFOutputPin* pPin)
{
    CAutoLock lock(&m_csSeeking);
    if (pPin == m_pSeekingPin)
    {
        m_pSeekingPin = NULL;
    }
}

void 
WMFDemuxFilter::GetSeekingParams(REFERENCE_TIME* ptStart, REFERENCE_TIME* ptStop, double* pdRate)
{
    if (ptStart != NULL)
    {
        *ptStart = m_tStart;
    }
    if (ptStop != NULL)
    {
        *ptStop = m_tStop;
    }
    if (pdRate != NULL)
    {
        *pdRate = m_dRate;
    }
}

HRESULT 
WMFDemuxFilter::Seek(REFERENCE_TIME tStart, REFERENCE_TIME tStop, double dRate)
{
    bool bActive = false;

    if (m_State != State_Stopped)
    {
        bActive = true;
        
        // flush all output pins
        PinMap::iterator it;
        for (it = m_Outputs.begin(); it != m_Outputs.end(); it++)
        {
            WMFOutputPin* pOutput = PinFromMap(it);
            pOutput->DeliverBeginFlush();
        }

        // stop reader object
        StopWMF();

        m_bEOF = false;

        // end flush so re-delivery can commence
        for (it = m_Outputs.begin(); it != m_Outputs.end(); it++)
        {
            WMFOutputPin* pOutput = PinFromMap(it);
            pOutput->DeliverEndFlush();
        }
    }

    // hold critsec while updating params
    {
        CAutoLock lock(&m_csSeeking);
        m_tStart = tStart;
        m_tStop = tStop;
        m_dRate = dRate;

        long dbgmsStop = 0;
        if (tStop > 0)
        {
            dbgmsStop = long(tStop/10000);
        }
        DbgLog((LOG_TRACE, 2, "Seek %d ms to %d ms", long(tStart/10000), dbgmsStop));
    }

    // restart if active
    HRESULT hr = S_OK;
    if (bActive)
    {
        hr = StartWMF();
    }
    return hr;
}

HRESULT 
WMFDemuxFilter::SetRate(double dRate)
{
    CAutoLock lock(&m_csSeeking);
    m_dRate = dRate;
    return S_OK;
}

HRESULT 
WMFDemuxFilter::SetStopTime(REFERENCE_TIME tStop)
{
    CAutoLock lock(&m_csSeeking);
    m_tStop = tStop;
    return S_OK;
}

// callbacks from WMF -------------------------------


STDMETHODIMP
WMFDemuxFilter::OnStatus( 
    /* [in] */ WMT_STATUS Status,
    /* [in] */ HRESULT hr,
    /* [in] */ WMT_ATTR_DATATYPE dwType,
    /* [in] */ BYTE* pValue,
    /* [in] */ void* pvContext)
{
    CAutoLock lock(&m_csStatus);
    switch (Status)
    {
    case WMT_OPENED:
        if (m_Op == eOpen)
        {
            m_Op = eNoop;
            m_hrAsync = hr;
            m_evStatus.Set();
        }
        break;

    case WMT_STOPPED:
        if (m_Op == eStop)
        {
            m_Op = eNoop;
            m_hrAsync = hr;
            m_evStatus.Set();
        }
        break;

    case WMT_CLOSED:
        if (m_Op == eClose)
        {
            m_Op = eNoop;
            m_hrAsync = hr;
            m_evStatus.Set();
        }
        break;

    case WMT_STARTED:
        {
            // ask for the first second to be delivered asap
            // (absolute, so include seek time
            m_tDelivery = m_tStart + UNITS;
            DbgLog((LOG_TRACE, 2, "Delivery up to %d ms", long(m_tDelivery/10000)));
            IWMReaderAdvanced2Ptr pRdr2 = m_pWMFReader;
            pRdr2->DeliverTime(m_tDelivery);
        }
        break;

    case WMT_END_OF_STREAMING:
    case WMT_EOF:
        if (!m_bEOF)
        {
            m_bEOF = true;
            PinMap::iterator it;
            for (it = m_Outputs.begin(); it != m_Outputs.end(); it++)
            {
                WMFOutputPin* pOutput = PinFromMap(it);
                pOutput->DeliverEndOfStream();
            }
        }
        break;

    case WMT_ERROR:
        DbgLog((LOG_ERROR, 0, "WMT Error hr = 0x%x", hr));
        NotifyEvent(EC_ERRORABORT, hr, 0);
        break;

    default:
        DbgLog((LOG_ERROR, 0, "Unknown WMT status code %d, hr 0x%x", Status, hr));
        break;
    }
    return S_OK;
}

STDMETHODIMP
WMFDemuxFilter::OnSample( 
    /* [in] */ DWORD dwOutputNum,
    /* [in] */ QWORD cnsSampleTime,
    /* [in] */ QWORD cnsSampleDuration,
    /* [in] */ DWORD dwFlags,
    /* [in] */ INSSBuffer* pSample,
    /* [in] */ void* pvContext)
{
    DbgLog((LOG_ERROR, 0, "Received uncompressed sample"));
    return S_FALSE;
}

STDMETHODIMP
WMFDemuxFilter::OnStreamSample( 
    /* [in] */ WORD wStreamNum,
    /* [in] */ QWORD cnsSampleTime,
    /* [in] */ QWORD cnsSampleDuration,
    /* [in] */ DWORD dwFlags,
    /* [in] */ INSSBuffer* pNSBuffer,
    /* [in] */ void* pvContext)
{
    // delivery of compressed sample

    // use map to translate stream number into pin
    PinMap::iterator it = m_Outputs.find(wStreamNum);
    if (it == m_Outputs.end())
    {
        return E_INVALIDARG;
    }
    WMFOutputPin* pPin = PinFromMap(it);

    // get contained sample object
    IEncapsulatedAccessPtr pEA = pNSBuffer;
    if (pEA == NULL)
    {
        return E_NOINTERFACE;
    }
    IUnknownPtr pUnk;
    pEA->GetEncapsulatedObject(&pUnk);
    IMediaSamplePtr pSample = pUnk;
    if (pSample == NULL)
    {
        return E_INVALIDARG;
    }
    // apply timestamps, adjusting for rate
    REFERENCE_TIME tStart = REFERENCE_TIME(cnsSampleTime) - m_tStart;
    tStart = REFERENCE_TIME(tStart / m_dRate);
    REFERENCE_TIME tStop = REFERENCE_TIME(cnsSampleTime) + REFERENCE_TIME(cnsSampleDuration) - m_tStart;
    tStop = REFERENCE_TIME(tStop / m_dRate);
    pSample->SetTime(&tStart, &tStop);

	HRESULT hr = pPin->Send(pSample, tStart, dwFlags);

    if (hr != S_OK)
    {
        DbgLog((LOG_TRACE, 2, "Stream %d delivery returns 0x%x", wStreamNum, hr));
    }
    return hr;
}

STDMETHODIMP
WMFDemuxFilter::OnTime( 
    /* [in] */ QWORD cnsCurrentTime,
    /* [in] */ void* pvContext)
{
    if (m_bEOF)
    {
        return S_FALSE;
    }

    bool bEnd = false;

    // check stop time under critsec
    {
        CAutoLock lock(&m_csSeeking);
        if (m_tStop >= 0)
        {
            if (cnsCurrentTime >= QWORD(m_tStop))
            {
                DbgLog((LOG_TRACE, 2, "Stopping at %d ms", long(cnsCurrentTime/10000)));
                bEnd = true;
            }
        }
    }

    // EOF if necessary, outside critsec
    if (bEnd)
    {
        if (!m_bEOF)
        {
            m_bEOF = true;
            PinMap::iterator it;
            for (it = m_Outputs.begin(); it != m_Outputs.end(); it++)
            {
                WMFOutputPin* pOutput = PinFromMap(it);
                pOutput->DeliverEndOfStream();
            }
        }
        return S_OK;
    }

    // ask for one more second
    m_tDelivery += UNITS;
    DbgLog((LOG_TRACE, 2, "Delivery up to %d ms", long(m_tDelivery/10000)));
    IWMReaderAdvanced2Ptr pRdr2 = m_pWMFReader;
    return pRdr2->DeliverTime(m_tDelivery);
}

STDMETHODIMP
WMFDemuxFilter::OnStreamSelection( 
    /* [in] */ WORD wStreamCount,
    /* [in] */ WORD* pStreamNumbers,
    /* [in] */ WMT_STREAM_SELECTION* pSelections,
    /* [in] */ void* pvContext)
{
    return S_OK;
}

STDMETHODIMP
WMFDemuxFilter::OnOutputPropsChanged( 
    /* [in] */ DWORD dwOutputNum,
    /* [in] */ WM_MEDIA_TYPE* pMediaType,
    /* [in] */ void* pvContext)
{
    return S_OK;
}

STDMETHODIMP
WMFDemuxFilter::AllocateForStream( 
    /* [in] */ WORD wStreamNum,
    /* [in] */ DWORD cbBuffer,
    /* [out] */ INSSBuffer** ppBuffer,
    /* [in] */ void* pvContext)
{
    // find output pin corresponding to this stream
    // use map to translate stream number into pin
    PinMap::iterator it = m_Outputs.find(wStreamNum);
    if (it == m_Outputs.end())
    {
        return E_INVALIDARG;
    }
    WMFOutputPin* pPin = PinFromMap(it);

    // allocate a buffer
    IMediaSamplePtr pSample;
    HRESULT hr = pPin->GetDeliveryBuffer(&pSample, NULL, NULL, 0);
    if (FAILED(hr))
    {
        return hr;
    }

    // is this buffer big enough? It should be, as we checked the max sample size.
    if ((DWORD)pSample->GetSize() < cbBuffer)
    {
        return E_FAIL;
    }

    // create an INSBuffer wrapper
    INSSBufferPtr pNS = new EncapsulateSample(pSample);
    *ppBuffer = pNS.Detach();
    return S_OK;
}

STDMETHODIMP
WMFDemuxFilter::AllocateForOutput( 
    /* [in] */ DWORD dwOutputNum,
    /* [in] */ DWORD cbBuffer,
    /* [out] */ INSSBuffer** ppBuffer,
    /* [in] */ void* pvContext)
{
    DbgLog((LOG_ERROR, 0, "Uncompressed allocation request"));
    return E_NOTIMPL;
}

// --- input pin implementation -------------------------

StreamInput::StreamInput(WMFDemuxFilter* pFilter, CCritSec* pLock, HRESULT* phr)
: CBasePin(NAME("StreamInput"), pFilter, pLock, phr, L"Input", PINDIR_INPUT),
  m_pDemux(pFilter)
{
}

HRESULT 
StreamInput::CheckMediaType(const CMediaType* pmt)
{
    // we accept specifically the mt that the registry pattern-match table
    // produces for WMV/WMA files
    if ((*pmt->Type() == MEDIATYPE_Stream) &&
        (*pmt->Subtype() == __uuidof(MEDIASUBTYPE_ASF)))
    {
        return S_OK;
    }
    return VFW_E_TYPE_NOT_ACCEPTED;
}

HRESULT 
StreamInput::GetMediaType(int iPosition, CMediaType* pmt)
{
    if (iPosition != 0)
    {
        return VFW_S_NO_MORE_ITEMS;
    }
    pmt->InitMediaType();
    pmt->SetType(&MEDIATYPE_Stream);
    pmt->SetSubtype(&__uuidof(MEDIASUBTYPE_ASF));

    return S_OK;
}

HRESULT 
StreamInput::CompleteConnect(IPin* pPeer)
{
    HRESULT hr = CBasePin::CompleteConnect(pPeer);
    if (SUCCEEDED(hr))
    {
        IAsyncReaderPtr pRdr = pPeer;
        if (pRdr == NULL)
        {
            hr = E_NOINTERFACE;
        }
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pDemux->CompleteConnect();
    }
    return hr;
}

HRESULT
StreamInput::BreakConnect()
{
    return m_pDemux->BreakConnect();
}

HRESULT 
StreamInput::GetStream(IStream** ppStream)
{
    IAsyncReaderPtr pReader = GetConnected();
    if (pReader == NULL)
    {
        return E_NOINTERFACE;
    }
    IStreamPtr pClone = new StreamOnAsyncReader(pReader, 0);
    *ppStream = pClone.Detach();
    return S_OK;
}

STDMETHODIMP
StreamInput::BeginFlush()
{
    return S_OK;
}

STDMETHODIMP
StreamInput::EndFlush()
{
    return S_OK;
}

// --- output pin implementation --------------------

WMFOutputPin::WMFOutputPin(WMFDemuxFilter* pParser, CCritSec* pLock, HRESULT* phr, LPCWSTR pName)
: CBaseOutputPin(NAME("WMFOutputPin"), pParser, pLock, phr, pName),
  m_bDiscont(true),
  m_bFirstSample(true),
  m_pParser(pParser)
{
}

STDMETHODIMP 
WMFOutputPin::NonDelegatingQueryInterface(REFIID iid, void** ppv)
{
    if (iid == IID_IMediaSeeking)
    {
        return GetInterface((IMediaSeeking*)this, ppv);
    } else 
    {
        return CBaseOutputPin::NonDelegatingQueryInterface(iid, ppv);
    }
}


// base class overrides for connection establishment
HRESULT 
WMFOutputPin::CheckMediaType(const CMediaType* pmt)
{
    if (*pmt == m_mtStream)
    {
        return S_OK;
    }
    return VFW_E_TYPE_NOT_ACCEPTED;
}

HRESULT 
WMFOutputPin::GetMediaType(int iPosition, CMediaType* pmt)
{
    if (iPosition != 0)
    {
        return VFW_S_NO_MORE_ITEMS;
    }
    *pmt = m_mtStream;
    return S_OK;
}

HRESULT 
WMFOutputPin::DecideBufferSize(IMemAllocator* pAlloc, ALLOCATOR_PROPERTIES* pprop)
{
    // we know the maximum compressed sample size, so make all the buffers big enough for that
    pprop->cbBuffer = m_cbMax;

    // needs to be enough to get from the key frame to the audio
    pprop->cBuffers = 200;       // ?
    ALLOCATOR_PROPERTIES propActual;
    return pAlloc->SetProperties(pprop, &propActual);
}

HRESULT 
WMFOutputPin::Active()
{
    m_bDiscont = true;
    m_bFirstSample = true;
    HRESULT hr = S_OK;
    if (IsConnected())
    {
        hr = CBaseOutputPin::Active();
        if (SUCCEEDED(hr))
        {
            m_pOutputQ = new COutputQueue(
                                         GetConnected(),
                                         &hr,
                                         false,
                                         true,
                                         10,
                                         true,
                                         10);
        }
    }
    return hr;
}

HRESULT 
WMFOutputPin::Inactive()
{
    HRESULT hr = CBaseOutputPin::Inactive();
    m_pOutputQ = NULL;
    return hr;
}

HRESULT 
WMFOutputPin::DeliverEndOfStream()
{
    if (m_pOutputQ != NULL)
    {
        m_pOutputQ->EOS();
    }
    return S_OK;
}

HRESULT 
WMFOutputPin::DeliverBeginFlush()
{
    if (m_pOutputQ != NULL)
    {
        m_pOutputQ->BeginFlush();
    }
    return S_OK;
}

HRESULT 
WMFOutputPin::DeliverEndFlush()
{
    if (m_pOutputQ != NULL)
    {
        m_pOutputQ->EndFlush();
    }
    // next sample will be after a discontinuity
    m_bDiscont = true;

    return S_OK;
}

HRESULT 
WMFOutputPin::Deliver(IMediaSample* pSample)
{
    HRESULT hr = S_FALSE;
    if (m_pOutputQ != NULL)
    {
        if (m_bDiscont)
        {
            pSample->SetDiscontinuity(true);
            m_bDiscont = false;

            // new segment to indicate playback range
            REFERENCE_TIME tStart, tStop;
            double dRate;
            m_pParser->GetSeekingParams(&tStart, &tStop, &dRate);
            if (tStop < 0)
            {
                tStop = 0x7fffffffffffffff;
            }
            m_pOutputQ->NewSegment(tStart, tStop, dRate);
        }
        // outputq needs to be given a refcount
        pSample->AddRef();
        hr = m_pOutputQ->Receive(pSample);
    }
    return hr;
}

void 
WMFOutputPin::OfferMediaTypes(const CMediaType* pmt, long cbMax)
{
    m_mtStream = *pmt;
    m_cbMax = cbMax;
}

// callback from SDK to deliver sample
HRESULT
WMFOutputPin::Send(IMediaSample* pSample, REFERENCE_TIME tStart, DWORD dwFlags)
{
    if (tStart < 0)
    {
        pSample->SetPreroll(true);
    }

    // apply flags
    if (dwFlags & WM_SF_CLEANPOINT)
    {
        pSample->SetSyncPoint(true);
    }

    if (m_bFirstSample)
    {
        m_bFirstSample = false;
    }
    else
    {
        // some audio streams have incorrect durations, (eg first sample at 0ms for 170ms, second at 128ms).
        // For these streams, we get a discont with each packet.
        // It turns out that if we ignore the discont on second and subsequent packets, the duration is ignored
        // and the stream plays correctly.
        if (IsAudio()) 
        {
            dwFlags &= ~(WM_SF_DISCONTINUITY);
        }
    }

    if (dwFlags & (WM_SF_DATALOSS | WM_SF_DISCONTINUITY))
    {
        pSample->SetDiscontinuity(true);
    }

    long cBytes = pSample->GetActualDataLength();

    HRESULT hr = Deliver(pSample);
    SendAnyway();
    return hr;
}

// -- output pin seeking methods -------------------------

STDMETHODIMP 
WMFOutputPin::GetCapabilities(DWORD * pCapabilities)
{

    // Some versions of DShow have an aggregation bug that
    // affects playback with Media Player. To work around this,
    // we need to report the capabilities and time format the
    // same on all pins, even though only one
    // can seek at once.
    *pCapabilities =        AM_SEEKING_CanSeekAbsolute |
                            AM_SEEKING_CanSeekForwards |
                            AM_SEEKING_CanSeekBackwards |
                            AM_SEEKING_CanGetDuration |
                            AM_SEEKING_CanGetStopPos;
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::CheckCapabilities(DWORD * pCapabilities)
{
    DWORD dwActual;
    GetCapabilities(&dwActual);
    if (*pCapabilities & (~dwActual))
    {
        return S_FALSE;
    }
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::IsFormatSupported(const GUID * pFormat)
{
    // Some versions of DShow have an aggregation bug that
    // affects playback with Media Player. To work around this,
    // we need to report the capabilities and time format the
    // same on all pins, even though only one
    // can seek at once.
    if (*pFormat == TIME_FORMAT_MEDIA_TIME)
    {
        return S_OK;
    }
    return S_FALSE;

}
STDMETHODIMP 
WMFOutputPin::QueryPreferredFormat(GUID * pFormat)
{
    // Some versions of DShow have an aggregation bug that
    // affects playback with Media Player. To work around this,
    // we need to report the capabilities and time format the
    // same on all pins, even though only one
    // can seek at once.
    *pFormat = TIME_FORMAT_MEDIA_TIME;
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::GetTimeFormat(GUID *pFormat)
{
    return QueryPreferredFormat(pFormat);
}

STDMETHODIMP 
WMFOutputPin::IsUsingTimeFormat(const GUID * pFormat)
{
    GUID guidActual;
    HRESULT hr = GetTimeFormat(&guidActual);

    if (SUCCEEDED(hr) && (guidActual == *pFormat))
    {
        return S_OK;
    } else
    {
        return S_FALSE;
    }
}

STDMETHODIMP 
WMFOutputPin::ConvertTimeFormat(
                                      LONGLONG* pTarget, 
                                      const GUID* pTargetFormat,
                                      LONGLONG Source, 
                                      const GUID* pSourceFormat)
{
    // format guids can be null to indicate current format

    // since we only support TIME_FORMAT_MEDIA_TIME, we don't really
    // offer any conversions.
    if (pTargetFormat == 0 || *pTargetFormat == TIME_FORMAT_MEDIA_TIME)
    {
        if (pSourceFormat == 0 || *pSourceFormat == TIME_FORMAT_MEDIA_TIME)
        {
            *pTarget = Source;
            return S_OK;
        }
    }

    return E_INVALIDARG;
}

STDMETHODIMP 
WMFOutputPin::SetTimeFormat(const GUID * pFormat)
{
    // only one pin can control seeking for the whole filter.
    // This method is used to select the seeker.
    if (*pFormat == TIME_FORMAT_MEDIA_TIME)
    {
        // try to select this pin as seeker (if the first to do so)
        if (m_pParser->SelectSeekingPin(this))
        {
            return S_OK;
        } else
        {
            return E_NOTIMPL;
        }
    } else if (*pFormat == TIME_FORMAT_NONE)
    {
        // deselect ourself, if we were the controlling pin
        m_pParser->DeselectSeekingPin(this);
        return S_OK;
    } else
    {
        // no other formats supported
        return E_NOTIMPL;
    }
}

STDMETHODIMP 
WMFOutputPin::GetDuration(LONGLONG *pDuration)
{
    *pDuration = m_pParser->GetDuration();
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::GetStopPosition(LONGLONG *pStop)
{
    REFERENCE_TIME tStart, tStop;
    double dRate;
    m_pParser->GetSeekingParams(&tStart, &tStop, &dRate);
    if (tStop < 0)
    {
        tStop = m_pParser->GetDuration();
    }
    *pStop = tStop;
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::GetCurrentPosition(LONGLONG *pCurrent)
{
    // this method is not supposed to report the previous start
    // position, but rather where we are now. This is normally
    // implemented by renderers, not parsers
    return E_NOTIMPL;
}

STDMETHODIMP 
WMFOutputPin::SetPositions(
                                 LONGLONG * pCurrent, 
                                 DWORD dwCurrentFlags, 
                                 LONGLONG * pStop, 
                                 DWORD dwStopFlags)
{
    // for media player, with the aggregation bug in DShow, it
    // is better to return success and ignore the call if we are
    // not the controlling pin
    if (!m_pParser->SelectSeekingPin(this))
    {
        return S_OK;
    }

    // fetch current properties
    REFERENCE_TIME tStart, tStop;
    double dRate;
    m_pParser->GetSeekingParams(&tStart, &tStop, &dRate);
    dwCurrentFlags &= AM_SEEKING_PositioningBitsMask;

    if (dwCurrentFlags == AM_SEEKING_AbsolutePositioning)
    {
        tStart = *pCurrent;
    } else if (dwCurrentFlags == AM_SEEKING_RelativePositioning)
    {
        tStart += *pCurrent;
    }

    dwStopFlags &= AM_SEEKING_PositioningBitsMask;
    if (dwStopFlags == AM_SEEKING_AbsolutePositioning)
    {
        tStop = *pStop;
    } else if (dwStopFlags == AM_SEEKING_IncrementalPositioning)
    {
        tStop = *pStop + tStart;
    } else
    {
        if (dwStopFlags == AM_SEEKING_RelativePositioning)
        {
            if (tStop < 0)
            {
                tStop = m_pParser->GetDuration();
            }
            tStop += *pStop;
        }
    }

    if (dwCurrentFlags)
    {
        return m_pParser->Seek(tStart, tStop, dRate);
    } else if (dwStopFlags)
    {
        // stop change only
        return m_pParser->SetStopTime(tStop);
    } else
    {
        // no operation required
        return S_FALSE;
    }

}

STDMETHODIMP 
WMFOutputPin::GetPositions(LONGLONG * pCurrent, LONGLONG * pStop)
{
    REFERENCE_TIME tStart, tStop;
    double dRate;
    m_pParser->GetSeekingParams(&tStart, &tStop, &dRate);
    *pCurrent = tStart;
    if (tStop < 0)
    {
        tStop = m_pParser->GetDuration();
    }
    *pStop = tStop;
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::GetAvailable(LONGLONG * pEarliest, LONGLONG * pLatest)
{
    if (pEarliest != NULL)
    {
        *pEarliest = 0;
    }
    if (pLatest != NULL)
    {
        *pLatest = m_pParser->GetDuration();
    }
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::SetRate(double dRate)
{
    HRESULT hr = S_OK;
    if (m_pParser->SelectSeekingPin(this))
    {
        hr = m_pParser->SetRate(dRate);
    }
    return hr;
}



STDMETHODIMP 
WMFOutputPin::GetRate(double * pdRate)
{
    REFERENCE_TIME tStart, tStop;
    double dRate;
    m_pParser->GetSeekingParams(&tStart, &tStop, &dRate);
    *pdRate = dRate;
    return S_OK;
}

STDMETHODIMP 
WMFOutputPin::GetPreroll(LONGLONG * pllPreroll)
{
    // don't need to allow any preroll time for us
    *pllPreroll = 0;
    return S_OK;
}



// INSSBuffer wrapper object ------------------------

EncapsulateSample::EncapsulateSample(IMediaSample* pSample)
: CUnknown(NAME("EncapsulateSample"), NULL),
  m_pSample(pSample)
{
    // for the reader, the WMF documentation seems incorrect.
    // The GetLength method should return the available size, not the
    // used portion
    m_pSample->SetActualDataLength(m_pSample->GetSize());
}

STDMETHODIMP 
EncapsulateSample::NonDelegatingQueryInterface(REFIID iid, void** ppv)
{
    if (iid == IID_INSSBuffer)
    {
        return GetInterface((INSSBuffer*)this, ppv);
    } else if (iid == __uuidof(IEncapsulatedAccess))
    {
        return GetInterface((IEncapsulatedAccess*)this, ppv);
    } else {
        return CUnknown::NonDelegatingQueryInterface(iid, ppv);
    }
}

STDMETHODIMP
EncapsulateSample::GetLength(DWORD *pdwLength)
{
    if (m_pSample == NULL)
    {
        return E_NOINTERFACE;
    }
    *pdwLength = m_pSample->GetActualDataLength();
    return S_OK;
}

STDMETHODIMP
EncapsulateSample::SetLength(DWORD dwLength)
{
    if (m_pSample == NULL)
    {
        return E_NOINTERFACE;
    }
    return m_pSample->SetActualDataLength(dwLength);
}

STDMETHODIMP
EncapsulateSample::GetMaxLength(DWORD* pdwLength)
{
    if (m_pSample == NULL)
    {
        return E_NOINTERFACE;
    }
    *pdwLength = m_pSample->GetSize();
    return S_OK;
}

STDMETHODIMP
EncapsulateSample::GetBuffer(BYTE** ppdwBuffer)
{
    if (m_pSample == NULL)
    {
        return E_NOINTERFACE;
    }
    return m_pSample->GetPointer(ppdwBuffer);
}

STDMETHODIMP
EncapsulateSample::GetBufferAndLength(BYTE** ppdwBuffer, DWORD* pdwLength)
{
    if (m_pSample == NULL)
    {
        return E_NOINTERFACE;
    }
    *pdwLength = m_pSample->GetActualDataLength();
    return m_pSample->GetPointer(ppdwBuffer);
}

STDMETHODIMP
EncapsulateSample::GetEncapsulatedObject(IUnknown** ppUnknown)
{
    *ppUnknown = m_pSample.Detach();
    return S_OK;
}
