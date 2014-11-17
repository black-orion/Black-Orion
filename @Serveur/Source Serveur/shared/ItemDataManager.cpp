#include "ItemDataManager.h"
#include "ItemData.h"
#include "ItemSet.h"
#include "RandomOption.h"
#include "../shared/Log.h"


IItemDataManager::IItemDataManager(IItemDataManagerSettings *_settings)
	: m_settings(_settings)
{
	FDASSERT(m_settings);
}

IItemDataManager::~IItemDataManager()
{
	FOR_EACH (m_items, i)
	{
		delete m_items[i];
	}

	FOR_EACH (m_sets, i)
	{
		delete m_sets[i];
	}
}

bool IItemDataManager::load_char()
{
	return _loadItems();
}

bool IItemDataManager::load_world()
{
	return _loadItems() &&
		_loadPropItemEtc();
}

bool IItemDataManager::saveItemsSpc(const char *_fileName) const
{
	FDASSERT(_fileName);

	CByteArray t_spc;

	//Header
	t_spc.addStringRaw("SPC1");
	t_spc.addInt(VERSION_UNION);

	//Items
	t_spc.addInt(m_items.size());

	FOR_EACH (m_items, i)
	{
		t_spc.addInt(m_items[i]->m_id);
		t_spc.addString(m_items[i]->m_idName.c_str());
		t_spc.addString(m_items[i]->m_name.c_str());
		t_spc.addByte(static_cast<Byte>(m_items[i]->m_version));
		t_spc.addShort(m_items[i]->m_ik1);
		t_spc.addShort(m_items[i]->m_ik2);
		t_spc.addShort(m_items[i]->m_ik3);
		t_spc.addByte(m_items[i]->m_handed);
		t_spc.addShort(m_items[i]->m_level);
		t_spc.addByte(m_items[i]->m_job);
		t_spc.addByte(m_items[i]->m_sex);
		t_spc.addInt(m_items[i]->m_cost);
		t_spc.addShort(m_items[i]->m_maxStack);
		t_spc.addByte(m_items[i]->m_tradable);
		t_spc.addInt(m_items[i]->m_attributeMin);
		t_spc.addInt(m_items[i]->m_attributeMax);
		t_spc.addInt(m_items[i]->m_effects[0].Type);
		t_spc.addInt(m_items[i]->m_effects[0].Amount);
		t_spc.addInt(m_items[i]->m_effects[1].Type);
		t_spc.addInt(m_items[i]->m_effects[1].Amount);
		t_spc.addInt(m_items[i]->m_effects[2].Type);
		t_spc.addInt(m_items[i]->m_effects[2].Amount);
	}

	/*
	//Header
	t_spc.addStringRaw("SPC0");
	t_spc.addInt(VERSION);

	//Items
	t_spc.addInt(m_items.size());

	FOR_EACH (m_items)
	{
		t_spc.addInt(m_items[i]->m_id);
		t_spc.addString(m_items[i]->m_idName.c_str());
		t_spc.addString(m_items[i]->m_name.c_str());
		t_spc.addByte(static_cast<Byte>(m_items[i]->m_version));
		t_spc.addShort(m_items[i]->m_ik1);
		t_spc.addShort(m_items[i]->m_ik2);
		t_spc.addShort(m_items[i]->m_ik3);
		t_spc.addByte(m_items[i]->m_handed);
		t_spc.addShort(m_items[i]->m_level);
		t_spc.addByte(m_items[i]->m_job);
		t_spc.addByte(m_items[i]->m_sex);
		t_spc.addInt(m_items[i]->m_cost);
		t_spc.addShort(m_items[i]->m_maxStack);
		t_spc.addByte(m_items[i]->m_tradable);
		t_spc.addInt(m_items[i]->m_attributeMin);
		t_spc.addInt(m_items[i]->m_attributeMax);
	}
	*/

	//Save as file
	return t_spc.toFile(_fileName);
}

