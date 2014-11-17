#ifndef PACKETCREATOR_H
#define PACKETCREATOR_H


#include "Base.h"
#include "E_STAT.h"
#include "E_GAME_TEXT.h"
#include "../shared/E_WEATHER.h"
#include "../login/LoginISC.h"


class IAccount;
class IWorldPlayer;
class IItemPack;
class IWorldObject;
class IPlayerObject;
class ICreature;
class INpcObject;
class ICharPlayer;
class IItemSlot;
class ILoginPlayer;
class IPostBox;
class IParty;
class IMovingObject;


class IPacketCreator
{
public:

	static CByteArray &getPacket();

	static void cleanup();

	//GENERAL

	static const CByteArray &greeting(s32 _id);


	//LOGIN

	enum E_LOGIN_COMMAND
	{
		LCMD_GREETING                  = 0x00000000,
		LCMD_ERROR                     = 0x000000fe,
		LCMD_SERVER_LIST               = 0x000000fd
	};

	enum E_LOGIN_ERROR
	{
		ERR_ALREADY_CONNECTED = 0x67, //Account is already connected
		ERR_OLD_CLIENT = 0x6b, //Old client version [closing]
		ERR_CAPACITY = 0x6c, //Capacity has been reached
		ERR_UNAVAILABLE = 0x6d, //Service unavailable
		ERR_BANNED = 0x77, //This ID has been blocked
		ERR_WRONG_PASSWORD = 0x78, //Wrong password
		ERR_WRONG_ID = 0x79, //Wrong ID
		ERR_TIME = 0x80, //Your time is up
		ERR_DATABASE = 0x81, //Other DB error
		ERR_10_PM = 0x83, //You cannot connect after 22:00
		ERR_OUTSIDE_SERVICE = 0x84, //You cannot connect from outside the service for Flyff
		ERR_CHARACTER_CHECKED = 0x85, //Your character is begin checked at the moment
		ERR_WRONG_PASSWORD_AGAIN = 0x86, //Cannot login for 15 seconds
		ERR_WRONG_PASSWORD_WAIT = 0x87, //Cannot login for 15 minutes
		ERR_VERIFICATION = 0x88, //Server verification error
		ERR_SESSION = 0x89, //Session is over

		ERR_NAME_IN_USE = 0x0524
	};

	static const CByteArray &loginError(E_LOGIN_ERROR _error);

	static const CByteArray &serverList(ILoginPlayer *_player, const ILoginISC::ServerList &_list);


	//CHAR

	enum E_CHAR_COMMAND
	{
		ECMD_CHANNEL_IP                = 0x000000f2,
		ECMD_CHAR_LIST                 = 0x000000f3,
		ECMD_WORLD_CONFIRMATION        = 0x0000ff05
	};

	static const CByteArray &worldIp(const char *_ip);

	static const CByteArray &charList(ICharPlayer *_player);

	static const CByteArray &confirmWorld();


	//WORLD

	enum E_WORLD_COMMAND
	{
		WCMD_SHARED_PACKET             = 0xffffff00,

