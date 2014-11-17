#ifndef LOG_H
#define LOG_H


#include "Base.h"


enum E_LOG_LEVEL
{
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR,
	LOG_CRITICAL,
	LOG_SUCCESS,
	LOG_GAME,
	LOG_ISC
};


class ILog
{
public:

	static bool open(const char *_fileName);

	static void close();

	static void write(E_LOG_LEVEL _type, const char *_format, ...);

	static void write(const char *_format, ...);

private:

	static FILE *ms_file;

	enum
	{
		BUF_SIZE = 4096
	};

	static char ms_buffer[BUF_SIZE];

	static void _printLogLevel(E_LOG_LEVEL _type);

	static void _printLogLevelToFile(E_LOG_LEVEL _type);

};

typedef ILog Log;


#endif //LOG_H
