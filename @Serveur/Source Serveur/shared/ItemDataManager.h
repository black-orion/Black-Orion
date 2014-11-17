#ifndef ITEMDATAMANAGER_H
#define ITEMDATAMANAGER_H


#include "Base.h"


class IItemData;
class IItemSet;


struct IItemDataManagerSettings
{

	bool WorldServer;

	bool LoadSpc;

	bool SaveSpc;

	sdk::stringc PropItemEtcFileName;

	//IF (LoadSpc)
	sdk::stringc SpcFileName;

	//ELSE
	sdk::stringc ItemIdFileName;

	sdk::stringc ItemTextFileName;

	sdk::stringc ItemDataFileName;

};


class IItemDataManager
{
public:

	IItemDataManager(IItemDataManagerSettings *_settings);

	~IItemDataManager();

	bool load_char();

	bool load_world();

	//create a blackorion item list which can be loaded fast
	bool saveItemsSpc(const char *_fileName) const;

	bool saveHtmlItemList(const char *_fileName) const;

	bool saveUseItemList(const char *_fileName) const;

	bool saveSpcItemList1(const char *_fileName) const;

	u32 getItemCount() const;

	const IItemData *getItemByNumber(u32 _num) const;

	const IItemData *getItemById(ID _id) const;

	const IItemData *getItemById(const char *_idName) const;

private:

	IItemDataManagerSettings *m_settings;

	CArray<IItemData*> m_items;

	CArray<IItemSet*> m_sets;

	IItemData *_getItemById(const char *_idName);

	bool _loadPropItemEtc();

	bool _loadItems();

	//load from special blackorion item file:
	bool _loadItemsSpc();

	//load from game files:
	bool _loadItemsNormally();

	bool _loadItemIds();

	bool _loadItemTexts();

	bool _loadItemData();

	const char *_getItemText(char *_dest, u32 _destSize, s32 _id);

	struct ItemText
	{
		s32 Id;

		sdk::stringc Value;

		ItemText(s32 _id = 0, const char *_value = "")
			: Id(_id)
			, Value(_value)
		{
		}
	};

	CArray<ItemText> m_itemTexts;

};


#endif //ITEMDATAMANAGER_H
