#include "Log.h"


FILE *ILog::ms_file = 0;

char ILog::ms_buffer[BUF_SIZE];

bool ILog::open(const char *_fileName)
{
	CConsole::setTextColor(CC_WHITE);

	//close if already opened
	close();

	//open
	fopen_s(&ms_file, _fileName, "a");

	if (ms_file)
	{
		fprintf_s(ms_file,
			"\n\n");

		return true;
	}

	return false;
}

void ILog::close()
{
	if (ms_file)
	{
		fprintf_s(ms_file,
			"\n\n");

		fclose(ms_file);
	}
}

void ILog::write(E_LOG_LEVEL _type, const char *_format, ...)
{
	FDASSERT(_format);

	va_list t_args;
	va_start(t_args, _format);
	vsnprintf(ms_buffer, BUF_SIZE - 1, _format, t_args);
	va_end(t_args);

	_printLogLevel(_type);

	printf("%s\n", ms_buffer);

	//save to file
	if (ms_file)
	{
		_printLogLevelToFile(_type);

		fprintf_s(ms_file, "%s\n", ms_buffer);
	}
}

void ILog::write(const char *_format, ...)
{
	FDASSERT(_format);

	va_list t_args;
	va_start(t_args, _format);
	vsnprintf(ms_buffer, BUF_SIZE - 1, _format, t_args);
	va_end(t_args);

	_printLogLevel(LOG_DEBUG);

	printf("%s\n", ms_buffer);

	//save to file
	if (ms_file)
	{
		_printLogLevelToFile(LOG_DEBUG);

		fprintf_s(ms_file, "%s\n", ms_buffer);
	}
}

void ILog::_printLogLevel(E_LOG_LEVEL _type)
{
	switch (_type)
	{
	case LOG_INFO:
		CConsole::setTextColor(CC_DARKRED);
		printf("[INFORMATION] ");
		break;

	case LOG_DEBUG:
		CConsole::setTextColor(CC_DARKGREEN);
		printf("[ORION-MODE] ");
		break;

	case LOG_WARNING:
		CConsole::setTextColor(CC_YELLOW);
		printf("[ATTENTION] ");
		break;

	case LOG_ERROR:
		CConsole::setTextColor(CC_RED);
		printf("[ERREUR] ");
		break;

	case LOG_CRITICAL:
		CConsole::setTextColor(CC_MAGENTA);
		printf("[CRITIQUE] ");
		break;

	case LOG_SUCCESS:
		CConsole::setTextColor(CC_GREEN);
		printf("[SUCCES] ");
		break;

	case LOG_GAME:
		CConsole::setTextColor(CC_BLUE);
		printf("[LOG] ");
		break;

	case LOG_ISC:
		CConsole::setTextColor(CC_CYAN);
		printf("[ISC-LINK] ");
		break;
	}

	CConsole::setTextColor(CC_WHITE);
}

void ILog::_printLogLevelToFile(E_LOG_LEVEL _type)
{
	FDASSERT(ms_file);

	switch (_type)
	{
	case LOG_INFO:
		fprintf_s(ms_file, "[INFORMATION] ");
		break;

	case LOG_DEBUG:
		fprintf_s(ms_file, "[ORION-MODE] ");
		break;

	case LOG_WARNING:
		fprintf_s(ms_file, "[ATTENTION]] ");
		break;

	case LOG_ERROR:
		fprintf_s(ms_file, "[ERREUR] ");
		break;

	case LOG_CRITICAL:
		fprintf_s(ms_file, "[CRITIQUE] ");
		break;

	case LOG_SUCCESS:
		fprintf_s(ms_file, "[SUCCES] ");
		break;

	case LOG_GAME:
		fprintf_s(ms_file, "[LOG] ");
		break;

	case LOG_ISC:
		fprintf_s(ms_file, "[ISC-LINK] ");
		break;
	}
}
