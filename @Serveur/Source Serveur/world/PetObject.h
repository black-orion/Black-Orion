#ifndef PETOBJECT_H
#define PETOBJECT_H


#include "WorldMain.h"
#include "MovingObject.h"


class IMoverData;
class IPlayerObject;


class IPetObject : public IMovingObject
{
public:

	IPetObject(ID _id, IWorld *_world, const IMoverData *_data, PlayerObjectPtr &_owner);

	~IPetObject();

	const IMoverData *getMoverData() const;

	const PlayerObjectPtr &getOwner() const;

	bool init();

	void onWorldRemove();

	void update();

protected:

	void _followOwner();

private:

	const IMoverData *m_moverData;

	PlayerObjectPtr m_owner;
};


#endif //PETOBJECT_H
