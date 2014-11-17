#include "MobObject.h"
#include "WorldField.h"
#include "Spawn.h"
#include "World.h"
#include "MoverData.h"
#include "WorldServer.h"
#include "PlayerObject.h"
#include "DropObject.h"
#include "WorldPlayer.h"
#include "SpawnData.h"
#include "../shared/PacketCreator.h"
#include "../shared/Character.h"


TimeMs IMobObject::ms_removeDelay = 0;
TimeMs IMobObject::ms_moveDelay = 10000;
f32 IMobObject::ms_moveRange = 5.0f;
IMobObject::PenyaDrop IMobObject::ms_penyaDrops[4] =
{
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0}
};


IMobObject::IMobObject(ID _id, IWorld *_world, const IMoverData *_mover, bool _aggro, ISpawn *_spawn,
					   const CPoint &_spawnPos)
	: ICreature(_id, _world)
	, m_mover(_mover)
	, m_spawn(_spawn)
	, m_aggro(_aggro)
	, m_nextMoveTime(0)
	, m_attackTarget(0)
	, m_nextAttackTime(0)
	, m_nextAggressionTime(0)
	, m_spawnPos(_spawnPos)
{
	FDASSERT(m_mover);

	setStat(DST_HP, m_mover->getHp());

	calculateStats();
}

IMobObject::~IMobObject()
{
}

IMobObject::E_TYPE IMobObject::getType() const
{
	return TYPE_MOB;
}

const IMoverData *IMobObject::getMover() const
{
	return m_mover;
}

ISpawn *IMobObject::getSpawn()
{
	return m_spawn;
}

const CPoint &IMobObject::getSpawnPosition() const
{
	return m_spawnPos;
}

LVL IMobObject::getLevel() const
{
	return (m_mover ? m_mover->getLevel() : 0);
}

TimeMs IMobObject::getNextMoveTime() const
{
	return m_nextMoveTime;
}

bool IMobObject::isAggressive() const
{
	return m_aggro;
}

const PlayerObjectPtr &IMobObject::getAttackTarget() const
{
	return m_attackTarget;
}

TimeMs IMobObject::getNextAttackTime() const
{
	return m_nextAttackTime;
}

bool IMobObject::init()
{
	return true;
}

void IMobObject::update()
{
	_updatePosition();

	//removing after death
	if (m_removeTime &&
		_time() >= m_removeTime)
	{
		printf(".... 1246\n");
		m_world->removeObject(this, true); //deletes this object!
		return;
	}

	//attack
	else if (m_attackTarget)
	{
		if (_time() >= m_nextAttackTime)
		{
			attack(m_attackTarget, 30);

			if (m_attackResult.Kill)
			{
				m_attackTarget = 0;
				follow(0);
			}

			m_nextAttackTime = _time() + random(m_mover->getAttackDelay(), m_mover->getAttackDelay() + 500);
		}
	}

	//walking around
	else if ((!m_spawn || m_spawn->getData()->isMobMoving()) &&
		_time() >= m_nextMoveTime)
	{
		//mob has a spawn -> use its move time
		if (m_spawn)
		{
			walk(CPoint::randomPosition(m_pos, m_spawn->getData()->getMoveDistance()));

			m_nextMoveTime = _time() + m_spawn->getData()->getMoveInterval() +
				random(m_spawn->getData()->getMoveInterval());
		}

		//use ms_moveDelay
		else
		{
			walk(CPoint::randomPosition(m_pos, ms_moveRange));

			m_nextMoveTime = _time() + ms_moveDelay + random(ms_moveDelay);
		}
	}

	//do aggro things
	else if (m_aggro)
	{
		if (_time() >= m_nextAggressionTime)
		{
			//watch out for a victim
			if (m_attackTarget == 0)
			{
				m_attackTarget = m_world->getNearestObject(TYPE_PLAYER, this, 5.0f);

				follow(m_attackTarget);
			}
			//
			else if (!m_pos.isInRange(m_attackTarget->getPosition(), 50.0f))
			{
				m_attackTarget = 0;

				follow(0);

				walk(m_spawnPos);
			}

			m_nextAggressionTime = _time() + 500;
		}
	}
}

void IMobObject::calculateStats()
{
	_clearStats();
}

const IMobObject::AttackResult &IMobObject::attack(const CreaturePtr &_target, s32 _attackMotion)
{
	FDASSERT(_target);

	m_attackResult.Damage = 0;
	m_attackResult.Flags = 0;

	if (_target->isDead())
	{
		return m_attackResult;
	}

	m_attackResult.Damage = random(m_mover->getAttackMin(), m_mover->getAttackMax());
	m_attackResult.Flags |= (sdk::random() % 4 == 0 ? ICreature::ATT_CRIT : 0);

	_target->damage(m_attackResult, this); //if hit

	sendToLocalArea(IPacketCreator::attack(this, _target, _attackMotion));

	_target->damage(m_attackResult, this);

	return m_attackResult;
}

void IMobObject::damage(AttackResult &_result, const CreaturePtr &_attacker)
{
	FDASSERT(_attacker);

	sendToLocalArea(IPacketCreator::damage(_attacker, this, _result.Damage, _result.Flags));

	m_stats[DST_HP] -= _result.Damage;

	if (isDead())
	{
		_result.Kill = true;

		kill(DEATH_PLAYER, _attacker);
	}
	else
	{
		if (_attacker->isPlayer())
		{
			if (m_attackTarget == 0)
			{
				m_attackTarget = boost::dynamic_pointer_cast<IPlayerObject>(_attacker);

				follow(m_attackTarget);
			}
		}
	}
}

