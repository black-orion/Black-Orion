#ifndef ITEMPACK_H
#define ITEMPACK_H


#include "Base.h"
#include "E_ELEMENT.h"
#include "DatabaseObject.h"
#include "SpecialOption.h"


class IItemData;
class IItemPackManager;


/// ItemProperties ///
//////////////////////

class IItemProperties
{
public:

	enum
	{
		UPGRADE_MAX = 0x7fff,
		UPGRADE_ELE_MAX = 0x7fff,

		COUNT_MAX = 99999,

		SLOT_COUNT_MAX = 10
	};

	IItemProperties();

	IItemProperties(const IItemData *_data, s32 _count = 1, s16 _upgrade = 0, E_ELEMENT _element = ELE_NONE,
		s16 _eleUpgrade = 0, const ISpecialOption &_spc = ISpecialOption());

	const char *getTypeName() const;

	const IItemData *getData() const;

	s32 getCount() const;

	s32 getMissingCountToMaximum() const;

	s16 getUpgrade() const;

	E_ELEMENT getElement() const;

	s16 getElementalUpgrade() const;

	u32 getSlotCount() const;

	const IItemData *getSlot(u32 _num) const;

	ID getSlotItemId(u32 _num) const;

	const CArray<const IItemData*> &getSlots() const;

	ISpecialOption &getSpecialOption();

	const ISpecialOption &getSpecialOption() const;

	const char *getFullName() const;

	PENYA getTotalCost() const;

	bool isValid() const;

	bool isFull() const;

	bool isEmpty() const;

	bool isEqual(const IItemProperties &_item) const;

	bool isPenya() const;

	void setData(const IItemData *_data);

	void setCount(s32 _count);

	void setUpgrade(s16 _upgrade);

	void setElement(E_ELEMENT _element);

	void setElementalUpgrade(s16 _eleUpgrade);

	void setSlots(const CArray<const IItemData*> &_slots);

	void setSpecialOption(const ISpecialOption &_awake);

	void addCount(s32 _count);

	void addSlot(const IItemData *_item);

	void removeSlot(u32 _num);

	void clearSlots();

	void clear();

protected:

	enum
	{
		BUF_SIZE = 256
	};

	static char ms_buffer[BUF_SIZE];

	const IItemData *m_data;

	s32 m_count;

	s16 m_upgrade;

	E_ELEMENT m_element;

	s16 m_eleUpgrade;

	CArray<const IItemData *> m_slots;

	ISpecialOption m_spc;

};


/// ItemPack ///
////////////////

//Eigenschaften (r = lesen, w = schreiben)

//                  Login   Char    World
//----------------------------------------
//	Id                -      (r)     (r)
//  Type              -      (r)     (r/w)
//  Owner             -      (r)     (r/w)
//  Data              -      (r)     (r/w)
//  Count             -       -      (r/w)
//  Upgrade           -       -      (r/w)
//  Element           -       -      (r/w)
//  EleUpgrade        -       -      (r/w)
//  Slots             -       -      (r/w)
//----------------------------------------
// SELECT                     x       x
// UPDATE                             x
// INSERT                     x       x
// DELETE                     x       x


class IItemPack : public IDatabaseObject, public IItemProperties
{
public:

	enum E_TYPE //Type ids must not be changed because of database compatibility
	{
		TYPE_NONE = 0,
		TYPE_INVENTORY = 1,
		TYPE_BAG = 2,
		TYPE_BANK = 3,
		TYPE_GUILD_BANK = 4,
		TYPE_POST = 5,

		COUNT_OF_TYPES
	};

	IItemPack(IItemPackManager *_manager);

	~IItemPack();

	void reset();

	void solve();

	ID getId() const;

	E_TYPE getType() const;

	s32 getPlace() const;

	void setId(ID _id);

	void setType(E_TYPE _type);

	void setPlace(s32 _place);

	static E_TYPE type(s32 _typeId);

	s32 getMaxPlace() const;

	const IItemProperties &toProperties() const;

	static s32 maxPlace(E_TYPE _type);

private:

	friend class IItemPackManager;

	ID m_id;

	E_TYPE m_type;

	s32 m_place;

};


#endif //ITEMPACK_H
