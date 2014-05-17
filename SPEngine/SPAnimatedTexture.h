//////////////////////////////////////////////////////////////////////////
/// @file		SPAnimatedTexture.h the header file of SPAnimatedTexture class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-18
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "SPTexture.h"

namespace SPEngine
{

	//////////////////////////////////////////////////////////////////////
	/// @brief SPAnimatedTexture class to extend SPTexture class, so that 
	/// it cam produce sprite animation.
	//////////////////////////////////////////////////////////////////////
	class SPAnimatedTexture : public SPTexture
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
		void SetRow(int setRow);
		int GetRow();
		void SetColumn(int setCol);
		int GetColumn();
		void SetFPS(float setFPS);
		float GetFPS();
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
		void Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFPS);
		void Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFPS, 
			D3DXVECTOR2 setOrigin);		
		void Load(
			SPString path,
			int setRow,
			int setColumn, 
			int setFrame,
			int setFPS, 
			D3DXVECTOR2 setOrigin);
		void Reload();
		/// @}

		/// @name Update and draw
		/// @{
		void Update(float timeElapsed);
		void DrawFrame();
		/// @}

		/// @name Action
		/// @{
		void Reset();
		void Stop();
		void Play();
		void Pause();
		void Remove();

		virtual SPString GetTextureType();

		/// @}		
	};

	typedef SPPointer<SPAnimatedTexture> SPAnimatedTexturePtr;
}

