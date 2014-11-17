#ifndef CHARSERVER_H
#define CHARSERVER_H


#include "CharMain.h"
#include "CharSettings.h"
#include "CharISC.h"
#include "../shared/AccountManager.h"
#include "../shared/CharacterManager.h"
#include "../shared/ItemPackManager.h"
#include "../shared/ItemDataManager.h"
#include "../shared/DatabaseConnection.h"


class ICharPlayer;


class ICharServer
{
public:

	ICharServer();

	~ICharServer();

	void start();

private:

	enum
	{
		BUF_SIZE = 1024
	};

	char m_buffer[BUF_SIZE];

	//Settings
	ICharSettings m_settings;

	//Networking
	CNetwork m_net;

	CNetAcceptor *m_acceptor;

	//Data
	IItemDataManager m_itemDataMngr;

	//Players
	CArray<ICharPlayer*> m_players;

	//ISC
	ICharISC m_isc;

	friend class ICharISC;

	//Database
	IDatabaseConnection m_dbc_0;

	IDatabaseConnection m_dbc_1;

	IAccountManager m_accountMngr;

	ICharacterManager m_charMngr;

	IItemPackManager m_itemPackMngr;

	//not really used
	TimeMs m_nextSaveTime;


	//:: FUNCTIONS ::

	ICharPlayer *_getPlayer(s32 _id);

	ICharPlayer *_createPlayer(CNetClient *_client);

	s32 _generatePlayerId();

	//loads config, database, inits network, etc
	bool _load();

	//the main loop
	bool _main();

	//sets the title to "blackorion Char {version}"
	void _setTitle();

	//reads the packet header
	bool _handlePacket(ICharPlayer *_player);

	//command handlers
	bool _cmdHandler_charList(ICharPlayer *_player);

	bool _cmdHandler_createChar(ICharPlayer *_player);

	bool _cmdHandler_deleteChar(ICharPlayer *_player);

	bool _cmdHandler_unknown_1(ICharPlayer *_player);

	bool _cmdHandler_ping(ICharPlayer *_player);

	bool _cmdHandler_worldLogin(ICharPlayer *_player);

};


#endif //CHARSERVER_H
