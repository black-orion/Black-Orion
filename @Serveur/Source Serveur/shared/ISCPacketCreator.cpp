#include "ISCPacketCreator.h"


CByteArray IISCPacketCreator::ms_packet = CByteArray();

void IISCPacketCreator::cleanup()
{
	ms_packet.destroy();
}

const CByteArray &IISCPacketCreator::auth(E_ISC_CLIENT_TYPE _type, const char *_password,
										  const char *_name, const char *_thisip, ID _extid, s32 _additional)
{
	_start(ISCC_AUTH);

	ms_packet.addInt(_type);
	ms_packet.addString(_password);
	ms_packet.addString(_name);
	ms_packet.addString(_thisip);
	ms_packet.addInt(_extid);
	ms_packet.addInt(_additional);

	_finish();

	return ms_packet;
}

const CByteArray &IISCPacketCreator::logout(ID _sid)
{
	_start(ISCC_LOGOUT);

	ms_packet.addInt(_sid);

	_finish();

	return ms_packet;
}

const CByteArray &IISCPacketCreator::channelInfos(s32 _currplayers, s32 _maxplayers)
{
	_start(ISCC_CHANNEL_INFOS);

	ms_packet.addInt(_currplayers);
	ms_packet.addInt(_maxplayers);

	_finish();

	return ms_packet;
}

const CByteArray &IISCPacketCreator::authAnswer(ID _sid, E_AUTH_ANSWER _answer)
{
	_start(ISCC_AUTH_ANSWER);

	ms_packet.addInt(_sid);
	ms_packet.addInt(_answer);

	_finish();

	return ms_packet;
}

const CByteArray &IISCPacketCreator::kick()
{
	_start(ISCC_KICK);

	_finish();

	return ms_packet;
}

void IISCPacketCreator::_start(E_ISC_COMMAND _command)
{
	ms_packet.clear();

	//begin
	ms_packet.addByte(ISC_PACKET_BEGIN);

	//size
	ms_packet.addInt(0);

	//command
	ms_packet.addInt(_command);
}

void IISCPacketCreator::_finish()
{
	FDASSERT(ms_packet.size() >= 9);

	ms_packet.setInt(1, ms_packet.size() - 5);
}