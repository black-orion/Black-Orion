#include "WorldObject.h"
#include "WorldField.h"
#include "World.h"
#include "../shared/PacketCreator.h"


IWorldGameSettings *IWorldObject::ms_gameSettings = 0;

IWorldObject::IWorldObject(ID _id, IWorld *_world)
	: ITimed()
	, m_id(_id)
	, m_field(0)
	, m_world(_world)
	, m_rotation(0)
	, m_size(100)
	, m_removeTime(0)
{
	FDASSERT(m_world);
}

IWorldObject::~IWorldObject()
{
}

ID IWorldObject::getId() const
{
	return m_id;
}

IWorldObject::E_TYPE IWorldObject::getType() const
{
	return TYPE_OBJECT;
}

bool IWorldObject::isPlayer() const
{
	return (getType() == TYPE_PLAYER);
}

bool IWorldObject::isNpc() const
{
	return (getType() == TYPE_NPC);
}

bool IWorldObject::isDrop() const
{
	return (getType() == TYPE_DROP);
}

bool IWorldObject::isMob() const
{
	return (getType() == TYPE_MOB);
}

bool IWorldObject::isCreature() const
{
	return (
		getType() == TYPE_PLAYER ||
		getType() == TYPE_MOB);
}

bool IWorldObject::isPet() const
{
	return (
		getType() == TYPE_ITEM_PET ||
		getType() == TYPE_STAT_PET);
}

IWorld *IWorldObject::getWorld()
{
	return m_world;
}

IWorldField *IWorldObject::getField()
{
	return m_field;
}

const CPoint &IWorldObject::getPosition() const
{
	return m_pos;
}

s16 IWorldObject::getRotation() const
{
	return m_rotation;
}

s16 IWorldObject::getSize() const
{
	return m_size;
}

TimeMs IWorldObject::getRemoveTime() const
{
	return m_removeTime;
}

void IWorldObject::setWorld(IWorld *_world)
{
	m_world = _world;
}

void IWorldObject::setField(IWorldField *_field)
{
	m_field = _field;
}

void IWorldObject::setPosition(const CPoint &_pos)
{
	m_pos = _pos;

	onChangePosition();
}

void IWorldObject::setPositionPlain(const CPoint &_pos)
{
	m_pos = _pos;
}

void IWorldObject::setRotation(s16 _rotation)
{
	m_rotation = _rotation;
}

void IWorldObject::setSize(s16 _size)
{
	m_size = _size;
}

void IWorldObject::setRemoveTime(TimeMs _time)
{
	m_removeTime = _time;
}

bool IWorldObject::init()
{
	return true;
}

void IWorldObject::update()
{
}

bool IWorldObject::sendToLocalArea(const CByteArray &_packet)
{
	FDASSERT(m_world);

	return m_world->sendToLocalArea(this, _packet);
}

bool IWorldObject::sendToLocalArea(const CByteArray &_packet, const PlayerObjectPtr &_noSend)
{
	FDASSERT(m_world);

	return m_world->sendToLocalArea(this, _packet, _noSend);
}

void IWorldObject::onChangePosition()
{
	FDASSERT(m_world);

	m_world->updateField(this);
}

void IWorldObject::onWorldRemove()
{
	FDASSERT(m_world);

	printf("IWorldObject::onWorldRemove() %s\n", getTypeName(getType()));

	m_world->noTarget(this);

	if (m_field)
	{
		m_field->removeObject(this);
	}

	m_world->noTarget(this);
}

void IWorldObject::onDestroy()
{
	FDASSERT(m_world);

	printf("IWorldObject::onDestroy() %s\n", getTypeName(getType()));

	ITimed::_removeTimedObject(this);
}

const char *IWorldObject::getTypeName(E_TYPE _type)
{
	switch (_type)
	{
	case TYPE_OBJECT:
		return "OBJECT";
	case TYPE_PLAYER:
		return "PLAYER";
	case TYPE_NPC:
		return "NPC";
	case TYPE_DROP:
		return "DROP";
	case TYPE_MOB:
		return "MOB";
	case TYPE_ITEM_PET:
		return "ITEM_PET";
	case TYPE_STAT_PET:
		return "STAT_PET";
	default:
		FDASSERT(false);
		return "";
	}
}

IWorldGameSettings *IWorldObject::getGameSettings()
{
	return ms_gameSettings;
}

void IWorldObject::setGameSettings(IWorldGameSettings *_settings)
{
	ms_gameSettings = _settings;
}
