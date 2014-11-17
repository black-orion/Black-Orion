#include "ItemData.h"
#include "RandomOption.h"
#include "ItemSet.h"


CArray<IRandomOption> IItemData::ms_randomOptions;

IItemData::IItemData(ID _id, const char *_idName)
	: m_id(_id)
	, m_idName(_idName)
	//, m_name("")
	, m_version(0)
	, m_ik1(IK1_GOLD)
	, m_ik2(IK2_GOLD)
	, m_ik3(IK3_GOLD)
	, m_handed(HD_ONE)
	, m_level(1)
	, m_job(JOB_VAGRANT)
	, m_sex(SEX_SEXLESS)
	, m_cost(0)
	, m_maxStack(1)
	, m_tradable(false)
	, m_attributeMin(0)
	, m_attributeMax(0)
	, m_set(0)
{
}

ID IItemData::getId() const
{
	return m_id;
}

const char *IItemData::getIdName() const
{
	return m_idName.c_str();
}

const char *IItemData::getName() const
{
	return m_name.c_str();
}

IItemData::E_ITEMKIND1 IItemData::getItemKind1() const
{
	return m_ik1;
}

IItemData::E_ITEMKIND2 IItemData::getItemKind2() const
{
	return m_ik2;
}

IItemData::E_ITEMKIND3 IItemData::getItemKind3() const
{
	return m_ik3;
}

IItemData::HANDED IItemData::getHanded() const
{
	return m_handed;
}

LVL IItemData::getLevel() const
{
	return m_level;
}

E_JOB IItemData::getJob() const
{
	return m_job;
}

E_SEX IItemData::getSex() const
{
	return m_sex;
}

PENYA IItemData::getCost() const
{
	return m_cost;
}

s32 IItemData::getStackSize() const
{
	return m_maxStack;
}

bool IItemData::isTradable() const
{
	return m_tradable;
}

s32 IItemData::getAttributeMin() const
{
	return m_attributeMin;
}

s32 IItemData::getAttributeMax() const
{
	return m_attributeMax;
}

const IStatEffect &IItemData::getEffect(u32 _num) const
{
	FDASSERT(_num < ARRAY_SIZE(m_effects));

	return m_effects[_num];
}

u32 IItemData::getPiercingEffectCount() const
{
	return m_piercingEffects.size();
}

const IStatEffect &IItemData::getPiercingEffect(u32 _num) const
{
	FDASSERT(_num < m_piercingEffects.size());

	return m_piercingEffects[_num];
}

const IItemSet *IItemData::getSet() const
{
	return m_set;
}

bool IItemData::isBrown() const
{
	return false; //...
}

bool IItemData::isGreen() const
{
	return false; //...
}

bool IItemData::isUltimate() const
{
	return false; //...
}

bool IItemData::canBeAwakened() const
{
	return (
		getItemKind1() == IK1_WEAPON ||
		getItemKind3() == IK3_SHIELD ||
		getItemKind3() == IK3_HELMET ||
		getItemKind3() == IK3_SUIT ||
		getItemKind3() == IK3_GAUNTLET ||
		getItemKind3() == IK3_BOOTS);
}

bool IItemData::canBeBlessed() const
{
	return (
		getItemKind3() == IK3_HAT ||
		getItemKind3() == IK3_CLOTH ||
		getItemKind3() == IK3_GLOVE ||
		getItemKind3() == IK3_SHOES ||
		getItemKind3() == IK3_CLOAK ||
		getItemKind3() == IK3_MASK);
}

bool IItemData::canBeUpgraded_Sun() const
{
	return (
		getItemKind1() == IK1_WEAPON ||
		getItemKind3() == IK3_SHIELD ||
		getItemKind3() == IK3_HELMET ||
		getItemKind3() == IK3_SUIT ||
		getItemKind3() == IK3_GAUNTLET ||
		getItemKind3() == IK3_BOOTS);
}

bool IItemData::canBeUpgraded_Moon() const
{
	return (
		getItemKind2() == IK2_JEWELRY);
}

