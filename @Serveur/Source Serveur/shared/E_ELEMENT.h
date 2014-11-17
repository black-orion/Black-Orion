#ifndef E_ELEMENT_H
#define E_ELEMENT_H


#include "Base.h"


enum E_ELEMENT
{
	ELE_NONE = 0,

	ELE_FIRE = 1,
	ELE_WATER = 2,
	ELE_ELECTRICITY = 3,
	ELE_WIND = 4,
	ELE_EARTH = 5
};


E_ELEMENT element(s32 _eleId);


#endif //E_ELEMENT_H
