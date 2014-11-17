#include "Party.h"
#include "PlayerObject.h"
#include "WorldPlayer.h"
#include "../shared/PacketCreator.h"


IParty::IParty()
	: m_id(0)
	, m_level(1)
	, m_adv(false)
	, m_exp(0)
	, m_points(0)
{
}

IParty::IParty(ID _id)
	: m_id(_id)
	, m_level(1)
	, m_adv(false)
	, m_exp(0)
	, m_points(0)
{
}

bool IParty::start(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_member)
{
	FDASSERT(_leader);
	FDASSERT(_member);

	m_members.push_back(_leader);
	m_members.push_back(_member);
	_leader->setParty(PartyPtr(this));
	_member->setParty(PartyPtr(this));

	_leader->getPlayer()->getClient()->send(IPacketCreator::partyUpdate(_leader, _leader, _member, PartyPtr(this)));
	_leader->getPlayer()->getClient()->send(IPacketCreator::partyUpdate(_member, _leader, _member, PartyPtr(this)));
	return true;
}

ID IParty::getId() const
{
	return m_id;
}

const char *IParty::getName() const
{
	return m_name.c_str();
}

LVL IParty::getLevel() const
{
	return m_level;
}

bool IParty::isAdvanced() const
{
	return m_adv;
}

s32 IParty::getExp() const
{
	return m_exp;
}

s32 IParty::getPoints() const
{
	return m_points;
}

u32 IParty::getMemberCount() const
{
	return m_members.size();
}

bool IParty::isFull() const
{
	return (getMemberCount() == MAX_MEMBERS);
}

const PlayerObjectPtr &IParty::getMember(u32 _num) const
{
	FDASSERT(_num < getMemberCount());

	return m_members[_num];
}

const PlayerObjectPtr &IParty::getLeader() const
{
	FDASSERT(!m_members.empty());

	return m_members[LEADER_POSITION];
}

bool IParty::isMember(const PlayerObjectPtr &_player) const
{
	FDASSERT(_player);

	return m_members.contains(_player);
}

void IParty::setName(const char *_name)
{
	FDASSERT(_name);

	m_name = _name;
}

void IParty::setLevel(LVL _level)
{
	m_level = _level;
}

void IParty::setExp(s32 _exp)
{
	m_exp = _exp;
}

void IParty::setPoints(s32 _points)
{
	m_points = _points;
}

void IParty::addMember(const PlayerObjectPtr &_player)
{
	FDASSERT(_player);

	if (!isFull())
	{
		m_members.push_back(_player);
		_player->setParty(PartyPtr(this));

		//_player->getPlayer()->getClient()->send(IPacketCreator::partyUpdate(_player, this));
	}
}

void IParty::removeMember(ID _objId)
{
	FOR_EACH (m_members, i)
	{
		if (m_members[i]->getId() == _objId)
		{
			//m_members[i]->getPlayer()->getClient()->send(IPacketCreator::partyLeft(m_members[i]));
			return;
		}
	}
}

void IParty::removeMemberSilently(ID _objId)
{
	FOR_EACH (m_members, i)
	{
		if (m_members[i]->getId() == _objId)
		{
			//m_members[i]->getPlayer()->getClient()->send(IPacketCreator::partyLeft(m_members[i]));
			return;
		}
	}
}

void IParty::transferLeadership(ID _newLeaderId)
{
}

void IParty::disband()
{
}

void IParty::sendToMembers(const CByteArray &_packet)
{
	FOR_EACH (m_members, i)
	{
		m_members[i]->getPlayer()->getClient()->send(_packet);
	}
}