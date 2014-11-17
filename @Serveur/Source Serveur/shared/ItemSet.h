#ifndef ITEMSET_H
#define ITEMSET_H


#include "Base.h"
#include "E_STAT.h"


class IItemDataManager;
class IItemData;


class IItemSet
{
public:

	enum
	{
		COUNT_OF_PARTS = 4
	};

	IItemSet();

	ID getId() const;

	const IItemData *getPart(u32 _num) const;

	u32 getEffectCount(u32 _parts) const;

	const IStatEffect &getEffect(u32 _parts, u32 _num) const;

	static bool isValidParts(u32 _parts);

private:

	friend class IItemDataManager;

	ID m_id;

	const IItemData *m_parts[COUNT_OF_PARTS];

	CArray<IStatEffect> m_effects[COUNT_OF_PARTS - 1];

	CArray<IStatEffect> &_getEffects(u32 _parts);

	const CArray<IStatEffect> &_getEffects(u32 _parts) const;

};


#endif //ITEMSET_H
