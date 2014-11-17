#include "Inventory.h"
#include "PlayerObject.h"
#include "DropObject.h"
#include "../shared/PacketCreator.h"
#include "../shared/ItemData.h"
#include "../shared/ItemSet.h"
#include "../shared/RandomOption.h"
#include "../shared/ItemPack.h"
#include "../shared/ItemPackManager.h"
#include "../shared/Log.h"
#include "../world/WorldPlayer.h"
#include "../world/World.h"
#include "../world/WorldServer.h"


//// IItemSlot ////
///////////////////

IItemSlot::IItemSlot()
	: m_id(0)
{
}

ID IItemSlot::getId() const
{
	return m_id;
}

const ItemPackPtr &IItemSlot::getItem() const
{
	return m_item;
}

void IItemSlot::setId(ID _id)
{
	m_id = _id;
}

void IItemSlot::setItem(const ItemPackPtr &_item)
{
	m_item = _item;

	if (m_item &&
		m_item->getPlace() >= INV_EQUIPS_INDEX)
	{
		m_id = m_item->getPlace();
	}
}

bool IItemSlot::isEmpty() const
{
	return (m_item == 0);
}


//// IInventory ////
////////////////////

char IInventory::ms_buffer[BUF_SIZE];

IInventory::IInventory(IPlayerObject *_owner)
	: m_owner(_owner)
{
	for (s32 i = 0; i < INV_TOTAL_ITEMS; ++i)
	{
		m_slots[i].setId(i);
	}
}

IPlayerObject *IInventory::getOwner()
{
	return m_owner;
}

u32 IInventory::getSlotCount() const
{
	return INV_TOTAL_ITEMS;
}

s32 IInventory::getCurrentItemCount() const
{
	s32 r_count = 0;

	for (u32 i = 0; i < getSlotCount(); ++i)
	{
		if (m_slots[i].getItem())
		{
			++r_count;
		}
	}

	return r_count;
}

bool IInventory::isSlot(u32 _pos) const
{
	return (_pos < getSlotCount());
}

bool IInventory::isSlotId(ID _id) const
{
	for (u32 i = 0; i < getSlotCount(); ++i)
	{
		if (m_slots[i].getId() == _id)
		{
			return true;
		}
	}

	return false;
}

IItemSlot &IInventory::getSlot(u32 _pos)
{
	FDASSERT(_pos < getSlotCount());

	return m_slots[_pos];
}

const IItemSlot &IInventory::getSlot(u32 _pos) const
{
	FDASSERT(_pos < getSlotCount());

	return m_slots[_pos];
}

void IInventory::removeItem(u32 _pos)
{
	if (isSlot(_pos))
	{
		_send(IPacketCreator::updateItem(m_owner, _pos, IPacketCreator::ITM_UPDATE_COUNT, 0));

		getSlot(_pos).setItem(0);
	}
}

void IInventory::removeItemById(ID _id)
{
	IItemSlot *t_slot = 0;
	u32 t_pos = 0;

	if (getSlotById(&t_slot, _id, &t_pos))
	{
		_send(IPacketCreator::updateItem(m_owner, t_pos, IPacketCreator::ITM_UPDATE_COUNT, 0));

		t_slot->setItem(0);
	}
}

bool IInventory::getSlotById(IItemSlot **_slot, ID _id, u32 *_out_pos)
{
	FDASSERT(_slot);

	for (u32 i = 0; i < getSlotCount(); ++i)
	{
		if (m_slots[i].getId() == _id)
		{
			*_slot = &m_slots[i];
			if (_out_pos)
			{
				*_out_pos = i;
			}
			return true;
		}
	}

	return false;
}

IItemSlot &IInventory::getEquipment(u32 _part)
{
	FDASSERT(_part + INV_EQUIPS_INDEX < getSlotCount());

	return getSlot(_part + INV_EQUIPS_INDEX);
}

