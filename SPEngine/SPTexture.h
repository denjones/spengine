//////////////////////////////////////////////////////////////////////////
/// @file		SPTexture.h the header file of SPTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-9
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <d3dx9tex.h>
#include "SPString.h"
#include "SPRectangle.h"
#include "SPHandle.h"
#include "SPPointer.h"
#include "ISPLoadable.h"

using namespace std;

namespace SPEngine
{
	//////////////////////////////////////////////////////////////////////
	/// @brief SPTextureTag just a tag passed to the handle.
	///
	//////////////////////////////////////////////////////////////////////
	struct SPTextureTag {};

	//////////////////////////////////////////////////////////////////////
	/// @brief SPTexture class to encapsulate D3DTexture.
	///
	//////////////////////////////////////////////////////////////////////
	class SPTexture : public ISPLoadable
	{
	protected:
		LPDIRECT3DTEXTURE9 texture; ///< Inner D3D texture pointer.
		D3DFORMAT format;			///< Texture format.
		SPString path;				///< The path / name of the texture.
		int width;					///< Width of the texture.
		int height;					///< Height of the texture.
		bool isRenderTarget;
		D3DXCOLOR backgroundColor;

		/// @name Properties
		/// @{
	public:
		const LPDIRECT3DTEXTURE9 GetD3DTexture() const { return texture; }
		const int GetWidth() const { return width; }
		const int GetHeight() const { return height; }
		const D3DFORMAT GetFormat() const { return format; }
		const D3DXCOLOR GetBackgroundColor() const { return backgroundColor; }
		const bool IsRenderTarget() const { return isRenderTarget; }
		const SPString GetPath() const { return path; }
		virtual SPRectangle SourceRectangle();
		/// @}

	friend class SPTextureManager;
	friend class SPPointer<SPTexture>;

	protected:
		SPTexture(void);

		//SPTexture(const SPTexture&);

		SPTexture(
			LPDIRECT3DDEVICE9 pDevice,
			LPCSTR		pSrcFile,
			UINT		setWidth,
			UINT		setHeight,
			UINT		MipLevels,
			DWORD		Usage,
			D3DFORMAT	Format,
			D3DPOOL		Pool,
			DWORD		Filter,
			DWORD		MipFilter,
			D3DCOLOR	ColorKey);

		SPTexture(SPString path);

		virtual ~SPTexture(void);

		
		/// @name Load/Unload function
		/// @{
		private:
		/// @brief Load texture for sprite manager.
		bool Load(SPString path);

		/// @brief Load texture for 3D use.
		bool Load(
			LPDIRECT3DDEVICE9 pDevice,
			LPCSTR		pSrcFile,
			UINT		setWidth,
			UINT		setHeight,
			UINT		MipLevels,
			DWORD		Usage,
			D3DFORMAT	Format,
			D3DPOOL		Pool,
			DWORD		Filter,
			DWORD		MipFilter, 
			D3DCOLOR	ColorKey);

		bool CreateBlank(int setWidth, int setHeight);
		bool CreateRenderTarget(int setWidth, int setHeight, D3DXCOLOR setColor);

	public:
		bool Fill(D3DCOLOR color);

		/// @brief Reload texture.
		bool Load();

		/// @brief Reload texture after unloaded.
		virtual bool Reload();

		/// @brief Unload texture.
		bool Unload();
		/// @}
	};

	typedef SPPointer<SPTexture> SPTexturePtr;
}


