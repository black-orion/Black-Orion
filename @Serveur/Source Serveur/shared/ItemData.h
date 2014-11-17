#ifndef ITEMDATA_H
#define ITEMDATA_H


#include "Base.h"
#include "ItemDataManager.h"
#include "RandomOption.h"
#include "E_CHAR.h"
#include "E_STAT.h"
#include "defineItem.h"


class IItemSet;


class IItemData
{
public:

	enum E_ITEMKIND1
	{
		IK1_GOLD = 0,
		IK1_WEAPON = 1,
		IK1_ARMOR = 2,
		IK1_GENERAL = 3,
		IK1_RIDE = 4,
		IK1_SYSTEM = 5,
		IK1_CHARGED = 6,
		IK1_HOUSING = 7,

		ITEMKIND1_COUNT
	};

	enum E_ITEMKIND2
	{
		IK2_GOLD = 0,
		IK2_WEAPON_HAND = 1,
		IK2_WEAPON_DIRECT = 2,
		IK2_WEAPON_MAGIC = 3,
		IK2_ARMOR = 7,
		IK2_ARMORETC = 8,
		IK2_CLOTH = 9,
		IK2_CLOTHETC = 10,
		IK2_REFRESHER = 11,
		IK2_POTION = 12,
		IK2_JEWELRY = 13,
		IK2_FOOD = 14,
		IK2_MAGIC = 15,
		IK2_GEM = 16,
		IK2_MATERIAL = 17,
		IK2_TOOLS = 18,
		IK2_SYSTEM = 19,
		IK2_RIDING = 20,
		IK2_MOB = 21,
		IK2_BLINKWING = 22,
		IK2_AIRFUEL = 23,
		IK2_CHARM = 24,
		IK2_BULLET = 25,
		IK2_TEXT = 26,
		IK2_GMTEXT = 27,
		IK2_GENERAL = 28,
		IK2_BUFF = 29,
		IK2_WARP = 30,
		IK2_SKILL = 31,
		IK2_CLOTHWIG = 32,
		IK2_BUFF2 = 33,
		IK2_FURNITURE = 34,
		IK2_PAPERING = 35,
		IK2_TOCASH = 36,
		IK2_BUFF_TOGIFT = 37,

		ITEMKIND2_COUNT
	};

	enum E_ITEMKIND3
	{
		IK3_GOLD = 0,

		IK3_HAND = 1,
		IK3_SWD = 2,
		IK3_AXE = 3,
		IK3_CHEERSTICK = 4,
		IK3_KNUCKLEHAMMER = 5,
		IK3_WAND = 6,
		IK3_STAFF = 7,
		IK3_THSWD = 8,
		IK3_THAXE = 9,
		IK3_VIRTUAL = 10,
		IK3_YOYO = 11,
		IK3_BOW = 12,
		IK3_YOBO = 13,

		IK3_SHIELD = 16,
		IK3_HELMET = 17,
		IK3_SUIT = 18,
		IK3_GAUNTLET = 19,
		IK3_BOOTS = 20,

		IK3_HAT = 21, //CS
		IK3_MASK = 22,
		IK3_SHOES = 23, //CS
		IK3_CLOAK = 24,
		IK3_CLOTH = 57, //CS
		IK3_GLOVE = 58, //CS

		IK3_REFRESHER = 25,
		IK3_POTION = 26,
		IK3_EARRING = 27,
		IK3_NECKLACE = 28,
		IK3_RING = 29,
		IK3_INSTANT = 30,
		IK3_COOKING = 31,
		IK3_ICECEARM = 32,
		IK3_PILL = 59,
		IK3_MAGICTRICK = 33,
		IK3_GEM = 34,
		IK3_DRINK = 35,
		IK3_COLLECTER = 36,
		IK3_ELECARD = 37,
		IK3_DICE = 38,
		IK3_SUPSTONE = 39,

		IK3_BOARD = 40,
		IK3_STICK = 41,
		IK3_EVENTMAIN = 42,
		IK3_QUEST = 43,
		IK3_MAP = 44,
		IK3_BLINKWING = 45,
		IK3_EVENTSUB = 46,
		IK3_TOWNBLINKWING = 47,

		IK3_ACCEL = 48,
		IK3_DELETE = 49,

		IK3_SCROLL = 50,
		IK3_ENCHANTWEAPON = 51,
		IK3_CFLIGHT = 52,
		IK3_BFLIGHT = 53,
		IK3_MAGICBOTH = 54,
		IK3_KEY = 55,
		IK3_BCHARM = 55,
		IK3_RCHARM = 56,
		IK3_ARROW = 60,

		IK3_PIERDICE = 61,
		IK3_SOCKETCARD = 62,
		IK3_SOCKETCARD2 = 63,

