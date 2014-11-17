#include "ItemSet.h"
#include "ItemData.h"


IItemSet::IItemSet()
	: m_id(0)
{
	memset(m_parts, 0, sizeof(m_parts));
}

ID IItemSet::getId() const
{
	return m_id;
}

const IItemData *IItemSet::getPart(u32 _num) const
{
	FDASSERT(_num < COUNT_OF_PARTS);

	return m_parts[_num];
}

u32 IItemSet::getEffectCount(u32 _parts) const
{
	return _getEffects(_parts).size();
}

const IStatEffect &IItemSet::getEffect(u32 _parts, u32 _num) const
{
	FDASSERT(_num <  _getEffects(_parts).size());

	return _getEffects(_parts)[_num];
}

CArray<IStatEffect> &IItemSet::_getEffects(u32 _parts)
{
	FDASSERT(isValidParts(_parts));

	return m_effects[_parts - 2];
}

const CArray<IStatEffect> &IItemSet::_getEffects(u32 _parts) const
{
	FDASSERT(isValidParts(_parts));

	return m_effects[_parts - 2];
}

bool IItemSet::isValidParts(u32 _parts)
{
	return (_parts >= 2 &&
		_parts <= 4);
}