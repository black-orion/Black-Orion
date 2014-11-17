#include "Timed.h"


TimeMs ITimed::ms_time = 0;

TimeMs ITimed::ms_lastUpdate = 0;

CArray<ITimed*> ITimed::ms_timedObjects;

ITimed::ITimed()
{
	_addTimedObject(this);
}

ITimed::~ITimed()
{
	_removeTimedObject(this);
}

void ITimed::update()
{
}

void ITimed::updateAll()
{
	ms_time = CTime::system();

	if (ms_time != ms_lastUpdate)
	{
		FOR_EACH (ms_timedObjects, i)
		{
			ms_timedObjects[i]->update();
		}

		ms_lastUpdate = ms_time;
	}
}

void ITimed::cleanup()
{
	ms_timedObjects.destroy();
}

TimeMs ITimed::_time()
{
	return ms_time;
}

void ITimed::_addTimedObject(ITimed *_obj)
{
	FDASSERT(_obj);

	ms_timedObjects.push_back(_obj);
}

void ITimed::_removeTimedObject(ITimed *_obj)
{
	FDASSERT(_obj);

	ms_timedObjects.erase_vfast(_obj);
}