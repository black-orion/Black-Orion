#include "PostBox.h"
#include "PlayerObject.h"
#include "MailManager.h"
#include "WorldServer.h"
#include "WorldPlayer.h"
#include "World.h"
#include "WorldSettings.h"
#include "../shared/PacketCreator.h"
#include "../shared/ItemPack.h"
#include "../shared/Log.h"


IPostBox::IPostBox(IPlayerObject *_owner)
	: m_owner(_owner)
{
	FDASSERT(m_owner);
}

IPlayerObject *IPostBox::getOwner()
{
	return m_owner;
}

MailPtr IPostBox::getMailById(ID _id) const
{
	FOR_EACH (m_mails, i)
	{
		if (m_mails[i]->getId() == _id)
		{
			return m_mails[i];
		}
	}

	return 0;
}

u32 IPostBox::getMailCount() const
{
	return m_mails.size();
}

const MailPtr &IPostBox::getMail(u32 _num) const
{
	FDASSERT(_num < m_mails.size());

	return m_mails[_num];
}

bool IPostBox::showList()
{
	_getMailManager()->getMails_W(this);

	return m_owner->getPlayer()->getClient()->send(IPacketCreator::mailBox(this));
}

void IPostBox::setMailRead(ID _mailId)
{
	MailPtr t_mail = getMailById(_mailId);

	if (t_mail)
	{
		t_mail->setRead(true);

		_getMailManager()->saveMail_W(t_mail);
	}
}

void IPostBox::takeMoney(ID _mailId)
{
	MailPtr t_mail = getMailById(_mailId);

	if (t_mail)
	{
		PENYA t_movePenya = Min(t_mail->getMoney(), m_owner->getCharacter()->getMoneyUntilMaximum());

		t_mail->setMoney(t_mail->getMoney() - t_movePenya);

		m_owner->changePenya(m_owner->getCharacter()->getPenya() + t_movePenya);

		_getMailManager()->saveMail_W(t_mail);
	}
}

void IPostBox::takeItem(ID _mailId)
{
	MailPtr t_mail = getMailById(_mailId);

	if (t_mail &&
		t_mail->getItem())
	{
		if (m_owner->getInventory()->addItem(t_mail->getItem()))
		{
			//...
		}
	}
}

void IPostBox::deleteMail(ID _mailId)
{
	MailPtr t_mail = getMailById(_mailId);

	if (t_mail)
	{
		_getMailManager()->deleteMail_W(t_mail);

		showList();
	}
}

bool IPostBox::sendMail(const char *_receiver, PENYA _money, ID _itemSlot, s32 _itemCount, const char *_title,
	const char *_content)
{
	FDASSERT(_receiver);
	FDASSERT(_title);
	FDASSERT(_content);

	CharacterPtr t_receiver;

	PlayerObjectPtr t_recvPlayer = m_owner->getWorld()->getPlayerByName(_receiver);

	if (t_recvPlayer) //receiver is online
	{
		t_receiver = t_recvPlayer->getCharacter();
	}
	else //receiver is offline
	{
		t_receiver = _getCharacterManager()->getCharacter_W(_receiver);
	}

	if (t_receiver == 0)
	{
		//...

		return false;
	}

	//mail cost
	PENYA t_penya = m_owner->getCharacter()->getPenya();
	if (t_penya >= _getSettings()->Game.MailCost)
	{
		t_penya -= _getSettings()->Game.MailCost;
		m_owner->changePenya(t_penya);
	}
	else
	{
		return false;
	}

	_money = Limit(_money, 0, m_owner->getCharacter()->getPenya());

	ID t_itemPackId = 0;

	if (_itemSlot >= 0)
	{
		IItemSlot *t_itemSlot = 0;
		u32 t_slotPos = 0;
		
		if (!m_owner->getInventory()->getSlotById(&t_itemSlot, _itemSlot, &t_slotPos) ||
			t_itemSlot->getItem() == 0)
		{
			//...

			Log::write(LOG_DEBUG, "Mail: Invalid item");

			return false;
		}

		_itemCount = Limit(_itemCount, 1, t_itemSlot->getItem()->getCount());

		//send the whole stack
		if (t_itemSlot->getItem()->getCount() == _itemCount)
		{
			ItemPackPtr t_item = t_itemSlot->getItem();

			//remove it from the client's inventory
			m_owner->getInventory()->removeItem(t_slotPos);

			//change the type and place
			t_item->setType(IItemPack::TYPE_POST);
			t_item->setPlace(0);

			_getItemPackManager()->saveItemPackLocation_W(t_item, t_receiver);

			//item id for the mail
			t_itemPackId = t_item->getId();
		}

		//create a copy with another amount
		else
		{
			IItemProperties t_itemProp;

			//delete the amount of items
			m_owner->getInventory()->deleteItem(t_slotPos, _itemCount, &t_itemProp);

			//create a new itempack for the mail
			ItemPackPtr t_item =
				_getItemPackManager()->createItemPack_W(t_receiver, IItemPack::TYPE_POST, 0, t_itemProp);

			if (t_item == 0) //error
			{
				Log::write(LOG_DEBUG, "Mail: Could not create item");
				return false;
			}

			//item id for the mail
			t_itemPackId = t_item->getId();
		}
	}

	if (_getMailManager()->createMail_W(m_owner, t_receiver, _money, t_itemPackId, _title, _content))
	{
		//take the money
		m_owner->changePenya(m_owner->getCharacter()->getPenya() - _money);

		if (t_recvPlayer)
		{
			t_recvPlayer->setFlags(IPlayerObject::FLAG_NEWMAIL);

			t_recvPlayer->getPlayer()->getClient()->send(IPacketCreator::flags(t_recvPlayer));
		}

		//update the list
		m_owner->getPlayer()->getClient()->send(IPacketCreator::mailBox(this));

		return true;
	}

	Log::write(LOG_DEBUG, "Mail: Could not create mail");
	return false;
}

void IPostBox::clearMails()
{
	m_mails.clear();
}

void IPostBox::addMail(const MailPtr &_mail)
{
	FDASSERT(_mail != 0);

	/*FOR_EACH (m_mails, i)
	{
		if (m_mails[i]->getId() == _mail->getId())
		{
			m_mails[i] = _mail;
			return;
		}
	}*/

	m_mails.push_back(_mail);
}

IWorldSettings *IPostBox::_getSettings()
{
	return m_owner->getWorld()->getServer()->getSettings();
}

IMailManager *IPostBox::_getMailManager()
{
	return m_owner->getWorld()->getServer()->getMailManager();
}

ICharacterManager *IPostBox::_getCharacterManager()
{
	return m_owner->getWorld()->getServer()->getCharacterManager();
}

IItemPackManager *IPostBox::_getItemPackManager()
{
	return m_owner->getWorld()->getServer()->getItemPackManager();
}