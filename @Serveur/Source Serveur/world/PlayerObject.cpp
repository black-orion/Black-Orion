#include "PlayerObject.h"
#include "WorldPlayer.h"
#include "WorldField.h"
#include "MobObject.h"
#include "MoverData.h"
#include "WorldDataManager.h"
#include "World.h"
#include "WorldServer.h"
#include "DropObject.h"
#include "NpcObject.h"
#include "PetObject.h"
#include "ItemPetObject.h"
#include "NpcObject.h"
#include "Party.h"
#include "../shared/PacketCreator.h"
#include "../shared/ItemData.h"
#include "../shared/ItemSet.h"
#include "../shared/RandomOption.h"
#include "../shared/ItemPack.h"
#include "../shared/Log.h"


char IPlayerObject::ms_buffer[BUF_SIZE];

IPlayerObject::IPlayerObject(ID _id, IWorld *_world, IWorldPlayer *_player)
	: ICreature(_id, _world)
	, m_player(_player)
	, m_flags(FLAG_NONE)
	, m_motion(0)
	, m_npcTarget(0)
	, m_inv(this)
	, m_post(this)
	, m_nextRegenerationTime(0)
	//, m_party(0)
{
	FDASSERT(m_player);

	const CharacterPtr &t_char = m_player->getCharacter();

	m_pos = t_char->getPosition();

	setStat(DST_HP, t_char->getHp());
	setStat(DST_MP, t_char->getMp());
	setStat(DST_FP, t_char->getFp());

	m_rotation = m_player->getCharacter()->getRotation();
	m_size = m_player->getCharacter()->getSize();

	//calculateStats();
}

IPlayerObject::~IPlayerObject()
{
	if (m_party)
	{
		m_party->removeMemberSilently(m_id);
	}
}

IPlayerObject::E_TYPE IPlayerObject::getType() const
{
	return TYPE_PLAYER;
}

IWorldPlayer *IPlayerObject::getPlayer()
{
	return m_player;
}

const AccountPtr &IPlayerObject::getAccount() const
{
	return m_player->getAccount();
}

const CharacterPtr &IPlayerObject::getCharacter() const
{
	return m_player->getCharacter();
}

s32 IPlayerObject::getFlags() const
{
	return m_flags;
}

bool IPlayerObject::isFlag(E_FLAGS _which)
{
	return (m_flags & _which) == _which;
}

s32 IPlayerObject::getMotion() const
{
	return m_motion;
}

RATE IPlayerObject::getExpRate() const
{
	return ms_gameSettings->Exp;
}

RATE IPlayerObject::getDropRate() const
{
	return ms_gameSettings->Drop;
}

RATE IPlayerObject::getPenyaRate() const
{
	return ms_gameSettings->Penya;
}

const NpcObjectPtr &IPlayerObject::getNpcTarget() const
{
	return m_npcTarget;
}

const PetObjectPtr &IPlayerObject::getPet() const
{
	return m_pet;
}

void IPlayerObject::setPet(const PetObjectPtr &_pet)
{
	m_pet = _pet;
}

LVL IPlayerObject::getLevel() const
{
	return (getCharacter() ? getCharacter()->getLevel() : 0);
}

void IPlayerObject::setFlags(s32 _flags)
{
	m_flags = _flags;
}

void IPlayerObject::setFlag(E_FLAGS _which, bool _value)
{
	if (_value)
	{
		m_flags |= _which;
	}
	else
	{
		m_flags &= ~_which;
	}
}

void IPlayerObject::toggleFlag(E_FLAGS _which)
{
	m_flags ^= _which;
}

void IPlayerObject::setMotion(s32 _motion)
{
	m_motion = _motion;
}

void IPlayerObject::setNpcTarget(const NpcObjectPtr &_npc)
{
	m_npcTarget = _npc;
}