const IItemSlot &IInventory::getEquipment(u32 _part) const
{
	FDASSERT(_part + INV_EQUIPS_INDEX < getSlotCount());

	return getSlot(_part + INV_EQUIPS_INDEX);
}

bool IInventory::getFreeSlot(u32 &_out_slot)
{
	for (u32 i = 0; i < INV_PLACES; ++i)
	{
		if (m_slots[i].isEmpty())
		{
			_out_slot = i;
			return true;
		}
	}

	return false;
}

const ItemPackPtr &IInventory::getItem(ID _id) const
{
	for (u32 i = 0; i < getSlotCount(); ++i)
	{
		if (m_slots[i].getId() == _id)
		{
			return m_slots[i].getItem();
		}
	}

	return m_slots[0].getItem();
}

bool IInventory::isRoomFor(const IItemProperties &_item) const
{
	FDASSERT(_item.isValid());

	s32 t_restCount = _item.getCount();

	for (u32 i = 0; (i < INV_PLACES) && (t_restCount > 0); ++i)
	{
		if (m_slots[i].getItem())
		{
			if (m_slots[i].getItem()->isEqual(_item) &&
				!m_slots[i].getItem()->isFull())
			{
				t_restCount -= m_slots[i].getItem()->getMissingCountToMaximum();
			}
		}
		else
		{
			t_restCount -= _item.getData()->getStackSize();
		}
	}

	return (t_restCount <= 0);
}

bool IInventory::moveItem(u32 _from, u32 _to)
{
	if (_from != _to &&
		_from < INV_PLACES &&
		_to < INV_PLACES)
	{
		IItemSlot &t_from = getSlot(_from);
		IItemSlot &t_to = getSlot(_to);

		if (!t_from.isEmpty())
		{
			//same item type
			if (t_to.getItem() &&
				t_from.getItem()->isEqual(*t_to.getItem()))
			{
				s32 t_tempCount = Limit<s32>(t_from.getItem()->getCount(), 0,
					t_to.getItem()->getMissingCountToMaximum());

				deleteItem(_from, t_tempCount);
				t_to.getItem()->addCount(t_tempCount);

				_send(IPacketCreator::moveItem(m_owner, _to, _from));
				return true;
			}

			//other type -> just swap
			else
			{
				_swapItems(t_from, _from, t_to, _to);

				_send(IPacketCreator::moveItem(m_owner, _from, _to));
				return true;
			}
		}
	}

	return false;
}

