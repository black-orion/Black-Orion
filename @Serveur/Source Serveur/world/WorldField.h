#ifndef WORLDFIELD_H
#define WORLDFIELD_H


#include "WorldMain.h"


class IWorldObject;
class IPlayerObject;


class IWorldField
{
public:

	IWorldField();

	//sets the _object's m_field to 'this'
	void addObject(const WorldObjectPtr &_object);

	//does not reset the _object's field
	void removeObject(const WorldObjectPtr &_object);

	const CVec2D<u32> &getPosition() const;

	u32 getObjectCount() const;

	WorldObjectPtr &getObject(u32 _num);

	void setPosition(const CVec2D<u32> &_pos);

	bool sendToAllPlayers(const CByteArray &_packet);

	bool sendToAllPlayersBut(const CByteArray &_packet, const PlayerObjectPtr &_playerObject);

	bool intersectsWith(const IWorldField *_field) const;

	//returns true if _field is in this' area
	bool isFieldInArea(const IWorldField *_field) const;

	bool despawnAll(const PlayerObjectPtr &_player) const;

	bool spawnAll(const PlayerObjectPtr &_player) const;

	bool isPlayerIn() const;

private:

	CVec2D<u32> m_pos;

	CArray<WorldObjectPtr> m_objects;

	s32 m_playersIn;

};


#endif //WORLDFIELD_H