void IPlayerObject::calculateStats()
{
	_clearStats();

	const CharacterPtr &t_char = m_player->getCharacter();

	//calculate base stats
	for (u32 i = INV_EQUIPS_INDEX; i < INV_TOTAL_ITEMS; ++i)
	{
		const ItemPackPtr &t_item = m_inv.getSlot(i).getItem();
		if (t_item)
		{
			_addItemStats(t_item);
		}
	}

	//set bonus
	CArray<std::pair<const IItemSet*, u32> > m_parts;

	const ItemPackPtr &t_cap = getInventory()->getEquipment(PARTS_CAP).getItem();
	if (t_cap &&
		t_cap->getData()->getSet())
	{
		bool t_found = false;

		for (u32 i = 0; i < m_parts.size(); ++i)
		{
			if (m_parts[i].first == t_cap->getData()->getSet())
			{
				++m_parts[i].second;
				t_found = true;
			}
		}

		if (!t_found)
		{
			m_parts.push_back(std::pair<const IItemSet*, u32>(t_cap->getData()->getSet(), 1));
		}
	}

	const ItemPackPtr &t_suit = getInventory()->getEquipment(PARTS_UPPER_BODY).getItem();
	if (t_suit &&
		t_suit->getData()->getSet())
	{
		bool t_found = false;

		for (u32 i = 0; i < m_parts.size(); ++i)
		{
			if (m_parts[i].first == t_suit->getData()->getSet())
			{
				++m_parts[i].second;
				t_found = true;
			}
		}

		if (!t_found)
		{
			m_parts.push_back(std::pair<const IItemSet*, u32>(t_suit->getData()->getSet(), 1));
		}
	}

	const ItemPackPtr &t_gaunt = getInventory()->getEquipment(PARTS_HAND).getItem();
	if (t_gaunt &&
		t_gaunt->getData()->getSet())
	{
		bool t_found = false;

		for (u32 i = 0; i < m_parts.size(); ++i)
		{
			if (m_parts[i].first == t_gaunt->getData()->getSet())
			{
				++m_parts[i].second;
				t_found = true;
			}
		}

		if (!t_found)
		{
			m_parts.push_back(std::pair<const IItemSet*, u32>(t_gaunt->getData()->getSet(), 1));
		}
	}

	const ItemPackPtr &t_boots = getInventory()->getEquipment(PARTS_FOOT).getItem();
	if (t_boots &&
		t_boots->getData()->getSet())
	{
		bool t_found = false;

		for (u32 i = 0; i < m_parts.size(); ++i)
		{
			if (m_parts[i].first == t_boots->getData()->getSet())
			{
				++m_parts[i].second;
				t_found = true;
			}
		}

		if (!t_found)
		{
			m_parts.push_back(std::pair<const IItemSet*, u32>(t_boots->getData()->getSet(), 1));
		}
	}

	for (u32 i = 0; i < m_parts.size(); ++i)
	{
		if (m_parts[i].second >= 2)
		{
			for (u32 j = 2; j <= m_parts[i].second; ++j)
			{
				for (u32 k = 0; k < m_parts[i].first->getEffectCount(j); ++k)
				{
					addStat(m_parts[i].first->getEffect(j, k));
				}
			}
		}
	}

	//base stats
	m_stats[DST_STR] += t_char->getStr() + m_stats[DST_STAT_ALLUP];
	m_stats[DST_STA] += t_char->getSta() + m_stats[DST_STAT_ALLUP];
	m_stats[DST_DEX] += t_char->getDex() + m_stats[DST_STAT_ALLUP];
	m_stats[DST_INT] += t_char->getInt() + m_stats[DST_STAT_ALLUP];

	//crit
	m_stats[DST_CHR_CHANCECRITICAL] +=
		static_cast<s32>(jobStats(getCharacter()->getJob()).Crit * m_stats[DST_DEX] / 10);

	//hp, mp, fp
	m_stats[DST_HP_MAX] +=
		s32((m_stats[DST_STA] * 0.02f + 1) * ((m_player->getCharacter()->getLevel() *
		(jobStats(m_player->getCharacter()->getJob()).HpRate) * 0.5f) *
		((m_player->getCharacter()->getLevel() + 1) * 0.25f)) +
		m_stats[DST_STA] * 10 + 80);

	m_stats[DST_MP_MAX] += s32((2 * m_player->getCharacter()->getLevel() + m_stats[DST_INT] * 8) *
		(jobStats(m_player->getCharacter()->getJob()).MpRate) + 22 + m_stats[DST_INT] *
		(jobStats(m_player->getCharacter()->getJob()).MpRate));

	m_stats[DST_FP_MAX] += s32((2 * m_player->getCharacter()->getLevel() + m_stats[DST_STA] * 6) *
		(jobStats(m_player->getCharacter()->getJob()).FpRate) + m_stats[DST_STA] *
		(jobStats(m_player->getCharacter()->getJob()).FpRate));

	m_stats[DST_HP_MAX] += m_stats[DST_HP_MAX] * m_stats[DST_HP_MAX_RATE] / 100;
	m_stats[DST_MP_MAX] += m_stats[DST_MP_MAX] * m_stats[DST_MP_MAX_RATE] / 100;
	m_stats[DST_FP_MAX] += m_stats[DST_FP_MAX] * m_stats[DST_FP_MAX_RATE] / 100;

	//hp, mp, fp reg
	m_stats[DST_HP_RECOVERY] = static_cast<s32>(
		(getCharacter()->getLevel() * 0.333333f) +
		(getStat(DST_STA) * jobStats(getCharacter()->getJob()).HpRegRate) +
		(getStat(DST_HP_MAX) / (500 * getCharacter()->getLevel())));
	//printf("HP reg = %d\n", m_stats[DST_HP_RECOVERY]);

	m_stats[DST_MP_RECOVERY] = static_cast<s32>(
		((getCharacter()->getLevel() * 1.5f) +
		(getStat(DST_INT) * jobStats(getCharacter()->getJob()).MpRegRate) +
		(getStat(DST_MP_MAX) / (500 * getCharacter()->getLevel()))) * 0.2f);
	printf("MP reg = %d\n", m_stats[DST_MP_RECOVERY]);

	m_stats[DST_FP_RECOVERY] = static_cast<s32>(
		((getCharacter()->getLevel() * 2) +
		(getStat(DST_STA) * jobStats(getCharacter()->getJob()).FpRegRate) +
		(getStat(DST_FP_MAX) / (500 * getCharacter()->getLevel()))) * 0.2f);
	printf("FP reg = %d\n", m_stats[DST_FP_RECOVERY]);

	//attack
	s32 t_weaponAtk = _calcWeaponAtk() + m_stats[DST_CHR_DMG] /*+ //AtkBonus (Add. Dmg)
		m_stats[DST_HPDMG_UP]*/; //??

	static const f32 TS_UPGRADE_ATK_RATE[] =
	{
		1.0f, 1.02f, 1.04f, 1.06f, 1.08f, 1.10f, 1.13f, 1.16f, 1.19f, 1.21f, 1.24f
	};

	static const s32 TS_UPGRADE_ATK_BONUS[] =
	{
		0, 1, 3, 5, 8, 11, 15, 19, 23, 29, 32
	};

	const ItemPackPtr &t_rWeapon = getInventory()->getEquipment(PARTS_RWEAPON).getItem();

	//calculate weapon atk
	if (t_rWeapon)
	{
		const s32 t_rWeaponUpgrade = Limit<s16>(t_rWeapon->getUpgrade(), 0, 10);

		m_stats[DST_ABILITY_MIN] = s32(
			((t_rWeapon->getData()->getAttributeMin() * 2) + t_weaponAtk) *
			TS_UPGRADE_ATK_RATE[t_rWeaponUpgrade]) +
			TS_UPGRADE_ATK_BONUS[t_rWeaponUpgrade];

		m_stats[DST_ABILITY_MAX] = s32(
			((t_rWeapon->getData()->getAttributeMax() * 2) + t_weaponAtk) *
			TS_UPGRADE_ATK_RATE[t_rWeaponUpgrade]) +
			TS_UPGRADE_ATK_BONUS[t_rWeaponUpgrade];
	}
	//atk without weapon
	else
	{
		m_stats[DST_ABILITY_MIN] = t_weaponAtk + 3;
		m_stats[DST_ABILITY_MAX] = t_weaponAtk + 5;
	}

	//add attack rate (%)
	m_stats[DST_ABILITY_MIN] = s32(m_stats[DST_ABILITY_MIN] * (100 + m_stats[DST_ATKPOWER_RATE]) / 100.0f);
	m_stats[DST_ABILITY_MAX] = s32(m_stats[DST_ABILITY_MAX] * (100 + m_stats[DST_ATKPOWER_RATE]) / 100.0f);

	//def
	_addEquipDef(PARTS_CAP);
	_addEquipDef(PARTS_UPPER_BODY);
	_addEquipDef(PARTS_HAND);
	_addEquipDef(PARTS_FOOT);
	_addEquipDef(PARTS_SHIELD);

	const IJobStats &t_jobStats = jobStats(m_player->getCharacter()->getJob());

	s32 t_addDef = m_stats[DST_ADJDEF] +
		s32(
		(t_jobStats.DefLevelRate * m_player->getCharacter()->getLevel()) +
		(t_jobStats.DefStaRate * m_stats[DST_STA])) -
		t_jobStats.BaseDef;

	m_def[0] /= 4;
	m_def[0] = s32((m_def[0] + t_addDef) * (m_stats[DST_ADJDEF_RATE] + 100) / 100.0f);
	m_def[1] /= 4;
	m_def[1] = s32((m_def[1] + t_addDef) * (m_stats[DST_ADJDEF_RATE] + 100) / 100.0f);
}

