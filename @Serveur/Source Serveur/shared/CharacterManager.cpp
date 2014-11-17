#include "CharacterManager.h"
#include "Character.h"
#include "Account.h"
#include "AccountManager.h"
#include "ItemPackManager.h"
#include "DatabaseConnection.h"
#include "Log.h"
#include "../char/CharPlayer.h"


ICharacterManager::ICharacterManager(IDatabaseConnection *_dbc, IAccountManager *_accMngr,
									 IItemPackManager *_itemMngr)
	: m_dbc(_dbc)
	, m_accMngr(_accMngr)
	, m_itemMngr(_itemMngr)
{
	FDASSERT(m_accMngr);
	FDASSERT(m_itemMngr);
}

ICharacterManager::~ICharacterManager()
{
}

void ICharacterManager::clear()
{
	m_chars.clear();
}

void ICharacterManager::add(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	m_chars.push_back(CharacterPtr((ICharacter*)_dbObj));
}

void ICharacterManager::remove(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	FOR_EACH (m_chars, i)
	{
		if (m_chars[i] == _dbObj)
		{
			m_chars[i].reset();
			m_chars.erase_fast(i);
			return;
		}
	}

	FDASSERT(false && "Invalid _dbObj");
}

void ICharacterManager::update()
{
	FOR_EACH (m_chars, i)
	{
		if (m_chars[i]->isUnique())
		{
			m_chars[i].reset();
			m_chars.erase_fast(i);
			if (i)
				--i;
		}
	}
}

u32 ICharacterManager::getCharacterNumber() const
{
	return m_chars.size();
}

void ICharacterManager::setDbc(IDatabaseConnection *_dbc)
{
	m_dbc = _dbc;
}


//:: CHAR SERVER FUNCTIONS ::

CharacterPtr ICharacterManager::getCharacter_C(ID _id, bool _fromDatabase)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_chars, i)
	{
		if (m_chars[i]->getId() == _id)
			return CharacterPtr(m_chars[i]);
	}

	if (!_fromDatabase)
		return 0;

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,account,place,sex,job,hairtype,haircolor,facetype,level,"
		"stat_str,stat_sta,stat_dex,stat_int FROM characters WHERE id='%u';",
		_id) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			CharacterPtr t_char = _newCharacter();

			//ID
			t_char->m_id = t_result.getFieldS32(0);

			//Name
			t_char->m_name = t_result.getFieldString(1);

			//Account
			ID t_accId = t_result.getFieldS32(2);

			//Place
			t_char->m_place = Limit(t_result.getFieldS32(3), 0, 2);

			//
			t_char->m_sex = sex(t_result.getFieldU32(4));
			t_char->m_job = job(t_result.getFieldU32(5));
			t_char->m_hairType = hair(t_result.getFieldS32(6));
			t_char->m_hairColor = t_result.getFieldS32(7);
			t_char->m_faceType = face(t_result.getFieldS32(8));
			t_char->m_level = Limit(t_result.getFieldS32(9), 1, 150);
			t_char->m_str = t_result.getFieldS32(10);
			t_char->m_sta = t_result.getFieldS32(11);
			t_char->m_dex = t_result.getFieldS32(12);
			t_char->m_int = t_result.getFieldS32(13);

			t_char->m_account = m_accMngr->getAccount_C(t_accId);

			//unknown account
			if (!t_char->m_account)
			{
				Log::write(LOG_ERROR, "Invalid account id %d in MySQL table 'characters' (id: %d)",
					t_accId, t_char->m_id);

				return 0;
			}

			t_char->m_account->setCharacter(t_char->m_place, t_char);

			return t_char;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getCharacter_C(ID)");
	}
#endif

	return 0;
}

