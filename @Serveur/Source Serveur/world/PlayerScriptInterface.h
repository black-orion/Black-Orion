#ifndef PLAYERSCRIPTINTERFACE_H
#define PLAYERSCRIPTINTERFACE_H


#include "WorldMain.h"
#include "../shared/Account.h"
#include "../shared/E_CHAR.h"

#include "../libs/angelscript/include/angelscript.h"
#include "../libs/angelscript/add_on/scriptstring/scriptstring.h"
#include "../libs/angelscript/add_on/scriptbuilder/scriptbuilder.h"


class IPlayerObject;
class INpcObject;


class IPlayerScriptInterface
{
public:

	IPlayerScriptInterface();

	~IPlayerScriptInterface();

	const PlayerObjectPtr &getPlayer();

	void setPlayer(const PlayerObjectPtr &_pObj);

	//script functions

	bool isValid() const;

	ID getId() const;

	ID getCharacterId() const;

	const std::string &getName() const;

	LVL getLevel() const;

	E_JOB getJob() const;

	s32 getStr() const;

	s32 getSta() const;

	s32 getDex() const;

	s32 getInt() const;

	s32 getStatPoints() const;

	ID getAccountId() const;

	const std::string &getAccountName() const;

	IAccount::E_ACCESS_LEVEL getAccessLevel() const;

	CPoint getPosition() const;

	s16 getRotation() const;

	s16 getSize() const;

	void setName(const std::string &_str);

	void setLevel(LVL _level);

	void setJob(E_JOB _job);

	void setStr(s32 _str);

	void setSta(s32 _sta);

	void setDex(s32 _dex);

	void setInt(s32 _int);

	void setStatPoints(s32 _sp);

	void setPosition(const CPoint &_pos);

	void setRotation(s16 _rotation);

	void setSize(s16 _size);

	//session
	bool isSessionVarSet(const std::string &_name);

	std::string &getSessionVar(const std::string &_name);

	void setSessionVar(const std::string &_name, const std::string &_value);

	void eraseSessionVar(const std::string &_name);

	void clearSession();

	static bool registerAll(asIScriptEngine *_engine);

private:

	PlayerObjectPtr m_playerObject;

};


#endif //PLAYERSCRIPTINTERFACE_H