const IItemData::ItemKindInfo IItemData::MS_ITEM_KIND1_INFOS[] =
{
	{IK1_GOLD, "IK1_GOLD"}, //0
	{IK1_WEAPON, "IK1_WEAPON"}, //1
	{IK1_ARMOR, "IK1_ARMOR"}, //2
	{IK1_GENERAL, "IK1_GENERAL"}, //3
	{IK1_RIDE, "IK1_RIDE"}, //4
	{IK1_SYSTEM, "IK1_SYSTEM"}, //5
	{IK1_CHARGED, "IK1_CHARGED"}, //6
	{IK1_HOUSING, "IK1_HOUSING"} //7
};

const IItemData::ItemKindInfo IItemData::MS_ITEM_KIND2_INFOS[] =
{
	{IK2_GOLD, "IK2_GOLD"}, //0
	{IK2_WEAPON_HAND, "IK2_WEAPON_HAND"}, //1
	{IK2_WEAPON_DIRECT, "IK2_WEAPON_DIRECT"}, //2
	{IK2_WEAPON_MAGIC, "IK2_WEAPON_MAGIC"}, //3
	{IK2_GOLD, ""}, //4
	{IK2_GOLD, ""}, //5
	{IK2_GOLD, ""}, //6
	{IK2_ARMOR, "IK2_ARMOR"}, //7
	{IK2_ARMORETC, "IK2_ARMORETC"}, //8
	{IK2_CLOTH, "IK2_CLOTH"}, //9
	{IK2_CLOTHETC, "IK2_CLOTHETC"}, //10
	{IK2_REFRESHER, "IK2_REFRESHER"}, //11
	{IK2_POTION, "IK2_POTION"}, //12
	{IK2_JEWELRY, "IK2_JEWELRY"}, //13
	{IK2_FOOD, "IK2_FOOD"}, //14
	{IK2_MAGIC, "IK2_MAGIC"}, //15
	{IK2_GEM, "IK2_GEM"}, //16
	{IK2_MATERIAL, "IK2_MATERIAL"}, //17
	{IK2_TOOLS, "IK2_TOOLS"}, //18
	{IK2_SYSTEM, "IK2_SYSTEM"}, //19
	{IK2_RIDING, "IK2_RIDING"}, //20
	{IK2_MOB, "IK2_MOB"}, //21
	{IK2_BLINKWING, "IK2_BLINKWING"}, //22
	{IK2_AIRFUEL, "IK2_AIRFUEL"}, //23
	{IK2_CHARM, "IK2_CHARM"}, //24
	{IK2_BULLET, "IK2_BULLET"}, //25
	{IK2_TEXT, "IK2_TEXT"}, //26
	{IK2_GMTEXT, "IK2_GMTEXT"}, //27
	{IK2_GENERAL, "IK2_GENERAL"}, //28
	{IK2_BUFF, "IK2_BUFF"}, //29
	{IK2_WARP, "IK2_WARP"}, //30
	{IK2_SKILL, "IK2_SKILL"}, //31
	{IK2_CLOTHWIG, "IK2_CLOTHWIG"}, //32
	{IK2_BUFF2, "IK2_BUFF2"}, //33
	{IK2_FURNITURE, "IK2_FURNITURE"}, //34
	{IK2_PAPERING, "IK2_PAPERING"}, //35
	{IK2_TOCASH, "IK2_TOCASH"}, //36
	{IK2_BUFF_TOGIFT, "IK2_BUFF_TOGIFT"} //37
};

