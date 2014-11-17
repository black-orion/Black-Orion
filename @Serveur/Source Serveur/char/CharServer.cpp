#include "CharServer.h"
#include "CharPlayer.h"
#include "../shared/Account.h"
#include "../shared/Character.h"
#include "../shared/PacketCreator.h"
#include "../shared/PacketReader.h"
#include "../shared/Log.h"


ICharServer::ICharServer()
	: m_acceptor(0)
	, m_accountMngr(&m_dbc_0)
	, m_charMngr(0, &m_accountMngr, &m_itemPackMngr)
	, m_itemPackMngr(0, &m_itemDataMngr)
	, m_nextSaveTime(0)
	, m_itemDataMngr(&m_settings.Data.Items)
	, m_isc(&m_settings.ISC, this)
{
}

ICharServer::~ICharServer()
{
	FOR_EACH (m_players, i)
	{
		delete m_players[i];
	}

	m_accountMngr.clear();
	m_charMngr.clear();
	m_itemPackMngr.clear();

	m_net.shutdown();
}

void ICharServer::start()
{
	if (!_load())
	{
		CConsole::wait();
		return;
	}

	while (_main());
}

ICharPlayer *ICharServer::_getPlayer(s32 _id)
{
	FOR_EACH (m_players, i)
	{
		if (m_players[i]->getId() == _id)
		{
			return m_players[i];
		}
	}

	return 0;
}

ICharPlayer *ICharServer::_createPlayer(CNetClient *_client)
{
	ICharPlayer *r_newPlayer = new ICharPlayer(_generatePlayerId(), _client);

	m_players.push_back(r_newPlayer);

	return r_newPlayer;
}

s32 ICharServer::_generatePlayerId()
{
	s32 r_newId = 1;

	while (_getPlayer(r_newId))
		++r_newId;

	return r_newId;
}

bool ICharServer::_load()
{
	//console title
	_setTitle();

	CConsole::initCloseHandler();

	//load configuration file
	if (!m_settings.load(CHAR_SETTINGS_FILE_NAME))
	{
		Log::write(LOG_ERROR, "Setting file \"%s\" could not be loaded!", CHAR_SETTINGS_FILE_NAME);
	}

	//open log file
	if (!Log::open(m_settings.Program.LogFileName.c_str()))
	{
		Log::write(LOG_ERROR, "Log file \"%s\" could not be opened!", m_settings.Program.LogFileName.c_str());
	}

	//init network
	if (!m_net.startup())
	{
		Log::write(LOG_CRITICAL, "Network could not be started!");

		return false;
	}

	m_net.setWaitingTime(33);

	//load items
	if (!m_itemDataMngr.load_char())
	{
		return false;
	}

	m_settings.Character.loadStartItems(&m_itemDataMngr);

	//connect to database
	if (!m_dbc_0.connect(
		m_settings.Database.Host.c_str(),
		m_settings.Database.Port,
		m_settings.Database.User.c_str(),
		m_settings.Database.Password.c_str(),
		m_settings.Database.Database.c_str()))
	{
		Log::write(LOG_ERROR, "Could not connect to the database (0): %s\n", m_dbc_0.getError());

		return false;
	}

	IDatabaseConnection *t_pdbc = 0;

	//same database
	if (m_settings.Database.Host == m_settings.Database.Host &&
		m_settings.Database.Port == m_settings.Database.Port &&
		m_settings.Database.User == m_settings.Database.User &&
		m_settings.Database.Password == m_settings.Database.Password &&
		m_settings.Database.Database == m_settings.Database.Database)
	{
		t_pdbc = &m_dbc_0;
	}

	else
	{
		if (!m_dbc_1.connect(
			m_settings.Database.Host.c_str(),
			m_settings.Database.Port,
			m_settings.Database.User.c_str(),
			m_settings.Database.Password.c_str(),
			m_settings.Database.Database.c_str()))
		{
			Log::write(LOG_ERROR, "Could not connect to the database (1): %s\n", m_dbc_1.getError());

			return false;
		}

		t_pdbc = &m_dbc_1;
	}

	//init character manager
	m_charMngr.setDbc(t_pdbc);
	m_itemPackMngr.setDbc(t_pdbc);

	Log::write(LOG_SUCCESS, "Connected to the database");

	//init ISC
	if (!m_isc.init(&m_net))
	{
		Log::write(LOG_ERROR, "ISC could not be initialized");

		return false;
	}

	//create acceptor on port 28000
	m_acceptor = m_net.createAcceptor(m_settings.Game.Port);

	if (!m_acceptor)
	{
		Log::write(LOG_ERROR, "Game port %u could not be used", m_settings.Game.Port);

		return false;
	}

	return true;
}

