#include "RandomOption.h"


IRandomOption::IRandomOption()
	: m_id(0)
{
}

ID IRandomOption::getId() const
{
	return m_id;
}

u32 IRandomOption::getEffectCount() const
{
	return m_effects.size();
}

const IStatEffect &IRandomOption::getEffect(u32 _num) const
{
	FDASSERT(_num < m_effects.size());

	return m_effects[_num];
}