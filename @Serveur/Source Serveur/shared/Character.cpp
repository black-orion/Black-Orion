#include "Character.h"
#include "Account.h"
#include "ItemPack.h"
#include "Log.h"


ICharacter::ICharacter(ICharacterManager *_manager)
	: IDatabaseObject((IDatabaseManager*)_manager)
	, m_id(0)
	, m_name("")
	, m_account(0)
	, m_online(false)
	, m_place(0)
	, m_level(1)
	, m_job(JOB_VAGRANT)
	, m_sex(SEX_MALE)
	, m_faceType(0)
	, m_hairType(0)
	, m_hairColor(0x808080ff)
	, m_penya(0)
	, m_bankPenya(0)
	, m_statPoints(0)
	, m_hp(1)
	, m_mp(1)
	, m_fp(1)
	, m_str(1)
	, m_sta(1)
	, m_dex(1)
	, m_int(1)
	, m_skillPoints(0)
	, m_state(STATE_CHAR)
	, m_worldId(1)
	, m_rotation(0)
	, m_size(100) //not 0
	, m_pvp(0)
	, m_pk(0)
	, m_disposition(0)
{
}

ICharacter::~ICharacter()
{
#ifdef SDEBUG
	Log::write(LOG_DEBUG, "ICharacter dtor %d", m_id);
#endif
}

void ICharacter::reset()
{
	m_id = 0;
	m_name.clear();
	//m_account = 0;
	m_online = false;
	m_place = 0;
	m_level = 1;
	m_job = JOB_VAGRANT;
	m_sex = SEX_MALE;
	m_faceType = 0;
	m_hairType = 0;
	m_hairColor = 0x808080ff;
	m_penya = 0;
	m_bankPenya = 0;
	m_statPoints = 0;
	m_str = 1;
	m_sta = 1;
	m_dex = 1;
	m_int = 1;
	m_skillPoints = 0;
	m_state = STATE_CHAR;
	m_worldId = 1;
	m_rotation = 0;
	m_size = 100; //not 0
	m_pvp = 0;
	m_pk = 0;
	m_disposition = 0;

	solve();
}

void ICharacter::solve()
{
	m_account.reset();
}

ID ICharacter::getId() const
{
	return m_id;
}

const char *ICharacter::getName() const
{
	return m_name.c_str();
}

const AccountPtr &ICharacter::getAccount()
{
	return m_account;
}

bool ICharacter::isOnline() const
{
	return m_online;
}

s32 ICharacter::getPlace() const
{
	return m_place;
}

LVL ICharacter::getLevel() const
{
	return m_level;
}

EXP ICharacter::getExp() const
{
	return m_exp;
}

E_JOB ICharacter::getJob() const
{
	return m_job;
}

E_SEX ICharacter::getSex() const
{
	return m_sex;
}

s32 ICharacter::getFaceType() const
{
	return m_faceType;
}

s32 ICharacter::getHairType() const
{
	return m_hairType;
}

s32 ICharacter::getHairColor() const
{
	return m_hairColor;
}

PENYA ICharacter::getPenya() const
{
	return m_penya;
}

PENYA ICharacter::getMoneyUntilMaximum() const
{
	FDASSERT(getPenya() <= MAX_PENYA);

	return (MAX_PENYA - getPenya());
}

PENYA64 ICharacter::getBankPenya() const
{
	return m_bankPenya;
}

const CPoint &ICharacter::getPosition() const
{
	return m_pos;
}

s16 ICharacter::getStatPoints() const
{
	return m_statPoints;
}

s32 ICharacter::getHp() const
{
	return m_hp;
}

s32 ICharacter::getMp() const
{
	return m_mp;
}

s32 ICharacter::getFp() const
{
	return m_fp;
}

s32 ICharacter::getStr() const
{
	return m_str;
}

s32 ICharacter::getSta() const
{
	return m_sta;
}

s32 ICharacter::getDex() const
{
	return m_dex;
}

s32 ICharacter::getInt() const
{
	return m_int;
}

s32 ICharacter::getSkillPoints() const
{
	return m_skillPoints;
}

ICharacter::E_STATE ICharacter::getState() const
{
	return m_state;
}

ID ICharacter::getWorldId() const
{
	return m_worldId;
}

s16 ICharacter::getRotation() const
{
	return m_rotation;
}

s16 ICharacter::getSize() const
{
	return m_size;
}

