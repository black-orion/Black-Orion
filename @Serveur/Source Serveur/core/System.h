#ifndef CORE_SYSTEM_H
#define CORE_SYSTEM_H


#include "CoreBase.h"
#include "Time.h"
#include "Pair.h"
#include "String.h"


BEGIN_NAMESPACE_CORE
{

	class CSystem
	{
	public:

		static void sleep(TimeMs _milliSeconds);

		static CPair<u32, u32> getMemoryUsage();

		static u32 getCpuSpeed();

		static stringc getCpuName();

		static bool execute(const char *_name, const char *_args);

		static bool getClipboard(char *_dest, u32 _destSize);

		static bool setClipboard(const char *_str);

		static stringc getUserName();

		static u32 getTime();

		static void exit(s32 _code);

		static s32 messageBox(const char *_caption, const char *_message);

	};

};


#endif //CORE_SYSTEM_H
