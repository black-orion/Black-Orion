#include "World.h"
#include "WorldField.h"
#include "WorldPlayer.h"
#include "PlayerObject.h"
#include "MobObject.h"
#include "NpcObject.h"
#include "DropObject.h"
#include "ItemPetObject.h"
#include "MoverData.h"
#include "WorldDataManager.h"
#include "Spawn.h"
#include "SpawnData.h"
#include "NpcData.h"
#include "WorldServer.h"
#include "../shared/PacketCreator.h"
#include "../shared/Log.h"
#include "../shared/Character.h"


ID IWorld::ms_nextObjectId = 1;

IWorld::IWorld(ID _id, const char *_name, s32 _width, s32 _height, s32 _fieldSize, IWorldDataManager *_data,
			   IWorldServer *_server)
	: ITimed()
	, m_id(_id)
	, m_name(_name)
	, m_width(_width)
	, m_height(_height)
	, m_fieldSize(_fieldSize)
	, m_data(_data)
	, m_pserver(_server)
{
	FDASSERT(m_data);
	FDASSERT(m_pserver);

	u32 t_newWidth = static_cast<u32>(ceil(f32(m_width) / f32(m_fieldSize)));
	u32 t_newHeight = static_cast<u32>(ceil(f32(m_height) / f32(m_fieldSize)));

	m_fields.resize(t_newWidth);

	u32 j;
	for (u32 i = 0; i < t_newWidth; ++i)
	{
		m_fields[i].resize(t_newHeight);

		for (j = 0; j < t_newHeight; ++j)
		{
			m_fields[i][j].setPosition(CVec2D<u32>(i, j));
		}
	}
}

IWorld::~IWorld()
{
	FOR_EACH (m_spawns, i)
	{
		delete m_spawns[i];
	}
}

ID IWorld::getId() const
{
	return m_id;
}

const char *IWorld::getName() const
{
	return m_name.c_str();
}

s32 IWorld::getWidth() const
{
	return m_width;
}

s32 IWorld::getHeight() const
{
	return m_height;
}

s32 IWorld::getFieldSize() const
{
	return m_fieldSize;
}

CVec2D<u32> IWorld::getDimension() const
{
	return CVec2D<u32>(m_fields.size(), m_fields.empty() ? 0 : m_fields[0].size());
}

IWorldField *IWorld::getField(u32 _x, u32 _y)
{
	FDASSERT(!m_fields.empty());
	FDASSERT(_x < m_fields.size());
	FDASSERT(_y < m_fields[0].size());

	return &m_fields[_x][_y];
}

const IWorldField *IWorld::getField(u32 _x, u32 _y) const
{
	FDASSERT(!m_fields.empty());
	FDASSERT(_x < m_fields.size());
	FDASSERT(_y < m_fields[0].size());

	return &m_fields[_x][_y];
}

IWorldField *IWorld::getFieldByPosition(const CPoint &_pos)
{
	FDASSERT(!m_fields.empty());
	FDASSERT(!m_fields[0].empty());

	if (static_cast<s32>(_pos.X) >= 0 &&
		static_cast<s32>(_pos.Z) >= 0 &&
		static_cast<s32>(_pos.X) < m_width &&
		static_cast<s32>(_pos.Z) < m_height)
	{
		return &m_fields
			[static_cast<u32>(_pos.X / m_fieldSize)]
			[static_cast<u32>(_pos.Z / m_fieldSize)];
	}

	return &m_fields[0][0];
}

const IWorldField *IWorld::getFieldByPosition(const CPoint &_pos) const
{
	FDASSERT(!m_fields.empty());
	FDASSERT(!m_fields[0].empty());

	if (static_cast<s32>(_pos.X) >= 0 &&
		static_cast<s32>(_pos.Z) >= 0 &&
		static_cast<s32>(_pos.X) < m_width &&
		static_cast<s32>(_pos.Z) < m_height)
	{
		return &m_fields
			[static_cast<u32>(_pos.X / m_fieldSize)]
			[static_cast<u32>(_pos.Z / m_fieldSize)];
	}

	return &m_fields[0][0];
}

IWorldServer *IWorld::getServer()
{
	return m_pserver;
}

ISpawn *IWorld::addSpawn(const ISpawnData *_data)
{
	FDASSERT(_data);

	ISpawn *t_spawn = new ISpawn(_data, this);

	m_spawns.push_back(t_spawn);

	return t_spawn;
}

