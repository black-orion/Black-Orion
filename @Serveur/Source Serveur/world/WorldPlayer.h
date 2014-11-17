#ifndef WORLDPLAYER_H
#define WORLDPLAYER_H


#include "WorldMain.h"
#include "../shared/DatabaseObject.h"


class IAccount;
class ICharacter;
class IPlayerObject;


class IWorldPlayer
{
public:

	IWorldPlayer(ID _id = 0, CNetClient *_client = 0);

	~IWorldPlayer();

	ID getId() const;

	CNetClient *getClient();

	const AccountPtr &getAccount();

	const CharacterPtr &getCharacter();

	const PlayerObjectPtr &getObject();

	void setAccount(const AccountPtr &_account);

	void setCharacter(const CharacterPtr &_char);

	void setObject(const PlayerObjectPtr &_object);

	void greenText(const char *_format, ...);

private:

	enum
	{
		BUF_SIZE = 2048
	};

	static char ms_buffer[BUF_SIZE];

	ID m_id;

	CNetClient *m_client;

	AccountPtr m_account;

	CharacterPtr m_char;

	PlayerObjectPtr m_object;

};


#endif //WORLDPLAYER_H
