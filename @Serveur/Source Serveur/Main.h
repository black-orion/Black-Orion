#ifndef MAIN_H
#define MAIN_H


#include "shared/Base.h"


//// SETTINGS ////
//////////////////


enum E_SERVER_TYPE
{
	ST_NONE = 0,
	ST_LOGIN = 1,
	ST_CHAR = 2,
	ST_WORLD = 3
};


//1 for Login, 2 for Char, 3 for World
#define SERVER_TYPE 1


//Settings

//link statically or dynamically
#ifndef SDEBUG
#define SETTING_MYSQL_STATIC_LINK
#endif


#endif //MAIN_H