CharacterPtr ICharacterManager::getCharacter_C(const char *_name, bool _fromDatabase)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_chars, i)
	{
		if (strcmp(m_chars[i]->getName(), _name) == 0)
		{
			return CharacterPtr(m_chars[i]);
		}
	}

	if (!_fromDatabase)
		return 0;

	sdk::stringc t_name = xescape(_name);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,account,place,sex,job,hairtype,haircolor,facetype,level,"
		"stat_str,stat_sta,stat_dex,stat_int FROM characters WHERE name='%s';",
		t_name.c_str()) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			CharacterPtr t_char = _newCharacter();

			//ID
			t_char->m_id = t_result.getFieldS32(0);

			//Name
			t_char->m_name = t_result.getFieldString(1);

			//Account
			ID t_accId = t_result.getFieldS32(2);

			//Place
			s32 t_place = Limit(t_result.getFieldS32(3), 0, 2);

			//
			t_char->m_sex = sex(t_result.getFieldU32(4));
			t_char->m_job = job(t_result.getFieldU32(5));
			t_char->m_hairType = hair(t_result.getFieldS32(6));
			t_char->m_hairColor = t_result.getFieldS32(7);
			t_char->m_faceType = face(t_result.getFieldS32(8));
			t_char->m_level = Limit(t_result.getFieldS32(9), 1, 150);
			t_char->m_str = t_result.getFieldS32(10);
			t_char->m_sta = t_result.getFieldS32(11);
			t_char->m_dex = t_result.getFieldS32(12);
			t_char->m_int = t_result.getFieldS32(13);

			t_char->m_account = m_accMngr->getAccount_C(t_accId);

			if (!t_char->m_account)
			{
				Log::write(LOG_WARNING, "Character \"%s\" (%d) has an invalid account id (%d)!",
					t_char->getName(), t_char->getId(), t_accId);

				return 0;
			}

			t_char->m_account->setCharacter(t_place, t_char);

			return t_char;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getCharacter_C(const char *)");
	}
#endif

	return 0;
}

bool ICharacterManager::createCharacter_C(ICharPlayer *_player, s32 _place,
										  const char *_name, E_SEX _sex, s32 _hairType, s32 _hairColor,
										  s32 _faceType, ICharCharacterSettings *_settings)
{
	FDASSERT(_player);
	FDASSERT(_name);
	FDASSERT(_place >= 0 && _place < 3);
	FDASSERT(_sex == sex(_sex));
	FDASSERT(_hairType == hair(_hairType));
	FDASSERT(_faceType == face(_faceType));
	FDASSERT(_settings);

	const AccountPtr &t_acc = _player->getAccount();

	sdk::stringc t_charName = xescape(_name);

	if (m_dbc->query(
		"INSERT INTO characters (account,name,place,sex,hairtype,haircolor,facetype,"
		"stat_str,stat_sta,stat_dex,stat_int,statpoints,creation) VALUES "
		"('%d','%s','%u','%d','%d','%d','%d','%d','%d','%d','%d','%d','%I64d')",
		t_acc->getId(), t_charName.c_str(), _place, _sex, _hairType, _hairColor, _faceType,
		_settings->BaseStr, _settings->BaseSta, _settings->BaseDex, _settings->BaseInt,
		_settings->BaseStatPoints, CTime::seconds()))
	{
		CharacterPtr t_char = getCharacter_C(t_charName.c_str());

		//creation successful
		if (t_char)
		{
			//create start items
			if (!m_itemMngr->createEquipment_C(t_char, _settings->StartItems))
			{
				Log::write(LOG_WARNING, "Could not create a new character's equipment!");
			}

			t_acc->setCharacter(_place, t_char);

			//load start items
			if (m_itemMngr->getEquipment_C(_player, _place))
			{
				return true;
			}
			else
			{
				Log::write(LOG_ERROR, "A new character's start equipment could not be loaded!");
			}
		}
		else
		{
			Log::write(LOG_ERROR, "A character could not be created!");
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("createCharacter_C");
	}
#endif

	return false;
}

bool ICharacterManager::deleteCharacter_C(const CharacterPtr &_char)
{
	FDASSERT(_char);

	if (m_dbc->query(
		"DELETE FROM characters WHERE id='%d' LIMIT 1",
		_char->getId()))
	{
		if (m_dbc->getAffectedRows() == 1)
		{
			return m_dbc->query(
				"DELETE FROM items WHERE owner='%d'; "
				"DELETE FROM mails WHERE receiver='%d';",
				_char->getId(), _char->getId());
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("deleteCharacter_C");
	}
#endif

	return false;
}

bool ICharacterManager::getCharacters_C(ICharPlayer *_player)
{
	FDASSERT(_player);
	FDASSERT(_player->getAccount());

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,place,sex,job,hairtype,haircolor,facetype,level,"
		"stat_str,stat_sta,stat_dex,stat_int FROM characters "
		"WHERE account='%d' LIMIT 3",
		_player->getAccount()->getId()) &&
		m_dbc->getResult(t_result))
	{
		while (t_result.nextRow())
		{
			CharacterPtr t_char = getCharacter_C(t_result.getFieldS32(0), false).get();

			if (!t_char)
			{
				t_char = _newCharacter();
			}

			t_char->m_id = t_result.getFieldS32(0);
			t_char->m_name = t_result.getFieldString(1);
			t_char->m_place = Limit(t_result.getFieldS32(2), 0, 2);
			t_char->m_sex = E_SEX(t_result.getFieldU32(3));
			t_char->m_job = E_JOB(t_result.getFieldU32(4));
			t_char->m_hairType = t_result.getFieldS32(5);
			t_char->m_hairColor = t_result.getFieldS32(6);
			t_char->m_faceType = t_result.getFieldS32(7);
			t_char->m_level = t_result.getFieldS32(8);
			t_char->m_str = t_result.getFieldS32(9);
			t_char->m_sta = t_result.getFieldS32(10);
			t_char->m_dex = t_result.getFieldS32(11);
			t_char->m_int = t_result.getFieldS32(12);

			_player->getAccount()->setCharacter(static_cast<u32>(t_char->m_place), t_char);
		}

		for (u32 i = 0; i < 3; ++i)
		{
			if (_player->getAccount()->getCharacter(i))
			{
				m_itemMngr->getEquipment_C(_player, i);
			}
		}

		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getCharacters_C");
	}
#endif

	return false;
}


