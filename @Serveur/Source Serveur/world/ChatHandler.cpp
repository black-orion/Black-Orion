#include "ChatHandler.h"
#include "WorldPlayer.h"
#include "WorldServer.h"
#include "WorldField.h"
#include "PlayerObject.h"
#include "DropObject.h"
#include "MobObject.h"
#include "World.h"
#include "SpawnData.h"
#include "CommandScriptEnv.h"
#include "../shared/PacketCreator.h"
#include "../shared/Log.h"
#include "../shared/Character.h"
#include "../shared/Account.h"


IChatHandler::IChatHandler()
	: m_pserver(0)
{
}

IChatHandler::~IChatHandler()
{
}

bool IChatHandler::init(IWorldServer *_server)
{
	FDASSERT(_server);

	m_pserver = _server;

	//init commands
	IWorldSettings::CommandSettings &t_settings = m_pserver->getSettings()->Commands;

#define NEW_COMMAND(name) m_cmdHandles.push_back(CommandHandle(&t_settings.name, &IChatHandler::_sCmd_##name))

	NEW_COMMAND(Info);
	NEW_COMMAND(Coin);
	NEW_COMMAND(Dice);
	NEW_COMMAND(Penya);
	NEW_COMMAND(Level);
	NEW_COMMAND(AccessLevel);
	NEW_COMMAND(ClearInv);
	NEW_COMMAND(DropInv);
	NEW_COMMAND(Shout);
	NEW_COMMAND(Item);
	NEW_COMMAND(Stat);
	NEW_COMMAND(Notice);
	NEW_COMMAND(Pos);
	NEW_COMMAND(Name);
	NEW_COMMAND(Exp);
	NEW_COMMAND(AddExp);
	NEW_COMMAND(Kill);
	NEW_COMMAND(Job);
	NEW_COMMAND(Points);
	NEW_COMMAND(GetPoints);
	NEW_COMMAND(PlayerInfo);
	NEW_COMMAND(Immortal);
	NEW_COMMAND(OneHit);
	NEW_COMMAND(God);
	NEW_COMMAND(SetAccessLevel);
	NEW_COMMAND(Mob);
	NEW_COMMAND(CreateSpawn);
	NEW_COMMAND(CreateItemList);
	NEW_COMMAND(Place);
	NEW_COMMAND(Ban);
	NEW_COMMAND(PvpPoints);
	NEW_COMMAND(PkPoints);
	NEW_COMMAND(Disposition);
	NEW_COMMAND(Weather);
	NEW_COMMAND(Revive);

#undef NEW_COMMAND

	return true;
}

