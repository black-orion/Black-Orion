#ifndef LOGINDATABASE_H
#define LOGINDATABASE_H


#include "LoginMain.h"
#include "../shared/Timed.h"


class IDatabaseConnection;


class ILoginDatabase : public ITimed
{
public:

	ILoginDatabase();
	~ILoginDatabase();
	bool init(IDatabaseConnection *_mySql);

	AccountPtr getAccount(const char *_name);
	bool createAccount(const char *_name, const char *_passwordHash, u32 _accessLevel);
	bool saveAccount(const AccountPtr &_account);

	void update();

private:

	IDatabaseConnection *m_mySql;
	CArray<AccountPtr> m_accounts;

	const AccountPtr &_newAccount();
};


#endif //LOGINDATABASE_H