#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H


#include "WorldMain.h"
#include "WorldSettings.h"
#include "../shared/Timed.h"
#include "../shared/RefCounted.h"


class IWorldPlayer;
class IWorldField;
class IWorld;
class IPlayerObject;


class IWorldObject : public ITimed, public IRefCounted
{
public:

	enum E_TYPE
	{
		TYPE_OBJECT   = 0x00,
		TYPE_PLAYER   = 0x01,
		TYPE_NPC      = 0x02,
		TYPE_DROP     = 0x04,
		TYPE_MOB      = 0x08,
		TYPE_ITEM_PET = 0x10,
		TYPE_STAT_PET = 0x20
	};

	IWorldObject(ID _id, IWorld *_world);

	virtual ~IWorldObject();

	ID getId() const;

	virtual E_TYPE getType() const;

	bool isPlayer() const;

	bool isNpc() const;

	bool isDrop() const;

	bool isMob() const;

	bool isCreature() const;

	bool isPet() const;

	IWorld *getWorld();

	IWorldField *getField();

	const CPoint &getPosition() const;

	s16 getRotation() const;

	s16 getSize() const;

	TimeMs getRemoveTime() const;

	void setWorld(IWorld *_world);

	void setField(IWorldField *_field);

	void setPosition(const CPoint &_pos);

	void setPositionPlain(const CPoint &_pos);

	void setRotation(s16 _rotation);

	void setSize(s16 _size);

	void setRemoveTime(TimeMs _time);

	virtual bool init();

	virtual void update();

	bool sendToLocalArea(const CByteArray &_packet);

	bool sendToLocalArea(const CByteArray &_packet, const PlayerObjectPtr &_noSend);

	void onChangePosition();

	virtual void onWorldRemove();

	virtual void onDestroy();

	static const char *getTypeName(E_TYPE _type);

	static IWorldGameSettings *getGameSettings();

	static void setGameSettings(IWorldGameSettings *_settings);

protected:

	ID m_id;

	IWorld *m_world;

	IWorldField *m_field;

	CPoint m_pos;

	s16 m_rotation; //3600 = 360°

	s16 m_size;

	TimeMs m_removeTime;

	static IWorldGameSettings *ms_gameSettings;
};


#endif //WORLDOBJECT_H
