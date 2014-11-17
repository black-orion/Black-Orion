#include "E_WEATHER.h"


E_WEATHER weather(s32 _id)
{
	return E_WEATHER(Limit<s32>(_id, WEATHER_NORMAL, WEATHER_RAIN));
}
