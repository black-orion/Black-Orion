#include "ItemPack.h"
#include "ItemData.h"
#include "Log.h"


/// ItemProperties ///
//////////////////////

char IItemProperties::ms_buffer[BUF_SIZE];

IItemProperties::IItemProperties()
	: m_data(0)
	, m_count(0)
	, m_upgrade(0)
	, m_element(ELE_NONE)
	, m_eleUpgrade(0)
{
}

IItemProperties::IItemProperties(const IItemData *_data,
								 s32 _count,
								 s16 _upgrade,
								 E_ELEMENT _element,
								 s16 _eleUpgrade,
								 const ISpecialOption &_spc)
	: m_data(_data)
	, m_count(_count)
	, m_upgrade(_upgrade)
	, m_element(_element)
	, m_eleUpgrade(_eleUpgrade)
	, m_spc(_spc)
{
}

const char *IItemProperties::getTypeName() const
{
	return typeid(*this).name();
}

const IItemData *IItemProperties::getData() const
{
	return m_data;
}

s32 IItemProperties::getCount() const
{
	return m_count;
}

s32 IItemProperties::getMissingCountToMaximum() const
{
	FDASSERT(m_data);

	return (m_data->getStackSize() - m_count);
}

s16 IItemProperties::getUpgrade() const
{
	return m_upgrade;
}

E_ELEMENT IItemProperties::getElement() const
{
	return m_element;
}

s16 IItemProperties::getElementalUpgrade() const
{
	return m_eleUpgrade;
}

u32 IItemProperties::getSlotCount() const
{
	return m_slots.size();
}

const IItemData *IItemProperties::getSlot(u32 _num) const
{
	FDASSERT(_num < m_slots.size());

	return m_slots[_num];
}

ID IItemProperties::getSlotItemId(u32 _num) const
{
	return ((_num < m_slots.size()) ? ((m_slots[_num] != 0) ? m_slots[_num]->getId() : 0) : 0);
}

const CArray<const IItemData*> &IItemProperties::getSlots() const
{
	return m_slots;
}

ISpecialOption &IItemProperties::getSpecialOption()
{
	return m_spc;
}

const ISpecialOption &IItemProperties::getSpecialOption() const
{
	return m_spc;
}

const char *IItemProperties::getFullName() const
{
	FDASSERT(m_data);

	if (m_upgrade > 0)
	{
		if (m_spc.getStatId())
		{
			sprintf(ms_buffer, "Statted %s+%d", m_data->getName(), m_upgrade); //... RandomOption name
		}
		else
		{
			sprintf(ms_buffer, "%s+%d", m_data->getName(), m_upgrade);
		}

		return ms_buffer;
	}
	else
	{
		return m_data->getName();
	}
}

PENYA IItemProperties::getTotalCost() const
{
	FDASSERT(m_data);

	static const f32 TS_UPGRADE_COST_FACTOR[] =
	{
		1.000000f, //+0
		1.155555f, //+1
		1.322216f, //+2
		1.600000f, //+3
		1.988888f, //+4
		2.488888f, //+5
		3.100000f, //+6
		3.822216f, //+7
		4.655555f, //+8
		5.600000f, //+9
		6.655555f //+10
	};

	return static_cast<PENYA>((m_data->getCost() * m_count) *
		TS_UPGRADE_COST_FACTOR[Limit<s16>(m_upgrade, 0, 10)]);
}

bool IItemProperties::isValid() const
{
	return (
		m_data &&
		m_count);
}

bool IItemProperties::isFull() const
{
	FDASSERT(m_data);

	return (m_count >= m_data->getStackSize());
}

bool IItemProperties::isEmpty() const
{
	return m_count == 0;
}

bool IItemProperties::isEqual(const IItemProperties &_item) const
{
	FDASSERT(m_data);

	return (m_data->getId() == _item.getData()->getId());
}

bool IItemProperties::isPenya() const
{
	FDASSERT(m_data);

	return m_data->getId() >= 12 && m_data->getId() <= 15;
}

void IItemProperties::setData(const IItemData *_data)
{
	m_data = _data;
}

