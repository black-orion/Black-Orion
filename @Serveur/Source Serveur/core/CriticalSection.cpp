#include "CriticalSection.h"


BEGIN_NAMESPACE_CORE
{

	CCriticalSection::CCriticalSection()
	{
#ifdef OS_WINDOWS
		InitializeCriticalSection(&m_cs);
#endif
	}

	CCriticalSection::~CCriticalSection()
	{
#ifdef OS_WINDOWS
		DeleteCriticalSection(&m_cs);
#endif
	}

	void CCriticalSection::enter()
	{
#ifdef OS_WINDOWS
		EnterCriticalSection(&m_cs);
#endif
	}

	void CCriticalSection::leave()
	{
#ifdef OS_WINDOWS
		LeaveCriticalSection(&m_cs);
#endif
	}

};
