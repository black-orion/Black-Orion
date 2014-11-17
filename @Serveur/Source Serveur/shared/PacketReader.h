#ifndef PACKETREADER_H
#define PACKETREADER_H


#include "Base.h"


class IPacketReader
{
public:

	static s32 readLoginHeader(CByteArray &_packet);

	static s32 readCharHeader(CByteArray &_packet);

	static s32 readWorldHeader(CByteArray &_packet);

};


#endif //PACKETREADER_H