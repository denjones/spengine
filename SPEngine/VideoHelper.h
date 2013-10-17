#pragma once

namespace SPEngine
{
	class VideoHelper
	{
	private:
		VideoHelper(void);
		~VideoHelper(void);

	public:
		static void Convert_UYV2_ARGB(
			unsigned char* source,
			int width, int height,
			int source_scan_size,
			unsigned char* dest, 
			int dest_scan_size);
	};
}


