#include "E_ELEMENT.h"


E_ELEMENT element(s32 _eleId)
{
	return E_ELEMENT(Limit<s32>(_eleId, ELE_NONE, ELE_EARTH));
}