bool IInventory::addItem(const IItemProperties &_item)
{
	FDASSERT(_item.isValid());

	IItemProperties t_tempItem = _item;

	if (shiftItem(t_tempItem))
	{
		return true;
	}

	s32 t_restCount = t_tempItem.getCount();
	u32 t_tempSlot = 0;

	while (t_restCount > 0)
	{
		t_tempItem.setCount(Limit(t_restCount, 1, _item.getData()->getStackSize()));

		if (getFreeSlot(t_tempSlot))
		{
			getSlot(t_tempSlot).setItem(
				_getItemPackMngr()->createItemPack_W(
				m_owner->getCharacter(),
				IItemPack::TYPE_INVENTORY,
				t_tempSlot,
				t_tempItem));

			t_restCount -= t_tempItem.getCount();

			if (getSlot(t_tempSlot).getItem())
			{
				_send(IPacketCreator::addItem(m_owner, t_tempSlot));
			}
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool IInventory::addItem(const ItemPackPtr &_item)
{
	FDASSERT(_item);

	if (shiftItem(*_item))
	{
		m_owner->getWorld()->getServer()->getItemPackManager()->removeItemPack_W(_item);
	}
	else
	{
		u32 t_slot = 0;

		if (getFreeSlot(t_slot))
		{
			_item->setPlace(t_slot);

			getSlot(t_slot).setItem(_item);

			_send(IPacketCreator::addItem(m_owner, t_slot));
			return true;
		}
	}

	return false;
}

bool IInventory::shiftItem(IItemProperties &_item)
{
	FDASSERT(_item.isValid());

	s32 t_tempCount = 0;

	for (u32 i = 0; (i < INV_PLACES) && (!_item.isEmpty()); ++i)
	{
		const ItemPackPtr &t_item = getSlot(i).getItem();

		if (t_item &&
			t_item->isEqual(_item) &&
			!t_item->isFull())
		{
			t_tempCount = Limit(_item.getCount(), 1, t_item->getMissingCountToMaximum());

			t_item->addCount(t_tempCount);

			_send(IPacketCreator::updateItem(m_owner, i, IPacketCreator::ITM_UPDATE_COUNT, t_item->getCount()));

			_item.addCount( - t_tempCount);
		}
	}

	return _item.isEmpty();
}

bool IInventory::dropItem(ID _slotId, s32 _count)
{
	//spawn the drop
	IItemProperties t_item;

	if (!deleteItemById(_slotId, _count, &t_item))
	{
		return false;
	}

	return (_getWorld()->createDropObject(
		t_item, CPoint::randomPosition(m_owner->getPosition(), WORLD_ITEM_DROP_RANGE)) != 0);
}

bool IInventory::deleteItemById(ID _slotId, s32 _count, IItemProperties *_takenItem)
{
	FDASSERT(_count > 0);

	IItemSlot *t_slot;
	u32 t_pos = 0;
	if (!getSlotById(&t_slot, _slotId, &t_pos))
	{
		return false;
	}

	return deleteItem(t_pos, _count, _takenItem);
}

bool IInventory::deleteItem(u32 _pos, s32 _count, IItemProperties *_takenItem)
{
	if (!isSlot(_pos))
	{
		return false;
	}

	IItemSlot &t_slot = getSlot(_pos);

	//check if the item exists and the count is valid
	if (!t_slot.getItem() ||
		_count < 1)
	{
		return false;
	}

	if (_count > t_slot.getItem()->getCount())
	{
		_count = t_slot.getItem()->getCount();
	}

	//decrease the count
	t_slot.getItem()->addCount( - _count);

	//update the taken item
	if (_takenItem)
	{
		*_takenItem = *t_slot.getItem();
		_takenItem->setCount(_count);
	}

	//update the client
	_send(IPacketCreator::updateItem(m_owner,
		_pos, IPacketCreator::ITM_UPDATE_COUNT, t_slot.getItem()->getCount()));

	//remove the item pack is empty
	if (t_slot.getItem()->isEmpty())
	{
		_getItemPackMngr()->removeItemPack_W(t_slot.getItem());

		t_slot.setItem(0);
	}

	return true;
}

bool IInventory::sellItem(ID _slotId, s32 _count)
{
	static IItemProperties t_item;

	if (!deleteItemById(_slotId, _count, &t_item))
	{
		return false;
	}

	PENYA t_penya = t_item.getTotalCost() / 4;

	m_owner->changePenya(m_owner->getCharacter()->getPenya() + t_penya);

	return true;
}

bool IInventory::equip(u32 _place)
{
	FDASSERT(isSlot(_place));

	IItemSlot &t_slot = getSlot(_place);

	FDASSERT(t_slot.getItem());

#ifdef SDEBUG
	printf("Equipping place %u %s\n", _place, t_slot.getItem()->getFullName());
#endif

	//Level
	if (m_owner->getCharacter()->getLevel() < t_slot.getItem()->getData()->getLevel())
	{
		_send(IPacketCreator::gameInfo(m_owner, TID_GAME_REQLEVEL,
			itostr(Limit(t_slot.getItem()->getData()->getLevel(), 0, 255))));
		return false;
	}

	//Job
	if (!isCompatibleJob(t_slot.getItem()->getData()->getJob(), m_owner->getCharacter()->getJob()))
	{
		sprintf(ms_buffer, "\"%s\"", t_slot.getItem()->getData()->getName());
		_send(IPacketCreator::gameInfo(m_owner, TID_GAME_WRONGJOB, ms_buffer));
		return false;
	}

	//Sex
	if (!isCompatibleSex(t_slot.getItem()->getData()->getSex(), m_owner->getCharacter()->getSex()))
	{
		sprintf(ms_buffer, "\"%s\"", t_slot.getItem()->getData()->getName());
		_send(IPacketCreator::gameInfo(m_owner, TID_GAME_WRONGSEX, ms_buffer));
		return false;
	}

	//where to put the new equip
	u32 t_equipPos = 0;

	switch (t_slot.getItem()->getData()->getItemKind3())
	{
	case IItemData::IK3_AXE:
	case IItemData::IK3_SWD:
	case IItemData::IK3_BOW:
	case IItemData::IK3_YOYO:
	case IItemData::IK3_CHEERSTICK:
	case IItemData::IK3_STAFF:
	case IItemData::IK3_WAND:
	case IItemData::IK3_KNUCKLEHAMMER:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_RWEAPON;
			break;
		}

	case IItemData::IK3_SHIELD:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_SHIELD;
			break;
		}

	case IItemData::IK3_HELMET:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_CAP;
			break;
		}

	case IItemData::IK3_SUIT:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_UPPER_BODY;
			break;
		}

	case IItemData::IK3_GAUNTLET:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_HAND;
			break;
		}

	case IItemData::IK3_BOOTS:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_FOOT;
			break;
		}

	case IItemData::IK3_HAT:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_HAT;
			break;
		}

	case IItemData::IK3_CLOTH:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_CLOTH;
			break;
		}

	case IItemData::IK3_GLOVE:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_GLOVE;
			break;
		}

	case IItemData::IK3_SHOES:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_BOOTS;
			break;
		}

	case IItemData::IK3_CLOAK:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_CLOAK;
			break;
		}

	case IItemData::IK3_MASK:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_MASK;
			break;
		}

	case IItemData::IK3_RING:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_RING1;
			if (getSlot(t_equipPos).getItem())
			{
				t_equipPos = INV_EQUIPS_INDEX + PARTS_RING2;
			}
			break;
		}

	case IItemData::IK3_EARRING:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_EARRING1;
			if (getSlot(t_equipPos).getItem())
			{
				t_equipPos = INV_EQUIPS_INDEX + PARTS_EARRING2;
			}
			break;
		}

	case IItemData::IK3_NECKLACE:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_NECKLACE1;
			break;
		}

	case IItemData::IK3_ARROW:
	//case IItemData::IK3_BCHARM:
		{
			if (getSlot(INV_EQUIPS_INDEX + PARTS_RWEAPON).getItem() &&
				getSlot(INV_EQUIPS_INDEX + PARTS_RWEAPON).getItem()->getData()->getItemKind3() ==
				IItemData::IK3_BOW)
			{
				t_equipPos = INV_EQUIPS_INDEX + PARTS_BULLET;
			}
			else
			{
				return false;
			}
			break;
		}

	case IItemData::IK3_BOARD:
	case IItemData::IK3_STICK:
		{
			t_equipPos = INV_EQUIPS_INDEX + PARTS_RIDE;
			break;
		}

	default:
		{
			Log::write(LOG_DEBUG, "Unknown ik3\n");
			return false;
		}
	};

	IItemSlot &t_equipSlot = getSlot(t_equipPos);

	//need to unequip
	if (t_equipSlot.getItem())
	{
		u32 t_freePos = 0;
		if (!getFreeSlot(t_freePos))
		{
			_send(IPacketCreator::gameInfo(m_owner, TID_GAME_LACKSPACE));
			return false;
		}

		IItemSlot &t_freeSlot = getSlot(t_freePos);

		sdk::swap(t_equipSlot, t_freeSlot);

		FDASSERT(t_freeSlot.getItem());

		t_freeSlot.getItem()->setPlace(t_freePos);
	}

