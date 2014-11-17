#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H


//Include this file whereever you want to detect memory leaks.
//In blackorion it should be included by "shared/base.h".
//Include all standard libs before!
//The redefinition of 'new' does not tolerate placement new's.


#ifndef NDEBUG
#ifdef _MSC_VER

#define _CRTDBG_MAP_ALLOC
#define _INC_MALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)

#endif //!NDEBUG
#endif //_MSC_VER


#endif //MEMORY_LEAK_H
