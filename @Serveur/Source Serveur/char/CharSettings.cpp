#include "CharSettings.h"
#include "../shared/Log.h"
#include "../shared/Character.h"


bool ICharSettings::CharacterSettings::loadStartItems(IItemDataManager *_itemMngr)
{
	FDASSERT(_itemMngr);

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	if (t_file.open(StartItemFileName.c_str()))
	{
		const u32 T_BUF_SIZE = 256;
		char t_buffer[T_BUF_SIZE];

		StartItem t_item;

		ID t_itemId;

		E_SEX t_currSex = SEX_SEXLESS;

		u32 t_slotCount;

		while (!t_file.end())
		{
			t_file.readNext(t_buffer, T_BUF_SIZE);

			//ITEM command
			if (xstricmp("ITEM", t_buffer) == 0)
			{
				t_item.m_sex = t_currSex;

				t_item.m_place = Limit(t_file.readInt(), 0, INV_TOTAL_ITEMS - 1);

				t_itemId = t_file.readInt();

				t_item.m_data = _itemMngr->getItemById(t_itemId);

				if (!t_item.m_data)
				{
					Log::write(LOG_WARNING,
						"Error in start item file \"%s\": Unknown item with id %d!",
						StartItemFileName.c_str(), t_itemId);
					break;
				}

				t_item.m_count = Limit<s32>(t_file.readInt(), 1, IItemPack::COUNT_MAX);

				t_item.m_upgrade = Limit<s32>(t_file.readInt(), 0, IItemPack::UPGRADE_MAX);

				t_item.m_element = element(t_file.readInt());

				t_item.m_eleUpgrade = Limit<s32>(t_file.readInt(), 0, IItemPack::UPGRADE_ELE_MAX);

				t_item.m_spc.setStat(t_file.readInt());

				t_slotCount = t_file.readUInt();

				if (t_slotCount > IItemPack::SLOT_COUNT_MAX)
				{
					Log::write(LOG_WARNING,
						"Error in start item file \"%s\": There cannot be more than 10 slots on 1 item!",
						StartItemFileName.c_str());
					break;
				}

				for (u32 i = 0; i < t_slotCount; ++i)
				{
					t_item.m_slots.push_back(_itemMngr->getItemById(t_file.readInt()));
				}

				FDASSERT(t_item.isValid());

				StartItems.push_back(t_item);
			}

			//SEX command
			else if (xstricmp("SEX", t_buffer) == 0)
			{
				t_file.readNext(t_buffer, T_BUF_SIZE);

				if (xstricmp("MALE", t_buffer) == 0)
				{
					t_currSex = SEX_MALE;
				}
				else if (xstricmp("FEMALE", t_buffer) == 0)
				{
					t_currSex = SEX_FEMALE;
				}
				else if (xstricmp("ALL", t_buffer) == 0 ||
					xstricmp("SEXLESS", t_buffer) == 0 ||
					xstricmp("NONE", t_buffer) == 0)
				{
					t_currSex = SEX_SEXLESS;
				}
			}

			//unknown
			else
			{
				Log::write(LOG_ERROR, "Unknown identifier '%s' in start item file \"%s\"!",
					t_buffer, StartItemFileName.c_str());

				return false;
			}
		}

		return true;
	}

	Log::write(LOG_ERROR, "Start inventory file \"%s\" could not be opened!", StartItemFileName.c_str());

	return false;
}

ICharSettings::ICharSettings()
{
}

bool ICharSettings::load(const char *_filename)
{
	bool r_opened = m_file.load(_filename);

	//ISC

	ISC.Host = m_file.getValueString("ISC", "host", "127.0.0.1");
	ISC.Port = m_file.getValueUInt("ISC", "port", ISC_STANDARD_PORT);
	ISC.Password = m_file.getValueString("ISC", "password", "");
	ISC.ThisIP = m_file.getValueString("ISC", "thisip", "127.0.0.1");
	ISC.ExternalId = m_file.getValueInt("ISC", "extid", 10);
	ISC.Name = m_file.getValueString("ISC", "name", "Cluster");

	//Game

	Game.Port = m_file.getValueUInt("GAME", "port", LOGIN_STANDARD_PORT);
	Game.SaveInterval = m_file.getValueUInt("GAME", "saveinterval", 60000);

	//Database

	Database.Host = m_file.getValueString("DATABASE", "host", "127.0.0.1");
	Database.Port = m_file.getValueUInt("DATABASE", "port", 3306);
	Database.User = m_file.getValueString("DATABASE", "user", "root");
	Database.Password = m_file.getValueString("DATABASE", "password", "");
	Database.Database = m_file.getValueString("DATABASE", "database", "blackorion_0");
	//Data

	Data.Items.WorldServer = false;
	Data.Items.PropItemEtcFileName = m_file.getValueString("DATA", "propitemetc", "data/PropItemEtc.inc");
	Data.Items.LoadSpc = m_file.getValueBool("DATA", "loadspc", false);
	Data.Items.SaveSpc = m_file.getValueBool("DATA", "savespc", false);
	Data.Items.SpcFileName = m_file.getValueString("DATA", "spcfilename", DATA_SPC_FILENAME);
	Data.Items.ItemIdFileName = m_file.getValueString("DATA", "itemids", DATA_ITEMS_IDS);
	Data.Items.ItemTextFileName = m_file.getValueString("DATA", "itemtexts", DATA_ITEMS_TEXTS);
	Data.Items.ItemDataFileName = m_file.getValueString("DATA", "itemdata", DATA_ITEMS_DATA);

	//Program

	Program.LogFileName = m_file.getValueString("PROGRAM", "log", "char.log");

	//Character

	Character.BaseStr = Limit(
		m_file.getValueInt("CHARACTER", "basestr", CHARACTER_STANDARD_BASE_STR),
		0, 2 << 15);
	Character.BaseSta = Limit(
		m_file.getValueInt("CHARACTER", "basesta", CHARACTER_STANDARD_BASE_STA),
		0, 2 << 15);
	Character.BaseDex = Limit(
		m_file.getValueInt("CHARACTER", "basedex", CHARACTER_STANDARD_BASE_DEX),
		0, 2 << 15);
	Character.BaseInt = Limit(
		m_file.getValueInt("CHARACTER", "baseint", CHARACTER_STANDARD_BASE_INT),
		0, 2 << 15);
	Character.BaseStatPoints = Limit(
		m_file.getValueInt("CHARACTER", "statpoints", CHARACTER_STANDARD_BASE_STAT_POINTS),
		0, 2 << 15);
	Character.Level = m_file.getValueInt("CHARACTER", "level", 1);
	Character.Penya = m_file.getValueInt("CHARACTER", "penya", 0);
	Character.Job = job(m_file.getValueInt("CHARACTER", "job", JOB_VAGRANT));
	Character.StartItemFileName = m_file.getValueString("CHARACTER", "startitemfile","data/_StartItems.txt");

	return r_opened;
}