const IPlayerObject::AttackResult &IPlayerObject::attack(const CreaturePtr &_target, s32 _attackMotion)
{
	FDASSERT(_target);

	m_attackResult.Damage = 0;
	m_attackResult.Flags = 0;

	if (_target->isDead())
	{
		return m_attackResult;
	}

	//arrows
	IItemSlot &t_weaponSlot = getInventory()->getEquipment(PARTS_RWEAPON);

	if (t_weaponSlot.getItem() &&
		t_weaponSlot.getItem()->getData()->getItemKind3() == IItemData::IK3_BOW)
	{
		IItemSlot &t_arrowSlot = getInventory()->getEquipment(PARTS_BULLET);

		if (t_arrowSlot.getItem() &&
			!t_arrowSlot.getItem()->isEmpty())
		{
			getInventory()->deleteItem(INV_EQUIPS_INDEX + PARTS_BULLET, 1);
		}
		else
		{
			return m_attackResult;
		}
	}

	//one hit kill
	if (isFlag(FLAG_ONEHITKILL))
	{
		m_attackResult.Damage = _target->getStat(DST_HP);
	}
	else
	{
		//hit rate
		bool t_hit = false;

		const CharacterPtr &t_char = m_player->getCharacter();

		switch (_target->getType())
		{
		case IWorldObject::TYPE_MOB:
			{
				MobObjectPtr t_mobObject = boost::dynamic_pointer_cast<IMobObject>(_target);

				s32 t_enemyFleeRate = t_mobObject->getMover()->getEvasion(); //...
				s32 t_enemyLevel = t_mobObject->getMover()->getLevel();

				s32 t_hitRate = (Limit(m_stats[DST_ADJ_HITRATE] +
					static_cast<s32>(
					m_stats[DST_DEX] / f32(m_stats[DST_DEX] + t_enemyFleeRate) * t_char->getLevel() /
					(t_char->getLevel() + t_enemyLevel) * 288),
					20, 96));

				t_hit = eventf(t_hitRate / 100.0f);
				break;
			}

		default:
			FDASSERT(false);
		}

		//hit
		if (t_hit)
		{
			s32 t_atk = m_stats[DST_ABILITY_MIN] +
				random(m_stats[DST_ABILITY_MIN], m_stats[DST_ABILITY_MAX]);

			s32 t_def = random(_target->getMinDef(), _target->getMaxDef());

			//level difference
			LVL t_lvlDiff = Limit(_target->getLevel() - this->getLevel(), -24, 24);

			if (t_lvlDiff > 0)
			{
				t_atk = static_cast<s32>((100 - t_lvlDiff * 4) / 100.0f * t_atk);
			}
			else
			{
				t_def = static_cast<s32>((100 + t_lvlDiff * 4) / 100.0f * t_def);
			}

			m_attackResult.Damage = Max(0, t_atk - t_def);

			//crit
			if (eventf(m_stats[DST_CHR_CHANCECRITICAL] / 100.0f))
			{
				//Additional damage of critical hits
				s32 t_adoch = (m_attackResult.Damage / 100) * m_stats[DST_CRITICAL_BONUS];

				m_attackResult.Damage += random(t_adoch, m_attackResult.Damage + t_adoch); //random bonus

				m_attackResult.Flags |= ICreature::ATT_CRIT;
			}

			//block
			s32 t_block = _target->getStat(DST_BLOCK_MELEE);

			if (eventf(t_block / 100.0f))
			{
				m_attackResult.Damage = Max(_target->getLevel() * 2,
					static_cast<s32>(m_attackResult.Damage * randomf() * 0.5f));

				m_attackResult.Flags |= ICreature::ATT_BLOCK;
			}

			m_attackResult.Damage = Limit(m_attackResult.Damage, 0, _target->getStat(DST_HP));
		}
		else
		{
			m_attackResult.Flags |= ICreature::ATT_MISS;
		}
	}

	sendToLocalArea(IPacketCreator::attack(this, _target, _attackMotion), this);

	_target->damage(m_attackResult, this);

	return m_attackResult;
}

