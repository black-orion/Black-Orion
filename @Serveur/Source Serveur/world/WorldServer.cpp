#include <time.h>    
#include "WorldServer.h"
#include "WorldPlayer.h"
#include "World.h"
#include "PlayerObject.h"
#include "SpawnData.h"
#include "WorldField.h"
#include "MobObject.h"
#include "DropObject.h"
#include "NpcData.h"
#include "NpcObject.h"
#include "NpcDialogEnv.h"
#include "CommandScriptEnv.h"
#include "Party.h"
#include "../shared/Account.h"
#include "../shared/Character.h"
#include "../shared/PacketCreator.h"
#include "../shared/PacketReader.h"
#include "../shared/Log.h"
#include "../shared/ItemData.h"
   

IWorldServer::IWorldServer()
	: m_acceptor(0)
	, m_accountMngr(&m_dbc_0)
	, m_charMngr(0, &m_accountMngr, &m_itemMngr)
	, m_itemMngr(0, m_data.getItemManager())
	, m_mailMngr(0, &m_charMngr, &m_itemMngr)
	, m_nextSaveTime(0)
	, m_isc(&m_settings.ISC, this)
	, m_chat()
	, m_packetReceiver(this)
	, m_data(&m_settings.Data)
	, m_weather(WEATHER_RAIN) 
	, m_nextWeatherChange(0)
	, m_weatherFixed(false)
{
}

IWorldServer::~IWorldServer()
{
	_saveAll();

	FOR_EACH (m_players, i)
	{
		delete m_players[i];
	}
	m_players.clear();

	FOR_EACH (m_worlds, i)
	{
		delete m_worlds[i];
	}
	m_worlds.clear();

	m_parties.clear();

	m_net.shutdown();

	m_mailMngr.clear();
	m_itemMngr.clear();
	m_charMngr.clear();
	m_accountMngr.clear();
}

//#include <fstream>

void IWorldServer::start()
{
	if (!_load())
	{
		CConsole::wait();
		return;
	}



	while (_main());
}

IWorld *IWorldServer::getWorld(ID _id)
{
	FOR_EACH (m_worlds, i)
	{
		if (m_worlds[i]->getId() == _id)
		{
			return m_worlds[i];
		}
	}

	return 0;
}

IWorld *IWorldServer::getWorld(const char *_title)
{
	FDASSERT(_title);

	FOR_EACH (m_worlds, i)
	{
		if (xstricmp(m_worlds[i]->getName(), _title) == 0)
		{
			return m_worlds[i];
		}
	}

	return 0;
}

E_WEATHER IWorldServer::getWeather() const
{
	return m_weather;
}

bool IWorldServer::isWeatherFixed() const
{
	return m_weatherFixed;
}

IAccountManager *IWorldServer::getAccountManager()
{
	return &m_accountMngr;
}

ICharacterManager *IWorldServer::getCharacterManager()
{
	return &m_charMngr;
}

IItemPackManager *IWorldServer::getItemPackManager()
{
	return &m_itemMngr;
}

IMailManager *IWorldServer::getMailManager()
{
	return &m_mailMngr;
}

IWorldDataManager *IWorldServer::getDataManager()
{
	return &m_data;
}

IWorldSettings *IWorldServer::getSettings()
{
	return &m_settings;
}

IChatHandler *IWorldServer::getChatHandler()
{
	return &m_chat;
}

IPacketReceiver *IWorldServer::getPacketReceiver()
{
	return &m_packetReceiver;
}

bool IWorldServer::sendToAllPlayers(const CByteArray &_packet)
{
	FOR_EACH (m_players, i)
	{
		if (!m_players[i]->getClient()->send(_packet))
			return false;
	}

	return true;
}

void IWorldServer::enterWorld(IWorldPlayer *_player)
{
	FDASSERT(_player);

	IWorld *t_world = getWorld(_player->getCharacter()->getWorldId());

	if (!t_world)
	{
		t_world = getWorld(1);

		if (!t_world &&
			!m_worlds.empty())
		{
			t_world = m_worlds[0];
		}
	}

	if (t_world)
	{
		t_world->addPlayer(_player);
	}
}

u32 IWorldServer::getTotalNpcCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_worlds, i)
	{
		r_count += m_worlds[i]->getNpcCount();
	}

	return r_count;
}

