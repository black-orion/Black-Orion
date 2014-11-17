#include "WorldDataManager.h"
#include "MoverData.h"
#include "SpawnData.h"
#include "NpcData.h"
#include "../shared/ItemData.h"
#include "../shared/ItemDataManager.h"
#include "../shared/Log.h"


IWorldDataManager::IWorldDataManager(IWorldDataSettings *_settings)
	: m_settings(_settings)
	, m_itemMngr(&_settings->Items)
{
	FDASSERT(m_settings);
}

IWorldDataManager::~IWorldDataManager()
{
	FOR_EACH (m_npcs, i)
	{
		delete m_npcs[i];
	}

	FOR_EACH (m_spawns, i)
	{
		delete m_spawns[i];
	}

	FOR_EACH (m_movers, i)
	{
		delete m_movers[i];
	}
}

bool IWorldDataManager::load()
{
	return (
		m_itemMngr.load_world() &&
		_loadMovers() &&
		_loadDrops() &&
		_loadSpawns() &&
		_loadNpcs() &&
		_loadExp() &&
		_loadJobInfos()
		);
}

IItemDataManager *IWorldDataManager::getItemManager()
{
	return &m_itemMngr;
}

u32 IWorldDataManager::getMoverCount() const
{
	return m_movers.size();
}

const IMoverData *IWorldDataManager::getMoverByNumber(u32 _num) const
{
	FDASSERT(_num < m_movers.size());

	return m_movers[_num];
}

const IMoverData *IWorldDataManager::getMoverById(const char *_idName) const
{
	FOR_EACH (m_movers, i)
	{
		if (strcmp(m_movers[i]->m_idName.c_str(), _idName) == 0)
			return m_movers[i];
	}

	return 0;
}

const IMoverData *IWorldDataManager::getMoverById(ID _id) const
{
	FOR_EACH (m_movers, i)
	{
		if (m_movers[i]->m_id == _id)
			return m_movers[i];
	}

	return 0;
}

u32 IWorldDataManager::getSpawnCount() const
{
	return m_spawns.size();
}

const ISpawnData *IWorldDataManager::getSpawnByNumber(u32 _num) const
{
	FDASSERT(_num < m_spawns.size());

	return m_spawns[_num];
}

const ISpawnData *IWorldDataManager::getSpawnById(const char *_fileName) const
{
	FOR_EACH (m_spawns, i)
	{
		if (strcmp(m_spawns[i]->m_fileName.c_str(), _fileName) == 0)
		{
			return m_spawns[i];
		}
	}

	return 0;
}

u32 IWorldDataManager::getNpcCount() const
{
	return m_npcs.size();
}

const INpcData *IWorldDataManager::getNpcByNumber(u32 _num) const
{
	FDASSERT(_num < m_npcs.size());

	return m_npcs[_num];
}

u32 IWorldDataManager::getLevelCount() const
{
	return m_levelExp.size();
}

EXP IWorldDataManager::getLevelExp(u32 _level) const
{
	FDASSERT(!m_levelExp.empty());

	if (_level < m_levelExp.size())
	{
		return m_levelExp[_level].LevelUp;
	}
	else
	{
		return m_levelExp.last().LevelUp;
	}
}

EXP IWorldDataManager::getExpLost(u32 _level) const
{
	FDASSERT(!m_levelExp.empty());

	if (_level < m_levelExp.size())
	{
		return m_levelExp[_level].DeathLost;
	}
	else
	{
		return m_levelExp.last().DeathLost;
	}
}

const ISpawnData *IWorldDataManager::createSpawn(const IMoverData *_mover, u32 _count, const CPoint &_pos,
												 ID _world, f32 _range, s16 _size, RATE _aggroRate,
												 TimeMs _respawnTime, bool _moving, TimeMs _movingInterval,
												 RATE _expRate, RATE _penyaRate, RATE _dropRate)
{
	FDASSERT(_mover);

	ISpawnData *t_newSpawn = new ISpawnData();

	t_newSpawn->m_mobs.push_back(_mover);
	t_newSpawn->m_maximum = _count;
	t_newSpawn->m_pos = _pos;
	t_newSpawn->m_world = _world;
	t_newSpawn->m_range = _range;
	t_newSpawn->m_size = _size;
	t_newSpawn->m_aggro = _aggroRate;
	t_newSpawn->m_respawnTime = _respawnTime;
	t_newSpawn->m_moving = _moving;
	t_newSpawn->m_moveInterval = _movingInterval;
	t_newSpawn->m_exp = _expRate;
	t_newSpawn->m_penya = _penyaRate;
	t_newSpawn->m_drop = _dropRate;

	m_spawns.push_back(t_newSpawn);
	return t_newSpawn;
}

