#ifndef CHARISC_H
#define CHARISC_H


#include "CharMain.h"
#include "CharSettings.h"


class ICharServer;


class ICharISC
{
public:

	ICharISC(ICharISCSettings *_settings, ICharServer *_server);

	~ICharISC();

	bool init(CNetwork *_network);

	bool run();

private:

	//Settings
	ICharISCSettings *m_settings;

	//Server
	ICharServer *m_pserver;

	//Connector
	struct LoginConnection
	{
		CNetConnector *Connector;

		Time NextConnect;

		bool IsWaitingForAuthAnswer;

		ID Id;

		LoginConnection()
			: Connector(0)
			, NextConnect(1)
			, IsWaitingForAuthAnswer(false)
			, Id(0)
		{
		}
	};

	LoginConnection m_connection;

	//Login connection
	bool _handlePacket(CNetConnector *_client);

	bool _cmdHandler_authAnswer(CNetConnector *_client);

};


#endif //CHARISC_H
