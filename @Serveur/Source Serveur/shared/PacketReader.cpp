#include "PacketReader.h"


s32 IPacketReader::readLoginHeader(CByteArray &_packet)
{
	//check the 1st byte
	if (_packet.getByte() != NET_PACKET_BEGIN)
		return 0;

	//skip the checksum
	_packet.getInt();

	//check the size
	u32 t_packetSize = static_cast<u32>(_packet.getInt());

	if (t_packetSize > _packet.size() - 13)
		return 0;

	//content checksum
	_packet.getInt();

	//the command
	return _packet.getInt();
}


s32 IPacketReader::readCharHeader(CByteArray &_packet)
{
	//check the 1st byte
	if (_packet.getByte() != NET_PACKET_BEGIN)
		return 0;

	//skip the checksum
	_packet.getInt();

	//check the size
	u32 t_packetSize = static_cast<u32>(_packet.getInt());

	if (t_packetSize > _packet.size() - 13)
		return 0;

	//content checksum
	_packet.getInt();

	//0xffffffff
	_packet.getInt();

	//the command
	return _packet.getInt();
}


s32 IPacketReader::readWorldHeader(CByteArray &_packet)
{
	//check the 1st byte
	if (_packet.getByte() != NET_PACKET_BEGIN)
		return 0;

	//skip the checksum
	_packet.getInt();

	//check the size
	u32 t_packetSize = static_cast<u32>(_packet.getInt());

	if (t_packetSize > _packet.size() - 13)
		return 0;

	//content checksum
	_packet.getInt();

	//0xffffffff
	_packet.getInt();

	//the command
	return _packet.getInt();
}