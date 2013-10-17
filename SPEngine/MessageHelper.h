#pragma once

namespace SPEngine
{
	class MessageHelper
	{
	private:
		MessageHelper(void);
		~MessageHelper(void);
	public:
		static void Msg(TCHAR *szFormat, ...);
		static void Msg(std::string msg, ...);
	};
}


