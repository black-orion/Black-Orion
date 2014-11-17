#ifndef ITEMPACKMANAGER_H
#define ITEMPACKMANAGER_H


#include "Base.h"
#include "DatabaseManager.h"
#include "DatabaseObject.h"
#include "ItemPack.h"
#include "../char/CharSettings.h"


class ICharacter;
class IItemDataManager;
class IDatabaseConnection;
class IQueryResult;
class IPlayerObject;
class ICharPlayer;


class IItemPackManager : public IDatabaseManager
{
public:

	IItemPackManager(IDatabaseConnection *_dbc, IItemDataManager *_dataMngr);

	~IItemPackManager();

	void clear();

	void add(IDatabaseObject *_dbObj);

	void remove(IDatabaseObject *_dbObj);

	void update();

	u32 getItemPackNumber() const;

	void setDbc(IDatabaseConnection *_dbc);


	//:: CHAR SERVER FUNCTIONS ::

	ItemPackPtr getItemPack_C(ID _id, bool _fromDatabase = true);

	bool getEquipment_C(ICharPlayer *_player, u32 _char);

	bool createEquipment_C(const CharacterPtr &_char, const CArray<IStartItem> &_startItems);


	//:: WORLD SERVER FUNCTIONS ::

	//bool getEquipmentAndInventory_W(const CharacterPtr &_char); //depr

	ItemPackPtr getItemPack_W(ID _id);

	ItemPackPtr getItemPack_W(const CharacterPtr &_owner, IItemPack::E_TYPE _type, s32 _slot);

	ItemPackPtr createItemPack_W(const CharacterPtr &_owner, IItemPack::E_TYPE _type, s32 _place,
		const IItemProperties &_prop);

	bool removeItemPack_W(const ItemPackPtr &_item);

	bool save_W();

	bool saveItems_W(const PlayerObjectPtr &_pObj);

	bool saveItemPack_W(const ItemPackPtr &_item);

	bool saveItemPackLocation_W(const ItemPackPtr &_item, const CharacterPtr &_owner);

	bool loadInventory_W(const PlayerObjectPtr &_player);

private:

	IDatabaseConnection *m_dbc;

	IItemDataManager *m_dataMngr;

	CArray<ItemPackPtr> m_items;

	ItemPackPtr _newItemPack();

	bool _saveItemPack_W(const ItemPackPtr &_item);

	bool _loadWorldItem(ItemPackPtr &_item, IQueryResult &_result);

};


#endif //ITEMPACKMANAGER_H