void IPlayerObject::damage(AttackResult &_result, const CreaturePtr &_attacker)
{
	FDASSERT(_attacker);

	//immortality
	if (isFlag(FLAG_INVINCIBLE))
	{
		return;
	}

	sendToLocalArea(IPacketCreator::damage(_attacker, this, _result.Damage, _result.Flags));

	m_stats[DST_HP] -= _result.Damage;

	if (getStat(DST_HP) < 0)
	{
		setStat(DST_HP, 0);
	}

	m_nextRegenerationTime = _time() + _getSettings()->Game.PlayerRegenerationTime;

	if (isDead())
	{
		_result.Kill = true;

		kill(DEATH_MOB, _attacker);
	}
	else
	{
		//... follow player etc.
	}
}

void IPlayerObject::kill(E_DEATH _type, const CreaturePtr &_killer)
{
	m_stats[DST_HP] = 0;

	sendToLocalArea(IPacketCreator::objectDeath(this));

	switch (_type)
	{
	case DEATH_MOB:
		{
			break;
		}

	case DEATH_PVP:
		{
			break;
		}

	case DEATH_PK:
		{
			break;
		}

	case DEATH_SPC:
		{
			break;
		}

	default:
		{
			FDASSERT(false && "Invalid param E_DEATH _type");
		}
	}
}

void IPlayerObject::updateCharacter()
{
	FDASSERT(m_player);

	const CharacterPtr &t_char = m_player->getCharacter();

	if (t_char)
	{
		t_char->setPosition(m_pos);
		t_char->setWorldId(m_world->getId());
		t_char->setRotation(m_rotation);

		t_char->setSize(m_size);

		t_char->setHp(getStat(DST_HP));
		t_char->setMp(getStat(DST_MP));
		t_char->setFp(getStat(DST_FP));
	}
}

void IPlayerObject::addMobExp(EXP _exp)
{
	FDASSERT(m_player);
	FDASSERT(m_player->getCharacter());

	changeExp(m_player->getCharacter()->getExp() + static_cast<EXP>(getExpRate() * _exp));
}

