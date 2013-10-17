#pragma once
#include <smartptr.h>
#include "BaseVideoRenderer.h"
#include "Texture3D.h"

namespace SPEngine
{
	const long MIN_VOLUME = -10000;
	const long MAX_VOLUME = 0;

	class VideoManager;

	enum PlaybackState
	{
		STATE_RUNNING,
		STATE_PAUSED,
		STATE_STOPPED,
		STATE_CLOSED
	};

	struct GraphEventCallback
	{
		virtual void OnGraphEvent(long eventCode, LONG_PTR param1, LONG_PTR param2) = 0;
	};

	class VideoTexture2 : public Texture3D
	{
		friend class VideoRenderer2;

		CCritSec g_Lock;

		PlaybackState	m_state;

		HWND			m_hwndVideo;	// Video clipping window
		HWND			m_hwndEvent;	// Window to receive events
		UINT			m_EventMsg;		// Windows message for graph events

		DWORD			m_seekCaps;		// Caps bits for IMediaSeeking

		// Audio
		BOOL            m_bAudioStream; // Is there an audio stream?
		long			m_lVolume;		// Current volume (unless muted)
		BOOL			m_bMute;		// Volume muted?		

		IGraphBuilder	*m_pGraph;
		IMediaControl	*m_pControl;
		IMediaEventEx	*m_pEvent;
		IMediaSeeking	*m_pSeek;
		IBasicAudio		*m_pAudio;
		IBaseFilter		*m_pRenderer;

		BaseVideoRenderer   *m_pVideo;

		LPDIRECT3DDEVICE9	g_pd3dDevice;
		D3DFORMAT			g_TextureFormat;

	public:
		VideoTexture2(void);
		VideoTexture2(HWND hwndVideo);
		~VideoTexture2(void);

		HRESULT SetEventWindow(HWND hwnd, UINT msg);

		PlaybackState State() const { return m_state; }

		HRESULT OpenFile(VideoManager* manager, const WCHAR* sFileName);
	
		// Streaming
		HRESULT Play();
		HRESULT Pause();
		HRESULT Stop();

		// VMR functionality
		BOOL    HasVideo() const;
		HRESULT UpdateVideoWindow(const LPRECT prc);
		HRESULT Repaint(HDC hdc);
		HRESULT DisplayModeChanged();

		// events
		HRESULT HandleGraphEvent(GraphEventCallback *pCB);

		// seeking
		BOOL	CanSeek() const;
		HRESULT SetPosition(REFERENCE_TIME pos);
		HRESULT GetDuration(LONGLONG *pDuration);
		HRESULT GetCurrentPosition(LONGLONG *pTimeNow);

		// Audio
		HRESULT	Mute(BOOL bMute);
		BOOL	IsMuted() const { return m_bMute; }
		HRESULT	SetVolume(long lVolume);
		long	GetVolume() const { return m_lVolume; }


	private:
		HRESULT InitializeGraph();
		void	TearDownGraph();
		HRESULT CreateVideoRenderer();
		HRESULT	RenderStreams(IBaseFilter *pSource);
		HRESULT UpdateVolume();
	};

	HRESULT RemoveUnconnectedRenderer(IGraphBuilder *pGraph, IBaseFilter *pRenderer, BOOL *pbRemoved);

}