void IChatHandler::chat(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(m_pserver);
	FDASSERT(_player);
	FDASSERT(_message);

	if (!*_message)
		return;

	switch (*_message++)
	{
	case '/': //Flyff commands
		{
			sscanf(_message, "%s%n", m_command, &m_command_size);
			_message += m_command_size;

			//Shout
			if (xstricmp("s", m_command) == 0)
			{
				_fCmd_Shout(_player, _message);
			}

			//Say
			else if (xstricmp("say", m_command) == 0)
			{
				_fCmd_Say(_player, _message);
			}

			//Whisper
			else if (xstricmp("w", m_command) == 0)
			{
				_fCmd_Whisper(_player, _message);
			}

			//PartyInvite
			else if (xstricmp("partyinvite", m_command) == 0)
			{
				_fCmd_PartyInvite(_player, _message);
			}

			//Teleport
			else if (xstricmp("teleport", m_command) == 0)
			{
				_fCmd_Teleport(_player, _message);
			}

			return;
		}

	case '#': //blackorion commands
		{
			sscanf(_message, "%s%n", m_command, &m_command_size);
			_message += m_command_size;

			bool t_usable = true;

			for (u32 i = 0; i < m_cmdHandles.size(); ++i)
			{
				if (_command(*m_cmdHandles[i].Command, m_command, _player, t_usable) &&
					t_usable)
				{
					(this->*m_cmdHandles[i].Function)(_player, _message);
					return;
				}
			}

			_player->greenText("Unknown command");

			/*IWorldCommandSettings &t_sett = m_pserver->m_settings.Commands;

			bool t_canUse = false;

			//Info
			if (_command(t_sett.Info, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_info(_player, _message);
				}
			}

			//Coin
			else if (_command(t_sett.Coin, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_coin(_player, _message);
				}
			}

			//Dice
			else if (_command(t_sett.Dice, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_dice(_player, _message);
				}
			}

			//Penya
			else if (_command(t_sett.Penya, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_penya(_player, _message);
				}
			}

			//Level
			else if (_command(t_sett.Level, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_level(_player, _message);
				}
			}

			//AccessLevel
			else if (_command(t_sett.AccessLevel, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_accessLevel(_player, _message);
				}
			}

			//ClearInv
			else if (_command(t_sett.ClearInv, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_clearInv(_player, _message);
				}
			}

			//DropInv
			else if (_command(t_sett.DropInv, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_dropInv(_player, _message);
				}
			}

			//Shout
			else if (_command(t_sett.Shout, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_shout(_player, _message);
				}
			}

			//Item
			else if (_command(t_sett.Item, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_item(_player, _message);
				}
			}

			//Stat
			else if (_command(t_sett.Stat, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_stat(_player, _message);
				}
			}

			//Notice
			else if (_command(t_sett.Notice, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_notice(_player, _message);
				}
			}

			//Pos
			else if (_command(t_sett.Pos, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_pos(_player, _message);
				}
			}

			//Name
			else if (_command(t_sett.Name, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_name(_player, _message);
				}
			}

			//Exp
			else if (_command(t_sett.Exp, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_exp(_player, _message);
				}
			}

			//AddExp
			else if (_command(t_sett.AddExp, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_addExp(_player, _message);
				}
			}

			//Kill
			else if (_command(t_sett.Kill, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_kill(_player, _message);
				}
			}

			//Job
			else if (_command(t_sett.Job, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_job(_player, _message);
				}
			}

			//Points
			else if (_command(t_sett.Points, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_points(_player, _message);
				}
			}

			//GetPoints
			else if (_command(t_sett.GetPoints, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_getPoints(_player, _message);
				}
			}

			//PlayerInfo
			else if (_command(t_sett.PlayerInfo, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_playerInfo(_player, _message);
				}
			}

			//Immortal
			else if (_command(t_sett.Immortal, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_immortal(_player, _message);
				}
			}

			//OneHit
			else if (_command(t_sett.OneHit, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_oneHit(_player, _message);
				}
			}

			//God
			else if (_command(t_sett.God, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_god(_player, _message);
				}
			}

			//SetAccessLevel
			else if (_command(t_sett.SetAccessLevel, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_setAccessLevel(_player, _message);
				}
			}

			//Mob
			else if (_command(t_sett.Mob, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_mob(_player, _message);
				}
			}

			//CreateSpawn
			else if (_command(t_sett.CreateSpawn, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_createSpawn(_player, _message);
				}
			}

			//CreateItemList
			else if (_command(t_sett.CreateItemList, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_createItemList(_player, _message);
				}
			}

			//Place
			else if (_command(t_sett.Place, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_place(_player, _message);
				}
			}

			//Ban
			else if (_command(t_sett.Ban, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_ban(_player, _message);
				}
			}

			//PvpPoints
			else if (_command(t_sett.PvpPoints, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_pvpPoints(_player, _message);
				}
			}

			//PkPoints
			else if (_command(t_sett.PkPoints, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_pkPoints(_player, _message);
				}
			}

			//Disposition
			else if (_command(t_sett.Disposition, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_disposition(_player, _message);
				}
			}

			//Weather
			else if (_command(t_sett.Weather, m_command, _player, t_canUse))
			{
				if (t_canUse)
				{
					_sCmd_weather(_player, _message);
				}
			}

			else
			{
				_player->greenText("Unknown command"));
			}*/

			return;
		}

	case '.': //Custom commands
		{
			ICommandScriptEnv::instance()->command(_player->getObject(), _message);
			return;
		}
	};

	//... normal chat
	*_message--;

	_player->getObject()->getWorld()->sendToLocalArea(_player->getObject(),
		IPacketCreator::chat(_player->getObject()->getId(), _message));
}

