#ifndef CORE_UTIL_H
#define CORE_UTIL_H


#include "CoreBase.h"
#include "Debug.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <wchar.h>


BEGIN_NAMESPACE_CORE
{

    //logic

	template <class T>
	T Min(T _first, T _second)
	{
		return (_first < _second ? _first : _second);
	}

	template <class T>
	T Max(T _first, T _second)
	{
		return (_first > _second ? _first : _second);
	}

	template <class T>
	T Limit(T _number, T _min, T _max)
	{
		FDASSERT(_min <= _max);

		return (_number < _min ? _min : (_number > _max ? _max : _number));
	}


	//arrays

	template <class T>
	void copy_raw(T *_dest, const T *_src, u32 _count)
	{
		memcpy(_dest, _src, _count * sizeof(T));
	}

	template <class T>
	void copy(T *_dest, const T *_src, u32 _count)
	{
		for (u32 i = 0; i < _count; ++i)
		{
			_dest[i] = _src[i];
		}
	}

	template <>
	inline void copy(s8 *_dest, const s8 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(u8 *_dest, const u8 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(s16 *_dest, const s16 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(u16 *_dest, const u16 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(s32 *_dest, const s32 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(u32 *_dest, const u32 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(s64 *_dest, const s64 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(u64 *_dest, const u64 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(f32 *_dest, const f32 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(f64 *_dest, const f64 *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <>
	inline void copy(wchar_t *_dest, const wchar_t *_src, u32 _count)
	{
		copy_raw(_dest, _src, _count);
	}

	template <class T>
	void move_raw(T *_dest, const T *_src, u32 _count)
	{
		memmove(_dest, _src, _count * sizeof(T));
	}

	template <class T>
	void move(T *_dest, const T *_src, u32 _count)
	{
		move_raw(_dest, _src, _count);
	}

	template <class T>
	s32 compare(const T *_str1, const T *_str2, u32 _count)
	{
		return memcmp(_str1, _str2, _count * sizeof(T));
	}

	template <class T>
	void assign(T *_dest, u32 _size, const T &_value)
	{
		for (u32 i = 0; i < _size; ++i)
		{
			_dest[i] = _value;
		}
	}

	template <class T>
	void foreach(T *_arr, u32 _size, void (*_func)(T&))
	{
		for (u32 i = 0; i < _size; ++i)
		{
			_func(_arr[i]);
		}
	}

	template <class T>
	void foreach(const T *_arr, u32 _size, void (*_func)(const T&))
	{
		for (u32 i = 0; i < _size; ++i)
		{
			_func(_arr[i]);
		}
	}

	template <class T>
	void foreach(const T *_arr, u32 _size, void (*_func)(T))
	{
		for (u32 i = 0; i < _size; ++i)
		{
			_func(_arr[i]);
		}
	}


	//strings

	inline u32 xstrlen(const char *_str)
	{
		return ::strlen(_str);
	}

	inline u32 xstrlen(const wchar_t *_str)
	{
	    return ::wcslen(_str);
	}

	inline char *xstrncpy(char *_dest, u32 _destSize, const char *_src, u32 _count)
	{
#ifdef _MSC_VER
		::strncpy_s(_dest, _destSize, _src, _count - 1);
		return _dest;
#else
		return ::strncpy(_dest, _src, Min(_count - 1, _destSize));
#endif
	}

	inline wchar_t *xstrncpy(wchar_t *_dest, u32 _destSize, wchar_t *_src, u32 _count)
	{
#ifdef _MSC_VER
		::wcsncpy_s(_dest, _destSize, _src, _count - 1);
		return _dest;
#else
		return ::wcsncpy(_dest, _src, _count - 1);
#endif
	}

	inline char *xstrcpy(char *_dest, u32 _destSize, const char *_src)
	{
		return xstrncpy(_dest, _destSize, _src, _destSize - 1);
	}

	inline wchar_t *xstrcpy(wchar_t *_dest, u32 _destSize, wchar_t *_src)
	{
		return xstrncpy(_dest, _destSize, _src, _destSize - 1);
	}

	inline s32 xstrcmp(const char *_str1, const char *_str2)
	{
		return ::strcmp(_str1, _str2);
	}

	inline s32 xstrcmp(const wchar_t *_str1, const wchar_t *_str2)
	{
		return ::wcscmp(_str1, _str2);
	}

	inline s32 xstrncmp(const char *_str1, const char *_str2, u32 _count)
	{
		return ::strncmp(_str1, _str2, _count);
	}

	inline s32 xstrncmp(const wchar_t *_str1, const wchar_t *_str2, u32 _count)
	{
		return ::wcsncmp(_str1, _str2, _count);
	}

	inline s32 xstricmp(const char *_str1, const char *_str2)
	{
#ifdef _MSC_VER
		return ::_stricmp(_str1, _str2);
#else
        return ::strcmp(_str1, _str2);
#endif
	}

	inline s32 xstricmp(const wchar_t *_str1, const wchar_t *_str2)
	{
#ifdef _MSC_VER
		return ::_wcsicmp(_str1, _str2);
#else
        return ::wcscmp(_str1, _str2);
#endif
	}

	inline char *xstrcat(char *_dest, u32 _destSize, const char *_src)
	{
#ifdef _MSC_VER
		::strcat_s(_dest, _destSize, _src);
		return _dest;
#else
        return ::strcat(_dest, _src);
#endif
	}

	inline wchar_t *xstrcat(wchar_t *_dest, u32 _destSize, wchar_t *_src)
	{
#ifdef _MSC_VER
		::wcscat_s(_dest, _destSize, _src);
		return _dest;
#else
        return ::wcscat(_dest, _src);
#endif
	}

	inline bool xisspace(char _chr)
	{
		return (
			_chr == ' ' ||
			_chr == '\t' ||
			_chr == '\n' ||
			_chr == '\r');
	}

	inline bool xisspace(wchar_t _chr)
	{
		return (
			_chr == L' ' ||
			_chr == L'\t' ||
			_chr == L'\n' ||
			_chr == L'\r');
	}

	inline s32 xtoi(const char *_str)
	{
		return ::atoi(_str);
	}

	inline s32 xtoi(const wchar_t *_str)
	{
#ifdef _MSC_VER
		return ::_wtoi(_str);
#else
        return 0;
#endif
	}

	inline u32 xtou(const char *_str)
	{
		return ::strtoul(_str, 0, 0);
	}

	inline u32 xtou(const wchar_t *_str)
	{
		return ::wcstoul(_str, 0, 0);
	}

	inline s64 xtoi64(const char *_str)
	{
#ifdef _MSC_VER
		return ::_atoi64(_str);
#else
        return 0;
#endif
	}

	inline s64 xtoi64(const wchar_t *_str)
	{
#ifdef _MSC_VER
		return ::_wtoi64(_str);
#else
        return 0;
#endif
	}

	inline u64 xtou64(const char *_str)
	{
#ifdef _MSC_VER
		return ::_atoi64(_str);
#else
        return 0;
#endif
	}

	inline u64 xtou64(const wchar_t *_str)
	{
#ifdef _MSC_VER
		return ::_wtoi64(_str);
#else
        return 0;
#endif
	}

	inline f32 xtof(const char *_str)
	{
		return static_cast<f32>(::atof(_str));
	}

	inline f32 xtof(const wchar_t *_str)
	{
#ifdef _MSC_VER
		return static_cast<f32>(::_wtof(_str));
#else
        return 0.0f;
#endif
	}

	inline f64 xtod(const char *_str)
	{
		return ::atof(_str);
	}

	inline f64 xtod(const wchar_t *_str)
	{
#ifdef _MSC_VER
		return ::_wtof(_str);
#else
        return 0.0;
#endif
	}

	inline char *itox(char *_dest, u32 _destSize, s32 _int)
	{
#ifdef _MSC_VER
		::_itoa_s(_int, _dest, _destSize, 10);
#else
        ::sprintf(_dest, "%d", _int);
#endif
		return _dest;
	}

	inline wchar_t *itox(wchar_t *_dest, u32 _destSize, s32 _int)
	{
#ifdef _MSC_VER
		::_itow_s(_int, _dest, _destSize, 10);
#else
        ::swprintf(_dest, L"%d", _int);
#endif
		return _dest;
	}

	inline char *utox(char *_dest, u32 _destSize, u32 _uint)
	{
#ifdef _MSC_VER
		::_itoa_s(_uint, _dest, _destSize, 10);
#else
        ::sprintf(_dest, "%u", _uint);
#endif
		return _dest;
	}

	inline wchar_t *utox(wchar_t *_dest, u32 _destSize, u32 _uint)
	{
#ifdef _MSC_VER
		::_itow_s(_uint, _dest, _destSize, 10);
#else
        ::swprintf(_dest, L"%d", _uint);
#endif
		return _dest;
	}

	inline char *i64tox(char *_dest, u32 _destSize, s64 _int)
	{
#ifdef _MSC_VER
		::_i64toa_s(_int, _dest, _destSize, 10);
#else
        ::sprintf(_dest, "%lld", _int);
#endif
		return _dest;
	}

	inline wchar_t *i64tox(wchar_t *_dest, u32 _destSize, s64 _int)
	{
#ifdef _MSC_VER
		::_i64tow_s(_int, _dest, _destSize, 10);
#else
        ::swprintf(_dest, L"%lld", _int);
#endif
		return _dest;
	}

	inline char *u64tox(char *_dest, u32 _destSize, u64 _uint)
	{
#ifdef _MSC_VER
		::_i64toa_s(_uint, _dest, _destSize, 10);
#else
        ::sprintf(_dest, "%llu", _uint);
#endif
		return _dest;
	}

	inline wchar_t *u64tox(wchar_t *_dest, u32 _destSize, u64 _uint)
	{
#ifdef _MSC_VER
		::_i64tow_s(_uint, _dest, _destSize, 10);
#else
        ::swprintf(_dest, L"%llu", _uint);
#endif
		return _dest;
	}

	inline char *ftox(char *_dest, u32 _destSize, f32 _float)
	{
#ifdef _MSC_VER
		::sprintf_s(_dest, _destSize, "%f", _float);
#else
        ::sprintf(_dest, "%f", _float);
#endif
		return _dest;
	}

	inline wchar_t *ftox(wchar_t *_dest, u32 _destSize, f32 _float)
	{
#ifdef _MSC_VER
		::swprintf_s(_dest, _destSize, L"%f", _float);
#else
        ::swprintf(_dest, L"%f", _float);
#endif
		return _dest;
	}

	inline char *dtox(char *_dest, u32 _destSize, f64 _double)
	{
#ifdef _MSC_VER
		::sprintf_s(_dest, _destSize, "%lf", _double);
#else
        ::sprintf(_dest, "%f", _double);
#endif
		return _dest;
	}

	inline wchar_t *dtox(wchar_t *_dest, u32 _destSize, f64 _double)
	{
#ifdef _MSC_VER
		::swprintf_s(_dest, _destSize, L"%lf", _double);
#else
        ::swprintf(_dest, L"%lf", _double);
#endif
		return _dest;
	}

#define DEFINE_XCHARACTER(name, value) \
	template <class T> \
	inline T name(); \
	template <> \
	inline char name<char>() \
	{ \
		return value; \
	} \
	template <> \
	inline wchar_t name<wchar_t>() \
	{ \
		return L##value; \
	} \

	DEFINE_XCHARACTER(xslash, '/')
	DEFINE_XCHARACTER(xbslash, '\\')
	DEFINE_XCHARACTER(xstar, '*')

	inline bool xescapable(char _chr)
	{
		return (
			_chr == '\'' ||
			_chr == '\"' ||
			_chr == '\\');
	}

	inline bool xescapable(wchar_t _chr)
	{
		return (
			_chr == L'\'' ||
			_chr == L'\"' ||
			_chr == L'\\');
	}

	template <class T>
	T *xescape(T *_dest, u32 _destSize, const T *_str)
	{
		if (!_destSize)
			return _dest;

		T *r_dest = _dest;

		while (*_str &&
			--_destSize)
		{
			if (xescapable(*_str))
			{
				if (_destSize - 1 == 0)
					break;

				*_dest = xbslash<T>();
				++_dest;
			}

			*_dest = *_str;

			++_str;
			++_dest;
		}

		*_dest = 0;

		return r_dest;
	}

	template <class T>
	T *trim(T *_dest, u32 _destSize, const T *_str)
	{
		return trim_back(_dest, _destSize, trim_front(_dest, _destSize, _str));
	}

	template <class T>
	T *trim_front(T *_dest, u32 _destsize, const T *_str)
	{
		while (*_str &&
			xisspace(*_str))
		{
			++_str;
		}
		xstrcpy(_dest, _destsize, _str);
		return _dest;
	}

	template <class T>
	const T *trim_front(const T *_str)
	{
		while (*_str &&
			xisspace(*_str))
		{
			++_str;
		}
		return _str;
	}

	template <class T>
	T *trim_back(T *_dest, u32 _destsize, const T *_str)
	{
		T *r_dest = _dest;
		xstrcpy(_dest, _destsize, _str);
		u32 t_strlen = xstrlen(_dest);
		_dest = &_dest[t_strlen];

		while (t_strlen > 0)
		{
			--t_strlen;
			--_dest;
			if (!xisspace(*_dest))
			{
				*(++_dest) = '\0';
				break;
			}
		}

		return r_dest;
	}

	inline bool xisipaddress(const char *_str)
	{
		u32 t_strlen = xstrlen(_str);

		static s32 n;
		static u32 a, b, c, d;

		if (t_strlen <= 15 &&
#ifdef _MSC_VER
		   sscanf_s(_str, "%3u.%3u.%3u.%3u%n", &a, &b, &c, &d, &n) >= 4 &&
#else
		   sscanf(_str, "%3u.%3u.%3u.%3u%n", &a, &b, &c, &d, &n) >= 4 &&
#endif
		   n == s32(t_strlen))
		{
			return (
				a <= 255 &&
				b <= 255 &&
				c <= 255 &&
				d <= 255);
		}

		return false;
	}

	inline bool xisipaddress(const wchar_t *_str)
	{
		u32 t_strlen = xstrlen(_str);

		static s32 n;
		static u32 a, b, c, d;

		if (t_strlen <= 15 &&
#ifdef _MSC_VER
		   swscanf_s(_str, L"%3u.%3u.%3u.%3u%n", &a, &b, &c, &d, &n) >= 4 &&
#else
		   swscanf(_str, L"%3u.%3u.%3u.%3u%n", &a, &b, &c, &d, &n) >= 4 &&
#endif
		   n == s32(t_strlen))
		{
			return (
				a <= 255 &&
				b <= 255 &&
				c <= 255 &&
				d <= 255);
		}

		return false;
	}


	//maths

	inline f32 sqrtf(f32 _float)
	{
		return ::sqrt(_float);
	}

	inline f64 sqrtd(f64 _double)
	{
		return ::sqrt(_double);
	}

	template <class T>
	T pow2(const T &_number)
	{
		return _number * _number;
	}

	template <class T>
	T pow3(const T &_number)
	{
		return _number * _number * _number;
	}

	void seed(u32 _number);

	u32 random();

	u32 random(u32 _max);

	u32 random(u32 _min, u32 _max);

	u32 random32(); //better results up to 0xffffffff

	u32 random32(u32 _max);

	u32 random32(u32 _min, u32 _max);

	f32 randomf();

	f64 randomd();

	inline bool equalf(f32 _float1, f32 _float2)
	{
		return (
			_float1 - 0.000001f < _float2 &&
			_float1 + 0.000001f > _float2);
	}

	inline bool eventf(f32 _chance)
	{
		return (_chance > randomf());
	}

	inline bool eventd(f64 _chance)
	{
		return (_chance > randomd());
	}


	//other

	template <class T>
	void swap(T &_first, T &_second)
	{
		T t_temp = _first;
		_first = _second;
		_second = t_temp;
	}


	//file

#ifndef _MSC_VER
	inline int fopen_s(FILE **_file, const char *_name, const char *_mode)
	{
	    *_file = fopen(_name, _mode);
	    return 0;
	}

#define fprintf_s fprintf
#endif

	inline u32 filesize(FILE *_file)
	{
		long t_pos = ftell(_file);
		fseek(_file, 0, SEEK_END);
		u32 r_filesize = static_cast<u32>(ftell(_file));
		fseek(_file, t_pos, SEEK_SET);
		return r_filesize;
	}

	inline bool freadall(Byte *_dest, u32 _bytes, FILE *_file)
	{
		FDASSERT(_bytes <= filesize(_file));

		u32 t_totalbytesread = 0;
		u32 t_bytesread = 0;

		while (ferror(_file) == 0 &&
			t_totalbytesread < _bytes)
		{
			t_bytesread = fread(_dest + t_totalbytesread, sizeof(Byte), (_bytes - t_totalbytesread), _file);

			t_totalbytesread += t_bytesread;
		}

		return (t_totalbytesread == _bytes);
	}
};


#endif //CORE_UTIL_H
