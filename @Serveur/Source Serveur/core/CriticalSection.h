#ifndef CORE_CRITICALSECTION_H
#define CORE_CRITICALSECTION_H


#include "CoreBase.h"

#ifdef OS_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif


BEGIN_NAMESPACE_CORE
{

	class CCriticalSection
	{
	public:

		CCriticalSection();

		~CCriticalSection();

		void enter();

		void leave();

	private:

#ifdef OS_WINDOWS

		CRITICAL_SECTION m_cs;

#endif

	};


	class CTempLock
	{
	public:

		CTempLock(CCriticalSection &_cs)
			: m_cs(_cs)
		{
			m_cs.enter();
		}

		~CTempLock()
		{
			m_cs.leave();
		}

	private:

		CCriticalSection &m_cs;

	};

};


#endif //CORE_CRITICALSECTION_H