bool IChatHandler::shout(IWorldPlayer *_player, const char *_msg)
{
	FDASSERT(_player);
	FDASSERT(_player->getObject());
	FDASSERT(_player->getObject()->getWorld());
	FDASSERT(_msg);

	if (_player->getCharacter()->hasFullShout())
	{
		return m_pserver->sendToAllPlayers(IPacketCreator::shout(_player->getObject()->getId(),
			_player->getCharacter()->getName(), _msg, 0xff99cc));
	}
	else
	{
		return _player->getObject()->getWorld()->sendToLocalArea(_player->getObject(),
			IPacketCreator::shout(_player->getObject()->getId(),
			_player->getCharacter()->getName(), _msg, 0xff99cc));
	}
}

bool IChatHandler::notice(IWorldPlayer *_player, const char *_msg)
{
	FDASSERT(_player);
	FDASSERT(_player->getObject());
	FDASSERT(_player->getObject()->getWorld());
	FDASSERT(_msg);

	return m_pserver->sendToAllPlayers(IPacketCreator::notice(_msg));
}

IWorldSettings *IChatHandler::_getSettings()
{
	FDASSERT(m_pserver);
	FDASSERT(m_pserver->getSettings());

	return m_pserver->getSettings();
}

IWorldDataManager *IChatHandler::_getWorldDataMngr()
{
	FDASSERT(m_pserver);
	FDASSERT(m_pserver->getDataManager());

	return m_pserver->getDataManager();
}

bool IChatHandler::_command(IWorldCommand &_cmd, const char *_str, IWorldPlayer *_player, bool &_out_usable)
{
	FDASSERT(_str);
	FDASSERT(_player);
	FDASSERT(_player->getAccount());

	bool t_found = false;

	for (u32 i = 0; i < _cmd.Strings.size(); ++i)
	{
		if (_cmd.Strings[i] == _str)
		{
			t_found = true;
			break;
		}
	}

	if (t_found)
	{
		if (_player->getAccount()->getAccessLevel() >= _cmd.Access)
		{
			_out_usable = true;
		}
		else
		{
			_out_usable = false;

			_player->greenText("Acces Superieur requis");
		}

		return true;
	}

	return false;
}

void IChatHandler::_fCmd_Shout(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	if (*_message == ' ')
		++_message;

	//send
	shout(_player, _message);
}

void IChatHandler::_fCmd_Say(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	CFileReader t_message;
	t_message.setContent(_message);

	//read the name
	t_message.readString(m_buffer, BUF_SIZE);

	//you cannot pm yourself
	if (strcmp(_player->getCharacter()->getName(), m_buffer) == 0)
	{
		return;
	}

	//get the message
	_message = trim_front(t_message.getContentRest());

	IWorldPlayer *t_player = m_pserver->getPlayer(m_buffer);

	if (t_player)
	{
		//send to the sender
		_player->getClient()->send(IPacketCreator::privateMessage(_player, t_player, _message));

		//and to the receiver
		t_player->getClient()->send(IPacketCreator::privateMessage(_player, 0, _message));
	}
	else
	{
		_player->greenText("Not connected");
	}
}

void IChatHandler::_fCmd_Whisper(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);
}

void IChatHandler::_fCmd_PartyInvite(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	sscanf(_message, "%s", m_buffer);

	IWorldPlayer *t_player = m_pserver->getPlayer(m_buffer);

	if (t_player == 0 ||
		t_player->getObject() == 0)
	{
		//_player->getClient()->send(IPacketCreator::gameInfo(_player->getObject(), ..));
		return;
	}

	_player->getObject()->partyInvite(t_player->getObject());
}

