#include "AccountManager.h"
#include "Account.h"
#include "DatabaseConnection.h"


IAccountManager::IAccountManager(IDatabaseConnection *_dbc)
	: m_dbc(_dbc)
{
}

IAccountManager::~IAccountManager()
{
}

void IAccountManager::clear()
{
	m_accounts.clear();
}

void IAccountManager::add(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	m_accounts.push_back(AccountPtr((IAccount*)_dbObj));
}

void IAccountManager::remove(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	FOR_EACH (m_accounts, i)
	{
		if (m_accounts[i] == _dbObj)
		{
			m_accounts[i].reset();
			m_accounts.erase_fast(i);
			return;
		}
	}

	FDASSERT(false && "Invalid _dbObj");
}

void IAccountManager::update()
{
	FOR_EACH (m_accounts, i)
	{
		if (m_accounts[i]->isUnique())
		{
			m_accounts[i].reset();
			m_accounts.erase_fast(i);
			if (i)
				--i;
		}
	}
}

u32 IAccountManager::getAccountNumber() const
{
	return m_accounts.size();
}

//:: GENERAL ::

bool IAccountManager::saveAccount_accessLevel(const AccountPtr &_acc)
{
	FDASSERT(_acc);

	if (m_dbc->query(
		"UPDATE comptes SET accesslevel='d' WHERE id='%d' LIMIT 1",
		_acc->m_access, _acc->m_id))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("saveAccount_accessLevel");
	}
#endif

	return false;
}

bool IAccountManager::saveAccount_banTime(const AccountPtr &_acc)
{
	FDASSERT(_acc);

	if (m_dbc->query(
		"UPDATE comptes SET bantime='%I64d' WHERE id='%d' LIMIT 1",
		_acc->m_bantime, _acc->m_id))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("saveAccount_banTime");
	}
#endif

	return false;
}


//:: LOGIN SERVER FUNCTIONS ::

AccountPtr IAccountManager::getAccount_L(ID _id)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_accounts, i)
	{
		if (m_accounts[i]->getId() == _id)
			return m_accounts[i];
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password,accesslevel,lastlogin,bantime FROM comptes "
		"WHERE id='%d'", _id) &&
		m_dbc->getResult(t_result))
	{
		AccountPtr t_account = _newAccount();

		t_account->setDatabaseStateLoaded();

		t_account->m_id = t_result.getFieldS32(0);
		t_account->m_name = t_result.getFieldString(1);
		t_account->m_password = t_result.getFieldString(2);
		t_account->m_access = IAccount::E_ACCESS_LEVEL(t_result.getFieldS32(3));
		t_account->m_lastlogin = t_result.getFieldS64(4);
		t_account->m_bantime = t_result.getFieldS64(5);

		return t_account;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_L(ID)");
	}
#endif

	return 0;
}

AccountPtr IAccountManager::getAccount_L(const char *_name)
{
	FDASSERT(m_dbc);
	FDASSERT(_name);

	FOR_EACH (m_accounts, i)
	{
		if (xstricmp(m_accounts[i]->getName(), _name) == 0)
			return m_accounts[i];
	}

	sdk::stringc t_accName = xescape(_name);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password,accesslevel,lastlogin,bantime FROM comptes "
		"WHERE name='%s' LIMIT 1",
		t_accName.c_str()) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			AccountPtr t_account = _newAccount();

			t_account->setDatabaseStateLoaded();

			t_account->m_id = t_result.getFieldS32(0);
			t_account->m_name = t_result.getFieldString(1);
			t_account->m_password = t_result.getFieldString(2);
			t_account->m_access = IAccount::E_ACCESS_LEVEL(t_result.getFieldS32(3));
			t_account->m_lastlogin = t_result.getFieldS64(4);
			t_account->m_bantime = t_result.getFieldS64(5);

			return t_account;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_L(const char *)");
	}
#endif

	return 0;
}

AccountPtr IAccountManager::createAccount_L(const char *_name, const char *_passwordHash, u32 _accessLevel)
{
	FDASSERT(_name);
	FDASSERT(_passwordHash);

	sdk::stringc t_accName = xescape(_name);
	sdk::stringc t_pwHash = xescape(_passwordHash);

	if (t_accName.size() < 3 ||
		t_accName.size() > 16)
	{
		return 0;
	}

	if (t_pwHash.size() != 32)
	{
		return 0;
	}

	if (m_dbc->query(
		"INSERT INTO comptes (name,password,accesslevel,creation) VALUES ('%s','%s','%u','%I64d')",
		t_accName.c_str(), t_pwHash.c_str(), _accessLevel, CTime::seconds()))
	{
		return getAccount_L(t_accName.c_str());
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("createAccount_L");
	}
#endif

	return 0;
}

