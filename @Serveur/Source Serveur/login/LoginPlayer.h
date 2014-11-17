#ifndef LOGINPLAYER_H
#define LOGINPLAYER_H


#include "LoginMain.h"
#include "../shared/DatabaseObject.h"


class IAccount;


class ILoginPlayer
{
public:

	ILoginPlayer(s32 _id = 0, CNetClient *_client = 0);

	~ILoginPlayer();

	s32 getId() const;

	CNetClient *getClient();

	const AccountPtr &getAccount();

	void setAccount(const AccountPtr &_account);

private:

	s32 m_id;

	CNetClient *m_client;

	AccountPtr m_account;

};


#endif //LOGINPLAYER_H