bool IItemDataManager::saveHtmlItemList(const char *_fileName) const
{
	FDASSERT(_fileName);

	FILE *t_file;
	fopen_s(&t_file, _fileName, "w");

	if (t_file)
	{
		fprintf_s(t_file, "<html><head><title>Item List</title>"
			"<style type=\"text/css\"><!--"
			"td { border:1px #505070 solid; font-size:12px; padding:2px; margin:0px; text-align:left; }"
			"td.m { text-align:center; }"
			//"td.r { text-align:right; }"
			//"td.l { text-align:left; padding-left:6px; }"
			"td.g { text-align:left; color:#009500; }"
			"tr:hover { background:#ddddff }"
			"tr.t { background:#cccccc }"
			"tr.t:hover { background:#cccccc }"
			"--></style>"
			"</head><body><table>"
			"<tr class=\"t\"><td>Name</td><td>ID-Name</td><td>ID Dec</td><td>ID Hex</td><td>Penya</td>"
			"<td>Level</td><td>IK1</td><td>IK2</td><td>IK3</td><td>Job</td></tr>");

		FOR_EACH (m_items, i)
		{
			if (!IItemData::itemKind1Name(m_items[i]->getItemKind1()) ||
				!IItemData::itemKind2Name(m_items[i]->getItemKind2()) ||
				!IItemData::itemKind3Name(m_items[i]->getItemKind3()))
			{
				printf("%p %p %p %d\n", IItemData::itemKind1Name(m_items[i]->getItemKind1()),
					IItemData::itemKind2Name(m_items[i]->getItemKind2()),
					IItemData::itemKind3Name(m_items[i]->getItemKind3()),
					m_items[i]->getItemKind3());
			}

			fprintf_s(t_file,
				"<tr><td>%s</td><td>%s</td><td class=\"m\">%d</td><td class=\"m\">0x%04x</td>"
				"<td class=\"m\">%d</td><td class=\"m\">%d</td><td>%s</td><td>%s</td><td>%s</td>"
				"<td>%s</td></tr>",
				m_items[i]->getName(),
				m_items[i]->getIdName(),
				m_items[i]->getId(),
				m_items[i]->getId(),
				m_items[i]->getCost(),
				m_items[i]->getLevel(),
				IItemData::itemKind1Name(m_items[i]->getItemKind1()),
				IItemData::itemKind2Name(m_items[i]->getItemKind2()),
				IItemData::itemKind3Name(m_items[i]->getItemKind3()),
				jobStats(m_items[i]->getJob()).Name.c_str());
		}

		fprintf_s(t_file, "</table></body></html>");

		fclose(t_file);
		return true;
	}

	return false;
}

bool IItemDataManager::saveUseItemList(const char *_fileName) const
{
	FDASSERT(_fileName);

	FILE *t_file;
	fopen_s(&t_file, _fileName, "w");

	if (t_file)
	{
		FOR_EACH (m_items, i)
		{
			fprintf_s(t_file,
				"%s|%d|%s|%s|%s|%s\n",
				m_items[i]->getIdName(),
				m_items[i]->getId(),
				IItemData::itemKind1Name(m_items[i]->getItemKind1()),
				IItemData::itemKind2Name(m_items[i]->getItemKind2()),
				IItemData::itemKind3Name(m_items[i]->getItemKind3()),
				m_items[i]->getName());
		}

		fclose(t_file);
		return true;
	}

	return false;
}

bool IItemDataManager::saveSpcItemList1(const char *_fileName) const
{
	FDASSERT(_fileName);

	FILE *t_file;
	fopen_s(&t_file, _fileName, "w");

	if (t_file)
	{
		FOR_EACH (m_items, i)
		{
			fprintf_s(t_file,
				"%d\t\"%s\"\n",
				m_items[i]->getId(),
				m_items[i]->getName());
		}

		fclose(t_file);
		return true;
	}

	return false;
}

u32 IItemDataManager::getItemCount() const
{
	return m_items.size();
}

const IItemData *IItemDataManager::getItemByNumber(u32 _num) const
{
	FDASSERT(_num < m_items.size());

	return m_items[_num];
}

const IItemData *IItemDataManager::getItemById(ID _id) const
{
	FOR_EACH (m_items, i)
	{
		if (m_items[i]->m_id == _id)
		{
			return m_items[i];
		}
	}

	return 0;
}

const IItemData *IItemDataManager::getItemById(const char *_idName) const
{
	FDASSERT(_idName);

	FOR_EACH (m_items, i)
	{
		if (strcmp(m_items[i]->m_idName.c_str(), _idName) == 0)
		{
			return m_items[i];
		}
	}

	return 0;
}

IItemData *IItemDataManager::_getItemById(const char *_idName)
{
	FDASSERT(_idName);

	FOR_EACH (m_items, i)
	{
		if (strcmp(m_items[i]->m_idName.c_str(), _idName) == 0)
		{
			return m_items[i];
		}
	}

	return 0;
}

