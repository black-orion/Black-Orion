#include "Debug.h"
#include "String.h"

#include <cstdarg>

#ifdef OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


BEGIN_NAMESPACE_CORE
{

	enum
	{
		BUF_SIZE = 4096
	};

	static char g_buffer[BUF_SIZE];

	static char g_buffer2[BUF_SIZE];

	bool debug_error_(const char *_fileName, u32 _line, const char *_format, ...)
	{
		va_list t_args;
		va_start(t_args, _format);
#ifdef _MSC_VER
		vsnprintf_s(g_buffer, BUF_SIZE, BUF_SIZE - 1, _format, t_args);
#else
		vsnprintf(g_buffer, BUF_SIZE - 1, _format, t_args);
#endif
		va_end(t_args);

#ifdef _MSC_VER
		sprintf_s(g_buffer2, sizeof(g_buffer2), "File: \"%s\"\nLine: %u\n%s\n\nExit?", _fileName, _line, g_buffer);
#else
		sprintf(g_buffer2, "File: \"%s\"\nLine: %u\n%s\n\nExit?", _fileName, _line, g_buffer);
#endif

		if (
#ifdef OS_WINDOWS
			MessageBoxA(0, g_buffer2, "Debug error", MB_YESNO) == IDYES
#elif defined OS_LINUX
			false
#else
			false
#endif
			)
		{
			exit(1);
		}

		return false;
	}
};
