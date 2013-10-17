//////////////////////////////////////////////////////////////////////////
/// @file		SPColorHelper.cpp the implement file of SPColorHelper class.
/// @author		Ken.J
/// @version	Alpha 0.7
/// @date		2012-7-18
//////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "SPColorHelper.h"

namespace SPEngine
{
	const D3DXCOLOR SPColor::AliceBlue = 0xFFF0F8FF;
	const D3DXCOLOR SPColor::AntiqueWhite = 0xFFFAEBD7;
	const D3DXCOLOR SPColor::Aqua = 0xFF00FFFF;
	const D3DXCOLOR SPColor::Aquamarine = 0xFF7FFFD4;
	const D3DXCOLOR SPColor::Azure = 0xFFF0FFFF;
	const D3DXCOLOR SPColor::Beige = 0xFFF5F5DC;
	const D3DXCOLOR SPColor::Bisque = 0xFFFFE4C4;
	const D3DXCOLOR SPColor::Black = 0xFF000000;
	const D3DXCOLOR SPColor::BlanchedAlmond = 0xFFFFEBCD;
	const D3DXCOLOR SPColor::Blue = 0xFF0000FF;
	const D3DXCOLOR SPColor::BlueViolet = 0xFF8A2BE2;
	const D3DXCOLOR SPColor::Brown = 0xFFA52A2A;
	const D3DXCOLOR SPColor::BurlyWood = 0xFFDEB887;
	const D3DXCOLOR SPColor::CadetBlue = 0xFF5F9EA0;
	const D3DXCOLOR SPColor::Chartreuse = 0xFF7FFF00;
	const D3DXCOLOR SPColor::Chocolate = 0xFFD2691E;
	const D3DXCOLOR SPColor::Coral = 0xFFFF7F50;
	const D3DXCOLOR SPColor::CornflowerBlue = 0xFF6495ED;
	const D3DXCOLOR SPColor::Cornsilk = 0xFFFFF8DC;
	const D3DXCOLOR SPColor::Crimson = 0xFFDC143C;
	const D3DXCOLOR SPColor::Cyan = 0xFF00FFFF;
	const D3DXCOLOR SPColor::DarkBlue = 0xFF00008B;
	const D3DXCOLOR SPColor::DarkCyan = 0xFF008B8B;
	const D3DXCOLOR SPColor::DarkGoldenrod = 0xFFB8860B;
	const D3DXCOLOR SPColor::DarkGray = 0xFFA9A9A9;
	const D3DXCOLOR SPColor::DarkGreen = 0xFF006400;
	const D3DXCOLOR SPColor::DarkKhaki = 0xFFBDB76B;
	const D3DXCOLOR SPColor::DarkMagenta = 0xFF8B008B;
	const D3DXCOLOR SPColor::DarkOliveGreen = 0xFF556B2F;
	const D3DXCOLOR SPColor::DarkOrange = 0xFFFF8C00;
	const D3DXCOLOR SPColor::DarkOrchid = 0xFF9932CC;
	const D3DXCOLOR SPColor::DarkRed = 0xFF8B0000;
	const D3DXCOLOR SPColor::DarkSalmon = 0xFFE9967A;
	const D3DXCOLOR SPColor::DarkSeaGreen = 0xFF8FBC8B;
	const D3DXCOLOR SPColor::DarkSlateBlue = 0xFF483D8B;
	const D3DXCOLOR SPColor::DarkSlateGray = 0xFF2F4F4F;
	const D3DXCOLOR SPColor::DarkTurquoise = 0xFF00CED1;
	const D3DXCOLOR SPColor::DarkViolet = 0xFF9400D3;
	const D3DXCOLOR SPColor::DeepPink = 0xFFFF1493;
	const D3DXCOLOR SPColor::DeepSkyBlue = 0xFF00BFFF;
	const D3DXCOLOR SPColor::DimGray = 0xFF696969;
	const D3DXCOLOR SPColor::DodgerBlue = 0xFF1E90FF;
	const D3DXCOLOR SPColor::Firebrick = 0xFFB22222;
	const D3DXCOLOR SPColor::FloralWhite = 0xFFFFFAF0;
	const D3DXCOLOR SPColor::ForestGreen = 0xFF228B22;
	const D3DXCOLOR SPColor::Fuchsia = 0xFFFF00FF;
	const D3DXCOLOR SPColor::Gainsboro = 0xFFDCDCDC;
	const D3DXCOLOR SPColor::GhostWhite = 0xFFF8F8FF;
	const D3DXCOLOR SPColor::Gold = 0xFFFFD700;
	const D3DXCOLOR SPColor::Goldenrod = 0xFFDAA520;
	const D3DXCOLOR SPColor::Gray = 0xFF808080;
	const D3DXCOLOR SPColor::Green = 0xFF008000;
	const D3DXCOLOR SPColor::GreenYellow = 0xFFADFF2F;
	const D3DXCOLOR SPColor::Honeydew = 0xFFF0FFF0;
	const D3DXCOLOR SPColor::HotPink = 0xFFFF69B4;
	const D3DXCOLOR SPColor::IndianRed = 0xFFCD5C5C;
	const D3DXCOLOR SPColor::Indigo = 0xFF4B0082;
	const D3DXCOLOR SPColor::Ivory = 0xFFFFFFF0;
	const D3DXCOLOR SPColor::Khaki = 0xFFF0E68C;
	const D3DXCOLOR SPColor::Lavender = 0xFFE6E6FA;
	const D3DXCOLOR SPColor::LavenderBlush = 0xFFFFF0F5;
	const D3DXCOLOR SPColor::LawnGreen = 0xFF7CFC00;
	const D3DXCOLOR SPColor::LemonChiffon = 0xFFFFFACD;
	const D3DXCOLOR SPColor::LightBlue = 0xFFADD8E6;
	const D3DXCOLOR SPColor::LightCoral = 0xFFF08080;
	const D3DXCOLOR SPColor::LightCyan = 0xFFE0FFFF;
	const D3DXCOLOR SPColor::LightGoldenrodYellow = 0xFFFAFAD2;
	const D3DXCOLOR SPColor::LightGray = 0xFFD3D3D3;
	const D3DXCOLOR SPColor::LightGreen = 0xFF90EE90;
	const D3DXCOLOR SPColor::LightPink = 0xFFFFB6C1;
	const D3DXCOLOR SPColor::LightSalmon = 0xFFFFA07A;
	const D3DXCOLOR SPColor::LightSeaGreen = 0xFF20B2AA;
	const D3DXCOLOR SPColor::LightSkyBlue = 0xFF87CEFA;
	const D3DXCOLOR SPColor::LightSlateGray = 0xFF778899;
	const D3DXCOLOR SPColor::LightSteelBlue = 0xFFB0C4DE;
	const D3DXCOLOR SPColor::LightYellow = 0xFFFFFFE0;
	const D3DXCOLOR SPColor::Lime = 0xFF00FF00;
	const D3DXCOLOR SPColor::LimeGreen = 0xFF32CD32;
	const D3DXCOLOR SPColor::Linen = 0xFFFAF0E6;
	const D3DXCOLOR SPColor::Magenta = 0xFFFF00FF;
	const D3DXCOLOR SPColor::Maroon = 0xFF800000;
	const D3DXCOLOR SPColor::MediumAquamarine = 0xFF66CDAA;
	const D3DXCOLOR SPColor::MediumBlue = 0xFF0000CD;
	const D3DXCOLOR SPColor::MediumOrchid = 0xFFBA55D3;
	const D3DXCOLOR SPColor::MediumPurple = 0xFF9370DB;
	const D3DXCOLOR SPColor::MediumSeaGreen = 0xFF3CB371;
	const D3DXCOLOR SPColor::MediumSlateBlue = 0xFF7B68EE;
	const D3DXCOLOR SPColor::MediumSpringGreen = 0xFF00FA9A;
	const D3DXCOLOR SPColor::MediumTurquoise = 0xFF48D1CC;
	const D3DXCOLOR SPColor::MediumVioletRed = 0xFFC71585;
	const D3DXCOLOR SPColor::MidnightBlue = 0xFF191970;
	const D3DXCOLOR SPColor::MintCream = 0xFFF5FFFA;
	const D3DXCOLOR SPColor::MistyRose = 0xFFFFE4E1;
	const D3DXCOLOR SPColor::Moccasin = 0xFFFFE4B5;
	const D3DXCOLOR SPColor::NavajoWhite = 0xFFFFDEAD;
	const D3DXCOLOR SPColor::Navy = 0xFF000080;
	const D3DXCOLOR SPColor::OldLace = 0xFFFDF5E6;
	const D3DXCOLOR SPColor::Olive = 0xFF808000;
	const D3DXCOLOR SPColor::OliveDrab = 0xFF6B8E23;
	const D3DXCOLOR SPColor::Orange = 0xFFFFA500;
	const D3DXCOLOR SPColor::OrangeRed = 0xFFFF4500;
	const D3DXCOLOR SPColor::Orchid = 0xFFDA70D6;
	const D3DXCOLOR SPColor::PaleGoldenrod = 0xFFEEE8AA;
	const D3DXCOLOR SPColor::PaleGreen = 0xFF98FB98;
	const D3DXCOLOR SPColor::PaleTurquoise = 0xFFAFEEEE;
	const D3DXCOLOR SPColor::PaleVioletRed = 0xFFDB7093;
	const D3DXCOLOR SPColor::PapayaWhip = 0xFFFFEFD5;
	const D3DXCOLOR SPColor::PeachPuff = 0xFFFFDAB9;
	const D3DXCOLOR SPColor::Peru = 0xFFCD853F;
	const D3DXCOLOR SPColor::Pink = 0xFFFFC0CB;
	const D3DXCOLOR SPColor::Plum = 0xFFDDA0DD;
	const D3DXCOLOR SPColor::PowderBlue = 0xFFB0E0E6;
	const D3DXCOLOR SPColor::Purple = 0xFF800080;
	const D3DXCOLOR SPColor::Red = 0xFFFF0000;
	const D3DXCOLOR SPColor::RosyBrown = 0xFFBC8F8F;
	const D3DXCOLOR SPColor::RoyalBlue = 0xFF4169E1;
	const D3DXCOLOR SPColor::SaddleBrown = 0xFF8B4513;
	const D3DXCOLOR SPColor::Salmon = 0xFFFA8072;
	const D3DXCOLOR SPColor::SandyBrown = 0xFFF4A460;
	const D3DXCOLOR SPColor::SeaGreen = 0xFF2E8B57;
	const D3DXCOLOR SPColor::SeaShell = 0xFFFFF5EE;
	const D3DXCOLOR SPColor::Sienna = 0xFFA0522D;
	const D3DXCOLOR SPColor::Silver = 0xFFC0C0C0;
	const D3DXCOLOR SPColor::SkyBlue = 0xFF87CEEB;
	const D3DXCOLOR SPColor::SlateBlue = 0xFF6A5ACD;
	const D3DXCOLOR SPColor::SlateGray = 0xFF708090;
	const D3DXCOLOR SPColor::Snow = 0xFFFFFAFA;
	const D3DXCOLOR SPColor::SpringGreen = 0xFF00FF7F;
	const D3DXCOLOR SPColor::SteelBlue = 0xFF4682B4;
	const D3DXCOLOR SPColor::Tan = 0xFFD2B48C;
	const D3DXCOLOR SPColor::Teal = 0xFF008080;
	const D3DXCOLOR SPColor::Thistle = 0xFFD8BFD8;
	const D3DXCOLOR SPColor::Tomato = 0xFFFF6347;
	const D3DXCOLOR SPColor::Transparent = 0x00FFFFFF;
	const D3DXCOLOR SPColor::Turquoise = 0xFF40E0D0;
	const D3DXCOLOR SPColor::Violet = 0xFFEE82EE;
	const D3DXCOLOR SPColor::Wheat = 0xFFF5DEB3;
	const D3DXCOLOR SPColor::White = 0xFFFFFFFF;
	const D3DXCOLOR SPColor::WhiteSmoke = 0xFFF5F5F5;
	const D3DXCOLOR SPColor::Yellow = 0xFFFFFF00;
	const D3DXCOLOR SPColor::YellowGreen = 0xFF9ACD32;

