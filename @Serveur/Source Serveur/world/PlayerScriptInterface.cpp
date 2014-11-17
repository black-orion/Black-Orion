#include "PlayerScriptInterface.h"
#include "WorldPlayer.h"
#include "PlayerObject.h"
#include "../shared/Character.h"


IPlayerScriptInterface::IPlayerScriptInterface()
{
}

IPlayerScriptInterface::~IPlayerScriptInterface()
{
}

const PlayerObjectPtr &IPlayerScriptInterface::getPlayer()
{
	return m_playerObject;
}

void IPlayerScriptInterface::setPlayer(const PlayerObjectPtr &_pObj)
{
	m_playerObject = _pObj;
}

bool IPlayerScriptInterface::isValid() const
{
	return m_playerObject != 0;
}

ID IPlayerScriptInterface::getId() const
{
	if (m_playerObject)
	{
		return m_playerObject->getId();
	}

	return 0;
}

ID IPlayerScriptInterface::getCharacterId() const
{
	if (m_playerObject &&
		m_playerObject->getCharacter())
	{
		return m_playerObject->getCharacter()->getId();
	}

	return 0;
}

const std::string &IPlayerScriptInterface::getName() const
{
	static std::string r_str;

	if (m_playerObject)
	{
		r_str = m_playerObject->getCharacter()->getName();
		return r_str;
	}

	r_str.clear();
	return r_str;
}

LVL IPlayerScriptInterface::getLevel() const
{
	if (m_playerObject)
	{
		return m_playerObject->getLevel();
	}

	return 0;
}

E_JOB IPlayerScriptInterface::getJob() const
{
	if (m_playerObject &&
		m_playerObject->getCharacter())
	{
		return m_playerObject->getCharacter()->getJob();
	}

	return JOB_VAGRANT;
}

s32 IPlayerScriptInterface::getStr() const
{
	if (m_playerObject)
	{
		return m_playerObject->getCharacter()->getStr();
	}

	return 0;
}

s32 IPlayerScriptInterface::getSta() const
{
	if (m_playerObject)
	{
		return m_playerObject->getCharacter()->getSta();
	}

	return 0;
}

s32 IPlayerScriptInterface::getDex() const
{
	if (m_playerObject)
	{
		return m_playerObject->getCharacter()->getDex();
	}

	return 0;
}

s32 IPlayerScriptInterface::getInt() const
{
	if (m_playerObject)
	{
		return m_playerObject->getCharacter()->getInt();
	}

	return 0;
}

s32 IPlayerScriptInterface::getStatPoints() const
{
	if (m_playerObject)
	{
		return m_playerObject->getCharacter()->getStatPoints();
	}

	return 0;
}

ID IPlayerScriptInterface::getAccountId() const
{
	if (m_playerObject)
	{
		return m_playerObject->getPlayer()->getAccount()->getId();
	}

	return 0;
}

const std::string &IPlayerScriptInterface::getAccountName() const
{
	static std::string r_str;

	if (m_playerObject)
	{
		r_str = m_playerObject->getPlayer()->getAccount()->getName();
		return r_str;
	}

	r_str.clear();
	return r_str;
}

IAccount::E_ACCESS_LEVEL IPlayerScriptInterface::getAccessLevel() const
{
	if (m_playerObject)
	{
		return m_playerObject->getPlayer()->getAccount()->getAccessLevel();
	}

	return IAccount::ACC_MINIMUM;
}

CPoint IPlayerScriptInterface::getPosition() const
{
	if (m_playerObject)
	{
		return m_playerObject->getPosition();
	}

	return CPoint();
}

s16 IPlayerScriptInterface::getRotation() const
{
	if (m_playerObject)
	{
		return m_playerObject->getRotation();
	}

	return 0;
}

s16 IPlayerScriptInterface::getSize() const
{
	if (m_playerObject)
	{
		return m_playerObject->getSize();
	}

	return 0;
}

void IPlayerScriptInterface::setName(const std::string &_str)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setName(_str.c_str());
	}
}

void IPlayerScriptInterface::setLevel(LVL _level)
{
	if (m_playerObject)
	{
		m_playerObject->changeLevel(_level);
	}
}

void IPlayerScriptInterface::setJob(E_JOB _job)
{
	if (m_playerObject)
	{
		m_playerObject->changeJob(_job);
	}
}

void IPlayerScriptInterface::setStr(s32 _str)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setStr(_str);
		m_playerObject->onBaseStatChanged();
	}
}

void IPlayerScriptInterface::setSta(s32 _sta)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setSta(_sta);
		m_playerObject->onBaseStatChanged();
	}
}

void IPlayerScriptInterface::setDex(s32 _dex)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setDex(_dex);
		m_playerObject->onBaseStatChanged();
	}
}

void IPlayerScriptInterface::setInt(s32 _int)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setInt(_int);
		m_playerObject->onBaseStatChanged();
	}
}

