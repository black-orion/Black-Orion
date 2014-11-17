#ifndef INVENTORY_H
#define INVENTORY_H


#include "WorldMain.h"
#include "../shared/E_CHAR.h"
#include "../shared/ItemPack.h"


class IPlayerObject;
class IWorld;
class IWorldSettings;


class IItemSlot
{
public:

	IItemSlot();

	ID getId() const;

	const ItemPackPtr &getItem() const;

	void setId(ID _id);

	void setItem(const ItemPackPtr &_item);

	bool isEmpty() const;

private:

	ID m_id;

	ItemPackPtr m_item;

};


class IInventory
{
public:

	IInventory(IPlayerObject *_owner);

	IPlayerObject *getOwner();

	u32 getSlotCount() const;

	s32 getCurrentItemCount() const;

	bool isSlot(u32 _pos) const;

	bool isSlotId(ID _id) const;

	IItemSlot &getSlot(u32 _pos);

	const IItemSlot &getSlot(u32 _pos) const;

	void removeItem(u32 _pos);

	void removeItemById(ID _id);

	bool getSlotById(IItemSlot **_slot, ID _id, u32 *_out_pos = 0);

	IItemSlot &getEquipment(u32 _part);

	const IItemSlot &getEquipment(u32 _part) const;

	bool getFreeSlot(u32 &_out_slot);

	const ItemPackPtr &getItem(ID _id) const;

	bool isRoomFor(const IItemProperties &_item) const;

	bool moveItem(u32 _from, u32 _to);

	bool addItem(const IItemProperties &_item);

	bool addItem(const ItemPackPtr &_item);

	bool shiftItem(IItemProperties &_item);

	bool dropItem(ID _slotId, s32 _count);

	bool deleteItemById(ID _slotId, s32 _count, IItemProperties *_takenItem = 0);

	bool deleteItem(u32 _pos, s32 _count, IItemProperties *_takenItem = 0);

	bool sellItem(ID _slotId, s32 _count);

	bool equip(u32 _place);

	bool unequip(ID _slotId);

	bool useItem(ID _slotId);

	bool useSpecialOptionScroll(ID _scrollId, ID _targetId);

	bool awaken(u32 _pos);

	bool cancelAwakening(u32 _pos);

	bool blessingOfGoddess(u32 _pos);

	bool upgrade(ID _materialId, ID _targetId);

	bool upgrade_Sun(u32 _material, u32 _target);

	bool upgrade_Moon(u32 _material, u32 _target);

	bool upgrade_Ultimate(u32 _material, u32 _target);

	bool spawnItemPet(u32 _slotPos);

	bool spawnStatPet(u32 _slotPos);

private:

	IPlayerObject *m_owner;

	IItemSlot m_slots[INV_TOTAL_ITEMS];

	enum
	{
		BUF_SIZE = 2048
	};

	static char ms_buffer[BUF_SIZE];

	IItemPackManager *_getItemPackMngr();

	IWorld *_getWorld();

	const IWorldSettings *_getSettings();

	void _swapItems(IItemSlot &_first, u32 _place1, IItemSlot &_second, u32 _place2);

	void _send(const CByteArray &_bytes);

};


#endif //INVENTORY_H