const IItemData::ItemKindInfo IItemData::MS_ITEM_KIND3_INFOS[] =
{
	{IK3_GOLD, "IK3_GOLD"}, //0
	{IK3_HAND, "IK3_HAND"}, //1
	{IK3_SWD, "IK3_SWD"}, //2
	{IK3_AXE, "IK3_AXE"}, //3
	{IK3_CHEERSTICK, "IK3_CHEERSTICK"}, //4
	{IK3_KNUCKLEHAMMER, "IK3_KNUCKLEHAMMER"}, //5
	{IK3_WAND, "IK3_WAND"}, //6
	{IK3_STAFF, "IK3_STAFF"}, //7
	{IK3_THSWD, "IK3_THSWD"}, //8
	{IK3_THAXE, "IK3_THAXE"}, //9
	{IK3_VIRTUAL, "IK3_VIRTUAL"}, //10
	{IK3_YOYO, "IK3_YOYO"}, //11
	{IK3_BOW, "IK3_BOW"}, //12
	{IK3_YOBO, "IK3_YOBO"}, //13
	{IK3_GOLD, ""}, //14
	{IK3_GOLD, ""}, //15
	{IK3_SHIELD, "IK3_SHIELD"}, //16
	{IK3_HELMET, "IK3_HELMET"}, //17
	{IK3_SUIT, "IK3_SUIT"}, //18
	{IK3_GAUNTLET, "IK3_GAUNTLET"}, //19
	{IK3_BOOTS, "IK3_BOOTS"}, //20
	{IK3_HAT, "IK3_HAT"}, //21
	{IK3_MASK, "IK3_MASK"}, //22
	{IK3_SHOES, "IK3_SHOES"}, //23
	{IK3_CLOAK, "IK3_CLOAK"}, //24
	{IK3_REFRESHER, "IK3_REFRESHER"}, //25
	{IK3_POTION, "IK3_POTION"}, //26
	{IK3_EARRING, "IK3_EARRING"}, //27
	{IK3_NECKLACE, "IK3_NECKLACE"}, //28
	{IK3_RING, "IK3_RING"}, //29
	{IK3_INSTANT, "IK3_INSTANT"}, //30
	{IK3_COOKING, "IK3_COOKING"}, //31
	{IK3_ICECEARM, "IK3_ICECEARM"}, //32
	{IK3_MAGICTRICK, "IK3_MAGICTRICK"}, //33
	{IK3_GEM, "IK3_GEM"}, //34
	{IK3_DRINK, "IK3_DRINK"}, //35
	{IK3_COLLECTER, "IK3_COLLECTER"}, //36
	{IK3_ELECARD, "IK3_ELECARD"}, //37
	{IK3_DICE, "IK3_DICE"}, //38
	{IK3_SUPSTONE, "IK3_SUPSTONE"}, //39
	{IK3_BOARD, "IK3_BOARD"}, //40
	{IK3_STICK, "IK3_STICK"}, //41
	{IK3_EVENTMAIN, "IK3_EVENTMAIN"}, //42
	{IK3_QUEST, "IK3_QUEST"}, //43
	{IK3_MAP, "IK3_MAP"}, //44
	{IK3_BLINKWING, "IK3_BLINKWING"}, //45
	{IK3_EVENTSUB, "IK3_EVENTSUB"}, //46
	{IK3_TOWNBLINKWING, "IK3_TOWNBLINKWING"}, //47
	{IK3_ACCEL, "IK3_ACCEL"}, //48
	{IK3_DELETE, "IK3_DELETE"}, //49
	{IK3_SCROLL, "IK3_SCROLL"}, //50
	{IK3_ENCHANTWEAPON, "IK3_ENCHANTWEAPON"}, //51
	{IK3_CFLIGHT, "IK3_CFLIGHT"}, //52
	{IK3_BFLIGHT, "IK3_BFLIGHT"}, //53
	{IK3_MAGICBOTH, "IK3_MAGICBOTH"}, //54
	{IK3_KEY, "IK3_KEY"}, //55    {IK3_BCHARM, "IK3_BCHARM"}, //55
	{IK3_RCHARM, "IK3_RCHARM"}, //56
	{IK3_CLOTH, "IK3_CLOTH"}, //57
	{IK3_GLOVE, "IK3_GLOVE"}, //58
	{IK3_PILL, "IK3_PILL"}, //59
	{IK3_ARROW, "IK3_ARROW"}, //60
	{IK3_PIERDICE, "IK3_PIERDICE"}, //61
	{IK3_SOCKETCARD, "IK3_SOCKETCARD"}, //62
	{IK3_SOCKETCARD2, "IK3_SOCKETCARD2"}, //63
	{IK3_GOLD, ""}, //64
	{IK3_GOLD, ""}, //65
	{IK3_GOLD, ""}, //66
	{IK3_GOLD, ""}, //67
	{IK3_GOLD, ""}, //68
	{IK3_GOLD, ""}, //69
	{IK3_TEXT_BOOK, "IK3_TEXT_BOOK"}, //70
	{IK3_TEXT_SCROLL, "IK3_TEXT_SCROLL"}, //71
	{IK3_TEXT_LETTER, "IK3_TEXT_LETTER"}, //72
	{IK3_GOLD, ""}, //73
	{IK3_GOLD, ""}, //74
	{IK3_GOLD, ""}, //75
	{IK3_GOLD, ""}, //76
	{IK3_GOLD, ""}, //77
	{IK3_GOLD, ""}, //78
	{IK3_GOLD, ""}, //79
	{IK3_TEXT_UNDYING, "IK3_TEXT_UNDYING"}, //80
	{IK3_TEXT_DISGUISE, "IK3_TEXT_DISGUISE"}, //81
	{IK3_TEXT_INVISIBLE, "IK3_TEXT_INVISIBLE"}, //82
	{IK3_TEXT_GM, "IK3_TEXT_GM"}, //83
	{IK3_BINDS, "IK3_BINDS"}, //84
	{IK3_CREATE_MONSTER, "IK3_CREATE_MONSTER"}, //85
	{IK3_GOLD, ""}, //86
	{IK3_GOLD, ""}, //87
	{IK3_GOLD, ""}, //88
	{IK3_GOLD, ""}, //89
	{IK3_POTION_BUFF_STR, "IK3_POTION_BUFF_STR"}, //90
	{IK3_POTION_BUFF_DEX, "IK3_POTION_BUFF_DEX"}, //91
	{IK3_POTION_BUFF_INT, "IK3_POTION_BUFF_INT"}, //92
	{IK3_POTION_BUFF_STA, "IK3_POTION_BUFF_STA"}, //93
	{IK3_POTION_BUFF_DEFENSE, "IK3_POTION_BUFF_DEFENSE"}, //94
	{IK3_ANGEL_BUFF, "IK3_ANGEL_BUFF"}, //95
	{IK3_GOLD, ""}, //96
	{IK3_GOLD, ""}, //97
	{IK3_GOLD, ""}, //98
	{IK3_GOLD, ""}, //99
	{IK3_PET, "IK3_PET"}, //100
	{IK3_RANDOM_SCROLL, "IK3_RANDOM_SCROLL"}, //101
	{IK3_ULTIMATE, "IK3_ULTIMATE"}, //102
	{IK3_GOLD, ""}, //103
	{IK3_LINK, "IK3_LINK"}, //104
	{IK3_GOLD, ""}, //105
	{IK3_GOLD, ""}, //106
	{IK3_GOLD, ""}, //107
	{IK3_GOLD, ""}, //108
	{IK3_GOLD, ""}, //109
	{IK3_GOLD, ""}, //110
	{IK3_GOLD, ""}, //111
	{IK3_GOLD, ""}, //112
	{IK3_GOLD, ""}, //113
	{IK3_GOLD, ""}, //114
	{IK3_GOLD, ""}, //115
	{IK3_GOLD, ""}, //116
	{IK3_GOLD, ""}, //117
	{IK3_GENERAL, "IK3_GENERAL"}, //118
	{IK3_ENCHANT, "IK3_ENCHANT"}, //119
	{IK3_EGG, "IK3_EGG"}, //120
	{IK3_FEED, "IK3_FEED"}, //121
	{IK3_TICKET, "IK3_TICKET"}, //122
	{IK3_POCKET, "IK3_POCKET"}, //123
	{IK3_BED, "IK3_BED"}, //124
	{IK3_SOFA, "IK3_SOFA"}, //125
	{IK3_WARDROBE, "IK3_WARDROBE"}, //126
	{IK3_CLOSET, "IK3_CLOSET"}, //127
	{IK3_TABLE, "IK3_TABLE"}, //128
	{IK3_CABINET, "IK3_CABINET"}, //129
	{IK3_PROPS, "IK3_PROPS"}, //130
	{IK3_WALLPAPER, "IK3_WALLPAPER"}, //131
	{IK3_CARPET, "IK3_CARPET"}, //132
	{IK3_COUPLE_BUFF, "IK3_COUPLE_BUFF"}, //133
	{IK3_FUNNYCOIN, "IK3_FUNNYCOIN"} //134
};

