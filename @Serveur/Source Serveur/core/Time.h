#ifndef CORE_TIME_H
#define CORE_TIME_H


#include "CoreBase.h"


BEGIN_NAMESPACE_CORE
{

	class CTime
	{
	public:

		static TimeMs system();

		static s64 seconds();

	};

};


#endif //CORE_TIME_H
