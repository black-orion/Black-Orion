#include "MailManager.h"
#include "Mail.h"
#include "PlayerObject.h"
#include "Inventory.h"
#include "../shared/DatabaseConnection.h"
#include "../shared/CharacterManager.h"
#include "../shared/ItemPackManager.h"
#include "../shared/Character.h"


IMailManager::IMailManager(IDatabaseConnection *_dbc,
						   ICharacterManager *_charMngr,
						   IItemPackManager *_itemMngr)
	: m_dbc(_dbc)
	, m_charMngr(_charMngr)
	, m_itemMngr(_itemMngr)
{
	FDASSERT(m_charMngr);
	FDASSERT(m_itemMngr);
}

IMailManager::~IMailManager()
{
}

void IMailManager::clear()
{
	m_mails.clear();
}

void IMailManager::add(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	m_mails.push_back((IMail*)_dbObj);
}

void IMailManager::remove(IDatabaseObject *_dbObj)
{
	FDASSERT(_dbObj);

	FOR_EACH (m_mails, i)
	{
		if (m_mails[i] == _dbObj)
		{
			m_mails[i].reset();
			m_mails.erase_fast(i);
			return;
		}
	}

	FDASSERT(false && "Invalid _dbObj");
}

void IMailManager::update()
{
	FOR_EACH (m_mails, i)
	{
		if (m_mails[i]->isUnique())
		{
			m_mails[i].reset();
			m_mails.erase_fast(i);
			if (i)
				--i;
		}
	}
}

u32 IMailManager::getMailNumber() const
{
	return m_mails.size();
}

void IMailManager::setDbc(IDatabaseConnection *_dbc)
{
	m_dbc = _dbc;
}


//:: WORLD SERVER FUNCTIONS ::

MailPtr IMailManager::getMail_W(ID _id, bool _fromDatabase)
{
	FDASSERT(m_dbc);

	FOR_EACH (m_mails, i)
	{
		if (m_mails[i]->getId() == _id)
		{
			return m_mails[i];
		}
	}

	if (!_fromDatabase)
	{
		return 0;
	}

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,sender,receiver,time,opened,money,item,title,content FROM mails WHERE id='%d'",
		_id) &&
		m_dbc->getResult(t_result))
	{
		if (t_result.nextRow())
		{
			MailPtr t_mail = _newMail();

			t_mail->m_id = t_result.getFieldS32(0);
			t_mail->m_sender = m_charMngr->getCharacter_W(t_result.getFieldS32(1));
			t_mail->m_receiver = m_charMngr->getCharacter_W(t_result.getFieldS32(2));
			t_mail->m_time = t_result.getFieldS64(3);
			t_mail->m_read = t_result.getFieldBool(4);
			t_mail->m_money = t_result.getFieldS32(5);
			ID t_itemId = t_result.getFieldS32(6);
			if (t_itemId)
			{
				t_mail->m_item = m_itemMngr->getItemPack_W(t_itemId);
			}
			t_mail->m_title = t_result.getFieldString(7);
			t_mail->m_content = t_result.getFieldString(8);

			return t_mail;
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getMail_W");
	}
#endif

	return 0;
}

bool IMailManager::getMails_W(IPostBox *_post)
{
	FDASSERT(_post);
	FDASSERT(m_dbc);

	IQueryResult t_result;

	if (m_dbc->query(
		"SELECT id,sender,receiver,time,opened,money,item,title,content FROM mails WHERE receiver='%d' "
		"ORDER BY time DESC",
		_post->getOwner()->getCharacter()->getId()) &&
		m_dbc->getResult(t_result))
	{
		_post->clearMails();

		while (t_result.nextRow())
		{
			MailPtr t_mail = getMail_W(t_result.getFieldS32(0), false);

			if (!t_mail)
			{
				t_mail = _newMail();
			}

			_post->addMail(t_mail);

			t_mail->m_id = t_result.getFieldS32(0);
			t_mail->m_sender = m_charMngr->getCharacter_W(t_result.getFieldS32(1));
			t_mail->m_receiver = m_charMngr->getCharacter_W(t_result.getFieldS32(2));
			t_mail->m_time = t_result.getFieldS64(3);
			t_mail->m_read = t_result.getFieldBool(4);
			t_mail->m_money = t_result.getFieldS32(5);
			ID t_itemId = t_result.getFieldS32(6);
			if (t_itemId)
			{
				t_mail->m_item = m_itemMngr->getItemPack_W(t_itemId);
			}
			t_mail->m_title = t_result.getFieldString(7);
			t_mail->m_content = t_result.getFieldString(8);
		}
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("getMails_W");
	}
#endif

	return false;
}

bool IMailManager::createMail_W(IPlayerObject *_sender, const CharacterPtr &_receiver, PENYA _money,
								ID _itemId, const char *_title, const char *_content)
{
	FDASSERT(_sender);
	FDASSERT(_receiver);
	FDASSERT(_title);
	FDASSERT(_content);
	FDASSERT(m_dbc);

	sdk::stringc t_title = xescape(_title);
	sdk::stringc t_content = xescape(_content);

	if (m_dbc->query(
		"INSERT INTO mails (sender,receiver,time,opened,money,item,title,content) VALUES "
		"('%d','%d','%I64d','0','%d','%d','%s','%s');",
		_sender->getCharacter()->getId(), _receiver->getId(), CTime::seconds(), _money,
		_itemId, t_title.c_str(), t_content.c_str()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("createMail_W");
	}
#endif

	return false;
}

bool IMailManager::deleteMail_W(const MailPtr &_mail)
{
	FDASSERT(m_dbc);
	FDASSERT(_mail);

	if (m_dbc->query(
		"DELETE FROM mails WHERE id='%d'",
		_mail->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("deleteMail_W");
	}
#endif

	return false;
}

bool IMailManager::saveMail_W(const MailPtr &_mail)
{
	FDASSERT(_mail);

	return _saveMail_W(_mail.get());
}

bool IMailManager::save_W()
{
	FOR_EACH (m_mails, i)
	{
		if (!_saveMail_W(m_mails[i]))
			return false;
	}

	return true;
}

MailPtr IMailManager::_newMail()
{
	return MailPtr(new IMail(this));
}

bool IMailManager::_saveMail_W(const MailPtr &_mail)
{
	FDASSERT(_mail);

	if (m_dbc->query(
		"UPDATE mails SET money='%d',opened='%d',item='%d' "
		"WHERE id='%d' LIMIT 1",
		_mail->getMoney(), _mail->isRead() ? 1 : 0, _mail->getItemId(), _mail->getId()))
	{
		return true;
	}
#ifdef SETTING_MYSQL_ERRORS_ENABLED
	else
	{
		PRINT_ERROR("_saveMail_W");
	}
#endif

	return false;
}