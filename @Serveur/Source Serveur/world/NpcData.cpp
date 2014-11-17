#include "NpcData.h"
#include "../shared/ItemData.h"


INpcData::INpcData()
	: m_mover(0)
	, m_worldId(1)
	, m_rotation(0)
	, m_size(100)
{
}

const char *INpcData::getName() const
{
	return m_name.c_str();
}

const char *INpcData::getFileName() const
{
	return m_fileName.c_str();
}

const char *INpcData::getDialogFileName() const
{
	return m_dialogFileName.c_str();
}

const IMoverData *INpcData::getMover() const
{
	return m_mover;
}

ID INpcData::getWorldId() const
{
	return m_worldId;
}

const CPoint &INpcData::getPosition() const
{
	return m_pos;
}

s16 INpcData::getRotation() const
{
	return m_rotation;
}

s16 INpcData::getSize() const
{
	return m_size;
}

u32 INpcData::getShopItemCount(u32 _page) const
{
	FDASSERT(_page < SHOP_PAGE_COUNT);

	return m_shopItems[_page].size();
}

const IItemProperties &INpcData::getShopItem(u32 _page, u32 _slot) const
{
	FDASSERT(_slot < getShopItemCount(_page));

	return m_shopItems[_page][_slot];
}

const IItemProperties *INpcData::getItemFromId(ID _itemId) const
{
	for (u32 i = 0; i < SHOP_PAGE_COUNT; ++i)
	{
		for (u32 j = 0; j < m_shopItems[i].size(); ++j)
		{
			if (m_shopItems[i][j].getData()->getId() == _itemId)
			{
				return &m_shopItems[i][j];
			}
		}
	}

	return 0;
}

u32 INpcData::getTextCount() const
{
	return m_texts.size();
}

const INpcData::Text &INpcData::getText(u32 _num) const
{
	FDASSERT(_num < m_texts.size());

	return m_texts[_num];
}