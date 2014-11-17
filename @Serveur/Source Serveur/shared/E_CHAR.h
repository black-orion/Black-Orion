#ifndef E_CHAR_H
#define E_CHAR_H


#include "Base.h"


//// JobType ////
/////////////////

enum E_JOB_TYPE
{
	JTYPE_BASE = 0,   //vagrant
	JTYPE_EXPERT = 1, //1st job
	JTYPE_PRO = 2,    //2nd job
	JTYPE_TROUPE = 3, //??
	JTYPE_COMMON = 4, //??
	JTYPE_MASTER = 5,
	JTYPE_HERO = 6,

	COUNT_OF_JOB_TYPES
};

E_JOB_TYPE jobType(const char *_title);

E_JOB_TYPE jobType(s32 _id);

const char *jobTypeTitle(E_JOB_TYPE _type);


//// Job ////
/////////////

enum E_JOB
{
	JOB_VAGRANT = 0,

	JOB_MERCENARY = 1,
	JOB_ACROBAT = 2,
	JOB_ASSIST = 3,
	JOB_MAGICIAN = 4,
	JOB_PUPPETEER = 5,

	JOB_KNIGHT = 6,
	JOB_BLADE = 7,
	JOB_JESTER = 8,
	JOB_RANGER = 9,
	JOB_RINGMASTER = 10,
	JOB_BILLPOSTER = 11,
	JOB_PSYKEEPER = 12,
	JOB_ELEMENTOR = 13,
	JOB_GATEKEEPER = 14,
	JOB_DOPPLER = 15,

	JOB_KNIGHT_MASTER = 16,
	JOB_BLADE_MASTER = 17,
	JOB_JESTER_MASTER = 18,
	JOB_RANGER_MASTER = 19,
	JOB_RINGMASTER_MASTER = 20,
	JOB_BILLPOSTER_MASTER = 21,
	JOB_PSYKEEPER_MASTER = 22,
	JOB_ELEMENTOR_MASTER = 23,

	JOB_KNIGHT_HERO = 24,
	JOB_BLADE_HERO = 25,
	JOB_JESTER_HERO = 26,
	JOB_RANGER_HERO = 27,
	JOB_RINGMASTER_HERO = 28,
	JOB_BILLPOSTER_HERO = 29,
	JOB_PSYKEEPER_HERO = 30,
	JOB_ELEMENTOR_HERO = 31,

	COUNT_OF_JOBS = 32
};


E_JOB job(const char *_title);

E_JOB job(s32 _id);

const char *jobTitle(E_JOB _job);

bool isMaster(E_JOB _job);

bool isHero(E_JOB _job);

bool isMasterOrHero(E_JOB _job);


struct IJobStats
{
	stringc Name;

	LVL MaxLevel;

	E_JOB FirstJob;

	f32 HpRate;

	f32 MpRate;

	f32 FpRate;

	f32 HpRegRate;

	f32 MpRegRate;

	f32 FpRegRate;

	f32 DefStaRate;

	f32 DefLevelRate;

	s32 BaseDef;

	f32 Sword;

	f32 Axe;

	f32 Staff;

	f32 Stick;

	f32 Knuckle;

	f32 Wand; //(per INT)

	f32 Block; //% of block per 10 DEX

	f32 Yoyo;

	f32 Crit; //% of crit per 10 DEX

	f32 Bow; //(per DEX), added

	IJobStats();
};


bool loadJobStats(const char *_fileName);

const IJobStats &jobStats(E_JOB _job);

bool isCompatibleJob(E_JOB _required, E_JOB _char);


//// Sex ////
/////////////

enum E_SEX
{
	SEX_MALE = 0,
	SEX_FEMALE = 1,
	SEX_SEXLESS = 2
};

E_SEX sex(const char *_name);

E_SEX sex(s32 _id);

const char *sexTitle(E_SEX _sex);

bool isCompatibleSex(E_SEX _required, E_SEX _char);


//// Face ////
//////////////

enum E_FACE
{
	FACE_0 = 0,
	FACE_1 = 1,
	FACE_2 = 2,
	FACE_3 = 3,
	FACE_4 = 4,
	FACE_5 = 5,
	FACE_6 = 6,
	FACE_7 = 7
};

E_FACE face(s32 _id);


//// Hair ////
//////////////

enum E_HAIR
{
	HAIR_0 = 0,
	HAIR_1 = 1,
	HAIR_2 = 2,
	HAIR_3 = 3,
	HAIR_4 = 4,
	HAIR_5 = 5,
	HAIR_6 = 6,
	HAIR_7 = 7
};

E_HAIR hair(s32 _id);


//// Inventory ////
///////////////////

enum E_INVENTORY
{
	//inventory content
	INV_WIDTH = 6,
	INV_HEIGHT = 7,
	INV_PLACES = INV_WIDTH * INV_HEIGHT,
	INV_PLACES_INDEX = 0,

	//equipment
	INV_EQUIPS = 31,
	INV_EQUIPS_INDEX = INV_PLACES,

	PARTS_HEAD = 0, //42 0x2a
	PARTS_HAIR = 1, //43 0x2b
	PARTS_UPPER_BODY = 2, //44 0x2c -> Suit
	PARTS_LOWER_BODY = 3, //45 0x2d
	PARTS_HAND = 4, //46 0x2e -> Gauntlet
	PARTS_FOOT = 5, //47 0x2f -> Boots
	PARTS_CAP = 6, //48 0x30 -> Helmet
	PARTS_ROBE = 7, //49 0x31
	PARTS_CLOAK = 8, //50 0x32
	PARTS_LWEAPON = 9, //51 0x33 -> Waffe links
	PARTS_RWEAPON = 10, //52 0x34 -> Waffe rechts
	PARTS_SHIELD = 11, //53 0x37 -> Schild
	PARTS_MASK = 12,
	PARTS_RIDE = 13,
	PARTS_CAP2 = 14,
	PARTS_UPPER2 = 15,
	PARTS_LOWER2 = 16,
	PARTS_HAND2 = 17,
	PARTS_FOOT2 = 18,
	PARTS_NECKLACE1 = 19,
	PARTS_RING1 = 20,
	PARTS_RING2 = 21,
	PARTS_EARRING1 = 22,
	PARTS_EARRING2 = 23,
	PARTS_PROPERTY = 24,
	PARTS_BULLET = 25,
	PARTS_HAT = 26,
	PARTS_CLOTH = 27,
	PARTS_GLOVE = 28,
	PARTS_BOOTS = 29,
	PARTS_CLOAK2 = 30,

	//total
	INV_TOTAL_ITEMS = INV_PLACES + INV_EQUIPS
};


#endif //E_CHAR_H
