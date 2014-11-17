#include "ItemPackManager.h"
#include "ItemDataManager.h"
#include "ItemData.h"
#include "Character.h"
#include "Log.h"
#include "DatabaseConnection.h"
#include "../world/PlayerObject.h"
#include "../char/CharPlayer.h"


#define WORLD_FULL_SELECT_PROPERTIES \
	"id,type,place,itemid,count,upgrade,element,eleupgrade,stats,leveldown," \
	"type0,amount0,type1,amount1,type2,amount2," \
	"slot1,slot2,slot3,slot4,slot5,slot6,slot7,slot8,slot9,slot10" \


IItemPackManager::IItemPackManager(IDatabaseConnection *_dbc, IItemDataManager *_dataMngr)
	: m_dbc(_dbc)
	, m_dataMngr(_dataMngr)
{
	FDASSERT(m_dataMngr);
}

IItemPackManager::~IItemPackManager()
{
}

void IItemPackManager::clear()
{
	m_items.clear();
}

void IItemPackManager::add(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	m_items.push_back((IItemPack*)_dbObj);
}

void IItemPackManager::remove(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	FOR_EACH (m_items, i)
	{
		if (m_items[i] == _dbObj)
		{
			m_items[i].reset();
			m_items.erase_fast(i);
			return;
		}
	}

	FDASSERT(false && "Invalid _dbObj");
}

void IItemPackManager::update()
{
	FOR_EACH (m_items, i)
	{
		if (m_items[i]->isUnique())
		{
			m_items[i].reset();
			m_items.erase_fast(i);
			if (i)
				--i;
		}
	}
}

u32 IItemPackManager::getItemPackNumber() const
{
	return m_items.size();
}

void IItemPackManager::setDbc(IDatabaseConnection *_dbc)
{
	m_dbc = _dbc;
}

//:: CHAR SERVER FUNCTIONS ::

ItemPackPtr IItemPackManager::getItemPack_C(ID _id, bool _fromDatabase)
{
	FDASSERT(m_dbc);
	FDASSERT(m_dataMngr);

	FOR_EACH (m_items, i)
	{
		if (m_items[i]->getId() == _id)
			return m_items[i];
	}

	if (!_fromDatabase)
		return 0;

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,type,place,itemid FROM items WHERE id='%d';",
		_id) &&
		m_dbc->getResult(t_result))
	{
		ItemPackPtr t_itemPack = _newItemPack();

		t_itemPack->m_id = t_result.getFieldS32(0);
		t_itemPack->m_type = IItemPack::type(t_result.getFieldS32(1));
		t_itemPack->m_place = Limit(t_result.getFieldS32(2), 0, t_itemPack->getMaxPlace());

		const s32 T_dataId = t_result.getFieldS32(3);

		t_itemPack->m_data = m_dataMngr->getItemById(T_dataId);

		if (t_itemPack->m_data == 0)
		{
			Log::write(LOG_ERROR, "ItemPack (Id %d): Invalid item Id %d", t_itemPack->m_id, T_dataId);

			return 0;
		}

		return t_itemPack;
	}

	return 0;
}

bool IItemPackManager::getEquipment_C(ICharPlayer *_player, u32 _char)
{
	FDASSERT(_player);
	FDASSERT(_char <= 2);

	const CharacterPtr &t_char = _player->getAccount()->getCharacter(_char);

	FDASSERT(t_char);

	_player->getEquipment(_char).clear();

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,place,itemid FROM items WHERE owner='%d' and type='%d' and place>'%d' ORDER BY place ASC",
		t_char->getId(), IItemPack::TYPE_INVENTORY, INV_EQUIPS_INDEX - 1) &&
		m_dbc->getResult(t_result))
	{
		ID t_itemId = 0;
		const IItemData *t_data = 0;

		while (t_result.nextRow())
		{
			t_itemId = t_result.getFieldS32(2);
			t_data = m_dataMngr->getItemById(t_itemId);

			if (t_data)
			{
				_player->getEquipment(_char).push_back(t_data);
			}
			else
			{
				Log::write(LOG_ERROR, "Invalid item type id %d in MySQL table 'items' (id: %d)",
					t_itemId, t_result.getFieldS32(0));
			}

		}

		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getEquipment_C");
	}
