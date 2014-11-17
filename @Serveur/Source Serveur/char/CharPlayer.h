#ifndef CHARPLAYER_H
#define CHARPLAYER_H


#include "CharMain.h"
#include "../shared/DatabaseObject.h"


class IAccount;
class IItemData;


class ICharPlayer
{
public:

	ICharPlayer(s32 _id = 0, CNetClient *_client = 0);

	~ICharPlayer();

	s32 getId() const;

	CNetClient *getClient();

	const AccountPtr &getAccount();

	CArray<const IItemData*> &getEquipment(u32 _char);

	void setAccount(const AccountPtr &_account);

private:

	s32 m_id;

	CNetClient *m_client;

	AccountPtr m_account;

	CArray<const IItemData*> m_equip[3];

};


#endif //CHARPLAYER_H