s32 ICharacter::getPvpPoints() const
{
	return m_pvp;
}

s32 ICharacter::getPkPoints() const
{
	return m_pk;
}

s32 ICharacter::getDisposition() const
{
	return m_disposition;
}

bool ICharacter::hasFullShout() const
{
	return false;
}

bool ICharacter::hasCorrectJob(E_JOB _reqJob) const
{
	if (_reqJob == JOB_VAGRANT)
	{
		return true;
	}

	if (m_job == _reqJob)
	{
		return true;
	}

	if (jobStats(m_job).FirstJob == _reqJob)
	{
		return true;
	}

	if (jobStats(jobStats(m_job).FirstJob).FirstJob == _reqJob)
	{
		return true;
	}

	return false;
}

bool ICharacter::hasCorrectSex(E_SEX _sex) const
{
	FDASSERT(_sex == sex(_sex));

	return (m_sex == _sex ||
		_sex == SEX_SEXLESS);
}

void ICharacter::setName(const char *_name)
{
	m_name = _name;
}

void ICharacter::setAccount(const AccountPtr &_account)
{
	m_account = _account;
}

void ICharacter::setOnline(bool _online)
{
	m_online = _online;
}

void ICharacter::setPlace(s32 _place)
{
	m_place = _place;
}

void ICharacter::setLevel(LVL _level)
{
	 m_level = _level;
}

void ICharacter::setExp(EXP _exp)
{
	m_exp = _exp;
}

void ICharacter::setJob(E_JOB _job)
{
	 m_job = _job;
}

void ICharacter::setSex(E_SEX _sex)
{
	 m_sex = _sex;
}

void ICharacter::setFaceType(s32 _facetype)
{
	 m_faceType = _facetype;
}

void ICharacter::setHairType(s32 _hairtype)
{
	 m_hairType = _hairtype;
}

void ICharacter::setHairColor(s32 _color)
{
	 m_hairColor = _color;
}

void ICharacter::setPenya(PENYA _penya)
{
	 m_penya = _penya;
}

void ICharacter::setBankPenya(PENYA64 _penya)
{
	 m_bankPenya = _penya;
}

void ICharacter::setPosition(const CPoint &_pos)
{
	m_pos = _pos;
}

void ICharacter::setStatPoints(s16 _statPoints)
{
	m_statPoints = _statPoints;
}

void ICharacter::setHp(s32 _hp)
{
	m_hp = _hp;
}

void ICharacter::setMp(s32 _mp)
{
	m_mp = _mp;
}

void ICharacter::setFp(s32 _fp)
{
	m_fp = _fp;
}

void ICharacter::setStr(s32 _str)
{
	m_str = _str;
}

void ICharacter::setSta(s32 _sta)
{
	m_sta = _sta;
}

void ICharacter::setDex(s32 _dex)
{
	m_dex = _dex;
}

void ICharacter::setInt(s32 _int)
{
	m_int = _int;
}

void ICharacter::setSkillPoints(s32 _skillPoints)
{
	m_skillPoints = _skillPoints;
}

void ICharacter::setState(E_STATE _state)
{
	m_state = _state;
}

void ICharacter::setWorldId(ID _id)
{
	m_worldId = _id;
}

void ICharacter::setRotation(s16 _rot)
{
	m_rotation = _rot;
}

void ICharacter::setSize(s16 _size)
{
	m_size = _size;
}

void ICharacter::addExp(EXP _exp)
{
	m_exp += _exp;
}

void ICharacter::removeExp(EXP _exp)
{
	m_exp -= _exp;

	if (m_exp < 0)
	{
		m_exp = 0;
	}
}

void ICharacter::addStr(s32 _str)
{
	m_str += _str;
}

void ICharacter::addSta(s32 _sta)
{
	m_sta += _sta;
}

void ICharacter::addDex(s32 _dex)
{
	m_dex += _dex;
}

void ICharacter::addInt(s32 _int)
{
	m_int += _int;
}

void ICharacter::incrementLevel()
{
	++m_level;
}

void ICharacter::decrementLevel()
{
	--m_level;
}

void ICharacter::setPvpPoints(s32 _pvp)
{
	m_pvp = _pvp;
}

void ICharacter::setPkPoints(s32 _pk)
{
	m_pk = _pk;
}

void ICharacter::setDisposition(s32 _disposition)
{
	m_disposition = _disposition;
}