IItemData::E_ITEMKIND1 IItemData::itemKind1(const char *_name)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND1_INFOS); ++i)
	{
		if (strcmp(MS_ITEM_KIND1_INFOS[i].Name, _name) == 0)
		{
			return E_ITEMKIND1(MS_ITEM_KIND1_INFOS[i].Kind);
		}
	}

	return IK1_GOLD;
}

IItemData::E_ITEMKIND2 IItemData::itemKind2(const char *_name)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND2_INFOS); ++i)
	{
		if (strcmp(MS_ITEM_KIND2_INFOS[i].Name, _name) == 0)
		{
			return E_ITEMKIND2(MS_ITEM_KIND2_INFOS[i].Kind);
		}
	}

	return IK2_GOLD;
}

IItemData::E_ITEMKIND3 IItemData::itemKind3(const char *_name)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND3_INFOS); ++i)
	{
		if (strcmp(MS_ITEM_KIND3_INFOS[i].Name, _name) == 0)
		{
			return E_ITEMKIND3(MS_ITEM_KIND3_INFOS[i].Kind);
		}
	}

	return IK3_GOLD;
}

IItemData::E_ITEMKIND1 IItemData::itemKind1(s32 _id)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND1_INFOS); ++i)
	{
		if (MS_ITEM_KIND1_INFOS[i].Kind == _id)
		{
			return E_ITEMKIND1(MS_ITEM_KIND1_INFOS[i].Kind);
		}
	}

	return IK1_GOLD;
}