bool ICharServer::_main()
{
	//check if the console is closed
	if (CConsole::isClosed())
		return false;

	//run the network
	if (!m_net.run())
	{
		return false;
	}

	//run the ISC
	if (!m_isc.run())
	{
		return false;
	}

	//handle new connections
	while (m_acceptor->isNew())
	{
		ICharPlayer *t_player = _createPlayer(m_acceptor->popClient());

		Log::write(LOG_DEBUG, "New Player connection");

		//send greeting
		t_player->getClient()->send(IPacketCreator::greeting(t_player->getId()));
	}

	//handle new data
	FOR_EACH (m_players, i)
	{
		//player disconnected
		if (!m_players[i]->getClient()->isConnected())
		{
			Log::write(LOG_GAME, "Player disconnected");

			delete m_players[i];
			m_players.erase(i);
			if (i)
				--i;
		}

		//new packets
		else if (!m_players[i]->getClient()->incoming().empty())
		{
			while (_handlePacket(m_players[i]));

			m_players[i]->getClient()->incoming().clear();
		}
	}

	ITimed::updateAll();

	return true;
}

void ICharServer::_setTitle()
{
	char t_buffer[256];

	sprintf(t_buffer, "%s %s", CHAR_PROGRAM_NAME, blackorion_getVersionStr());

	CConsole::setTitle(t_buffer);
}

bool ICharServer::_handlePacket(ICharPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	s32 t_command = IPacketReader::readCharHeader(t_packet);

	//handle the command
	switch (t_command)
	{
	case 0xf6:
		return _cmdHandler_charList(_player);

	case 0xf4:
		return _cmdHandler_createChar(_player);

	case 0xf5:
		return _cmdHandler_deleteChar(_player);

	case 0x0b:
		return _cmdHandler_unknown_1(_player);

	case 0x14:
		return _cmdHandler_ping(_player);

	case 0xff05:
		return _cmdHandler_worldLogin(_player);

	case 0:
		Log::write(LOG_WARNING, "Packet endommagée recu");
		return false;

	default:
		Log::write(LOG_DEBUG, "Packet Inconnu (%x)", t_command);

#ifdef SDEBUG
		sprintf(m_buffer, "logs/_inconnue_%x.txt", t_command);
		t_packet.saveFormatted(m_buffer);
#endif

		return false;
	}

	return !t_packet.end();
}