bool IItemDataManager::_loadPropItemEtc()
{
	CFileReader t_file;

	u32 t_piercingCount = 0;
	u32 t_setCount = 0;

	u32 t_begin = CTime::system();

	if (t_file.open(m_settings->PropItemEtcFileName.c_str()))
	{
		t_file.setOption(CFileReader::opt_comments, true);

		const u32 T_BUF_SIZE = 1024;
		char t_buffer[T_BUF_SIZE];

		IStatEffect t_effect;

		while (!t_file.end())
		{
			t_file.readNext(t_buffer, T_BUF_SIZE);

			//Piercings
			if (strcmp("Piercing", t_buffer) == 0)
			{
				t_file.readNext(t_buffer, T_BUF_SIZE);

				IItemData *t_item = _getItemById(t_buffer);

				t_file.readNext(t_buffer, T_BUF_SIZE);

				if (t_buffer[0] != '{')
				{
					Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\"!",
						t_file.getFileName(), t_buffer);
					return false;
				}

				if (t_item)
				{
					while (!t_file.end())
					{
						t_file.readNext(t_buffer, T_BUF_SIZE);

						if (t_buffer[0] == '}')
							break;

						t_effect.Type = stat(t_buffer);
						t_effect.Amount = t_file.readInt();

						if (!t_effect.isNull())
						{
							t_item->m_piercingEffects.push_back(t_effect);
						}
						else
						{
							Log::write(LOG_WARNING, "Warning in file \"%s\": Invalid piercing effect %s %+d",
								t_file.getFileName(), t_buffer, t_effect.Amount);
						}
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Error in file \"%s\": Unknown item id \"%s\"!",
						t_file.getFileName(), t_buffer);
					return false;
				}

				++t_piercingCount;
			} //end of Piercings

			//Sets
			else if (strcmp("SetItem", t_buffer) == 0)
			{
				IItemSet t_set;
				u32 t_currPart = 0;

				//Id
				t_set.m_id = t_file.readInt();

				//Name
				t_file.skipNext();

				if (t_file.readNext(t_buffer, T_BUF_SIZE)[0] == '{')
				{
					//Set Parts
					if (strcmp("Elem", t_file.readNext(t_buffer, T_BUF_SIZE)) == 0 &&
						t_file.readNext(t_buffer, T_BUF_SIZE)[0] == '{')
					{
						while (!t_file.end())
						{
							t_file.readNext(t_buffer, T_BUF_SIZE);

							if (t_buffer[0] == '}')
								break;

							const IItemData * const t_setItem = getItemById(t_buffer);

							if (!t_setItem)
							{
								Log::write(LOG_ERROR, "Error in file \"%s\": Unknown item id \"%s\" in set %d!",
									t_file.getFileName(), t_buffer, t_set.m_id);
								return false;
							}

							if (t_currPart == IItemSet::COUNT_OF_PARTS)
							{
								Log::write(LOG_ERROR, "Error in file \"%s\": Too many parts in set %d!",
									t_file.getFileName(), t_set.m_id);
								return false;
							}

							t_set.m_parts[t_currPart++] = t_setItem;

							t_file.skipNext();
						}
					}
					else
					{
						Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\" in set %d!",
							t_file.getFileName(), t_buffer, t_set.m_id);
						return false;
					} //end of Set Parts

					//Set Effects
					if (strcmp("Avail", t_file.readNext(t_buffer, T_BUF_SIZE)) == 0 &&
						t_file.readNext(t_buffer, T_BUF_SIZE)[0] == '{')
					{
						while (!t_file.end())
						{
							t_file.readNext(t_buffer, T_BUF_SIZE);

							if (t_buffer[0] == '}')
								break;

							t_effect.Type = stat(t_buffer);
							t_effect.Amount = t_file.readInt();

							if (t_effect.isNull())
							{
								Log::write(LOG_WARNING,
									"Warning in file \"%s\": Invalid set effect %s %+d in set %d",
									t_file.getFileName(), t_buffer, t_effect.Amount, t_set.m_id);
							}

							u32 t_parts = t_file.readUInt();

							if (!IItemSet::isValidParts(t_parts))
							{
								Log::write(LOG_WARNING,
									"Warning in file \"%s\": Invalid parts count %u in set %d",
									t_file.getFileName(), t_buffer, t_parts, t_set.m_id);

								t_parts = IItemSet::COUNT_OF_PARTS;
							}

							t_set._getEffects(t_parts).push_back(t_effect);
						}
					}
					else
					{
						Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\" in set %d!",
							t_file.getFileName(), t_buffer, t_set.m_id);
						return false;
					} //End of Set Effects

					if (t_file.readNext(t_buffer, T_BUF_SIZE)[0] != '}')
					{
						Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\" at the end of set %d!",
							t_file.getFileName(), t_buffer, t_set.m_id);
						return false;
					}

					++t_setCount;
					m_sets.push_back(new IItemSet(t_set));

					for (u32 i = 0; i < IItemSet::COUNT_OF_PARTS; ++i)
					{
						const_cast<IItemData*>(m_sets.last()->m_parts[i])->m_set = m_sets.last();
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\" in set %d!",
						t_file.getFileName(), t_buffer, t_set.m_id);
					return false;
				}
			} //end of Sets

			//Stattings
			else if (strcmp("RandomOptItem", t_buffer) == 0)
			{
				u32 t_id = t_file.readUInt();
				t_file.skipNext(3);

				if (IItemData::ms_randomOptions.size() <= t_id)
				{
					IItemData::ms_randomOptions.resize(t_id + 1);
				}

				IRandomOption &t_ro = IItemData::ms_randomOptions[t_id];

				t_ro.m_id = static_cast<ID>(t_id);

				if (t_file.readNext(t_buffer, T_BUF_SIZE)[0] == '{')
				{
					while (!t_file.end())
					{
						if (t_file.readNext(t_buffer, T_BUF_SIZE)[0] == '}')
							break;

						t_effect.Type = stat(t_buffer);
						t_effect.Amount = t_file.readInt();

						t_ro.m_effects.push_back(t_effect);
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Error in file \"%s\": Invalid identifier \"%s\" in statting %u!",
						t_file.getFileName(), t_buffer, t_id);
					return false;
				}
			} //end of Stattings
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open item prop etc file \"%s\"!", t_file.getFileName());
		return false;
	}

	Log::write(LOG_SUCCESS, "Loaded %u piercings, %u sets and %u stattings in %u ms",
		t_piercingCount, t_setCount, IItemData::ms_randomOptions.size(), CTime::system() - t_begin);

	return true;
}

