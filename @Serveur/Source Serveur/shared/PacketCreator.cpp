#include "PacketCreator.h"
#include "Account.h"
#include "Character.h"
#include "Log.h"
#include "ItemPack.h"
#include "ItemData.h"
#include "../login/LoginPlayer.h"
#include "../char/CharPlayer.h"
#include "../world/WorldPlayer.h"
#include "../world/PlayerObject.h"
#include "../world/MobObject.h"
#include "../world/NpcObject.h"
#include "../world/DropObject.h"
#include "../world/MoverData.h"
#include "../world/Creature.h"
#include "../world/NpcData.h"
#include "../world/World.h"
#include "../world/PostBox.h"
#include "../world/Party.h"


char IPacketCreator::ms_buffer[BUF_SIZE];

CByteArray IPacketCreator::ms_packet = CByteArray();

CByteArray &IPacketCreator::getPacket()
{
	return ms_packet;
}

void IPacketCreator::cleanup()
{
	ms_packet.destroy();
}

const CByteArray &IPacketCreator::greeting(s32 _id)
{
	_start(LCMD_GREETING);

	ms_packet.addInt(_id);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::loginError(IPacketCreator::E_LOGIN_ERROR _error)
{
	_start(LCMD_ERROR);

	ms_packet.addInt(_error);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::serverList(ILoginPlayer *_player, const ILoginISC::ServerList &_list)
{
	_start(LCMD_SERVER_LIST);

	ms_packet.addInt(0);
	ms_packet.addByte(1);
	//ms_packet.addString(_player->getAccount()->getName());
	
	ms_packet.addInt(_list.getServerCount());

	const ILoginISC::ServerList::Cluster *t_cluster;
	const ILoginISC::ServerList::Channel *t_channel;

	FOR_EACH (_list.Clusters, i)
	{
		t_cluster = &_list.Clusters[i];

		ms_packet.addInt(-1);
		ms_packet.addInt(t_cluster->Id);
		ms_packet.addString(t_cluster->Name);
		ms_packet.addString(strcmp(_player->getClient()->getIp(), "127.0.0.1") == 0 ? "127.0.0.1" : t_cluster->IP);
		ms_packet.addInt(1);
		ms_packet.addInt(1);
		ms_packet.addInt(1);
		ms_packet.addInt(1);

		FOR_EACH (t_cluster->Channels, j)
		{
			t_channel = &t_cluster->Channels[j];

			ms_packet.addInt(t_cluster->Id);
			ms_packet.addInt(t_channel->Id);
			ms_packet.addString(t_channel->Name);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(t_channel->CurrentPlayers);
			ms_packet.addInt(1);
			ms_packet.addInt(t_channel->MaxPlayers);
		}
	
	}

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::worldIp(const char *_ip)
{
	FDASSERT(_ip);

	_start(ECMD_CHANNEL_IP);

	ms_packet.addString(_ip);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::charList(ICharPlayer *_player)
{
	FDASSERT(_player);

	const AccountPtr &t_acc = _player->getAccount();

	FDASSERT(t_acc);

	_start(ECMD_CHAR_LIST);

	ms_packet.addInt(0);

	s32 t_char_count = 0;

	for (u32 i = 0; i < 3; ++i)
	{
		if (t_acc->getCharacter(i))
		{
			++t_char_count;
		}
	}

	ms_packet.addInt(t_char_count);

	for (u32 i = 0; i < 3; ++i)
	{
		const CharacterPtr &t_char = t_acc->getCharacter(i);

		if (t_char)
		{
			ms_packet.addInt(i);
			ms_packet.addInt(1);
			ms_packet.addInt(1);
			ms_packet.addInt(0x0b);
			ms_packet.addString(t_char->getName());

			ms_packet.addByte(0x0e);
			ms_packet.addByte(0xa6);
			ms_packet.addByte(0xd9);
			ms_packet.addByte(0x45);

			ms_packet.addByte(0xa5);
			ms_packet.addByte(0x79);
			ms_packet.addByte(0xc8);
			ms_packet.addByte(0x42);

			ms_packet.addByte(0x3f);
			ms_packet.addByte(0x58);
			ms_packet.addByte(0x49);
			ms_packet.addByte(0x45);

			ms_packet.addInt(t_char->getId());
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);

			ms_packet.addInt(t_char->getHairType());
			ms_packet.addInt(t_char->getHairColor());
			ms_packet.addInt(t_char->getFaceType());
			ms_packet.addByte(t_char->getSex());
			ms_packet.addInt(t_char->getJob());
			ms_packet.addInt(t_char->getLevel());
			ms_packet.addInt(0);
			ms_packet.addInt(t_char->getStr()); //STR
			ms_packet.addInt(t_char->getSta()); //STA
			ms_packet.addInt(t_char->getDex()); //DEX
			ms_packet.addInt(t_char->getInt()); //INT
			ms_packet.addInt(0);

			//Equipment
			ms_packet.addInt(_player->getEquipment(i).size());

			for (u32 j = 0; j < _player->getEquipment(i).size(); ++j)
			{
				if (_player->getEquipment(i)[j])
				{
					ms_packet.addInt(_player->getEquipment(i)[j]->getId());
				}
			}
		}
	}

	ms_packet.addInt(t_char_count);

	for (u32 i = 0; i < 3; ++i)
	{
		const CharacterPtr &t_char = t_acc->getCharacter(i);

		if (t_char)
		{
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addByte(0);
		}
	}

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::confirmWorld()
{
	_start(ECMD_WORLD_CONFIRMATION);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::worldBegin(IWorldPlayer *_player)
{
	const PlayerObjectPtr &t_obj = _player->getObject();
	ICharacter *t_char = _player->getCharacter().get();
	IAccount *t_acc = _player->getAccount().get();

//#define VERSION_12
//#define VERSION_13
//#define VERSION_14
#define VERSION_15



#ifdef VERSION_12

	_startShared(t_obj->getId(), 0xff00);

	_addPart(WCMD_SPAWN, t_obj->getId());

	ms_packet.addByte(5);
	ms_packet.addInt(_player->getCharacter()->getSex() == SEX_MALE ? 11 : 12);
	ms_packet.addByte(5);
	ms_packet.addShort(_player->getCharacter()->getSex() == SEX_MALE ? 11 : 12);
	ms_packet.addShort(t_obj->getSize()); //size
	ms_packet.addCoordinates(t_obj->getPosition()); //pos
	ms_packet.addShort(0); //Winkel
	ms_packet.addInt(t_obj->getId()); //!!ID!!
	ms_packet.addShort(0); //action?
	ms_packet.addByte(1);
	ms_packet.addInt(t_obj->getStat(DST_HP));
	ms_packet.addInt(5); //motion (5 = Rückwärts laufen)
	ms_packet.addInt(1); //1 stance
	ms_packet.addByte(1); //1
	ms_packet.addString(_player->getCharacter()->getName()); //name
	ms_packet.addShort(_player->getCharacter()->getSex()); //sex
	ms_packet.addByte(_player->getCharacter()->getHairType()); //Haartyp
	ms_packet.addInt(_player->getCharacter()->getHairColor()); //Haarfarbe
	ms_packet.addByte(_player->getCharacter()->getFaceType()); //Gesicht
	ms_packet.addInt(_player->getCharacter()->getId());
	ms_packet.addByte(_player->getCharacter()->getJob());
	ms_packet.addShort(_player->getCharacter()->getStr()); //STR
	ms_packet.addShort(_player->getCharacter()->getSta()); //STA
	ms_packet.addShort(_player->getCharacter()->getDex()); //DEX
	ms_packet.addShort(_player->getCharacter()->getInt()); //INT
	ms_packet.addShort(_player->getCharacter()->getLevel()); //level

	ms_packet.addInt(0xffffffff);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addByte(_player->getAccount()->getAccessLevel()); //Access
	ms_packet.addInt(_player->getObject()->getFlags());
	ms_packet.addInt(0);
	ms_packet.addInt(502);
	ms_packet.addInt(0);
	ms_packet.addInt(_player->getCharacter()->getPkPoints());
	ms_packet.addInt(_player->getCharacter()->getDisposition());
	ms_packet.addInt(0);
	ms_packet.addInt(_player->getCharacter()->getPvpPoints());

	for (u32 i = 0; i < 233; i++)
		ms_packet.addByte(0);

	ms_packet.addShort(t_obj->getStat(DST_MP)); //mp
	ms_packet.addShort(t_obj->getStat(DST_FP)); //fp
	ms_packet.addShort(13); //???
	ms_packet.addShort(0); //???
	ms_packet.addInt(0); //Flugexp
	ms_packet.addInt(_player->getCharacter()->getPenya());
	ms_packet.addInt64(_player->getCharacter()->getExp()); //exp
	ms_packet.addInt(0);
	ms_packet.addInt(_player->getCharacter()->getSkillPoints()); //SkillPoints

	for (u32 i = 0; i < 72; i++)
		ms_packet.addInt(0);
	ms_packet.addShort(0);

	ms_packet.addInt(1); //Vagrant Skill 1
	ms_packet.addInt(0); //Level
	ms_packet.addInt(2); //Vagrant Skill 2
	ms_packet.addInt(0); //Level
	ms_packet.addInt(3); //Vagrant Skill 3
	ms_packet.addInt(0); //Level
	for (u8 i = 0; i < 42; i++)
	{
		ms_packet.addInt(0xffffffff); //---
		ms_packet.addInt(0);  //Level
	}

	ms_packet.addByte(3); //cheer points
	ms_packet.addInt(0x36ee80);
	ms_packet.addInt(0); //char slot
	ms_packet.addInt((s32)_player->getCharacter()->getBankPenya()); //bank 1
	ms_packet.addInt(0); //bank 2
	ms_packet.addInt(0); //bank 3
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0xffffff00);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);

	IInventory *t_inv = _player->getObject()->getInventory();

	for (u32 i = 0; i < INV_PLACES; i++)
	{
		ms_packet.addInt(t_inv->getSlot(i).getId());
	}
	for (u32 i = INV_PLACES; i < INV_TOTAL_ITEMS; i++)
	{
		ms_packet.addInt(t_inv->getSlot(i).getItem() ? t_inv->getSlot(i).getId() : -1);
	}

	ms_packet.addByte(_player->getObject()->getInventory()->getCurrentItemCount());

	IItemPack *t_itemPack;

	for (u32 i = 0; i < INV_TOTAL_ITEMS; i++)
	{
		t_itemPack = _player->getObject()->getInventory()->getSlot(i).getItem().get();

		if (t_itemPack)
		{
			ms_packet.addByte(t_inv->getSlot(i).getId());
			ms_packet.addInt(t_inv->getSlot(i).getId());
			ms_packet.addInt(t_itemPack->getData()->getId());
			ms_packet.addInt(0);
			ms_packet.addInt(0); //Str: "sealed character name"
			ms_packet.addShort(t_itemPack->getCount());
			ms_packet.addByte(0); //"sealed character lvl"
			ms_packet.addInt(0x6ddd00); //durability
			ms_packet.addInt(0); //"sealed character job"
			ms_packet.addByte(0);
			ms_packet.addInt(t_itemPack->getUpgrade()); //upgrade
			ms_packet.addInt(0);
			ms_packet.addByte(t_itemPack->getElement()); //ele
			ms_packet.addInt(t_itemPack->getElementalUpgrade()); //eleupgr
			ms_packet.addInt(0);
			ms_packet.addInt(t_itemPack->getSlotCount());
			for (u32 j = 0; j < t_itemPack->getSlotCount(); ++j)
			{
				ms_packet.addInt(t_itemPack->getSlot(j)->getId());
			}
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt64(t_itemPack->getSpecialOption().getCode());
			ms_packet.addByte(0);
			ms_packet.addInt(0);
		}
	}

	//-----

	/*ms_packet.addByte(3);

	ms_packet.addByte(0);
	ms_packet.addInt(0); //unique item id
	ms_packet.addInt(22354);
	ms_packet.addInt(rand());
	ms_packet.addInt(0); //Str: "sealed character name"
	ms_packet.addShort(1);
	ms_packet.addByte(0); //"sealed character lvl"
	ms_packet.addInt(0x6ddd00); //durability
	ms_packet.addInt(0); //"sealed character job"
	ms_packet.addByte(0);
	ms_packet.addInt(20); //upgrade
	ms_packet.addInt(0);
	ms_packet.addByte(1); //ele
	ms_packet.addByte(10); //eleupgr
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);

	ms_packet.addByte(51);
	ms_packet.addInt(51); //unique item id
	ms_packet.addInt(22355);
	ms_packet.addInt(rand());
	ms_packet.addInt(0); //Str: "sealed character name"
	ms_packet.addShort(1);
	ms_packet.addByte(0); //"sealed character lvl"
	ms_packet.addInt(0x6ddd00); //durability
	ms_packet.addInt(0); //"sealed character job"
	ms_packet.addByte(0);
	ms_packet.addInt(10); //upgrade
	ms_packet.addInt(0);
	ms_packet.addByte(3); //ele
	ms_packet.addInt(10); //eleupgr
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);

	ms_packet.addByte(52);
	ms_packet.addInt(52); //unique item id
	ms_packet.addInt(22355);
	ms_packet.addInt(rand());
	ms_packet.addInt(0); //Str: "sealed character name"
	ms_packet.addShort(1);
	ms_packet.addByte(0); //"sealed character lvl"
	ms_packet.addInt(0x6ddd00); //durability
	ms_packet.addInt(0); //"sealed character job"
	ms_packet.addByte(0);
	ms_packet.addInt(10); //upgrade
	ms_packet.addInt(0);
	ms_packet.addByte(3); //ele
	ms_packet.addInt(10); //eleupgr
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);*/

	//-----

	for (s32 i = 0; i < INV_PLACES; i++)
	{
		ms_packet.addInt(i);
	}
	for (s32 i = INV_PLACES; i < INV_TOTAL_ITEMS; i++)
	{
		ms_packet.addInt(t_inv->getSlot(i).getItem() ? i : -1);
	}

	for (u32 i = 0; i < 3; i++)
	{
		for (s32 j = 0; j < 42; j++)
			ms_packet.addInt(j);

		ms_packet.addByte(0);

		for (s32 j = 0; j < 42; j++)
			ms_packet.addInt(j);
	}

	ms_packet.addInt(-1);

	ms_packet.addByte(1);
	for (s32 i = 0; i < 6; i++)
		ms_packet.addInt(i);

	ms_packet.addByte(0);
	for (s32 i = 0; i < 6; i++)
		ms_packet.addInt(i);

	/*ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addByte(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);*/

	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addInt(79);
	ms_packet.addInt(32);
	ms_packet.addInt(66);
	ms_packet.addInt(15);
	for (s32 i = 0; i < 141; i++)
		ms_packet.addInt(0);

	_finish();

#endif

#ifdef VERSION_13

	_startShared(t_obj->getId());

	_addPart(WCMD_SPAWN, t_obj->getId());

	ms_packet.addByte(5);
	ms_packet.addInt(t_char->getSex() == SEX_FEMALE ? 12 : 11);
	ms_packet.addByte(5);
	ms_packet.addShort(t_char->getSex() == SEX_FEMALE ? 12 : 11);
	ms_packet.addShort(t_obj->getSize());
	ms_packet.addCoordinates(t_obj->getPosition());
	ms_packet.addShort(t_obj->getRotation());
	ms_packet.addInt(t_obj->getId());
	ms_packet.addShort(0);
	ms_packet.addByte(1);
	ms_packet.addInt(230); //HP
	ms_packet.addInt(0); //motion
	ms_packet.addInt(1); //stance
	ms_packet.addByte(1);
	ms_packet.addString(t_char->getName());
	ms_packet.addShort(t_char->getSex());
	ms_packet.addByte(t_char->getHairType());
	ms_packet.addInt(t_char->getHairColor());
	ms_packet.addByte(t_char->getFaceType());
	ms_packet.addInt(t_char->getId());
	ms_packet.addByte(t_char->getJob());
	ms_packet.addShort(t_char->getStr());
	ms_packet.addShort(t_char->getSta());
	ms_packet.addShort(t_char->getDex());
	ms_packet.addShort(t_char->getInt());
	ms_packet.addShort(t_char->getLevel());
	ms_packet.addInt(-1);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addShort(t_acc->getAccessLevel());
	ms_packet.addByte(0);
	ms_packet.addShort(0x1002);
	ms_packet.addInt(0);
	ms_packet.addInt(502);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addInt(-1);
	for (u32 i = 0; i < 78; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(t_obj->getStat(DST_MP));
	ms_packet.addShort(t_obj->getStat(DST_FP));
	for (u32 i = 0; i < 48; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(0);


	/*for (u32 i = 0; i < 8; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(-1);
	for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(3);
	ms_packet.addInt(0x02030003);
	for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(9);
	ms_packet.addInt(5);
	for (u32 i = 0; i < 36; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(63); //MP
	ms_packet.addShort(32); //FP
	ms_packet.addInt(1); //Fluglvl
	ms_packet.addInt(0); //Flugexp
	ms_packet.addInt(t_char->getPenya()); //Penya
	ms_packet.addInt64(t_char->getExp());
	ms_packet.addInt(333); //??
	ms_packet.addInt(t_char->getSkillPoints());
	ms_packet.addInt(12800898); //??
	ms_packet.addInt(0);
	ms_packet.addInt(65); //??
	for (u32 i = 0; i < 32; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(1);
	ms_packet.addCoordinates(t_obj->getPosition());
	ms_packet.addShort(0); //collecting quest count
	ms_packet.addShort(0); //other quests
	ms_packet.addByte(0);
	ms_packet.addByte(0); //# of quests done
	for (u32 i = 0; i < 33; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(1);
	ms_packet.addInt(0);
	ms_packet.addInt(2);
	ms_packet.addInt(0);
	ms_packet.addInt(3);
	ms_packet.addInt(0);
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(-1);
		ms_packet.addInt(0);
	}
	ms_packet.addByte(0); //cheer points
	ms_packet.addInt(3600000); //cheer time oder so
	ms_packet.addByte(0 ? t_char->getPlace() : 0); //char slot
	ms_packet.addInt(0); //bank penya 1
	ms_packet.addInt(0); //2
	ms_packet.addInt(0); //3
	ms_packet.addInt(t_char->getId()); //bank char id
	ms_packet.addInt(0); //2
	ms_packet.addInt(0); //3
	ms_packet.addInt(0);
	ms_packet.addInt(0xffffff);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addByte(0);
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(i);
	}
	for (u32 i = 42; i < 73; ++i)
	{
		ms_packet.addInt(-1);
	}
	ms_packet.addByte(0);
	/*IItemPack *t_itemPack;
	for (u32 i = 0; i < 73; ++i)
	{
		t_itemPack = t_char->getInventory()->getItm(i).get();

		if (t_itemPack)
		{
			ms_packet.addByte(i);
			ms_packet.addInt(i); //unique item id
			ms_packet.addInt(t_itemPack->getData()->getId());
			ms_packet.addInt(rand());
			ms_packet.addInt(0); //Str: "sealed character name"
			ms_packet.addShort(t_itemPack->getCount());
			ms_packet.addByte(0); //"sealed character lvl"
			ms_packet.addInt(0x6ddd00); //durability
			ms_packet.addInt(0); //"sealed character job"
			ms_packet.addByte(0);
			ms_packet.addInt(t_itemPack->getUpgrade()); //upgrade
			ms_packet.addInt(0);
			ms_packet.addByte(t_itemPack->getElement()); //ele
			ms_packet.addByte((s8)t_itemPack->getElementalUpgrade()); //eleupgr
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
		}
	}*-/
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(i);
	}
	for (u32 i = 42; i < 73; ++i)
	{
		ms_packet.addInt(-1);
	}

	for (u32 i = 0; i < 3; ++i)
	{
		for (u32 j = 0; j < 42; ++j)
		{
			ms_packet.addInt(j);
		}

		ms_packet.addByte(0);

		for (u32 j = 0; j < 42; ++j)
		{
			ms_packet.addInt(j);
		}
	}

	ms_packet.addInt(-1);

	ms_packet.addByte(1);
	for (u32 i = 0; i < 6; ++i)
	{
		ms_packet.addInt(i);
	}
	ms_packet.addByte(0);
	for (u32 i = 0; i < 6; ++i)
	{
		ms_packet.addInt(i);
	}
	/*for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addInt(79);
	ms_packet.addInt(32);
	ms_packet.addInt(66);
	ms_packet.addInt(15);
	for (u32 i = 0; i < 141; ++i)
		ms_packet.addInt(0);*/

	_finish();

#endif

#ifdef VERSION_14
	CByteArray b;
	bool r = b.fromFile("begin.txt");
	assert(r);
	b.addByte(0);
	ms_packet.addHex(b.data());
	printf("%u bytes\n", ms_packet.size());
#endif

#ifdef VERSION_15
	_startShared(t_obj->getId());

	_addPart(WCMD_SPAWN, t_obj->getId());

	ms_packet.addByte(5);
	ms_packet.addInt(t_char->getSex() == SEX_FEMALE ? 12 : 11);
	ms_packet.addByte(5);
	ms_packet.addShort(t_char->getSex() == SEX_FEMALE ? 12 : 11);
	ms_packet.addShort(t_obj->getSize());
	ms_packet.addCoordinates(t_obj->getPosition());
	ms_packet.addShort(t_obj->getRotation());
	ms_packet.addInt(t_obj->getId());
	ms_packet.addShort(0);
	ms_packet.addByte(1);
	ms_packet.addInt(230); //HP
	ms_packet.addInt(0); //motion
	ms_packet.addInt(1); //stance
	ms_packet.addByte(1);
	ms_packet.addString(t_char->getName());
	ms_packet.addShort(t_char->getSex());
	ms_packet.addByte(t_char->getHairType());
	ms_packet.addInt(t_char->getHairColor());
	ms_packet.addByte(t_char->getFaceType());
	ms_packet.addInt(t_char->getId());
	ms_packet.addByte(t_char->getJob());
	ms_packet.addShort(t_char->getStr());
	ms_packet.addShort(t_char->getSta());
	ms_packet.addShort(t_char->getDex());
	ms_packet.addShort(t_char->getInt());
	ms_packet.addShort(t_char->getLevel());
	ms_packet.addInt(-1);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addShort(t_acc->getAccessLevel());
	ms_packet.addByte(0);
	ms_packet.addShort(0x1002);
	ms_packet.addInt(0);
	ms_packet.addInt(502);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addInt(-1);
	for (u32 i = 0; i < 78; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(t_obj->getStat(DST_MP));
	ms_packet.addShort(t_obj->getStat(DST_FP));
	for (u32 i = 0; i < 48; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(0);


	/*for (u32 i = 0; i < 8; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(-1);
	for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(3);
	ms_packet.addInt(0x02030003);
	for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(9);
	ms_packet.addInt(5);
	for (u32 i = 0; i < 36; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(63); //MP
	ms_packet.addShort(32); //FP
	ms_packet.addInt(1); //Fluglvl
	ms_packet.addInt(0); //Flugexp
	ms_packet.addInt(t_char->getPenya()); //Penya
	ms_packet.addInt64(t_char->getExp());
	ms_packet.addInt(333); //??
	ms_packet.addInt(t_char->getSkillPoints());
	ms_packet.addInt(12800898); //??
	ms_packet.addInt(0);
	ms_packet.addInt(65); //??
	for (u32 i = 0; i < 32; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(1);
	ms_packet.addCoordinates(t_obj->getPosition());
	ms_packet.addShort(0); //collecting quest count
	ms_packet.addShort(0); //other quests
	ms_packet.addByte(0);
	ms_packet.addByte(0); //# of quests done
	for (u32 i = 0; i < 33; ++i)
		ms_packet.addInt(0);
	ms_packet.addInt(1);
	ms_packet.addInt(0);
	ms_packet.addInt(2);
	ms_packet.addInt(0);
	ms_packet.addInt(3);
	ms_packet.addInt(0);
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(-1);
		ms_packet.addInt(0);
	}
	ms_packet.addByte(0); //cheer points
	ms_packet.addInt(3600000); //cheer time oder so
	ms_packet.addByte(0 ? t_char->getPlace() : 0); //char slot
	ms_packet.addInt(0); //bank penya 1
	ms_packet.addInt(0); //2
	ms_packet.addInt(0); //3
	ms_packet.addInt(t_char->getId()); //bank char id
	ms_packet.addInt(0); //2
	ms_packet.addInt(0); //3
	ms_packet.addInt(0);
	ms_packet.addInt(0xffffff);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addByte(0);
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(i);
	}
	for (u32 i = 42; i < 73; ++i)
	{
		ms_packet.addInt(-1);
	}
	ms_packet.addByte(0);
	/*IItemPack *t_itemPack;
	for (u32 i = 0; i < 73; ++i)
	{
		t_itemPack = t_char->getInventory()->getItm(i).get();

		if (t_itemPack)
		{
			ms_packet.addByte(i);
			ms_packet.addInt(i); //unique item id
			ms_packet.addInt(t_itemPack->getData()->getId());
			ms_packet.addInt(rand());
			ms_packet.addInt(0); //Str: "sealed character name"
			ms_packet.addShort(t_itemPack->getCount());
			ms_packet.addByte(0); //"sealed character lvl"
			ms_packet.addInt(0x6ddd00); //durability
			ms_packet.addInt(0); //"sealed character job"
			ms_packet.addByte(0);
			ms_packet.addInt(t_itemPack->getUpgrade()); //upgrade
			ms_packet.addInt(0);
			ms_packet.addByte(t_itemPack->getElement()); //ele
			ms_packet.addByte((s8)t_itemPack->getElementalUpgrade()); //eleupgr
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
		}
	}*/
	for (u32 i = 0; i < 42; ++i)
	{
		ms_packet.addInt(i);
	}
	for (u32 i = 42; i < 73; ++i)
	{
		ms_packet.addInt(-1);
	}

	for (u32 i = 0; i < 3; ++i)
	{
		for (u32 j = 0; j < 42; ++j)
		{
			ms_packet.addInt(j);
		}

		ms_packet.addByte(0);

		for (u32 j = 0; j < 42; ++j)
		{
			ms_packet.addInt(j);
		}
	}

	ms_packet.addInt(-1);

	ms_packet.addByte(1);
	for (u32 i = 0; i < 6; ++i)
	{
		ms_packet.addInt(i);
	}
	ms_packet.addByte(0);
	for (u32 i = 0; i < 6; ++i)
	{
		ms_packet.addInt(i);
	}
	/*for (u32 i = 0; i < 9; ++i)
		ms_packet.addInt(0);
	ms_packet.addShort(0);
	ms_packet.addInt(79);
	ms_packet.addInt(32);
	ms_packet.addInt(66);
	ms_packet.addInt(15);
	for (u32 i = 0; i < 141; ++i)
		ms_packet.addInt(0);*/


	_finish();

	CByteArray b;
	bool r = b.fromFile("begin.txt");
	assert(r);
	b.addByte(0);
	ms_packet.addHex(b.data());
	printf("%u bytes\n", ms_packet.size());

#endif

	return ms_packet;
}

const CByteArray &IPacketCreator::weatherAuto(E_WEATHER _weather)
{
	switch (_weather)
	{
	case WEATHER_SNOW:
		return weatherSnow();

	case WEATHER_RAIN:
		return weatherRain();

	default:
		return weatherNormal();
	}
}

const CByteArray &IPacketCreator::weatherNormal()
{
	_startShared(0);

	_addPart(WCMD_WEATHER_NORMAL, -1);

	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::weatherSnow()
{
	_startShared(0);

	_addPart(WCMD_WEATHER_SNOW, -1);

	ms_packet.addInt(1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::weatherRain()
{
	_startShared(0);

	_addPart(WCMD_WEATHER_RAIN, -1);

	ms_packet.addInt(1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::notice(const char *_text)
{
	_start(WCMD_NOTICE);

	ms_packet.addString(_text);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::chat(ID _senderId, const char *_text)
{
	_startShared(_senderId);

	_addPart(WCMD_LOCAL_CHAT, _senderId);

	ms_packet.addString(_text);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::shout(ID _senderId, const char *_name, const char *_text, s32 _color)
{
	_startShared(0);

	_addPart(WCMD_SHOUT, -1);

	ms_packet.addInt(_senderId);
	ms_packet.addString(_name);
	ms_packet.addString(_text);
	ms_packet.addInt(_color);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::greenText(const char *_text)
{
	_startShared(0);

	_addPart(WCMD_GREEN_TEXT, -1);

	ms_packet.addByte(1);
	ms_packet.addString(_text);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::privateMessage(IWorldPlayer *_from, IWorldPlayer *_to, const char *_text)
{
	FDASSERT(_from);
	FDASSERT(_text);

	_start(WCMD_PRIVATE_MESSAGE);

	ms_packet.addString(_from->getCharacter()->getName());
	if (_to)
	{
		ms_packet.addString(_to->getCharacter()->getName());
	}
	else
	{
		ms_packet.addInt(0);
	}
	ms_packet.addString(_text);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::gameInfo(const PlayerObjectPtr &_obj, E_GAME_TEXT _type, const char *_text)
{
	_startShared(0);

	_addPart(WCMD_INFO_TEXT, _obj->getId());

	ms_packet.addInt(_type);
	ms_packet.addString(_text);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::gameInfo(const PlayerObjectPtr &_obj, E_GAME_TEXT _type)
{
	_startShared(0);

	_addPart(WCMD_INFO_TEXT, _obj->getId());

	ms_packet.addInt(_type);
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::spawn(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	_startShared(0);

	switch (_object->getType())
	{
	case IWorldObject::TYPE_MOB:
		{
			MobObjectPtr t_mob = boost::dynamic_pointer_cast<IMobObject>(_object);

			_addPart(WCMD_SPAWN, t_mob->getId());

			ms_packet.addByte(5);
			ms_packet.addInt(t_mob->getMover()->getId());
			ms_packet.addByte(5);
			ms_packet.addShort(t_mob->getMover()->getId());
			ms_packet.addShort(t_mob->getSize());

			//force the mob to spawn on the ground
			ms_packet.addCoordinates(t_mob->getPosition());
			ms_packet.addShort(t_mob->getRotation());

			//ms_packet.addInt(t_mob->getId());
			//ms_packet.addShort(5);
			_addPart(E_WORLD_COMMAND(5), t_mob->getId());

			ms_packet.addByte(0);
			ms_packet.addInt(t_mob->getStat(DST_HP)); //HP
			ms_packet.addInt(0); //Motion
			ms_packet.addInt(0); //Stance
			ms_packet.addShort(0x0b);
			ms_packet.addInt(-1);
			ms_packet.addShort(0);
			ms_packet.addByte(t_mob->isAggressive()); //aggro
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addShort(0x3f80);
			ms_packet.addInt(0);

			break;
		}

	case IWorldObject::TYPE_DROP:
		{
			DropObjectPtr t_drop = boost::dynamic_pointer_cast<IDropObject>(_object);
			IItemProperties &t_item = t_drop->getItem();

			FDASSERT(t_item.isValid());

			_addPart(WCMD_SPAWN, t_drop->getId());

			/*
					ms_packet.addByte(i);
					ms_packet.addInt(i); //unique item id
					ms_packet.addInt(t_itemPack->getData()->getId());
					ms_packet.addInt(0);
					ms_packet.addInt(0); //Str: "sealed character name"
					ms_packet.addShort(t_itemPack->getCount());
					ms_packet.addByte(0); //"sealed character lvl"
					ms_packet.addInt(0x6ddd00); //durability
					ms_packet.addInt(0); //"sealed character job"
					ms_packet.addByte(0);
					ms_packet.addInt(t_itemPack->getUpgrade()); //upgrade
					ms_packet.addInt(0);
					ms_packet.addByte(t_itemPack->getElement()); //ele
					ms_packet.addInt(t_itemPack->getElementalUpgrade()); //eleupgr
					ms_packet.addInt(0);
					ms_packet.addInt(t_itemPack->getSlotCount());
					for (u32 j = 0; j < t_itemPack->getSlotCount(); ++j)
					{
						ms_packet.addInt(t_itemPack->getSlot(j)->getId());
					}
					ms_packet.addInt(0);
					ms_packet.addInt(0);
					ms_packet.addInt64(t_itemPack->getSpecialOption().getCode());
					ms_packet.addByte(0);
					ms_packet.addInt(0);
			*/

			ms_packet.addByte(4);
			ms_packet.addInt(t_item.getData()->getId());
			ms_packet.addByte(4);
			ms_packet.addShort(t_item.getData()->getId());
			ms_packet.addShort(t_drop->getSize()); //Größe
			ms_packet.addCoordinates(t_drop->getPosition());
			ms_packet.addShort(0);
			ms_packet.addInt(t_drop->getId());
			ms_packet.addInt(-1);
			ms_packet.addInt(t_item.getData()->getId());
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(t_item.getCount());
			ms_packet.addInt(0x6ddd);
			ms_packet.addInt(0);
			ms_packet.addInt(t_item.getUpgrade());
			ms_packet.addInt(0);
			ms_packet.addByte(t_item.getElement());
			ms_packet.addInt(t_item.getElementalUpgrade());
			ms_packet.addInt(0);
			ms_packet.addInt(t_item.getSlotCount());
			for (u32 i = 0; i < t_item.getSlotCount(); ++i)
			{
				ms_packet.addInt(t_item.getSlot(i)->getId());
			}
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt64(t_item.getSpecialOption().getCode());
			ms_packet.addShort(0);

			break;
		}

	case IWorldObject::TYPE_PLAYER:
		{
			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(_object);

			const CharacterPtr &t_char = t_player->getPlayer()->getCharacter();

			_addPart(WCMD_SPAWN, t_player->getCharacter()->getId());

			ms_packet.addByte(5);
			ms_packet.addInt(t_player->getPlayer()->getCharacter()->getSex() == SEX_MALE ? 11 : 12); //model
			ms_packet.addByte(5);
			ms_packet.addShort(t_player->getPlayer()->getCharacter()->getSex() == SEX_MALE ? 11 : 12); //model
			ms_packet.addShort(t_player->getSize());
			ms_packet.addCoordinates(t_player->getPosition());
			ms_packet.addShort(t_player->getRotation());
			ms_packet.addInt(t_player->getId()); //ID
			ms_packet.addShort(0); //0
			ms_packet.addByte(1);
			ms_packet.addInt(t_player->getStat(DST_HP)); //HP
			ms_packet.addInt(0); //Motion, 0x5004 = vorw.laufen, 5 = rückw.
			ms_packet.addInt(0); //Stance
			ms_packet.addByte(1);
			ms_packet.addString(t_char->getName()); //name
			ms_packet.addShort(t_char->getSex());
			ms_packet.addByte(t_char->getHairType());
			ms_packet.addInt(t_char->getHairColor()); //Haarfarbe
			ms_packet.addByte(t_char->getFaceType()); //Gesicht
			ms_packet.addInt(t_player->getId());
			ms_packet.addByte(t_char->getJob());
			ms_packet.addShort(t_char->getStr());
			ms_packet.addShort(t_char->getSta());
			ms_packet.addShort(t_char->getDex());
			ms_packet.addShort(t_char->getInt());
			ms_packet.addShort(t_char->getLevel());
			ms_packet.addInt(-1);
			ms_packet.addInt(0);
			ms_packet.addByte(0);
			ms_packet.addInt(0);
			ms_packet.addByte(0);
			ms_packet.addByte(t_player->getPlayer()->getAccount()->getAccessLevel());
			ms_packet.addInt(t_player->getFlags());
			ms_packet.addInt(0);
			ms_packet.addInt(0x1f8);
			ms_packet.addInt(0);
			ms_packet.addInt(t_player->getCharacter()->getPkPoints()); //Karma
			ms_packet.addInt(t_player->getCharacter()->getDisposition()); //Disposition
			ms_packet.addInt(0);
			ms_packet.addInt(t_player->getCharacter()->getPvpPoints()); //Reputation

			ms_packet.addByte(0);

			IInventory *t_inv = t_player->getInventory();

			s32 t_equipCount = 0;
			for (u32 i = 42; i < 73; ++i)
			{
				if (!t_inv->getSlot(i).isEmpty())
				{
					ms_packet.addByte(static_cast<Byte>(t_inv->getSlot(i).getItem()->getUpgrade()));
					ms_packet.addByte(0);
					ms_packet.addByte(static_cast<Byte>(t_inv->getSlot(i).getItem()->getElement()));
					ms_packet.addByte(static_cast<Byte>(t_inv->getSlot(i).getItem()->getElementalUpgrade()));

					++t_equipCount;
				}
				else
				{
					ms_packet.addInt(0);
				}
			}

			for (s32 i = 0; i < 28; ++i)
			{
				ms_packet.addInt(0);
			}

			ms_packet.addByte(t_equipCount);

			for (s32 i = 42; i < 73; ++i)
			{
				if (!t_inv->getSlot(i).isEmpty())
				{
					ms_packet.addByte(i - 42);
					ms_packet.addShort(t_inv->getSlot(i).getItem()->getData()->getId());
					ms_packet.addByte(0);
				}
			}

			break;
		}

	case IWorldObject::TYPE_NPC:
		{
			NpcObjectPtr t_npc = boost::dynamic_pointer_cast<INpcObject>(_object);

			//Log::write(LOG_DEBUG, "Npc Spawn %d %d %s", t_npc->getId(), t_npc->getData()->getMover()->getId(),
			//	t_npc->getData()->getName());

			_addPart(WCMD_SPAWN, t_npc->getId());

			ms_packet.addByte(5);
			ms_packet.addInt(t_npc->getData()->getMover()->getId());
			ms_packet.addByte(5);
			ms_packet.addShort(t_npc->getData()->getMover()->getId());
			ms_packet.addShort(t_npc->getSize());
			ms_packet.addCoordinates(t_npc->getPosition());
			ms_packet.addShort(t_npc->getRotation());
			ms_packet.addInt(t_npc->getId());

			/*
			ms_packet.addByte(1);
			ms_packet.addShort(0);
			ms_packet.addInt(-1);
			ms_packet.addInt(1);
			ms_packet.addInt(0);
			ms_packet.addByte(1);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addShort(0);
			ms_packet.addString(t_npc->getData()->getName());
			ms_packet.addInt(0x3f800000);
			ms_packet.addInt(0);
			*/

			ms_packet.addShort(0); //action
			ms_packet.addByte(0);
			ms_packet.addInt(1);
			ms_packet.addInt(1);
			ms_packet.addInt(0);
			ms_packet.addInt(1);
			ms_packet.addByte(0);
			ms_packet.addByte(0);
			ms_packet.addByte(0);
			ms_packet.addString(t_npc->getData()->getName());
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addShort(0);
			ms_packet.addInt(0x3f80);
			ms_packet.addShort(0);

			break;
		}

	default:
		{
			debug_error("Invalid object type (id: %d", _object->getType());
		}
	};

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::despawn(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	//Log::write(LOG_DEBUG, "Despawning object #%d (type: %u)", _object->getId(), _object->getType());

	_startShared(0);

	_addPart(WCMD_DESPAWN, _object->getId());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::positionUpdate(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	_startShared(0);

	_addPart(WCMD_TELEPORT, _object->getId());

	ms_packet.addCoordinates(_object->getPosition());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::worldPosUpdate(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	_startShared(0);

	_addPart(WCMD_TELEPORT_WORLD, _object->getId());

	ms_packet.addInt(_object->getWorld()->getId());
	ms_packet.addCoordinates(_object->getPosition());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::objectWalking(const MovingObjectPtr &_obj)
{
	FDASSERT(_obj);

	//Log::write(LOG_DEBUG, "Walking object #%d (type: %u)", _object->getId(), _object->getType());

	_startShared(0);

	_addPart(WCMD_OBJECT_WALK, _obj->getId());

	ms_packet.addCoordinates(_obj->getPosition()); //Target pos
	ms_packet.addByte(1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::follow(const MovingObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_OBJECT_FOLLOW, _obj->getId());

	ms_packet.addInt(_obj->getFollowed()->getId());
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::damage(const WorldObjectPtr &_attacker, const WorldObjectPtr &_target, s32 _damage,
										 s32 _flags)
{
	FDASSERT(_attacker);
	FDASSERT(_target);

	_startShared(0);

	_addPart(WCMD_DAMAGE, _target->getId());

	ms_packet.addInt(_attacker->getId());
	ms_packet.addInt(_damage);
	ms_packet.addInt(_flags);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::attack(const CreaturePtr &_attacker, const CreaturePtr &_target, s32 _motion)
{
	FDASSERT(_attacker);
	FDASSERT(_target);

	_startShared(0);

	_addPart(WCMD_ATTACK_MOTION, _attacker->getId());

	ms_packet.addInt(_motion);
	ms_packet.addInt(_target->getId());
	ms_packet.addInt(0);
	ms_packet.addInt(0x10000);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::objectDeath(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	_startShared(0);

	_addPart(WCMD_OBJECT_DEATH, _object->getId());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::flags(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_FLAGS, _obj->getId());

	ms_packet.addInt(_obj->getFlags());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateFace(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_UPDATE_FACE, _obj->getId());

	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getId());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getFaceType());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateHair(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_UPDATE_HAIR, _obj->getId());

	ms_packet.addByte(_obj->getPlayer()->getCharacter()->getHairType());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getHairColor());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::motion(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_MOTION, _obj->getId());

	ms_packet.addInt(_obj->getMotion());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::gfxEffect(const PlayerObjectPtr &_obj, ID _effectId)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_GFX_EFFECT, _obj->getId());

	ms_packet.addInt(_effectId);
	ms_packet.addCoordinates(_obj->getPosition());
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::skillMotion(const PlayerObjectPtr &_user,
											  const PlayerObjectPtr &_target,
											  ID _skillId,
											  s32 _level,
											  s32 _type)
{
	FDASSERT(_user);
	FDASSERT(_target);

	_startShared(0);

	_addPart(WCMD_SKILL_MOTION, _user->getId());

	ms_packet.addInt(_skillId);
	ms_packet.addInt(_level);
	ms_packet.addInt(_target->getId());
	ms_packet.addInt(0);
	ms_packet.addInt(_type);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::buff(const PlayerObjectPtr &_target, ID _skillId, s32 _level, TimeMs _duration)
{
	FDASSERT(_target);

	_startShared(0);

	_addPart(WCMD_BUFF, _target->getId());

	ms_packet.addInt(_target->getId());
	ms_packet.addShort(1);
	ms_packet.addShort(_skillId);
	ms_packet.addInt(_level);
	ms_packet.addInt(_duration);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::increaseAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount)
{
	FDASSERT(_obj);

	_startShared(0);
	_addPart(WCMD_INCREASE_ATTRIBUTE, _obj->getId());

	ms_packet.addInt(_stat >= DST_GOLD ? _stat + 9900 : _stat);
	ms_packet.addInt(_amount);
	ms_packet.addInt(-1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::decreaseAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount)
{
	FDASSERT(_obj);

	_startShared(0);
	_addPart(WCMD_DECREASE_ATTRIBUTE, _obj->getId());

	ms_packet.addInt(_stat >= DST_GOLD ? _stat + 9900 : _stat);
	ms_packet.addInt(_amount);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount)
{
	FDASSERT(_obj);

	_startShared(0);
	_addPart(WCMD_UPDATE_ATTRIBUTE, _obj->getId());

	ms_packet.addInt(_stat >= DST_GOLD ? _stat + 9900 : _stat);
	ms_packet.addInt(_amount);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateAttribute(const CreaturePtr &_obj, E_STAT _stat)
{
	FDASSERT(_obj);

	_startShared(0);
	_addPart(WCMD_UPDATE_ATTRIBUTE, _obj->getId());

	ms_packet.addInt(_stat >= DST_GOLD ? _stat + 9900 : _stat);
	ms_packet.addInt(_obj->getStat(_stat));

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::levelInfos(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_LEVEL_INFOS, _obj->getId());

	ms_packet.addInt64(_obj->getPlayer()->getCharacter()->getExp());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getLevel());
	ms_packet.addShort(0);
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getSkillPoints());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::statInfos(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_STAT_INFOS, _obj->getId());

	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getStr());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getSta());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getDex());
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getInt());
	ms_packet.addInt(0);
	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getStatPoints());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::statPoints(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_STAT_POINTS, _obj->getId());

	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getStatPoints());
	ms_packet.addShort(0);
	ms_packet.addByte(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::job(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_JOB, _obj->getId());

	ms_packet.addInt(_obj->getPlayer()->getCharacter()->getJob());

	ms_packet.addInt(1);
	ms_packet.addInt(0);
	ms_packet.addInt(2);
	ms_packet.addInt(0);
	ms_packet.addInt(3);
	ms_packet.addInt(0);
	for (u32 i = 0; i < 55; i++)
	{
		ms_packet.addInt(-1);
		ms_packet.addInt(0);
	}

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::skillTree(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_SKILL_TREE, _obj->getId());

	ms_packet.addInt(0);

	//...

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::changeName(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_start(WCMD_NAME);

	ms_packet.addInt(_obj->getCharacter()->getId());
	ms_packet.addString(_obj->getCharacter()->getName());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::characterInfos(const CharacterPtr &_char)
{
	FDASSERT(_char);

	_startShared(0);

	_addPart(WCMD_CHARACTER_INFOS, -1);

	ms_packet.addInt(_char->getId());
	ms_packet.addString(_char->getName());
	ms_packet.addByte(0); //sex?
	ms_packet.addByte(1); //job?
	ms_packet.addShort(1);
	ms_packet.addInt(17); //level?
	ms_packet.addInt(1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::mailBox(IPostBox *_post)
{
	FDASSERT(_post);

	_startShared(0);

	_addPart(WCMD_MAILBOX, _post->getOwner()->getId());

	ms_packet.addInt(_post->getOwner()->getCharacter()->getId());
	ms_packet.addInt(_post->getMailCount()); //number

	for (u32 i = 0; i < _post->getMailCount(); ++i)
	{
		const MailPtr &t_mail = _post->getMail(i);

		ms_packet.addInt(t_mail->getId()); //id
		ms_packet.addInt(t_mail->getSender()->getId());

		ms_packet.addByte(0); //no item
		ms_packet.addInt(t_mail->getMoney()); //money
		ms_packet.addInt(static_cast<s32>(CTime::seconds() - t_mail->getTime())); //delta time
		ms_packet.addByte(t_mail->isRead()); //read
		ms_packet.addString(t_mail->getTitle());
		ms_packet.addString(t_mail->getContent());
	}

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::pvpPoints(const PlayerObjectPtr &_pObj)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_PVP_POINTS, _pObj->getId());

	ms_packet.addInt(_pObj->getCharacter()->getPvpPoints());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::revival(const PlayerObjectPtr &_pObj)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_REVIVAL, _pObj->getId());

	_finish();

	return ms_packet;
}

/*const CByteArray &IPacketCreator::karma(const PlayerObjectPtr &_pObj)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_KARMA, _pObj->getId());

	printf("pk: %d, disp: %d\n",
		_pObj->getCharacter()->getPkPoints(),
		_pObj->getCharacter()->getDisposition());

	ms_packet.addInt(_pObj->getCharacter()->getPkPoints());
	ms_packet.addInt(_pObj->getCharacter()->getDisposition());

	_finish();

	return ms_packet;
}*/

const CByteArray &IPacketCreator::mailUpdate(const PlayerObjectPtr &_obj, ID _mail, E_MAIL_UPDATE _type)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_MAIL_UPDATE, _obj->getId());

	ms_packet.addInt(_mail);
	ms_packet.addInt(_type);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::openShop(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_PLAYER_SHOP_OPEN, _obj->getId());

	ms_packet.addString("::shop::");

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::closeShop(const PlayerObjectPtr &_obj)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_PLAYER_SHOP_CLOSE, _obj->getId());

	ms_packet.addInt(1);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::addItemToShop(const PlayerObjectPtr &_obj, u32 _shopSlot)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_PLAYER_SHOP_ADD, _obj->getId());

	ms_packet.addShort(0); //to
	ms_packet.addByte(0); //from
	ms_packet.addShort(1); //count
	ms_packet.addInt(123456789); //price

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::shopChat(const PlayerObjectPtr &_obj, const char *_message)
{
	FDASSERT(_obj);

	_startShared(0);

	_addPart(WCMD_SHOP_CHAT, _obj->getId());

	ms_packet.addInt(_obj->getId());
	ms_packet.addString(_message);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::moveItem(const PlayerObjectPtr &_pObj, u32 _oldSlot, u32 _newSlot)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_INVENTORY_MOVE_ITEM, _pObj->getId());

	ms_packet.addByte(0);
	ms_packet.addByte(_newSlot);
	ms_packet.addByte(_oldSlot);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::addItem(const PlayerObjectPtr &_pObj, u32 _slot)
{
	FDASSERT(_pObj);

	IItemSlot &t_slot = _pObj->getInventory()->getSlot(_slot);
	const ItemPackPtr &t_item = t_slot.getItem();

	_startShared(0);

	_addPart(WCMD_INVENTORY_ADD_ITEM, _pObj->getId());

	ms_packet.addByte(0);
	ms_packet.addInt(-1);

	ms_packet.addInt(t_item->getData()->getId());
	ms_packet.addInt(t_item->getId());
	ms_packet.addInt(0);
	ms_packet.addShort(t_item->getCount());
	ms_packet.addByte(0);
	ms_packet.addInt(-1);
	ms_packet.addInt(0);
	ms_packet.addByte(0);
	ms_packet.addInt(t_item->getUpgrade());
	ms_packet.addInt(0);
	ms_packet.addByte(t_item->getElement());
	ms_packet.addInt(t_item->getElementalUpgrade());
	ms_packet.addInt(0);
	ms_packet.addInt(t_item->getSlotCount());
	for (u32 j = 0; j < t_item->getSlotCount(); ++j)
	{
		ms_packet.addInt(t_item->getSlot(j)->getId());
	}
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt64(t_item->getSpecialOption().getCode());
	ms_packet.addInt(0);
	ms_packet.addByte(0);

	ms_packet.addByte(1);
	ms_packet.addByte(t_slot.getId());
	ms_packet.addByte(t_item->getCount());
	ms_packet.addByte(0);

	printf("add slot id: %d\n", t_slot.getId());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateItem(const PlayerObjectPtr &_pObj,
											 u32 _slot,
											 E_ITEM_UPDATE_TYPE _type,
											 s32 _data,
											 s32 _card)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_INVENTORY_UPDATE_ITEM, _pObj->getId());

	IItemSlot &t_slot = _pObj->getInventory()->getSlot(_slot);

	ms_packet.addByte(0);
	ms_packet.addByte(t_slot.getId()); //id
	ms_packet.addByte(_type); //update type
	ms_packet.addShort(_data); //data
	ms_packet.addShort(_card); //card socket

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::updateSpcOption(const PlayerObjectPtr &_pObj,
												  u32 _slot)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_SPECIAL_OPTION, _pObj->getId());

	IItemSlot &t_slot = _pObj->getInventory()->getSlot(_slot);

	FDASSERT(t_slot.getItem());

	ms_packet.addByte(t_slot.getId()); //id
	ms_packet.addByte(10);
	ms_packet.addInt64(t_slot.getItem()->getSpecialOption().getCode());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::moveEquip(const PlayerObjectPtr &_pObj,
											const IItemSlot &_slot,
											u32 _toSlot,
											bool _equip)
{
	FDASSERT(_pObj);

	_startShared(0);

	_addPart(WCMD_MOVE_EQUIP, _pObj->getId());

	ms_packet.addByte(_slot.getId());
	ms_packet.addInt(0);
	ms_packet.addByte(_equip);
	ms_packet.addInt(_slot.getItem() ? _slot.getItem()->getData()->getId() : 0);
	ms_packet.addInt(_slot.getItem() ? _slot.getItem()->getUpgrade() : 0);
	ms_packet.addInt(_slot.getItem() ? _slot.getItem()->getElement() : 0);
	ms_packet.addInt(_slot.getItem() ? _slot.getItem()->getElementalUpgrade() : 0);
	ms_packet.addInt(0);
	ms_packet.addInt(_toSlot);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcShop(const NpcObjectPtr &_npc)
{
	FDASSERT(_npc);

	_startShared(0);

	_addPart(WCMD_NPC_SHOP, _npc->getId());

	s32 j, k;
	u32 l;

	for (u32 i = 0; i < INpcData::SHOP_PAGE_COUNT; i++)
	{
		//0-99 hinzufügen
		for (j = 0; j < 100; j++)
		{
			ms_packet.addInt(j);
		}

		ms_packet.addByte(_npc->getData()->getShopItemCount(i)); //Item-Anzahl

		//Items
		for (l = 0; l < _npc->getData()->getShopItemCount(i); l++)
		{
			ms_packet.addByte(s8(l));
			ms_packet.addInt(l);

			ms_packet.addInt(_npc->getData()->getShopItem(i, l).getData()->getId()); //ID
			ms_packet.addInt(0);
			ms_packet.addInt(0);
			ms_packet.addInt(_npc->getData()->getShopItem(i, l).getData()->getStackSize()); //max Anzahl
			ms_packet.addInt(0x249f);
			for (k = 0; k < 11; k++)
				ms_packet.addInt(0);
			ms_packet.addShort(0);
		}

		//0-99 hinzufügen
		for (j = 0; j < 100; j++)
		{
			ms_packet.addInt(j);
		}
	}

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcDialogClear(const NpcObjectPtr &_npc)
{
	FDASSERT(_npc);

	_startShared(0);

	_addPart(WCMD_NPC_DIALOG, _npc->getId());
	ms_packet.addShort(0x1d);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcDialogClose(const NpcObjectPtr &_npc)
{
	FDASSERT(_npc);

	_startShared(0);

	_addPart(WCMD_NPC_DIALOG, _npc->getId());
	ms_packet.addShort(0x16);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcDialogText(const NpcObjectPtr &_npc, const char *_text)
{
	FDASSERT(_npc);
	FDASSERT(_text);

	_startShared(0);

	_addPart(WCMD_NPC_DIALOG, _npc->getId());
	ms_packet.addShort(0x12);
	ms_packet.addString(_text);
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcDialogLink(const NpcObjectPtr &_npc, const char *_text, const char *_internal,
												s32 _action1, s32 _action2)
{
	FDASSERT(_npc);
	FDASSERT(_text);
	FDASSERT(_internal);

	_startShared(0);

	_addPart(WCMD_NPC_DIALOG, _npc->getId());
	ms_packet.addShort(0x10);
	ms_packet.addString(_text); //"Bye!"
	ms_packet.addString(_internal); //"BUTTON_BYE"
	ms_packet.addInt(_action1);
	ms_packet.addInt(_action2);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::npcDialogButton(const NpcObjectPtr &_npc, const char *_text, const char *_internal,
												  s32 _action1, s32 _action2)
{
	FDASSERT(_npc);
	FDASSERT(_text);
	FDASSERT(_internal);

	_startShared(0);

	_addPart(WCMD_NPC_DIALOG, _npc->getId());
	ms_packet.addShort(0x13);
	ms_packet.addString(_text); //"__YES__"
	ms_packet.addString(_internal); //"BTN_ADD_QUEST"
	ms_packet.addInt(_action1);
	ms_packet.addInt(_action2);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::partyInvitation(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_invitee)
{
	FDASSERT(_leader);
	FDASSERT(_invitee);

	_startShared(0);

	_addPart(WCMD_PARTY_INVITATION, _invitee->getId());

	ms_packet.addInt(_leader->getCharacter()->getId());
	ms_packet.addInt(1); //lvl
	ms_packet.addInt(0); //job
	ms_packet.addByte(0); ///gender

	ms_packet.addInt(_invitee->getCharacter()->getId());
	ms_packet.addInt(1); //lvl
	ms_packet.addInt(0); //job
	ms_packet.addByte(0); //gender

	ms_packet.addString(_leader->getCharacter()->getName());
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::partyRejection(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_invitee)
{
	FDASSERT(_leader);
	FDASSERT(_invitee);

	_startShared(0);

	_addPart(WCMD_PARTY_REJECTION, _leader->getId());
	ms_packet.addInt(_leader->getCharacter()->getId());
	ms_packet.addInt(_invitee->getCharacter()->getId());
	ms_packet.addInt(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::partyUpdate(const PlayerObjectPtr &_receiver,
											  const PlayerObjectPtr &_asker,
											  const PlayerObjectPtr &_target,
											  PartyPtr &_party)
{
	FDASSERT(_receiver);
	FDASSERT(_asker);
	FDASSERT(_target);
	FDASSERT(_party);

	_startShared(0);

	_addPart(WCMD_PARTY_UPDATE, _receiver->getId());

	ms_packet.addInt(_target->getCharacter()->getId());
	ms_packet.addString(_asker->getCharacter()->getName());
	ms_packet.addString(_target->getCharacter()->getName());

	ms_packet.addInt(_party->getMemberCount());
	ms_packet.addInt(_party->getId());
	ms_packet.addInt(_party->isAdvanced());
	ms_packet.addInt(_party->getMemberCount());
	ms_packet.addInt(_party->getLevel());
	ms_packet.addInt(_party->getExp());
	ms_packet.addInt(_party->getPoints());
	ms_packet.addInt(0); //exp: 0=level, 1=contribution
	ms_packet.addInt(0); //item: 0=individually, 1=sequentially, 2=manually, 3=randomly
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	ms_packet.addInt(0);
	if (_party->isAdvanced())
	{
		ms_packet.addString(_party->getName());
	}
	for (u32 i = 0; i < _party->getMemberCount(); ++i)
	{
		ms_packet.addInt(_party->getMember(i)->getCharacter()->getId());
		ms_packet.addInt(0); //net status
	}

	_finish();

	ms_packet.saveFormatted("_partyUpdate.txt");

	return ms_packet;
}

const CByteArray &IPacketCreator::partyDisband(const PlayerObjectPtr &_member)
{
	FDASSERT(_member);

	_startShared(0);

	_addPart(WCMD_PARTY_DISBAND, _member->getId());
	ms_packet.addInt(0);
	ms_packet.addShort(0);

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::partyTransfer(const PlayerObjectPtr &_member, const PlayerObjectPtr &_leader)
{
	FDASSERT(_member);
	FDASSERT(_leader);

	_startShared(0);

	_addPart(WCMD_PARTY_TRANSFER, _member->getId());
	ms_packet.addInt(_leader->getCharacter()->getId());

	_finish();

	return ms_packet;
}

const CByteArray &IPacketCreator::partyLevel(PartyPtr &_party)
{
	FDASSERT(_party);

	_startShared(0);

	_addPart(WCMD_PARTY_LEVEL, -1);
	ms_packet.addInt(_party->getExp());
	ms_packet.addInt(_party->getLevel());
	ms_packet.addInt(_party->getPoints());

	_finish();

	return ms_packet;
}

void IPacketCreator::_start(s32 _cmd)
{
	ms_packet.clear();

	ms_packet.addByte(NET_PACKET_BEGIN);
	ms_packet.addInt(0); //size
	ms_packet.addInt(_cmd);
}

void IPacketCreator::_startShared(ID _id, u32 cmd)
{
	ms_packet.clear();

	ms_packet.addByte(NET_PACKET_BEGIN);
	ms_packet.addInt(0); //size
	ms_packet.addInt(cmd);

	ms_packet.addInt(_id);
	ms_packet.addShort(0); //part count
}

void IPacketCreator::_addPart(E_WORLD_COMMAND _cmd, ID _id)
{
	FDASSERT(ms_packet.size() >= 15);

	ms_packet.setShort(13, ms_packet.getShort(13) + 1);

	ms_packet.addInt(_id);
	ms_packet.addShort(_cmd);
}

void IPacketCreator::_finish()
{
	FDASSERT(ms_packet.size() >= 5);

	ms_packet.setInt(1, ms_packet.size() - 5);
}
