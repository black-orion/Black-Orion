#include "System.h"

#ifdef OS_WINDOWS
//#define WIN32_LEAN_AND_MEAN //ShellExecuteA timeGetTime
#include <windows.h>
#elif defined OS_LINUX
#include <unistd.h>
#endif


BEGIN_NAMESPACE_CORE
{

	void CSystem::sleep(TimeMs _milliSeconds)
	{
#ifdef OS_WINDOWS
		Sleep(_milliSeconds);
#elif defined OS_LINUX
		usleep(_milliSeconds * 1000);
#endif
	}

	CPair<u32, u32> CSystem::getMemoryUsage()
	{
#ifdef OS_WINDOWS
		MEMORYSTATUS MemoryStatus;
		MemoryStatus.dwLength = sizeof(MEMORYSTATUS);

		GlobalMemoryStatus(&MemoryStatus);

		return CPair<u32, u32>(MemoryStatus.dwAvailPhys >> 10, MemoryStatus.dwTotalPhys >> 10);
#elif defined OS_LINUX
		return CPair<u32, u32>(1, 1);
#endif
	}

	u32 CSystem::getCpuSpeed()
	{
#ifdef OS_WINDOWS
		HKEY t_key;
		LONG t_err = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &t_key);

		if (t_err != ERROR_SUCCESS)
			return 0;

		DWORD t_speed = 0;
		DWORD t_size = sizeof(t_speed);
		t_err = RegQueryValueExA(t_key, "~MHz", 0, 0, (LPBYTE)&t_speed, &t_size);

		RegCloseKey(t_key);

		if (t_err != ERROR_SUCCESS)
			return 0;

		return t_speed;
#elif defined OS_LINUX
		return 0;
#endif
	}

	stringc CSystem::getCpuName()
	{
#ifdef OS_WINDOWS
		HKEY t_key;
		LONG t_err = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &t_key);

		if (t_err != ERROR_SUCCESS)
			return "";

		char t_buffer[256];
		DWORD t_size = sizeof(t_buffer);
		t_err = RegQueryValueExA(t_key, "ProcessorNameString", 0, 0, (LPBYTE)&t_buffer, &t_size);

		RegCloseKey(t_key);

		if (t_err != ERROR_SUCCESS)
			return "";

		return t_buffer;
#elif defined OS_LINUX
		return "";
#endif
	}

	bool CSystem::execute(const char *_name, const char *_args)
	{
#ifdef OS_WINDOWS
		return ShellExecuteA(0, "open", _name, _args ? _args : "", "", 1) != 0;
#elif defined OS_LINUX
		return false;
#endif
	}

	bool CSystem::getClipboard(char *_dest, u32 _destSize)
	{
#ifdef OS_WINDOWS
		if (OpenClipboard(0))
		{
			HANDLE t_cbhandle = GetClipboardData(CF_TEXT);
			const char *t_text = (const char*)GlobalLock(t_cbhandle);
			GlobalUnlock(t_cbhandle);
			CloseClipboard();
			xstrcpy(_dest, _destSize, t_text);
			return true;
		}
#elif defined OS_LINUX
		//...
#endif
		return false;
	}

	bool CSystem::setClipboard(const char *_str)
	{
#ifdef OS_WINDOWS
		if (OpenClipboard(0))
		{
			EmptyClipboard();
			HANDLE t_buf = GlobalAlloc(GMEM_DDESHARE, strlen(_str) + 1);
			char *t_text = (char*)GlobalLock(t_buf);
			xstrcpy(t_text, 2147483647, _str);
			GlobalUnlock(t_buf);
			SetClipboardData(CF_TEXT, t_buf);
			CloseClipboard();
			return true;
		}
#elif defined OS_LINUX
		//...
#endif
		return false;
	}

	stringc CSystem::getUserName()
	{
#ifdef OS_WINDOWS
		static char t_buffer[256];
		DWORD t_buf_size = sizeof(t_buffer) / sizeof(char);
		if (GetUserNameA(t_buffer, &t_buf_size))
		{
			return t_buffer;
		}
#elif defined OS_LINUX
		//...
#endif
		return "";
	}

	u32 CSystem::getTime()
	{
#ifdef OS_WINDOWS
		return timeGetTime();
#elif defined OS_LINUX
		//...
#endif
	}

	void CSystem::exit(s32 _code)
	{
		::exit(_code);
	}

	s32 CSystem::messageBox(const char *_caption, const char *_message)
	{
#ifdef OS_WINDOWS
		return MessageBoxA(0, _message, _caption, MB_OK);
#elif defined OS_LINUX
		return 0;
#else
		return 0;
#endif
	}

};
