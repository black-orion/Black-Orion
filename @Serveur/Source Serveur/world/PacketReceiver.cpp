#include "PacketReceiver.h"
#include "WorldServer.h"
#include "WorldPlayer.h"
#include "World.h"
#include "PlayerObject.h"
#include "MobObject.h"
#include "NpcObject.h"
#include "NpcData.h"
#include "../shared/PacketReader.h"
#include "../shared/Log.h"
#include "../shared/ItemData.h"

#include "../shared/PacketCreator.h"


IPacketReceiver::IPacketReceiver(IWorldServer *_server)
	: m_server(_server)
{
	FDASSERT(m_server);
}

bool IPacketReceiver::handlePacket(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	s32 t_command = IPacketReader::readWorldHeader(t_packet);

	//handle the command
	switch (t_command)
	{
	case 0x001a:
		return _sendMail(_player);

	case 0x001b:
		return _mailDelete(_player);

	case 0x001c:
		return _mailTakeItem(_player);

	case 0x001d:
		return _mailBox(_player);

	case 0x001f:
		return _mailTakeMoney(_player);

	case 0x0024:
		return _mailRead(_player);

	case 0xff00:
		return _login(_player);

	case 0x0f0003:
		return _skillChange(_player);

	case 0xff0000:
		return _chat(_player);

	case 0xff0006:
		return _invMoveItem(_player);

	case 0xff0007:
		return _invDropItem(_player);

	case 0xff0010:
	case 0xff0011:
	case 0xff0012:
		return _attack(_player);

	case 0xff000b:
		return _invUnequip(_player);

	case 0xff0019:
		return _invDeleteItem(_player);

	case 0xff0021:
		return _useItem(_player);

	case 0xff0022:
		return _unknown_1(_player);

	case 0xff0023:
		return _targetChange(_player);

	case 0xff00a7:
		return _trade(_player);

	case 0xff00a9:
		return _shopOpen(_player);

	case 0xff00aa:
		return _shopClose(_player);

	case 0xff00ab:
		return _shopAddItem(_player);

	case 0xff00ae:
		return _shopRemoveItem(_player);

	case 0xff00b0:
		return _talkToNpc(_player);

	case 0xff00b1:
		return _tradeNpc(_player);

	case 0xff00b3:
		return _buyNpc(_player);

	case 0xff00b4:
		return _sellNpc(_player);

	case 0xff00c1:
		return _loadStar(_player);

	case 0xff00d2:
		return _unknown_0(_player);

	case 0x70000004:
		return _specialOptionScroll(_player);

	case 0xf000b04e:
		return _request_ranking_guild(_player);

	case 0xf000b024:
	case 0xf000f113:
		return _upgrade(_player);

	case 0xf000b055:
		return _shopChat(_player);

	case 0xf000b058:
		return _shopChatEnter(_player);

	case 0xf000b059:
		return _shopChatLeave(_player);

	case 0xf000d022:
		return _in_GuildCombat(_player);

	case 0xf000f009:
		return _viewEquipment(_player);

	case 0xf000f501:
		return _statChange(_player);

	case 0xf000f802:
		return _characterInfos(_player);

	case 0xf000f813:
		return _buffEvent(_player);

	case 0xffffff00:
		return _mouseControl(_player);

	case 0xffffff01:
		return _keyboardControl(_player);

	case 0xffffff02:
		return _motion(_player);

	case 0xffffff07:
		return _follow(_player);

	case 0xffffff08:
		return _querygetpos(_player);

	case 0xffffff09:
		return _getpos(_player);

	case 0xffffff11:
		return _partyAccept(_player);

	case 0xffffff17:
		return _partyInvitation(_player);

	case 0xffffff18:
		return _partyReject(_player);

	case 0xffffff61:
		return _addFriendPerClick(_player);

	case 0xffffff67:
		return _messengerStatus(_player);

	case 0xffffff6b:
		return _addFriend(_player);

	case 0xffffff7c:
		return _cheer(_player);

	case 0:
		Log::write(LOG_WARNING, "Packet client Invalide");

#ifdef SDEBUG
		t_packet.saveFormatted("_invalide_packets.txt");
#endif
		return false;

	default:
		Log::write(LOG_DEBUG, "Packet inconnue Recu 0x%x", t_command);

#ifdef SDEBUG
		sprintf(m_buffer, "logs/_inconnue_%x.txt", t_command);
		t_packet.saveFormatted(m_buffer);
#endif
		return false;
	}

	return !t_packet.end();
}