		//part commands (short)
		WCMD_LOCAL_CHAT                = 0x0001,
		WCMD_INVENTORY_ADD_ITEM        = 0x0003,
		WCMD_INVENTORY_MOVE_ITEM       = 0x0004,
		WCMD_MOVE_EQUIP                = 0x0006,
		WCMD_GFX_EFFECT                = 0x000f,
		WCMD_TELEPORT                  = 0x0010,
		WCMD_LEVEL_INFOS               = 0x0012,
		WCMD_DAMAGE                    = 0x0013,
		WCMD_NPC_SHOP                  = 0x0014,
		WCMD_INVENTORY_UPDATE_ITEM     = 0x0018,
		WCMD_SKILL_MOTION              = 0x0019,
		WCMD_INCREASE_ATTRIBUTE        = 0x001c,
		WCMD_DECREASE_ATTRIBUTE        = 0x001d,
		WCMD_UPDATE_ATTRIBUTE          = 0x001e,
		WCMD_NPC_DIALOG                = 0x0024,
		//WCMD_KARMA                     = 0x0028,
		WCMD_PVP_POINTS                = 0x0040,
		WCMD_PLAYER_SHOP_OPEN          = 0x0042,
		WCMD_PLAYER_SHOP_CLOSE         = 0x0043,
		WCMD_PLAYER_SHOP_ADD           = 0x0044,
		WCMD_UPDATE_HAIR               = 0x0048,
		WCMD_BUFF                      = 0x004c,
		WCMD_UPDATE_FACE               = 0x004d,
		WCMD_WEATHER_NORMAL            = 0x0060,
		WCMD_WEATHER_SNOW              = 0x0061,
		WCMD_WEATHER_RAIN              = 0x0062,
		WCMD_STAT_INFOS                = 0x006a,
		WCMD_NEW_FRIEND                = 0x0070,
		WCMD_PARTY_TRANSFER            = 0x0079,
		WCMD_SKILL_TREE                = 0x007d,
		WCMD_PARTY_UPDATE              = 0x0082,
		WCMD_PARTY_DISBAND             = 0x0082,
		WCMD_PARTY_INVITATION          = 0x0083,
		WCMD_PARTY_REJECTION           = 0x0084,
		WCMD_PARTY_LEVEL               = 0x0085,
		WCMD_INFO_TEXT                 = 0x0095,
		WCMD_GAME_TIME                 = 0x0096,
		WCMD_HOT_SLOTS                 = 0x0097,
		WCMD_MOTION                    = 0x0098,
		WCMD_GREEN_TEXT                = 0x00a0,
		WCMD_REVIVAL                   = 0x00a2,
		WCMD_STAT_POINTS               = 0x00a6,
		WCMD_JOB                       = 0x00a7,
		WCMD_OBJECT_WALK               = 0x00c1,
		WCMD_OBJECT_FOLLOW             = 0x00c2,
		WCMD_OBJECT_DEATH              = 0x00c7,
		WCMD_SHOUT                     = 0x00d0,
		WCMD_FLAGS                     = 0x00d3,
		WCMD_ATTACK_MOTION             = 0x00e0,
		WCMD_ATTACK_MOTION_2           = 0x00e3,
		WCMD_MAIL_UPDATE               = 0x00e7,
		WCMD_MAILBOX                   = 0x00e9,
		WCMD_SPAWN                     = 0x00f0,
		WCMD_DESPAWN                   = 0x00f1,
		WCMD_TELEPORT_WORLD            = 0x00f2,
		WCMD_SPECIAL_OPTION            = 0x0140,
		WCMD_CHARACTER_INFOS           = 0x0141,
		WCMD_SHOP_CHAT                 = 0x047b,

		WCMD_NAME                      = 0x000012,
		WCMD_PRIVATE_MESSAGE           = 0xff00e0,
		WCMD_NOTICE                    = 0xff00ea
	};

	enum E_ITEM_UPDATE_TYPE
	{
		ITM_UPDATE_COUNT          = 0x0000,
        ITM_UPDATE_UPGRADE        = 0x0003,
        ITM_UPDATE_ELEUPGRADE     = 0x0004,
        ITM_UPDATE_ELEMENT        = 0x0005,
        ITM_UPDATE_SOCKETS        = 0x0006,
        ITM_UPDATE_CARD           = 0x0007,
        ITM_UPDATE_TICKET         = 0x000b
	};

	//general
	static const CByteArray &worldBegin(IWorldPlayer *_player);

	static const CByteArray &weatherAuto(E_WEATHER _weather);

	static const CByteArray &weatherNormal();

	static const CByteArray &weatherSnow();

	static const CByteArray &weatherRain();

	//chat etc.
	static const CByteArray &notice(const char *_text);

	static const CByteArray &chat(ID _senderId, const char *_text);

	static const CByteArray &shout(ID _senderId, const char *_name, const char *_text, s32 _color = 0xff99cc);

	static const CByteArray &greenText(const char *_text);

	static const CByteArray &privateMessage(IWorldPlayer *_from, IWorldPlayer *_to, const char *_text);

	static const CByteArray &gameInfo(const PlayerObjectPtr &_obj, E_GAME_TEXT _type, const char *_text);

	static const CByteArray &gameInfo(const PlayerObjectPtr &_obj, E_GAME_TEXT _type);

	//objects
	static const CByteArray &spawn(const WorldObjectPtr &_object);

	static const CByteArray &despawn(const WorldObjectPtr &_object);

	static const CByteArray &positionUpdate(const WorldObjectPtr &_object);

	static const CByteArray &worldPosUpdate(const WorldObjectPtr &_object);

	static const CByteArray &objectWalking(const MovingObjectPtr &_obj);

	static const CByteArray &follow(const MovingObjectPtr &_obj);

	static const CByteArray &damage(const WorldObjectPtr &_attacker, const WorldObjectPtr &_target, s32 _damage, s32 _flags);

	static const CByteArray &attack(const CreaturePtr &_attacker, const CreaturePtr &_target, s32 _motion);

	static const CByteArray &objectDeath(const WorldObjectPtr &_object);

	static const CByteArray &flags(const PlayerObjectPtr &_obj);

	static const CByteArray &updateFace(const PlayerObjectPtr &_obj);

	static const CByteArray &updateHair(const PlayerObjectPtr &_obj);

	static const CByteArray &motion(const PlayerObjectPtr &_obj);

	static const CByteArray &gfxEffect(const PlayerObjectPtr &_obj, ID _effectId);

