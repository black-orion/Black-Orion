#include "WorldSettings.h"


IWorldSettings::CommandSettings::Cmd::Cmd()
	: Access(IAccount::ACC_MAXIMUM)
{
}

void IWorldSettings::CommandSettings::Cmd::init(CConfigReader &_file, const char *_cat, const char *_val)
{
	FDASSERT(_cat);
	FDASSERT(_val);

	Access = IAccount::E_ACCESS_LEVEL(_file.getValueUInt(_cat, _val, Access));

	sdk::stringc t_strings = _file.getValueString(_cat, (stringc(_val) + "_str").c_str(), _val);
	u32 t_stringsLen = t_strings.size();
	t_strings.replace(',', 0);
	const char *t_pos = t_strings.c_str();
	const char *t_end = t_strings.c_str() + t_strings.size();

	while (t_pos < t_end)
	{
		Strings.push_back(t_pos);

		while (*t_pos)
			++t_pos;

		++t_pos;
	}
}

IWorldSettings::IWorldSettings()
{
}

bool IWorldSettings::load(const char *_filename)
{
	bool r_opened = m_file.load(_filename);

	//ISC

	ISC.Host = m_file.getValueString("ISC", "host", "127.0.0.1");
	ISC.Port = m_file.getValueUInt("ISC", "port", ISC_STANDARD_PORT);
	ISC.Password = m_file.getValueString("ISC", "password", "");
	ISC.ThisIP = m_file.getValueString("ISC", "thisip", "127.0.0.1");
	ISC.ExternalId = m_file.getValueInt("ISC", "extid", 11);
	ISC.ParentId = m_file.getValueInt("ISC", "parent", 10);
	ISC.Name = m_file.getValueString("ISC", "name", "Cluster");

	//Game

	Game.Port = m_file.getValueUInt("GAME", "port", LOGIN_STANDARD_PORT);
	Game.Exp = m_file.getValueDouble("GAME", "exp", 1.0f);
	Game.Drop = m_file.getValueDouble("GAME", "drop", 1.0f);
	Game.Penya = m_file.getValueDouble("GAME", "penya", 1.0f);
	Game.SaveInterval = m_file.getValueUInt("GAME", "saveinterval", 60000);
	Game.MobRemoveTime = m_file.getValueUInt("GAME", "mobremovetime", 5000);
	Game.ItemRemoveTime = m_file.getValueUInt("GAME", "itemremovetime", 180000);
	Game.DropOwnershipTime = m_file.getValueUInt("GAME", "dropowntime", 30000);
	Game.PenyaDropLimit_0 = m_file.getValueInt("GAME", "penyadroplimit_0", 20);
	Game.PenyaDropLimit_1 = m_file.getValueInt("GAME", "penyadroplimit_1", 50);
	Game.PenyaDropLimit_2 = m_file.getValueInt("GAME", "penyadroplimit_2", 100);
	Game.PenyaDropLimit_3 = m_file.getValueInt("GAME", "penyadroplimit_3", MAX_PENYA);
	Game.LevelUpStatPoints = m_file.getValueInt("GAME", "lvlupsp", 2);
	Game.LevelUpStatPointsMaster = m_file.getValueInt("GAME", "lvlupspmaster", 3);
	Game.LevelUpStatPointsHero = m_file.getValueInt("GAME", "lvlupsphero", 0);
	Game.DeathExpLostFrom = m_file.getValueInt("GAME", "deathexplostfrom", 20);
	Game.Delevel = m_file.getValueBool("GAME", "delevel", true);
	Game.LootRange = m_file.getValueFloat("GAME", "lootrange", 2.0f);
	Game.ExpMaxLevel = Limit(m_file.getValueInt("GAME", "expmaxlvl", 121),
		CHARACTER_LEVEL_MIN, CHARACTER_LEVEL_MAX);
	Game.SpcMaxLevel = Limit(m_file.getValueInt("GAME", "spcmaxlvl", 150),
		CHARACTER_LEVEL_MIN, CHARACTER_LEVEL_MAX);
	Game.MailCost = Limit(m_file.getValueInt("GAME", "mailcost", 150), 0, MAX_PENYA);
	Game.PlayerRegenerationTime = Limit<u32>(m_file.getValueUInt("GAME", "plregtime", 4000), 0, 60 * 1000);
	Game.WeatherType = weather(m_file.getValueInt("GAME", "weathertype", WEATHER_RAIN));
	Game.WeatherRainTime = m_file.getValueUInt("GAME", "raintime", 60);
	Game.WeatherRainExp = m_file.getValueDouble("GAME", "rainexp", 1.0);

	//DATABASE

	Database.Host = m_file.getValueString("DATABASE", "host", "127.0.0.1");
	Database.Port = m_file.getValueUInt("DATABASE", "port", 3306);
	Database.User = m_file.getValueString("DATABASE", "user", "root");
	Database.Password = m_file.getValueString("DATABASE", "password", "");
	Database.Database = m_file.getValueString("DATABASE", "database", "blackorion_0");

	//Data

	Data.MoverIdFileName = m_file.getValueString("DATA", "moverids", DATA_MOVER_IDS);
	Data.MoverDataFileName = m_file.getValueString("DATA", "moverdata", DATA_MOVER_DATA);
	Data.DropFolder = m_file.getValueString("DATA", "drops", DATA_DROPS_FOLDER);
	Data.DropFileEnding = m_file.getValueString("DATA", "dropending", DATA_DROPS_ENDING);
	Data.SpawnFolder = m_file.getValueString("DATA", "spawns", DATA_SPAWNS_FOLDER);
	Data.SpawnFileEnding = m_file.getValueString("DATA", "spawnending", DATA_SPAWNS_ENDING);
	Data.NpcFolder = m_file.getValueString("DATA", "npcs", DATA_NPCS_FOLDER);
	Data.NpcFileEnding = m_file.getValueString("DATA", "npcending", DATA_NPCS_ENDING);
	Data.NpcDialogFolder = m_file.getValueString("DATA", "npcdialogs", DATA_NPC_DIALOGS_FOLDER);
	Data.ExpFileName = m_file.getValueString("DATA", "expfilename", DATA_EXP_FILENAME);
	Data.JobFileName = m_file.getValueString("DATA", "jobfilename", DATA_JOB_FILENAME);
	Data.WorldFileName = m_file.getValueString("DATA", "worldbfilename", DATA_WORLD_FILENAME);
	Data.Items.WorldServer = true;
	Data.Items.PropItemEtcFileName = m_file.getValueString("DATA", "propitemetc", "data/PropItemEtc.inc");
	Data.Items.LoadSpc = m_file.getValueBool("DATA", "loadspc", false);
	Data.Items.SaveSpc = m_file.getValueBool("DATA", "savespc", false);
	Data.Items.SpcFileName = m_file.getValueString("DATA", "spcfilename", DATA_SPC_FILENAME);
	Data.Items.ItemIdFileName = m_file.getValueString("DATA", "itemids", DATA_ITEMS_IDS);
	Data.Items.ItemTextFileName = m_file.getValueString("DATA", "itemtexts", DATA_ITEMS_TEXTS);
	Data.Items.ItemDataFileName = m_file.getValueString("DATA", "itemdata", DATA_ITEMS_DATA);

	//Program

	Program.LogFileName = m_file.getValueString("PROGRAM", "log", "world.log");

	//Commands
	
	Commands.Info.init(m_file, "COMMANDS", "info");
	Commands.Coin.init(m_file, "COMMANDS", "coin");
	Commands.Dice.init(m_file, "COMMANDS", "dice");
	Commands.Penya.init(m_file, "COMMANDS", "penya");
	Commands.Level.init(m_file, "COMMANDS", "level");
	Commands.AccessLevel.init(m_file, "COMMANDS", "accesslevel");
	Commands.ClearInv.init(m_file, "COMMANDS", "clearinv");
	Commands.DropInv.init(m_file, "COMMANDS", "dropinv");
	Commands.Shout.init(m_file, "COMMANDS", "shout");
	Commands.Item.init(m_file, "COMMANDS", "item");
	Commands.Stat.init(m_file, "COMMANDS", "stat");
	Commands.Notice.init(m_file, "COMMANDS", "notice");
	Commands.Pos.init(m_file, "COMMANDS", "pos");
	Commands.Name.init(m_file, "COMMANDS", "name");
	Commands.Exp.init(m_file, "COMMANDS", "exp");
	Commands.AddExp.init(m_file, "COMMANDS", "addexp");
	Commands.Kill.init(m_file, "COMMANDS", "kill");
	Commands.Job.init(m_file, "COMMANDS", "job");
	Commands.Points.init(m_file, "COMMANDS", "points");
	Commands.GetPoints.init(m_file, "COMMANDS", "getpoints");
	Commands.PlayerInfo.init(m_file, "COMMANDS", "playerinfo");
	Commands.Immortal.init(m_file, "COMMANDS", "immortal");
	Commands.OneHit.init(m_file, "COMMANDS", "onehit");
	Commands.God.init(m_file, "COMMANDS", "god");
	Commands.SetAccessLevel.init(m_file, "COMMANDS", "setaccesslevel");
	Commands.Mob.init(m_file, "COMMANDS", "mob");
	Commands.CreateSpawn.init(m_file, "COMMANDS", "createspawn");
	Commands.CreateItemList.init(m_file, "COMMANDS", "createitemlist");
	Commands.Place.init(m_file, "COMMANDS", "place");
	Commands.Ban.init(m_file, "COMMANDS", "ban");
	Commands.PvpPoints.init(m_file, "COMMANDS", "pvppoints");
	Commands.PkPoints.init(m_file, "COMMANDS", "pkpoints");
	Commands.Disposition.init(m_file, "COMMANDS", "disposition");
	Commands.Weather.init(m_file, "COMMANDS", "weather");
	Commands.Revive.init(m_file, "COMMANDS", "revive");
	Commands.ScriptFolder = m_file.getValueString("COMMANDS", "scriptfolder", "data/cmds/");
	Commands.ScriptDefinitionFileName = m_file.getValueString("COMMANDS", "scriptdefs", "data/cmds/_Commands.txt");

	return r_opened;
}