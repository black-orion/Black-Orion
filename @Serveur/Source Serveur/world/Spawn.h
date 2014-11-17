#ifndef SPAWN_H
#define SPAWN_H


#include "WorldMain.h"
#include "../shared/Timed.h"


class ISpawnData;
class IMobObject;
class IWorld;


class ISpawn : public ITimed
{
public:

	ISpawn(const ISpawnData *_data, IWorld *_world);

	const ISpawnData *getData() const;

	IWorld *getWorld();

	u32 getMobCount() const;

	const MobObjectPtr &getMob(u32 _num);

	bool isActive() const;

	TimeMs getNextRespawnTime() const;

	void setActive(bool _active);

	void update();

	void killAllSpawnedMobs();

	void removeMob(const MobObjectPtr &_mob);

private:

	const ISpawnData *m_data;

	IWorld *m_world;

	CArray<MobObjectPtr> m_mobs;

	bool m_active;

	TimeMs m_nextRespawn;

};


#endif //SPAWN_H