u32 IWorldServer::getTotalMobCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_worlds, i)
	{
		r_count += m_worlds[i]->getMobCount();
	}

	return r_count;
}

u32 IWorldServer::getTotalDropCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_worlds, i)
	{
		r_count += m_worlds[i]->getDropCount();
	}

	return r_count;
}

IWorldPlayer *IWorldServer::getPlayer(const char *_name)
{
	FDASSERT(_name);

	FOR_EACH (m_players, i)
	{
		if (strcmp(m_players[i]->getCharacter()->getName(), _name) == 0)
		{
			return m_players[i];
		}
	}

	return 0;
}

IWorldPlayer *IWorldServer::getPlayerByObjectId(ID _id)
{
	FOR_EACH (m_players, i)
	{
		if (m_players[i]->getObject() &&
			m_players[i]->getObject()->getId() == _id)
		{
			return m_players[i];
		}
	}

	return 0;
}

IWorldPlayer *IWorldServer::getPlayerByCharacterId(ID _id)
{
	FOR_EACH (m_players, i)
	{
		if (m_players[i]->getCharacter() &&
			m_players[i]->getCharacter()->getId() == _id)
		{
			return m_players[i];
		}
	}

	return 0;
}

void IWorldServer::removePlayer(IWorldPlayer *_player)
{
	FDASSERT(_player);

	//save the character
	if (_player->getObject() &&
		_player->getCharacter())
	{
		_player->getCharacter()->setOnline(false);

		_player->getObject()->updateCharacter();

		//save character
		if (!m_charMngr.saveCharacter_W(_player->getCharacter()) ||
			!m_charMngr.saveCharacter_onlineStatus_W(_player->getCharacter()))
		{
			Log::write(LOG_ERROR, "Could not save the character \"%s\"!",
				_player->getCharacter()->getName());
		}

		//save inventory
		if (!m_itemMngr.saveItems_W(_player->getObject()))
		{
			Log::write(LOG_ERROR, "Could not save the character \"%s\"'s items!",
				_player->getCharacter()->getName());
		}
	}

	delete _player;
	m_players.erase_vfast(_player);
}

u32 IWorldServer::getPartyCount() const
{
	return m_parties.size();
}

PartyPtr &IWorldServer::getParty(u32 _num)
{
	FDASSERT(_num < getPartyCount());

	return m_parties[_num];
}

PartyPtr &IWorldServer::createParty(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_member)
{
	FDASSERT(_leader);
	FDASSERT(_member);
	FDASSERT(_leader != _member);

	m_parties.push_back(PartyPtr(new IParty(_generatePartyId())));
	m_parties.last()->start(_leader, _member);

	return m_parties.last();
}

void IWorldServer::removeParty(const PartyPtr &_party)
{
	FDASSERT(_party);

	_party->disband();

	u32 t_index = 0;
	if (m_parties.find(t_index, _party))
	{
		m_parties[t_index].reset();
		m_parties.erase_fast(t_index);
		return;
	}

	FDASSERT(false);
}

void IWorldServer::setWeather(E_WEATHER _weather)
{
	FDASSERT(weather(_weather) == _weather);

	m_weather = _weather;

	if (!m_players.empty())
	{
		sendToAllPlayers(IPacketCreator::weatherAuto(m_weather));
	}
}

void IWorldServer::setWeatherFixed(bool _fixed)
{
	m_weatherFixed = _fixed;
}

void IWorldServer::update()
{
	//new connections
	while (m_acceptor->isNew())
	{
		IWorldPlayer *t_player = _createPlayer(m_acceptor->popClient());

		Log::write(LOG_DEBUG, "Nouveau Joueur");

		//send greeting
		t_player->getClient()->send(IPacketCreator::greeting(t_player->getId()));
	}

	//incoming data
	FOR_EACH (m_players, i)
	{
		//player disconnected
		if (!m_players[i]->getClient()->isConnected())
		{
			Log::write(LOG_GAME, "Joueur Deconnecter");

			removePlayer(m_players[i]);

			if (i)
				--i;
		}

		//new packets
		else if (!m_players[i]->getClient()->incoming().empty())
		{
			while (m_packetReceiver.handlePacket(m_players[i]));

			m_players[i]->getClient()->incoming().clear();
		}
	}

	//weather control
	if (!m_weatherFixed &&
		m_settings.Game.WeatherType != WEATHER_NORMAL &&
		_time() >= m_nextWeatherChange)
	{
		if (m_weather == WEATHER_NORMAL)
		{
			setWeather(m_settings.Game.WeatherType);
		}
		else
		{
			setWeather(WEATHER_NORMAL);
		}

		m_nextWeatherChange =
			_time() + random(m_settings.Game.WeatherRainTime, 2 * m_settings.Game.WeatherRainTime);
	}
}