bool IAccountManager::saveAccount_L(const AccountPtr &_acc)
{
	FDASSERT(_acc);

	if (m_dbc->query(
		"UPDATE comptes SET lastlogin='%I64d' WHERE id='%d' LIMIT 1",
		_acc->m_lastlogin, _acc->m_id))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("saveAccount_L");
	}
#endif

	return false;
}


//:: CHAR SERVER FUNCTIONS ::

AccountPtr IAccountManager::getAccount_C(ID _id)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_accounts, i)
	{
		if (m_accounts[i]->getId() == _id)
			return m_accounts[i];
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password FROM comptes WHERE id='%d'",
		_id) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			AccountPtr t_account = _newAccount();

			t_account->setDatabaseStateLoaded();

			t_account->m_id = t_result.getFieldS32(0);
			t_account->m_name = t_result.getFieldString(1);
			t_account->m_password = t_result.getFieldString(2);

			return t_account;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_C(ID)");
	}
#endif

	return 0;
}

AccountPtr IAccountManager::getAccount_C(const char *_name)
{
	FDASSERT(m_dbc);
	FDASSERT(_name);

	FOR_EACH (m_accounts, i)
	{
		if (xstricmp(m_accounts[i]->getName(), _name) == 0)
			return AccountPtr(m_accounts[i]);
	}

	sdk::stringc t_accName = xescape(_name);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password FROM comptes WHERE name='%s'",
		t_accName.c_str()) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			AccountPtr t_account = _newAccount();

			t_account->setDatabaseStateLoaded();

			t_account->m_id = t_result.getFieldS32(0);
			t_account->m_name = t_result.getFieldString(1);
			t_account->m_password = t_result.getFieldString(2);

			return t_account;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_C(const char *)");
	}
#endif

	return 0;
}


//:: WORLD SERVER FUNCTIONS ::

AccountPtr IAccountManager::getAccount_W(ID _id)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_accounts, i)
	{
		if (m_accounts[i]->getId() == _id)
			return AccountPtr(m_accounts[i]);
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password,accesslevel,lastlogin,bantime,points FROM comptes "
		"WHERE id='%d'",
		_id) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			AccountPtr t_account = _newAccount();

			t_account->setDatabaseStateLoaded();

			t_account->m_id = t_result.getFieldS32(0);
			t_account->m_name = t_result.getFieldString(1);
			t_account->m_password = t_result.getFieldString(2);
			t_account->m_access = IAccount::E_ACCESS_LEVEL(t_result.getFieldS32(3));
			t_account->m_lastlogin = t_result.getFieldS64(4);
			t_account->m_bantime = t_result.getFieldS64(5);
			t_account->m_points = t_result.getFieldU32(6);

			return t_account;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_W(ID)");
	}
#endif

	return AccountPtr(0);
}

AccountPtr IAccountManager::getAccount_W(const char *_name)
{
	FDASSERT(m_dbc);
	FDASSERT(_name);

	FOR_EACH (m_accounts, i)
	{
		if (xstricmp(m_accounts[i]->getName(), _name) == 0)
			return AccountPtr(m_accounts[i]);
	}

	sdk::stringc t_accName = xescape(_name);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,name,password,accesslevel,lastlogin,bantime,points FROM comptes "
		"WHERE name='%s';",
		t_accName.c_str()) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			AccountPtr t_account = _newAccount();

			t_account->setDatabaseStateLoaded();

			t_account->m_id = t_result.getFieldS32(0);
			t_account->m_name = t_result.getFieldString(1);
			t_account->m_password = t_result.getFieldString(2);
			t_account->m_access = IAccount::E_ACCESS_LEVEL(t_result.getFieldS32(3));
			t_account->m_lastlogin = t_result.getFieldS64(4);
			t_account->m_bantime = t_result.getFieldS64(5);
			t_account->m_points = t_result.getFieldU32(6);

			return AccountPtr(t_account);
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getAccount_W(const char *)");
	}
#endif

	return AccountPtr(0);
}

bool IAccountManager::saveAccount_W(const AccountPtr &_acc)
{
	FDASSERT(_acc);

	return _saveAccount_W(_acc.get());
}

bool IAccountManager::save_W()
{
	FOR_EACH (m_accounts, i)
	{
		if (!_saveAccount_W(m_accounts[i]))
			return false;
	}

	return true;
}

AccountPtr IAccountManager::_newAccount()
{
	return AccountPtr(new IAccount(this));
}

bool IAccountManager::_saveAccount_W(const AccountPtr &_acc)
{
	FDASSERT(_acc);

	if (m_dbc->query(
		"UPDATE comptes SET points='%u' WHERE id='%d' LIMIT 1",
		_acc->m_points, _acc->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("_saveAccount_W");
	}
#endif

	return false;
}