void IChatHandler::_fCmd_Teleport(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	CPoint t_pos;
	ID t_world = 0;

	sscanf(_message, "%d %f %f", &t_world, &t_pos.X, &t_pos.Z);

	IWorld *t_newWorld = m_pserver->getWorld(t_world);

	if (t_newWorld)
	{
		_player->getObject()->teleport(t_pos, t_newWorld);
	}
	else
	{
		_player->greenText("Teleport failed: World doesn't exist.");
	}
}

void IChatHandler::_sCmd_Info(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	sprintf(m_buffer, "{blackorion %s} Players: %u | NPCs: %u | Mobs: %u | Drops: %u",
		blackorion_getVersionStr(), m_pserver->m_players.size(), m_pserver->getTotalNpcCount(),
		m_pserver->getTotalMobCount(), m_pserver->getTotalDropCount());

	_player->greenText(m_buffer);
}

void IChatHandler::_sCmd_Coin(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	_player->greenText((random32() & 1) ? "heads" : "tails");
}

void IChatHandler::_sCmd_Dice(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_faces = 6;

	sscanf(_message, "%d", &t_faces);

	if (t_faces > 1)
	{
		sprintf(m_buffer, "Result: %d", (random32() % t_faces) + 1);

		_player->greenText(m_buffer);
	}
}

void IChatHandler::_sCmd_Penya(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	PENYA t_penya = 0;

	sscanf(_message, "%d", &t_penya);

	_player->getCharacter()->setPenya(t_penya);

	_player->getClient()->send(
		IPacketCreator::updateAttribute(_player->getObject(), DST_GOLD, _player->getCharacter()->getPenya()));
}

void IChatHandler::_sCmd_Level(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	LVL t_level = _player->getCharacter()->getLevel();

	sscanf(_message, "%d", &t_level);

	_player->getObject()->changeLevel(t_level);
}

void IChatHandler::_sCmd_AccessLevel(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_access = _player->getAccount()->getAccessLevel();

	sscanf(_message, "%d", &t_access);

	_player->getObject()->changeAccessLevel(IAccount::accessLevel(t_access));

	sprintf(m_buffer, "Current access level: %d", _player->getAccount()->getAccessLevel());

	_player->greenText(m_buffer);
}

void IChatHandler::_sCmd_ClearInv(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	//...

	_player->greenText("Inventory cleared");
}

void IChatHandler::_sCmd_DropInv(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const CharacterPtr &t_char = _player->getCharacter();

	/*for (s32 i = 0; i < INV_PLACES; ++i)
	{
		if (t_char->getInventory()->getInventoryItem(i))
		{
			_player->getObject()->inventoryDropItem(i);
		}
	}*/

	_player->greenText("Inventory dropped");
}

void IChatHandler::_sCmd_Shout(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	if (*_message == ' ')
		++_message;

	//send
	shout(_player, _message);
}

void IChatHandler::_sCmd_Item(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	ID t_itemId = 0;
	s32 t_count = 1;
	s32 t_upgrade = 0;
	s32 t_ele = 0;
	s32 t_eleUp = 0;

	sscanf(_message, "%d %d %d %d %d", &t_itemId, &t_count, &t_upgrade, &t_ele, &t_eleUp);

	const IItemData *t_data = m_pserver->getDataManager()->getItemManager()->getItemById(t_itemId);

	if (t_data)
	{
		IItemProperties t_itemProp(t_data, Max(t_count, 1), Max(t_upgrade, 0), element(t_ele), Max(t_eleUp, 0));

		if (_player->getObject()->getInventory()->addItem(t_itemProp))
		{
			_player->greenText("Item created.");
		}
		else
		{
			_player->greenText("Error. Not enough space?");
		}
	}
}