bool IPacketReceiver::_login(IWorldPlayer *_player)
{
	static const u32 T_BUF_SIZE = 256;
	static char ts_buf_charname[T_BUF_SIZE];
	static char ts_buf_accname[T_BUF_SIZE];
	static char ts_buf_password[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//not used
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getInt();
	t_packet.getByte();

	//char name
	if (!t_packet.getString(ts_buf_charname, T_BUF_SIZE))
		return false;

	//account name
	if (!t_packet.getString(ts_buf_accname, T_BUF_SIZE))
		return false;

	//pw
	if (!t_packet.getString(ts_buf_password, T_BUF_SIZE))
		return false;

	//check account
	AccountPtr t_account = m_server->getAccountManager()->getAccount_W(ts_buf_accname);

	if (t_account &&
		xstricmp(t_account->getPassword(), ts_buf_password) == 0)
	{
		_player->setAccount(t_account);

		//check character
		CharacterPtr t_char = m_server->getCharacterManager()->getCharacter_W(ts_buf_charname);

		//char exists?
		if (t_char)
		{
			_player->setCharacter(t_char);

			_player->getCharacter()->setOnline(true);

			m_server->getCharacterManager()->saveCharacter_onlineStatus_W(_player->getCharacter());
		}
		//wrong char name
		else
		{
			return false;
		}
	}

	//wrong id or wrong password
	else
	{
		return false;
	}

	t_packet.getInt();
	t_packet.getInt();

	Log::write(LOG_GAME, "Nouveau Joueur");

	m_server->enterWorld(_player);

	return !t_packet.end();
}

bool IPacketReceiver::_chat(IWorldPlayer *_player)
{
	static const u32 T_BUF_SIZE = 512;
	static char ts_buf[T_BUF_SIZE];

	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//the message
	if (!t_packet.getString(ts_buf, T_BUF_SIZE))
		return false;

	m_server->getChatHandler()->chat(_player, ts_buf);

	return !t_packet.end();
}

bool IPacketReceiver::_attack(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	s32 t_motion = t_packet.getInt();
	ID t_targetId = t_packet.getInt();

	t_packet.skip(3 * sizeof(s32)); //3 ints

	Log::write(LOG_DEBUG, "Joueur attaquant %d", t_targetId);

	WorldObjectPtr t_obj = _player->getObject()->getWorld()->getObjectById(t_targetId);

	if (t_obj &&
		t_obj->isMob())
	{
		_player->getObject()->attack(boost::dynamic_pointer_cast<IMobObject>(t_obj), t_motion);
	}

	return !t_packet.end();
}

bool IPacketReceiver::_mouseControl(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getShort();
	t_packet.getByte();

	// Set the position
	CPoint t_pos;
	t_packet.getCoordinates(t_pos);

	t_packet.getByte();

	_player->getObject()->walk(t_pos);

	return !t_packet.end();
}

bool IPacketReceiver::_keyboardControl(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	CPoint t_pos;
	t_packet.getCoordinates(t_pos);

#ifdef SDEBUG
	printf("%f %f %f\n", t_pos.X, t_pos.Y, t_pos.Z);

	printf("%d ", t_packet.getInt());
	printf("%d ", t_packet.getInt());
	printf("%d\n", t_packet.getInt());

	f32 t_angle = t_packet.getFloat();

	printf("Angle: %f\n", t_angle);

	s32 t_move = t_packet.getInt();
	s32 t_motion = t_packet.getInt();
	s32 t_action = t_packet.getInt();

	printf("%d %d %d\n", t_move, t_motion, t_action);

	printf("%d ", t_packet.getInt());
	printf("%d ", t_packet.getInt());
	printf("%d ", t_packet.getInt());
	printf("%d ", t_packet.getInt());
	printf("%d\n", t_packet.getInt());

	while (!t_packet.end())
		printf("%02x\n", t_packet.getByte());
#else
	t_packet.quit();
#endif

	return !t_packet.end();
}

bool IPacketReceiver::_motion(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	CPoint t_pos;
	t_packet.getCoordinates(t_pos);

#ifdef SDEBUG
	printf("Motion: %f %f %f\n", t_pos.X, t_pos.Y, t_pos.Z);

	t_packet.saveFormatted("__motion.txt");
#endif

	t_packet.quit();

	return !t_packet.end();
}

bool IPacketReceiver::_invUnequip(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_slotId = t_packet.getInt();

	t_packet.skip(sizeof(s32) + sizeof(s16) + sizeof(s8));

	_player->getObject()->getInventory()->unequip(t_slotId);

	return !t_packet.end();
}

bool IPacketReceiver::_invDropItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s32));
	ID t_slotId = t_packet.getInt();
	s32 t_count = t_packet.getShort();
	t_packet.getFloat(); //x
	t_packet.getFloat(); //y
	t_packet.getFloat(); //z

	_player->getObject()->getInventory()->dropItem(t_slotId, t_count);

	return !t_packet.end();
}

