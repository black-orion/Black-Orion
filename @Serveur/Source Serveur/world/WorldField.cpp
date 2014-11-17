#include "WorldField.h"
#include "WorldObject.h"
#include "PlayerObject.h"
#include "WorldPlayer.h"
#include "../shared/PacketCreator.h"


IWorldField::IWorldField()
	: m_playersIn(0)
{
}

void IWorldField::addObject(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	m_objects.push_back(_object);
	_object->setField(this);

	if (_object->getType() == IWorldObject::TYPE_PLAYER)
	{
		++m_playersIn;
	}
}

void IWorldField::removeObject(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	if (_object->isPlayer())
	{
		--m_playersIn;
	}

	u32 t_index = 0;
	if (m_objects.find(t_index, _object))
	{
		m_objects[t_index].reset();
		m_objects.erase_fast(t_index);
	}
}

const CVec2D<u32> &IWorldField::getPosition() const
{
	return m_pos;
}

u32 IWorldField::getObjectCount() const
{
	return m_objects.size();
}

WorldObjectPtr &IWorldField::getObject(u32 _num)
{
	FDASSERT(_num < m_objects.size());

	return m_objects[_num];
}

void IWorldField::setPosition(const CVec2D<u32> &_pos)
{
	m_pos = _pos;
}

bool IWorldField::sendToAllPlayers(const CByteArray &_packet)
{
	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->getType() == IWorldObject::TYPE_PLAYER)
		{
			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(m_objects[i]);
			FDASSERT(t_player->getPlayer());
			FDASSERT(t_player->getPlayer()->getClient());

			if (!t_player->getPlayer()->getClient()->send(_packet))
				return false;
		}
	}

	return true;
}

bool IWorldField::sendToAllPlayersBut(const CByteArray &_packet, const PlayerObjectPtr &_playerObject)
{
	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->getType() == IWorldObject::TYPE_PLAYER &&
			m_objects[i] != _playerObject)
		{
			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(m_objects[i]);

			FDASSERT(t_player->getPlayer());
			FDASSERT(t_player->getPlayer()->getClient());

			if (!t_player->getPlayer()->getClient()->send(_packet))
				return false;
		}
	}

	return true;
}

bool IWorldField::intersectsWith(const IWorldField *_field) const
{
	FDASSERT(_field);

	const CVec2D<u32> &t_pos = _field->getPosition();

	CVec2D<u32> t_diff(
		t_pos.X > m_pos.X ? t_pos.X - m_pos.X : m_pos.X - t_pos.X,
		t_pos.Y > m_pos.Y ? t_pos.Y - m_pos.Y : m_pos.Y - t_pos.Y);

	return (t_diff.X < (1 + 2 * WORLD_FIELD_SIGHT) &&
		t_diff.Y < (1 + 2 * WORLD_FIELD_SIGHT));
}

bool IWorldField::isFieldInArea(const IWorldField *_field) const
{
	FDASSERT(_field);

	return (
		_field->m_pos.X + WORLD_FIELD_SIGHT >= m_pos.X &&
		_field->m_pos.Y + WORLD_FIELD_SIGHT >= m_pos.Y &&

		_field->m_pos.X <= m_pos.X + WORLD_FIELD_SIGHT &&
		_field->m_pos.Y <= m_pos.Y + WORLD_FIELD_SIGHT
		);
}

bool IWorldField::despawnAll(const PlayerObjectPtr &_player) const
{
	FDASSERT(_player);

	for (u32 i = 0; i < m_objects.size(); ++i)
	{
		if (m_objects[i] != _player)
		{
			if (!_player->getPlayer()->getClient()->send(IPacketCreator::despawn(m_objects[i])))
			{
				return false;
			}
		}
	}

	return true;
}

bool IWorldField::spawnAll(const PlayerObjectPtr &_player) const
{
	FDASSERT(_player);

	for (u32 i = 0; i < m_objects.size(); ++i)
	{
		if (m_objects[i] != _player)
		{
			if (!_player->getPlayer()->getClient()->send(IPacketCreator::spawn(m_objects[i])))
			{
				return false;
			}
		}
	}

	return true;
}

bool IWorldField::isPlayerIn() const
{
	/*for (u32 i = 0; i < m_objects.size(); ++i)
	{
		if (m_objects[i]->getType() == IWorldObject::TYPE_PLAYER)
		{
			return true;
		}
	}

	return false;*/

	return m_playersIn != 0;
}