void IChatHandler::_sCmd_Stat(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_amount = 0;

	sscanf(_message, "%s %d", m_buffer, &t_amount);

	E_STAT t_stat = DST_NONE;

	if (xstricmp("STR", m_buffer) == 0)
	{
		t_stat = DST_STR;
	}
	else if (xstricmp("STA", m_buffer) == 0)
	{
		t_stat = DST_STA;
	}
	else if (xstricmp("DEX", m_buffer) == 0)
	{
		t_stat = DST_DEX;
	}
	else if (xstricmp("INT", m_buffer) == 0)
	{
		t_stat = DST_INT;
	}
	else
	{
		t_stat = stat(xtoi(m_buffer));
	}

	switch (t_stat)
	{
	case DST_STR:
		_player->getCharacter()->addStr(t_amount);
		break;

	case DST_STA:
		_player->getCharacter()->addSta(t_amount);
		break;

	case DST_DEX:
		_player->getCharacter()->addDex(t_amount);
		break;

	case DST_INT:
		_player->getCharacter()->addInt(t_amount);
		break;

	default:
		_player->greenText("Invalid stat type");
		return;
	}

	_player->getObject()->onBaseStatChanged();

	_player->getObject()->sendToLocalArea(IPacketCreator::statInfos(_player->getObject()));
}

void IChatHandler::_sCmd_Notice(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	if (*_message == ' ')
		++_message;

	//send
	notice(_player, _message);
}

void IChatHandler::_sCmd_Pos(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const CPoint &t_pos = _player->getObject()->getPosition();

	sprintf(m_buffer, "%f %f %f", t_pos.X, t_pos.Y, t_pos.Z);

	_player->greenText(m_buffer);
}

void IChatHandler::_sCmd_Name(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const char *t_name = trim(m_buffer, BUF_SIZE, _message);

	if (t_name[0])
	{
		_player->getCharacter()->setName(t_name);
	}
	else
	{
		_player->greenText("You have to enter a new name");
	}
}

void IChatHandler::_sCmd_Exp(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	EXP t_exp = 0;
	sscanf(_message, "%lld", &t_exp);

	_player->getObject()->changeExp(t_exp);
}

void IChatHandler::_sCmd_AddExp(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	EXP t_exp = 0;
	sscanf(_message, "%lld", &t_exp);

	_player->getObject()->changeExp(_player->getCharacter()->getExp() + t_exp);
}

void IChatHandler::_sCmd_Kill(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const char *t_name = trim(m_buffer, BUF_SIZE, _message);

	PlayerObjectPtr &t_target = _player->getObject()->getWorld()->getPlayerByName(t_name);

	if (t_target)
	{
		if (t_target->getPlayer()->getAccount()->getAccessLevel() <= _player->getAccount()->getAccessLevel())
		{
			t_target->kill(ICreature::DEATH_SPC, _player->getObject());
		}
		else
		{
			_player->greenText("You are not authorized to kill this player");
		}
	}
	else
	{
		_player->greenText("Player not connected");
	}
}

void IChatHandler::_sCmd_Job(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_job = 0;
	sscanf(_message, "%d", &t_job);

	if (t_job == job(t_job))
	{
		_player->getObject()->changeJob(E_JOB(t_job));
	}
	else
	{
		_player->greenText("Invalid job id");
	}
}

void IChatHandler::_sCmd_Points(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const char *t_str = trim(m_buffer, BUF_SIZE, _message);

	if (t_str[0])
	{
		_player->getAccount()->setPoints(xtoi(t_str));
	}
	else
	{
		sprintf(m_buffer, "You have got %d points", _player->getAccount()->getPoints());
		_player->greenText(m_buffer);
	}
}

void IChatHandler::_sCmd_GetPoints(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	sprintf(m_buffer, "You have got %d points", _player->getAccount()->getPoints());
	_player->greenText(m_buffer);
}

void IChatHandler::_sCmd_PlayerInfo(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	const char *t_name = trim(m_buffer, BUF_SIZE, _message);

	if (t_name[0])
	{
		PlayerObjectPtr &t_player = _player->getObject()->getWorld()->getPlayerByName(t_name);

		if (t_player)
		{
			sprintf(m_buffer, "Acc: %s, AccLvl: %d, pts: %d",
				t_player->getPlayer()->getAccount()->getName(),
				t_player->getPlayer()->getAccount()->getAccessLevel(),
				t_player->getPlayer()->getAccount()->getPoints());

			_player->greenText(m_buffer);
		}
		else
		{
			_player->greenText("Player not connected");
		}
	}
	else
	{
		_player->greenText("You have to enter a player name");
	}
}