u32 IWorld::getSpawnCount() const
{
	return m_spawns.size();
}

ISpawn *IWorld::getSpawn(u32 _num)
{
	FDASSERT(_num < m_spawns.size());

	return m_spawns[_num];
}

void IWorld::removeSpawn(u32 _num)
{
	FDASSERT(_num < m_spawns.size());

	delete m_spawns[_num];

	m_spawns.erase_fast(_num);
}

void IWorld::updateField(const WorldObjectPtr &_obj)
{
	FDASSERT(_obj);
	FDASSERT(_obj->getWorld() == this);

	IWorldField *t_field = getFieldByPosition(_obj->getPosition());

	//the field has changed
	if (t_field != _obj->getField())
	{
		_changeField(_obj, _obj->getField(), t_field);
	}
}

MobObjectPtr IWorld::createMobObject(const IMoverData *_mover, const CPoint &_pos, bool _aggro, ISpawn *_spawn)
{
	FDASSERT(_mover);

	IMobObject *t_mob = new IMobObject(_generateObjectId(), this, _mover, _aggro, _spawn);

	t_mob->setPosition(_pos);
	t_mob->setRotation(random(0, 3599));

	if (_spawn &&
		_spawn->getData())
	{
		t_mob->setSize(_spawn->getData()->getMoverSize());
	}

	addObject(t_mob);

	return t_mob;
}

NpcObjectPtr IWorld::createNpcObject(const INpcData *_data)
{
	FDASSERT(_data);

	INpcObject *t_npc = new INpcObject(_generateObjectId(), this, _data);

	if (t_npc->init())
	{
		addObject(t_npc);
		return t_npc;
	}
	else
	{
		delete t_npc;
		return 0;
	}
}

DropObjectPtr IWorld::createDropObject(const IItemProperties &_item, const CPoint &_pos,
									   PlayerObjectPtr _owner)
{
	DropObjectPtr t_drop = new IDropObject(_generateObjectId(), this);

	t_drop->setItem(_item);
	t_drop->setPosition(_pos);
	t_drop->setRotation(random(0, 3599));
	t_drop->setOwner(_owner);
	t_drop->setOwnershipEnd(_time() + m_pserver->getSettings()->Game.DropOwnershipTime);

	addObject(t_drop);

	return t_drop;
}

ItemPetObjectPtr IWorld::createItemPetObject(PlayerObjectPtr &_owner, const IMoverData *_mover)
{
	FDASSERT(_owner);
	FDASSERT(_mover);

	ItemPetObjectPtr t_pet(new IItemPetObject(_generateObjectId(), this, _mover, _owner));

	t_pet->setPosition(CPoint::randomPosition(_owner->getPosition(), 2.0f));
	t_pet->setRotation(random(0, 3599));

	_owner->setPet(t_pet);

	addObject(t_pet);

	return t_pet;
}

u32 IWorld::getObjectCount() const
{
	return m_objects.size();
}

WorldObjectPtr &IWorld::getObjectByNumber(u32 _num)
{
	FDASSERT(_num < m_objects.size());

	return m_objects[_num];
}

WorldObjectPtr IWorld::getObjectById(ID _id)
{
	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->getId() == _id)
		{
			return m_objects[i];
		}
	}

	return 0;
}

PlayerObjectPtr IWorld::getPlayerByName(const char *_name)
{
	FDASSERT(_name);

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isPlayer())
		{
			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(m_objects[i]);

			if (strcmp(t_player->getPlayer()->getCharacter()->getName(), _name) == 0)
			{
				return t_player;
			}
		}
	}

	return 0;
}

NpcObjectPtr IWorld::getNpcByTitle(const char *_title)
{
	FDASSERT(_title);

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isNpc())
		{
			NpcObjectPtr t_npc = boost::dynamic_pointer_cast<INpcObject>(m_objects[i]);

			FDASSERT(t_npc->getData());

			if (xstricmp(t_npc->getData()->getName(), _title) == 0)
			{
				return t_npc;
			}
		}
	}

	return 0;
}

u32 IWorld::getPlayerCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isPlayer())
		{
			++r_count;
		}
	}

	return r_count;
}

u32 IWorld::getNpcCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isNpc())
		{
			++r_count;
		}
	}

	return r_count;
}