void IPlayerScriptInterface::setStatPoints(s32 _sp)
{
	if (m_playerObject)
	{
		m_playerObject->getCharacter()->setStatPoints(_sp);
		m_playerObject->onBaseStatChanged();
	}
}

void IPlayerScriptInterface::setPosition(const CPoint &_pos)
{
	if (m_playerObject)
	{
		m_playerObject->teleport(_pos);
	}
}

void IPlayerScriptInterface::setRotation(s16 _rotation)
{
	if (m_playerObject)
	{
		m_playerObject->setRotation(_rotation);
	}
}

void IPlayerScriptInterface::setSize(s16 _size)
{
	if (m_playerObject)
	{
		m_playerObject->setSize(_size);
	}
}

bool IPlayerScriptInterface::isSessionVarSet(const std::string &_name)
{
	if (m_playerObject)
	{
		return m_playerObject->isSessionVarSet(_name);
	}

	return false;
}

std::string &IPlayerScriptInterface::getSessionVar(const std::string &_name)
{
	if (m_playerObject)
	{
		return m_playerObject->getSessionVar(_name);
	}

	static std::string ts_empty;
	ts_empty.clear();
	return ts_empty;
}

void IPlayerScriptInterface::setSessionVar(const std::string &_name, const std::string &_value)
{
	if (m_playerObject)
	{
		return m_playerObject->setSessionVar(_name, _value);
	}
}

void IPlayerScriptInterface::eraseSessionVar(const std::string &_name)
{
	if (m_playerObject)
	{
		m_playerObject->eraseSessionVar(_name);
	}
}

void IPlayerScriptInterface::clearSession()
{
	if (m_playerObject)
	{
		m_playerObject->clearSession();
	}
}


////////////
#ifdef new
#undef new
#endif
////////////

//the debug 'new' has to be undefined here because of that placement new:

void IPlayerScriptInterface_Constructor(void *memory)
{
	new (memory) IPlayerScriptInterface();
}

void IPlayerScriptInterface_Destructor(void *memory)
{
	((IPlayerScriptInterface*)memory)->~IPlayerScriptInterface();
}

/////////////////////////////////
#include "../core/MemoryLeak.h"
/////////////////////////////////


