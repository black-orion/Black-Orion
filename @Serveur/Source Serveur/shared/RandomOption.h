#ifndef RANDOMOPTION_H
#define RANDOMOPTION_H


#include "Base.h"
#include "E_STAT.h"


class IItemDataManager;


class IRandomOption
{
public:

	IRandomOption();

	ID getId() const;

	u32 getEffectCount() const;

	const IStatEffect &getEffect(u32 _num) const;

private:

	friend class IItemDataManager;

	ID m_id;

	CArray<IStatEffect> m_effects;
};


#endif //RANDOMOPTION_H
