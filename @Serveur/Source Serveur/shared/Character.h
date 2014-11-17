#ifndef CHARACTER_H
#define CHARACTER_H


#include "Base.h"
#include "E_CHAR.h"
#include "DatabaseObject.h"


class ICharacterManager;
class IDatabaseManager;
class IAccount;


//Eigenschaften (r = lesen, w = schreiben)

//                  Login   Char    World
//----------------------------------------
//	Id                -      (r)     (r)
//	Name              -      (r)     (r/w)
//  Account           -      (r)     (r)
//  Level             -      (r)     (r/w)
//  Exp               -      (r)     (r/w)
//  Job               -      (r)     (r/w)
//  Sex               -      (r)     (r/w)
//  Str/Sta..         -      (r)     (r/w)
//  ...               "       "       "
//----------------------------------------
// SELECT                     x       x
// UPDATE                             x
// INSERT                     x
// DELETE                     x


class ICharacter : public IDatabaseObject
{
public:

	enum E_STATE
	{
		STATE_CHAR,
		STATE_WORLD
	};

	ICharacter(ICharacterManager *_manager);

	~ICharacter();

	void reset();

	void solve();

	ID getId() const;

	const char *getName() const;

	const AccountPtr &getAccount();

	bool isOnline() const;

	s32 getPlace() const;

	LVL getLevel() const;

	EXP getExp() const;

	E_JOB getJob() const;

	E_SEX getSex() const;

	s32 getFaceType() const;

	s32 getHairType() const;

	s32 getHairColor() const;

	PENYA getPenya() const;

	PENYA getMoneyUntilMaximum() const;

	PENYA64 getBankPenya() const;

	const CPoint &getPosition() const;

	s16 getStatPoints() const;

	s32 getHp() const;

	s32 getMp() const;

	s32 getFp() const;

	s32 getStr() const;

	s32 getSta() const;

	s32 getDex() const;

	s32 getInt() const;

	s32 getSkillPoints() const;

	E_STATE getState() const;

	ID getWorldId() const;

	s16 getRotation() const;

	s16 getSize() const;

	s32 getPvpPoints() const;

	s32 getPkPoints() const;

	s32 getDisposition() const;

	bool hasFullShout() const;

	bool hasCorrectJob(E_JOB _reqJob) const;

	bool hasCorrectSex(E_SEX _sex) const;

	void setName(const char *_name);

	void setAccount(const AccountPtr &_account);

	void setOnline(bool _online);

	void setPlace(s32 _place);

	void setLevel(LVL _level);

	void setExp(EXP _exp);

	void setJob(E_JOB _job);

	void setSex(E_SEX _sex);

	void setFaceType(s32 _facetype);

	void setHairType(s32 _hairtype);

	void setHairColor(s32 _color);

	void setPenya(PENYA _penya);

	void setBankPenya(PENYA64 _penya);

	void setPosition(const CPoint &_pos);

	void setStatPoints(s16 _statPoints);

	void setHp(s32 _hp);

	void setMp(s32 _mp);

	void setFp(s32 _fp);

	void setStr(s32 _str);

	void setSta(s32 _sta);

	void setDex(s32 _dex);

	void setInt(s32 _int);

	void setSkillPoints(s32 _skillPoints);

	void setState(E_STATE _state);

	void setWorldId(ID _id);

	void setRotation(s16 _rot);

	void setSize(s16 _size);

	void addExp(EXP _exp);

	void removeExp(EXP _exp);

	void addStr(s32 _str);

	void addSta(s32 _sta);

	void addDex(s32 _dex);

	void addInt(s32 _int);

	void incrementLevel();

	void decrementLevel();

	void setPvpPoints(s32 _pvp);

	void setPkPoints(s32 _pk);

	void setDisposition(s32 _disposition);

private:

	friend class ICharacterManager;

	ID m_id;

	sdk::stringc m_name;

	AccountPtr m_account;

	bool m_online;

	s32 m_place;

	LVL m_level;

	EXP m_exp;

	E_JOB m_job;

	E_SEX m_sex;

	s32 m_faceType;

	s32 m_hairType;

	union
	{
		s32 m_hairColor;
		s8 m_hairColorRgba[4];
	};

	PENYA m_penya;

	PENYA64 m_bankPenya;

	CPoint m_pos;

	ID m_worldId;

	s16 m_rotation;

	s16 m_size;

	s32 m_hp;

	s32 m_mp;

	s32 m_fp;

	s32 m_str;

	s32 m_sta;

	s32 m_dex;

	s32 m_int;

	s16 m_statPoints;

	s32 m_skillPoints;

	LVL m_flyLevel; //.

	s32 m_flyExp; //.

	s32 m_pvp;

	s32 m_pk;

	s32 m_disposition;

	E_STATE m_state;

};


#endif //CHARACTER_H