bool IPlayerScriptInterface::registerAll(asIScriptEngine *_engine)
{
	FDASSERT(_engine);

	if (
		_engine->RegisterTypedef("s8", "int8") >= 0 &&
		_engine->RegisterTypedef("u8", "uint8") >= 0 &&
		_engine->RegisterTypedef("s16", "int16") >= 0 &&
		_engine->RegisterTypedef("u16", "uint16") >= 0 &&
		_engine->RegisterTypedef("s32", "int") >= 0 &&
		_engine->RegisterTypedef("u32", "uint") >= 0 &&
		_engine->RegisterTypedef("s64", "int64") >= 0 &&
		_engine->RegisterTypedef("u64", "uint64") >= 0 &&
		_engine->RegisterTypedef("f32", "float") >= 0 &&
		_engine->RegisterTypedef("f64", "double") >= 0 &&

		_engine->RegisterEnum("E_JOB") >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_VAGRANT", JOB_VAGRANT) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_MERCENARY", JOB_MERCENARY) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_ACROBAT", JOB_ACROBAT) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_ASSIST", JOB_ASSIST) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_MAGICIAN", JOB_MAGICIAN) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_PUPPETEER", JOB_PUPPETEER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_KNIGHT", JOB_KNIGHT) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BLADE", JOB_BLADE) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_JESTER", JOB_JESTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RANGER", JOB_RANGER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RINGMASTER", JOB_RINGMASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BILLPOSTER", JOB_BILLPOSTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_PSYKEEPER", JOB_PSYKEEPER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_ELEMENTOR", JOB_ELEMENTOR) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_GATEKEEPER", JOB_GATEKEEPER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_DOPPLER", JOB_DOPPLER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_KNIGHT_MASTER", JOB_KNIGHT_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BLADE_MASTER", JOB_BLADE_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_JESTER_MASTER", JOB_JESTER_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RANGER_MASTER", JOB_RANGER_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RINGMASTER_MASTER", JOB_RINGMASTER_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BILLPOSTER_MASTER", JOB_BILLPOSTER_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_PSYKEEPER_MASTER", JOB_PSYKEEPER_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_ELEMENTOR_MASTER", JOB_ELEMENTOR_MASTER) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_KNIGHT_HERO", JOB_KNIGHT_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BLADE_HERO", JOB_BLADE_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_JESTER_HERO", JOB_JESTER_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RANGER_HERO", JOB_RANGER_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_RINGMASTER_HERO", JOB_RINGMASTER_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_BILLPOSTER_HERO", JOB_BILLPOSTER_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_PSYKEEPER_HERO", JOB_PSYKEEPER_HERO) >= 0 &&
		_engine->RegisterEnumValue("E_JOB", "JOB_ELEMENTOR_HERO", JOB_ELEMENTOR_HERO) >= 0 &&

		_engine->RegisterEnum("E_SEX") >= 0 &&
		_engine->RegisterEnumValue("E_SEX", "SEX_MALE", SEX_MALE) >= 0 &&
		_engine->RegisterEnumValue("E_SEX", "SEX_FEMALE", SEX_FEMALE) >= 0 &&
		_engine->RegisterEnumValue("E_SEX", "SEX_SEXLESS", SEX_SEXLESS) >= 0 &&

		//_engine->RegisterObjectType("CPoint", sizeof(CPoint), asOBJ_VALUE | asOBJ_APP_CLASS_CDA) >= 0 &&

		_engine->RegisterObjectType("IPlayer", sizeof(IPlayerScriptInterface),
		asOBJ_VALUE | asOBJ_APP_CLASS_CDA) >= 0 &&

		_engine->RegisterObjectBehaviour("IPlayer", asBEHAVE_CONSTRUCT,
		"void f()", asFUNCTION(IPlayerScriptInterface_Constructor), asCALL_CDECL_OBJLAST) >= 0 &&

		_engine->RegisterObjectBehaviour("IPlayer", asBEHAVE_DESTRUCT,
		"void f()", asFUNCTION(IPlayerScriptInterface_Destructor), asCALL_CDECL_OBJLAST) >= 0 &&

		//_engine->RegisterObjectBehaviour("IPlayer", asBEHAVE_ASSIGNMENT,
		//"IPlayer &f(const IPlayer &in)", asMETHODPR(IPlayerScriptInterface, operator =,
		//(const IPlayerScriptInterface&), IPlayerScriptInterface&), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "IPlayer &opAssign(const IPlayer &in)",
			asMETHOD(IPlayerScriptInterface, operator=), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getId() const",
		asMETHOD(IPlayerScriptInterface, getId), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getCharacterId() const",
		asMETHOD(IPlayerScriptInterface, getCharacterId), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "const string &getName() const",
		asMETHOD(IPlayerScriptInterface, getName), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getLevel() const",
		asMETHOD(IPlayerScriptInterface, getLevel), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "E_JOB getJob() const",
		asMETHOD(IPlayerScriptInterface, getJob), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getStr() const",
		asMETHOD(IPlayerScriptInterface, getStr), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getSta() const",
		asMETHOD(IPlayerScriptInterface, getSta), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getDex() const",
		asMETHOD(IPlayerScriptInterface, getDex), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getInt() const",
		asMETHOD(IPlayerScriptInterface, getInt), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getStatPoints() const",
		asMETHOD(IPlayerScriptInterface, getStatPoints), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getAccountId() const",
		asMETHOD(IPlayerScriptInterface, getAccountId), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "const string &getAccountName() const",
		asMETHOD(IPlayerScriptInterface, getAccountName), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s32 getAccessLevel() const",
		asMETHOD(IPlayerScriptInterface, getAccessLevel), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s16 getRotation() const",
		asMETHOD(IPlayerScriptInterface, getRotation), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "s16 getSize() const",
		asMETHOD(IPlayerScriptInterface, getSize), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setJob(E_JOB)",
		asMETHOD(IPlayerScriptInterface, setJob), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setLevel(s32)",
		asMETHOD(IPlayerScriptInterface, setLevel), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setName(const string &in)",
		asMETHOD(IPlayerScriptInterface, setName), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setStr(s32)",
		asMETHOD(IPlayerScriptInterface, setStr), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setSta(s32)",
		asMETHOD(IPlayerScriptInterface, setSta), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setDex(s32)",
		asMETHOD(IPlayerScriptInterface, setDex), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setInt(s32)",
		asMETHOD(IPlayerScriptInterface, setInt), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setStatPoints(s32)",
		asMETHOD(IPlayerScriptInterface, setStatPoints), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setRotation(s16)",
		asMETHOD(IPlayerScriptInterface, setRotation), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void setSize(s16)",
		asMETHOD(IPlayerScriptInterface, setSize), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "bool isSessionVarSet(const string &in)",
		asMETHOD(IPlayerScriptInterface, isSessionVarSet), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "string &getSessionVar(const string &in)",
		asMETHOD(IPlayerScriptInterface, getSessionVar), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "string &setSessionVar(const string &in, const string &in)",
		asMETHOD(IPlayerScriptInterface, setSessionVar), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void eraseSessionVar(const string &in)",
		asMETHOD(IPlayerScriptInterface, eraseSessionVar), asCALL_THISCALL) >= 0 &&

		_engine->RegisterObjectMethod("IPlayer", "void clearSession()",
		asMETHOD(IPlayerScriptInterface, clearSession), asCALL_THISCALL) >= 0
		)
	{
		return true;
	}
	else
	{
		return false;
	}
}
