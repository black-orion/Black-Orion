#include "ISCPacketReader.h"


E_ISC_COMMAND IISCPacketReader::readHeader(CByteArray &_packet)
{
	if (_packet.size() < 5)
	{
		printf("ISC error: Packet too short!\n");
		return ISCC_NONE;
	}

	//check the begin
	if (_packet.getByte() != ISC_PACKET_BEGIN)
	{
		printf("ISC error: First byte wrong!\n");
		return ISCC_NONE;
	}

	//size
	u32 t_size = static_cast<u32>(_packet.getInt());

	if (t_size > _packet.size() - 5)
	{
		printf("ISC error: Wrong packet size!\n");
		return ISCC_NONE;
	}

	//command
	return E_ISC_COMMAND(_packet.getInt());
}