#endif

	return false;
}

bool IItemPackManager::createEquipment_C(const CharacterPtr &_char,
										 const CArray<IStartItem> &_startItems)
{
	FDASSERT(_char);

	for (u32 i = 0; i < _startItems.size(); ++i)
	{
		if (_char->hasCorrectSex(_startItems[i].getSex()))
		{
			FDASSERT(_startItems[i].isValid());

			if (m_dbc->query("INSERT INTO items (owner,type,place,itemid,count,upgrade,element,eleupgrade,stats,"
				"type0,amount0,type1,amount1,type2,amount2,slot1,slot2,slot3,slot4,slot5,slot6,slot7,slot8,"
				"slot9,slot10) VALUES ('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',"
				"'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
				_char->getId(), IItemPack::TYPE_INVENTORY, _startItems[i].getPlace(),
				_startItems[i].getData()->getId(), _startItems[i].getCount(), _startItems[i].getUpgrade(),
				_startItems[i].getElement(), _startItems[i].getElementalUpgrade(),
				_startItems[i].getSpecialOption().getStatId(),
				_startItems[i].getSpecialOption().getEffect(0).Type, _startItems[i].getSpecialOption().getEffect(0).Amount,
				_startItems[i].getSpecialOption().getEffect(1).Type, _startItems[i].getSpecialOption().getEffect(1).Amount,
				_startItems[i].getSpecialOption().getEffect(2).Type, _startItems[i].getSpecialOption().getEffect(2).Amount,
				_startItems[i].getSlotItemId(0), _startItems[i].getSlotItemId(1),
				_startItems[i].getSlotItemId(2), _startItems[i].getSlotItemId(3),
				_startItems[i].getSlotItemId(4), _startItems[i].getSlotItemId(5),
				_startItems[i].getSlotItemId(6), _startItems[i].getSlotItemId(7),
				_startItems[i].getSlotItemId(8), _startItems[i].getSlotItemId(9)))
			{
			}
		#ifdef SETTING_MYSQL_ERRORS_ENABLED
			else
			{
				PRINT_ERROR("createEquipment_C");
				return false;
			}
	#endif
		}
	}

	return true;
}


//:: WORLD SERVER FUNCTIONS ::

ItemPackPtr IItemPackManager::getItemPack_W(ID _id)
{
	FDASSERT(m_dbc);
	FDASSERT(m_dataMngr);

	FOR_EACH (m_items, i)
	{
		if (m_items[i]->getId() == _id)
			return m_items[i];
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT " WORLD_FULL_SELECT_PROPERTIES " FROM items "
		"WHERE id='%d';",
		_id) &&
		m_dbc->getResult(t_result))
	{
		ItemPackPtr t_itemPack;

		if (t_result.nextRow())
		{
			t_itemPack = _newItemPack();

			_loadWorldItem(t_itemPack, t_result);
		}

		return t_itemPack;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getItemPack_W(ID)");
	}
#endif

	return 0;
}

ItemPackPtr IItemPackManager::getItemPack_W(const CharacterPtr &_owner,
											 IItemPack::E_TYPE _type,
											 s32 _slot)
{
	FDASSERT(m_dbc);
	FDASSERT(m_dataMngr);

	FDASSERT(_owner);

	//...

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT " WORLD_FULL_SELECT_PROPERTIES " FROM items "
		"WHERE owner='%d' and type='%d' and place='%d' ORDER BY id DESC",
		_owner->getId(), s32(_type), _slot) &&
		m_dbc->getResult(t_result))
	{
		ItemPackPtr t_itemPack;

		if (t_result.nextRow())
		{
			t_itemPack = _newItemPack();

			_loadWorldItem(t_itemPack, t_result);

			t_itemPack->setType(_type);
		}

		return t_itemPack;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getItemPack_W(const CharacterPtr &)");
	}
#endif

	return 0;
}

