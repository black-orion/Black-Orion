#ifndef LOGINSERVER_H
#define LOGINSERVER_H


#include "LoginMain.h"
#include "LoginSettings.h"
#include "LoginISC.h"
#include "LoginDatabase.h"
#include "../shared/Account.h"
#include "../shared/DatabaseConnection.h"


class ILoginPlayer;


class ILoginServer
{
public:

	ILoginServer();

	~ILoginServer();

	void start();

private:

	enum
	{
		BUF_SIZE = 1024
	};

	char m_buffer[BUF_SIZE];

	//Settings
	ILoginSettings m_settings;

	//Networking
	CNetwork m_net;

	CNetAcceptor *m_acceptor;

	//Players
	CArray<ILoginPlayer*> m_players;

	IAccount::E_ACCESS_LEVEL m_reqAccessLevel;

	//ISC
	ILoginISC m_isc;

	friend class ILoginISC;

	//Database
	IDatabaseConnection m_dbc;

	ILoginDatabase m_database;


	//:: FUNCTIONS ::

	ILoginPlayer *_getPlayer(s32 _id);

	ILoginPlayer *_createPlayer(CNetClient *_client);

	s32 _generatePlayerId();

	//loads config, database, inits network, etc
	bool _load();

	//the main loop
	bool _main();

	//sets the title to "blackorion Login {version}"
	void _setTitle();

	//reads the packet header
	bool _handlePacket(ILoginPlayer *_player);

	//command handlers
	bool _cmdHandler__erreur(ILoginPlayer *_player);

	bool _cmdHandler_login(ILoginPlayer *_player);

	bool _cmdHandler_loginRetry(ILoginPlayer *_player);

	bool _cmdHandler_unknown_1(ILoginPlayer *_player);

};


#endif //LOGINSERVER_H
