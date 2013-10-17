//////////////////////////////////////////////////////////////////////////
/// @file		SPAnimatedTexture.h the header file of SPAnimatedTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-18
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPUpdatableTexture.h"

namespace SPEngine
{

	//////////////////////////////////////////////////////////////////////
	/// @brief SPAnimatedTexture class to extend SPTexture class, so that 
	/// it cam produce sprite animation.
	//////////////////////////////////////////////////////////////////////
	class SPAnimatedTexture : public SPUpdatableTexture
	{
	protected:
		int		row, column;	///< Number of rows and columns.
		int		frameCount;		///< Total frames of the animation.		
		int		frame;			///< Current frame.
		float	timePerFrame;	///< Lasting time of one frame.
		float	totalElapsed;	///< Elapsed time since created.
		bool	isPaused;		///< Is paused.
		bool	isToBeRemoved;	///< To flag if the animation can be removed.
		D3DXVECTOR2 origin;		///< The frame to start at.

	public:
		/// @name Properties
		/// @{
		SPRectangle SourceRectangle();
		bool IsToBeRemoved();
		bool IsPause();
		bool SetRow(int setRow);
		bool SetColumn(int setCol);
		bool SetFPS(float setFPS);
		/// @}

	public:
		SPAnimatedTexture(void);
		SPAnimatedTexture(
			SPString setFilename, 
			int setRow,
			int setColumn, 
			int setFPS, 
			D3DXVECTOR2 setOrigin);
		SPAnimatedTexture(
			SPString setFilename, 
			int setRow, 
			int setColumn,
			int setFPS);
		SPAnimatedTexture(
			SPString setFilename,
			int setRow, 
			int setColumn,
			int setFrame, 
			int setFPS);
		SPAnimatedTexture(
			SPString	setFilename,
			int		setRow, 
			int		setColumn, 
			int		setFrame, 
			int		setFPS,
			D3DXVECTOR2 setOrigin);
		virtual ~SPAnimatedTexture(void);

		/// @name Load function
		/// @{
		bool Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFPS);
		bool Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFPS, 
			D3DXVECTOR2 setOrigin);		
		bool Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFrame,
			int setFPS, 
			D3DXVECTOR2 setOrigin);
		bool Reload();
		/// @}

		/// @name Update and draw
		/// @{
		bool Update(float timeElapsed);
		bool DrawFrame();
		/// @}

		/// @name Action
		/// @{
		bool Reset();
		bool Stop();
		bool Play();
		bool Pause();
		bool Remove();
		/// @}		
	};

	typedef SPPointer<SPAnimatedTexture> SPAnimatedTexturePtr;
}

