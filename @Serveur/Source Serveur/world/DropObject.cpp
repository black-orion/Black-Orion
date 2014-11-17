#include "DropObject.h"
#include "PlayerObject.h"
#include "World.h"


TimeMs IDropObject::ms_removeDelay = 0;

IDropObject::IDropObject(ID _id, IWorld *_world)
	: IWorldObject(_id, _world)
	, m_owner(0)
	, m_ownershipEnd(0)
{
	m_removeTime = _time() + ms_removeDelay;
}

IDropObject::~IDropObject()
{
}

IDropObject::E_TYPE IDropObject::getType() const
{
	return TYPE_DROP;
}

IItemProperties &IDropObject::getItem()
{
	return m_item;
}

const IItemProperties &IDropObject::getItem() const
{
	return m_item;
}

const PlayerObjectPtr &IDropObject::getOwner() const
{
	return m_owner;
}

TimeMs IDropObject::getOwnershipEnd() const
{
	return m_ownershipEnd;
}

void IDropObject::setItem(const IItemProperties &_item)
{
	m_item = _item;
}

void IDropObject::setOwner(const PlayerObjectPtr &_owner)
{
	m_owner = _owner;
}

void IDropObject::setOwnershipEnd(TimeMs _time)
{
	m_ownershipEnd = _time;
}

bool IDropObject::init()
{
	return true;
}

void IDropObject::onWorldRemove()
{
	IWorldObject::onWorldRemove();

	m_owner.reset();
}

void IDropObject::onDestroy()
{
	IWorldObject::onDestroy();
}

void IDropObject::update()
{
	//removing
	if (m_removeTime &&
		_time() >= m_removeTime)
	{
		m_world->removeObject(this, true); //deletes this object!
		return;
	}

	//end of ownership
	if (m_owner &&
		_time() >= m_ownershipEnd)
	{
		m_owner = 0;
	}
}

TimeMs IDropObject::getRemoveDelay()
{
	return ms_removeDelay;
}

void IDropObject::setRemoveDelay(TimeMs _time)
{
	ms_removeDelay = _time;
}