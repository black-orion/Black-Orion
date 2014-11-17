#ifndef MAIL_H
#define MAIL_H


#include "WorldMain.h"
#include "../shared/DatabaseObject.h"
#include "../shared/ItemPack.h"


class ICharacter;
class IMailManager;


class IMail : public IDatabaseObject
{
public:

	IMail(IMailManager *_manager);

	~IMail();

	void reset();

	void solve();

	ID getId() const;

	const CharacterPtr &getSender() const;

	const CharacterPtr &getReceiver() const;

	Time getTime() const;

	bool isRead() const;

	PENYA getMoney() const;

	const ItemPackPtr &getItem() const;

	ID getItemId() const;

	const char *getTitle() const;

	const char *getContent() const;

	void setSender(const CharacterPtr &_char);

	void setReceiver(const CharacterPtr &_char);

	void setTime(Time _time);

	void setRead(bool _read);

	void setMoney(PENYA _money);

	void setItem(const ItemPackPtr &_item);

	void setTitle(const char *_title);

	void setContent(const char *_content);

private:

	friend class IMailManager;

	ID m_id;

	CharacterPtr m_sender;

	CharacterPtr m_receiver;

	Time m_time;

	bool m_read;

	PENYA m_money;

	ItemPackPtr m_item;

	sdk::stringc m_title;

	sdk::stringc m_content;

};


#endif //MAIL_H