IItemData::E_ITEMKIND2 IItemData::itemKind2(s32 _id)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND2_INFOS); ++i)
	{
		if (MS_ITEM_KIND2_INFOS[i].Kind == _id)
		{
			return E_ITEMKIND2(MS_ITEM_KIND2_INFOS[i].Kind);
		}
	}

	return IK2_GOLD;
}

IItemData::E_ITEMKIND3 IItemData::itemKind3(s32 _id)
{
	for (u32 i = 0; i < ARRAY_SIZE(MS_ITEM_KIND3_INFOS); ++i)
	{
		if (MS_ITEM_KIND3_INFOS[i].Kind == _id)
		{
			return E_ITEMKIND3(MS_ITEM_KIND3_INFOS[i].Kind);
		}
	}

	return IK3_GOLD;
}

const char *IItemData::itemKind1Name(E_ITEMKIND1 _ik1)
{
	FDASSERT(_ik1 == itemKind1(_ik1));

	return MS_ITEM_KIND1_INFOS[_ik1].Name;
}

const char *IItemData::itemKind2Name(E_ITEMKIND2 _ik2)
{
	FDASSERT(_ik2 == itemKind2(_ik2));

	return MS_ITEM_KIND2_INFOS[_ik2].Name;
}

const char *IItemData::itemKind3Name(E_ITEMKIND3 _ik3)
{
	FDASSERT(_ik3 == itemKind3(_ik3));

	return MS_ITEM_KIND3_INFOS[_ik3].Name;
}

IItemData::HANDED IItemData::handed(const char *_name)
{
	return (strcmp("HD_TWO", _name) == 0) ? HD_TWO : HD_ONE;
}

u32 IItemData::randomOptionCount()
{
	return ms_randomOptions.size();
}

const IRandomOption *IItemData::randomOption(ID _id)
{
	if (_id < s32(ms_randomOptions.size()))
	{
		return &ms_randomOptions[_id];
	}
	else
	{
		return 0;
	}
}

void IItemData::cleanup()
{
	ms_randomOptions.destroy();
}
