#ifndef CORE_DEBUG_H
#define CORE_DEBUG_H


#include "CoreBase.h"


BEGIN_NAMESPACE_CORE
{

	//// Error output ////

	bool debug_error_(const char *_fileName, u32 _line, const char *_format, ...);

};

#define debug_error(format,...) NAMESPACE_CORE::debug_error_(__FILE__,__LINE__,format,__VA_ARGS__)

//#define FASSERT(expr) do{if(!(expr)){debug_error("Expression: \"" #expr "\"");}}while(0)
#define FASSERT(expr) do{ }while(0)

#ifdef SDEBUG
#define DEBUG_ONLY(code) code
#else
#define DEBUG_ONLY(code) (void(0))
#endif

#ifdef SDEBUG
#define DEBUG_NOT(code) (void(0))
#else
#define DEBUG_NOT(code) code
#endif

#ifdef SDEBUG
#define DEBUG_BEGIN
#else
#define DEBUG_BEGIN if (false)
#endif

#define FDASSERT(expr) DEBUG_ONLY(FASSERT(expr))

#ifdef SDEBUG
#define DEBUG_VAR(debug,release) (debug)
#else
#define DEBUG_VAR(debug,release) (release)
#endif

#ifdef SDEBUG
#define DEBUG_ON (true)
#else
#define DEBUG_ON (false)
#endif


#endif //CORE_DEBUG_H
