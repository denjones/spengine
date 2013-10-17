//////////////////////////////////////////////////////////////////////////
/// @file		SPSpriteManager3D.h the header file of SPSpriteManager3D class.
/// @author		Ken.J & BlackSky
/// @version	Alpha 0.7
/// @date		2012-7-19
//////////////////////////////////////////////////////////////////////////

#pragma once

namespace SPEngine
{
	// FVF to describe out custom vertex structure.
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	#define D3DFVF_COLOR (D3DFVF_XYZ | D3DFVF_DIFFUSE) 
	#define D3DFVF_NORMAL_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL) 
	#define D3DFVF_NORMAL_TEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 
	#define D3DFVF_NORMAL_TEX_COLOR (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1 ) 

	//////////////////////////////////////////////////////////////////////
	/// @brief To define several types of vertex.
	///
	//////////////////////////////////////////////////////////////////////
	namespace SPVertex
	{
		//////////////////////////////////////////////////////////////////
		/// @brief NormalVertex contain the normal vector of the vertex.
		///
		//////////////////////////////////////////////////////////////////
		struct NormalVertex 
		{ 
			NormalVertex(){}
			NormalVertex(float setX, float setY, float setZ,
				float setNX, float setNY, float setNZ)
			{
				x = setX;
				y = setY;
				z = setZ;
				nx = setNX;
				ny = setNY;
				nz = setNZ;
			}
			float x, y, z;		// Position
			float nx, ny, nz;	// Normal vector
			static const DWORD FVF = D3DFVF_NORMAL_VERTEX;
		}; 

		//////////////////////////////////////////////////////////////////
		/// @brief ColorVertex contain the color of the vertex.
		///
		//////////////////////////////////////////////////////////////////
		struct ColorVertex 
		{ 
			ColorVertex(){}
			ColorVertex(float setX, float setY, float setZ, DWORD setColor)
			{
				x = setX;
				y = setY;
				z = setZ;
				color = setColor;
			}
			float x, y, z;		// Position
			DWORD color;		// Color
			static const DWORD FVF = D3DFVF_COLOR;
		}; 

		//////////////////////////////////////////////////////////////////
		/// @brief NormalTexVertex contain the normal vector of the vertex.
		/// and the texture coordinate.
		///
		//////////////////////////////////////////////////////////////////
		struct NormalTexVertex 
		{ 
			NormalTexVertex(){}
			NormalTexVertex(float setX, float setY, float setZ, 
				float setNX, float setNY, float setNZ,
				float setU, float setV)
			{
				x = setX;
				y = setY;
				z = setZ;
				nx = setNX;
				ny = setNY;
				nz = setNZ;
				u = setU;
				v = setV;
			}
			float x, y, z;		// Position
			float nx, ny, nz;	// Normal vector
			float u, v;			// Texture position
			static const DWORD FVF = D3DFVF_NORMAL_TEX;
		}; 

		//////////////////////////////////////////////////////////////////
		/// @brief NormalTexColorVertex contain the normal vector of the vertex.
		/// and the texture coordinate and the color.
		///
		//////////////////////////////////////////////////////////////////
		struct NormalTexColorVertex
		{
			NormalTexColorVertex(){}
			NormalTexColorVertex(float setX, float setY, float setZ,
				float setNX,float setNY, float setNZ,
				float setU, float setV, DWORD setColor)
			{
				x = setX;
				y = setY;
				z = setZ;
				nx = setNX;
				ny = setNY;
				nz = setNZ;
				u = setU;
				v = setV;
				color = setColor;
			}

			float x, y, z;		// Position
			float nx, ny, nz;	// Normal vector
			DWORD color;		// Color
			float u, v;			// Texture position
			static const DWORD FVF = D3DFVF_NORMAL_TEX_COLOR;
		};

		//////////////////////////////////////////////////////////////////
		/// @brief Vertex the most simple vertex contain only the position
		/// of the vertex.
		///
		//////////////////////////////////////////////////////////////////
		struct Vertex 
		{ 
			Vertex(){} 
			Vertex(float setX, float setY, float setZ) 
			{ 
				x = setX; y = setY; z = setZ; 
			} 
			float x, y, z; 
			static const DWORD FVF = D3DFVF_XYZ; 
		};
	}
}

