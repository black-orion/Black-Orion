#ifndef WORLD_H
#define WORLD_H


#include "WorldMain.h"
#include "WorldObject.h"
#include "WorldField.h"
#include "../shared/Timed.h"
#include "../shared/ItemPack.h"


class IWorldServer;
class IPlayerObject;
class IMobObject;
class INpcObject;
class IDropObject;
class IMoverData;
class IWorldDataManager;
class ISpawn;
class ISpawnData;
class INpcData;


class IWorld : public ITimed
{
public:

	IWorld(ID _id, const char *_name, s32 _width, s32 _height, s32 _fieldSize, IWorldDataManager *_data,
		IWorldServer *_server);

	~IWorld();

	ID getId() const;

	const char *getName() const;

	s32 getWidth() const;

	s32 getHeight() const;

	s32 getFieldSize() const;

	CVec2D<u32> getDimension() const;

	IWorldField *getField(u32 _x, u32 _y);

	const IWorldField *getField(u32 _x, u32 _y) const;

	IWorldField *getFieldByPosition(const CPoint &_pos);

	const IWorldField *getFieldByPosition(const CPoint &_pos) const;

	IWorldServer *getServer();

	ISpawn *addSpawn(const ISpawnData *_data);

	u32 getSpawnCount() const;

	ISpawn *getSpawn(u32 _num);

	void removeSpawn(u32 _num);

	void updateField(const WorldObjectPtr &_obj);

	MobObjectPtr createMobObject(const IMoverData *_mover, const CPoint &_pos, bool _aggro, ISpawn *_spawn);

	NpcObjectPtr createNpcObject(const INpcData *_data);

	DropObjectPtr createDropObject(const IItemProperties &_item, const CPoint &_pos,
		PlayerObjectPtr _owner = PlayerObjectPtr(0));

	ItemPetObjectPtr createItemPetObject(PlayerObjectPtr &_owner, const IMoverData *_mover);

	StatPetObjectPtr createStatPetObject(PlayerObjectPtr &_owner, const IMoverData *_mover /*, ...*/);

	u32 getObjectCount() const;

	WorldObjectPtr &getObjectByNumber(u32 _num);

	WorldObjectPtr getObjectById(ID _id);

	PlayerObjectPtr getPlayerByName(const char *_name);

	NpcObjectPtr getNpcByTitle(const char *_title);

	u32 getPlayerCount() const;

	u32 getNpcCount() const;

	u32 getMobCount() const;

	u32 getDropCount() const;

	bool isObjectIn(const WorldObjectPtr &_object);

	void addObject(const WorldObjectPtr &_object);

	void removeObject(u32 _num, bool _destroy);

	void removeObject(const WorldObjectPtr &_object, bool _destroy);

	void transferObject(const WorldObjectPtr &_object, IWorld *_targetWorld);

	void noTarget(const WorldObjectPtr &_obj);

	void buffEvent(const WorldObjectPtr &_pObj);

	void update();

	//Adds the player to this world and creates an object if necessary.
	//Spawns everything, removes and despawns player from the old world (if it's not 0).
	void addPlayer(IWorldPlayer *_player, const CPoint *_pos = 0);

	bool sendToAllPlayers(const CByteArray &_packet);

	bool sendToLocalArea(const WorldObjectPtr &_obj, const CByteArray &_packet);

	bool sendToLocalArea(const WorldObjectPtr &_obj, const CByteArray &_packet, const PlayerObjectPtr &_noSend);

	bool isPlayerInLocalArea(const WorldObjectPtr &_obj) const;

	PlayerObjectPtr getNearestObject(IWorldObject::E_TYPE _type, const WorldObjectPtr &_obj, f32 _range);

private:

	//data
	IWorldDataManager *m_data;

	//general infos
	ID m_id;

	sdk::stringc m_name;

	IWorldServer *m_pserver;

	s32 m_width;

	s32 m_height;

	s32 m_fieldSize;

	//fields
	CArray<CArray<IWorldField> > m_fields;

	//objects
	CArray<WorldObjectPtr> m_objects;

	//mob spawns
	CArray<ISpawn*> m_spawns;

	static ID ms_nextObjectId;

	IPlayerObject *_createPlayerObject(IWorldPlayer *_player);

	void _changeField(const WorldObjectPtr &_obj, IWorldField *_old, IWorldField *_new);

	void _getCorrectedFieldRange(CVec2D<u32> &_start, CVec2D<u32> &_end, const IWorldField *_field) const;

	static ID _generateObjectId();

};


#endif //WORLD_H
