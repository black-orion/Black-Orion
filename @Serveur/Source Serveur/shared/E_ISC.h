#ifndef E_ISC_H
#define E_ISC_H


#include "Base.h"


enum E_ISC_COMMAND
{
	//General
	ISCC_NONE = 0x00,

	//Login
	ISCC_KICK = 0x03,
	ISCC_AUTH_ANSWER = 0x04,

	//Client
	ISCC_AUTH = 0x01,
	ISCC_LOGOUT = 0x02,

	//Char
	ISCC_CHANNEL_INFOS = 0x11
};


enum E_ISC_CLIENT_TYPE
{
	ISC_CLIENT_CLUSTER,
	ISC_CLIENT_CHANNEL
};


#endif //E_ISC_H