void IChatHandler::_sCmd_Immortal(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	_player->getObject()->toggleFlag(IPlayerObject::FLAG_INVINCIBLE);

	if (_player->getObject()->isFlag(IPlayerObject::FLAG_INVINCIBLE))
	{
		_player->greenText("Immortality on");
	}
	else
	{
		_player->greenText("Immortality off");
	}
}

void IChatHandler::_sCmd_OneHit(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	_player->getObject()->toggleFlag(IPlayerObject::FLAG_ONEHITKILL);

	if (_player->getObject()->isFlag(IPlayerObject::FLAG_ONEHITKILL))
	{
		_player->greenText("Onehit on");
	}
	else
	{
		_player->greenText("Onehit off");
	}
}

void IChatHandler::_sCmd_God(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	_sCmd_Immortal(_player, _message);
	_sCmd_OneHit(_player, _message);
}

void IChatHandler::_sCmd_SetAccessLevel(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	char t_name[256];
	s32 t_accLvl = 0;

	sscanf(_message, "%s %d", t_name, &t_accLvl);

	if (t_name[0])
	{
		PlayerObjectPtr &t_player = _player->getObject()->getWorld()->getPlayerByName(t_name);

		if (t_player)
		{
			t_player->getPlayer()->getAccount()->setAccessLevel(
				IAccount::accessLevel(Limit<s32>(t_accLvl, 0, _player->getAccount()->getAccessLevel())));

			sprintf(m_buffer, "Your access level has been changed to %d",
				_player->getAccount()->getAccessLevel());
			t_player->getPlayer()->getClient()->send(IPacketCreator::greenText(m_buffer));
		}
		else
		{
			_player->greenText("Player not connected");
		}
	}
}

void IChatHandler::_sCmd_Mob(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_mobId = 20;
	s32 t_count = 1;
	f32 t_radius = 1.0f;
	f32 t_aggro = 0.0f;

	sscanf(_message, "%d %d %f %f", &t_mobId, &t_count, &t_radius, &t_aggro);

	if (t_count >= 1 &&
		t_count <= 1000)
	{
		const IMoverData *t_mover = _getWorldDataMngr()->getMoverById(t_mobId);

		if (t_mover)
		{
			t_radius = Limit(t_radius, 0.0f, 200.0f);

			for (s32 i = 0; i < t_count; ++i)
			{
				_player->getObject()->getWorld()->createMobObject(
					t_mover,
					CPoint::randomPosition(_player->getObject()->getPosition(), t_radius),
					eventf(t_aggro),
					0);
			}
		}
		else
		{
			_player->greenText("Invalid mob id");
		}
	}
	else
	{
		_player->greenText("Invalid count");
	}
}

void IChatHandler::_sCmd_CreateSpawn(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_mobId = 20;
	u32 t_count = 1;
	f32 t_radius = 1.0f;
	f32 t_aggro = 0.0f;
	s32 t_size = 100;

	sscanf(_message, "%d %u %f %f %d", &t_mobId, &t_count, &t_radius, &t_aggro, &t_size);

	if (t_count >= 1 &&
		t_count <= 1000)
	{
		const IMoverData *t_mover = _getWorldDataMngr()->getMoverById(t_mobId);

		if (t_mover)
		{
			t_radius = Limit(t_radius, 0.0f, 200.0f);
			t_aggro = Limit(t_aggro, 0.0f, 1.0f);
			t_size = Limit(t_size, 0, 0x7fff);

			//create the spawn
			const ISpawnData *t_newSpawn = _getWorldDataMngr()->createSpawn(
				t_mover, t_count, _player->getObject()->getPosition(),
				_player->getObject()->getWorld()->getId(), t_radius, static_cast<s16>(t_size),
				t_aggro, 1000, true, 7000, 1.0f, 1.0f, 1.0f);

			//create the file name
			char t_fileName[512];
			sprintf(t_fileName, "%s_%d_%s_%lld%s",
				_getSettings()->Data.SpawnFolder.c_str(),
				t_mobId,
				_player->getCharacter()->getName(),
				CTime::seconds(),
				_getSettings()->Data.SpawnFileEnding.c_str());

			//add it to the world and save it
			if (t_newSpawn &&
				(_player->getObject()->getWorld()->addSpawn(t_newSpawn) != 0) &&
				t_newSpawn->saveFile(t_fileName))
			{
				sprintf(m_buffer, "Spawn created and saved as \"%s\"", t_fileName);
				_player->greenText(m_buffer);
			}
			else
			{
				_player->greenText("Spawn could not be created");
			}
		}
		else
		{
			_player->greenText("Invalid mob id");
		}
	}
	else
	{
		_player->greenText("Invalid count");
	}
}

