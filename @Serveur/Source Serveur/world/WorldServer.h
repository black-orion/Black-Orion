#ifndef WORLDSERVER_H
#define WORLDSERVER_H


#include "WorldMain.h"
#include "WorldSettings.h"
#include "WorldISC.h"
#include "ChatHandler.h"
#include "WorldDataManager.h"
#include "PacketReceiver.h"
#include "MailManager.h"
#include "../shared/AccountManager.h"
#include "../shared/CharacterManager.h"
#include "../shared/ItemPackManager.h"
#include "../shared/DatabaseConnection.h"
#include "../shared/Timed.h"


class IWorldObject;
class IWorldPlayer;
class IWorld;
class IPlayerObject;
class ICreature;
class IParty;


class IWorldServer : public ITimed
{
public:

	IWorldServer();

	~IWorldServer();

	void start();

	IWorld *getWorld(ID _id);

	IWorld *getWorld(const char *_title);

	E_WEATHER getWeather() const;

	bool isWeatherFixed() const;

	IAccountManager *getAccountManager();

	ICharacterManager *getCharacterManager();

	IItemPackManager *getItemPackManager();

	IMailManager *getMailManager();

	IWorldDataManager *getDataManager();

	IWorldSettings *getSettings();

	IChatHandler *getChatHandler();

	IPacketReceiver *getPacketReceiver();

	bool sendToAllPlayers(const CByteArray &_packet);

	void enterWorld(IWorldPlayer *_player);

	u32 getTotalNpcCount() const;

	u32 getTotalMobCount() const;

	u32 getTotalDropCount() const;

	IWorldPlayer *getPlayer(const char *_name);

	IWorldPlayer *getPlayerByObjectId(ID _id);

	IWorldPlayer *getPlayerByCharacterId(ID _id);

	void removePlayer(IWorldPlayer *_player);

	u32 getPartyCount() const;

	PartyPtr &getParty(u32 _num);

	PartyPtr &createParty(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_member);

	void removeParty(const PartyPtr &_party);

	void setWeather(E_WEATHER _weather);

	void setWeatherFixed(bool _fixed);

	void update();

private:

	//Friend class
	friend class IChatHandler;

	//Settings
	IWorldSettings m_settings;

	//Networking
	CNetwork m_net;

	CNetAcceptor *m_acceptor;

	//Data
	IWorldDataManager m_data;

	//Players
	CArray<IWorldPlayer*> m_players;

	CArray<PartyPtr> m_parties;

	IChatHandler m_chat;

	IPacketReceiver m_packetReceiver;

	//World
	CArray<IWorld*> m_worlds;

	E_WEATHER m_weather;

	TimeMs m_nextWeatherChange;

	bool m_weatherFixed;

	//ISC
	IWorldISC m_isc;

	friend class IWorldISC;

	//Database
	IDatabaseConnection m_dbc_0;

	IDatabaseConnection m_dbc_1;

	IAccountManager m_accountMngr;

	ICharacterManager m_charMngr;

	IItemPackManager m_itemMngr;

	IMailManager m_mailMngr;

	TimeMs m_nextSaveTime;


	//:: FUNCTIONS ::

	//players:
	IWorldPlayer *_getPlayer(s32 _id);

	IWorldPlayer *_createPlayer(CNetClient *_client);

	//world:
	bool _createWorlds();

	//loads config, database, inits network, etc
	bool _load();

	//the main loop
	bool _main();

	void _saveAll();

	//sets the title to "blackorion World {version}"
	void _setTitle();

	ID _generatePlayerId();

	ID _generatePartyId();

};


#endif //WORLDSERVER_H
