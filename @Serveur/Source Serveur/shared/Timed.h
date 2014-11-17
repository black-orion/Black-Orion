#ifndef TIMED_H
#define TIMED_H


#include "Base.h"


class ITimed
{
public:

	ITimed();

	virtual ~ITimed();

	virtual void update();

	static void updateAll();

	static void cleanup();

protected:

	static TimeMs _time();

	static void _addTimedObject(ITimed *_obj);

	static void _removeTimedObject(ITimed *_obj);

private:

	static TimeMs ms_time;

	static TimeMs ms_lastUpdate;

	static CArray<ITimed*> ms_timedObjects;

};


#endif //TIMED_H