//:: WORLD SERVER FUNCTIONS ::

CharacterPtr ICharacterManager::getCharacter_W(ID _id)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_chars, i)
	{
		if (m_chars[i]->getId() == _id)
			return m_chars[i];
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,account,place,sex,job,hairtype,haircolor,facetype,level,"
		"stat_str,stat_sta,stat_dex,stat_int,statpoints,posx,posy,posz,world,exp,"
		"skillpoints,hp,mp,fp,penya,pvp,pk,disposition FROM characters WHERE id='%d';",
		_id) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			CharacterPtr t_char = _newCharacter();

			t_char->m_id = t_result.getFieldS32(0);
			t_char->m_name = t_result.getFieldString(1);

			ID t_accId = t_result.getFieldS32(2);
			t_char->m_place = t_result.getFieldS32(3);

			t_char->m_sex = E_SEX(t_result.getFieldU32(4));
			t_char->m_job = E_JOB(t_result.getFieldU32(5));
			t_char->m_hairType = t_result.getFieldS32(6);
			t_char->m_hairColor = t_result.getFieldS32(7);
			t_char->m_faceType = t_result.getFieldS32(8);
			t_char->m_level = t_result.getFieldS32(9);
			t_char->m_str = t_result.getFieldS32(10);
			t_char->m_sta = t_result.getFieldS32(11);
			t_char->m_dex = t_result.getFieldS32(12);
			t_char->m_int = t_result.getFieldS32(13);
			t_char->m_statPoints = t_result.getFieldS32(14);

			//position
			t_char->m_pos = CPoint(
				t_result.getFieldF32(15),
				t_result.getFieldF32(16),
				t_result.getFieldF32(17));

			t_char->m_worldId = t_result.getFieldS32(18);
			t_char->m_exp = t_result.getFieldS64(19);
			t_char->m_skillPoints = t_result.getFieldS32(20);
			t_char->setHp(t_result.getFieldS32(21));
			t_char->setMp(t_result.getFieldS32(22));
			t_char->setFp(t_result.getFieldS32(23));
			t_char->setPenya(t_result.getFieldS32(24));
			t_char->setPvpPoints(t_result.getFieldS32(25));
			t_char->setPkPoints(t_result.getFieldS32(26));
			t_char->setDisposition(t_result.getFieldS32(27));

			AccountPtr t_account = m_accMngr->getAccount_W(t_accId);

			if (t_account)
			{
				t_char->m_account = t_account;

				t_account->setCharacter(t_char->m_place, t_char);

				return t_char;
			}
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getCharacter_W(ID)");
	}
#endif

	return 0;
}

