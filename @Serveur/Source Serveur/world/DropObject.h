#ifndef DROPOBJECT_H
#define DROPOBJECT_H


#include "WorldMain.h"
#include "WorldObject.h"
#include "../shared/ItemPack.h"


class IPlayerObject;


class IDropObject : public IWorldObject
{
public:

	IDropObject(ID _id, IWorld *_world);

	~IDropObject();

	E_TYPE getType() const;

	IItemProperties &getItem();

	const IItemProperties &getItem() const;

	const PlayerObjectPtr &getOwner() const;

	TimeMs getOwnershipEnd() const;

	void setItem(const IItemProperties &_item);

	void setOwner(const PlayerObjectPtr &_owner);

	void setOwnershipEnd(TimeMs _time);

	bool init();

	void onWorldRemove();

	void onDestroy();

	void update();

	static TimeMs getRemoveDelay();

	static void setRemoveDelay(TimeMs _time);

private:

	IItemProperties m_item;

	PlayerObjectPtr m_owner;

	TimeMs m_ownershipEnd;

	static TimeMs ms_removeDelay;

};


#endif //DROPOBJECT_H
