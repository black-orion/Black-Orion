#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H


#include "Base.h"
#include "DatabaseManager.h"
#include "DatabaseObject.h"


class IAccount;
class IDatabaseConnection;


class IAccountManager : public IDatabaseManager
{
public:

	IAccountManager(IDatabaseConnection *_dbc);

	~IAccountManager();

	void clear();

	void add(IDatabaseObject *_dbObj);

	void remove(IDatabaseObject *_dbObj);

	void update();

	u32 getAccountNumber() const;


	//:: GENERAL ::

	bool saveAccount_accessLevel(const AccountPtr &_acc);

	bool saveAccount_banTime(const AccountPtr &_acc);


	//:: LOGIN SERVER FUNCTIONS ::

	AccountPtr getAccount_L(ID _id);

	AccountPtr getAccount_L(const char *_name);

	AccountPtr createAccount_L(const char *_name, const char *_passwordHash, u32 _accessLevel);

	bool saveAccount_L(const AccountPtr &_acc);


	//:: CHAR SERVER FUNCTIONS ::

	AccountPtr getAccount_C(ID _id);

	AccountPtr getAccount_C(const char *_name);


	//:: WORLD SERVER FUNCTIONS ::

	AccountPtr getAccount_W(ID _id);

	AccountPtr getAccount_W(const char *_name);

	bool saveAccount_W(const AccountPtr &_acc);

	bool save_W();

private:

	IDatabaseConnection *m_dbc;

	CArray<AccountPtr> m_accounts;

	AccountPtr _newAccount();

	bool _saveAccount_W(const AccountPtr &_acc);

};


#endif //ACCOUNTMANAGER_H