bool IPlayerObject::canLevelUp() const
{
	return (
		getCharacter()->getLevel() < _getSettings()->Game.ExpMaxLevel &&
		getCharacter()->getLevel() < jobStats(getCharacter()->getJob()).MaxLevel &&
		getCharacter()->getExp() >= _getWorldDataMngr()->getLevelExp(getCharacter()->getLevel()));
}

bool IPlayerObject::levelUp()
{
	bool r_leveledUp = false;

	LVL t_oldLevel = getCharacter()->getLevel();

	while (canLevelUp())
	{
		//remove exp
		getCharacter()->addExp( - _getWorldDataMngr()->getLevelExp(getCharacter()->getLevel()));

		getCharacter()->incrementLevel();

		//add stat points
		if (isMaster(getCharacter()->getJob()))
		{
			getCharacter()->setStatPoints(getCharacter()->getStatPoints() +
				ms_gameSettings->LevelUpStatPointsMaster);
		}
		else if (isHero(getCharacter()->getJob()))
		{
			getCharacter()->setStatPoints(getCharacter()->getStatPoints() +
				ms_gameSettings->LevelUpStatPointsHero);
		}
		else
		{
			getCharacter()->setStatPoints(getCharacter()->getStatPoints() +
				ms_gameSettings->LevelUpStatPoints);
		}
	}

	//level has changed
	if (t_oldLevel != getCharacter()->getLevel())
	{
		return (changeLevel(getCharacter()->getLevel()) &&
			sendToLocalArea(IPacketCreator::statPoints(this)));
	}

	return false;
}

bool IPlayerObject::changePenya(PENYA _new)
{
	FDASSERT(m_player);

	m_player->getCharacter()->setPenya(_new);

	return sendToLocalArea(IPacketCreator::updateAttribute(this, DST_GOLD, _new));
}

bool IPlayerObject::changeExp(EXP _exp)
{
	FDASSERT(m_player);

	//Level down
	if (_getSettings()->Game.Delevel)
	{
		while (_exp < 0)
		{
			if (getCharacter()->getLevel() <= 1)
			{
				_exp = 0;
				break;
			}

			getCharacter()->setLevel(getCharacter()->getLevel() - 1);
			_exp += _getWorldDataMngr()->getLevelExp(getCharacter()->getLevel());
		}
	}
	else
	{
		_exp = Max<EXP>(_exp, 0);
	}

	getCharacter()->setExp(_exp);

	if (!levelUp())
	{
		return sendToLocalArea(IPacketCreator::levelInfos(this));
	}

	return true;
}

bool IPlayerObject::changeJob(E_JOB _job)
{
	FDASSERT(_job == job(_job));

	getCharacter()->setJob(_job);

	return sendToLocalArea(IPacketCreator::job(this));
}

bool IPlayerObject::changeLevel(LVL _lvl)
{
	getCharacter()->setLevel(Limit(_lvl, 1, _getSettings()->Game.SpcMaxLevel));

	calculateStats();

	fillHp();
	fillMp();
	fillFp();

	return sendToLocalArea(IPacketCreator::levelInfos(this));
}

bool IPlayerObject::changeBanTime(Time _until)
{
	FDASSERT(getAccount());

	getAccount()->setBanTime(_until);

	return getWorld()->getServer()->getAccountManager()->saveAccount_banTime(getAccount());
}

bool IPlayerObject::changeAccessLevel(IAccount::E_ACCESS_LEVEL _accessLevel)
{
	FDASSERT(getAccount());

	getAccount()->setAccessLevel(_accessLevel);

	return getWorld()->getServer()->getAccountManager()->saveAccount_accessLevel(getAccount());
}

bool IPlayerObject::changePvpPoints(s32 _pvp)
{
	FDASSERT(getCharacter());

	getCharacter()->setPvpPoints(_pvp);

	return sendToLocalArea(IPacketCreator::pvpPoints(this));
}

bool IPlayerObject::changePkPoints(s32 _pk)
{
	FDASSERT(getCharacter());

	getCharacter()->setPkPoints(_pk);

	//return sendToLocalArea(IPacketCreator::karma(this));
	return true;
}

bool IPlayerObject::changeDisposition(s32 _disposition)
{
	FDASSERT(getCharacter());

	getCharacter()->setDisposition(_disposition);

	//return sendToLocalArea(IPacketCreator::karma(this));
	return true;
}

bool IPlayerObject::isAllowedToTake(const DropObjectPtr &_drop)
{
	return
		(!_drop->getOwner() ||
		(_drop->getOwner() == this)); //party is missing
}

void IPlayerObject::teleport(const CPoint &_pos, IWorld *_world)
{
	//same world
	if (!_world ||
		m_world == _world)
	{
		m_pos = _pos;
		sendToLocalArea(IPacketCreator::positionUpdate(this));
		onChangePosition();
	}

	//other world
	else
	{
		_world->transferObject(this, _world);
	}

	m_nextPosUpdate = 0;
}

IInventory *IPlayerObject::getInventory()
{
	return &m_inv;
}

const IInventory *IPlayerObject::getInventory() const
{
	return &m_inv;
}

