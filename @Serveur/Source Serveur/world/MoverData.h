#ifndef MOVERDATA_H
#define MOVERDATA_H


#include "WorldMain.h"
#include "WorldDataManager.h"
#include "../shared/E_ELEMENT.h"
#include "../shared/ItemPack.h"


class IItemData;


class IMoverData
{
public:

	struct DropBase
	{
		RATE Chance;

		DropBase(RATE _chance)
			: Chance(_chance)
		{
		}

		virtual ~DropBase()
		{
		}

		virtual bool isSpc() const
		{
			return false;
		}
	};

	struct Drop : public DropBase
	{
		const IItemData *Item;

		bool Clean;

		Drop(const IItemData *_item = 0, RATE _chance = 0.0f, bool _isClean = false)
			: Item(_item)
			, DropBase(_chance)
			, Clean(_isClean)
		{
		}

		bool isSpc() const
		{
			return false;
		}
	};

	struct DropSpc : public DropBase, public IItemProperties
	{
		DropSpc(const IItemProperties &_prop, RATE _chance)
			: IItemProperties(_prop)
			, DropBase(_chance)
		{
		}

		bool isSpc() const
		{
			return true;
		}
	};

	enum CLASS
	{
		RANK_LOW,
		RANK_NORMAL,
		RANK_CAPTAIN,
		RANK_BOSS,
		RANK_SUPER
	};

	IMoverData();

	~IMoverData();

	ID getId() const;

	const char *getIdName() const;

	LVL getLevel() const;

	E_ELEMENT getElement() const;

	EXP getExp() const;

	PENYA getPenyaMin() const;

	PENYA getPenyaMax() const;

	u32 getDropCount() const;

	const DropBase *getDrop(u32 _num) const;

	s32 getHp() const;

	s32 getDef() const;

	s32 getAttackMin() const;

	s32 getAttackMax() const;

	TimeMs getAttackDelay() const;

	s32 getHitRate() const;

	s32 getEvasion() const;

private:

	friend class IWorldDataManager;

	ID m_id;

	sdk::stringc m_idName;

	LVL m_level;

	CLASS m_class; //.

	E_ELEMENT m_element;

	EXP m_exp;

	s32 m_hp;

	s32 m_def;

	s32 m_atkMin;

	s32 m_atkMax;

	TimeMs m_attackDelay;

	s32 m_hit;

	s32 m_evasion;

	// Drops:
	PENYA m_penyaMin;

	PENYA m_penyaMax;

	CArray<DropBase*> m_drops;

};


#endif //WORLDPLAYER_H
