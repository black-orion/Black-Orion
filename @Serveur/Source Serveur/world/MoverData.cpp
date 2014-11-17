#include "MoverData.h"


IMoverData::IMoverData()
	: m_id(0)
	, m_idName("")
	, m_level(0)
	, m_class(RANK_LOW)
	, m_element(ELE_NONE)
	, m_exp(0)
	, m_penyaMin(0)
	, m_penyaMax(0)
	, m_hp(1)
	, m_def(0)
	, m_atkMin(0)
	, m_atkMax(0)
	, m_attackDelay(5000)
	, m_hit(100)
	, m_evasion(100)
{
}

IMoverData::~IMoverData()
{
	FOR_EACH (m_drops, i)
	{
		delete m_drops[i];
	}
}

ID IMoverData::getId() const
{
	return m_id;
}

const char *IMoverData::getIdName() const
{
	return m_idName.c_str();
}

LVL IMoverData::getLevel() const
{
	return m_level;
}

E_ELEMENT IMoverData::getElement() const
{
	return m_element;
}

EXP IMoverData::getExp() const
{
	return m_exp;
}

PENYA IMoverData::getPenyaMin() const
{
	return m_penyaMin;
}

PENYA IMoverData::getPenyaMax() const
{
	return m_penyaMax;
}

u32 IMoverData::getDropCount() const
{
	return m_drops.size();
}

const IMoverData::DropBase *IMoverData::getDrop(u32 _num) const
{
	FDASSERT(_num < m_drops.size());

	return m_drops[_num];
}

s32 IMoverData::getHp() const
{
	return m_hp;
}

s32 IMoverData::getDef() const
{
	return m_def;
}

s32 IMoverData::getAttackMin() const
{
	return m_atkMin;
}

s32 IMoverData::getAttackMax() const
{
	return m_atkMax;
}

TimeMs IMoverData::getAttackDelay() const
{
	return m_attackDelay;
}

s32 IMoverData::getHitRate() const
{
	return m_hit;
}

s32 IMoverData::getEvasion() const
{
	return m_evasion;
}