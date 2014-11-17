#include "Time.h"

#include <ctime>

#ifdef OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


BEGIN_NAMESPACE_CORE
{

	TimeMs CTime::system()
	{
#ifdef OS_WINDOWS
		return ::GetTickCount();
#elif defined OS_LINUX
		return 0;
#else
		return 0;
#endif
	}

	s64 CTime::seconds()
	{
		return std::time(0);
	}

};