IWorldPlayer *IWorldServer::_getPlayer(s32 _id)
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

IWorldPlayer *IWorldServer::_createPlayer(CNetClient *_client)
{
	IWorldPlayer *r_newPlayer = new IWorldPlayer(_generatePlayerId(), _client);

	m_players.push_back(r_newPlayer);

	return r_newPlayer;
}

bool IWorldServer::_createWorlds()
{
	//read the world file
	CFileReader t_file;

	if (t_file.open(m_settings.Data.WorldFileName.c_str(), true))
	{
		t_file.setOption(CFileReader::opt_comments, true);

		char t_title[256];
		ID t_id = 0;
		u32 t_width = 0;
		u32 t_height = 0;
		u32 t_fieldSize = 0;

		while (!t_file.end())
		{
			if (!t_file.readNext(t_title, sizeof(t_title)))
				break;

			t_id = t_file.readInt();
			t_width = t_file.readUInt();
			t_height = t_file.readUInt();
			t_fieldSize = t_file.readUInt();

			if (getWorld(t_id) ||
				getWorld(t_title))
			{
				Log::write(LOG_ERROR, "World %d (%s) already defined!", t_id, t_title);
				continue;
			}

			m_worlds.push_back(new IWorld(t_id, t_title, t_width, t_height, t_fieldSize, &m_data, this));
		}

		Log::write(LOG_SUCCESS, "Created %u worlds", m_worlds.size());
	}
	else
	{
		Log::write(LOG_ERROR, "Could not load world definition file \"%s\"!", t_file.getFileName());
		return false;
	}

	//create all the spawns
	for (u32 i = 0; i < m_data.getSpawnCount(); ++i)
	{
		IWorld *t_world = getWorld(m_data.getSpawnByNumber(i)->getWorldId());

		if (t_world)
		{
			t_world->addSpawn(m_data.getSpawnByNumber(i));
		}

		//unknown world id
		else
		{
			Log::write(LOG_WARNING, "World '%d' in spawn file \"%s\" does not exist",
				m_data.getSpawnByNumber(i)->getWorldId(), m_data.getSpawnByNumber(i)->getFileName());
		}
	}

	//spawn npcs
	for (u32 i = 0; i < m_data.getNpcCount(); ++i)
	{
		IWorld *t_world = getWorld(m_data.getNpcByNumber(i)->getWorldId());

		if (t_world)
		{
			t_world->createNpcObject(m_data.getNpcByNumber(i));
		}

		//unknown world id
		else
		{
			Log::write(LOG_WARNING, "World '%d' in npc file \"%s\" does not exist",
				m_data.getNpcByNumber(i)->getWorldId(), m_data.getNpcByNumber(i)->getFileName());
		}
	}

	return true;
}

