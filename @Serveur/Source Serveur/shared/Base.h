#ifndef BASE_H
#define BASE_H


#include "../core/Core.h"

using namespace sdk;


#include "../libs/boost/static_assert.hpp"
#include "../libs/boost/smart_ptr.hpp"

//TYPE SIZE ASSERTS
/////////////////////

BOOST_STATIC_ASSERT(sizeof(sdk::s8) == 1);
BOOST_STATIC_ASSERT(sizeof(sdk::u8) == 1);
BOOST_STATIC_ASSERT(sizeof(sdk::s16) == 2);
BOOST_STATIC_ASSERT(sizeof(sdk::u16) == 2);
BOOST_STATIC_ASSERT(sizeof(sdk::s32) == 4);
BOOST_STATIC_ASSERT(sizeof(sdk::u32) == 4);
BOOST_STATIC_ASSERT(sizeof(sdk::s64) == 8);
BOOST_STATIC_ASSERT(sizeof(sdk::u64) == 8);
BOOST_STATIC_ASSERT(sizeof(sdk::f32) == 4);
BOOST_STATIC_ASSERT(sizeof(sdk::f64) == 8);


#include <sstream>

using namespace std;


#include "../core/MemoryLeak.h"


//DATABASE OBJECT TYPES
/////////////////////////

class ICharacter;
class IAccount;
class IItemPack;
class IMail;

typedef boost::intrusive_ptr<IAccount> AccountPtr;
typedef boost::intrusive_ptr<ICharacter> CharacterPtr;
typedef boost::intrusive_ptr<IItemPack> ItemPackPtr;
typedef boost::intrusive_ptr<IMail> MailPtr;

//WORLD CONTENT TYPES
///////////////////////

class IWorldObject;
class ICreature;
class IPlayerObject;
class IMobObject;
class INpcObject;
class IDropObject;
class IMovingObject;
class IPetObject;
class IItemPetObject;
class IStatPetObject;
class IParty;

typedef boost::intrusive_ptr<IWorldObject> WorldObjectPtr;
typedef boost::intrusive_ptr<ICreature> CreaturePtr;
typedef boost::intrusive_ptr<IPlayerObject> PlayerObjectPtr;
typedef boost::intrusive_ptr<IMobObject> MobObjectPtr;
typedef boost::intrusive_ptr<INpcObject> NpcObjectPtr;
typedef boost::intrusive_ptr<IDropObject> DropObjectPtr;
typedef boost::intrusive_ptr<IParty> PartyPtr;
typedef boost::intrusive_ptr<IMovingObject> MovingObjectPtr;
typedef boost::intrusive_ptr<IPetObject> PetObjectPtr;
typedef boost::intrusive_ptr<IItemPetObject> ItemPetObjectPtr;
typedef boost::intrusive_ptr<IStatPetObject> StatPetObjectPtr;


//UTIL
////////

const char *itostr(u32 _int); //up to 255


//COMPILER SETTINGS
/////////////////////

#ifdef _MSC_VER
#pragma warning(disable:4355) //use of 'this' in the ctor
#pragma warning(disable:4996) //this function may be unsafe
#pragma warning(disable:4309) //Verkürzung eines konstanten Wertes
#endif


//// TYPES ////
///////////////

typedef s32 ID;
typedef s32 PENYA;
typedef s64 PENYA64;
typedef s64 EXP;
typedef f64 RATE;
typedef s32 LVL;
typedef s64 Time;
typedef CVec3D<f32> CPoint;


//// VERSION ////
/////////////////

static const u32 VERSION_MAJOR = 16;
static const u32 VERSION_MINOR = 5;
static const u32 VERSION_UNION = VERSION_MAJOR * 1000 + VERSION_MINOR;

const char *blackorion_getVersionStr();


//// SETTINGS ////
//////////////////

#define SETTING_MYSQL_ERRORS_ENABLED


//// CONSTANTS ////
///////////////////

/// FILES

static const char * const LOGIN_SETTINGS_FILE_NAME = "login.ini";
static const char * const CHAR_SETTINGS_FILE_NAME = "char.ini";
static const char * const WORLD_SETTINGS_FILE_NAME = "world.ini";


/// ISC

static const PORT ISC_STANDARD_PORT = 13579;
static const Byte ISC_PACKET_BEGIN = 0x52;


/// NET

static const Byte NET_PACKET_BEGIN = 0x5e;
static const PORT LOGIN_STANDARD_PORT = 23000;
static const PORT CHAR_STANDARD_PORT = 28000;
static const PORT WORLD_STANDARD_PORT = 15400;


/// GAME

static const RATE GAME_STANDARD_EXP_RATE = 1.0f;
static const RATE GAME_STANDARD_DROP_RATE = 1.0f;
static const RATE GAME_STANDARD_PENYA_RATE = 1.0f;


/// CHARACTER

static const u32 CHARACTER_NAME_MIN = 4;
static const u32 CHARACTER_NAME_MAX = 16;
static const s32 CHARACTER_STANDARD_BASE_STR = 15;
static const s32 CHARACTER_STANDARD_BASE_STA = 15;
static const s32 CHARACTER_STANDARD_BASE_DEX = 15;
static const s32 CHARACTER_STANDARD_BASE_INT = 15;
static const s32 CHARACTER_STANDARD_BASE_STAT_POINTS = 0;
static const PENYA MAX_PENYA = 2100000000;
static const LVL CHARACTER_LEVEL_MIN = 1;
static const LVL CHARACTER_LEVEL_MAX = 0x7fff;


/// DATA

static const char * const DATA_MOVER_IDS = "data/_moverIds.txt";
static const char * const DATA_MOVER_DATA = "data/propMover.txt";
static const char * const DATA_DROPS_FOLDER = "data/drops/";
static const char * const DATA_DROPS_ENDING = ".drop";
static const char * const DATA_SPAWNS_FOLDER = "data/spawns/";
static const char * const DATA_SPAWNS_ENDING = ".spawn";
static const char * const DATA_NPCS_FOLDER = "data/npcs/";
static const char * const DATA_NPCS_ENDING = ".npc";
static const char * const DATA_NPC_DIALOGS_FOLDER = "data/npcdialogs/";
static const char * const DATA_EXP_FILENAME = "data/_exp.txt";
static const char * const DATA_JOB_FILENAME = "data/_jobs.txt";
static const char * const DATA_WORLD_FILENAME = "data/_worlds.txt";
static const char * const DATA_SPC_FILENAME = "data/_ItemSpc.bin";
static const char * const DATA_ITEMS_IDS = "data/defineItem.h";
static const char * const DATA_ITEMS_TEXTS = "data/propItem.txt.txt";
static const char * const DATA_ITEMS_DATA = "data/propItem.txt";


#endif //BASE_H