CharacterPtr ICharacterManager::getCharacter_W(const char *_name)
{
	FDASSERT(m_dbc);
	FDASSERT(_name);

	FOR_EACH (m_chars, i)
	{
		if (strcmp(m_chars[i]->getName(), _name) == 0)
			return m_chars[i];
	}

	sdk::stringc t_charName = xescape(_name);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,account,place,sex,job,hairtype,haircolor,facetype,level,"
		"stat_str,stat_sta,stat_dex,stat_int,statpoints,posx,posy,posz,world,exp,"
		"skillpoints,hp,mp,fp,penya,pvp,pk,disposition FROM characters WHERE name='%s';",
		t_charName.c_str()) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			CharacterPtr t_char = _newCharacter();

			t_char->m_id = t_result.getFieldS32(0);
			t_char->m_name = t_result.getFieldString(1);

			ID t_accId = t_result.getFieldS32(2);
			t_char->m_place = t_result.getFieldS32(3);

			t_char->m_sex = E_SEX(t_result.getFieldU32(4));
			t_char->m_job = E_JOB(t_result.getFieldU32(5));
			t_char->m_hairType = t_result.getFieldS32(6);
			t_char->m_hairColor = t_result.getFieldS32(7);
			t_char->m_faceType = t_result.getFieldS32(8);
			t_char->m_level = t_result.getFieldS32(9);
			t_char->m_str = t_result.getFieldS32(10);
			t_char->m_sta = t_result.getFieldS32(11);
			t_char->m_dex = t_result.getFieldS32(12);
			t_char->m_int = t_result.getFieldS32(13);
			t_char->m_statPoints = t_result.getFieldS32(14);

			//position
			t_char->m_pos = CPoint(
				t_result.getFieldF32(15),
				t_result.getFieldF32(16),
				t_result.getFieldF32(17));

			t_char->m_worldId = t_result.getFieldS32(18);
			t_char->m_exp = t_result.getFieldS64(19);
			t_char->m_skillPoints = t_result.getFieldS32(20);
			t_char->setHp(t_result.getFieldS32(21));
			t_char->setMp(t_result.getFieldS32(22));
			t_char->setFp(t_result.getFieldS32(23));
			t_char->setPenya(t_result.getFieldS32(24));
			t_char->setPvpPoints(t_result.getFieldS32(25));
			t_char->setPkPoints(t_result.getFieldS32(26));
			t_char->setDisposition(t_result.getFieldS32(27));

			AccountPtr t_account = m_accMngr->getAccount_W(t_accId);

			if (t_account)
			{
				t_char->m_account = t_account;

				t_account->setCharacter(t_char->m_place, t_char);

				return t_char;
			}
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getCharacter_W(const char *)");
	}
#endif

	return 0;
}

bool ICharacterManager::saveCharacter_W(const CharacterPtr &_char)
{
	FDASSERT(_char);

	return _saveCharacter_W(_char.get());
}

bool ICharacterManager::saveCharacter_onlineStatus_W(const CharacterPtr &_char)
{
	FDASSERT(_char);

	return _saveCharacter_onlineStatus_W(_char.get());
}

bool ICharacterManager::save_W()
{
	FOR_EACH (m_chars, i)
	{
		if (!_saveCharacter_W(m_chars[i]))
		{
			return false;
		}
	}

	return true;
}

CharacterPtr ICharacterManager::_newCharacter()
{
	return CharacterPtr(new ICharacter(this));
}

bool ICharacterManager::_saveCharacter_W(const CharacterPtr &_char)
{
	FDASSERT(_char);

	if (m_dbc->query("UPDATE characters SET name='%s',sex='%d',job='%d',hairtype='%d',haircolor='%d',"
		"facetype='%d',level='%d',stat_str='%d',stat_sta='%d',stat_dex='%d',stat_int='%d',hp='%d',"
		"mp='%d',fp='%d',statpoints='%d',posx='%f',posy='%f',posz='%f',world='%d',exp='%I64d',"
		"skillpoints='%d',penya='%d',pvp='%d',pk='%d',disposition='%d' WHERE id='%d' LIMIT 1",
		_char->getName(), _char->getSex(), _char->getJob(), _char->getHairType(), _char->getHairColor(),
		_char->getFaceType(), _char->getLevel(), _char->getStr(), _char->getSta(), _char->getDex(),
		_char->getInt(), _char->getHp(), _char->getMp(), _char->getFp(),_char->getStatPoints(),
		_char->getPosition().X, _char->getPosition().Y,	_char->getPosition().Z, _char->getWorldId(),
		_char->getExp(), _char->getSkillPoints(), _char->getPenya(), _char->getPvpPoints(),
		_char->getPkPoints(), _char->getDisposition(), _char->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("_saveCharacter_W");
	}
#endif

	return true;
}

bool ICharacterManager::_saveCharacter_onlineStatus_W(const CharacterPtr &_char)
{
	FDASSERT(_char);

	if (m_dbc->query("UPDATE characters SET online='%d' WHERE id='%d' LIMIT 1",
		s32(_char->isOnline() ? 1 : 0), _char->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("_saveCharacter_onlineStatus_W");
	}
#endif

	return true;
}