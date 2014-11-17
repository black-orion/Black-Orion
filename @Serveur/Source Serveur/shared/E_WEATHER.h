#ifndef E_WEATHER_H
#define E_WEATHER_H


#include "Base.h"


enum E_WEATHER
{
	WEATHER_NORMAL,
	WEATHER_SNOW,
	WEATHER_RAIN
};

E_WEATHER weather(s32 _id);


#endif //E_WEATHER_H
