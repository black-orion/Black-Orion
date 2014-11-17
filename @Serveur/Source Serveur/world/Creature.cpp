#include "Creature.h"
#include "WorldField.h"
#include "World.h"
#include "PlayerObject.h"
#include "../shared/PacketCreator.h"


ICreature::ICreature(ID _id, IWorld *_world)
	: IMovingObject(_id, _world)
{
	_clearStats();
}

ICreature::~ICreature()
{
}

bool ICreature::isAlive() const
{
	return (m_stats[DST_HP] > 0);
}

bool ICreature::isDead() const
{
	return !isAlive();
}

s32 ICreature::getStat(E_STAT _type) const
{
	FDASSERT(_type == stat(_type));

	return m_stats[_type];
}

s32 ICreature::getMinDef() const
{
	return m_def[0];
}

s32 ICreature::getMaxDef() const
{
	return m_def[1];
}

LVL ICreature::getLevel() const
{
	return 0;
}

s32 ICreature::getSpeed() const
{
	return m_stats[DST_SPEED];
}

void ICreature::setStat(E_STAT _type, s32 _amount)
{	
	FDASSERT(_type == stat(_type));

	m_stats[_type] = _amount;
}

void ICreature::setStat(E_STAT _type, s32 _amount, bool _sendUpdate)
{	
	FDASSERT(_type == stat(_type));

	m_stats[_type] = _amount;

	if (_sendUpdate)
	{
		sendToLocalArea(IPacketCreator::updateAttribute(this, _type, m_stats[_type]));
	}
}

void ICreature::setMinDef(s32 _def)
{
	m_def[0] = _def;
}

void ICreature::setMaxDef(s32 _def)
{
	m_def[1] = _def;
}

void ICreature::setTarget(IWorldObject *_target)
{
	m_target = _target;
}

void ICreature::addStat(E_STAT _type, s32 _amount)
{	
	FDASSERT(_type == stat(_type));

	m_stats[_type] += _amount;
}

void ICreature::addStat(const IStatEffect &_effect)
{
	addStat(_effect.Type, _effect.Amount);
}

void ICreature::addMinDef(s32 _def)
{
	m_def[0] += _def;
}

void ICreature::addMaxDef(s32 _def)
{
	m_def[1] += _def;
}

void ICreature::fillHp()
{
	setStat(DST_HP, getStat(DST_HP_MAX));
}

void ICreature::fillMp()
{
	setStat(DST_MP, getStat(DST_MP_MAX));
}

void ICreature::fillFp()
{
	setStat(DST_FP, getStat(DST_FP_MAX));
}

void ICreature::calculateStats()
{
	_clearStats();
}

const ICreature::AttackResult &ICreature::getAttackResult() const
{
	return m_attackResult;
}

const ICreature::AttackResult &ICreature::attack(ICreature *_target, s32 _attackMotion)
{
	FDASSERT(_target);

	//..

	return m_attackResult;
}

void ICreature::damage(AttackResult &_result, const CreaturePtr &_attacker)
{
	FDASSERT(_attacker);

	FDASSERT(false && "Method not implemented by an heir!");
}

void ICreature::kill(E_DEATH _type, const CreaturePtr &_killer)
{
	m_stats[DST_HP] = 0;

	m_field->sendToAllPlayers(IPacketCreator::objectDeath(this));
}

void ICreature::onStatRelatedChanged()
{
}

void ICreature::onWorldRemove()
{
	IMovingObject::onWorldRemove();
}

void ICreature::onDestroy()
{
	IMovingObject::onDestroy();
}

