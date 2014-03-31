//////////////////////////////////////////////////////////////////////////
/// @file		SPVideoRenderer.cpp the implement file of SPVideoRenderer class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-23
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPVideoRenderer.h"
#include "SPVideo.h"
#include "SPMessageHelper.h"
#include "SPVideoHelper.h"
#include "SPLogHelper.h"
#include "SPDevice.h"
#include "SPVideoTexture.h"
#include "SPStringHelper.h"

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
	SPVideoRenderer::SPVideoRenderer(SPDShowData* dShow, LPUNKNOWN pUnk, HRESULT *phr )
		: CBaseVideoRenderer(__uuidof(CLSID_TextureRenderer),
		NAME("Texture Renderer"), pUnk, phr),
		m_bUseDynamicTextures(FALSE)
	{
		m_dShowData = dShow;
		m_hw_yuv = false;
		m_videoTexture = NULL;
		m_lVidWidth = 0;
		m_lVidHeight = 0;
		m_typeSet = false;
		m_needToBeUpdated = false;
		m_waitingToUpdate =false;
		
		// Store and AddRef the texture for our use.
		ASSERT(phr);
		if (phr)
			*phr = S_OK;
	}


	//-----------------------------------------------------------------------------
	// VideoRenderer destructor
	//-----------------------------------------------------------------------------
	SPVideoRenderer::~SPVideoRenderer()
	{
		// Do nothing
		m_videoTexture = NULL;
		m_dShowData = NULL;
	}


	//-----------------------------------------------------------------------------
	// CheckMediaType: This method forces the graph to give us an R8G8B8 video
	// type, making our copy to texture memory trivial.
	//-----------------------------------------------------------------------------
	HRESULT SPVideoRenderer::CheckMediaType(const CMediaType *pMediaType)
	{
		HRESULT   hr = E_FAIL;
		VIDEOINFO *pVideoInfo = NULL;

		CheckPointer(pMediaType,E_POINTER);

		// Reject the connection if this is not a video type
		if( *pMediaType->FormatType() != FORMAT_VideoInfo ) 
		{
			return E_INVALIDARG;
		}

		if (*pMediaType->FormatType() == FORMAT_VideoInfo)
		{
			SPLogHelper::WriteLog("[DShow] Testing FORMAT_VideoInfo ... ");
		}

		if (*pMediaType->FormatType() == FORMAT_VideoInfo2)
		{
			SPLogHelper::WriteLog("[DShow] Testing FORMAT_VideoInfo2 ... ");
		}


		// Only accept RGB24 video
		pVideoInfo = (VIDEOINFO *)pMediaType->Format();

		GUID a = *pMediaType->Subtype();
		GUID b = MEDIASUBTYPE_RGB32;
		GUID c = MEDIASUBTYPE_AYUV;
		GUID d = MEDIASUBTYPE_YUY2;

		if (IsEqualGUID( *pMediaType->Type(),   MEDIATYPE_Video))
		{
			if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_NV12))
			{
				SPLogHelper::WriteLog("[DShow] NV12");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_NV24))
			{
				SPLogHelper::WriteLog("[DShow] NV24");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_UYVY))
			{
				SPLogHelper::WriteLog("[DShow] UYVY");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_YUYV))
			{
				SPLogHelper::WriteLog("[DShow] YUYV");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_YUY2))
			{
				SPLogHelper::WriteLog("[DShow] YUY2");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_RGB24))
			{
				SPLogHelper::WriteLog("[DShow] RGB24");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_RGB32))
			{
				SPLogHelper::WriteLog("[DShow] RGB32");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_YV12))
			{
				SPLogHelper::WriteLog("[DShow] YV12");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), MEDIASUBTYPE_IYUV))
			{
				SPLogHelper::WriteLog("[DShow] IYUV");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_H264_E))
			{
				SPLogHelper::WriteLog("[DShow] H264_E");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_H264_F))
			{
				SPLogHelper::WriteLog("[DShow] H264_F");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_VC1_A))
			{
				SPLogHelper::WriteLog("[DShow] VC1_A");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_VC1_B))
			{
				SPLogHelper::WriteLog("[DShow] VC1_B");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_VC1_C))
			{
				SPLogHelper::WriteLog("[DShow] VC1_C");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_VC1_D))
			{
				SPLogHelper::WriteLog("[DShow] VC1_D");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_MPG2_A))
			{
				SPLogHelper::WriteLog("[DShow] MPG2_A");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_MPG2_B))
			{
				SPLogHelper::WriteLog("[DShow] MPG2_B");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_MPG2_C))
			{
				SPLogHelper::WriteLog("[DShow] MPG2_C");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_MPG2_D))
			{
				SPLogHelper::WriteLog("[DShow] MPG2_D");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_WM8_A))
			{
				SPLogHelper::WriteLog("[DShow] WM8_A");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_WM8_B))
			{
				SPLogHelper::WriteLog("[DShow] WM8_B");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_WM9_A))
			{
				SPLogHelper::WriteLog("[DShow] WM9_A");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_WM9_B))
			{
				SPLogHelper::WriteLog("[DShow] WM9_B");
			}
			else if (IsEqualGUID( *pMediaType->Subtype(), CLSID_DXVA_WM9_C))
			{
				SPLogHelper::WriteLog("[DShow] WM9_C");
			}
			else
			{
				GUID subtype = *pMediaType->Subtype();
				SPLogHelper::WriteLog(SPStringHelper::Format("[DShow] GUID {%.8x, %.4x, %.4x, {%.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x, %.2x}}",
					subtype.Data1, subtype.Data2, subtype.Data3,
					subtype.Data4[0], subtype.Data4[1], subtype.Data4[2], subtype.Data4[3],
					subtype.Data4[4], subtype.Data4[5], subtype.Data4[6], subtype.Data4[7]));
			}

			if (   IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_UYVY) 
				|| IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YUYV)
				|| IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YUY2)
				|| IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB24)
				|| IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB32)
				//|| IsEqualGUID(*pmt->Subtype(), CLSID_DXVA_H264_E)
				//|| IsEqualGUID(*pmt->Subtype(), MEDIASUBTYPE_NV12)
				|| (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YV12)) && m_hw_yuv)
			{
				hr = S_OK;
			}
		}

		return hr;
	}

	//-----------------------------------------------------------------------------
	// SetMediaType: Graph connection has been made.
	//-----------------------------------------------------------------------------
	HRESULT SPVideoRenderer::SetMediaType(const CMediaType *pMediaType)
	{
		HRESULT hr;

		UINT uintWidth = 2;
		UINT uintHeight = 2;

		if (*pMediaType->FormatType() == FORMAT_VideoInfo)
		{
			VIDEOINFOHEADER* info_header = (VIDEOINFOHEADER*)pMediaType->Format();
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

		if (*pMediaType->FormatType() == FORMAT_VideoInfo2)
		{
			VIDEOINFOHEADER* info_header = (VIDEOINFOHEADER*)pMediaType->Format();
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

		if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_UYVY))
		{
			m_texture_format = D3DFMT_UYVY;
			m_bit_per_pixel = 16;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YUY2) 
			|| IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YUYV))
		{
			m_texture_format = D3DFMT_YUY2;
			m_bit_per_pixel = 16;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_YV12))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB24))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 24;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_RGB32))
		{
			m_texture_format = D3DFMT_A8R8G8B8;
			m_bit_per_pixel = 32;
			hr = S_OK;
		} 
		else if (IsEqualGUID(*pMediaType->Subtype(), MEDIASUBTYPE_NV12))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		}

		if (IsEqualGUID(*pMediaType->Subtype(), CLSID_DXVA_H264_E))
		{
			m_texture_format = D3DFMT_X8R8G8B8;
			m_bit_per_pixel = 12;
			hr = S_OK;
		}

		switch (m_texture_format)
		{
			case  D3DFMT_A8R8G8B8:
				m_lVidPitch = (m_lVidWidth * 4 + 4) & ~(4);
				break;
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

		SPLogHelper::WriteLog(SPStringHelper::Format("[DShow] Trying to initialize %dx%dx%d", m_lVidWidth, m_lVidHeight, m_bit_per_pixel));
		if (m_lVidWidth <= 0 || m_lVidHeight <= 0)
		{
			return -1;
		}

		// Retrieve the size of this media type
		
		VIDEOINFO *pviBmp;    // Bitmap info header
		pviBmp = (VIDEOINFO *)pMediaType->Format();

		// here let's check if we can use dynamic textures
		D3DCAPS9 caps;
		ZeroMemory( &caps, sizeof(D3DCAPS9));
		hr = SPDevice::GetSingleton()->GetD3DDevice()->GetDeviceCaps( &caps );
		if( caps.Caps2 & D3DCAPS2_DYNAMICTEXTURES )
		{
			m_bUseDynamicTextures = TRUE;
		}

		uintWidth = m_lVidWidth;
		uintHeight = m_lVidHeight;

		if ((m_texture_format == D3DFMT_YUY2 ||
			m_texture_format == D3DFMT_UYVY))
		{
			if (!m_hw_yuv)
			{
				m_texture_format = D3DFMT_X8R8G8B8;
				SPLogHelper::WriteLog("[DShow] Use CPU YUV transform");
			} 
			else
			{
				SPLogHelper::WriteLog("[DShow] Use GPU YUV transform");
				m_texture_format = D3DFMT_A8L8;
			}
		}

		if (m_bit_per_pixel == 12 && m_hw_yuv)
		{
			m_texture_format = D3DFMT_A8;
			uintHeight = uintHeight * 3 / 2;
		}

		// Create the texture that maps to this media type
		

		//m_video->g_Lock.Unlock();

		m_typeSet = true;

		return S_OK;
	}


	//-----------------------------------------------------------------------------
	// DoRenderSample: A sample has been delivered. Copy it to the texture.
	//-----------------------------------------------------------------------------
	HRESULT SPVideoRenderer::DoRenderSample( IMediaSample * pSample )
	{
		// Critical Section.	
		m_lock.Lock();

		// Check if texture exists.
		if (!m_videoTexture)
		{
			m_lock.Unlock();
			m_needToBeUpdated = false;
			return S_OK;
		}

		m_needToBeUpdated = true;

		m_lock.Unlock();

		while(true)
		{
			m_lock.Lock();
			if (m_waitingToUpdate)
			{
				//m_lock.Unlock();
				break;
			}
			else if (m_dShowData->IsControlling())
			{
				m_needToBeUpdated = false;
				m_lock.Unlock();				
				return S_OK;
			}

			m_lock.Unlock();
		}

		BYTE  *pBmpBuffer, *pTxtBuffer;	// Bitmap buffer, texture buffer
		LONG  lTxtPitch;				// Pitch of bitmap, texture

		BYTE  * pbS = NULL;
		DWORD * pdwS = NULL;
		DWORD * pdwD = NULL;
		LONG row, col, dwordWidth;

		CheckPointer(pSample,E_POINTER);
		CheckPointer(m_videoTexture->texture,E_UNEXPECTED);

		// Get the video bitmap buffer
		pSample->GetPointer( &pBmpBuffer );
		int lSampleSize = pSample->GetSize();
		bool bFilpVertical = m_dShowData->IsFlipVertical();

		// Lock the Texture
		D3DLOCKED_RECT d3dlr;
		if( m_bUseDynamicTextures )
		{
			if( FAILED(m_videoTexture->texture->LockRect(0, &d3dlr, 0, D3DLOCK_DISCARD)))
			{
				m_needToBeUpdated = false;
				m_lock.Unlock();
				return E_FAIL;
			}
		}
		else
		{
			if (FAILED(m_videoTexture->texture->LockRect(0, &d3dlr, 0, 0)))
			{
				m_needToBeUpdated = false;
				m_lock.Unlock();
				return E_FAIL;
			}
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
				if (m_lVidWidth == lTxtPitch && !bFilpVertical)
				{
					//Copy all as is
					lSampleSize = min(m_lVidPitch * m_lVidHeight * 3 / 2, lSampleSize);
					memcpy(pTxtBuffer, pBmpBuffer, lSampleSize);
				} 
				else
				{
					//copy by lines
					if (!bFilpVertical)
					{
						for (row = m_lVidHeight * 3 / 2 - 1; row >= 0 ; row--)
						{
							memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth);
							pTxtBuffer += lTxtPitch;
						}
					}
					else
					{
						for (row = 0; row < m_lVidHeight * 3 / 2; row++)
						{
							memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth);
							pTxtBuffer += lTxtPitch;
						}
					}					
				}
			}
		}
		else if (m_bit_per_pixel == 16)
		{
			//conversion
			if (!m_hw_yuv)
			{
				SPVideoHelper::Convert_UYV2_ARGB((unsigned char*)pBmpBuffer,
					m_lVidWidth, m_lVidHeight, m_lVidPitch, 
					(unsigned char*)pTxtBuffer, lTxtPitch, bFilpVertical);
			}
			else
			{
				if (m_lVidWidth == (m_lVidPitch >> 1) && m_lVidWidth == (lTxtPitch >> 1) && !bFilpVertical)
				{
					//Copy all as is
					lSampleSize = min(m_lVidPitch*m_lVidHeight, lSampleSize);
					memcpy(pTxtBuffer, pBmpBuffer, lSampleSize);
				} 
				else
				{
					//copy by lines
					if (!bFilpVertical)
					{
						for (row = m_lVidHeight - 1; row >= 0; row--)
						{
							memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth * 2);
							pTxtBuffer += lTxtPitch;
						}
					}
					else
					{
						for (row = 0; row < m_lVidHeight; row++)
						{
							memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth * 2);
							pTxtBuffer += lTxtPitch;
						}
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

			if (!bFilpVertical)
			{
				pBmpBuffer = pBmpBuffer + (m_lVidHeight - 1) * m_lVidPitch;

				for (row = m_lVidHeight - 1; row >= 0; row--)
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
					for( col = 0; col < m_lVidWidth % 4; col++)
					{
						*pdwD = 0xFF000000     |
							(pbS[2] << 16) |
							(pbS[1] <<  8) |
							(pbS[0]);
						pdwD++;
						pbS += 3;
					}

					pBmpBuffer  -= m_lVidPitch;
					pTxtBuffer += lTxtPitch;
				}// for rows
			}
			else
			{
				for (row = 0; row< m_lVidHeight; row++)
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
					for( col = 0; col < m_lVidWidth % 4; col++)
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
		}
		else if (m_bit_per_pixel == 32)
		{
			//copy by lines
			if (!bFilpVertical)
			{
				for (row = m_lVidHeight - 1; row >= 0; row--)
				{
					memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth * 4);
					pTxtBuffer += lTxtPitch;
				}
			}
			else
			{
				for (row = 0; row < m_lVidHeight; row++)
				{
					memcpy( pTxtBuffer, pBmpBuffer+(m_lVidPitch * row), m_lVidWidth * 4);
					pTxtBuffer += lTxtPitch;
				}
			}
		}

		HRESULT hr = m_videoTexture->texture->UnlockRect(0);

		// Finish updating.
		m_needToBeUpdated = false;
		m_lock.Unlock();

		// Unlock the Texture
		if (FAILED(hr))
		{
			return E_FAIL;
		}

		return S_OK;
	}

	bool SPVideoRenderer::UpdateTexture()
	{
		// Critical Section.
		m_lock.Lock();		

		if (!m_videoTexture)
		{
			m_lock.Unlock();
			return true;
		}

		if (!m_needToBeUpdated)
		{
			m_lock.Unlock();
			return true;
		}

		m_waitingToUpdate = true;

		m_lock.Unlock();

		while(true)
		{
			m_lock.Lock();
			if (!m_needToBeUpdated)
			{
				m_waitingToUpdate = false;
				m_lock.Unlock();
				break;
			}
			m_lock.Unlock();
		}

		return true;
	}

	bool SPVideoRenderer::ResizeTexture()
	{
		if (!m_typeSet)
		{
			return false;
		}

		HRESULT hr = E_UNEXPECTED;

		if( m_bUseDynamicTextures )
		{
			hr = SPDevice::GetSingleton()->GetD3DDevice()->CreateTexture(
				m_lVidWidth, m_lVidHeight, 1,
				D3DUSAGE_DYNAMIC, m_texture_format, D3DPOOL_DEFAULT,
				&m_videoTexture->texture, NULL);

			if( FAILED(hr))
			{
				m_bUseDynamicTextures = FALSE;
			}
		}
		else			
		{
			hr = SPDevice::GetSingleton()->GetD3DDevice()->CreateTexture(
				m_lVidWidth, m_lVidHeight, 1, 
				0, m_texture_format, D3DPOOL_DEFAULT, //D3DPOOL_MANAGED
				&m_videoTexture->texture, NULL);
		}

		if( FAILED(hr))
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[DShow] WARNING: Could not create the D3DX texture!  hr=0x%x", hr));
			return false;
		}

		// CreateTexture can silently change the parameters on us
		D3DSURFACE_DESC ddsd;
		ZeroMemory(&ddsd, sizeof(ddsd));

		if (FAILED( hr = m_videoTexture->texture->GetLevelDesc(0, &ddsd)))
		{
			SPLogHelper::WriteLog(SPStringHelper::Format("[DShow] WARNING: Could not get level Description of D3DX texture! hr = 0x%x", hr));
			return false;
		}

		SmartPtr<IDirect3DSurface9> pSurf;

		if (SUCCEEDED(hr = m_videoTexture->texture->GetSurfaceLevel(0, &pSurf)))
		{
			pSurf->GetDesc(&ddsd);
		}

		// Save format info
		m_texture_format = ddsd.Format;

		SPLogHelper::WriteLog(SPStringHelper::Format("[DShow] Format accepted (%X) %dx%d", m_texture_format, m_lVidWidth, m_lVidHeight));

		m_videoTexture->height = m_lVidHeight;
		m_videoTexture->width = m_lVidWidth;
		m_videoTexture->format = m_texture_format;

		return true;
	}

	bool SPVideoRenderer::SetTexture( SPVideoTexture* setTex )
	{
		if (!m_typeSet)
		{
			SPLogHelper::WriteLog("[DShow] WARNING: Cannot set render texture. Video not loaded!");
			return false;
		}

		m_videoTexture = setTex;

		if (m_videoTexture)
		{
			ResizeTexture();
		}

		return true;
	}

}