IPostBox *IPlayerObject::getPostBox()
{
	return &m_post;
}

const IPostBox *IPlayerObject::getPostBox() const
{
	return &m_post;
}

PartyPtr &IPlayerObject::getParty()
{
	return m_party;
}

const PartyPtr &IPlayerObject::getParty() const
{
	return m_party;
}

void IPlayerObject::setParty(PartyPtr &_party)
{
	m_party = _party;
}

void IPlayerObject::partyInvite(const PlayerObjectPtr &_invitee)
{
	FDASSERT(_invitee);

	if (m_party &&
		(m_party->isMember(_invitee) ||
		m_party->getLeader() != this))
	{
		return;
	}

	_invitee->getPlayer()->getClient()->send(IPacketCreator::partyInvitation(this, _invitee));

	m_invitees.push_back(_invitee->getCharacter()->getId());
}

void IPlayerObject::partyInvitationAccepted(const PlayerObjectPtr &_invitee)
{
	FDASSERT(_invitee);
	FDASSERT(this != _invitee);

	//find the invitation
	u32 t_index = 0;
	if (m_invitees.find(t_index, _invitee->getCharacter()->getId()))
	{
		m_invitees.erase_fast(t_index);

		if (m_party)
		{
			m_party->addMember(_invitee);
		}
		else
		{
			m_party = _getServer()->createParty(this, _invitee);
		}
	}
	else
	{
		Log::write(LOG_GAME, "'%s' accepted a party invitation which has never been sent!",
			_invitee->getCharacter()->getName());
	}
}

void IPlayerObject::reviveLoadStar()
{
	FDASSERT(isDead());

	m_world->noTarget(this);

	setStat(DST_HP, Max(static_cast<s32>(getStat(DST_HP_MAX) * 0.3f), 1), true);
	setStat(DST_MP, Max(static_cast<s32>(getStat(DST_MP_MAX) * 0.3f), 1), true);
	setStat(DST_FP, Max(static_cast<s32>(getStat(DST_FP_MAX) * 0.3f), 1), true);

	sendToLocalArea(IPacketCreator::revival(this));

	teleport(CPoint(6967, 100, 3333));

	if (getCharacter()->getLevel() >= _getSettings()->Game.DeathExpLostFrom)
	{
		changeExp(getCharacter()->getExp() - _getWorldDataMngr()->getExpLost(getCharacter()->getLevel()));
	}
}

void IPlayerObject::reviveOriginal()
{
	FDASSERT(isDead());

	m_world->noTarget(this);

	setStat(DST_HP, Max(static_cast<s32>(getStat(DST_HP_MAX) * 0.3f), 1), true);
	setStat(DST_MP, Max(static_cast<s32>(getStat(DST_MP_MAX) * 0.3f), 1), true);
	setStat(DST_FP, Max(static_cast<s32>(getStat(DST_FP_MAX) * 0.3f), 1), true);

	sendToLocalArea(IPacketCreator::revival(this));
}

void IPlayerObject::reviveBySkill()
{
	FDASSERT(isDead());
}

void IPlayerObject::onWorldRemove()
{
	ICreature::onWorldRemove();

	m_npcTarget.reset();
	m_pet.reset();
}

void IPlayerObject::onDestroy()
{
	ICreature::onDestroy();

	if (m_party)
	{
		m_party->removeMember(getId());
		m_party.reset();
	}
}

void IPlayerObject::_addItemStats(const ItemPackPtr &_item)
{
	FDASSERT(_item);
	FDASSERT(_item->getData());

	//item standard effects
	addStat(_item->getData()->getEffect(0).Type, _item->getData()->getEffect(0).Amount);
	addStat(_item->getData()->getEffect(1).Type, _item->getData()->getEffect(1).Amount);
	addStat(_item->getData()->getEffect(2).Type, _item->getData()->getEffect(2).Amount);

	//awakening
	addStat(_item->getSpecialOption().getEffect(0).Type, _item->getSpecialOption().getEffect(0).Amount);
	addStat(_item->getSpecialOption().getEffect(1).Type, _item->getSpecialOption().getEffect(1).Amount);
	addStat(_item->getSpecialOption().getEffect(2).Type, _item->getSpecialOption().getEffect(2).Amount);

	//statting
	if (_item->getSpecialOption().getStat())
	{
		for (u32 i = 0; i < _item->getSpecialOption().getStat()->getEffectCount(); ++i)
		{
			addStat(_item->getSpecialOption().getStat()->getEffect(i));
		}
	}

	//sockets
	for (u32 i = 0; i < _item->getSlotCount(); ++i)
	{
		if (_item->getSlot(i))
		{
			for (u32 j = 0; j < _item->getSlot(i)->getPiercingEffectCount(); ++j)
			{
				const IStatEffect &t_bonus = _item->getSlot(i)->getPiercingEffect(j);

				addStat(t_bonus.Type, t_bonus.Amount);
			}
		}
	}
}

