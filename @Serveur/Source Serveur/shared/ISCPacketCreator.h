#ifndef ISCPACKETCREATOR_H
#define ISCPACKETCREATOR_H


#include "Base.h"
#include "E_ISC.h"


class IISCPacketCreator
{
public:

	static void cleanup();

	//sent by connector
	//_extid should be unique in the network, _additional is the cluster ID if a channel auths
	static const CByteArray &auth(E_ISC_CLIENT_TYPE _type, const char *_password, const char *_name,
		const char *_thisip, ID _extid, s32 _additional = 0);

	static const CByteArray &logout(ID _sid);

	//channel
	static const CByteArray &channelInfos(s32 _currplayers, s32 _maxplayers);

	//sent to client
	enum E_AUTH_ANSWER
	{
		ANSWER_OK,
		ANSWER_WRONG_PASSWORD,
		ANSWER_ERROR
	};

	static const CByteArray &authAnswer(ID _sid, E_AUTH_ANSWER _answer);

	static const CByteArray &kick();

private:

	static CByteArray ms_packet;

	static void _start(E_ISC_COMMAND _command);

	static void _finish();

};


#endif //ISCPACKETCREATOR_H