ItemPackPtr IItemPackManager::createItemPack_W(const CharacterPtr &_owner,
										IItemPack::E_TYPE _type,
										s32 _place,
										const IItemProperties &_prop)
{
	FDASSERT(_owner);
	FDASSERT(_prop.isValid());

	if (m_dbc->query("INSERT INTO items (owner,type,place,itemid,count,upgrade,element,eleupgrade,stats,"
		"leveldown,"
		"type0,amount0,type1,amount1,type2,amount2,slot1,slot2,slot3,slot4,slot5,slot6,slot7,slot8,"
		"slot9,slot10) VALUES('%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d',"
		"'%d','%d','%d','%d','%d','%d','%d','%d','%d','%d','%d')",
		_owner->getId(), s32(_type), _place, _prop.getData()->getId(), _prop.getCount(), s32(_prop.getUpgrade()),
		s32(_prop.getElement()), s32(_prop.getElementalUpgrade()), _prop.getSpecialOption().getStatId(),
		s32(_prop.getSpecialOption().getLevelDown()),
		s32(_prop.getSpecialOption().getEffect(0).Type), _prop.getSpecialOption().getEffect(0).Amount,
		s32(_prop.getSpecialOption().getEffect(1).Type), _prop.getSpecialOption().getEffect(1).Amount,
		s32(_prop.getSpecialOption().getEffect(2).Type), _prop.getSpecialOption().getEffect(2).Amount,
		_prop.getSlotItemId(0), _prop.getSlotItemId(1), _prop.getSlotItemId(2), _prop.getSlotItemId(3),
		_prop.getSlotItemId(4), _prop.getSlotItemId(5), _prop.getSlotItemId(6), _prop.getSlotItemId(7),
		_prop.getSlotItemId(8), _prop.getSlotItemId(9)))
	{
		return getItemPack_W(_owner, _type, _place);
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("createItemPack_W");
	}
#endif

	return 0;
}

bool IItemPackManager::removeItemPack_W(const ItemPackPtr &_item)
{
	FDASSERT(_item);

	if (m_dbc->query("DELETE FROM items WHERE id='%d'",
		_item->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("removeItemPack_W");
	}
#endif

	return false;
}

bool IItemPackManager::save_W()
{
	FOR_EACH (m_items, i)
	{
		if (!_saveItemPack_W(m_items[i]))
			return false;
	}

	return true;
}

bool IItemPackManager::saveItems_W(const PlayerObjectPtr &_pObj)
{
	FDASSERT(_pObj);

	IInventory *t_inv = _pObj->getInventory();

	for (u32 i = 0; i < t_inv->getSlotCount(); ++i)
	{
		const ItemPackPtr &t_item = t_inv->getSlot(i).getItem();

		if (t_item)
		{
			if (!saveItemPack_W(t_item))
			{
				return false;
			}
		}
	}

	return true;
}

bool IItemPackManager::saveItemPack_W(const ItemPackPtr &_item)
{
	FDASSERT(_item);

	return _saveItemPack_W(_item);
}

bool IItemPackManager::saveItemPackLocation_W(const ItemPackPtr &_item, const CharacterPtr &_owner)
{
	FDASSERT(_item);
	FDASSERT(_owner);
	FDASSERT(m_dbc);

	if (m_dbc->query(
		"UPDATE items SET type='%d',place='%d',owner='%d' WHERE id='%d'",
		_item->getType(), _item->getPlace(), _owner->getId(), _item->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("saveItemPackLocation_W");
	}
#endif

	return false;
}

bool IItemPackManager::loadInventory_W(const PlayerObjectPtr &_player)
{
	FDASSERT(_player);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT " WORLD_FULL_SELECT_PROPERTIES " FROM items "
		"WHERE owner='%d' and type='%d'",
		_player->getCharacter()->getId(), IItemPack::TYPE_INVENTORY) &&
		m_dbc->getResult(t_result))
	{
		ItemPackPtr t_itemPack;

		while (t_result.nextRow())
		{
			t_itemPack = _newItemPack();

			_loadWorldItem(t_itemPack, t_result);

			_player->getInventory()->getSlot(t_itemPack->getPlace()).setItem(t_itemPack);
		}

		Log::write(LOG_DEBUG, "%d Items loaded", _player->getInventory()->getCurrentItemCount());

		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("loadInventory_W");
	}
#endif

	return false;
}

ItemPackPtr IItemPackManager::_newItemPack()
{
	return ItemPackPtr(new IItemPack(this));
}

