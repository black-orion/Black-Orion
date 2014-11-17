#include "Mail.h"
#include "../shared/Character.h"
#include "../shared/Log.h"


IMail::IMail(IMailManager *_manager)
	: IDatabaseObject((IDatabaseManager*)_manager)
	, m_id(0)
	//, m_sender(0)
	//, m_receiver(0)
	, m_time(0)
	, m_read(false)
	, m_money(0)
	//, m_item(0)
	//, m_title("")
	//, m_content("")
{
}

IMail::~IMail()
{
#ifdef SDEBUG
	Log::write(LOG_DEBUG, "IMail dtor %d", m_id);
#endif
}

void IMail::reset()
{
	m_id = 0;
	m_sender = 0;
	m_receiver = 0;
	m_time = 0;
	m_read = false;
	m_money = 0;
	m_item = 0;
	m_title.clear();
	m_content.clear();

	solve();
}

void IMail::solve()
{
	m_sender.reset();
	m_receiver.reset();
	m_item.reset();
}

ID IMail::getId() const
{
	return m_id;
}

const CharacterPtr &IMail::getSender() const
{
	return m_sender;
}

const CharacterPtr &IMail::getReceiver() const
{
	return m_receiver;
}

Time IMail::getTime() const
{
	return m_time;
}

bool IMail::isRead() const
{
	return m_read;
}

PENYA IMail::getMoney() const
{
	return m_money;
}

const ItemPackPtr &IMail::getItem() const
{
	return m_item;
}

ID IMail::getItemId() const
{
	return m_item ? m_item->getId() : 0;
}

const char *IMail::getTitle() const
{
	return m_title.c_str();
}

const char *IMail::getContent() const
{
	return m_content.c_str();
}

void IMail::setSender(const CharacterPtr &_char)
{
	m_sender = _char;
}

void IMail::setReceiver(const CharacterPtr &_char)
{
	m_receiver = _char;
}

void IMail::setTime(Time _time)
{
	m_time = _time;
}

void IMail::setRead(bool _read)
{
	m_read = _read;
}

void IMail::setMoney(PENYA _money)
{
	m_money = _money;
}

void IMail::setItem(const ItemPackPtr &_item)
{
	m_item = _item;
}

void IMail::setTitle(const char *_title)
{
	m_title = _title;
}

void IMail::setContent(const char *_content)
{
	m_content = _content;
}