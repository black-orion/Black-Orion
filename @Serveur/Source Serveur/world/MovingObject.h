#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H


#include "WorldMain.h"
#include "WorldObject.h"


class IMovingObject : public IWorldObject
{
public:

	IMovingObject(ID _id, IWorld *_world);

	~IMovingObject();

	const CPoint &getTargetPos() const;

	WorldObjectPtr &getTarget();

	WorldObjectPtr &getFollowed();

	virtual s32 getSpeed() const;

	void setTargetPos(const CPoint &_pos);

	void setTarget(const WorldObjectPtr &_target);

	void walk(const CPoint &_pos);

	void follow(const WorldObjectPtr &_obj);

	bool isMoving() const;

	void onWorldRemove();

	void onDestroy();

protected:

	CPoint m_targetPos;

	TimeMs m_nextPosUpdate;

	WorldObjectPtr m_target;

	WorldObjectPtr m_followed;

	void _updatePosition();

};


#endif //CREATURE_H
