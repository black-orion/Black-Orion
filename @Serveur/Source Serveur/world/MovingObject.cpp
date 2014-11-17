#include "MovingObject.h"
#include "World.h"
#include "PlayerObject.h"
#include "../shared/PacketCreator.h"


IMovingObject::IMovingObject(ID _id, IWorld *_world)
	: IWorldObject(_id, _world)
	, m_nextPosUpdate(0)
	, m_target(0)
	, m_followed(0)
{
}

IMovingObject::~IMovingObject()
{
}

const CPoint &IMovingObject::getTargetPos() const
{
	return m_targetPos;
}

WorldObjectPtr &IMovingObject::getTarget()
{
	return m_target;
}

WorldObjectPtr &IMovingObject::getFollowed()
{
	return m_followed;
}

s32 IMovingObject::getSpeed() const
{
	return 100;
}

void IMovingObject::setTargetPos(const CPoint &_pos)
{
	m_targetPos = _pos;
}

void IMovingObject::setTarget(const WorldObjectPtr &_target)
{
	m_target = _target;
}

void IMovingObject::walk(const CPoint &_pos)
{
	FDASSERT(m_world);

	m_followed = 0;

	m_targetPos = _pos;
	m_nextPosUpdate = _time() + CREATURE_POS_UPDATE_INTERVAL;

	if (isPlayer())
	{
		sendToLocalArea(IPacketCreator::objectWalking(this), dynamic_cast<IPlayerObject*>(this));
	}
	else
	{
		if (m_world->isPlayerInLocalArea(this))
		{
			sendToLocalArea(IPacketCreator::objectWalking(this));
		}
	}
}

void IMovingObject::follow(const WorldObjectPtr &_obj)
{
	m_followed = _obj;

	if (m_followed)
	{
		m_targetPos.X = m_followed->getPosition().X;
		m_targetPos.Y = m_pos.Y;
		m_targetPos.Z = m_followed->getPosition().Z;

		m_nextPosUpdate = _time() + CREATURE_POS_UPDATE_INTERVAL;

		if (isPlayer())
		{
			m_world->sendToLocalArea(this, IPacketCreator::follow(this), dynamic_cast<IPlayerObject*>(this));
		}
		else
		{
			m_world->sendToLocalArea(this, IPacketCreator::follow(this));
		}
	}
}

bool IMovingObject::isMoving() const
{
	return (m_nextPosUpdate != 0);
}

void IMovingObject::onWorldRemove()
{
	IWorldObject::onWorldRemove();

	m_followed.reset();
	m_target.reset();
}

void IMovingObject::onDestroy()
{
	IWorldObject::onDestroy();
}

void IMovingObject::_updatePosition()
{
	//position update
	if (m_nextPosUpdate &&
		_time() >= m_nextPosUpdate)
	{
		if (m_followed &&
			m_followed->isCreature())
		{
			m_targetPos.X = m_followed->getPosition().X;
			m_targetPos.Y = m_pos.Y;
			m_targetPos.Z = m_followed->getPosition().Z;
		}

		//move
		CPoint t_speed = (m_targetPos - m_pos);
		f32 t_length = t_speed.length();

		//stop if the distance is 0
		if (equalf(t_length, 0.0f))
		{
			m_nextPosUpdate = 0;

			m_pos = m_targetPos;
		}
		else
		{
			t_speed /= t_length;

			u32 t_negativity = 
				u32(m_pos.X < m_targetPos.X) |
				u32(m_pos.Y < m_targetPos.Y) << 1 |
				u32(m_pos.Z < m_targetPos.Z) << 2;

			static const f32 SPEED_FACTOR = 1.0f / 10000.0f;

			m_pos +=
				t_speed * f32(_time() - m_nextPosUpdate + CREATURE_POS_UPDATE_INTERVAL) *
				SPEED_FACTOR * f32(getSpeed());

			m_nextPosUpdate = _time() + CREATURE_POS_UPDATE_INTERVAL;

			if (t_negativity != (
				u32(m_pos.X < m_targetPos.X) |
				u32(m_pos.Y < m_targetPos.Y) << 1 |
				u32(m_pos.Z < m_targetPos.Z) << 2))
			{
#ifdef SDEBUG
				if (isPlayer())
					printf("target reached (obj %d)\n", m_id);
#endif

				m_nextPosUpdate = 0;

				m_pos = m_targetPos;
			}
		}

		onChangePosition();
	}
}