#ifdef SDEBUG
	printf("t_equipSlot.getId(): %d\n", t_equipSlot.getId());
	printf("t_slot.getId(): %d\n", t_slot.getId());
#endif

	m_owner->sendToLocalArea(IPacketCreator::moveEquip(m_owner, t_slot, t_equipPos, true));

	sdk::swap(t_equipSlot, t_slot);
	t_equipSlot.getItem()->setPlace(t_equipPos);

	m_owner->onStatRelatedChanged();

	return true;
}

bool IInventory::unequip(ID _slotId)
{
	IItemSlot *t_slot = 0;
	u32 t_slotPlace = 0;

	if (!getSlotById(&t_slot, _slotId, &t_slotPlace) ||
		t_slotPlace < INV_EQUIPS_INDEX ||
		!t_slot->getItem())
	{
		printf("invalid unequip slot id %d\n", _slotId);
		return false;
	}

	if (isRoomFor(*t_slot->getItem()))
	{
		u32 t_newSlotPlace = 0;
		getFreeSlot(t_newSlotPlace);

		m_owner->sendToLocalArea(IPacketCreator::moveEquip(m_owner, *t_slot, t_newSlotPlace, false));

		IItemSlot &t_newSlot = getSlot(t_newSlotPlace);

		sdk::swap(*t_slot, t_newSlot);

		t_newSlot.getItem()->setPlace(t_newSlotPlace);

		m_owner->onStatRelatedChanged();
	}
	else
	{
		_send(IPacketCreator::gameInfo(m_owner, TID_GAME_LACKSPACE));
		return false;
	}

	return true;
}

