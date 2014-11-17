#include "PetObject.h"
#include "PlayerObject.h"


IPetObject::IPetObject(ID _id, IWorld *_world, const IMoverData *_data, PlayerObjectPtr &_owner)
	: IMovingObject(_id, _world)
	, m_moverData(_data)
	, m_owner(_owner)
{
	FDASSERT(m_moverData != 0);
	FDASSERT(m_owner != 0);
}

IPetObject::~IPetObject()
{
}

const IMoverData *IPetObject::getMoverData() const
{
	return m_moverData;
}

const PlayerObjectPtr &IPetObject::getOwner() const
{
	return m_owner;
}

bool IPetObject::init()
{
	return true;
}

void IPetObject::onWorldRemove()
{
	m_owner.reset();
}

void IPetObject::update()
{
	_followOwner();
}

void IPetObject::_followOwner()
{
	if (!isMoving() &&
		!getPosition().isInRangeSq(getOwner()->getPosition(), 5 * 5))
	{
		printf("following\n");
		walk(getOwner()->getPosition());
	}
}