	static const CByteArray &skillMotion(const PlayerObjectPtr &_user, const PlayerObjectPtr &_target,
		ID _skillId, s32 _level, s32 _type = 1);

	static const CByteArray &buff(const PlayerObjectPtr &_target, ID _skillId, s32 _level, TimeMs _duration);

	static const CByteArray &increaseAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount);

	static const CByteArray &decreaseAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount);

	static const CByteArray &updateAttribute(const CreaturePtr &_obj, E_STAT _stat, s32 _amount);

	static const CByteArray &updateAttribute(const CreaturePtr &_obj, E_STAT _stat);

	static const CByteArray &levelInfos(const PlayerObjectPtr &_obj); //Lvl, Exp, SkillPoints

	static const CByteArray &statInfos(const PlayerObjectPtr &_obj);

	static const CByteArray &statPoints(const PlayerObjectPtr &_obj);

	static const CByteArray &job(const PlayerObjectPtr &_obj);

	static const CByteArray &skillTree(const PlayerObjectPtr &_obj);

	static const CByteArray &changeName(const PlayerObjectPtr &_obj);

	static const CByteArray &characterInfos(const CharacterPtr &_char);

	static const CByteArray &mailBox(IPostBox *_post);

	static const CByteArray &pvpPoints(const PlayerObjectPtr &_pObj);

	//static const CByteArray &karma(const PlayerObjectPtr &_pObj);

	static const CByteArray &revival(const PlayerObjectPtr &_pObj);

	enum E_MAIL_UPDATE
	{
		MAIL_SUPPRESS          = 0,
		MAIL_READ_TAKE_OBJECT  = 1,
		MAIL_READ_MONEY        = 2,
		MAIL_READ_TAKE_NOTHING = 3
	};

	static const CByteArray &mailUpdate(const PlayerObjectPtr &_obj, ID _mail, E_MAIL_UPDATE _type);

	//Player Shops
	static const CByteArray &openShop(const PlayerObjectPtr &_obj);

	static const CByteArray &closeShop(const PlayerObjectPtr &_obj);

	static const CByteArray &addItemToShop(const PlayerObjectPtr &_obj, u32 _shopSlot);

	static const CByteArray &shopChat(const PlayerObjectPtr &_obj, const char *_message);

	//Inventory
	static const CByteArray &moveItem(const PlayerObjectPtr &_pObj, u32 _oldSlot, u32 _newSlot);

	static const CByteArray &addItem(const PlayerObjectPtr &_pObj, u32 _slot);

	static const CByteArray &updateItem(const PlayerObjectPtr &_pObj, u32 _slot, E_ITEM_UPDATE_TYPE _type,
		s32 _data, s32 _card = 0);

	static const CByteArray &updateSpcOption(const PlayerObjectPtr &_pObj, u32 _slot);

	static const CByteArray &moveEquip(const PlayerObjectPtr &_pObj, const IItemSlot &_slot, u32 _toSlot, bool _equip);

	//NPCs
	static const CByteArray &npcShop(const NpcObjectPtr &_npc);

	static const CByteArray &npcDialogClear(const NpcObjectPtr &_npc);

	static const CByteArray &npcDialogClose(const NpcObjectPtr &_npc);

	static const CByteArray &npcDialogText(const NpcObjectPtr &_npc, const char *_text);

	static const CByteArray &npcDialogLink(const NpcObjectPtr &_npc, const char *_text, const char *_internal,
		s32 _action1, s32 _action2);

	static const CByteArray &npcDialogButton(const NpcObjectPtr &_npc, const char *_text, const char *_internal,
		s32 _action1, s32 _action2);

	//Party
	static const CByteArray &partyInvitation(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_invitee);

	static const CByteArray &partyRejection(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_invitee);

	static const CByteArray &partyUpdate(const PlayerObjectPtr &_receiver, const PlayerObjectPtr &_asker,
		const PlayerObjectPtr &_target, PartyPtr &_party);

	static const CByteArray &partyDisband(const PlayerObjectPtr &_member);

	static const CByteArray &partyTransfer(const PlayerObjectPtr &_member, const PlayerObjectPtr &_leader);

	static const CByteArray &partyLevel(PartyPtr &_party);

private:

	enum
	{
		BUF_SIZE = 2048
	};

	static char ms_buffer[BUF_SIZE];

	static CByteArray ms_packet;

	static void _start(s32 _cmd);

	static void _startShared(ID _id, u32 cmd = WCMD_SHARED_PACKET);

	static void _addPart(E_WORLD_COMMAND _cmd, ID _id);

	static void _finish();

};

typedef const CByteArray &(*ObjPacket)(const WorldObjectPtr &);
typedef const CByteArray &(*PlayerObjPacket)(const PlayerObjectPtr &);


#endif //PACKETCREATOR_H
