#ifndef ACCOUNT_H
#define ACCOUNT_H


#include "Base.h"
#include "DatabaseObject.h"


class IAccountManager;
class IDatabaseManager;
class ICharacter;


//Eigenschaften (r = lesen, w = schreiben)

//                  Login   Char    World
//----------------------------------------
//	Id               (r)     (r)     (r)
//	Name             (r)     (r)     (r)
//	Password         (r)     (r)     (r)
//  AccessLevel      (r)      -      (r/w)
//  Points            -       -      (r/w)
//  LastLogin        (r/w)    -       -
//  BanTime          (r)      -      (r/w)
//  Creation          -       -       -
//----------------------------------------
// SELECT             x       x       x
// UPDATE             x               x
// INSERT             x
// DELETE             x


class IAccount : public IDatabaseObject
{
public:

	enum E_ACCESS_LEVEL
	{
		ACC_MINIMUM = 0,

		ACC_PLAYER = 70,
		ACC_GAMEMASTER = 100, //??
		ACC_ADMIN = 120,      //??

		ACC_MAXIMUM = 65535
	};

	enum E_STATE
	{
		STATE_LOGIN,
		STATE_CHAR,
		STATE_WORLD
	};

	IAccount(IAccountManager *_manager = 0);

	~IAccount();

	void reset();

	void solve();

	ID getId() const;

	const char *getName() const;

	const char *getPassword() const;

	E_ACCESS_LEVEL getAccessLevel() const;

	u32 getPoints() const;

	Time getLastLogin() const;

	Time getBanTime() const;

	const CharacterPtr &getCharacter(u32 _num);

	E_STATE getState() const;

	bool isCharOn(const char *_charname) const;

	bool isCharOn(const CharacterPtr &_char) const;

	bool isOnline() const;

	void setId(ID _id);

	void setName(const char *_name);

	void setPassword(const char *_password);

	void setPoints(u32 _points);

	void setAccessLevel(E_ACCESS_LEVEL _access);

	void setLastLogin(Time _time);

	void setBanTime(Time _time);

	void setCharacter(u32 _num, const CharacterPtr &_char);

	void setOnline(bool _online);

	void setState(E_STATE _state);

	void updateLastLogin();

	void removeCharacter(const CharacterPtr &_char);

	static E_ACCESS_LEVEL accessLevel(s32 _id);

private:

	friend class IAccountManager;

	ID m_id;

	sdk::stringc m_name;

	sdk::stringc m_password;

	E_ACCESS_LEVEL m_access;

	u32 m_points;

	Time m_lastlogin;

	Time m_bantime;

	bool m_online;

	CharacterPtr m_characters[3];

	E_STATE m_state;

};


#endif //ACCOUNT_H