		IK3_TEXT_BOOK = 70,
		IK3_TEXT_SCROLL = 71,
		IK3_TEXT_LETTER = 72,

		IK3_TEXT_UNDYING = 80,
		IK3_TEXT_DISGUISE = 81,
		IK3_TEXT_INVISIBLE = 82,
		IK3_TEXT_GM = 83,

		IK3_BINDS = 84,

		IK3_CREATE_MONSTER = 85,

		IK3_POTION_BUFF_STR = 90,
		IK3_POTION_BUFF_DEX = 91,
		IK3_POTION_BUFF_INT = 92,
		IK3_POTION_BUFF_STA = 93,
		IK3_POTION_BUFF_DEFENSE = 94,

		IK3_ANGEL_BUFF = 95,

		IK3_PET = 100,
		IK3_RANDOM_SCROLL = 101,

		IK3_ULTIMATE = 102,

		IK3_LINK = 104,

		IK3_GENERAL = 118,

		IK3_ENCHANT = 119,

		IK3_EGG = 120,
		IK3_FEED = 121,

		IK3_TICKET = 122,
		IK3_POCKET = 123,

		IK3_BED = 124,
		IK3_SOFA = 125,
		IK3_WARDROBE = 126,
		IK3_CLOSET = 127,
		IK3_TABLE = 128,
		IK3_CABINET = 129,
		IK3_PROPS = 130,
		IK3_WALLPAPER = 131,
		IK3_CARPET = 132,
		IK3_COUPLE_BUFF = 133,
		IK3_FUNNYCOIN = 134,
		IK3_FLOWER = 135,

		MAX_ITEM_KIND3 = 136,

		ITEMKIND3_COUNT
	};

	enum HANDED
	{
		HD_ONE = 0,
		HD_TWO = 1
	};

	IItemData(ID _id = 0, const char *_idName = "");

	ID getId() const;

	const char *getIdName() const;

	const char *getName() const;

	E_ITEMKIND1 getItemKind1() const;

	E_ITEMKIND2 getItemKind2() const;

	E_ITEMKIND3 getItemKind3() const;

	HANDED getHanded() const;

	LVL getLevel() const;

	E_JOB getJob() const;

	E_SEX getSex() const;

	PENYA getCost() const;

	s32 getStackSize() const;

	bool isTradable() const;

	s32 getAttributeMin() const;

	s32 getAttributeMax() const;

	const IStatEffect &getEffect(u32 _num) const;

	u32 getPiercingEffectCount() const;

	const IStatEffect &getPiercingEffect(u32 _num) const;

	const IItemSet *getSet() const;

	bool isBrown() const;

	bool isGreen() const;

	bool isUltimate() const;

	bool canBeAwakened() const;

	bool canBeBlessed() const;

	bool canBeUpgraded_Sun() const;

	bool canBeUpgraded_Moon() const;

	static E_ITEMKIND1 itemKind1(const char *_name);

	static E_ITEMKIND2 itemKind2(const char *_name);

	static E_ITEMKIND3 itemKind3(const char *_name);

	static E_ITEMKIND1 itemKind1(s32 _id);

	static E_ITEMKIND2 itemKind2(s32 _id);

	static E_ITEMKIND3 itemKind3(s32 _id);

	static const char *itemKind1Name(E_ITEMKIND1 _ik1);

	static const char *itemKind2Name(E_ITEMKIND2 _ik2);

	static const char *itemKind3Name(E_ITEMKIND3 _ik3);

	static HANDED handed(const char *_name);

	static u32 randomOptionCount();

	static const IRandomOption *randomOption(ID _id);

	static void cleanup();

private:

	friend class IItemDataManager;

	sdk::stringc m_idName;

	sdk::stringc m_name;

	ID m_id;

	E_ITEMKIND1 m_ik1;

	E_ITEMKIND2 m_ik2;

	E_ITEMKIND3 m_ik3;

	HANDED m_handed;

	LVL m_level;

	E_JOB m_job;

	E_SEX m_sex;

	PENYA m_cost;

	s32 m_attributeMin;

	s32 m_attributeMax;

	IStatEffect m_effects[3];

	s32 m_maxStack;

	s16 m_version;

	bool m_tradable;

	//from PropItemEtc.inc:

	CArray<IStatEffect> m_piercingEffects;

	const IItemSet *m_set;

	//End from PropItemEtc.inc

	struct ItemKindInfo
	{
		u32 Kind;

		const char *Name;
	};

	static const ItemKindInfo MS_ITEM_KIND1_INFOS[];

	static const ItemKindInfo MS_ITEM_KIND2_INFOS[];

	static const ItemKindInfo MS_ITEM_KIND3_INFOS[];

	static CArray<IRandomOption> ms_randomOptions;

};


#endif //ITEMDATA_H