void IPlayerObject::update()
{
	_updatePosition();

	//follow an object
	if (m_followed)
	{
		//take drops
		if (m_followed->isDrop() &&
			m_followed->getPosition().getXZ().isInRange(m_pos.getXZ(), ms_gameSettings->LootRange))
		{
			DropObjectPtr t_drop = boost::dynamic_pointer_cast<IDropObject>(m_followed);

			//the item could have an owner
			if (isAllowedToTake(t_drop))
			{
				//money
				if (t_drop->getItem().isPenya())
				{
					changePenya(getCharacter()->getPenya() + t_drop->getItem().getCount());

					//display the money found
					sprintf(ms_buffer, "%d %d",
						t_drop->getItem().getCount(), getCharacter()->getPenya());

					m_player->getClient()->send(IPacketCreator::gameInfo(this, TID_GAME_REAPMONEY, ms_buffer));

					//remove the drop obj
					m_world->removeObject(m_followed, true);
					m_followed = 0;
				}

				//items
				else if (getInventory()->isRoomFor(t_drop->getItem()))
				{
					m_motion = 11;
					m_world->sendToLocalArea(this, IPacketCreator::motion(this));
					m_motion = 0;

					getInventory()->addItem(t_drop->getItem());

					//display the item found
					sprintf(ms_buffer, "\"%s\"",
						t_drop->getItem().getFullName());

					m_player->getClient()->send(IPacketCreator::gameInfo(this, TID_GAME_REAPITEM, ms_buffer));

					//remove the drop obj
					m_world->removeObject(m_followed, true);
					m_followed = 0;
				}

				//inv is full
				else
				{
					m_player->getClient()->send(IPacketCreator::gameInfo(this, TID_GAME_LACKSPACE));

					follow(0);
				}
			}
			else
			{
				follow(0);

				m_player->getClient()->send(IPacketCreator::gameInfo(this, TID_GAME_HOLDITEM));
			}
		}
	}

	//regeneration
	if (_time() >= m_nextRegenerationTime &&
		isAlive())
	{
		//HP
		if (getStat(DST_HP) < getStat(DST_HP_MAX))
		{
			addStat(DST_HP, Limit(getStat(DST_HP_RECOVERY), 1, getStat(DST_HP_MAX) - getStat(DST_HP)));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_HP, getStat(DST_HP)));
		}
		else if (getStat(DST_HP) > getStat(DST_HP_MAX))
		{
			setStat(DST_HP, getStat(DST_HP_MAX));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_HP, getStat(DST_HP)));
		}

		//MP
		if (getStat(DST_MP) < getStat(DST_MP_MAX))
		{
			addStat(DST_MP, Limit(getStat(DST_MP_RECOVERY), 1, getStat(DST_MP_MAX) - getStat(DST_MP)));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_MP, getStat(DST_MP)));
		}
		else if (getStat(DST_MP) > getStat(DST_MP_MAX))
		{
			setStat(DST_MP, getStat(DST_MP_MAX));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_MP, getStat(DST_MP)));
		}

		//FP
		if (getStat(DST_FP) < getStat(DST_FP_MAX))
		{
			addStat(DST_FP, Limit(getStat(DST_FP_RECOVERY), 1, getStat(DST_FP_MAX) - getStat(DST_FP)));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_FP, getStat(DST_FP)));
		}
		else if (getStat(DST_FP) > getStat(DST_FP_MAX))
		{
			setStat(DST_FP, getStat(DST_FP_MAX));
			m_player->getClient()->send(IPacketCreator::updateAttribute(this, DST_FP, getStat(DST_FP)));
		}

		m_nextRegenerationTime = _time() + _getSettings()->Game.PlayerRegenerationTime;
	}
}

void IPlayerObject::onBaseStatChanged()
{
	m_player->getClient()->send(IPacketCreator::statInfos(this));

	onStatRelatedChanged();
}

void IPlayerObject::onStatRelatedChanged()
{
	calculateStats();
}

u32 IPlayerObject::getSessionVarCount() const
{
	return m_sessionVars.size();
}

CPair<std::string, std::string> &IPlayerObject::getSessionVar(u32 _num)
{
	FDASSERT(_num < m_sessionVars.size());

	return m_sessionVars.get(_num);
}

const CPair<std::string, std::string> &IPlayerObject::getSessionVar(u32 _num) const
{
	FDASSERT(_num < m_sessionVars.size());

	return m_sessionVars.get(_num);
}

std::string &IPlayerObject::getSessionVar(const std::string &_name)
{
	return m_sessionVars[_name];
}

void IPlayerObject::setSessionVar(u32 _num, const std::string &_name, const std::string &_value)
{
	FDASSERT(_num < m_sessionVars.size());

	m_sessionVars.get(_num).first = _name;
	m_sessionVars.get(_num).second = _value;
}

void IPlayerObject::setSessionVar(const std::string &_name, const std::string &_value)
{
	m_sessionVars[_name] = _value;
}

