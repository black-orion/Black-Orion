#ifndef SPAWNDATA_H
#define SPAWNDATA_H


#include "WorldMain.h"
#include "WorldDataManager.h"


class IMoverData;


class ISpawnData
{
public:

	ISpawnData();

	const char *getFileName() const;

	u32 getMoverCount() const;

	const IMoverData *getMover(u32 _num = 0) const;

	const IMoverData *getRandomMover() const;

	u32 getMobMaximum() const;

	RATE getAggroChance() const;

	bool isMobMoving() const;

	f32 getMoveDistance() const;

	RATE getExpRate() const;

	RATE getDropRate() const;

	RATE getPenyaRate() const;

	const CPoint &getPosition() const;

	CPoint getRandomPosition() const;

	f32 getRange() const;

	ID getWorldId() const;

	s16 getMoverSize() const;

	TimeMs getRespawnTime() const;

	TimeMs getMoveInterval() const;

	bool saveFile(const char *_fileName) const;

private:

	friend class IWorldDataManager;

	sdk::stringc m_fileName;

	CArray<const IMoverData*> m_mobs;

	u32 m_maximum;

	RATE m_aggro;

	bool m_moving;

	f32 m_moveDistance;

	RATE m_exp;

	RATE m_drop;

	RATE m_penya;

	CPoint m_pos;

	f32 m_range;

	s16 m_size;

	ID m_world;

	TimeMs m_respawnTime;

	TimeMs m_moveInterval;

};


#endif //SPAWNDATA_H