bool IInventory::useItem(ID _slotId)
{
	IItemSlot *t_slot = 0;
	u32 t_slotPos = 0;

	if (!getSlotById(&t_slot, _slotId, &t_slotPos))
	{
		Log::write(LOG_ERROR, "Invalid slot id: %d", _slotId);
		return false;
	}

	if (t_slotPos >= INV_EQUIPS_INDEX)
	{
		Log::write(LOG_ERROR, "Invalid slot pos: %u", t_slotPos);
		return false;
	}

	const ItemPackPtr &t_item = t_slot->getItem();

	if (!t_item ||
		!t_item->isValid())
	{
		Log::write(LOG_ERROR, "Slot is empty: id %d", _slotId);
		return false;
	}

	switch (t_item->getData()->getItemKind1())
	{
		//Equipment (Weapons, Armor, CS)
	case IItemData::IK1_ARMOR:
	case IItemData::IK1_WEAPON:
		{
			return equip(t_slotPos);
		}

	case IItemData::IK1_GENERAL:
		{
			switch (t_item->getData()->getItemKind2())
			{
				//Equipment (Jewelry, Arrows, Posters)
			case IItemData::IK2_JEWELRY:
			case IItemData::IK2_CHARM:
			case IItemData::IK2_BULLET:
				{
					return equip(t_slotPos);
				}

			case IItemData::IK2_GENERAL:
				{
					switch (t_item->getData()->getItemKind3())
					{
					case IItemData::IK3_PET:
						{
							return spawnItemPet(t_slotPos);
						}

					case IItemData::IK3_EGG:
						{
							return spawnStatPet(t_slotPos);
						}
					}
				}
			}
			break;
		}

	case IItemData::IK1_SYSTEM:
		{
			switch (t_item->getData()->getItemKind2())
			{
			case IItemData::IK2_SYSTEM:
				{
					switch (t_item->getData()->getItemKind3())
					{
					case IItemData::IK3_SCROLL: //Scrolls
						{
							switch (t_item->getData()->getId())
							{
							case II_SYS_SYS_SCR_PERIN: //Perin
								{
									if (m_owner->getCharacter()->getPenya() <
										MAX_PENYA - t_item->getData()->getCost())
									{
										m_owner->changePenya(
											m_owner->getCharacter()->getPenya() + t_item->getData()->getCost());

										deleteItem(t_slotPos, 1);
										return true;
									}
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
			break;
		}
	}

	return false;
}

bool IInventory::useSpecialOptionScroll(ID _scrollId, ID _targetId)
{
	IItemSlot *t_scrollSlot = 0;
	IItemSlot *t_targetSlot = 0;
	u32 t_scrollPos = 0;
	u32 t_targetPos = 0;

	if (!getSlotById(&t_scrollSlot, _scrollId, &t_scrollPos) ||
		!getSlotById(&t_targetSlot, _targetId, &t_targetPos))
	{
		Log::write(LOG_ERROR, "Invalid spc opt slot %d -> %d\n", _scrollId, _targetId);
		return false;
	}

	if (t_scrollSlot->isEmpty() ||
		t_targetSlot->isEmpty())
	{
		Log::write(LOG_ERROR, "Empty spc opt slot %d -> %d\n", _scrollId, _targetId);
		return false;
	}

	const ItemPackPtr &t_scroll = t_scrollSlot->getItem();
	const ItemPackPtr &t_target = t_targetSlot->getItem();

	FDASSERT(t_scroll->isValid());
	FDASSERT(t_target->isValid());

	switch (t_scroll->getData()->getId())
	{
	case II_SYS_SYS_SCR_AWAKE: //Scroll of Awakening
		{
#ifdef SDEBUG
			Log::write(LOG_DEBUG, "Using Scroll of Awakening");
#endif

			if (t_target->getSpecialOption().isNull() &&
				t_target->getData()->canBeAwakened())
			{
				deleteItem(t_scrollPos, 1);
				return awaken(t_targetPos);
			}
			break;
		}

	case II_SYS_SYS_SCR_AWAKECANCEL: //Scroll of Reversion
		{
#ifdef SDEBUG
			Log::write(LOG_DEBUG, "Using Scroll of Reversion");
#endif

			if (!t_target->getSpecialOption().isNull() &&
				t_target->getData()->canBeAwakened())
			{
				deleteItem(t_scrollPos, 1);
				return cancelAwakening(t_targetPos);
			}
			break;
		}

	case II_SYS_SYS_SCR_BLESSEDNESS: //Blessing of Goddess
		{
#ifdef SDEBUG
			Log::write(LOG_DEBUG, "Using Blessing of Goddess");
#endif

			if (t_target->getSpecialOption().isNull() &&
				t_target->getData()->canBeBlessed())
			{
				deleteItem(t_scrollPos, 1);
				return blessingOfGoddess(t_targetPos);
			}
			break;
		}

	case II_SYS_SYS_SCR_LEVELDOWN01: //Scroll of Reduction B
		{
#ifdef SDEBUG
			Log::write(LOG_DEBUG, "Using Scroll of Reduction B");
#endif
			break;
		}

	case II_SYS_SYS_SCR_LEVELDOWN02: //Scroll of Reduction A
		{
#ifdef SDEBUG
			Log::write(LOG_DEBUG, "Using Scroll of Reduction A");
#endif
			break;
		}

	default:
		{
			Log::write(LOG_DEBUG, "Unknown spc opt scroll %d", t_scroll->getData()->getId());
		}
	}

	return false;
}

bool IInventory::awaken(u32 _pos)
{
	FDASSERT(isSlot(_pos));

	IItemSlot &t_slot = getSlot(_pos);

	FDASSERT(t_slot.getItem());

	ISpecialOption &t_spc = t_slot.getItem()->getSpecialOption();

	t_spc.setEffect(0, IStatEffect(E_STAT(DST_STR + random(0, 3)), random(1, 75)));

	if (eventf(0.333333f))
	{
		if (eventf(0.5f))
		{
			t_spc.setEffect(1, IStatEffect(E_STAT(DST_STR + random(0, 3)), random(1, 75)));
		}
		else
		{
			t_spc.setEffect(1, IStatEffect(E_STAT(DST_STR + random(0, 3)), random(1, 75)));
			t_spc.setEffect(2, IStatEffect(E_STAT(DST_STR + random(0, 3)), random(1, 75)));
		}
	}

	_send(IPacketCreator::updateSpcOption(m_owner, _pos));
	return true;
}

bool IInventory::cancelAwakening(u32 _pos)
{
	FDASSERT(isSlot(_pos));

	IItemSlot &t_slot = getSlot(_pos);

	FDASSERT(t_slot.getItem());

	t_slot.getItem()->getSpecialOption().clearAwakening();

	_send(IPacketCreator::updateSpcOption(m_owner, _pos));
	return true;
}

bool IInventory::blessingOfGoddess(u32 _pos)
{
	FDASSERT(isSlot(_pos));

	IItemSlot &t_slot = getSlot(_pos);

	FDASSERT(t_slot.getItem());

	//...
	t_slot.getItem()->getSpecialOption().setEffect(0, IStatEffect(DST_STA, 99));

	_send(IPacketCreator::updateSpcOption(m_owner, _pos));
	return true;
}

bool IInventory::upgrade(ID _materialId, ID _targetId)
{
	IItemSlot *t_materialSlot = 0;
	IItemSlot *t_targetSlot = 0;
	u32 t_materialPos = 0;
	u32 t_targetPos = 0;

	if (!getSlotById(&t_materialSlot, _materialId, &t_materialPos) ||
		!getSlotById(&t_targetSlot, _targetId, &t_targetPos))
	{
		Log::write(LOG_ERROR, "Invalid upgrade slot %d -> %d\n", _materialId, _targetId);
		return false;
	}

	if (t_materialSlot->isEmpty() ||
		t_targetSlot->isEmpty())
	{
		Log::write(LOG_ERROR, "Empty upgrade slot %d -> %d\n", _materialId, _targetId);
		return false;
	}

	const ItemPackPtr &t_material = t_materialSlot->getItem();
	const ItemPackPtr &t_target = t_targetSlot->getItem();

	switch (t_material->getData()->getItemKind3())
	{
	case IItemData::IK3_ENCHANT: //Sunstone & Shining Orichalcum
		{
			switch (t_material->getData()->getId())
			{
			case II_GEN_MAT_ORICHALCUM01: //Sunstone
			case II_GEN_MAT_ORICHALCUM01_1: //Sunstone (Event)
				{
					if (t_target->getData()->canBeUpgraded_Sun())
					{
						return upgrade_Sun(t_materialPos, t_targetPos);
					}

					break;
				}

			case II_GEN_MAT_ORICHALCUM02: //Shining Orichalcum
				{
					if (t_target->getData()->isUltimate())
					{
						return upgrade_Ultimate(t_materialPos, t_targetPos);
					}

					break;
				}
            default:;
			}

			break;
		}

	case IItemData::IK3_PIERDICE: //Moonstone & Powerdices
		{
			switch (t_material->getData()->getId())
			{
			case II_GEN_MAT_MOONSTONE: //Moonstone
			case II_GEN_MAT_MOONSTONE_1: //Moonstone (Event)
				{
					if (t_target->getData()->canBeUpgraded_Moon())
					{
						return upgrade_Moon(t_materialPos, t_targetPos);
					}

					break;
				}
            default:;
			}

			break;
		}

	case IItemData::IK3_ELECARD: //Element card
		{
			break;
		}

	case IItemData::IK3_SOCKETCARD: //Socket card
		{
			break;
		}

    default:;
	}

	return false;
}

bool IInventory::upgrade_Sun(u32 _material, u32 _target)
{
	FDASSERT(isSlot(_material));
	FDASSERT(isSlot(_target));

	IItemSlot &t_materialSlot = getSlot(_material);
	IItemSlot &t_targetSlot = getSlot(_target);

	const ItemPackPtr &t_material = t_materialSlot.getItem();
	const ItemPackPtr &t_target = t_targetSlot.getItem();

	FDASSERT(t_material);
	FDASSERT(t_material->isValid());
	FDASSERT(t_target);
	FDASSERT(t_target->isValid());

	switch (t_target->getData()->getItemKind1())
	{
	case IItemData::IK1_WEAPON:
	case IItemData::IK1_ARMOR:
		{
			if (t_target->getUpgrade() < 10)
			{
				if (eventf(1.0f))
				{
					t_target->setUpgrade(t_target->getUpgrade() + 1);

					_send(IPacketCreator::gfxEffect(m_owner, 1714));

					_send(IPacketCreator::updateItem(
						m_owner,
						_target,
						IPacketCreator::ITM_UPDATE_UPGRADE,
						t_target->getUpgrade()));
				}
				else
				{
					_send(IPacketCreator::gfxEffect(m_owner, 1715));
				}

				return deleteItem(_material, 1);
			}

			break;
		}
    default:;
	}

	return false;
}

bool IInventory::upgrade_Moon(u32 _material, u32 _target)
{
	FDASSERT(isSlot(_material));
	FDASSERT(isSlot(_target));

	IItemSlot &t_materialSlot = getSlot(_material);
	IItemSlot &t_targetSlot = getSlot(_target);

	const ItemPackPtr &t_material = t_materialSlot.getItem();
	const ItemPackPtr &t_target = t_targetSlot.getItem();

	FDASSERT(t_material);
	FDASSERT(t_material->isValid());
	FDASSERT(t_target);
	FDASSERT(t_target->isValid());

	if (t_target->getUpgrade() < 20)
	{
		if (eventf(1.0f))
		{
			t_target->setUpgrade(t_target->getUpgrade() + 1);

			_send(IPacketCreator::gfxEffect(m_owner, 1714));

			_send(IPacketCreator::updateItem(
				m_owner,
				_target,
				IPacketCreator::ITM_UPDATE_UPGRADE,
				t_target->getUpgrade()));
		}
		else
		{
			_send(IPacketCreator::gfxEffect(m_owner, 1715));
		}

		return deleteItem(_material, 1);
	}

	return false;
}

bool IInventory::upgrade_Ultimate(u32 _material, u32 _target)
{
	printf("ultimate upgrade\n");
	return false;
}

bool IInventory::spawnItemPet(u32 _slotPos)
{
	return false;
}

bool IInventory::spawnStatPet(u32 _slotPos)
{
	return false;
}

IItemPackManager *IInventory::_getItemPackMngr()
{
	FDASSERT(m_owner);
	FDASSERT(m_owner->getWorld());
	FDASSERT(m_owner->getWorld()->getServer());
	FDASSERT(m_owner->getWorld()->getServer()->getItemPackManager());

	return m_owner->getWorld()->getServer()->getItemPackManager();
}

IWorld *IInventory::_getWorld()
{
	FDASSERT(m_owner);
	FDASSERT(m_owner->getWorld());

	return m_owner->getWorld();
}

const IWorldSettings *IInventory::_getSettings()
{
	return _getWorld()->getServer()->getSettings();
}

void IInventory::_swapItems(IItemSlot &_first, u32 _place1, IItemSlot &_second, u32 _place2)
{
	if (_first.getItem())
	{
		if (_second.getItem())
		{
			u32 t_slot = _first.getItem()->getPlace();
			_first.getItem()->setPlace(_first.getItem()->getPlace());
			_second.getItem()->setPlace(t_slot);
		}
		else
		{
			_first.getItem()->setPlace(_place2);
		}
	}
	else
	{
		if (_second.getItem())
		{
			_second.getItem()->setPlace(_place1);
		}
	}

	sdk::swap(_first, _second);
}

void IInventory::_send(const CByteArray &_bytes)
{
	FDASSERT(m_owner);
	FDASSERT(m_owner->getPlayer());
	FDASSERT(m_owner->getPlayer()->getClient());

	m_owner->getPlayer()->getClient()->send(_bytes);
}
