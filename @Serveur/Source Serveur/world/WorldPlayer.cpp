#include "WorldPlayer.h"
#include "PlayerObject.h"
#include "World.h"
#include "WorldServer.h"
#include "../shared/Account.h"
#include "../shared/Character.h"
#include "../shared/PacketCreator.h"


char IWorldPlayer::ms_buffer[BUF_SIZE];

IWorldPlayer::IWorldPlayer(ID _id, CNetClient *_client)
	: m_id(_id)
	, m_client(_client)
	, m_account(0)
	, m_char(0)
	, m_object(0)
{
}

IWorldPlayer::~IWorldPlayer()
{
	if (m_client)
	{
		m_client->free();
	}

	if (m_object)
	{
		m_object->getWorld()->removeObject(m_object, true);
	}

	if (m_account)
	{
		m_account->solve();
	}
}

ID IWorldPlayer::getId() const
{
	return m_id;
}

CNetClient *IWorldPlayer::getClient()
{
	return m_client;
}

const AccountPtr &IWorldPlayer::getAccount()
{
	return m_account;
}

const CharacterPtr &IWorldPlayer::getCharacter()
{
	return m_char;
}

const PlayerObjectPtr &IWorldPlayer::getObject()
{
	return m_object;
}

void IWorldPlayer::setAccount(const AccountPtr &_account)
{
	m_account = _account;
}

void IWorldPlayer::setCharacter(const CharacterPtr &_char)
{
	m_char = _char;
}

void IWorldPlayer::setObject(const PlayerObjectPtr &_object)
{
	m_object = _object;
}

void IWorldPlayer::greenText(const char *_format, ...)
{
	FDASSERT(_format);

	va_list t_args;
	va_start(t_args, _format);
	vsnprintf(ms_buffer, BUF_SIZE - 1, _format, t_args);
	va_end(t_args);

	getClient()->send(IPacketCreator::greenText(ms_buffer));
}
