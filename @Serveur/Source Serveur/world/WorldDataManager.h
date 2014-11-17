#ifndef WORLDDATAMANAGER_H
#define WORLDDATAMANAGER_H


#include "WorldMain.h"
#include "WorldSettings.h"
#include "../shared/ItemDataManager.h"


class IMoverData;
class ISpawnData;
class IItemData;
class INpcData;


class IWorldDataManager
{
public:

	IWorldDataManager(IWorldDataSettings *_settings);

	~IWorldDataManager();

	bool load();

	IItemDataManager *getItemManager();

	u32 getMoverCount() const;

	const IMoverData *getMoverByNumber(u32 _num) const;

	const IMoverData *getMoverById(const char *_idName) const;

	const IMoverData *getMoverById(ID _id) const;

	u32 getSpawnCount() const;

	const ISpawnData *getSpawnByNumber(u32 _num) const;

	const ISpawnData *getSpawnById(const char *_fileName) const;

	u32 getNpcCount() const;

	const INpcData *getNpcByNumber(u32 _num) const;

	u32 getLevelCount() const;

	//_level = current char lvl
	EXP getLevelExp(u32 _level) const;

	EXP getExpLost(u32 _level) const;

	const ISpawnData *createSpawn(const IMoverData *_mover, u32 _count, const CPoint &_pos, ID _world,
		f32 _range,	s16 _size, RATE _aggroRate, TimeMs _respawnTime, bool _moving, TimeMs _movingInterval,
		RATE _expRate, RATE _penyaRate, RATE _dropRate);

private:

	IWorldDataSettings *m_settings;

	IItemDataManager m_itemMngr;

	CArray<IMoverData*> m_movers;

	CArray<ISpawnData*> m_spawns;

	CArray<INpcData*> m_npcs;

	struct LevelExp
	{
		EXP LevelUp;
		EXP DeathLost;

		LevelExp(EXP _levelUp = 0, EXP _deathLost = 0)
			: LevelUp(_levelUp)
			, DeathLost(_deathLost)
		{
		}
	};

	CArray<LevelExp> m_levelExp;

	IMoverData *_getMover(const char *_idName);

	IMoverData *_getMover(ID _id);

	bool _loadMovers();

	bool _loadDrops();

	bool _loadSpawns();

	bool _loadNpcs();

	bool _loadExp();

	bool _loadJobInfos();

};


#endif //WORLDDATAMANAGER_H
