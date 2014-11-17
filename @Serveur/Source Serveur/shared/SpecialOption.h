#ifndef AWAKENING_H
#define AWAKENING_H


#include "Base.h"
#include "E_STAT.h"


class IRandomOption;


enum E_LEVEL_DOWN
{
	NO_LEVEL_DOWN = 0,
	LEVEL_DOWN_LOW = 1,
	LEVEL_DOWN_HIGH = 2
};


E_LEVEL_DOWN levelDown(ID _id);


class ISpecialOption
{
public:

	enum
	{
		EFFECT_COUNT = 3
	};

	ISpecialOption();

	ISpecialOption(s64 _code);

	ISpecialOption(
		const IStatEffect &_effect0,
		const IStatEffect &_effect1 = IStatEffect(),
		const IStatEffect &_effect2 = IStatEffect(),
		E_LEVEL_DOWN _lvlDown = NO_LEVEL_DOWN,
		const IRandomOption *_stat = 0);

	ISpecialOption(
		E_STAT _type0, s32 _amount0,
		E_STAT _type1 = DST_NONE, s32 _amount1 = 0,
		E_STAT _type2 = DST_NONE, s32 _amount2 = 0,
		E_LEVEL_DOWN _lvlDown = NO_LEVEL_DOWN,
		const IRandomOption *_stat = 0);

	void reset();

	IStatEffect &getEffect(u32 _num);

	const IStatEffect &getEffect(u32 _num) const;

	E_LEVEL_DOWN getLevelDown() const;

	const IRandomOption *getStat() const;

	ID getStatId() const;

	s64 getCode();

	void setEffect(u32 _num, const IStatEffect &_effect);

	void setLevelDown(E_LEVEL_DOWN _lvlDown);

	void setStat(const IRandomOption *_stat);

	void setStat(ID _statId);

	void setCode(s64 _code);

	void updateCode();

	bool isNull();

	bool isValid();

	void clearAwakening();

private:

	IStatEffect m_effect0;
	IStatEffect m_effect1;
	IStatEffect m_effect2;

	E_LEVEL_DOWN m_lvlDown;

	const IRandomOption *m_stat;

	s64 m_code;

};


#endif //AWAKENING_H