bool ICharServer::_cmdHandler_charList(ICharPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char ts_buf_1[T_BUF_SIZE];
	static char ts_buf_2[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//client compile date (ignore)
	if (!t_packet.getString(ts_buf_1, T_BUF_SIZE))
		return false;

	//???
	t_packet.getInt();

	//name
	if (!t_packet.getString(ts_buf_1, T_BUF_SIZE))
		return false;

	//password
	if (!t_packet.getString(ts_buf_2, T_BUF_SIZE))
		return false;

	//channel-ID
	s32 t_channelId = t_packet.getInt();

	//check login information
	AccountPtr t_account = m_accountMngr.getAccount_C(ts_buf_1);

	if (t_account &&
		xstricmp(t_account->getPassword(), ts_buf_2) == 0)
	{
		_player->setAccount(t_account);

		if (!m_charMngr.getCharacters_C(_player))
		{
			Log::write(LOG_WARNING, "Pas de Personnage");
		}

		_player->getClient()->send(IPacketCreator::charList(_player));

		if (strcmp("127.0.0.1", _player->getClient()->getIp()) == 0)
		{
			_player->getClient()->send(IPacketCreator::worldIp("127.0.0.1"));
		}
		else
		{
			_player->getClient()->send(IPacketCreator::worldIp(m_settings.ISC.ThisIP.c_str())); //TODO!!!
		}

		Log::write(LOG_GAME, "Le Joueur accedes a ses Personnages");
	}
	else
	{
		return false;
	}


	return !t_packet.end();
}

bool ICharServer::_cmdHandler_createChar(ICharPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char ts_buf_1[T_BUF_SIZE];
	static char ts_buf_2[T_BUF_SIZE];

	FDASSERT(_player);

	if (!_player->getAccount())
		return false;

	CByteArray &t_packet = _player->getClient()->incoming();

	//name
	if (!t_packet.getString(ts_buf_1, T_BUF_SIZE))
		return false;

	//password
	if (!t_packet.getString(ts_buf_2, T_BUF_SIZE))
		return false;

	if (xstricmp(_player->getAccount()->getName(), ts_buf_1) != 0 ||
		xstricmp(_player->getAccount()->getPassword(), ts_buf_2) != 0)
	{
		return false;
	}

	//place
	s32 t_place = t_packet.getByte();

	if (t_place < 0 ||
		t_place > 2)
	{
		return false;
	}

	//character name
	if (!t_packet.getString(ts_buf_1, T_BUF_SIZE))
		return false;

	t_packet.skip(3);

	//hair
	s32 t_hairType = t_packet.getByte();

	s32 t_hairColor = t_packet.getInt();

	//sex
	E_SEX t_sex = E_SEX(t_packet.getShort());

	if (t_sex != SEX_MALE &&
		t_sex != SEX_FEMALE)
	{
		return false;
	}

	//face
	s32 t_faceType = t_packet.getByte();

	t_packet.getInt();

	//name too long
	u32 t_nameLen = strlen(ts_buf_1);
	if (t_nameLen < CHARACTER_NAME_MIN ||
		t_nameLen > CHARACTER_NAME_MAX)
	{
		return false;
	}

	//check the name for invalid letters
/*	static const tr1::regex TS_CHAR_NAME_REGEX("[a-zA-Z0-9]+");
	if (!tr1::regex_match(ts_buf_1, TS_CHAR_NAME_REGEX))
	{
		return false;
	}
*/
	//is the name in use?
	if (m_charMngr.getCharacter_C(ts_buf_1))
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_NAME_IN_USE));
	}

	else
	{
		if (!m_charMngr.createCharacter_C(_player, t_place, ts_buf_1, t_sex, t_hairType,
			t_hairColor, t_faceType, &m_settings.Character))
		{
			Log::write(LOG_ERROR, "Erreur dans la Création de personnage!");
		}

		_player->getClient()->send(IPacketCreator::charList(_player));
	}

	return !t_packet.end();
}

bool ICharServer::_cmdHandler_deleteChar(ICharPlayer *_player)
{
	FDASSERT(_player);

	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf_1[TS_BUF_SIZE];
	static char ts_buf_2[TS_BUF_SIZE];
	static char ts_buf_3[TS_BUF_SIZE];

	if (!_player->getAccount())
		return false;

	CByteArray &t_packet = _player->getClient()->incoming();

	// username
	if(!t_packet.getString(ts_buf_1, TS_BUF_SIZE))
		return false;

	// password
	if(!t_packet.getString(ts_buf_2, TS_BUF_SIZE))
		return false;

	// password validation
	if(!t_packet.getString(ts_buf_3, TS_BUF_SIZE))
		return false;

	ID t_charId = t_packet.getInt();
	t_packet.getInt(); //???

	// Check sent data
	if (xstricmp(ts_buf_1, _player->getAccount()->getName()) != 0)
		return false;

	if (xstricmp(ts_buf_2, ts_buf_3) != 0)
		return false;

	if (xstricmp(ts_buf_2, _player->getAccount()->getPassword()) != 0)
		return false;

	CharacterPtr t_char = m_charMngr.getCharacter_C(t_charId, false);
	if (!t_char)
	{
		return false;
	}

	if (!_player->getAccount()->isCharOn(t_char))
	{
		return false;
	}

	m_charMngr.deleteCharacter_C(t_char);

	_player->getAccount()->removeCharacter(t_char);

	_player->getClient()->send(IPacketCreator::charList(_player));

	return !t_packet.end();
}

bool ICharServer::_cmdHandler_unknown_1(ICharPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//???
	t_packet.getInt();

	return !t_packet.end();
}

bool ICharServer::_cmdHandler_ping(ICharPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getInt();

	// PING

	return !t_packet.end();
}

bool ICharServer::_cmdHandler_worldLogin(ICharPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char ts_buf[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//acc name
	if (!t_packet.getString(ts_buf, T_BUF_SIZE))
		return false;

	if (xstricmp(_player->getAccount()->getName(), ts_buf) != 0)
		return false;

	//???
	t_packet.getInt();

	//char name
	if (!t_packet.getString(ts_buf, T_BUF_SIZE))
		return false;

	if (!_player->getAccount()->isCharOn(ts_buf))
		return false;

	//...

	Log::write(LOG_GAME, "Le Joueur va IG");

	_player->getClient()->send(IPacketCreator::confirmWorld());

	_player->getAccount()->solve();

	return !t_packet.end();
}