bool IPlayerObject::isSessionVarSet(const std::string &_name)
{
	return m_sessionVars.find_key(_name);
}

void IPlayerObject::eraseSessionVar(u32 _num)
{
	FDASSERT(_num < m_sessionVars.size());

	m_sessionVars.erase(_num);
}

void IPlayerObject::eraseSessionVar(const std::string &_name)
{
	m_sessionVars.erase_by_key(_name);
}

void IPlayerObject::clearSession()
{
	m_sessionVars.clear();
}

s32 IPlayerObject::_calcWeaponAtk() const
{
	const ItemPackPtr &t_rWeapon = getInventory()->getEquipment(PARTS_RWEAPON).getItem();

	if (t_rWeapon)
	{
		const IJobStats &t_jobStats = jobStats(m_player->getCharacter()->getJob());

		switch (t_rWeapon->getData()->getItemKind3())
		{
		case IItemData::IK3_SWD:
			return s32(
				((m_stats[DST_STR] - 12) * t_jobStats.Sword) +
				(m_player->getCharacter()->getLevel() * 1.1f)) +
				m_stats[DST_SWD_DMG];

		case IItemData::IK3_AXE:
			return s32(
				((m_stats[DST_STR] - 12) * t_jobStats.Axe) +
				(m_player->getCharacter()->getLevel() * 1.2f)) +
				m_stats[DST_AXE_DMG];

		case IItemData::IK3_CHEERSTICK:
			return s32(
				((m_stats[DST_STR] - 10) * t_jobStats.Stick) +
				(m_player->getCharacter()->getLevel() * 1.3f));

		case IItemData::IK3_KNUCKLEHAMMER:
			return s32(
				((m_stats[DST_STR] - 10) * t_jobStats.Knuckle) +
				(m_player->getCharacter()->getLevel() * 1.2f)) +
				m_stats[DST_KNUCKLE_DMG];

		case IItemData::IK3_WAND:
			return s32(
				((m_stats[DST_INT] - 10) * t_jobStats.Wand) +
				(m_player->getCharacter()->getLevel() * 1.2f));

		case IItemData::IK3_STAFF:
			return s32(
				((m_stats[DST_STR] - 10) * t_jobStats.Staff) +
				(m_player->getCharacter()->getLevel() * 1.1f));

		case IItemData::IK3_YOYO:
			return s32(
				((m_stats[DST_STR] - 12) * t_jobStats.Yoyo) +
				(m_player->getCharacter()->getLevel() * 1.1f)) +
				m_stats[DST_YOY_DMG];

		case IItemData::IK3_BOW:
			return s32(
				((m_stats[DST_DEX] - 14) * t_jobStats.Bow) +
				((m_player->getCharacter()->getLevel() * 1.3f) +
				(m_stats[DST_STR] * 0.2f)) * 0.7f) +
				m_stats[DST_BOW_DMG];
		};
	}

	return s32(
		((m_stats[DST_STR] - 10) * 0.8f) +
		(m_player->getCharacter()->getLevel() * 1.1f));
}

void IPlayerObject::_addEquipDef(E_INVENTORY _equipType)
{
	static const f32 TS_UPGRADE_DEF_RATE[] =
	{
		1.0f, 1.02f, 1.04f, 1.06f, 1.08f, 1.10f, 1.13f, 1.16f, 1.19f, 1.21f, 1.24f
	};

	static const s32 TS_UPGRADE_DEF_BONUS[] =
	{
		0, 1, 3, 5, 8, 11, 15, 19, 23, 29, 32
	};

	const ItemPackPtr &t_equip = getInventory()->getEquipment(_equipType).getItem();

	if (t_equip)
	{
		const s32 t_upgrade = Limit<s32>(t_equip->getUpgrade(), 0, 10);

		addMinDef(s32(t_equip->getData()->getAttributeMin() *
			TS_UPGRADE_DEF_RATE[t_upgrade]) +
			TS_UPGRADE_DEF_BONUS[t_upgrade]);

		addMaxDef(s32(t_equip->getData()->getAttributeMax() *
			TS_UPGRADE_DEF_RATE[Limit<s32>(t_equip->getUpgrade(), 0, 10)]) +
			TS_UPGRADE_DEF_BONUS[t_upgrade]);
	}
}

bool IPlayerObject::_isCharacter() const
{
	return (m_player &&
		m_player->getCharacter());
}

IWorldServer *IPlayerObject::_getServer()
{
	FDASSERT(m_world);

	return m_world->getServer();
}

const IWorldSettings *IPlayerObject::_getSettings() const
{
	FDASSERT(m_world);
	FDASSERT(m_world->getServer());
	FDASSERT(m_world->getServer()->getSettings());

	return m_world->getServer()->getSettings();
}

const IWorldDataManager *IPlayerObject::_getWorldDataMngr() const
{
	FDASSERT(m_world);
	FDASSERT(m_world->getServer());
	FDASSERT(m_world->getServer()->getDataManager());

	return m_world->getServer()->getDataManager();
}