bool IItemPackManager::_saveItemPack_W(const ItemPackPtr &_item)
{
	FDASSERT(_item);

	u32 t_begin = CTime::system();

	if ((m_dbc->query("UPDATE items SET type='%d',place='%d',itemid='%d',count='%d',"
		"upgrade='%d',element='%d',eleupgrade='%d',stats='%d',type0='%d',amount0='%d',"
		"type1='%d',amount1='%d',type2='%d',amount2='%d',leveldown='%d',"
		"slot1='%d',slot2='%d',slot3='%d',slot4='%d',slot5='%d',slot6='%d',slot7='%d',"
		"slot8='%d',slot9='%d',slot10='%d' WHERE id='%d' LIMIT 1",
		/*_item->getType()*/ 1, _item->getPlace(), _item->getData()->getId(), _item->getCount(),
		_item->getUpgrade(), _item->getElement(), _item->getElementalUpgrade(),
		_item->getSpecialOption().getStatId(),
		_item->getSpecialOption().getEffect(0).Type, _item->getSpecialOption().getEffect(0).Amount,
		_item->getSpecialOption().getEffect(1).Type, _item->getSpecialOption().getEffect(1).Amount,
		_item->getSpecialOption().getEffect(2).Type, _item->getSpecialOption().getEffect(2).Amount,
		_item->getSpecialOption().getLevelDown(),
		_item->getSlotItemId(0),
		_item->getSlotItemId(1),
		_item->getSlotItemId(2),
		_item->getSlotItemId(3),
		_item->getSlotItemId(4),
		_item->getSlotItemId(5),
		_item->getSlotItemId(6),
		_item->getSlotItemId(7),
		_item->getSlotItemId(8),
		_item->getSlotItemId(9),
		_item->getId())))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("_saveItemPack_W");
	}
#endif

	return false;
}

bool IItemPackManager::_loadWorldItem(ItemPackPtr &_item, IQueryResult &_result)
{
	FDASSERT(_item);

	//WORLD_FULL_SELECT_PROPERTIES

	//id
	_item->m_id = _result.getFieldS32(0);

	//type
	_item->setType(IItemPack::type(_result.getFieldS32(1)));

	//place
	u32 t_place = Limit<u32>(_result.getFieldU32(2), 0, _item->getMaxPlace());
	_item->setPlace(t_place);

	//item data
	ID t_itemId = _result.getFieldS32(3);
	_item->m_data = m_dataMngr->getItemById(t_itemId);

	if (!_item->m_data)
	{
		Log::write(LOG_ERROR, "Invalid item type id %d in MySQL table 'items' (id: %d)",
			t_itemId, _item->m_id);
		return false;
	}

	_item->m_count = Limit(_result.getFieldS32(4), 0, _item->m_data->getStackSize());
	_item->m_upgrade = Limit<s32>(_result.getFieldS32(5), 0, IItemPack::UPGRADE_MAX);
	_item->m_element = element(_result.getFieldS32(6));
	_item->m_eleUpgrade = Limit<s32>(_result.getFieldS32(7), 0, IItemPack::UPGRADE_ELE_MAX);
	_item->m_spc.setStat(_result.getFieldS32(8));
	_item->m_spc.setLevelDown(levelDown(_result.getFieldS32(9)));
	_item->m_spc.setEffect(0, IStatEffect(stat(_result.getFieldS32(10)), _result.getFieldS32(11)));
	_item->m_spc.setEffect(1, IStatEffect(stat(_result.getFieldS32(12)), _result.getFieldS32(13)));
	_item->m_spc.setEffect(2, IStatEffect(stat(_result.getFieldS32(14)), _result.getFieldS32(15)));

	//slots:
	s32 t_slotItemId;
	const IItemData *t_itemData;

	for (u32 i = 0; i < 10; ++i)
	{
		t_slotItemId = _result.getFieldS32(16 + i);
		if (t_slotItemId)
		{
			t_itemData = m_dataMngr->getItemById(t_slotItemId);
			if (t_itemData)
			{
				_item->addSlot(t_itemData);
			}
			else
			{
				Log::write(LOG_ERROR, "ItemPack (Id %d): Invalid slot item Id %d in slot %u",
					_item->m_id, t_slotItemId, i + 1);
			}
		}
	}

	return _item->isValid();
}