#pragma once

namespace SPEngine
{
	// FVF to describe out custom vertex structure.
	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
	#define D3DFVF_COLOR (D3DFVF_XYZ | D3DFVF_DIFFUSE) 
	#define D3DFVF_NORMAL_VERTEX (D3DFVF_XYZ | D3DFVF_NORMAL) 
	#define D3DFVF_NORMAL_TEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1) 
	#define D3DFVF_NORMAL_TEX_COLOR (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE| D3DFVF_TEX1 ) 

	namespace Vertex
	{
		// Custom vertex type.
		struct CustomVertex
		{
			float x, y, z;		// Position
			float rhw;
			DWORD color;		// Color
		};

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
			static const DWORD FVF;
		}; 

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
			static const DWORD FVF;
		}; 

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
			static const DWORD FVF;
		}; 

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
			static const DWORD FVF;
		};

		struct Vertex 
		{ 
			Vertex(){} 
			Vertex(float setX, float setY, float setZ) 
			{ 
				x = setX; y = setY; z = setZ; 
			} 
			float x, y, z; 
			static const DWORD FVF; 
		};
	}
}

