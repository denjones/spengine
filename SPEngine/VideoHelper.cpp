#include "StdAfx.h"
#include "VideoHelper.h"

namespace SPEngine
{
	VideoHelper::VideoHelper(void)
	{
	}


	VideoHelper::~VideoHelper(void)
	{
	}

	void VideoHelper::Convert_UYV2_ARGB(
		unsigned char* source, 
		int width, 
		int height,
		int source_scan_size,
		unsigned char* dest,
		int dest_scan_size)
	{
		width /= 2;
		/*char str_name[2048];
		sprintf_s(str_name, 2048, "d:/dump_%d.raw", count);
		FILE* raw_damp = fopen(str_name, "wb");
		fwrite(source, width*height*4, 1, raw_damp);
		fclose(raw_damp);
		count ++;*/

		for (int y = 0; y < height; y++)
		{
			unsigned char* source_scan = source;
			unsigned char* dest_scan = dest;

			for (int x = 0; x < width; x ++)
			{
				int d = int(source_scan[3]) - 128;
				int e = int(source_scan[1]) - 128;
				int c = (int(source_scan[0]) - 16)*298;
				int f = 409*e + 128;
				int g = -100*d - 208*e + 128;
				int t = 516*d + 128;

				int v = (c + f) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;        
				dest_scan[0] = v;
				v = (c + g) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;
				dest_scan[1] = v;
				v = (c + t) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;
				dest_scan[2] = v;
				dest_scan[3] = 255;

				dest_scan += 4;
				c = (int(source_scan[2]) - 16)*298;
				v = (c + f) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;        
				dest_scan[0] = v;
				v = (c + g) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;
				dest_scan[1] = v;
				v = (c + t) >> 8; if (v < 0) v = 0; if (v > 255) v = 255;
				dest_scan[2] = v;
				dest_scan[3] = 255;

				dest_scan += 4;
				source_scan += 4;
			}
			dest += dest_scan_size;
			source += source_scan_size;
		}
	}
}