IMoverData *IWorldDataManager::_getMover(const char *_idName)
{
	FDASSERT(_idName);

	FOR_EACH (m_movers, i)
	{
		if (strcmp(m_movers[i]->m_idName.c_str(), _idName) == 0)
			return m_movers[i];
	}

	return 0;
}

IMoverData *IWorldDataManager::_getMover(ID _id)
{
	FOR_EACH (m_movers, i)
	{
		if (m_movers[i]->getId() == _id)
		{
			return m_movers[i];
		}
	}

	return 0;
}

bool IWorldDataManager::_loadMovers()
{
	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf1[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//:: Movers

	IMoverData *t_newMover;

	//read mover ids
	if (t_file.open(m_settings->MoverIdFileName.c_str(), true))
	{
		ID t_id = 0;

		while (!t_file.end())
		{
			t_file.readNext(ts_buf1, TS_BUF_SIZE);

			//skips #define's
			if (strcmp("#define", ts_buf1) == 0)
			{
				continue;
			}

			//check the token
			else if (ts_buf1[0] == 0)
			{
				break;
			}

			//create a mover
			else
			{
				t_newMover = new IMoverData();

				t_newMover->m_idName = ts_buf1;

				t_newMover->m_id = t_file.readInt();

				m_movers.push_back(t_newMover);
			}
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the mover id file \"%s\"", m_settings->MoverIdFileName.c_str());
		return false;
	}

	//read mover data
	if (t_file.open(m_settings->MoverDataFileName.c_str()))
	{
		IMoverData *t_mover;

		while (!t_file.end())
		{
			t_mover = _getMover(t_file.readNext(ts_buf1, TS_BUF_SIZE));

			if (t_mover)
			{
				//name
				t_file.skipNext();

				//AI
				t_file.skipNext();

				//STR
				t_file.readInt();

				//STA
				t_file.readInt();

				//DEX
				t_file.readInt();

				//INT
				t_file.readInt();

				//Hit rate
				t_mover->m_hit = t_file.readInt();

				//Evasion rate
				t_mover->m_evasion = t_file.readInt();

				//race
				t_file.skipNext();

				//belligerence
				t_file.skipNext();

				//gender
				t_file.skipNext();

				//Level
				t_mover->m_level = t_file.readInt();

				//Flightlevel
				t_file.skipNext();

				//Size
				t_file.skipNext();

				//Class
				t_file.readNext(ts_buf1, TS_BUF_SIZE);

				if (strcmp("RANK_LOW", ts_buf1) == 0)
				{
					t_mover->m_class = IMoverData::RANK_LOW;
				}
				else if (strcmp("RANK_NORMAL", ts_buf1) == 0)
				{
					t_mover->m_class = IMoverData::RANK_NORMAL;
				}
				else if (strcmp("RANK_CAPTAIN", ts_buf1) == 0)
				{
					t_mover->m_class = IMoverData::RANK_CAPTAIN;
				}
				else if (strcmp("RANK_BOSS", ts_buf1) == 0)
				{
					t_mover->m_class = IMoverData::RANK_BOSS;
				}
				else if (strcmp("RANK_SUPER", ts_buf1) == 0)
				{
					t_mover->m_class = IMoverData::RANK_SUPER;
				}

				//IfPart
				t_file.skipNext();

				//Karma
				t_file.skipNext();

				//Usable
				t_file.skipNext();

				//Action radius
				t_file.skipNext();

				//LimitAtk
				t_mover->m_atkMin = t_file.readInt();
				t_mover->m_atkMax = t_file.readInt();

				//Atk1/2/3 (mob weapon)
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//HorizontalRate VerticalRate DiagonalRate ThrustRate ChestRate HeadRate ArmRate LegRate
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//AttackSpeed
				t_file.skipNext();

				//ReAttackDelay
				t_mover->m_attackDelay = t_file.readUInt();

				//HP/MP/DEF
				t_mover->m_hp = t_file.readInt();
				t_file.skipNext();
				t_mover->m_def = t_file.readInt();

				//abrasion, hardness, AdjAtkDelay
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//ElementType
				t_mover->m_element = E_ELEMENT(Limit<u32>(t_file.readUInt(), ELE_NONE, ELE_EARTH));

				//ElementAtk
				t_file.skipNext();

				//HideLevel
				t_file.skipNext();

				//Speed
				t_file.skipNext();

				//Shelter
				t_file.skipNext();

				//Flying
				t_file.skipNext();

				//JumpIng
				t_file.skipNext();

				//AirJump
				t_file.skipNext();

				//Taming
				t_file.skipNext();

				//ResisMagic, Elec, Fire, Wind, Water, Earth
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//Cash
				t_file.skipNext();

				//SourceMaterial, MaterialAmount
				t_file.skipNext();
				t_file.skipNext();

				//Cohesion, HoldingTime, CorrectionValue
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//EXP, FXP
				t_mover->m_exp = t_file.readInt64();
				t_file.skipNext();

				//BodyState, AddAbility, Killable
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//3x (VirtItem, VirtType)
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//SndAtk1, SndAtk2
				t_file.skipNext();
				t_file.skipNext();

				//SndDie1, SndDie2
				t_file.skipNext();
				t_file.skipNext();

				//SndDmg1, SndDmg2, SndDmg3
				t_file.skipNext();
				t_file.skipNext();
				t_file.skipNext();

				//SndIdle1, SndIdle2
				t_file.skipNext();
				t_file.skipNext();

				//Comment
				t_file.skipNext();
			}

			else
			{
				Log::write(LOG_ERROR, "Mover \"%s\" in file \"%s\" does not exist", ts_buf1,
					m_settings->MoverDataFileName.c_str());

				return false;
			}
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the mover data file \"%s\"",
			m_settings->MoverDataFileName.c_str());

		return false;
	}

	Log::write(LOG_SUCCESS, "Loaded %u movers", m_movers.size());

	return true;
}

bool IWorldDataManager::_loadDrops()
{
	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf1[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//load the folder
	CFileList t_folder;
	const char *t_fileEnding = 0;

	IMoverData *t_mover = 0;

	ID t_moverId = 0;

	RATE t_dropRate = 0.0f;

	const IItemData *t_item = 0;

	IItemProperties t_itemProp;

	ID t_itemId = 0;

	RATE t_itemDropRate = 0.0f;

	bool t_clean = false;

	bool t_indep = false;

	u32 t_dropFiles = 0;

	if (t_folder.scan(m_settings->DropFolder.c_str(), false))
	{
		for (u32 i = 0; i < t_folder.getFileCount(); ++i)
		{
			//check the file ending
			t_fileEnding = strrchr(t_folder.getFile(i).Name.c_str(), '.');
			if (t_fileEnding &&
				xstricmp(m_settings->DropFileEnding.c_str(), t_fileEnding) == 0)
			{
				//load the spawn file
				sprintf(ts_buf1, "%s%s", m_settings->DropFolder.c_str(),
					t_folder.getFile(i).Name.c_str());

				if (t_file.open(ts_buf1, true))
				{
					++t_dropFiles;

					t_mover = 0;
					t_dropRate = 1.0f;

					while (!t_file.end())
					{
						t_file.readNext(ts_buf1, TS_BUF_SIZE);

						//mob command
						if (xstricmp("MOB", ts_buf1) == 0)
						{
							t_moverId = t_file.readInt();
							t_mover = _getMover(t_moverId);

							if (!t_mover)
							{
								Log::write(LOG_WARNING, "Drop file \"%s\": Mover %d does not exist",
									t_file.getFileName(), t_moverId);
								break;
							}
						}

						else if (!t_mover)
						{
							Log::write(LOG_WARNING, "Drop file \"%s\": Mover must be defined first!",
									t_file.getFileName());
							break;
						}

						//penya command
						else if (xstricmp("PENYA", ts_buf1) == 0)
						{
							t_mover->m_penyaMin = Limit(t_file.readInt(),
								0, MAX_PENYA);

							t_mover->m_penyaMax = Limit(t_file.readInt(),
								t_mover->m_penyaMin, MAX_PENYA);
						}

						//rate command
						else if (xstricmp("RATE", ts_buf1) == 0)
						{
							t_dropRate = t_file.readDouble();
						}

						//upgraded drop rates
						else if (xstricmp("UPGRADERATE", ts_buf1) == 0)
						{
							t_file.readUInt(); //Upgrade
							t_file.readDouble(); //Chance
						}

						//item
						else if (xstricmp("ITEM", ts_buf1) == 0)
						{
							t_clean = false;
							t_indep = false;

							//allow multiple modifiers here
							while (true)
							{
								t_file.readNext(ts_buf1, TS_BUF_SIZE);

								//clean modifier
								if (xstricmp("CLEAN", ts_buf1) == 0)
								{
									t_clean = true;
								}

								//independence modifier
								else if (xstricmp("INDEPENDENT", ts_buf1) == 0)
								{
									t_indep = true;
								}

								else
								{
									break;
								}
							}

							t_itemId = xtoi(ts_buf1);

							t_item = m_itemMngr.getItemById(t_itemId);

							if (t_item)
							{
								t_itemDropRate = t_file.readDouble();

								//if independent, dont add the global drop rate
								if (!t_indep)
								{
									t_itemDropRate *= t_dropRate;
								}

								//no need to add the item if its rate is zero
								if (t_itemDropRate > 0.0f)
								{
									IMoverData::Drop *t_drop =
										new IMoverData::Drop(t_item, t_itemDropRate, t_clean);

									t_mover->m_drops.push_back(t_drop);
								}
							}
							else
							{
								Log::write(LOG_WARNING, "Drop file \"%s\": Undefined ITEM %d!",
									t_file.getFileName(), t_itemId);
							}
						}

						//itemspc
						else if (xstricmp("ITEMSPC", ts_buf1) == 0)
						{
							t_indep = false;

							t_itemProp.clear();
							t_itemProp.setCount(1);

							while (!t_file.end())
							{
								t_file.readNext(ts_buf1, TS_BUF_SIZE);

								//id
								if (xstricmp("ID", ts_buf1) == 0)
								{
									t_itemId = t_file.readInt();
									t_item = m_itemMngr.getItemById(t_itemId);

									if (t_item)
									{
										t_itemProp.setData(t_item);
									}
									else
									{
										Log::write(LOG_WARNING, "Drop file \"%s\": Undefined item ID %d!",
											t_file.getFileName(), t_itemId);
									}
								}

								//count
								else if (xstricmp("COUNT", ts_buf1) == 0)
								{
									t_itemProp.setCount(Limit<s32>(t_file.readInt(), 0, IItemPack::COUNT_MAX));
								}

								//rate
								else if (xstricmp("RATE", ts_buf1) == 0)
								{
									t_itemDropRate = t_file.readDouble();

									if (!t_indep)
									{
										t_itemDropRate *= t_dropRate;
									}
								}

								//upgr
								else if (xstricmp("UPGR", ts_buf1) == 0)
								{
									t_itemProp.setUpgrade(
										Limit<s32>(t_file.readInt(), 0, IItemPack::UPGRADE_MAX));
								}

								//ele
								else if (xstricmp("ELE", ts_buf1) == 0)
								{
									t_itemProp.setElement(element(t_file.readInt()));
								}

								//eleup
								else if (xstricmp("ELEUP", ts_buf1) == 0)
								{
									t_itemProp.setElementalUpgrade(
										Limit<s32>(t_file.readInt(), 0, IItemPack::UPGRADE_ELE_MAX));
								}

								//awak
								else if (xstricmp("AWAK", ts_buf1) == 0)
								{
									t_file.skipNext();
								}

								//stat
								else if (xstricmp("STAT", ts_buf1) == 0)
								{
									t_file.skipNext();
								}

								//slots
								else if (xstricmp("SLOTS", ts_buf1) == 0)
								{
									s32 t_slotCount = t_file.readInt();

									//check slot count
									if (t_slotCount < 0 ||
										t_slotCount > IItemPack::SLOT_COUNT_MAX)
									{
										Log::write(LOG_ERROR, "Drop file \"%s\": Invalid slot count %d!",
												t_file.getFileName(), t_slotCount);
									}

									while (t_slotCount--)
									{
										t_itemId = t_file.readInt();
										t_item = m_itemMngr.getItemById(t_itemId);

										if (t_item)
										{
											t_itemProp.addSlot(t_item);
										}
										else
										{
											Log::write(LOG_WARNING, "Drop file \"%s\": Undefined item %d!",
												t_file.getFileName(), t_itemId);
										}
									}
								}

								//independent
								else if (xstricmp("INDEPENDENT", ts_buf1) == 0)
								{
									t_indep = true;
								}

								//end
								else if (xstricmp("ENDSPC", ts_buf1) == 0)
								{
									break;
								}

								//unknown
								else if (ts_buf1[0])
								{
									Log::write(LOG_WARNING, "Unknown identifier '%s' in drop file \"%s\"",
										ts_buf1, t_file.getFileName());
								}
							}

							if (t_itemProp.isValid())
							{
								IMoverData::DropSpc *t_drop = new IMoverData::DropSpc(t_itemProp, t_itemDropRate);

								t_mover->m_drops.push_back(t_drop);
							}
							else
							{
								Log::write(LOG_WARNING, "Invalid spc item in drop file \"%s\"",
									t_file.getFileName());
							}
						}

						//unknown
						else if (ts_buf1[0])
						{
							Log::write(LOG_WARNING, "Unknown identifier '%s' in drop file \"%s\"",
								ts_buf1, t_file.getFileName());
						}
					}

					//calculate the drop rates
					if (!t_mover)
					{
						FOR_EACH (t_mover->m_drops, i)
						{
							t_mover->m_drops[i]->Chance *= t_dropRate;
						}
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Could not open drop file \"%s\"!",
						ts_buf1);
				}
			}
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the drop folder \"%s\"!",
			m_settings->DropFolder.c_str());
		return false;
	}

	u32 t_totalDrops = 0;
	FOR_EACH (m_movers, i)
	{
		t_totalDrops += m_movers[i]->m_drops.size();
	}

	Log::write(LOG_SUCCESS, "Loaded %u drop files (%u total items)",
		t_dropFiles, t_totalDrops);

	return true;
}

bool IWorldDataManager::_loadSpawns()
{
	static const u32 TS_BUF_SIZE = 256;
	static char ts_buf1[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//load the folder
	CFileList t_folder;
	const char *t_fileEnding;

	ISpawnData *t_spawn;

	const IMoverData *t_mover;

	s32 t_moverId;

	if (t_folder.scan(m_settings->SpawnFolder.c_str(), false))
	{
		for (u32 i = 0; i < t_folder.getFileCount(); ++i)
		{
			//check the file ending
			t_fileEnding = strrchr(t_folder.getFile(i).Name.c_str(), '.');
			if (t_fileEnding &&
				xstricmp(m_settings->SpawnFileEnding.c_str(), t_fileEnding) == 0)
			{
				//load the spawn file
				sprintf(ts_buf1, "%s%s", m_settings->SpawnFolder.c_str(),
					t_folder.getFile(i).Name.c_str());

				if (t_file.open(ts_buf1, true))
				{
					t_spawn = new ISpawnData();
					t_spawn->m_fileName = ts_buf1;

					while (!t_file.end())
					{
						t_file.readNext(ts_buf1, TS_BUF_SIZE);

						//mob command
						if (xstricmp("MOB", ts_buf1) == 0)
						{
							t_moverId = t_file.readInt();
							t_mover = getMoverById(t_moverId);

							if (t_mover &&
								t_mover->getId() != 1021) //improv
							{
								t_spawn->m_mobs.push_back(t_mover);
							}
							else
							{
								Log::write(LOG_WARNING, "Spawn file \"%s\": Mover %d does not exist",
									t_file.getFileName(), t_moverId);
							}
						}

						//count command
						else if (xstricmp("COUNT", ts_buf1) == 0)
						{
							t_spawn->m_maximum = t_file.readUInt();
						}

						//moving command
						else if (xstricmp("MOVING", ts_buf1) == 0)
						{
							t_spawn->m_moving = t_file.readBool();
						}

						//move distance
						else if (xstricmp("MOVEDISTANCE", ts_buf1) == 0)
						{
							t_spawn->m_moveDistance = Limit(t_file.readFloat(), 0.0f, 100.0f);
						}

						//moveInterval command
						else if (xstricmp("MOVINGINTERVAL", ts_buf1) == 0)
						{
							t_spawn->m_moveInterval = t_file.readUInt();
						}

						//exp command
						else if (xstricmp("EXP", ts_buf1) == 0)
						{
							t_spawn->m_exp = t_file.readDouble();
						}

						//drop command
						else if (xstricmp("DROP", ts_buf1) == 0)
						{
							t_spawn->m_drop = t_file.readDouble();
						}

						//penya command
						else if (xstricmp("PENYA", ts_buf1) == 0)
						{
							t_spawn->m_penya = t_file.readDouble();
						}

						//position command
						else if (xstricmp("POS", ts_buf1) == 0 ||
							xstricmp("POSITION", ts_buf1) == 0)
						{
							t_spawn->m_pos.X = t_file.readFloat();
							t_spawn->m_pos.Y = t_file.readFloat();
							t_spawn->m_pos.Z = t_file.readFloat();
						}

						//size command
						else if (xstricmp("SIZE", ts_buf1) == 0)
						{
							t_spawn->m_size = static_cast<s16>(t_file.readInt());
						}

						//world command
						else if (xstricmp("WORLD", ts_buf1) == 0)
						{
							t_spawn->m_world = t_file.readInt();
						}

						//range command
						else if (xstricmp("RANGE", ts_buf1) == 0)
						{
							t_spawn->m_range = t_file.readFloat();
						}

						//aggro command
						else if (xstricmp("AGGRO", ts_buf1) == 0)
						{
							t_spawn->m_aggro = t_file.readDouble();
						}

						//respawn time command
						else if (xstricmp("RESPAWNTIME", ts_buf1) == 0)
						{
							t_spawn->m_respawnTime = t_file.readUInt();
						}

						//unknown
						else if (ts_buf1[0])
						{
							Log::write(LOG_WARNING, "Unknown command '%s' in spawn file \"%s\"",
								ts_buf1, t_file.getFileName());
						}
					}

					if (t_spawn->getMoverCount())
					{
						if (t_spawn->getMoverCount() > 1000)
						{
							Log::write(LOG_WARNING, "More than 1000 Mobs in spawn file \"%s\"!",
								t_spawn->getMoverCount());
						}

						m_spawns.push_back(t_spawn);
					}
					else
					{
						Log::write(LOG_WARNING, "No movers in spawn file \"%s\"!", t_spawn->getFileName());
						delete t_spawn;
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Could not open spawn file \"%s\"!", ts_buf1);
				}
			}
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the spawn folder \"%s\"!", m_settings->SpawnFolder.c_str());
		return false;
	}

	Log::write(LOG_SUCCESS, "Loaded %u spawns", m_spawns.size());

	return true;
}

bool IWorldDataManager::_loadNpcs()
{
	static const u32 TS_BUF_SIZE = 1024;
	static char ts_buf1[TS_BUF_SIZE];

	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	//load the folder
	CFileList t_folder;
	const char *t_fileEnding;

	INpcData *t_npc;

	s32 t_moverId;

	const IItemData *t_item;

	if (t_folder.scan(m_settings->NpcFolder.c_str(), false))
	{
		for (u32 i = 0; i < t_folder.getFileCount(); ++i)
		{
			//check the file ending
			t_fileEnding = strrchr(t_folder.getFile(i).Name.c_str(), '.');
			if (t_fileEnding &&
				xstricmp(m_settings->NpcFileEnding.c_str(), t_fileEnding) == 0)
			{
				//load the spawn file
				sprintf(ts_buf1, "%s%s", m_settings->NpcFolder.c_str(),
					t_folder.getFile(i).Name.c_str());

				if (t_file.open(ts_buf1, true))
				{
					t_npc = new INpcData();

					t_npc->m_fileName = ts_buf1;

					while (!t_file.end())
					{
						t_file.readNext(ts_buf1, TS_BUF_SIZE);

						//mover command
						if (xstricmp("MOVER", ts_buf1) == 0)
						{
							t_moverId = t_file.readInt();

							t_npc->m_mover = getMoverById(t_moverId);

							if (!t_npc->m_mover)
							{
								Log::write(LOG_WARNING, "Unknown mover '%d' in npc file \"%s\"",
									t_moverId, t_file.getFileName());
							}
						}

						//name
						else if (xstricmp("NAME", ts_buf1) == 0)
						{
							t_npc->m_name = t_file.readString();
						}

						//dialog
						else if (xstricmp("DIALOG", ts_buf1) == 0)
						{
							t_npc->m_dialogFileName = t_file.readString();
						}

						//position
						else if (xstricmp("POS", ts_buf1) == 0)
						{
							t_npc->m_pos.X = t_file.readFloat();
							t_npc->m_pos.Y = t_file.readFloat();
							t_npc->m_pos.Z = t_file.readFloat();
						}

						//world
						else if (xstricmp("WORLD", ts_buf1) == 0)
						{
							t_npc->m_worldId = t_file.readInt();
						}

						//rotation
						else if (xstricmp("ROTATION", ts_buf1) == 0)
						{
							t_npc->m_rotation = t_file.readInt();
						}

						//size
						else if (xstricmp("SIZE", ts_buf1) == 0)
						{
							t_npc->m_size = t_file.readInt();
						}

						//page
						else if (xstricmp("PAGE", ts_buf1) == 0)
						{
							u32 t_page = static_cast<u32>(t_file.readInt());

							if (t_page >= INpcData::SHOP_PAGE_COUNT)
							{
								Log::write(LOG_WARNING, "Invalid page id '%u' in npc file \"%s\"",
									t_page, t_file.getFileName());

								t_page = 0;
							}

							t_file.readNext(ts_buf1, TS_BUF_SIZE);

							while (xstricmp("END", ts_buf1) != 0)
							{
								t_item = getItemManager()->getItemById(xtoi(ts_buf1));

								if (t_item)
								{
									t_npc->m_shopItems[t_page].push_back(IItemProperties(t_item, 1));
								}
								else
								{
									Log::write(LOG_WARNING, "Invalid item '%s' in npc file \"%s\"",
										ts_buf1, t_file.getFileName());
								}

								t_file.readNext(ts_buf1, TS_BUF_SIZE);
							}
						}

						//text
						else if (xstricmp("TEXT", ts_buf1) == 0)
						{
							TimeMs t_delay = t_file.readUInt();
							t_file.readString(ts_buf1, TS_BUF_SIZE);

							if (ts_buf1[0])
							{
								t_npc->m_texts.push_back(INpcData::Text(t_delay * 1000, ts_buf1));
							}
						}

						//unknown
						else if (ts_buf1[0])
						{
							Log::write(LOG_WARNING, "Unknown command '%s' in npc file \"%s\"",
								ts_buf1, t_file.getFileName());
						}
					}

					if (t_npc->m_mover)
					{
						m_npcs.push_back(t_npc);
					}
					else
					{
						delete t_npc;
					}
				}
				else
				{
					Log::write(LOG_ERROR, "Could not open npc file \"%s\"!", ts_buf1);
				}
			}
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the npc folder \"%s\"!", m_settings->NpcFolder.c_str());
		return false;
	}

	Log::write(LOG_SUCCESS, "Loaded %u npcs", m_npcs.size());

	return true;
}

bool IWorldDataManager::_loadExp()
{
	CFileReader t_file;
	t_file.setOption(CFileReader::opt_comments, true);

	if (t_file.open(m_settings->ExpFileName.c_str(), true))
	{
		EXP t_levelUp;
		EXP t_deathLost;
		while (!t_file.end())
		{
			t_levelUp = t_file.readInt64();
			t_deathLost = t_file.readInt64();
			m_levelExp.push_back(LevelExp(t_levelUp, t_deathLost));
		}
	}
	else
	{
		Log::write(LOG_ERROR, "Could not open the exp file \"%s\"!", m_settings->ExpFileName.c_str());
		return false;
	}

	if (m_levelExp.empty())
	{
		Log::write(LOG_ERROR, "No exp values loaded");
		return false;
	}

	Log::write(LOG_SUCCESS, "Loaded %u exp values", m_levelExp.size());

	return true;
}

bool IWorldDataManager::_loadJobInfos()
{
	if (loadJobStats(m_settings->JobFileName.c_str()))
	{
		Log::write(LOG_SUCCESS, "Loaded job infos");
		return true;
	}

	return false;
}