bool IPacketReceiver::_invDeleteItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_slotId = t_packet.getInt();
	s32 t_count = t_packet.getInt();

	_player->getObject()->getInventory()->deleteItem(t_slotId, t_count);

	return !t_packet.end();
}

bool IPacketReceiver::_useItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getShort(); //0
	ID t_slotId = t_packet.getShort();
	t_packet.getInt(); //-1
	t_packet.getInt(); //-1
	t_packet.getInt(); //0xbf800000

#ifdef SDEBUG
	Log::write(LOG_DEBUG, "Item with id %d is used", t_slotId);
#endif

	_player->getObject()->getInventory()->useItem(t_slotId);

	return !t_packet.end();
}

bool IPacketReceiver::_invMoveItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getByte(); //Unknown
	u32 t_oldSlotPos = t_packet.getByte();
	u32 t_newSlotPos = t_packet.getByte();

#ifdef SDEBUG
	Log::write(LOG_DEBUG, "moveItem %d -> %d", t_oldSlotPos, t_newSlotPos);
#endif

	_player->getObject()->getInventory()->moveItem(t_oldSlotPos, t_newSlotPos);

	return !t_packet.end();
}

bool IPacketReceiver::_targetChange(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_targetId = t_packet.getInt();
	s8 t_action = t_packet.getByte();

#ifdef SDEBUG
	Log::write(LOG_DEBUG, "Player target changed: %d (%d)", t_targetId, s32(t_action));
#endif

	return !t_packet.end();
}

bool IPacketReceiver::_follow(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_targetId = t_packet.getInt();
	t_packet.skip(sizeof(s32));

	Log::write(LOG_DEBUG, "Player follows %d", t_targetId);

	_player->getObject()->follow(_player->getObject()->getWorld()->getObjectById(t_targetId));

	return !t_packet.end();
}

bool IPacketReceiver::_querygetpos(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_targetId = t_packet.getInt();

	return !t_packet.end();
}

bool IPacketReceiver::_getpos(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();
// 3Partie  vPos = Position , fAngle = Angle , objid = Objet
	ID t_vPos = t_packet.getInt();
float  t_fAngle = t_packet.getFloat();
	ID t_objid = t_packet.getInt();

	return !t_packet.end();
}


bool IPacketReceiver::_talkToNpc(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_npcId = t_packet.getInt();
	if (!t_packet.getString(m_buffer, BUF_SIZE))
		return false;
	//printf("%d\n", m_buffer); //???
	s32 t_action1 = t_packet.getInt(); //action id 1
	s32 t_action2 = t_packet.getInt(); //action id 2
	t_packet.getInt(); //npc id
	s32 t_unknown = t_packet.getInt(); //???

	WorldObjectPtr &t_obj = _player->getObject()->getWorld()->getObjectById(t_npcId);

	if (t_obj &&
		t_obj->isNpc())
	{
		NpcObjectPtr t_npc = boost::dynamic_pointer_cast<INpcObject>(t_obj);
		t_npc->dialogAction(_player->getObject(), m_buffer, t_action1, t_action2, t_unknown);
	}
	else
	{
		printf("Npc invalide id %d\n", t_npcId);
	}

	return !t_packet.end();
}