u32 IWorld::getMobCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isMob())
		{
			++r_count;
		}
	}

	return r_count;
}

u32 IWorld::getDropCount() const
{
	u32 r_count = 0;

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isDrop())
		{
			++r_count;
		}
	}

	return r_count;
}

bool IWorld::isObjectIn(const WorldObjectPtr &_object)
{
	FDASSERT(_object);

	return m_objects.contains(_object);
}

void IWorld::addObject(const WorldObjectPtr &_obj)
{
	FDASSERT(_obj);

	if (_obj->isPlayer())
	{
		addPlayer(boost::dynamic_pointer_cast<IPlayerObject>(_obj)->getPlayer());
	}
	else
	{
		m_objects.push_back(_obj);

		_obj->setWorld(this);

		updateField(_obj);
	}
}

void IWorld::removeObject(u32 _num, bool _destroy)
{
	FDASSERT(_num < m_objects.size());

	_changeField(m_objects[_num], m_objects[_num]->getField(), 0);

	if (_destroy)
	{
		m_objects[_num]->onWorldRemove();
		m_objects[_num]->onDestroy();
	}
	else
	{
		m_objects[_num]->onWorldRemove();
	}

	m_objects[_num].reset();
	m_objects.erase_fast(_num);
}

void IWorld::removeObject(const WorldObjectPtr &_object, bool _destroy)
{
	FDASSERT(_object);

	u32 t_index = 0;
	if (m_objects.find(t_index, _object))
	{
		removeObject(t_index, _destroy);
		return;
	}

	FDASSERT(false);
}

void IWorld::transferObject(const WorldObjectPtr &_object, IWorld *_targetWorld)
{
	FDASSERT(_targetWorld);

	_targetWorld->addObject(_object);

	removeObject(_object, false);
}

void IWorld::noTarget(const WorldObjectPtr &_obj)
{
	FDASSERT(_obj);

	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isCreature())
		{
			CreaturePtr t_creature = boost::dynamic_pointer_cast<ICreature>(m_objects[i]);

			if (t_creature->getTarget() == _obj)
			{
				t_creature->setTarget(0);
			}

			if (t_creature->getFollowed() == _obj)
			{
				t_creature->follow(0);
			}
		}
	}
}

void IWorld::buffEvent(const WorldObjectPtr &_pObj)
{
	FDASSERT(_pObj);
}

void IWorld::update()
{
}

void IWorld::addPlayer(IWorldPlayer *_player, const CPoint *_pos)
{
	FDASSERT(_player);

	//change world
	if (_player->getObject())
	{
		//remove the object from its previous world
		if (_player->getObject()->getWorld())
		{
			FDASSERT(_player->getObject()->getWorld() != this && "IWorld::addPlayer() call is not needed");

			_player->getObject()->getWorld()->removeObject(_player->getObject(), false);
		}

		_player->getObject()->setWorld(this);
		if (_pos)
		{
			_player->getObject()->setPositionPlain(*_pos);
		}

		_player->getClient()->send(IPacketCreator::worldPosUpdate(_player->getObject()));
		_player->getClient()->send(IPacketCreator::worldBegin(_player));

		//add it to this world and spawn everything
		addObject(_player->getObject());
	}

	//there is no object -> create one
	else
	{
		_player->setObject(_createPlayerObject(_player));

		//error
		if (!_player->getObject())
		{
			Log::write(LOG_ERROR, "Could not create world object for character \"%s\"!",
				_player->getCharacter()->getName());
			return;
		}

		m_pserver->getItemPackManager()->loadInventory_W(_player->getObject());

		_player->getObject()->onStatRelatedChanged();

		_player->getClient()->send(IPacketCreator::worldBegin(_player));
		_player->getClient()->send(IPacketCreator::positionUpdate(_player->getObject()));

		//add it to this world and spawn everything
		updateField(_player->getObject());
	}

	_player->getClient()->send(IPacketCreator::weatherAuto(m_pserver->getWeather()));
}

IPlayerObject *IWorld::_createPlayerObject(IWorldPlayer *_player)
{
	FDASSERT(_player);

	IPlayerObject *r_obj = new IPlayerObject(_generateObjectId(), this, _player);

	m_objects.push_back(r_obj);

	//no updateField() !!

	return r_obj;
}

