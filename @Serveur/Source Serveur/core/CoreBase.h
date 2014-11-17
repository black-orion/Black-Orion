#ifndef CORE_BASE_H
#define CORE_BASE_H


#include <typeinfo>


//// OS ////

#ifdef _WIN32
#define OS_WINDOWS
#else
#define OS_LINUX
#endif


//// Irrlicht ////

//#define SETTING_IRRLICHT


//// Debugging ////

#ifndef NDEBUG
#define SDEBUG
#endif


#ifdef SETTING_IRRLICHT

#include <irrlicht.h>

using namespace irr;

#endif //SETTING_IRRLICHT


//// Types ////

#define NAMESPACE_CORE sdk
#define BEGIN_NAMESPACE_CORE namespace NAMESPACE_CORE


BEGIN_NAMESPACE_CORE
{

#ifndef SETTING_IRRLICHT

	typedef signed int s32;

	typedef unsigned int u32;

	typedef signed short s16;

	typedef unsigned short u16;

	typedef signed char s8;

	typedef unsigned char u8;

	typedef char c8;

	typedef wchar_t c16;

	typedef float f32;

	typedef double f64;

#endif //ndef SETTING_IRRLICHT

#ifdef _MSC_VER

	typedef signed __int64 s64;

	typedef unsigned __int64 u64;

#else

	typedef signed long long s64;

	typedef unsigned long long u64;

#endif

	typedef char Byte;

	typedef u32 PORT;

	typedef u32 TimeMs;

	static const int TYPE_CHECK_32_BIT[
		sizeof(s8) == 1 &&
		sizeof(s16) == 2 &&
		sizeof(s32) == 4 &&
		sizeof(s64) == 8 &&
		sizeof(f32) == 4 &&
		sizeof(f64) == 8] = {1};


#define LOOP(type, index, count) for (type index = 0; index < (count); ++index)

#define FOR_EACH(container, counter) for (u32 counter = 0; counter < (container).size(); ++counter)

#define ARRAY_SIZE(arr) (sizeof(arr)/(sizeof((arr)[0])))

};


#endif //CORE_BASE_H

