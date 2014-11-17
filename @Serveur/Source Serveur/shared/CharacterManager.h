#ifndef CHARACTERMANAGER_H
#define CHARACTERMANAGER_H


#include "Base.h"
#include "DatabaseManager.h"
#include "E_CHAR.h"
#include "../char/CharSettings.h"


class ICharacter;
class IAccount;
class IAccountManager;
class IItemPackManager;
class IDatabaseConnection;
class ICharPlayer;


class ICharacterManager : public IDatabaseManager
{
public:

	ICharacterManager(IDatabaseConnection *_dbc, IAccountManager *_accMngr, IItemPackManager *_itemMngr);

	~ICharacterManager();

	void clear();

	void add(IDatabaseObject *_dbObj);

	void remove(IDatabaseObject *_dbObj);

	void update();

	u32 getCharacterNumber() const;

	void setDbc(IDatabaseConnection *_dbc);


	//:: CHAR SERVER FUNCTIONS ::

	//not loading equipment
	CharacterPtr getCharacter_C(ID _id, bool _fromDatabase = true);

	//not loading equipment
	CharacterPtr getCharacter_C(const char *_name, bool _fromDatabase = true);

	//loading equipment
	bool createCharacter_C(ICharPlayer *_player, s32 _place, const char *_name,
		E_SEX _sex, s32 _hairType, s32 _hairColor, s32 _faceType, ICharCharacterSettings *_settings);

	//deletes a char from the database
	bool deleteCharacter_C(const CharacterPtr &_char);

	//loading equipment
	bool getCharacters_C(ICharPlayer *_player);


	//:: WORLD SERVER FUNCTIONS ::

	CharacterPtr getCharacter_W(ID _id);

	CharacterPtr getCharacter_W(const char *_name);

	bool saveCharacter_W(const CharacterPtr &_char);

	bool saveCharacter_onlineStatus_W(const CharacterPtr &_char);

	bool save_W();

private:

	IDatabaseConnection *m_dbc;

	IAccountManager *m_accMngr;

	IItemPackManager *m_itemMngr;

	CArray<CharacterPtr> m_chars;

	CharacterPtr _newCharacter();

	bool _saveCharacter_W(const CharacterPtr &_char);

	bool _saveCharacter_onlineStatus_W(const CharacterPtr &_char);

};


#endif //CHARACTERMANAGER_H
