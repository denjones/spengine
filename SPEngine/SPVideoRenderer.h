//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoRenderer.h the header file of SPVideoRenderer class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace SPEngine
{
	//-----------------------------------------------------------------------------
	// Define GUID for Texture Renderer
	// {71771540-2017-11cf-AE26-0020AFD79767}
	//-----------------------------------------------------------------------------
	struct __declspec(uuid("{71771540-2017-11cf-ae26-0020afd79767}")) CLSID_TextureRenderer;

	class SPVideoTexture;
	class SPDShowData;

	//////////////////////////////////////////////////////////////////////
	/// @brief SPVideoRenderer DShow filter to render the pins onto a texture.
	///
	//////////////////////////////////////////////////////////////////////
	class SPVideoRenderer : public CBaseVideoRenderer
	{
		CCritSec			m_lock;
		bool				m_waitingToUpdate;
		bool				m_needToBeUpdated;
		SPVideoTexture*		m_videoTexture;
		SPDShowData*		m_dShowData;
		bool				m_hw_yuv;
		bool				m_typeSet;
		D3DFORMAT			m_texture_format;
		int					m_bit_per_pixel;

		BOOL m_bUseDynamicTextures;
		LONG m_lVidWidth;			///< Video width
		LONG m_lVidHeight;			///< Video Height
		LONG m_lVidPitch;			///< Video Pitch

	public:
		SPVideoRenderer(SPDShowData* dShow, LPUNKNOWN pUnk, HRESULT *phr);
		virtual ~SPVideoRenderer();

	public:
		/// @name Implement methods.
		/// @{

		/// @brief Check whether format acceptable.
		HRESULT CheckMediaType(const CMediaType *pmt );

		/// @brief Video format notification.
		HRESULT SetMediaType(const CMediaType *pmt );

		/// @brief Render video sample.
		HRESULT DoRenderSample(IMediaSample *pMediaSample); 

		/// @}
		/// @name Texture Methods
		/// @{
		bool SetTexture(SPVideoTexture* setVideo);
		bool ResizeTexture();
		bool UpdateTexture();
		/// @}
	};
}