void IChatHandler::_sCmd_CreateItemList(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_listType = 0;
	sscanf(_message, "%d", &t_listType);

	bool t_success = false;

	switch (t_listType)
	{
	case 0:
		{
			sprintf(m_buffer, "itemList_%s.html", _player->getCharacter()->getName());

			t_success = m_pserver->getDataManager()->getItemManager()->saveHtmlItemList(m_buffer);
			break;
		}

	case 1:
		{
			sprintf(m_buffer, "itemList_%s.txt", _player->getCharacter()->getName());

			t_success = m_pserver->getDataManager()->getItemManager()->saveUseItemList(m_buffer);
			break;
		}

	case 2:
		{
			sprintf(m_buffer, "itemList_spc1_%s.txt", _player->getCharacter()->getName());

			t_success = m_pserver->getDataManager()->getItemManager()->saveSpcItemList1(m_buffer);
			break;
		}
	}

	if (t_success)
	{
		_player->greenText("Item list saved!");
	}
	else
	{
		_player->greenText("Error");
	}
}

void IChatHandler::_sCmd_Place(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	sscanf(_message, "%s", m_buffer);

	CPoint t_pos;
	IWorld *t_world = 0;

	/*
	Charerstellung = 6973 100 3328
	CW                 = 3889.79 59 3926.37
	Arena (Glaub Welt 204) = 540 138.51 485
	Flaris(Aus der Arena) = 6935.36 100.06 3247.69
	Flaris (Blink)     = 7161 100 3264
	Flaris (TownBlink) = 6968.38 100 3328.86
	Saint Morning   = 8321 100 3720
	SM Town         = 8470.57 100 3635.78
	SM Arena( Aus der Arena) = 8441.85 100 3622.26
	Arena (Tod) = 538.78 138.23 474.75
	Darkon = 3896 59 4378
	DarkonTown = 3808.40 59 4455.15
	Darkon(Aus der Arena) = 3808.40 59 4455.15
	*/

	if (xstricmp("flaris", m_buffer) == 0 ||
		xstricmp("fl", m_buffer) == 0)
	{
		t_pos.X = 6960;
		t_pos.Y = 100;
		t_pos.Z = 3221;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("creation", m_buffer) == 0)
	{
		t_pos.X = 6973;
		t_pos.Y = 100;
		t_pos.Z = 3328;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("flbw", m_buffer) == 0)
	{
		t_pos.X = 6968.38f;
		t_pos.Y = 100;
		t_pos.Z = 3328.86f;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("madren", m_buffer) == 0)
	{
		t_pos.X = 7338;
		t_pos.Y = 116;
		t_pos.Z = 3656;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("mas", m_buffer) == 0)
	{
		t_pos.X = 7618;
		t_pos.Y = 155;
		t_pos.Z = 4275;

		t_world = m_pserver->getWorld(1);
	}
	else if (
		xstricmp("sm", m_buffer) == 0 ||
		xstricmp("saint", m_buffer) == 0)
	{
		t_pos.X = 8321;
		t_pos.Y = 100;
		t_pos.Z = 3720;

		t_world = m_pserver->getWorld(1);
	}
	else if (
		xstricmp("darken", m_buffer) == 0 ||
		xstricmp("darkon", m_buffer) == 0)
	{
		t_pos.X = 3808.40f;
		t_pos.Y = 59;
		t_pos.Z = 4455.15f;

		t_world = m_pserver->getWorld(1);
	}
	else if (
		xstricmp("mine", m_buffer) == 0 ||
		xstricmp("dekane", m_buffer) == 0)
	{
		t_pos.X = 5072;
		t_pos.Y = 55;
		t_pos.Z = 3964;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("cw", m_buffer) == 0)
	{
		t_pos.X = 3890;
		t_pos.Y = 59;
		t_pos.Z = 3925;

		t_world = m_pserver->getWorld(1);
	}
	else if (
		xstricmp("desert", m_buffer) == 0 ||
		xstricmp("gm", m_buffer) == 0)
	{
		t_pos.X = 8217;
		t_pos.Y = 100;
		t_pos.Z = 5656;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("chaner", m_buffer) == 0)
	{
		t_pos.X = 7295;
		t_pos.Y = 124;
		t_pos.Z = 3693;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("babari", m_buffer) == 0)
	{
		t_pos.X = 6965;
		t_pos.Y = 100;
		t_pos.Z = 3170;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("glaphan", m_buffer) == 0)
	{
		t_pos.X = 3345;
		t_pos.Y = 94;
		t_pos.Z = 2550;

		t_world = m_pserver->getWorld(1);
	}
	else if (xstricmp("azria", m_buffer) == 0)
	{
		t_pos.X = 1271;
		t_pos.Y = 113;
		t_pos.Z = 1324;

		t_world = m_pserver->getWorld(2);
	}
	else if (xstricmp("volcano", m_buffer) == 0)
	{
		t_pos.X = 1413;
		t_pos.Y = 86;
		t_pos.Z = 528;

		t_world = m_pserver->getWorld(203);
	}
	else
	{
		_player->greenText("Unknown position");
		return;
	}

	_player->getObject()->teleport(t_pos, t_world);
}