bool IPacketReceiver::_tradeNpc(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_npcId = t_packet.getInt();

	WorldObjectPtr &t_obj = _player->getObject()->getWorld()->getObjectById(t_npcId);

	if (t_obj &&
		t_obj->isNpc())
	{
		_player->getObject()->setNpcTarget(boost::dynamic_pointer_cast<INpcObject>(t_obj));
		_player->getClient()->send(IPacketCreator::npcShop(boost::dynamic_pointer_cast<INpcObject>(t_obj)));
	}
	else
	{
		Log::write(LOG_WARNING, "Npc trade with non-npc object!");
	}

	return !t_packet.end();
}

bool IPacketReceiver::_buyNpc(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s16));

	s32 t_buyCount = t_packet.getShort();
	ID t_itemId = t_packet.getInt();
	const IItemProperties *t_item;

	NpcObjectPtr t_npc = _player->getObject()->getNpcTarget();
	if (t_npc)
	{
		t_item = t_npc->getData()->getItemFromId(t_itemId);

		if (t_item)
		{
			IItemProperties t_newItem(t_item->getData(), t_buyCount);

			//is there a place for the item in the players's inv?
			//if (_player->getCharacter()->getInventory()->isPlaceFor(t_newItem))
			if (true)
			{
				PENYA t_totalCost = t_buyCount * t_item->getData()->getCost();

				//check the money
				if (_player->getCharacter()->getPenya() >= t_totalCost)
				{
					//take the money
					_player->getObject()->changePenya(_player->getCharacter()->getPenya() - t_totalCost);

					//give the items
					_player->getObject()->getInventory()->addItem(t_newItem);
				}
				else
				{
					//... not enough penyas (client should not allow the player to buy this)
				}
			}
			else
			{
				//... no place for the items (does the client check this?)
			}
		}
		else
		{
			Log::write(LOG_DEBUG, "Player tries to buy an invalid NPC shop item (%d)!", t_itemId);
		}
	}

	return !t_packet.end();
}

bool IPacketReceiver::_sellNpc(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_slotId = t_packet.getByte();
	s32 t_count = t_packet.getShort();

	_player->getObject()->getInventory()->sellItem(t_slotId, t_count);

	return !t_packet.end();
}

bool IPacketReceiver:: _request_ranking_guild(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_nVer = t_packet.getInt();

	return !t_packet.end();
}



bool IPacketReceiver::_upgrade(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_targetId = t_packet.getInt();
	ID t_materialId = t_packet.getInt();

	_player->getObject()->getInventory()->upgrade(t_materialId, t_targetId);

	return !t_packet.end();
}

bool IPacketReceiver::_buffEvent(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	static char t_buf[256];

	if (!t_packet.getString(t_buf, sizeof(t_buf)))
		return false;

#ifdef SDEBUG
	printf("%s\n", t_buf);
#endif

	_player->getObject()->getWorld()->buffEvent(_player->getObject());

	return !t_packet.end();
}

bool IPacketReceiver::_addFriend(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s32)); //unknown

	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf[TS_BUF_SIZE];

	t_packet.getString(ts_buf, TS_BUF_SIZE);

#ifdef SDEBUG
	Log::write(LOG_DEBUG, "Add friend \"%s\"", ts_buf);
#endif

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_addFriendPerClick(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s32)); //31

	ID t_playerId = t_packet.getInt();

	WorldObjectPtr &t_obj = _player->getObject()->getWorld()->getObjectById(t_playerId);

	if (t_obj &&
		t_obj->isPlayer())
	{
		PlayerObjectPtr t_pObj = boost::dynamic_pointer_cast<IPlayerObject>(t_obj);

#ifdef SDEBUG
		Log::write(LOG_DEBUG, "Add friend \"%s\"", t_pObj->getCharacter()->getName());
#endif

		//...
	}

	return !t_packet.end();
}

