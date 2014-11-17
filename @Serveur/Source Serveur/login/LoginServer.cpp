#include "LoginServer.h"
#include "LoginPlayer.h"
#include "../shared/PacketCreator.h"
#include "../shared/PacketReader.h"
#include "../shared/Log.h"


ILoginServer::ILoginServer()
	: m_acceptor(0)
	, m_isc(&m_settings.ISC, this)
	, m_reqAccessLevel(IAccount::ACC_MINIMUM)
{
}

ILoginServer::~ILoginServer()
{
	FOR_EACH (m_players, i)
	{
		delete m_players[i];
	}

	m_net.shutdown();
}

void ILoginServer::start()
{
	if (!_load())
	{
		CConsole::wait();
		return;
	}

	while (_main());
}

ILoginPlayer *ILoginServer::_getPlayer(s32 _id)
{
	FOR_EACH (m_players, i)
	{
		if (m_players[i]->getId() == _id)
			return m_players[i];
	}

	return 0;
}

ILoginPlayer *ILoginServer::_createPlayer(CNetClient *_client)
{
	ILoginPlayer *r_newPlayer = new ILoginPlayer(_generatePlayerId(), _client);

	m_players.push_back(r_newPlayer);

	return r_newPlayer;
}

s32 ILoginServer::_generatePlayerId()
{
	s32 r_newId = 1;

	while (_getPlayer(r_newId))
		++r_newId;

	return r_newId;
}

bool ILoginServer::_load()
{
	//console title
	_setTitle();

	CConsole::initCloseHandler();

	//load configuration file
	if (!m_settings.load(LOGIN_SETTINGS_FILE_NAME))
	{
		Log::write(LOG_ERROR, "Setting file \"%s\" could not be loaded!", LOGIN_SETTINGS_FILE_NAME);
	}

	m_reqAccessLevel = m_settings.Game.RequiredAccessLevel;

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

	//connect to database
	if (!m_dbc.connect(m_settings.Database.Host.c_str(), m_settings.Database.Port,
		m_settings.Database.User.c_str(), m_settings.Database.Password.c_str(),
		m_settings.Database.Database.c_str()))
	{
		Log::write(LOG_ERROR, "Connection a Mysql Impossible: %s\n", m_dbc.getError());

		return false;
	}

	m_database.init(&m_dbc);
	Log::write(LOG_SUCCESS, "Connecter a la BDD");

	//init ISC
	if (!m_isc.init(&m_net))
	{
		Log::write(LOG_ERROR, "ISC ne peu être lancer");

		return false;
	}

	//create acceptor on port 23000
	m_acceptor = m_net.createAcceptor(m_settings.Game.Port);

	if (!m_acceptor)
	{
		Log::write(LOG_ERROR, "Game port %u could not be used", m_settings.Game.Port);

		return false;
	}

	return true;
}

bool ILoginServer::_main()
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
		ILoginPlayer *t_player = _createPlayer(m_acceptor->popClient());

		Log::write(LOG_GAME, "Joueur connecter");

		//send greeting
		t_player->getClient()->send(IPacketCreator::greeting(t_player->getId()));
	}

	//handle new data
	FOR_EACH (m_players, i)
	{
		//player disconnected
		if (!m_players[i]->getClient()->isConnected())
		{
			Log::write(LOG_GAME, "Joueur déconecter");

			if (m_players[i]->getAccount())
			{
				m_players[i]->getAccount()->setOnline(false);
			}

			delete m_players[i];
			m_players.erase(i);
		}

		//new packets
		else if (m_players[i]->getClient()->isNew())
		{
			while (_handlePacket(m_players[i]));

			m_players[i]->getClient()->incoming().clear();
		}
	}

	ITimed::updateAll();

	return true;
}

void ILoginServer::_setTitle()
{
	char t_buffer[256];

	sprintf(t_buffer, "%s %s", LOGIN_PROGRAM_NAME, blackorion_getVersionStr());

	CConsole::setTitle(t_buffer);
}

bool ILoginServer::_handlePacket(ILoginPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	s32 t_command = IPacketReader::readLoginHeader(t_packet);

	//handle the command
	switch (t_command)
	{

	case 0xfc:
		return _cmdHandler_login(_player);

	case 0xfe:
		return _cmdHandler__erreur(_player);

	case 0x16:
		return _cmdHandler_loginRetry(_player);

	case 0x14:
		return false;

	case 0xffffffff: // Time Out
		return _cmdHandler_unknown_1(_player);

	case 0:
		Log::write(LOG_WARNING, "Packet endommagée recu");
		return false;

	default:
		Log::write(LOG_DEBUG, "Packet Inconnu ");

#ifdef SDEBUG
		sprintf(m_buffer, "logs/_inconnue_%x.txt", t_command);
		t_packet.saveFormatted(m_buffer);
#endif

		return false;
	}

	return !t_packet.end();
}

