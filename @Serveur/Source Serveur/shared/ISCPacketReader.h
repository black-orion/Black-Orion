#ifndef ISCPACKETREADER_H
#define ISCPACKETREADER_H


#include "Base.h"
#include "E_ISC.h"


class IISCPacketReader
{
public:

	static E_ISC_COMMAND readHeader(CByteArray &_packet);

};


#endif //ISCPACKETREADER_H