bool IItemDataManager::_loadItems()
{
	bool t_success = false;

	if (m_settings->LoadSpc)
	{
		t_success = _loadItemsSpc();
	}
	else
	{
		if (_loadItemsNormally())
		{
			if (m_settings->SaveSpc)
			{
				t_success = saveItemsSpc(m_settings->SpcFileName.c_str());
			}
			else
			{
				t_success = true;
			}
		}
	}

	return t_success;
}

bool IItemDataManager::_loadItemsSpc()
{
	static const u32 TS_BUF_SIZE = 512;
	static char ts_buf1[TS_BUF_SIZE];

	u32 t_start = CTime::system();

	CByteArray t_spc;

	if (!t_spc.fromFile(m_settings->SpcFileName.c_str()))
	{
		Log::write(LOG_ERROR, "Could not open item spc file \"%s\"!", m_settings->SpcFileName.c_str());
		return false;
	}

	//Header
	if (!t_spc.getStringRaw(ts_buf1, 4)) //spc file version
	{
		Log::write(LOG_ERROR, "%u Invalid item spc file header!", t_spc.size());
		return false;
	}

	t_spc.getInt(); //blackorion version

	//Items
	u32 t_itemCount = t_spc.getInt();
	m_items.resize(t_itemCount);

	s32 t_id;

	if (strcmp("SPC0", ts_buf1) == 0) //spc file version 0
	{
		Log::write(LOG_WARNING, "Using old spc file (version %s)!", ts_buf1);

		FOR_EACH (m_items, i)
		{
			//Id
			t_id = t_spc.getInt();
			t_spc.getString(ts_buf1, TS_BUF_SIZE);

			//IdName
			m_items[i] = new IItemData(t_id, ts_buf1);

			//Name
			t_spc.getString(ts_buf1, TS_BUF_SIZE);
			m_items[i]->m_name = ts_buf1;

			//Version
			m_items[i]->m_version = t_spc.getByte();

			//IKs
			m_items[i]->m_ik1 = IItemData::itemKind1(t_spc.getShort());
			m_items[i]->m_ik2 = IItemData::itemKind2(t_spc.getShort());
			m_items[i]->m_ik3 = IItemData::itemKind3(t_spc.getShort());

			//Handed
			m_items[i]->m_handed = (t_spc.getByte() == IItemData::HD_TWO ?
				IItemData::HD_TWO : IItemData::HD_ONE);

			//Level
			m_items[i]->m_level = Limit<s16>(t_spc.getShort(), 0, 255);

			//Job
			m_items[i]->m_job = job(t_spc.getByte());

			//Sex
			m_items[i]->m_sex = sex(t_spc.getByte());

			//Cost
			m_items[i]->m_cost = Limit(t_spc.getInt(), 0, MAX_PENYA);

			//MaxStack
			m_items[i]->m_maxStack = Limit<s16>(t_spc.getShort(), 1, 9999);

			//Tradable
			m_items[i]->m_tradable = (t_spc.getByte() != 0);

			//Min/MaxAbility
			m_items[i]->m_attributeMin = t_spc.getInt();
			m_items[i]->m_attributeMax = t_spc.getInt();
		}
	}
	else if (strcmp("SPC1", ts_buf1) == 0) //spc file version 1
	{
		FOR_EACH (m_items, i)
		{
			//Id
			t_id = t_spc.getInt();
			t_spc.getString(ts_buf1, TS_BUF_SIZE);

			//IdName
			m_items[i] = new IItemData(t_id, ts_buf1);

			//Name
			t_spc.getString(ts_buf1, TS_BUF_SIZE);
			m_items[i]->m_name = ts_buf1;

			//Version
			m_items[i]->m_version = t_spc.getByte();

			//IKs
			m_items[i]->m_ik1 = IItemData::itemKind1(t_spc.getShort());
			m_items[i]->m_ik2 = IItemData::itemKind2(t_spc.getShort());
			m_items[i]->m_ik3 = IItemData::itemKind3(t_spc.getShort());

			//Handed
			m_items[i]->m_handed = (t_spc.getByte() == IItemData::HD_TWO ?
				IItemData::HD_TWO : IItemData::HD_ONE);

			//Level
			m_items[i]->m_level = Limit<s16>(t_spc.getShort(), 0, 255);

			//Job
			m_items[i]->m_job = job(t_spc.getByte());

			//Sex
			m_items[i]->m_sex = sex(t_spc.getByte());

			//Cost
			m_items[i]->m_cost = Limit(t_spc.getInt(), 0, MAX_PENYA);

			//MaxStack
			m_items[i]->m_maxStack = Limit<s16>(t_spc.getShort(), 1, 9999);

			//Tradable
			m_items[i]->m_tradable = (t_spc.getByte() != 0);

			//Min/MaxAbility
			m_items[i]->m_attributeMin = t_spc.getInt();
			m_items[i]->m_attributeMax = t_spc.getInt();

			//Effects
			m_items[i]->m_effects[0].Type = stat(t_spc.getInt());
			m_items[i]->m_effects[0].Amount = t_spc.getInt();
			m_items[i]->m_effects[1].Type = stat(t_spc.getInt());
			m_items[i]->m_effects[1].Amount = t_spc.getInt();
			m_items[i]->m_effects[2].Type = stat(t_spc.getInt());
			m_items[i]->m_effects[2].Amount = t_spc.getInt();
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Unknown item spc file version \"%s\"!", ts_buf1);
		return false;
	}

	u32 t_end = CTime::system();

	Log::write(LOG_SUCCESS, "Loaded %u items in %u ms", m_items.size(), t_end - t_start);

	return true;
}

