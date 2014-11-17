#include "SpecialOption.h"
#include "ItemData.h"
#include "RandomOption.h"


E_LEVEL_DOWN levelDown(ID _id)
{
	switch (_id)
	{
	case LEVEL_DOWN_LOW:
	case LEVEL_DOWN_HIGH:
		return E_LEVEL_DOWN(_id);

	default:
		return NO_LEVEL_DOWN;
	}
}

ISpecialOption::ISpecialOption()
	: m_code(0)
	, m_lvlDown(NO_LEVEL_DOWN)
	, m_stat(0)
{
}

ISpecialOption::ISpecialOption(s64 _code)
	: m_lvlDown(NO_LEVEL_DOWN)
	, m_stat(0)
{
	setCode(_code);
}

ISpecialOption::ISpecialOption(
	const IStatEffect &_effect0,
	const IStatEffect &_effect1,
	const IStatEffect &_effect2,
	E_LEVEL_DOWN _lvlDown,
	const IRandomOption *_stat)
	: m_code(0)
	, m_lvlDown(_lvlDown)
	, m_stat(_stat)
	, m_effect0(_effect0)
	, m_effect1(_effect1)
	, m_effect2(_effect2)
{
}

ISpecialOption::ISpecialOption(
	E_STAT _type0, s32 _amount0,
	E_STAT _type1, s32 _amount1,
	E_STAT _type2, s32 _amount2,
	E_LEVEL_DOWN _lvlDown,
	const IRandomOption * _stat)
	: m_code(0)
	, m_lvlDown(_lvlDown)
	, m_stat(_stat)
	, m_effect0(_type0, _amount0)
	, m_effect1(_type1, _amount1)
	, m_effect2(_type2, _amount2)
{
}

void ISpecialOption::reset()
{
	m_code = 0;
	m_lvlDown = NO_LEVEL_DOWN;
	m_stat = 0;
	m_effect0.reset();
	m_effect1.reset();
	m_effect2.reset();
}

IStatEffect &ISpecialOption::getEffect(u32 _num)
{
	FDASSERT(_num < EFFECT_COUNT);

	switch (_num)
	{
	case 0:
		return m_effect0;

	case 1:
		return m_effect1;

	default:
		return m_effect2;
	};
}

const IStatEffect &ISpecialOption::getEffect(u32 _num) const
{
	FDASSERT(_num < EFFECT_COUNT);

	switch (_num)
	{
	case 0:
		return m_effect0;

	case 1:
		return m_effect1;

	default:
		return m_effect2;
	};
}

E_LEVEL_DOWN ISpecialOption::getLevelDown() const
{
	return m_lvlDown;
}

const IRandomOption *ISpecialOption::getStat() const
{
	return m_stat;
}

ID ISpecialOption::getStatId() const
{
	return m_stat ? m_stat->getId() : 0;
}

s64 ISpecialOption::getCode()
{
	if (m_code == 0)
	{
		updateCode();
	}

	return m_code;
}

void ISpecialOption::setEffect(u32 _num, const IStatEffect &_effect)
{
	FDASSERT(_num < EFFECT_COUNT);

	m_code = 0;

	switch (_num)
	{
	case 0:
		m_effect0 = _effect;

	case 1:
		m_effect1 = _effect;

	case 2:
		m_effect2 = _effect;
	};
}

void ISpecialOption::setLevelDown(E_LEVEL_DOWN _lvlDown)
{
	m_lvlDown = _lvlDown;
}

void ISpecialOption::setStat(const IRandomOption *_stat)
{
	m_stat = _stat;
}

void ISpecialOption::setStat(ID _statId)
{
	m_stat = IItemData::randomOption(_statId);
}

void ISpecialOption::setCode(s64 _code)
{
	m_code = _code;

	//effect 2

	setStat(_code & 0xff);

	_code >>= 8;
	m_effect2.Amount = _code & ((1 << 9) - 1);
	if (_code & (1 << 9))
	{
		m_effect2.Amount = -m_effect2.Amount;
	}

	_code >>= 10;
	m_effect2.Type = stat(_code & ((1 << 8) - 1));

	//effect 1

	_code >>= 8;
	m_effect1.Amount = _code & ((1 << 9) - 1);
	if (_code & (1 << 9))
	{
		m_effect1.Amount = -m_effect1.Amount;
	}

	_code >>= 10;
	m_effect1.Type = stat(_code & ((1 << 8) - 1));

	//effect 0

	_code >>= 8;
	m_effect0.Amount = _code & ((1 << 9) - 1);
	if (_code & (1 << 9))
	{
		m_effect0.Amount = -m_effect0.Amount;
	}

	_code >>= 10;
	m_effect0.Type = stat(_code & ((1 << 8) - 1));
}

void ISpecialOption::updateCode()
{
	m_code =
		s64(getStatId()) |

		(s64(m_effect0.Amount & ((1 << 10) - 1)) << 8) |
		//(s64(m_effect2.Amount < 0) << 16) |
		(s64(m_effect0.Type & ((1 << 8) - 1)) << 18) |

		(s64(m_effect1.Amount & ((1 << 10) - 1)) << 26) |
		//(s64(m_effect1.Amount < 0) << 34) |
		(s64(m_effect1.Type & ((1 << 8) - 1)) << 36) |

		(s64(m_effect2.Amount & ((1 << 10) - 1)) << 44) |
		//(s64(m_effect0.Amount < 0) << 52) |
		(s64(m_effect2.Type & ((1 << 8) - 1)) << 54);

	//Scroll of Level Down (-10)
	if (m_lvlDown)
	{
		if (m_effect0.Amount)
		{
			if (m_effect1.Amount)
			{
				if (m_effect2.Amount)
				{
					m_code |= (s64(m_lvlDown) << 62);
				}
				else
				{
					m_code |= (s64(m_lvlDown) << 44);
				}
			}
			else
			{
				m_code |= (s64(m_lvlDown) << 26);
			}
		}
		else
		{
			m_code |= (s64(m_lvlDown) << 19);
		}
	}
}

bool ISpecialOption::isNull()
{
	return (
		m_effect0.isNull() &&
		m_effect1.isNull() &&
		m_effect2.isNull());
}

bool ISpecialOption::isValid()
{
	return (
		m_effect0.isValid() &&
		m_effect1.isValid() &&
		m_effect2.isValid());
}

void ISpecialOption::clearAwakening()
{
	m_effect0.reset();
	m_effect1.reset();
	m_effect2.reset();

	m_code = 0;
}