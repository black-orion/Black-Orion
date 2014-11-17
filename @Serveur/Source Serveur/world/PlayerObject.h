#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H


#include "WorldMain.h"
#include "WorldObject.h"
#include "Creature.h"
#include "Inventory.h"
#include "PostBox.h"
#include "../shared/Character.h"


class INpcObject;
class IDropObject;
class IWorldDataManager;
class IParty;
class IWorldServer;


class IPlayerObject : public ICreature
{
public:

	enum E_FLAGS
	{
		FLAG_NONE        = 0x00000000,
		FLAG_INVINCIBLE  = 0x00000001,
		FLAG_INVISIBLE   = 0x00000002,
		FLAG_ONEHITKILL  = 0x00000004,
		FLAG_FROZEN      = 0x00000008,
		FLAG_INVINCIBLE2 = 0x00000020,
		FLAG_PK          = 0x00001000,
		FLAG_DISALLOWPVP = 0x00002000,
		FLAG_NEWMAIL     = 0x00008000,
		FLAG_DISABLEVIEW = 0x00020000,
		FLAG_SHOWWELCOME = 0x10000000
	};

	IPlayerObject(ID _id, IWorld *_world, IWorldPlayer *_player);

	~IPlayerObject();

	E_TYPE getType() const;

	IWorldPlayer *getPlayer();

	const AccountPtr &getAccount() const;

	const CharacterPtr &getCharacter() const;

	s32 getFlags() const;

	bool isFlag(E_FLAGS _which);

	s32 getMotion() const;

	RATE getExpRate() const;

	RATE getDropRate() const;

	RATE getPenyaRate() const;

	const NpcObjectPtr &getNpcTarget() const;

	const PetObjectPtr &getPet() const;

	void setPet(const PetObjectPtr &_pet);

	LVL getLevel() const;

	void setFlags(s32 _flags);

	void setFlag(E_FLAGS _which, bool _value);

	void toggleFlag(E_FLAGS _which);

	void setMotion(s32 _motion);

	void setNpcTarget(const NpcObjectPtr &_npc);

	void calculateStats();

	const AttackResult &attack(const CreaturePtr &_target, s32 _attackMotion = 30);

	void damage(AttackResult &_result, const CreaturePtr &_attacker);

	void kill(E_DEATH _type, const CreaturePtr &_killer = 0);

	void updateCharacter();

	void addMobExp(EXP _exp);

	bool canLevelUp() const;

	bool levelUp();

	bool changePenya(PENYA _new);

	bool changeExp(EXP _exp);

	bool changeJob(E_JOB _job);

	bool changeLevel(LVL _lvl);

	bool changeBanTime(Time _until);

	bool changeAccessLevel(IAccount::E_ACCESS_LEVEL _accessLevel);

	bool changePvpPoints(s32 _pvp);

	bool changePkPoints(s32 _pk);

	bool changeDisposition(s32 _disposition);

	bool isAllowedToTake(const DropObjectPtr &_drop);

	void teleport(const CPoint &_pos, IWorld *_world = 0);

	IInventory *getInventory();

	const IInventory *getInventory() const;

	IPostBox *getPostBox();

	const IPostBox *getPostBox() const;

	PartyPtr &getParty();

	const PartyPtr &getParty() const;

	void setParty(PartyPtr &_party);

	void partyInvite(const PlayerObjectPtr &_invitee);

	void partyInvitationAccepted(const PlayerObjectPtr &_invitee);

	void reviveLoadStar();

	void reviveOriginal();

	void reviveBySkill();

	void onWorldRemove();

	void onDestroy();

	void update();

	void onBaseStatChanged();

	void onStatRelatedChanged();

	u32 getSessionVarCount() const;

	CPair<std::string, std::string> &getSessionVar(u32 _num);

	const CPair<std::string, std::string> &getSessionVar(u32 _num) const;

	std::string &getSessionVar(const std::string &_name);

	void setSessionVar(u32 _num, const std::string &_name, const std::string &_value);

	void setSessionVar(const std::string &_name, const std::string &_value);

	bool isSessionVarSet(const std::string &_name);

	void eraseSessionVar(u32 _num);

	void eraseSessionVar(const std::string &_name);

	void clearSession();

private:

	IWorldPlayer *m_player;

	s32 m_flags;

	s32 m_motion;

	TimeMs m_nextRegenerationTime;

	NpcObjectPtr m_npcTarget;

	IInventory m_inv;

	IPostBox m_post;

	PartyPtr m_party;

	CArray<ID> m_invitees;

	PetObjectPtr m_pet;

	//session
	CMap<std::string, std::string> m_sessionVars;

	enum
	{
		BUF_SIZE = 2048
	};

	static char ms_buffer[BUF_SIZE];

	void _addItemStats(const ItemPackPtr &_item);

	s32 _calcWeaponAtk() const;

	void _addEquipDef(E_INVENTORY _equipType);

	bool _isCharacter() const;

	IWorldServer *_getServer();

	const IWorldSettings *_getSettings() const;

	const IWorldDataManager *_getWorldDataMngr() const;

};


#endif //PLAYEROBJECT_H