bool ILoginServer::_cmdHandler_login(ILoginPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char t_ccd     [T_BUF_SIZE];
	static char t_checksum[T_BUF_SIZE];
	static char t_name    [T_BUF_SIZE];
	static char t_password[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//client compile date
	if (!t_packet.getString(t_ccd, T_BUF_SIZE))
		return false;

	//flyff.a checksum
	if (!t_packet.getString(t_checksum, T_BUF_SIZE))
		return false;

	//account name
	if (!t_packet.getString(t_name, T_BUF_SIZE))
		return false;

	//password
	if (!t_packet.getString(t_password, T_BUF_SIZE))
		return false;


	//is the server full?
	if (m_players.size() >= m_settings.Game.MaxPlayers)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_CAPACITY));
		return false;
	}

	//check account and pw
	AccountPtr t_account = m_database.getAccount(t_name);

	//wrong id
	if (!t_account)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_WRONG_ID));

		//register per login
		if (m_settings.Game.LoginRegister)
		{
			bool t_creationSuccess = m_database.createAccount(t_name, t_password, IAccount::ACC_PLAYER);

			if (t_creationSuccess)
			{
				Log::write(LOG_GAME, "Compte \"%s\" Cree par connection!", t_name);
			}
			else
			{
				Log::write(LOG_WARNING, "Impossible de crée le compte");
			}
		}
	}

	//wrong access level
	else if (t_account->getAccessLevel() < m_reqAccessLevel)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_UNAVAILABLE));
	}

	//wrong pw
	else if (xstricmp(t_account->getPassword(), t_password) != 0)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_WRONG_PASSWORD));
	}

	//already connected
	else if (t_account->isOnline())
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_ALREADY_CONNECTED));
	}

	//banned
	else if (t_account->getBanTime() >= CTime::seconds())
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_BANNED));
	}

	//client compile date
	else if (!m_settings.Game.ClientCompileDate.empty() &&
		m_settings.Game.ClientCompileDate != t_ccd)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_OLD_CLIENT));

		Log::write(LOG_GAME, "Wrong CCD: '%s', [%s], '%s'", t_account->getName(), t_ccd, t_checksum);
	}

	//flyff.a checksum
	else if (!m_settings.Game.Checksum.empty() &&
		m_settings.Game.Checksum != t_checksum)
	{
		_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_OLD_CLIENT));

		Log::write(LOG_GAME, "Wrong Checksum: '%s', '%s', [%s]", t_account->getName(), t_ccd, t_checksum);
	}

	//correct
	else
	{
		t_account->updateLastLogin();
		t_account->setOnline(true);
		_player->setAccount(t_account);
		m_database.saveAccount(t_account);

		_player->getClient()->send(IPacketCreator::serverList(_player, m_isc.getServerList()));
		Log::write(LOG_GAME, "Login: Utilisateur '%s', date '%s', mdp '%s'", t_account->getName(), t_ccd, t_password);
	}

	return false;
}

bool ILoginServer::_cmdHandler__erreur(ILoginPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.destroy ();

	return false;
}



bool ILoginServer::_cmdHandler_loginRetry(ILoginPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char t_buffer_1[T_BUF_SIZE];
	static char t_buffer_2[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//account name
	if (!t_packet.getString(t_buffer_1, T_BUF_SIZE))
		return false;

	//password
	if (!t_packet.getString(t_buffer_2, T_BUF_SIZE))
		return false;

	//check account and pw
	AccountPtr t_account = m_database.getAccount(t_buffer_1);

	//can login
	if (t_account &&
		xstricmp(t_account->getPassword(), t_buffer_2) == 0 &&
		t_account->getBanTime() >= CTime::seconds())
	{
		if (!t_account->isOnline())
		{
			t_account->updateLastLogin();
			t_account->setOnline(true);
			_player->setAccount(t_account);
			m_database.saveAccount(t_account);

			_player->getClient()->send(IPacketCreator::serverList(_player, m_isc.getServerList()));
		}
		else
		{
			_player->getClient()->send(IPacketCreator::loginError(IPacketCreator::ERR_ALREADY_CONNECTED));
		}
	}

	return !t_packet.end();
}


bool ILoginServer::_cmdHandler_unknown_1(ILoginPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getInt();

	return false;
}