bool IItemDataManager::_loadItemsNormally()
{
	TimeMs t_start = CTime::system();

	if (_loadItemIds() &&
		_loadItemTexts() &&
		_loadItemData())
	{
		TimeMs t_end = CTime::system();

		Log::write(LOG_SUCCESS, "Loaded %u items in %u ms", m_items.size(), t_end - t_start);

		return true;
	}

	return false;
}

bool IItemDataManager::_loadItemIds()
{
	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf1[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//:: Item Ids

	//no need to reallocate the array later

	if (t_file.open(m_settings->ItemIdFileName.c_str(), true))
	{
		ID t_id = 0;

		while (!t_file.end())
		{
			t_file.readNext(ts_buf1, TS_BUF_SIZE);

			//#define Makro
			if (strcmp("#define", ts_buf1) == 0)
			{
				t_file.readNext(ts_buf1, TS_BUF_SIZE);

				//ensure that this is an item definition
				if (ts_buf1[0] == 'I' &&
					ts_buf1[1] == 'I')
				{
					m_items.push_back(new IItemData(t_file.readInt(), ts_buf1));
				}
			}

			else
			{
				t_file.skipLine();
			}
		}

		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open item definition file \"%s\"",
			m_settings->ItemIdFileName.c_str());
	}

	return false;
}

