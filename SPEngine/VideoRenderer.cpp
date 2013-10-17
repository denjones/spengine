#include "StdAfx.h"
#include "VideoRenderer.h"
#include "VideoTexture.h"
#include "MessageHelper.h"
#include "VideoHelper.h"
#include "LogHelper.h"

namespace SPEngine
{
	GUID CLSID_DXVA_H264_E = {0x1B81BE68, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_H264_F = {0x1B81BE69, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};

	GUID CLSID_DXVA_VC1_A =  {0x1B81BEA0, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_VC1_B =  {0x1B81BEA1, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_VC1_C =  {0x1B81BEA2, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_VC1_D =  {0x1B81BEA3, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};

	GUID CLSID_DXVA_MPG2_A = {0x1B81BE0A, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_MPG2_B = {0x1B81BE0B, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_MPG2_C = {0x1B81BE0C, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_MPG2_D = {0x1B81BE0D, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};

	GUID CLSID_DXVA_WM8_A =  {0x1B81BE80, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_WM8_B =  {0x1B81BE81, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};

	GUID CLSID_DXVA_WM9_A = {0x1B81BE90, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_WM9_B = {0x1B81BE91, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};
	GUID CLSID_DXVA_WM9_C = {0x1B81BE94, 0xA0C7, 0x11D3, {0xB9, 0x84, 0x00, 0xC0, 0x4F, 0x2E, 0x73, 0xC5}};

	GUID CLSID_NV24 =       {0x3432564E, 0x0000, 0x0010, {0x80, 0x00, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71}};



	//-----------------------------------------------------------------------------
	// VideoRenderer constructor
	//-----------------------------------------------------------------------------
	VideoRenderer::VideoRenderer(VideoTexture* setVideo, LPUNKNOWN pUnk, HRESULT *phr )
		: CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer),
		NAME("Texture Renderer"), pUnk, phr),
		m_bUseDynamicTextures(FALSE)
	{
		m_hw_yuv = false;
		video = setVideo;
		// Store and AddRef the texture for our use.
		ASSERT(phr);
		if (phr)
			*phr = S_OK;
	}


	//-----------------------------------------------------------------------------
	// VideoRenderer destructor
	//-----------------------------------------------------------------------------
	VideoRenderer::~VideoRenderer()
	{
		// Do nothing
		video = NULL;
	}


	//-----------------------------------------------------------------------------
	// CheckMediaType: This method forces the graph to give us an R8G8B8 video
	// type, making our copy to texture memory trivial.
	//-----------------------------------------------------------------------------
	HRESULT VideoRenderer::CheckMediaType(const CMediaType *pmt)
	{
		HRESULT   hr = E_FAIL;
		VIDEOINFO *pvi = NULL;

		CheckPointer(pmt,E_POINTER);

		// Reject the connection if this is not a video type
		if( *pmt->FormatType() != FORMAT_VideoInfo ) 
		{
			return E_INVALIDARG;
		}

		if (*pmt->FormatType() == FORMAT_VideoInfo)
		{
			LogHelper::WriteLog(" Testing FORMAT_VideoInfo ");
		}

		if (*pmt->FormatType() == FORMAT_VideoInfo2)
		{
			LogHelper::WriteLog(" Testing FORMAT_VideoInfo2 ");
		}


		// Only accept RGB24 video
		pvi = (VIDEOINFO *)pmt->Format();

		GUID a = *pmt->Subtype();
		GUID b = MEDIASUBTYPE_RGB32;
		GUID c = MEDIASUBTYPE_AYUV;
		GUID d = MEDIASUBTYPE_YUY2;

		if (IsEqualGUID( *pmt->Type(),   MEDIATYPE_Video))
		{
			if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_NV12))
				LogHelper::WriteLog(" NV12\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_NV24))
				LogHelper::WriteLog(" NV24\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_UYVY))
				LogHelper::WriteLog(" UYVY\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_YUYV))
				LogHelper::WriteLog(" YUYV\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_YUY2))
				LogHelper::WriteLog(" YUY2\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_RGB24))
				LogHelper::WriteLog(" RGB24\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_RGB32))
				LogHelper::WriteLog(" RGB32\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_YV12))
				LogHelper::WriteLog(" YV12\n");
			else if (IsEqualGUID( *pmt->Subtype(), MEDIASUBTYPE_IYUV))
				LogHelper::WriteLog(" IYUV\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_H264_E))
				LogHelper::WriteLog(" H264_E\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_H264_F))
				LogHelper::WriteLog(" H264_F\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_VC1_A))
				LogHelper::WriteLog(" VC1_A\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_VC1_B))
				LogHelper::WriteLog(" VC1_B\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_VC1_C))
				LogHelper::WriteLog(" VC1_C\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_VC1_D))
				LogHelper::WriteLog(" VC1_D\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_MPG2_A))
				LogHelper::WriteLog(" MPG2_A\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_MPG2_B))
				LogHelper::WriteLog(" MPG2_B\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_MPG2_C))
				LogHelper::WriteLog(" MPG2_C\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_MPG2_D))
				LogHelper::WriteLog(" MPG2_D\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_WM8_A))
				LogHelper::WriteLog(" WM8_A\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_WM8_B))
				LogHelper::WriteLog(" WM8_B\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_WM9_A))
				LogHelper::WriteLog(" WM9_A\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_WM9_B))
				LogHelper::WriteLog(" WM9_B\n");
			else if (IsEqualGUID( *pmt->Subtype(), CLSID_DXVA_WM9_C))
				LogHelper::WriteLog(" WM9_C\n");
			else
			{
				GUID subtype = *pmt->Subtype();
				LogHelper::WriteLog(" GUID {%.8x, %.4x, %.4x, {%.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x}}\n",
					subtype.Data1, subtype.Data2, subtype.Data3,
					subtype.Data4[0], subtype.Data4[1], subtype.Data4[2], subtype.Data4[3],
					subtype.Data4[4], subtype.Data4[5], subtype.Data4[6], subtype.Data4[7]);
			}

			if (   IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_UYVY) 
				|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YUYV)
				|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YUY2)
				|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_RGB24)
				//|| IsEqualGUID(*pmt->Subtype(), CLSID_DXVA_H264_E)
				//|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_NV12)
				|| (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YV12)) && m_hw_yuv)
			{
				hr = S_OK;
			}
		}


		return hr;
	}

	//-----------------------------------------------------------------------------
	// SetMediaType: Graph connection has been made.
	//-----------------------------------------------------------------------------
	HRESULT VideoRenderer::SetMediaType(const CMediaType *pmt)
	{
		video->g_Lock.Lock();		

		HRESULT hr;

		UINT uintWidth = 2;
		UINT uintHeight = 2;		

		if (*pmt->FormatType() == FORMAT_VideoInfo)
		{
			VIDEOINFOHEADER* info_header = (VIDEOINFOHEADER*)pmt->Format();
			if (info_header->bmiHeader.biSize == sizeof(BITMAPINFOHEADER))
			{
				m_lVidWidth  = info_header->bmiHeader.biWidth;
				m_lVidHeight = abs(info_header->bmiHeader.biHeight);
			} 
			else
			{
				m_lVidWidth  = abs(info_header->rcSource.right -info_header->rcSource.left);
				m_lVidHeight = abs(info_header->rcSource.bottom-info_header->rcSource.top);
			}
		}

		if (*pmt->FormatType() == FORMAT_VideoInfo2)
		{
			VIDEOINFOHEADER* info_header = (VIDEOINFOHEADER*)pmt->Format();
			if (info_header->bmiHeader.biSize == sizeof(BITMAPINFOHEADER))
			{
				m_lVidWidth  = info_header->bmiHeader.biWidth;
				m_lVidHeight = abs(info_header->bmiHeader.biHeight);
			} else
			{
				m_lVidWidth  = abs(info_header->rcSource.right -info_header->rcSource.left);
				m_lVidHeight = abs(info_header->rcSource.bottom-info_header->rcSource.top);
			}
		}

		video->height = m_lVidHeight;
		video->width = m_lVidWidth;

		if (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_UYVY))
		{
			m_texture_format = D3DFMT_UYVY;
			m_bit_per_pixel = 16;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YUY2) 
			|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YUYV))
		{
			m_texture_format = D3DFMT_YUY2;
			m_bit_per_pixel = 16;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_YV12))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_RGB24))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 24;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_NV12))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		}

		if (IsEqualGUID(*pmt->Subtype(), CLSID_DXVA_H264_E))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		}

		switch (m_texture_format)
		{
			case D3DFMT_X8R8G8B8:
			case D3DFMT_R8G8B8:
				if (m_bit_per_pixel == 12 && m_hw_yuv)
				{
					m_lVidPitch = m_lVidWidth;
				}
				else
				{
					m_lVidPitch  = (m_lVidWidth * 3 + 3) & ~(3); // We are forcing RGB24
				}
				break;
			case D3DFMT_YUY2:
			case D3DFMT_UYVY:
			case D3DFMT_A8L8:
				m_lVidPitch  = (m_lVidWidth * 2); // We are forcing 16bpp
				break;
			default:
				return E_FAIL;
				break;
		}

		LogHelper::WriteLog("Try to initialize %dx%dx%d\n", m_lVidWidth, m_lVidHeight, m_bit_per_pixel);
		if (m_lVidWidth <= 0 || m_lVidHeight <= 0)
		{
			return -1;
		}


		// Retrieve the size of this media type
		
		VIDEOINFO *pviBmp;                      // Bitmap info header
		pviBmp = (VIDEOINFO *)pmt->Format();

		//m_lVidWidth  = pviBmp->bmiHeader.biWidth;
		//m_lVidHeight = abs(pviBmp->bmiHeader.biHeight);
		//m_lVidPitch  = (m_lVidWidth * 3 + 3) & ~(3); // We are forcing RGB24

		

		// here let's check if we can use dynamic textures
		D3DCAPS9 caps;
		ZeroMemory( &caps, sizeof(D3DCAPS9));
		hr = video->g_pd3dDevice->GetDeviceCaps( &caps );
		if( caps.Caps2 & D3DCAPS2_DYNAMICTEXTURES )
		{
			m_bUseDynamicTextures = TRUE;
		}

		//if( caps.TextureCaps & D3DPTEXTURECAPS_POW2 )
		//{
		//	while( (LONG)uintWidth < m_lVidWidth )
		//	{
		//		uintWidth = uintWidth << 1;
		//	}
		//	while( (LONG)uintHeight < m_lVidHeight )
		//	{
		//		uintHeight = uintHeight << 1;
		//	}
		//	//video->UpgradeGeometry( m_lVidWidth, uintWidth, m_lVidHeight, uintHeight);
		//}
		//else
		//{
			uintWidth = m_lVidWidth;
			uintHeight = m_lVidHeight;
		//}		

		if ((m_texture_format == D3DFMT_YUY2 ||
			m_texture_format == D3DFMT_UYVY))
		{
			if (!m_hw_yuv)
			{
				m_texture_format = D3DFMT_X8R8G8B8;
				LogHelper::WriteLog(" Use CPU yuv transform\n");
			} 
			else
			{
				LogHelper::WriteLog(" Use GPU yuv transform\n");
				m_texture_format = D3DFMT_A8L8;
			}
		}

		if (m_bit_per_pixel == 12 && m_hw_yuv)
		{
			m_texture_format = D3DFMT_A8;
			uintHeight = uintHeight * 3 / 2;
		}

		// Create the texture that maps to this media type
		hr = E_UNEXPECTED;
		if( m_bUseDynamicTextures )
		{
			hr = video->g_pd3dDevice->CreateTexture(uintWidth, uintHeight, 1,
				D3DUSAGE_DYNAMIC, m_texture_format, D3DPOOL_DEFAULT,
				&video->texture, NULL);
			//g_pachRenderMethod = g_achDynTextr;
			if( FAILED(hr))
			{
				m_bUseDynamicTextures = FALSE;
			}
		}

		if( FALSE == m_bUseDynamicTextures )
		{
			hr = video->g_pd3dDevice->CreateTexture(uintWidth, uintHeight, 1, 
				0, m_texture_format, D3DPOOL_MANAGED,
				&video->texture, NULL);
			//g_pachRenderMethod = g_achCopy;
		}

		if( FAILED(hr))
		{
			LogHelper::WriteLog(TEXT("Could not create the D3DX texture!  hr=0x%x"), hr);
			return hr;
		}

		// CreateTexture can silently change the parameters on us
		D3DSURFACE_DESC ddsd;
		ZeroMemory(&ddsd, sizeof(ddsd));

		if ( FAILED( hr = video->texture->GetLevelDesc( 0, &ddsd ) ) ) {
			LogHelper::WriteLog(TEXT("Could not get level Description of D3DX texture! hr = 0x%x"), hr);
			return hr;
		}

		SmartPtr<IDirect3DSurface9> pSurf;

		if (SUCCEEDED(hr = video->texture->GetSurfaceLevel(0, &pSurf)))
			pSurf->GetDesc(&ddsd);

		// Save format info
		 m_texture_format = ddsd.Format;

		//if (video->g_TextureFormat != D3DFMT_X8R8G8B8 &&
		//	video->g_TextureFormat != D3DFMT_A1R5G5B5) {
		//		//Msg(TEXT("Texture is format we can't handle! Format = 0x%x"), g_TextureFormat);
		//		return VFW_E_TYPE_NOT_ACCEPTED;
		//}

		LogHelper::WriteLog(" Format accepted (%X) %dx%d\n", m_texture_format, m_lVidWidth, m_lVidHeight);

		video->g_Lock.Unlock();

		return S_OK;
	}


	//-----------------------------------------------------------------------------
	// DoRenderSample: A sample has been delivered. Copy it to the texture.
	//-----------------------------------------------------------------------------
	HRESULT VideoRenderer::DoRenderSample( IMediaSample * pSample )
	{
		video->g_Lock.Lock();

		BYTE  *pBmpBuffer, *pTxtBuffer; // Bitmap buffer, texture buffer
		LONG  lTxtPitch;                // Pitch of bitmap, texture

		BYTE  * pbS = NULL;
		DWORD * pdwS = NULL;
		DWORD * pdwD = NULL;
		UINT row, col, dwordWidth;

		CheckPointer(pSample,E_POINTER);
		CheckPointer(video->texture,E_UNEXPECTED);

		// Get the video bitmap buffer
		pSample->GetPointer( &pBmpBuffer );
		int lSampleSize = pSample->GetSize();

		// Lock the Texture
		D3DLOCKED_RECT d3dlr;
		if( m_bUseDynamicTextures )
		{
			if( FAILED(video->texture->LockRect(0, &d3dlr, 0, D3DLOCK_DISCARD)))
				return E_FAIL;
		}
		else
		{
			if (FAILED(video->texture->LockRect(0, &d3dlr, 0, 0)))
				return E_FAIL;
		}

		// Get the texture buffer & pitch
		pTxtBuffer = static_cast<byte *>(d3dlr.pBits);
		lTxtPitch = d3dlr.Pitch;

		//m_bit_per_pixel = 16;

		// Copy the bits
		if (m_bit_per_pixel == 8)
		{
			lSampleSize = min(m_lVidPitch * m_lVidHeight * 3 / 2, lSampleSize);
			memcpy(pTxtBuffer, pBmpBuffer, lSampleSize);
		} 
		else if (m_bit_per_pixel == 12)
		{
			if (m_hw_yuv)
			{
				if (m_lVidWidth == lTxtPitch)
				{
					//Copy all as is
					lSampleSize = min(m_lVidPitch * m_lVidHeight * 3 / 2, lSampleSize);
					memcpy(pTxtBuffer, pBmpBuffer, lSampleSize);
				} 
				else
				{
					//copy by lines
					for (row = 0; row < m_lVidHeight * 3 / 2; row++)
					{
						memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth);
						pTxtBuffer += lTxtPitch;
					}
				}
			}
		}
		else if (m_bit_per_pixel == 16)
		{
			//conversion
			if (!m_hw_yuv)
			{
				VideoHelper::Convert_UYV2_ARGB((unsigned char*)pBmpBuffer, m_lVidWidth, m_lVidHeight, m_lVidPitch, (unsigned char*)pTxtBuffer, lTxtPitch);
			}
			else
			{
				if (m_lVidWidth == (m_lVidPitch >> 1) && m_lVidWidth == (lTxtPitch >> 1))
				{
					//Copy all as is
					lSampleSize = min(m_lVidPitch*m_lVidHeight, lSampleSize);
					memcpy(pTxtBuffer, pBmpBuffer, lSampleSize);
				} 
				else
				{
					//copy by lines
					for (row = 0; row < m_lVidHeight; row++)
					{
						memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth * 2);
						pTxtBuffer += lTxtPitch;
					}
				}
			}
		} 
		else if (m_bit_per_pixel == 24)
		{
			// Instead of copying data bytewise, we use DWORD alignment here.
			// We also unroll loop by copying 4 pixels at once.
			//
			// original BYTE array is [b0][g0][r0][b1][g1][r1][b2][g2][r2][b3][g3][r3]
			//
			// aligned DWORD array is     [b1 r0 g0 b0][g2 b2 r1 g1][r3 g3 b3 r2]
			//
			// We want to transform it to [ff r0 g0 b0][ff r1 g1 b1][ff r2 g2 b2][ff r3 b3 g3]
			// below, bitwise operations do exactly this.

			dwordWidth = m_lVidWidth / 4; // aligned width of the row, in DWORDS
			// (pixel by 3 bytes over sizeof(DWORD))

			for (row = 0; row< (UINT)m_lVidHeight; row++)
			{
				pdwS = ( DWORD*)pBmpBuffer;
				pdwD = ( DWORD*)pTxtBuffer;

				for( col = 0; col < dwordWidth; col ++ )
				{
					pdwD[0] =  pdwS[0] | 0xFF000000;
					pdwD[1] = ((pdwS[1]<<8)  | 0xFF000000) | (pdwS[0]>>24);
					pdwD[2] = ((pdwS[2]<<16) | 0xFF000000) | (pdwS[1]>>16);
					pdwD[3] = 0xFF000000 | (pdwS[2]>>8);
					pdwD +=4;
					pdwS +=3;
				}

				// we might have remaining (misaligned) bytes here
				pbS = (BYTE*) pdwS;
				for( col = 0; col < (UINT)m_lVidWidth % 4; col++)
				{
					*pdwD = 0xFF000000     |
						(pbS[2] << 16) |
						(pbS[1] <<  8) |
						(pbS[0]);
					pdwD++;
					pbS += 3;
				}

				pBmpBuffer  += m_lVidPitch;
				pTxtBuffer += lTxtPitch;
			}// for rows
		}

		HRESULT hr = video->texture->UnlockRect(0);
		
		video->g_Lock.Unlock();

		// Unlock the Texture
		if (FAILED(hr))
			return E_FAIL;

		return S_OK;
	}
}