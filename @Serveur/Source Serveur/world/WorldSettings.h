#ifndef WORLDSETTINGS_H
#define WORLDSETTINGS_H


#include "WorldMain.h"
#include "../shared/ItemDataManager.h"
#include "../shared/Account.h"
#include "../shared/E_WEATHER.h"


class IWorldSettings
{
public:

	struct ISCSettings
	{
		sdk::stringc Host;
		PORT Port;
		sdk::stringc Password;
		sdk::stringc ThisIP;
		ID ExternalId;
		ID ParentId;
		sdk::stringc Name;
	} ISC;

	struct GameSettings
	{
		PORT Port;
		RATE Exp;
		RATE Drop;
		RATE Penya;
		TimeMs SaveInterval;
		TimeMs MobRemoveTime;
		TimeMs ItemRemoveTime;
		TimeMs DropOwnershipTime;
		PENYA PenyaDropLimit_0;
		PENYA PenyaDropLimit_1;
		PENYA PenyaDropLimit_2;
		PENYA PenyaDropLimit_3;
		s32 LevelUpStatPoints;
		s32 LevelUpStatPointsMaster;
		s32 LevelUpStatPointsHero;
		LVL DeathExpLostFrom;
		bool Delevel;
		f32 LootRange;
		LVL ExpMaxLevel;
		LVL SpcMaxLevel;
		PENYA MailCost;
		TimeMs PlayerRegenerationTime;
		E_WEATHER WeatherType;
		TimeMs WeatherRainTime;
		RATE WeatherRainExp;
	} Game;

	struct DatabaseSettings
	{
		sdk::stringc Host;
		PORT Port;
		sdk::stringc User;
		sdk::stringc Password;
		sdk::stringc Database;
	} Database;

	struct DataSettings
	{
		sdk::stringc MoverIdFileName;
		sdk::stringc MoverDataFileName;
		sdk::stringc DropFolder;
		sdk::stringc DropFileEnding;
		sdk::stringc SpawnFolder;
		sdk::stringc SpawnFileEnding;
		sdk::stringc NpcFolder;
		sdk::stringc NpcFileEnding;
		sdk::stringc NpcDialogFolder;
		sdk::stringc ExpFileName;
		sdk::stringc JobFileName;
		sdk::stringc WorldFileName;
		IItemDataManagerSettings Items;
	} Data;

	struct ProgramSettings
	{
		sdk::stringc LogFileName;
	} Program;

	struct CommandSettings
	{
		struct Cmd
		{
			CArray<sdk::stringc> Strings;
			IAccount::E_ACCESS_LEVEL Access;

			Cmd();
			void init(CConfigReader &_file, const char *_cat, const char *_val);
		};

		Cmd Info;
		Cmd Coin;
		Cmd Dice;
		Cmd Penya;
		Cmd Level;
		Cmd AccessLevel;
		Cmd ClearInv;
		Cmd DropInv;
		Cmd Shout;
		Cmd Item;
		Cmd Stat;
		Cmd Notice;
		Cmd Pos;
		Cmd Name;
		Cmd Exp;
		Cmd AddExp;
		Cmd Kill;
		Cmd Job;
		Cmd Points;
		Cmd GetPoints;
		Cmd PlayerInfo;
		Cmd Immortal;
		Cmd OneHit;
		Cmd God;
		Cmd SetAccessLevel;
		Cmd Mob;
		Cmd CreateSpawn;
		Cmd CreateItemList;
		Cmd Place;
		Cmd Ban;
		Cmd PvpPoints;
		Cmd PkPoints;
		Cmd Disposition;
		Cmd Weather;
		Cmd Revive;
		sdk::stringc ScriptFolder;
		sdk::stringc ScriptDefinitionFileName;
	} Commands;

	IWorldSettings();
	bool load(const char *_filename);

private:

	CConfigReader m_file;

};

typedef IWorldSettings::ISCSettings IWorldISCSettings;
typedef IWorldSettings::GameSettings IWorldGameSettings;
typedef IWorldSettings::DatabaseSettings IWorldDatabaseSettings;
typedef IWorldSettings::DataSettings IWorldDataSettings;
typedef IWorldSettings::CommandSettings IWorldCommandSettings;
typedef IWorldSettings::CommandSettings::Cmd IWorldCommand;


#endif //WORLDSETTINGS_H