bool IPacketReceiver::_messengerStatus(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s32)); //unknown
	s32 t_status = t_packet.getInt();

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_statChange(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	s32 t_str = t_packet.getInt();
	s32 t_sta = t_packet.getInt();
	s32 t_dex = t_packet.getInt();
	s32 t_int = t_packet.getInt();

	if (t_str >= 0 &&
		t_sta >= 0 &&
		t_dex >= 0 &&
		t_int >= 0)
	{
		s32 t_sum = t_str + t_sta + t_dex + t_int;

		if (t_sum > 0)
		{
			_player->getCharacter()->addStr(t_str);
			_player->getCharacter()->addSta(t_sta);
			_player->getCharacter()->addDex(t_dex);
			_player->getCharacter()->addInt(t_int);
			_player->getCharacter()->setStatPoints(_player->getCharacter()->getStatPoints() - t_sum);

			_player->getObject()->onBaseStatChanged();
		}
	}

	return !t_packet.end();
}

bool IPacketReceiver::_skillChange(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	for (u32 i = 0; i < 49; ++i)
	{
		s32 skill = t_packet.getInt();
		s32 level = t_packet.getInt();

#ifdef SDEBUG
		Log::write(LOG_DEBUG, "%d := %d\n", skill, level);
#endif
	}

	return !t_packet.end();
}

bool IPacketReceiver::_specialOptionScroll(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_scrollId = t_packet.getInt();
	ID t_targetId = t_packet.getInt();

	_player->getObject()->getInventory()->useSpecialOptionScroll(t_scrollId, t_targetId);

	return !t_packet.end();
}

bool IPacketReceiver::_shopAddItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	u32 t_shopPos = t_packet.getShort();
	u32 t_invPos = t_packet.getByte();
	s32 t_count = t_packet.getShort();
	PENYA t_price = t_packet.getInt();

	printf("Item %u -> %u (%d) %d PENYA\n", t_invPos, t_shopPos, t_count, t_price);

	//...

	_player->getClient()->send(IPacketCreator::addItemToShop(_player->getObject(), 0));

	return !t_packet.end();
}

bool IPacketReceiver::_shopRemoveItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	u32 t_shopPos = t_packet.getByte();

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_shopChat(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	if (!t_packet.getString(m_buffer, BUF_SIZE)) //chat text
		return false;

	//...

	_player->getObject()->sendToLocalArea(IPacketCreator::shopChat(_player->getObject(), m_buffer));

	return !t_packet.end();
}

bool IPacketReceiver::_shopOpen(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	if (!t_packet.getString(m_buffer, BUF_SIZE)) //shop name
		return false;

	//...

	_player->getObject()->sendToLocalArea(IPacketCreator::openShop(_player->getObject()));

	return !t_packet.end();
}

bool IPacketReceiver::_shopClose(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.getInt(); //???

	_player->getObject()->sendToLocalArea(IPacketCreator::closeShop(_player->getObject()));

	return !t_packet.end();
}

