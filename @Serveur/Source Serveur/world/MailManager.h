#ifndef MAILMANAGER_H
#define MAILMANAGER_H


#include "WorldMain.h"
#include "../shared/DatabaseManager.h"
#include "../shared/DatabaseObject.h"


class IMail;
class IDatabaseConnection;
class ICharacterManager;
class IItemPackManager;
class IPlayerObject;
class IPostBox;


class IMailManager : public IDatabaseManager
{
public:

	IMailManager(IDatabaseConnection *_dbc, ICharacterManager *_charMngr, IItemPackManager *_itemMngr);

	~IMailManager();

	void clear();

	void add(IDatabaseObject *_dbObj);

	void remove(IDatabaseObject *_dbObj);

	void update();

	u32 getMailNumber() const;

	void setDbc(IDatabaseConnection *_dbc);


	//:: WORLD SERVER FUNCTIONS ::

	MailPtr getMail_W(ID _id, bool _fromDatabase = true);

	bool getMails_W(IPostBox *_post);

	bool createMail_W(IPlayerObject *_sender, const CharacterPtr &_receiver, PENYA _money,
		ID _itemId, const char *_title, const char *_content);

	bool deleteMail_W(const MailPtr &_mail);

	bool saveMail_W(const MailPtr &_mail);

	bool save_W();

private:

	IDatabaseConnection *m_dbc;

	ICharacterManager *m_charMngr;

	IItemPackManager *m_itemMngr;

	CArray<MailPtr> m_mails;

	MailPtr _newMail();

	bool _saveMail_W(const MailPtr &_mail);

};


#endif //MAILMANAGER_H
