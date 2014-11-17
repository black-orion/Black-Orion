#include "CharPlayer.h"
#include "../shared/Account.h"


ICharPlayer::ICharPlayer(s32 _id, CNetClient *_client)
	: m_id(_id)
	, m_client(_client)
	, m_account(0)
{
}

ICharPlayer::~ICharPlayer()
{
	if (m_client)
	{
		m_client->free();
	}

	if (m_account)
	{
		m_account->solve();
	}
}

s32 ICharPlayer::getId() const
{
	return m_id;
}

CNetClient *ICharPlayer::getClient()
{
	return m_client;
}

const AccountPtr &ICharPlayer::getAccount()
{
	return m_account;
}

CArray<const IItemData*> &ICharPlayer::getEquipment(u32 _char)
{
	FDASSERT(_char < ARRAY_SIZE(m_equip));

	return m_equip[_char];
}

void ICharPlayer::setAccount(const AccountPtr &_account)
{
	m_account = _account;
}
