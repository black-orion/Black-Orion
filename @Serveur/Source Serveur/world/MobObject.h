#ifndef MOBOBJECT_H
#define MOBOBJECT_H


#include "WorldMain.h"
#include "WorldObject.h"
#include "Creature.h"
#include "../shared/ItemPack.h"


class IMoverData;
class ISpawn;


class IMobObject : public ICreature
{
public:

	enum
	{
		PENYA_DROP_ITEM_COUNT = 4
	};

	struct PenyaDrop
	{
		PENYA Amount;

		const IItemData *Item;
	};

	IMobObject(ID _id, IWorld *_world, const IMoverData *_mover, bool _aggro, ISpawn *_spawn = 0,
		const CPoint &_spawnPos = CPoint());

	~IMobObject();

	E_TYPE getType() const;

	const IMoverData *getMover() const;

	ISpawn *getSpawn();

	const CPoint &getSpawnPosition() const;

	LVL getLevel() const;

	TimeMs getNextMoveTime() const;

	bool isAggressive() const;

	const PlayerObjectPtr &getAttackTarget() const;

	TimeMs getNextAttackTime() const;

	//copies position etc from the character
	bool init();

	void update();

	void calculateStats();

	const AttackResult &attack(const CreaturePtr &_target, s32 _attackMotion = 30);

	void damage(AttackResult &_result, const CreaturePtr &_attacker);

	void kill(E_DEATH _type, CreaturePtr _killer = CreaturePtr());

	void onWorldRemove();

	void onDestroy();

	static TimeMs getRemoveDelay();

	static TimeMs getMoveDelay();

	static f32 getMoveRange();

	static void setRemoveDelay(TimeMs _time);

	//set the delay for all mobs without a spawn
	static void setMoveDelay(TimeMs _time);

	static void setMoveRange(f32 _range);

	static void setPenyaDropItems(const PenyaDrop *_dropArray);

private:

	const IMoverData *m_mover;

	ISpawn *m_spawn;

	CPoint m_spawnPos;

	IItemProperties m_dropItem;

	TimeMs m_nextMoveTime;

	bool m_aggro;

	PlayerObjectPtr m_attackTarget;

	TimeMs m_nextAttackTime;

	TimeMs m_nextAggressionTime;

	static PenyaDrop ms_penyaDrops[PENYA_DROP_ITEM_COUNT];

	static TimeMs ms_removeDelay;

	static TimeMs ms_moveDelay;

	static f32 ms_moveRange;

	void _dropItems(const PlayerObjectPtr &_owner);

	virtual void _onDeath();

	static const IItemData *_getPenyaDropItem(PENYA _amount);

};


/// Special case: Clockwork ///
///////////////////////////////

class IGuild;

class IClockWorkObject : public IMobObject
{
public:

	IClockWorkObject(ID _id, IWorld *_world, const IMoverData *_mover, bool _aggro = false);

	~IClockWorkObject();

	IGuild *getGuild();

	void enterRoom(IGuild *_guild);

	void leaveRoom();

	void update();

private:

	IGuild *m_guild;

	TimeMs m_endTime;

	void _onDeath();

};


/// Special case: Meteonyker ///
////////////////////////////////


#endif //MOBOBJECT_H