void IItemProperties::setCount(s32 _count)
{
	FDASSERT(_count >= 0);

	m_count = _count;
}

void IItemProperties::setUpgrade(s16 _upgrade)
{
	FDASSERT(_upgrade >= 0);

	m_upgrade = _upgrade;
}

void IItemProperties::setElement(E_ELEMENT _element)
{
	FDASSERT(_element >= ELE_NONE && _element <= ELE_EARTH);

	m_element = _element;
}

void IItemProperties::setElementalUpgrade(s16 _eleUpgrade)
{
	FDASSERT(_eleUpgrade >= 0);

	m_eleUpgrade = _eleUpgrade;
}

void IItemProperties::setSlots(const CArray<const IItemData*> &_slots)
{
	m_slots = _slots;
}

void IItemProperties::setSpecialOption(const ISpecialOption &_awake)
{
	m_spc = _awake;
}

void IItemProperties::addCount(s32 _count)
{
	m_count += _count;

	FDASSERT(m_data);

#ifdef SDEBUG
	if (!(m_count >= 0 && m_count <= m_data->getStackSize()))
	{
		debug_error("IItemProperties::addCount(s32 _count = %d) -> name: %s, m_count: %d",
			_count, getFullName(), m_count);
	}
#endif
}

void IItemProperties::addSlot(const IItemData *_item)
{
	FDASSERT(_item);

	m_slots.push_back(_item);
}

void IItemProperties::removeSlot(u32 _num)
{
	FDASSERT(_num < m_slots.size());

	m_slots.erase(_num);
}

void IItemProperties::clearSlots()
{
	m_slots.clear();
}

void IItemProperties::clear()
{
	m_data = 0;
	m_count = 0;
	m_upgrade = 0;
	m_element = ELE_NONE;
	m_eleUpgrade = 0;
}


/// ItemPack ///
////////////////

IItemPack::IItemPack(IItemPackManager *_manager)
	: IDatabaseObject((IDatabaseManager*)_manager)
	, m_id(0)
	, m_type(TYPE_NONE)
	, m_place(0)
{
}

IItemPack::~IItemPack()
{
#ifdef SDEBUG
	Log::write(LOG_DEBUG, "IItemPack dtor %d", m_id);
#endif
}

void IItemPack::reset()
{
	m_id = 0;
	m_type = TYPE_NONE;
	m_place = 0;

	m_data = 0;
	m_count = 0;
	m_upgrade = 0;
	m_element = ELE_NONE;
	m_eleUpgrade = 0;
	m_slots.clear();

	m_spc.reset();

	solve();
}

void IItemPack::solve()
{
}

ID IItemPack::getId() const
{
	return m_id;
}

IItemPack::E_TYPE IItemPack::getType() const
{
	return m_type;
}

s32 IItemPack::getPlace() const
{
	return m_place;
}

void IItemPack::setId(ID _id)
{
	m_id = _id;
}

void IItemPack::setType(E_TYPE _type)
{
	FDASSERT(_type == type(_type));

	m_type = _type;
}

void IItemPack::setPlace(s32 _place)
{
	m_place = Limit(_place, 0, getMaxPlace());
}

s32 IItemPack::getMaxPlace() const
{
	return maxPlace(m_type);
}

const IItemProperties &IItemPack::toProperties() const
{
	return *this;
}

IItemPack::E_TYPE IItemPack::type(s32 _typeId)
{
	return E_TYPE(Limit<s32>(_typeId, TYPE_NONE, COUNT_OF_TYPES - 1));
}

s32 IItemPack::maxPlace(E_TYPE _type)
{
	FDASSERT(_type == type(_type));

	//the maximum place counts
	static const s32 TS_NUM_PLACES[] =
	{
		1,     //TYPE_NONE = 0
		6 * 7 + 31, //TYPE_INVENTORY
		6,     //TYPE_BAG
		20,    //TYPE_BANK
		20,    //TYPE_GUILD_BANK
		1,     //TYPE_POST
		1      //TYPE_DROP
	};

	//return the number of the last place
	return TS_NUM_PLACES[_type] - 1;
}
