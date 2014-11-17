#ifndef POSTBOX_H
#define POSTBOX_H


#include "WorldMain.h"
#include "Mail.h"
#include "../shared/E_CHAR.h"
#include "../shared/ItemPack.h"


class IPlayerObject;
class IMailManager;
class ICharacterManager;
class IWorldSettings;


class IPostBox
{
public:

	IPostBox(IPlayerObject *_owner);

	IPlayerObject *getOwner();

	MailPtr getMailById(ID _id) const;

	u32 getMailCount() const;

	const MailPtr &getMail(u32 _num) const;

	bool showList();

	void setMailRead(ID _mailId);

	void takeMoney(ID _mailId);

	void takeItem(ID _mailId);

	void deleteMail(ID _mailId);

	bool sendMail(const char *_receiver, PENYA _money, ID _itemSlot, s32 _itemCount, const char *_title,
		const char *_content);

	void clearMails();

	void addMail(const MailPtr &_mail);

private:

	IPlayerObject *m_owner;

	CArray<MailPtr> m_mails;

	IWorldSettings *_getSettings();

	IMailManager *_getMailManager();

	ICharacterManager *_getCharacterManager();

	IItemPackManager *_getItemPackManager();

};


#endif //POSTBOX_H