	//const D3DXCOLOR SPColor::ColorHelper::White = D3DCOLOR_XRGB(255, 255, 255); 
	//const D3DXCOLOR SPColor::ColorHelper::Black = D3DCOLOR_XRGB( 0, 0, 0);
	//const D3DXCOLOR SPColor::ColorHelper::Red = D3DCOLOR_XRGB(255, 0, 0); 
	//const D3DXCOLOR SPColor::ColorHelper::Green = D3DCOLOR_XRGB( 0, 255, 0); 
	//const D3DXCOLOR SPColor::ColorHelper::Blue = D3DCOLOR_XRGB( 0, 0, 255); 
	//const D3DXCOLOR SPColor::ColorHelper::Yellow = D3DCOLOR_XRGB(255, 255, 0); 
	//const D3DXCOLOR SPColor::ColorHelper::Cyan = D3DCOLOR_XRGB( 0, 255, 255); 
	//const D3DXCOLOR SPColor::ColorHelper::Magenta = D3DCOLOR_XRGB(255, 0, 255); 

	D3DXCOLOR SPColorHelper::AlphaColor( float alpha, D3DXCOLOR color )
	{
		//return alpha * color;
		return D3DXCOLOR(color.r, color.g, color.b, alpha);
	}

	D3DXVECTOR4 SPColorHelper::RGBToHSV( D3DXCOLOR color)
	{
		float H,S,V;
		float maxRGB = max(color.r, max(color.g, color.b));
		float minRGB = min(color.r, min(color.g, color.b));
				
		if (maxRGB - minRGB == 0)
		{
			H = 0;
		}
		else if (color.r == maxRGB)
		{
			H = (color.g - color.b) / (maxRGB - minRGB);
		}
		else if (color.g == maxRGB)
		{
			H = 2 + (color.b - color.r) / (maxRGB - minRGB);
		}
		else
		{
			H = 4 + (color.r - color.g) / (maxRGB - minRGB);
		}

		H = H / 6;

		//if (H < 0)
		//{
		//	H += 1;
		//}

		S = (maxRGB - minRGB) / maxRGB;

		V = maxRGB;

		return D3DXVECTOR4(H, S, V, color.a);
	}