//params _obj and _new are independent from _obj's m_field
void IWorld::_changeField(const WorldObjectPtr &_obj, IWorldField *_old, IWorldField *_new)
{
	FDASSERT(_obj);
	FDASSERT(_old || _new && ("!_old" + u32(_old != 0)));
	FDASSERT(_old != _new);

	//temp field ptr
	IWorldField *t_field;

	if (_old)
	{
		_old->removeObject(_obj);

		//only despawn
		if (!_new)
		{
			sendToLocalArea(_obj, IPacketCreator::despawn(_obj));
			return;
		}
	}

	if (_new)
	{
		_new->addObject(_obj);

		//printf("obj %d added to field\n", _obj->getId());

		//despawn and spawn
		if (_old)
		{
			CVec2D<u32> t_start, t_end;

			u32 x, y;

			//packet for (de)spawning the _obj
			static CByteArray t_despawnPacket;
			t_despawnPacket.clear(); //important!

			//despawning:
			_getCorrectedFieldRange(t_start, t_end, _old);

			for (y = t_start.Y; y <= t_end.Y; ++y)
			{
				for (x = t_start.X; x <= t_end.X; ++x)
				{
					t_field = getField(x, y);

					FDASSERT(t_field);

					if (!_new->isFieldInArea(t_field))
					{
						if (t_field->isPlayerIn())
						{
							if (t_despawnPacket.empty())
							{
								t_despawnPacket = IPacketCreator::despawn(_obj);
							}

							if (_obj->getType() == IWorldObject::TYPE_PLAYER)
							{
								t_field->sendToAllPlayersBut(t_despawnPacket,
									boost::dynamic_pointer_cast<IPlayerObject>(_obj));
							}
							else
							{
								t_field->sendToAllPlayers(t_despawnPacket);
							}
						}

						if (_obj->getType() == IWorldObject::TYPE_PLAYER)
						{
							t_field->despawnAll(boost::dynamic_pointer_cast<IPlayerObject>(_obj));
						}
					}
				}
			}

			t_despawnPacket.clear();

			//spawning:
			_getCorrectedFieldRange(t_start, t_end, _new);

			for (y = t_start.Y; y <= t_end.Y; ++y)
			{
				for (x = t_start.X; x <= t_end.X; ++x)
				{
					t_field = getField(x, y);

					FDASSERT(t_field);

					if (!_old->isFieldInArea(t_field))
					{
						if (t_field->isPlayerIn())
						{
							if (t_despawnPacket.empty())
							{
								t_despawnPacket = IPacketCreator::spawn(_obj);
							}

							if (_obj->getType() == IWorldObject::TYPE_PLAYER)
							{
								PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(_obj);
								t_field->spawnAll(t_player);
								t_field->sendToAllPlayersBut(t_despawnPacket, t_player);
							}
							else
							{
								t_field->sendToAllPlayers(t_despawnPacket);
							}
						}
						else
						{
							if (_obj->getType() == IWorldObject::TYPE_PLAYER)
							{
								t_field->spawnAll(boost::dynamic_pointer_cast<IPlayerObject>(_obj));
							}
						}
					}
				}
			}
		}
		//whole new (!_old)
		else
		{
			CVec2D<u32> t_start, t_end;

			_getCorrectedFieldRange(t_start, t_end, _new);

			IWorldField *t_field;

			const CByteArray *t_packet;
			t_packet = 0;

			u32 x, y;

			if (_obj->getType() == IWorldObject::TYPE_PLAYER)
			{
				for (y = t_start.Y; y <= t_end.Y; ++y)
				{
					for (x = t_start.X; x <= t_end.X; ++x)
					{
						t_field = getField(x, y);

						if (t_field->isPlayerIn())
						{
							if (!t_packet)
							{
								t_packet = &IPacketCreator::spawn(_obj);
							}

							t_field->sendToAllPlayersBut(*t_packet, boost::dynamic_pointer_cast<IPlayerObject>(_obj));
						}

						t_field->spawnAll(boost::dynamic_pointer_cast<IPlayerObject>(_obj));
					}
				}
			}
			else
			{
				for (y = t_start.Y; y <= t_end.Y; ++y)
				{
					for (x = t_start.X; x <= t_end.X; ++x)
					{
						t_field = getField(x, y);

						if (t_field->isPlayerIn())
						{
							if (!t_packet)
							{
								t_packet = &IPacketCreator::spawn(_obj);
							}

							t_field->sendToAllPlayers(*t_packet);
						}
					}
				}
			}
		}
	}
}