bool IItemDataManager::_loadItemTexts()
{
	static const u32 TS_BUF_SIZE = 512;
	static char ts_buf1[TS_BUF_SIZE];
	static char ts_buf2[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//:: Item Texts

	//no need to resize later
	m_itemTexts.resize(10000);
	m_itemTexts.resize(0);

	if (t_file.open(m_settings->ItemTextFileName.c_str(), true))
	{
		const char *t_text;

		while (!t_file.end())
		{
			t_file.readNext(ts_buf1, TS_BUF_SIZE);
			t_file.readLine(ts_buf2, TS_BUF_SIZE);
			t_text = trim_front(ts_buf2);

			if (t_text[0])
			{
				m_itemTexts.push_back(
					ItemText(
					xtoi(ts_buf1 + 17),
					t_text
					));
			}
		}

		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open item text file \"%s\"",
			m_settings->ItemTextFileName.c_str());
	}

	return false;
}

bool IItemDataManager::_loadItemData()
{
	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf1[TS_BUF_SIZE];
	static char ts_buf2[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//:: Item Data

	u32 t_lines = 0;

	if (t_file.open(m_settings->ItemDataFileName.c_str(), true))
	{
		CArray<IItemData*> t_tempItems = m_items;

		u32 i, c = m_items.size();

		IItemData *t_item;
		IItemData t_pseudoItem;

		s32 t_version;

		while (!t_file.end())
		{
			//1 Version
			t_version = t_file.readInt();

			//2 Titel
			t_file.readNext(ts_buf1, TS_BUF_SIZE);

			t_item = 0;
			for (i = 0; i < c; i++)
			{
				if (strcmp(t_tempItems[i]->m_idName.c_str() + 3, ts_buf1 + 3) == 0)
				{
					t_item = t_tempItems[i];
					t_tempItems.erase(i);
					--c;
					break;
				}
			}

			if (!t_item)
			{
				t_item = &t_pseudoItem;
			}

			t_item->m_version = t_version;

			//3 Name

			t_item->m_name =
				_getItemText(ts_buf2, TS_BUF_SIZE, atoi(t_file.readNext(ts_buf1, TS_BUF_SIZE) + 17));

			//4 Num (u32) (?)
			t_file.skipNext();

			//5 PackSize
			t_item->m_maxStack = t_file.readInt();

			//6 IK1
			t_item->m_ik1 = IItemData::itemKind1(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			//7 IK2
			t_item->m_ik2 = IItemData::itemKind2(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			//8 IK3
			t_item->m_ik3 = IItemData::itemKind3(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			//9 Job
			t_item->m_job = job(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			//10 Permanence (bool) (?)
			t_file.skipNext();

			//11 Useable (bool) (?)
			t_file.skipNext();

			//12 Sex
			t_item->m_sex = sex(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			//13 Cost
			t_item->m_cost = t_file.readInt();

			//14 Endurance (u32) [Haltbarkeit] (?)
			t_file.skipNext();

			//15 Abrasion (u32) [Abnutzung] (?)
			t_file.skipNext();

			//16 MaxRepair (u32) (?)
			t_file.skipNext();

			//17 Handed
			if (strcmp(t_file.readNext(ts_buf1, TS_BUF_SIZE), "HD_TWO") == 0)
				t_item->m_handed = IItemData::HD_TWO;
			else
				t_item->m_handed = IItemData::HD_ONE;

			//18 Flag (u32) (?)
			t_file.skipNext();

			//19 Parts (?)
			//...
			t_file.skipNext();

			//20 Partsub (?)
			//...
			t_file.skipNext();

			//21 Partfile (bool) (?)
			t_file.skipNext();

			//22 Exclusive (u32) (?)
			t_file.skipNext();

			//23 BasePartsIgnore (u32) (?)
			t_file.skipNext();

			//24 ItemLV (u32) (?) //nicht das ben. Level!
			t_file.skipNext();

			//25 ItemRare (u32) (?) //= ItemLV
			t_file.skipNext();

			//26 Shopable (bool) (?)
			t_item->m_tradable = t_file.readBool();

			//27 Log (bool) (?)
			t_file.skipNext();

			//28 Charged (bool) (?)
			t_file.skipNext();

			//29 LinkKindBullet (u32) (?)
			t_file.skipNext();

			//30 LinkKind (u32) (?)
			t_file.skipNext();

			//31 AbilityMin
			t_item->m_attributeMin = t_file.readInt();

			//32 AbilityMax
			t_item->m_attributeMax = t_file.readInt();

			//33 ItemType (enum) (?)
			t_file.skipNext();

			//34 ItemEAtk (u16) (?)
			t_file.skipNext();

			//35 Parry (u32) (?)
			t_file.skipNext();

			//36 BlockRating (u32) (?)
			t_file.skipNext();

			//37 AddSkillMin (u32) (?)
			t_file.skipNext();

			//38 AddSkillMax (u32) (?)
			t_file.skipNext();

			//39 AttackStyle (u32) (?)
			t_file.skipNext();

			//40 WeaponType (u32) (?)
			t_file.skipNext();

			//41 ItemAtkOrder1 (u32) (?)
			t_file.skipNext();

			//42 ItemAtkOrder2 (u32) (?)
			t_file.skipNext();

			//43 ItemAtkOrder3 (u32) (?)
			t_file.skipNext();

			//44 ItemAtkOrder4 (u32) (?)
			t_file.skipNext();

			//45 ContinuousPain (bool) (?)
			t_file.skipNext();

			//46 ShellQuantity (u32) (?)
			t_file.skipNext();

			//47 Recoil (u32) (?)
			t_file.skipNext();

			//48 LoadingTime (u32) (?)
			t_file.skipNext();

			//49 AdjHitRate (n) (?)
			t_file.skipNext();

			//50 AttackSpeed (float) (?)
			t_file.skipNext();

			//51 DmgShift (u32) (?)
			t_file.skipNext();

			//52 AttackRange (u32)
			//...
			t_file.skipNext();

			//53 Probability (u32) (?)
			t_file.skipNext();

			//54 DestParam1 (u32) (?)
			t_file.readNext(ts_buf1, TS_BUF_SIZE);
			if (ts_buf1[0] != '=')
			{
				t_item->m_effects[0].Type = stat(ts_buf1);
			}

			//55 DestParam2 (u32) (?)
			t_file.readNext(ts_buf1, TS_BUF_SIZE);
			if (ts_buf1[0] != '=')
			{
				t_item->m_effects[1].Type = stat(ts_buf1);
			}

			//56 DestParam3 (u32) (?)
			t_file.readNext(ts_buf1, TS_BUF_SIZE);
			if (ts_buf1[0] != '=')
			{
				t_item->m_effects[2].Type = stat(ts_buf1);
			}

			//57 AdjParamVal1 (u32) (?)
			t_item->m_effects[0].Amount = t_file.readInt();

			//58 AdjParamVal2 (u32) (?)
			t_item->m_effects[1].Amount = t_file.readInt();

			//59 AdjParamVal3 (u32) (?)
			t_item->m_effects[2].Amount = t_file.readInt();

			//60 ChgParamVal1 (u32) (?)
			t_file.skipNext();

			//61 ChgParamVal2 (u32) (?)
			t_file.skipNext();

			//62 ChgParamVal3 (u32) (?)
			t_file.skipNext();

			//63 destData1 (u32) (?)
			t_file.skipNext();

			//64 destData2 (u32) (?)
			t_file.skipNext();

			//65 destData3 (u32) (?)
			t_file.skipNext();

			//66 activeskill (u32) (?)
			t_file.skipNext();

			//67 activeskillLv (u32) (?)
			t_file.skipNext();

			//68 activeskillper (u32) (?)
			t_file.skipNext();

			//69 ReqMp (u32) (?)
			t_file.skipNext();

			//70 ReqFp (u32) (?)
			t_file.skipNext();

			//71 ReqDisLV (u32) (?)
			t_file.skipNext();

			//72 ReSkill1 (u32) (?)
			t_file.skipNext();

			//73 ReSkillLevel1 (u32) (?)
			t_file.skipNext();

			//74 ReSkill2 (u32) (?)
			t_file.skipNext();

			//75 ReSkillLevel2 (u32) (?)
			t_file.skipNext();

			//76 SkillReadyType (u32) (?)
			t_file.skipNext();

			//77 SkillReady (u32) (?)
			t_file.skipNext();

			//78 SkillRange (u32) (?)
			t_file.skipNext();

			//79 SfxElemental (u32) (?)
			t_file.skipNext();

			//80 SfxObj (u32) (?)
			t_file.skipNext();

			//81 SfxObj2 (u32) (?)
			t_file.skipNext();

			//82 SfxObj3 (u32) (?)
			t_file.skipNext();

			//83 SfxObj4 (u32) (?)
			t_file.skipNext();

			//84 SfxObj5 (u32) (?)
			t_file.skipNext();

			//85 UseMotion (u32) (?)
			t_file.skipNext();

			//86 CircleTime (u32) (?)
			t_file.skipNext();

			//87 SkillTime (u32) (?)
			t_file.skipNext();

			//88 ExeTarget (u32) (?)
			t_file.skipNext();

			//89 UseChance (u32) (?)
			t_file.skipNext();

			//90 SpellRegion (u32) (?)
			t_file.skipNext();

			//91 SpellType (u32) (?)
			t_file.skipNext();

			//92 ReferStat1 (u32) (?) //WEAPON_GENERAL...
			t_file.skipNext();

			//93 ReferStat2 (u32) (?)
			t_file.skipNext();

			//94 ReferTarget1 (u32) (?)
			t_file.skipNext();

			//95 ReferTarget2 (u32) (?)
			t_file.skipNext();

			//96 ReferValue1 (u32) (?)
			t_file.skipNext();

			//97 ReferValue2 (u32) (?)
			t_file.skipNext();

			//98 SkillType (u32) (?)
			t_file.skipNext();

			//99 ItemResistElecricity (f) (?)
			t_file.skipNext();

			//100 ItemResistFire (f) (?)
			t_file.skipNext();

			//101 ItemResistWind (f) (?)
			t_file.skipNext();

			//102 ItemResistWater (f) (?)
			t_file.skipNext();

			//103 ItemResistEarth (f) (?)
			t_file.skipNext();

			//104 Evildoing (n) (?)
			t_file.skipNext();

			//105 ExpertLV (u32) (?)
			t_file.skipNext();

			//106 ExpertMax () (?)
			t_file.skipNext();

			//107 SubDefine (u32) (?)
			t_file.skipNext();

			//108 Exp (u32) (?)
			t_file.skipNext();

			//109 ComboStyle (u32) (?)
			t_file.skipNext();

			//110 FlightSpeed (f) (?)
			t_file.skipNext();

			//111 FlightLRAngle (f) (?)
			t_file.skipNext();

			//112 FlightTBAngle (f) (?)
			t_file.skipNext();

			//113 FlightLimit (u32) (?)
			t_file.skipNext();

			//114 FFuelReMax (u32) (?)
			t_file.skipNext();

			//115 AFuelReMax (u32) (?)
			t_file.skipNext();

			//116 FuelRe (u32) (?)
			t_file.skipNext();

			//117 LimitLevel1 (u32) (?)
			t_item->m_level = t_file.readInt();

			//118 Reflect (u32) (?)
			t_file.skipNext();

			//119 SndAttack1 (u32) (?)
			t_file.skipNext();

			//120 SndAttack2 (u32) (?)
			t_file.skipNext();

			//121 Icon (sz) (?)
			t_file.skipString("\"\"\"");

			//122 QuestID (u32) (?)
			t_file.skipNext();

			//123 TextFile (sz) (?)
			t_file.skipString("\"\"\"");

			//124 Comment (sz) (?)
			t_file.skipNext();
		}

		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open item data file \"%s\"",
			m_settings->ItemDataFileName.c_str());
	}

	return false;
}

const char *IItemDataManager::_getItemText(char *_dest, u32 _destSize, s32 _id)
{
	FOR_EACH (m_itemTexts, i)
	{
		if (m_itemTexts[i].Id == _id)
		{
			xstrcpy(_dest, _destSize, m_itemTexts[i].Value.c_str());

			m_itemTexts.erase_fast(i);

			return _dest;
		}
	}

	return "";
}
