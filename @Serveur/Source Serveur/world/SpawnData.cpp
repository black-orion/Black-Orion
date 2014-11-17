#include "SpawnData.h"
#include "MoverData.h"


ISpawnData::ISpawnData()
	: m_fileName("")
	, m_maximum(0)
	, m_aggro(0.0f)
	, m_moving(true)
	, m_moveDistance(5.0f)
	, m_exp(1.0f)
	, m_drop(1.0f)
	, m_penya(1.0f)
	, m_range(0.0f)
	, m_size(100)
	, m_world(1)
	, m_respawnTime(1000)
	, m_moveInterval(5000)
{
}

const char *ISpawnData::getFileName() const
{
	return m_fileName.c_str();
}

u32 ISpawnData::getMoverCount() const
{
	return m_mobs.size();
}

const IMoverData *ISpawnData::getMover(u32 _num) const
{
	FDASSERT(_num < m_mobs.size());

	return m_mobs[_num];
}

const IMoverData *ISpawnData::getRandomMover() const
{
	FDASSERT(!m_mobs.empty());

	return m_mobs[random(m_mobs.size() - 1)];
}

u32 ISpawnData::getMobMaximum() const
{
	return m_maximum;
}

RATE ISpawnData::getAggroChance() const
{
	return m_aggro;
}

bool ISpawnData::isMobMoving() const
{
	return m_moving;
}

f32 ISpawnData::getMoveDistance() const
{
	return m_moveDistance;
}

RATE ISpawnData::getExpRate() const
{
	return m_exp;
}

RATE ISpawnData::getDropRate() const
{
	return m_drop;
}

RATE ISpawnData::getPenyaRate() const
{
	return m_penya;
}

const CPoint &ISpawnData::getPosition() const
{
	return m_pos;
}

CPoint ISpawnData::getRandomPosition() const
{
	return CPoint::randomPosition(m_pos, m_range);
}

f32 ISpawnData::getRange() const
{
	return m_range;
}

ID ISpawnData::getWorldId() const
{
	return m_world;
}

s16 ISpawnData::getMoverSize() const
{
	return m_size;
}

TimeMs ISpawnData::getRespawnTime() const
{
	return m_respawnTime;
}

TimeMs ISpawnData::getMoveInterval() const
{
	return m_moveInterval;
}

bool ISpawnData::saveFile(const char *_fileName) const
{
	FDASSERT(_fileName);

	FILE *t_file;
	fopen_s(&t_file, _fileName, "w");

	if (t_file)
	{
		for (u32 i = 0; i < m_mobs.size(); ++i)
		{
			fprintf_s(t_file, "MOB %d //%s\n", m_mobs[i]->getId(), m_mobs[i]->getIdName());
		}

		fprintf_s(t_file, "COUNT %u\n", m_maximum);
		fprintf_s(t_file, "POS %.1f %.1f %.1f\n", m_pos.X, m_pos.Y, m_pos.Z);
		fprintf_s(t_file, "WORLD %d\n", m_world);
		fprintf_s(t_file, "SIZE %d\n", (s32)m_size);
		fprintf_s(t_file, "RANGE %.1f\n", m_range);
		fprintf_s(t_file, "MOVING %d\n", (s32)m_moving);
		fprintf_s(t_file, "MOVINGINTERVAL %u\n", m_moveInterval);
		fprintf_s(t_file, "AGGRO %.4lf\n", m_aggro);
		fprintf_s(t_file, "RESPAWNTIME %u\n", m_respawnTime);
		fprintf_s(t_file, "EXP %.6lf\n", m_exp);
		fprintf_s(t_file, "PENYA %.6lf\n", m_penya);
		fprintf_s(t_file, "DROP %.6lf\n", m_drop);

		fclose(t_file);
		return true;
	}

	return false;
}
