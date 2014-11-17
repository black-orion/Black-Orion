#include "Console.h"
#include "CriticalSection.h"


#ifdef OS_WINDOWS
#include <windows.h>
#include <conio.h> //_getch()
#else
#include <iostream> //cin.get()
using std::cin;
#endif


BEGIN_NAMESPACE_CORE
{
	CCriticalSection g_cs;
	bool g_closing = false;

#ifdef OS_WINDOWS
	BOOL WINAPI consolehandler(DWORD _event)
	{
		switch(_event)
		{
		case CTRL_C_EVENT:
			break;

		case CTRL_BREAK_EVENT:
			break;

		case CTRL_CLOSE_EVENT:
			{
				CTempLock t_lock(g_cs);
				g_closing = true;
				break;
			}

		case CTRL_LOGOFF_EVENT:
			break;

		case CTRL_SHUTDOWN_EVENT:
			break;
		}
		return TRUE;
	}
#endif

	//IO

	void CConsole::print(const char *_format, ...)
	{
	}

	void CConsole::output(const char *_str)
	{
	}

	void CConsole::read(const char *_format, ...)
	{
	}

	void CConsole::input(char *_dest, u32 _destSize)
	{
	}

	void CConsole::wait()
	{
#ifdef OS_WINDOWS
		_getch();
#else
		cin.get();
#endif
	}

	void CConsole::clear()
	{
#ifdef OS_WINDOWS
		COORD t_coordScreen = {0, 0};
		DWORD t_charsWritten = 0;
		CONSOLE_SCREEN_BUFFER_INFO t_csbi;
		DWORD t_conSize = 0;
		HANDLE t_console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(t_console, &t_csbi);
		t_conSize = t_csbi.dwSize.X * t_csbi.dwSize.Y;
		FillConsoleOutputCharacter(t_console, ' ', t_conSize, t_coordScreen, &t_charsWritten);
		GetConsoleScreenBufferInfo(t_console, &t_csbi);
		FillConsoleOutputAttribute(t_console, t_csbi.wAttributes, t_conSize, t_coordScreen,
			&t_charsWritten);
		SetConsoleCursorPosition(t_console, t_coordScreen);
#elif defined OS_LINUX
		//...
#endif
	}

	E_CONSOLE_COLOR CConsole::getTextColor()
	{
#ifdef OS_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO t_csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &t_csbi);
		return E_CONSOLE_COLOR(t_csbi.wAttributes & 0x0f);
#elif defined OS_LINUX
		return CC_BLACK;
#else
		return CC_BLACK;
#endif
	}

	E_CONSOLE_COLOR CConsole::getBackgroundColor()
	{
#ifdef OS_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO t_csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &t_csbi);
		return E_CONSOLE_COLOR((t_csbi.wAttributes >> 4) & 0x0f);
#elif defined OS_LINUX
		return CC_BLACK;
#else
		return CC_BLACK;
#endif
	}

	void CConsole::setTextColor(E_CONSOLE_COLOR _color)
	{
#ifdef OS_WINDOWS
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _color | (getBackgroundColor() << 4));
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::setBackgroundColor(E_CONSOLE_COLOR _color)
	{
#ifdef OS_WINDOWS
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), getTextColor() | (_color << 4));
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::setTitle(const char *_str)
	{
#ifdef OS_WINDOWS
		SetConsoleTitleA(_str);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::setTitle(const wchar_t *_str)
	{
#ifdef OS_WINDOWS
		SetConsoleTitleW(_str);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::getTitle(char *_dest, u32 _destSize)
	{
#ifdef OS_WINDOWS
		GetConsoleTitleA(_dest, _destSize);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::getTitle(wchar_t *_dest, u32 _destSize)
	{
#ifdef OS_WINDOWS
		GetConsoleTitleW(_dest, _destSize);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::getOriginalTitle(char *_dest, u32 _destSize)
	{
#ifdef OS_WINDOWS
		//GetConsoleOriginalTitleA(_dest, _destSize);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::getOriginalTitle(wchar_t *_dest, u32 _destSize)
	{
#ifdef OS_WINDOWS
		//GetConsoleOriginalTitleW(_dest, _destSize);
#elif defined OS_LINUX
		//...
#endif
	}

	bool CConsole::initCloseHandler()
	{
#ifdef OS_WINDOWS
		return SetConsoleCtrlHandler((PHANDLER_ROUTINE)consolehandler, TRUE) != 0;
#elif defined OS_LINUX
		//...
		return false;
#else
		return false;
#endif
	}

	bool CConsole::isClosed()
	{
		CTempLock t_lock(g_cs);

		return g_closing;
	}

	//Window

	void CConsole::hide()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::show()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		ShowWindow(GetConsoleWindow(), SW_SHOWNORMAL);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::showCursor(bool _show)
	{
#ifdef OS_WINDOWS
		CONSOLE_CURSOR_INFO t_cci;
		t_cci.dwSize = sizeof(t_cci);
		t_cci.bVisible = _show;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &t_cci);
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::flash()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		FlashWindow(GetConsoleWindow(), true);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::minimize()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		ShowWindow(GetConsoleWindow(), SW_SHOWMINIMIZED);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::restore()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		ShowWindow(GetConsoleWindow(), SW_RESTORE);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::maximize()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::resize(s32 _width, s32 _height)
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		CVec2D<s32> t_pos = getPosition();
		MoveWindow(GetConsoleWindow(), t_pos.X, t_pos.Y, _width, _height, true);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::resize(const CVec2D<s32> &_size)
	{
		resize(_size.X, _size.Y);
	}

	CVec2D<s32> CConsole::getSize()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		RECT t_rect = {0, 0, 0, 0};
		GetWindowRect(GetConsoleWindow(), &t_rect);
		return CVec2D<s32>(t_rect.right - t_rect.left, t_rect.bottom - t_rect.top);
#endif
#elif defined OS_LINUX
		//...
		return CVec2D<s32>();
#endif
		return CVec2D<s32>();
	}

	void CConsole::move(s32 _x, s32 _y)
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		CVec2D<s32> t_size = getSize();
		MoveWindow(GetConsoleWindow(), _x, _y, t_size.X, t_size.Y, true);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	void CConsole::move(const CVec2D<s32> &_pos)
	{
		move(_pos.X, _pos.Y);
	}

	CVec2D<s32> CConsole::getPosition()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		RECT t_rect = {0, 0, 0, 0};
		GetWindowRect(GetConsoleWindow(), &t_rect);
		return CVec2D<s32>(t_rect.left, t_rect.top);
#endif
#elif defined OS_LINUX
		return CVec2D<s32>();
#endif
		return CVec2D<s32>();
	}

	void CConsole::disableCloseButton()
	{
#ifdef OS_WINDOWS
#ifdef _MSC_VER
		RemoveMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
#endif
#elif defined OS_LINUX
		//...
#endif
	}

	bool CConsole::create()
	{
#ifdef OS_WINDOWS
		return AllocConsole() != 0;
#elif defined OS_LINUX
		return false;
#else
		return false;
#endif
	}

	bool CConsole::free()
	{
#ifdef OS_WINDOWS
		return FreeConsole() != 0;
#elif defined OS_LINUX
		return false;
#else
		return false;
#endif
	}

}
