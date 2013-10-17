#pragma once

namespace SPEngine
{
	//-----------------------------------------------------------------------------
	// Define GUID for Texture Renderer
	// {71771540-2017-11cf-AE26-0020AFD79767}
	//-----------------------------------------------------------------------------
	struct __declspec(uuid("{71771540-2017-11cf-ae26-0020afd79767}")) CLSID_TextureRenderer;

	class VideoTexture;

	class VideoRenderer : public CBaseVideoRenderer
	{
		bool			m_hw_yuv;
		VideoTexture*	video;
		D3DFORMAT		m_texture_format;
		int				m_bit_per_pixel;

		BOOL m_bUseDynamicTextures;
		LONG m_lVidWidth;	// Video width
		LONG m_lVidHeight;  // Video Height
		LONG m_lVidPitch;   // Video Pitch

	public:
		VideoRenderer(VideoTexture* setVideo, LPUNKNOWN pUnk, HRESULT *phr);
		~VideoRenderer();

	public:
		HRESULT CheckMediaType(const CMediaType *pmt );     // Format acceptable?
		HRESULT SetMediaType(const CMediaType *pmt );       // Video format notification
		HRESULT DoRenderSample(IMediaSample *pMediaSample); // New video sample
	};
}

