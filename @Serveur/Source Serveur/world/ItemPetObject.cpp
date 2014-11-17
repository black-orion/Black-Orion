#include "ItemPetObject.h"
#include "PlayerObject.h"


IItemPetObject::IItemPetObject(ID _id, IWorld *_world, const IMoverData *_data, PlayerObjectPtr &_owner)
	: IPetObject(_id, _world, _data, _owner)
{
}

IWorldObject::E_TYPE IItemPetObject::getType() const
{
	return TYPE_ITEM_PET;
}

bool IItemPetObject::init()
{
	return true;
}

void IItemPetObject::update()
{
	_followOwner();
}