void ICreature::_clearStats()
{
	m_stats[DST_STR] = 0; 
	m_stats[DST_DEX] = 0; 
	m_stats[DST_INT] = 0; 
	m_stats[DST_STA] = 0; 
	m_stats[DST_YOY_DMG] = 0; 
	m_stats[DST_BOW_DMG] = 0; 
	m_stats[DST_CHR_RANGE] = 0;
	m_stats[DST_BLOCK_RANGE] = 0; 
	m_stats[DST_CHR_CHANCECRITICAL] = 0; 
	m_stats[DST_CHR_BLEEDING] = 0;
	m_stats[DST_SPEED] = 64; //! 
	m_stats[DST_ABILITY_MIN] = 0; 
	m_stats[DST_ABILITY_MAX] = 0; 
	m_stats[DST_BLOCK_MELEE] = 0; 
	m_stats[DST_MASTRY_EARTH] = 0;
	m_stats[DST_STOP_MOVEMENT] = 0;
	m_stats[DST_MASTRY_FIRE] = 0;
	m_stats[DST_MASTRY_WATER] = 0;
	m_stats[DST_MASTRY_ELECTRICITY] = 0;
	m_stats[DST_MASTRY_WIND] = 0;
	m_stats[DST_KNUCKLE_DMG] = 0; 
	m_stats[DST_PVP_DMG_RATE] = 0;
	m_stats[DST_ATTACKSPEED] = 0; 
	m_stats[DST_SWD_DMG] = 0; 
	m_stats[DST_ADJDEF] = 0; 
	m_stats[DST_RESIST_MAGIC] = 0; 
	m_stats[DST_RESIST_ELECTRICITY] = 0;
	m_stats[DST_REFLECT_DAMAGE] = 0;
	m_stats[DST_RESIST_FIRE] = 0;
	m_stats[DST_RESIST_WIND] = 0;
	m_stats[DST_RESIST_WATER] = 0;
	m_stats[DST_RESIST_EARTH] = 0;
	m_stats[DST_AXE_DMG] = 0; 
	m_stats[DST_HP_MAX] = 0; 
	m_stats[DST_MP_MAX] = 0; 
	m_stats[DST_FP_MAX] = 0; 
	//m_stats[DST_HP] = 0; !
	//m_stats[DST_MP] = 0; !
	//m_stats[DST_FP] = 0; !
	m_stats[DST_HP_RECOVERY] = 0; 
	m_stats[DST_MP_RECOVERY] = 0; 
	m_stats[DST_FP_RECOVERY] = 0; 
	m_stats[DST_KILL_HP] = 0;
	m_stats[DST_KILL_MP] = 0;
	m_stats[DST_KILL_FP] = 0;
	m_stats[DST_ADJ_HITRATE] = 0; 
	m_stats[DST_CLEARBUFF] = 0;
	m_stats[DST_CHR_STEALHP_IMM] = 0;
	m_stats[DST_ATTACKSPEED_RATE] = 0;
	m_stats[DST_HP_MAX_RATE] = 0; 
	m_stats[DST_MP_MAX_RATE] = 0; 
	m_stats[DST_FP_MAX_RATE] = 0; 
	m_stats[DST_CHR_WEAEATKCHANGE] = 0;
	m_stats[DST_CHR_STEALHP] = 0;
	m_stats[DST_CHR_CHANCESTUN] = 0;
	m_stats[DST_AUTOHP] = 0;
	m_stats[DST_CHR_CHANCEDARK] = 0;
	m_stats[DST_CHR_CHANCEPOISON] = 0;
	m_stats[DST_IMMUNITY] = 0;
	m_stats[DST_ADDMAGIC] = 0;
	m_stats[DST_CHR_DMG] = 0; 
	m_stats[DST_CHRSTATE] = 0;
	m_stats[DST_PARRY] = 0;
	m_stats[DST_ATKPOWER_RATE] = 0; 
	m_stats[DST_EXPERIENCE] = 0;
	m_stats[DST_JUMPING] = 0;
	m_stats[DST_CHR_CHANCESTEALHP] = 0;
	m_stats[DST_CHR_CHANCEBLEEDING] = 0;
	m_stats[DST_RECOVERY_EXP] = 0;
	m_stats[DST_ADJDEF_RATE] = 0; 
	m_stats[DST_MP_DEC_RATE] = 0;
	m_stats[DST_FP_DEC_RATE] = 0;
	m_stats[DST_SPELL_RATE] = 0;
	m_stats[DST_CAST_CRITICAL_RATE] = 0;
	m_stats[DST_CRITICAL_BONUS] = 0; 
	m_stats[DST_SKILL_LEVEL] = 0;
	m_stats[DST_MONSTER_DMG] = 0;
	m_stats[DST_PVP_DMG] = 0; 
	m_stats[DST_MELEE_STEALHP] = 0;
	m_stats[DST_HEAL] = 0;
	m_stats[DST_ATKPOWER] = 0;
	m_stats[DST_ONEHANDMASTER_DMG] = 0;
	m_stats[DST_TWOHANDMASTER_DMG] = 0;
	m_stats[DST_YOYOMASTER_DMG] = 0;
	m_stats[DST_BOWMASTER_DMG] = 0;
	m_stats[DST_KNUCKLEMASTER_DMG] = 0;
	m_stats[DST_HAWKEYE_RATE] = 0;
	m_stats[DST_RESIST_MAGIC_RATE] = 0;
	m_stats[DST_GIFTBOX] = 0;
	m_stats[MAX_ADJPARAMARY] = 0;
	m_stats[DST_GOLD] = 0; 
	m_stats[DST_PXP] = 0;
	m_stats[DST_RESIST_ALL] = 0;
	m_stats[DST_STAT_ALLUP] = 0;
	m_stats[DST_HPDMG_UP] = 0; 
	m_stats[DST_DEFHITRATE_DOWN] = 0;
	m_stats[DST_CURECHR] = 0; 
	m_stats[DST_HP_RECOVERY_RATE] = 0; 
	m_stats[DST_MP_RECOVERY_RATE] = 0; 
	m_stats[DST_FP_RECOVERY_RATE] = 0; 
	m_stats[DST_LOCOMOTION] = 0; 
	m_stats[DST_MASTRY_ALL] = 0;
	m_stats[DST_ALL_RECOVERY] = 0;
	m_stats[DST_ALL_RECOVERY_RATE] = 0;
	m_stats[DST_KILL_ALL] = 0;
	m_stats[DST_KILL_HP_RATE] = 0;
	m_stats[DST_KILL_MP_RATE] = 0;
	m_stats[DST_KILL_FP_RATE] = 0;
	m_stats[DST_KILL_ALL_RATE] = 0;
	m_stats[DST_ALL_DEC_RATE] = 0;

	m_def[0] = 0;
	m_def[1] = 0;
}

void ICreature::_creatureRemove()
{
}