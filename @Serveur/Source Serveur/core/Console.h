#ifndef CORE_CONSOLE_H
#define CORE_CONSOLE_H


#include "CoreBase.h"
#include "String.h"
#include "Vec2D.h"


BEGIN_NAMESPACE_CORE
{
	enum E_CONSOLE_COLOR
	{
		CC_BLACK = 0,
		CC_DARKBLUE,
		CC_DARKGREEN,
		CC_DARKCYAN,
		CC_DARKRED,
		CC_DARKMAGENTA,
		CC_DARKBROWN,
		CC_LIGHTGRAY,
		CC_DARKGRAY,
		CC_BLUE,
		CC_GREEN,
		CC_CYAN,
		CC_RED,
		CC_MAGENTA,
		CC_YELLOW,
		CC_WHITE
	};

	class CConsole
	{
	public:

		//IO

		static void print(const char *_format, ...);

		static void output(const char *_str);

		static void read(const char *_format, ...);

		static void input(char *_dest, u32 _destSize);

		static void wait();

		static void clear();

		static E_CONSOLE_COLOR getTextColor();

		static E_CONSOLE_COLOR getBackgroundColor();

		static void setTextColor(E_CONSOLE_COLOR _color);

		static void setBackgroundColor(E_CONSOLE_COLOR _color);

		static void setTitle(const char *_str);

		static void setTitle(const wchar_t *_str);

		static void getTitle(char *_dest, u32 _destSize);

		static void getTitle(wchar_t *_dest, u32 _destSize);

		static void getOriginalTitle(char *_dest, u32 _destSize);

		static void getOriginalTitle(wchar_t *_dest, u32 _destSize);

		static bool initCloseHandler();

		static bool isClosed();

		//Window

		static void hide();

		static void show();

		static void showCursor(bool _show = true);

		static void flash();

		static void minimize();

		static void restore();

		static void maximize();

		static void resize(s32 _width, s32 _height);

		static void resize(const CVec2D<s32> &_size);

		static CVec2D<s32> getSize();

		static void move(s32 _x, s32 _y);

		static void move(const CVec2D<s32> &_pos);

		static CVec2D<s32> getPosition();

		static void disableCloseButton();

		static bool create();

		static bool free();

	};

};


#endif //CORE_CONSOLE_H
