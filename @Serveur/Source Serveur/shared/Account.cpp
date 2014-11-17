#include "Account.h"
#include "Character.h"
#include "Log.h"


IAccount::IAccount(IAccountManager *_manager)
	: IDatabaseObject((IDatabaseManager*)_manager)
	, m_id(0)
	, m_name("")
	, m_password("")
	, m_access(ACC_PLAYER)
	, m_points(0)
	, m_lastlogin(0)
	, m_bantime(0)
	, m_online(false)
	, m_state(STATE_LOGIN)
{
}

IAccount::~IAccount()
{
#ifdef SDEBUG
	Log::write(LOG_DEBUG, "IAccount dtor %d", m_id);
#endif
}

void IAccount::reset()
{
	m_id = 0;
	m_name.clear();
	m_password.clear();
	m_access = ACC_PLAYER;
	m_points = 0;
	m_lastlogin = 0;
	m_bantime = 0;
	m_online = false;
	m_state = STATE_LOGIN;

	solve();
}

void IAccount::solve()
{
	if (m_characters[0])
	{
		m_characters[0]->setAccount(0);
		m_characters[0].reset();
	}

	if (m_characters[1])
	{
		m_characters[1]->setAccount(0);
		m_characters[1].reset();
	}

	if (m_characters[2])
	{
		m_characters[2]->setAccount(0);
		m_characters[2].reset();
	}
}

ID IAccount::getId() const
{
	return m_id;
}

const char *IAccount::getName() const
{
	return m_name.c_str();
}

const char *IAccount::getPassword() const
{
	return m_password.c_str();
}

IAccount::E_ACCESS_LEVEL IAccount::getAccessLevel() const
{
	return m_access;
}

u32 IAccount::getPoints() const
{
	return m_points;
}

Time IAccount::getLastLogin() const
{
	return m_lastlogin;
}

Time IAccount::getBanTime() const
{
	return m_bantime;
}

const CharacterPtr &IAccount::getCharacter(u32 _num)
{
	FDASSERT(_num < 3);

	return m_characters[_num];
}

IAccount::E_STATE IAccount::getState() const
{
	return m_state;
}

bool IAccount::isCharOn(const char *_charname) const
{
	if (m_characters[0] &&
		strcmp(m_characters[0]->getName(), _charname) == 0)
	{
		return true;
	}

	if (m_characters[1] &&
		strcmp(m_characters[1]->getName(), _charname) == 0)
	{
		return true;
	}

	if (m_characters[2] &&
		strcmp(m_characters[2]->getName(), _charname) == 0)
	{
		return true;
	}

	return false;
}

bool IAccount::isCharOn(const CharacterPtr &_char) const
{
	if (m_characters[0] == _char)
	{
		return true;
	}

	if (m_characters[1] == _char)
	{
		return true;
	}

	if (m_characters[2] == _char)
	{
		return true;
	}

	return false;
}

bool IAccount::isOnline() const
{
	return m_online;
}

void IAccount::setId(ID _id)
{
	m_id = _id;
}

void IAccount::setName(const char *_name)
{
	m_name = _name;
}

void IAccount::setPassword(const char *_password)
{
	m_password = _password;
}

void IAccount::setPoints(u32 _points)
{
	m_points = _points;

	if (m_points < 0)
	{
		m_points = 0;
	}
}

void IAccount::setAccessLevel(E_ACCESS_LEVEL _access)
{
	m_access = _access;
}

void IAccount::setLastLogin(Time _time)
{
	m_lastlogin = _time;
}

void IAccount::setBanTime(Time _time)
{
	m_bantime = _time;
}

void IAccount::setCharacter(u32 _num, const CharacterPtr &_char)
{
	FDASSERT(_num < 3);

	m_characters[_num] = _char;
}

void IAccount::setOnline(bool _online)
{
	m_online = _online;
}

void IAccount::setState(E_STATE _state)
{
	FDASSERT(
		_state == STATE_LOGIN ||
		_state == STATE_CHAR ||
		_state == STATE_WORLD);

	m_state = _state;
}

void IAccount::updateLastLogin()
{
	m_lastlogin = CTime::seconds();
}

void IAccount::removeCharacter(const CharacterPtr &_char)
{
	FDASSERT(_char);

	if (m_characters[0] == _char)
	{
		m_characters[0].reset();
	}

	else if (m_characters[1] == _char)
	{
		m_characters[1].reset();
	}

	else if (m_characters[2] == _char)
	{
		m_characters[2].reset();
	}
}

IAccount::E_ACCESS_LEVEL IAccount::accessLevel(s32 _id)
{
	return E_ACCESS_LEVEL(Limit<s32>(_id, ACC_MINIMUM, ACC_MAXIMUM));
}