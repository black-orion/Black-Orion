#include "LoginDatabase.h"
#include "../shared/Account.h"
#include "../shared/DatabaseConnection.h"
#include "../shared/Log.h"


ILoginDatabase::ILoginDatabase()
	: m_mySql(0)
{
}

ILoginDatabase::~ILoginDatabase()
{
}

bool ILoginDatabase::init(IDatabaseConnection *_mySql)
{
	m_mySql = _mySql;
	return (m_mySql != 0);
}

AccountPtr ILoginDatabase::getAccount(const char *_name)
{
	FDASSERT(_name);
	FDASSERT(m_mySql);

	FOR_EACH (m_accounts, i)
	{
		if (xstricmp(m_accounts[i]->getName(), _name) == 0)
		{
			return m_accounts[i];
		}
	}

	IQueryResult t_result;

	sdk::stringc t_name = m_mySql->escapeString(_name);

	if (m_mySql->query(
		"SELECT id,name,password,accesslevel,lastlogin,bantime FROM comptes "
		"WHERE name='%s' LIMIT 1",
		t_name.c_str()) &&
		m_mySql->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			const AccountPtr &t_account = _newAccount();

			t_account->setId         ( t_result.getFieldS32   (0) );
			t_account->setName       ( t_result.getFieldString(1) );
			t_account->setPassword   ( t_result.getFieldString(2) );
			t_account->setAccessLevel( IAccount::accessLevel(t_result.getFieldS32(3)) );
			t_account->setLastLogin  ( t_result.getFieldS64   (4) );
			t_account->setBanTime    ( t_result.getFieldS64   (5) );

			return t_account;
		}
	}
	else
	{
		Log::write(LOG_ERROR, "MySQL: %s", m_mySql->getError());
	}

	return 0;
}

bool ILoginDatabase::createAccount(const char *_name, const char *_passwordHash, u32 _accessLevel)
{
	FDASSERT(_name);
	FDASSERT(_passwordHash);
	FDASSERT(m_mySql);

	sdk::stringc t_name = m_mySql->escapeString(_name);
	sdk::stringc t_password = m_mySql->escapeString(_passwordHash);

	if (
		m_mySql->query(
		"INSERT INTO comptes(name,password,accesslevel,creation) VALUES ('%s','%s','%u','%lld')",
		t_name.c_str(), t_password.c_str(), _accessLevel, CTime::seconds()))
	{
		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "MySQL: %s", m_mySql->getError());
		return false;
	}
}

bool ILoginDatabase::saveAccount(const AccountPtr &_account)
{
	FDASSERT(_name);
	FDASSERT(_account);

	if (
		m_mySql->query(
		"UPDATE comptes SET lastlogin='%lld' WHERE id='%d' LIMIT 1",
		_account->getLastLogin(), _account->getId()))
	{
		return true;
	}
	else
	{
		Log::write(LOG_ERROR, "MySQL: %s", m_mySql->getError());
		return false;
	}
}

void ILoginDatabase::update()
{
}

const AccountPtr &ILoginDatabase::_newAccount()
{
	m_accounts.push_back(AccountPtr(new IAccount()));
	return m_accounts.last();
}