bool IPacketReceiver::_shopChatEnter(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_shopChatLeave(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_in_GuildCombat(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	//...

	return !t_packet.end();
}


bool IPacketReceiver::_mailBox(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	_player->getObject()->getPostBox()->showList();

	return !t_packet.end();
}

bool IPacketReceiver::_mailRead(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_mailId = t_packet.getInt();

	_player->getObject()->getPostBox()->setMailRead(t_mailId);

	return !t_packet.end();
}

bool IPacketReceiver::_mailTakeMoney(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_mailId = t_packet.getInt();

	_player->getObject()->getPostBox()->takeMoney(t_mailId);

	return !t_packet.end();
}

bool IPacketReceiver::_mailTakeItem(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_mailId = t_packet.getInt();

	_player->getObject()->getPostBox()->takeItem(t_mailId);

	return !t_packet.end();
}

bool IPacketReceiver::_sendMail(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_slotId = t_packet.getByte();
	s32 t_itemCount = t_packet.getShort();
	sdk::stringc t_receiverName = t_packet.getString();
	PENYA t_money = t_packet.getInt();
	sdk::stringc t_title = t_packet.getString();
	sdk::stringc t_text = t_packet.getString();

	_player->getObject()->getPostBox()->sendMail(t_receiverName.c_str(), t_money, t_slotId, t_itemCount,
		t_title.c_str(), t_text.c_str());

	return !t_packet.end();
}

bool IPacketReceiver::_mailDelete(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_mailId = t_packet.getInt();

	_player->getObject()->getPostBox()->deleteMail(t_mailId);

	return !t_packet.end();
}

bool IPacketReceiver::_characterInfos(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_charId = t_packet.getInt();
	t_packet.skip(sizeof(s32));

	CharacterPtr t_char = m_server->getCharacterManager()->getCharacter_W(t_charId);

	if (t_char)
	{
		_player->getClient()->send(IPacketCreator::characterInfos(t_char));
	}

	return !t_packet.end();
}

bool IPacketReceiver::_partyInvitation(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	t_packet.skip(sizeof(s32));

	ID t_playerId = t_packet.getInt();

	t_packet.skip(sizeof(s32));

	IPlayerObject *t_pObj = 0;

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_cheer(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_playerId = t_packet.getInt();

	IPlayerObject *t_pObj = 0;

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_viewEquipment(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_playerId = t_packet.getInt();

	IPlayerObject *t_pObj = 0;

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_trade(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_playerId = t_packet.getInt();

	IPlayerObject *t_pObj = 0;

	//...

	return !t_packet.end();
}

bool IPacketReceiver::_partyAccept(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_leaderId = t_packet.getInt();
	t_packet.skip(sizeof(s32)); //1
	t_packet.skip(sizeof(s32)); //0
	t_packet.skip(sizeof(s32)); //0
	ID t_inviteeId = t_packet.getInt();
	t_packet.skip(sizeof(s32)); //100
	t_packet.skip(sizeof(s32)); //0
	t_packet.skip(sizeof(s32)); //0

	//get the inviting player
	IWorldPlayer *t_leaderPlayer = m_server->getPlayerByCharacterId(t_leaderId);

	//does the leader exist and is the invitee id correct?
	if (t_leaderPlayer == 0 ||
		_player->getCharacter()->getId() != t_inviteeId)
	{
		return false;
	}

	//leader player object
	PlayerObjectPtr t_leader = t_leaderPlayer->getObject();

	if (t_leader == 0 ||
		t_leader == _player->getObject())
	{
		return false;
	}

	printf("Groupe Accepter(Chef %s)\n", t_leader->getCharacter()->getName());

	t_leader->partyInvitationAccepted(_player->getObject());

	return !t_packet.end();
}

bool IPacketReceiver::_partyReject(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	ID t_leaderId = t_packet.getInt();
	ID t_inviteeId = t_packet.getInt();
	t_packet.skip(sizeof(s32));

	return !t_packet.end();
}

bool IPacketReceiver::_loadStar(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

	Log::write(LOG_DEBUG, "Player is resurrected at the load star");

	if (_player->getObject()->isDead())
	{
		_player->getObject()->reviveLoadStar();
	}
	else
	{
		return false;
	}

	return !t_packet.end();
}

bool IPacketReceiver::_unknown_0(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

#ifdef SDEBUG
	printf("Target id: %d\n",
		_player->getObject()->getTarget() ? _player->getObject()->getTarget()->getId() : -1);

	printf("0xff00d2:\n");
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
#else
	t_packet.quit();
#endif

	return !t_packet.end();
}

bool IPacketReceiver::_unknown_1(IWorldPlayer *_player)
{
	FDASSERT(_player);

	CByteArray &t_packet = _player->getClient()->incoming();

#ifdef SDEBUG
	printf("Target id: %d\n",
		_player->getObject()->getTarget() ? _player->getObject()->getTarget()->getId() : -1);

	printf("0xff0022:\n");
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
	printf("%d\n", t_packet.getInt());
#else
	t_packet.quit();
#endif

	return !t_packet.end();
}