void IWorld::_getCorrectedFieldRange(CVec2D<u32> &_start,
									 CVec2D<u32> &_end,
									 const IWorldField *_field) const
{
	FDASSERT(_field);

	//start point for any operations
	_start = _field->getPosition();

	//end point
	_end = _start;

	if (_start.X >= WORLD_FIELD_SIGHT)
	{
		_start.X -= WORLD_FIELD_SIGHT;
	}

	//Y here is Z in the world
	if (_start.Y >= WORLD_FIELD_SIGHT)
	{
		_start.Y -= WORLD_FIELD_SIGHT;
	}

	//correct the end point
	_end.X += WORLD_FIELD_SIGHT;
	_end.Y += WORLD_FIELD_SIGHT;

	if (_end.X >= m_fields.size())
	{
		_end.X = m_fields.size() - 1;
	}

	if (_end.Y >= m_fields[0].size())
	{
		_end.Y = m_fields[0].size() - 1;
	}
}

ID IWorld::_generateObjectId()
{
	FDASSERT(ms_nextObjectId >= 0);

	return ms_nextObjectId++;
}

bool IWorld::sendToAllPlayers(const CByteArray &_packet)
{
	FOR_EACH (m_objects, i)
	{
		if (m_objects[i]->isPlayer())
		{
			PlayerObjectPtr t_player = boost::dynamic_pointer_cast<IPlayerObject>(m_objects[i]);

			FDASSERT(t_player->getPlayer());
			FDASSERT(t_player->getPlayer()->getClient());

			if (!t_player->getPlayer()->getClient()->send(_packet))
			{
				return false;
			}
		}
	}

	return true;
}

bool IWorld::sendToLocalArea(const WorldObjectPtr &_obj, const CByteArray &_packet)
{
	FDASSERT(_obj);

	CVec2D<u32> t_start, t_end;

	_getCorrectedFieldRange(t_start, t_end, _obj->getField());

	IWorldField *t_field;

	u32 x, y;
	for (y = t_start.Y; y <= t_end.Y; ++y)
	{
		for (x = t_start.X; x <= t_end.X; ++x)
		{
			t_field = getField(x, y);

			if (t_field->isPlayerIn())
			{
				if (!t_field->sendToAllPlayers(_packet))
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool IWorld::sendToLocalArea(const WorldObjectPtr &_obj, const CByteArray &_packet, const PlayerObjectPtr &_noSend)
{
	FDASSERT(_obj);

	CVec2D<u32> t_start, t_end;

	_getCorrectedFieldRange(t_start, t_end, _obj->getField());

	IWorldField *t_field;

	u32 x;
	for (u32 y = t_start.Y; y <= t_end.Y; ++y)
	{
		for (x = t_start.X; x <= t_end.X; ++x)
		{
			t_field = getField(x, y);

			FDASSERT(t_field);

			if (!t_field->sendToAllPlayersBut(_packet, _noSend))
			{
				return false;
			}
		}
	}

	return true;
}

bool IWorld::isPlayerInLocalArea(const WorldObjectPtr &_obj) const
{
	FDASSERT(_obj);

	CVec2D<u32> t_start, t_end;

	_getCorrectedFieldRange(t_start, t_end, _obj->getField());

	u32 x, y;
	for (y = t_start.Y; y <= t_end.Y; ++y)
	{
		for (x = t_start.X; x <= t_end.X; ++x)
		{
			if (getField(x, y)->isPlayerIn())
			{
				return true;
			}
		}
	}

	return false;
}

PlayerObjectPtr IWorld::getNearestObject(IWorldObject::E_TYPE _type, const WorldObjectPtr &_obj, f32 _range)
{
	FDASSERT(_obj);

	_range *= _range;

	PlayerObjectPtr r_obj;

	IWorldField *t_field = _obj->getField();
	FDASSERT(t_field);

	for (u32 i = 0; i < t_field->getObjectCount(); ++i)
	{
		if (_type & t_field->getObject(i)->getType())
		{
			if (_obj->getPosition().isInRangeSq(t_field->getObject(i)->getPosition(), _range))
			{
				r_obj = boost::dynamic_pointer_cast<IPlayerObject>(t_field->getObject(i));

				_range = (r_obj->getPosition() - t_field->getObject(i)->getPosition()).lengthSq();
			}
		}
	}

	return r_obj;
}
