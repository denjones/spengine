//////////////////////////////////////////////////////////////////////////
/// @file		SPDShowData.h the header file of SPDShowData class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#include <DShow.h>
#include "SPPointer.h"
#include "SPVideoRenderer.h"
#include <smartptr.h>
#include "SPFileSourceFilter.h"
#include "SPString.h"

using namespace std;

namespace SPEngine
{
	const long MIN_VOLUME = -10000;
	const long MAX_VOLUME = 0;

	struct GraphEventCallback
	{
		virtual bool OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2) = 0;
	};

	//////////////////////////////////////////////////////////////////////
	/// @brief SPDShowData to hold DShow data, including filters and filter graph.
	///
	//////////////////////////////////////////////////////////////////////
	class SPDShowData
	{
	public:
		SPDShowData();
		~SPDShowData();

	protected:
		CCritSec	controlLock;

		SmartPtr<IFilterGraph>		m_pBase;
		SmartPtr<IGraphBuilder>		m_pGraph;
		SmartPtr<IMediaControl>		m_pControl;
		SmartPtr<IMediaEventEx>		m_pEvent;
		SmartPtr<IMediaSeeking>		m_pSeek;
		SmartPtr<IBasicAudio>		m_pAudio;
		SmartPtr<SPFileSourceFilter>m_pSource;
		SmartPtr<SPVideoRenderer>	m_pRenderer;

		HWND			m_hwndVideo;	///< Video clipping window
		HWND			m_hwndEvent;	///< Window to receive events
		UINT			m_EventMsg;		///< Windows message for graph events
		DWORD			m_seekCaps;		///< Caps bits for IMediaSeeking

		// Audio
		//BOOL            m_bAudioStream; ///< Is there an audio stream?
		long			m_lVolume;		///< Current volume (unless muted)
		BOOL			m_bMute;		///< Volume muted?		
		bool			m_bControlling;
		bool			m_bFilpVertical;

	public:
		SmartPtr<IFilterGraph> GetBase(){ return	m_pBase;}
		SmartPtr<IGraphBuilder>	GetGraph(){ return	m_pGraph;}
		SmartPtr<IMediaControl>	GetControl(){ return m_pControl;}
		SmartPtr<IMediaEventEx>	GetEvent(){ return	m_pEvent;}
		SmartPtr<IMediaSeeking>	GetSeek(){ return m_pSeek;}
		SmartPtr<IBasicAudio> GetAudio(){ return m_pAudio;}
		SmartPtr<SPFileSourceFilter> GetSource(){ return m_pSource;}
		SmartPtr<SPVideoRenderer> GetRenderer(){ return m_pRenderer;}

		float GetPlayingPosition();

		DWORD GetSeekCap(){return m_seekCaps;}
		HRESULT SetMute(bool isMute){m_bMute = isMute; return UpdateVolume();}
		HRESULT SetVolume(long setVolume){m_lVolume = setVolume; return UpdateVolume();}

		bool Load(SPString fileName);
		bool Unload();

		HRESULT UpdateVolume();
		HRESULT RenderStreams(SmartPtr<SPFileSourceFilter> pSource);

		// events
		HRESULT HandleGraphEvent(GraphEventCallback *pCB);
		HRESULT SetEventWindow(HWND hwnd, UINT msg);

		void LockControl();
		void UnlockControl();
		bool IsControlling();
		bool IsFlipVertical();
		bool SetFlipVertical(bool setFlip);
		bool IsFilpVertical() { return m_bFilpVertical; }
	};

	typedef SPPointer<SPDShowData> SPDShowDataPtr;

	HRESULT RemoveUnconnectedRenderer(
		SmartPtr<IGraphBuilder> pGraph,
		SmartPtr<IBaseFilter> pRenderer,
		BOOL *pbRemoved);
}