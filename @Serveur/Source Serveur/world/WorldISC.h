#ifndef WORLDISC_H
#define WORLDISC_H


#include "WorldMain.h"
#include "WorldSettings.h"


class IWorldServer;


class IWorldISC
{
public:

	IWorldISC(IWorldISCSettings *_settings, IWorldServer *_server);

	~IWorldISC();

	bool init(CNetwork *_network);

	bool run();

private:

	//Settings
	IWorldISCSettings *m_settings;

	//Server
	IWorldServer *m_pserver;

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


#endif //WORLDISC_H
