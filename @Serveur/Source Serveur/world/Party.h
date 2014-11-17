#ifndef PARTY_H
#define PARTY_H


#include "WorldMain.h"
#include "../shared/RefCounted.h"


class IPlayerObject;


class IParty : public IRefCounted
{
public:

	enum
	{
		LEADER_POSITION = 0,

		MAX_MEMBERS = 8
	};

	IParty();
	IParty(ID _id);

	bool start(const PlayerObjectPtr &_leader, const PlayerObjectPtr &_member);

	ID getId() const;

	const char *getName() const;

	LVL getLevel() const;

	bool isAdvanced() const;

	s32 getExp() const;

	s32 getPoints() const;

	u32 getMemberCount() const;

	bool isFull() const;

	const PlayerObjectPtr &getMember(u32 _num) const;

	const PlayerObjectPtr &getLeader() const;

	bool isMember(const PlayerObjectPtr &_player) const;

	void setName(const char *_name);

	void setLevel(LVL _level);

	void setExp(s32 _exp);

	void setPoints(s32 _points);

	void addMember(const PlayerObjectPtr &_player);

	void removeMember(ID _objId);

	void removeMemberSilently(ID _objId);

	void transferLeadership(ID _newLeaderId);

	void disband();

	void sendToMembers(const CByteArray &_packet);

private:

	ID m_id;

	sdk::stringc m_name;

	CArray<PlayerObjectPtr> m_members;

	LVL m_level;

	bool m_adv;

	s32 m_exp;

	s32 m_points;

	//item and exp distribution type

};


#endif //PARTY_H