void IChatHandler::_sCmd_Ban(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	u32 t_days = 0;
	u32 t_hours = 0;

	sscanf(_message, "%s %u %u", m_buffer, &t_days, &t_hours);

	if (m_buffer[0] != 0)
	{
		IWorldPlayer *t_player = _player->getObject()->getWorld()->getServer()->getPlayer(m_buffer);

		Time t_now = CTime::seconds();

		if (t_player &&
			t_player->getObject())
		{
			if (_player->getAccount()->getAccessLevel() > t_player->getAccount()->getAccessLevel())
			{
				t_player->getObject()->changeBanTime(t_now + (t_days * 24 + t_hours) * 60 * 60);

				m_pserver->removePlayer(t_player);
			}
		}
		else
		{
			//...

			if (t_now != t_player->getAccount()->getBanTime())
			{
				m_pserver->removePlayer(t_player);
			}

			_player->greenText("Not connected (offline ban is todo)");
		}
	}
	else
	{
		_player->greenText("#ban [str]name [uint]days");
	}
}

void IChatHandler::_sCmd_PvpPoints(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_points = 0;

	sscanf(_message, "%d", &t_points);

	_player->getObject()->changePvpPoints(t_points);
}

void IChatHandler::_sCmd_PkPoints(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_points = 0;

	sscanf(_message, "%d", &t_points);

	_player->getObject()->changePkPoints(t_points);
}

void IChatHandler::_sCmd_Disposition(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_points = 0;

	sscanf(_message, "%d", &t_points);

	_player->getObject()->changeDisposition(t_points);
}

void IChatHandler::_sCmd_Weather(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	s32 t_weather = 0;

	sscanf(_message, "%d", &t_weather);

	if (t_weather < 0)
	{
		m_pserver->setWeatherFixed(false);
	}
	else
	{
		m_pserver->setWeatherFixed(true);
		m_pserver->setWeather(weather(t_weather));
	}
}

void IChatHandler::_sCmd_Revive(IWorldPlayer *_player, const char *_message)
{
	FDASSERT(_player);
	FDASSERT(_message);

	_player->getObject()->reviveOriginal();
}

