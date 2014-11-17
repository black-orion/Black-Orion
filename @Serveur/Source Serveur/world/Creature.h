#ifndef CREATURE_H
#define CREATURE_H


#include "WorldMain.h"
#include "MovingObject.h"
#include "../shared/E_STAT.h"


class ICreature : public IMovingObject
{
public:

	enum E_ATTACK_FLAG
	{
		ATT_NORMAL = 0x00000000,
		ATT_MISS   = 0x00000002,
		ATT_CRIT   = 0x00000040,
		ATT_PARRY  = 0x00000200,
		ATT_BLOCK  = 0x00001000
	};

	enum E_DEATH
	{
		DEATH_MOB, //player killed by mob
		DEATH_PLAYER, //mob killed by player
		DEATH_PVP, //player killed by player
		DEATH_PK, //player killed by player
		DEATH_SPC //sth killed by a special event
	};

	struct AttackResult
	{
		s32 Damage;

		s32 Flags;

		bool Kill;

		AttackResult()
			: Damage(0)
			, Flags(ATT_NORMAL)
			, Kill(false)
		{
		}
	};

	ICreature(ID _id, IWorld *_world);

	~ICreature();

	bool isAlive() const;

	bool isDead() const;

	s32 getStat(E_STAT _type) const;

	s32 getMinDef() const;

	s32 getMaxDef() const;

	virtual LVL getLevel() const;

	s32 getSpeed() const;

	void setStat(E_STAT _type, s32 _amount);

	void setStat(E_STAT _type, s32 _amount, bool _sendUpdate);

	void setMinDef(s32 _def);

	void setMaxDef(s32 _def);

	void setTarget(IWorldObject *_target);

	void addStat(E_STAT _type, s32 _amount);

	void addStat(const IStatEffect &_effect);

	void addMinDef(s32 _def);

	void addMaxDef(s32 _def);

	void fillHp();

	void fillMp();

	void fillFp();

	virtual void calculateStats();

	const AttackResult &getAttackResult() const;

	virtual const AttackResult &attack(ICreature *_target, s32 _attackMotion = 30);

	virtual void damage(AttackResult &_result, const CreaturePtr &_attacker);

	virtual void kill(E_DEATH _type, const CreaturePtr &_killer = CreaturePtr());

	void onStatRelatedChanged();

	void onWorldRemove();

	void onDestroy();

protected:

	AttackResult m_attackResult;

	s32 m_stats[COUNT_OF_STATS];

	s32 m_def[2];

	void _clearStats();

	void _creatureRemove();

};


#endif //CREATURE_H
