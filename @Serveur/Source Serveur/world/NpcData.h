#ifndef NPCDATA_H
#define NPCDATA_H


#include "WorldMain.h"
#include "../shared/ItemPack.h"


class IMoverData;
class IWorldDataManager;


class INpcData
{
public:

	enum
	{
		SHOP_PAGE_COUNT = 4
	};

	struct Text
	{
		TimeMs Delay;
		stringc Str;

		Text()
		{
		}

		Text(TimeMs _delay, const char *_str)
			: Delay(_delay)
			, Str(_str)
		{
		}
	};

	INpcData();

	const char *getName() const;

	const char *getFileName() const;

	const char *getDialogFileName() const;

	const IMoverData *getMover() const;

	ID getWorldId() const;

	const CPoint &getPosition() const;

	s16 getRotation() const;

	s16 getSize() const;

	u32 getShopItemCount(u32 _page) const;

	const IItemProperties &getShopItem(u32 _page, u32 _slot) const;

	const IItemProperties *getItemFromId(ID _itemId) const;

	u32 getTextCount() const;

	const Text &getText(u32 _num) const;

private:

	friend class IWorldDataManager;

	sdk::stringc m_name;

	sdk::stringc m_fileName;

	sdk::stringc m_dialogFileName;

	const IMoverData *m_mover;

	ID m_worldId;

	CPoint m_pos;

	s16 m_rotation;

	s16 m_size;

	CArray<IItemProperties> m_shopItems[SHOP_PAGE_COUNT];

	CArray<Text> m_texts;

};


#endif //NPCDATA_H
