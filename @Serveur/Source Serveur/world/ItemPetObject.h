#ifndef ITEMPETOBJECT_H
#define ITEMPETOBJECT_H


#include "WorldMain.h"
#include "PetObject.h"


class IItemPetObject : public IPetObject
{
public:

	IItemPetObject(ID _id, IWorld *_world, const IMoverData *_data, PlayerObjectPtr &_owner);

	E_TYPE getType() const;

	bool init();

	void update();

private:
};


#endif //ITEMPETOBJECT_H