bool IWorldServer::_load()
{
	//console title
	_setTitle();

	CConsole::initCloseHandler();

	time_t now;                                                                  
	char *_date;  
	time(&now);
	_date = ctime(&now);

	Log::write(LOG_INFO, "Bienvenus dans Black-Orion");
	Log::write(LOG_INFO, "Merci de Votre Confiance");
	Log::write(LOG_INFO, "%s ", _date);
	//load configuration file
	if (!m_settings.load(WORLD_SETTINGS_FILE_NAME))
	{
		Log::write(LOG_ERROR, "Setting file \"%s\" could not be loaded!", WORLD_SETTINGS_FILE_NAME);
	}

	IWorldObject::setGameSettings(&m_settings.Game);
	IMobObject::setRemoveDelay(m_settings.Game.MobRemoveTime);
	IDropObject::setRemoveDelay(m_settings.Game.ItemRemoveTime);

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

	//load data
	if (!m_data.load())
	{
		return false;
	}

	IMobObject::PenyaDrop t_penyaDrops[4] =
	{
		{m_settings.Game.PenyaDropLimit_0, m_data.getItemManager()->getItemById(12)},
		{m_settings.Game.PenyaDropLimit_1, m_data.getItemManager()->getItemById(13)},
		{m_settings.Game.PenyaDropLimit_2, m_data.getItemManager()->getItemById(14)},
		{m_settings.Game.PenyaDropLimit_3, m_data.getItemManager()->getItemById(15)}
	};

	if (!t_penyaDrops[0].Item ||
		!t_penyaDrops[1].Item ||
		!t_penyaDrops[2].Item ||
		!t_penyaDrops[3].Item)
	{
		Log::write(LOG_ERROR, "Some of the penya drop items 12, 13, 14 and 15 are not defined!");
		return false;
	}

	IMobObject::setPenyaDropItems(t_penyaDrops);

	//NPC dialogs
	if (!INpcDialogEnv::instance()->init(&m_settings))
	{
		Log::write(LOG_ERROR, "Could not init the NPC dialog environment!");
		return false;
	}

	//init chat and command scripts
	if (!m_chat.init(this) ||
		!ICommandScriptEnv::instance()->loadScripts(&m_chat, &m_settings))
	{
		return false;
	}

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

	Log::write(LOG_SUCCESS, "Connected to the database");

	//init character/item manager
	m_charMngr.setDbc(t_pdbc);
	m_itemMngr.setDbc(t_pdbc);
	m_mailMngr.setDbc(t_pdbc);

	//init ISC
	if (!m_isc.init(&m_net))
	{
		Log::write(LOG_ERROR, "ISC could not be initialized");

		return false;
	}

	//create acceptor on port 15400
	m_acceptor = m_net.createAcceptor(m_settings.Game.Port);

	if (!m_acceptor)
	{
		Log::write(LOG_ERROR, "Le Port %u ne peu pas etre utliser", m_settings.Game.Port);

		return false;
	}

	//init worlds
	if (!_createWorlds())
	{
		Log::write(LOG_CRITICAL, "Error on creating the game worlds");

		return false;
	}

	return true;
}

bool IWorldServer::_main()
{
	//check if the console is closed
	if (CConsole::isClosed())
	{
		return false;
	}

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

	ITimed::updateAll();

	return true;
}

void IWorldServer::_saveAll()
{
	//accounts
	if (m_accountMngr.getAccountNumber())
	{
		Log::write(LOG_GAME, "Sauvgarde de %u comptes dans la base de donnée...", m_accountMngr.getAccountNumber());

		if (m_accountMngr.save_W())
		{
			Log::write(LOG_SUCCESS, "OK.");
		}
		else
		{
			Log::write(LOG_ERROR, "Erreur!");
		}
	}

	//chars
	if (m_charMngr.getCharacterNumber())
	{
		//update chars to save them
		FOR_EACH (m_players, i)
		{
			if (m_players[i]->getObject())
			{
				m_players[i]->getObject()->updateCharacter();
			}
		}

		Log::write(LOG_GAME, "Saving %u characters to the database...", m_charMngr.getCharacterNumber());

		if (m_charMngr.save_W())
		{
			Log::write(LOG_SUCCESS, "Done.");
		}
		else
		{
			Log::write(LOG_ERROR, "Error!");
		}
	}

	//items
	if (m_itemMngr.getItemPackNumber())
	{
		Log::write(LOG_GAME, "Saving %u items to the database...", m_itemMngr.getItemPackNumber());

		if (m_itemMngr.save_W())
		{
			Log::write(LOG_SUCCESS, "Done.");
		}
		else
		{
			Log::write(LOG_ERROR, "Error!");
		}
	}
}

void IWorldServer::_setTitle()
{
	char t_buffer[256];

	sprintf(t_buffer, "%s %s", WORLD_PROGRAM_NAME, blackorion_getVersionStr());

	CConsole::setTitle(t_buffer);
}

ID IWorldServer::_generatePlayerId()
{
	static ID ms_nextPlayerId = 0;

	++ms_nextPlayerId;

	return ms_nextPlayerId;
}

ID IWorldServer::_generatePartyId()
{
	static ID ms_nextPartyId = 0;

	++ms_nextPartyId;

	return ms_nextPartyId;
}