	D3DXCOLOR SPColorHelper::HSVToRGB( D3DXVECTOR4 AHSV )
	{
		float A,H,S,V;
		float R = 1;
		float G = 1;
		float B = 1;
		
		H = AHSV.x;
		S = AHSV.y;
		V = AHSV.z;
		A = AHSV.w;

		if (S == 0)
		{
			R = G = B = V;
		}
		else
		{
			if (H < 0)
			{
				H = H + 1;
			}

			H = 6 * H;


			int i = (int)H;
			float f = H - i;
			float a, b, c;

			a = V * (1 - S);
			b = V * (1 - S * f);
			c = V * (1 - S * (1 - f));

			switch(i)
			{
			case 0:
				R = V;
				G = c;
				B = a;
				break;
			case 1:
				R = b;
				G = V;
				B = a;
				break;
			case 2:
				R = a;
				G = V;
				B = c;
				break;
			case 3:
				R = a;
				G = b;
				B = V;
				break;
			case 4:
				R = c;
				G = a;
				B = V;
				break;
			case 5:
				R = V;
				G = a;
				B = b;
				break;
			}
		}

		return D3DXCOLOR(R, G, B, A);
	}

	void SPColorHelper::RGBtoHSV( float r, float g, float b, float *h, float *s, float *v )
	{
		float Min, Max, delta;

		Min = min(r, min(g, b));
		Max = max(r, max(g, b));
		*v = Max;				// v

		delta = Max - Min;

		if( Max != 0 )
			*s = delta / Max;		// s
		else {
			// r = g = b = 0		// s = 0, v is undefined
			*s = 0;
			*h = -1;
			return;
		}

		if( r == Max )
		{
			*h = ( g - b ) / delta;		// between yellow & magenta
		}
		else if( g == Max )
		{
			*h = 2 + ( b - r ) / delta;	// between cyan & yellow
		}
		else
		{
			*h = 4 + ( r - g ) / delta;	// between magenta & cyan
		}

		*h *= 60;				// degrees
		if( *h < 0 )
		{
			*h += 360;
		}

	}

	void SPColorHelper::HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
	{
		int i;
		float f, p, q, t;

		if( s == 0 ) 
		{
			*r = *g = *b = v;
			return;
		}

		h /= 60;			// sector 0 to 5
		i = (int)floor( h );
		f = h - i;			// factorial part of h
		p = v * ( 1 - s );
		q = v * ( 1 - s * f );
		t = v * ( 1 - s * ( 1 - f ) );

		switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
		}

	}
}