#include "Spawn.h"
#include "MobObject.h"
#include "SpawnData.h"
#include "World.h"
#include "WorldField.h" //.


ISpawn::ISpawn(const ISpawnData *_data, IWorld *_world)
	: ITimed()
	, m_data(_data)
	, m_world(_world)
	, m_active(true)
	, m_nextRespawn(0)
{
	FDASSERT(m_data);
	FDASSERT(m_world);
}

const ISpawnData *ISpawn::getData() const
{
	return m_data;
}

IWorld *ISpawn::getWorld()
{
	return m_world;
}

u32 ISpawn::getMobCount() const
{
	return m_mobs.size();
}

const MobObjectPtr &ISpawn::getMob(u32 _num)
{
	FDASSERT(_num < m_mobs.size());

	return m_mobs[_num];
}

bool ISpawn::isActive() const
{
	return m_active;
}

TimeMs ISpawn::getNextRespawnTime() const
{
	return m_nextRespawn;
}

void ISpawn::setActive(bool _active)
{
	m_active = _active;
}

void ISpawn::update()
{
	if (m_mobs.size() < m_data->getMobMaximum())
	{
		if (m_nextRespawn == 0)
		{
			m_nextRespawn = _time() + m_data->getRespawnTime();
		}

		else
		{
			while (m_mobs.size() < m_data->getMobMaximum())
			{
				//time to respawn
				if (_time() > m_nextRespawn)
				{
					//create a random mover at a random position
					m_mobs.push_back(
						m_world->createMobObject(
						m_data->getRandomMover(),
						m_data->getRandomPosition(),
						eventd(m_data->getAggroChance()),
						this));

					m_nextRespawn += m_data->getRespawnTime();
				}
				else
				{
					return;
				}
			}

			m_nextRespawn = 0;
		}
	}
}

void ISpawn::killAllSpawnedMobs()
{
	FOR_EACH (m_mobs, i)
	{
		m_mobs[i]->kill(ICreature::DEATH_SPC);
	}

	m_mobs.clear();
}

void ISpawn::removeMob(const MobObjectPtr &_mob)
{
	FDASSERT(_mob);

	u32 t_index = 0;
	if (m_mobs.find(t_index, _mob))
	{
		m_mobs[t_index].reset();
		m_mobs.erase_fast(t_index);
	}
}