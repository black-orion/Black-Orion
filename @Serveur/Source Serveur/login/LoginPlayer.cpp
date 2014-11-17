#include "LoginPlayer.h"
#include "../shared/Account.h"


ILoginPlayer::ILoginPlayer(s32 _id, CNetClient *_client)
	: m_id(_id)
	, m_client(_client)
	, m_account(0)
{
}

ILoginPlayer::~ILoginPlayer()
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

s32 ILoginPlayer::getId() const
{
	return m_id;
}

CNetClient *ILoginPlayer::getClient()
{
	return m_client;
}

const AccountPtr &ILoginPlayer::getAccount()
{
	return m_account;
}

void ILoginPlayer::setAccount(const AccountPtr &_account)
{
	m_account = _account;
}