void IMobObject::kill(E_DEATH _type, CreaturePtr _killer)
{
	m_stats[DST_HP] = 0;

	sendToLocalArea(IPacketCreator::objectDeath(this));

	m_removeTime = _time() + ms_removeDelay;

	if (m_spawn)
	{
		m_spawn->removeMob(this);
	}

	switch (_type)
	{
	case DEATH_PLAYER:
		{
			FDASSERT(_killer);
			FDASSERT(_killer->getType() == IWorldObject::TYPE_PLAYER);

			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(_killer);

			t_player->addMobExp(m_mover->getExp());

			_dropItems(t_player);

			break;
		}

	case DEATH_SPC:
		{
			break;
		}

	default:
		{
			FDASSERT(false && "Invalid param E_DEATH _type");
		}
	}

	_onDeath();
}

void IMobObject::onWorldRemove()
{
	ICreature::onWorldRemove();

	m_attackTarget.reset();
}

void IMobObject::onDestroy()
{
	ICreature::onDestroy();
}

TimeMs IMobObject::getRemoveDelay()
{
	return ms_removeDelay;
}

TimeMs IMobObject::getMoveDelay()
{
	return ms_moveDelay;
}

f32 IMobObject::getMoveRange()
{
	return ms_moveRange;
}

void IMobObject::setRemoveDelay(TimeMs _time)
{
	ms_removeDelay = _time;
}

void IMobObject::setMoveDelay(TimeMs _time)
{
	ms_moveDelay = _time;
}

void IMobObject::setMoveRange(f32 _range)
{
	ms_moveRange = _range;
}

void IMobObject::setPenyaDropItems(const PenyaDrop *_dropArray)
{
	FDASSERT(_dropArray);

	for (u32 i = 0; i < PENYA_DROP_ITEM_COUNT; ++i)
	{
		ms_penyaDrops[i] = _dropArray[i];
	}
}

void IMobObject::_dropItems(const PlayerObjectPtr &_owner)
{
	FDASSERT(m_mover);
	FDASSERT(m_world);

	PENYA t_penyas = random(
		static_cast<PENYA>(m_mover->getPenyaMin() * _owner->getPenyaRate()),
		static_cast<PENYA>(m_mover->getPenyaMax() * _owner->getPenyaRate()));

	if (t_penyas)
	{
		m_dropItem.clear();

		m_dropItem.setData(_getPenyaDropItem(t_penyas));
		m_dropItem.setCount(t_penyas);

		//create it on the same height as the player
		m_pos.Y = _owner->getPosition().Y;

		m_world->createDropObject(m_dropItem, CPoint::randomPosition(m_pos, WORLD_ITEM_DROP_RANGE), _owner);
	}

	RATE t_playerDropRate = _owner->getDropRate();

	for (u32 i = 0; i < m_mover->getDropCount(); ++i)
	{
		if (eventd(m_mover->getDrop(i)->Chance * t_playerDropRate))
		{
			m_dropItem.clear();

			//special item?
			if (m_mover->getDrop(i)->isSpc())
			{
				const IMoverData::DropSpc *t_dropSpc =
					dynamic_cast<const IMoverData::DropSpc*>(m_mover->getDrop(i));

				m_dropItem.setData(t_dropSpc->getData());
				m_dropItem.setCount(t_dropSpc->getCount());
				m_dropItem.setUpgrade(t_dropSpc->getUpgrade());
				m_dropItem.setElement(t_dropSpc->getElement());
				m_dropItem.setElementalUpgrade(t_dropSpc->getElementalUpgrade());
				m_dropItem.setSlots(t_dropSpc->getSlots());

				//Awak
				//Stat
			}

			//normal
			else
			{
				const IMoverData::Drop *t_drop =
					dynamic_cast<const IMoverData::Drop*>(m_mover->getDrop(i));

				m_dropItem.setData(t_drop->Item);
				m_dropItem.setCount(1);

				//only add random stat or upgrade if wanted
				if (!t_drop->Clean)
				{
					//Upgrade, Stat ...
				}
			}

			m_world->createDropObject(m_dropItem, CPoint::randomPosition(m_pos, WORLD_ITEM_DROP_RANGE), _owner);
		}
	}
}

void IMobObject::_onDeath()
{
}

const IItemData *IMobObject::_getPenyaDropItem(PENYA _amount)
{
	FDASSERT(ARRAY_SIZE(ms_penyaDrops));

	for (u32 i = 0; i < ARRAY_SIZE(ms_penyaDrops); ++i)
	{
		FDASSERT(ms_penyaDrops[i].Item);

		if (_amount <= ms_penyaDrops[i].Amount)
		{
			return ms_penyaDrops[i].Item;
		}
	}

	return ms_penyaDrops[ARRAY_SIZE(ms_penyaDrops) - 1].Item;
}


/// Special case: Clockwork ///
///////////////////////////////


IClockWorkObject::IClockWorkObject(ID _id, IWorld *_world, const IMoverData *_mover, bool _aggro)
	: IMobObject(_id, _world, _mover, _aggro)
	, m_guild(0)
{
}

IClockWorkObject::~IClockWorkObject()
{
}

IGuild *IClockWorkObject::getGuild()
{
	return m_guild;
}

void IClockWorkObject::enterRoom(IGuild *_guild)
{
	FDASSERT(_guild);

	m_guild = _guild;

	//...
}

void IClockWorkObject::leaveRoom()
{
	FDASSERT(m_guild);

	//...
}

void IClockWorkObject::update()
{
	//end of time?
	if (_time() >= m_endTime)
	{
		leaveRoom();
	}
}

void IClockWorkObject::_onDeath()
{
}


/// Special case: Meteonyker ///
////////////////////////////////
