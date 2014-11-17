#include "NpcObject.h"
#include "NpcData.h"
#include "World.h"
#include "PlayerObject.h"
#include "WorldPlayer.h"
#include "NpcDialogEnv.h"
#include "../shared/PacketCreator.h"
#include "../shared/Log.h"


INpcObject::INpcObject(ID _id,
					   IWorld *_world,
					   const INpcData *_data)
	: IWorldObject(_id, _world)
	, m_data(_data)
	, m_text(0)
	, m_nextText(0)
	, m_dialogScript(0)
{
	FDASSERT(m_data);

	m_size = m_data->getSize();
	m_rotation = m_data->getRotation();
	m_pos = m_data->getPosition();
	m_mover = m_data->getMover();
}

INpcObject::~INpcObject()
{
}

INpcObject::E_TYPE INpcObject::getType() const
{
	return TYPE_NPC;
}

const INpcData *INpcObject::getData() const
{
	return m_data;
}

const IMoverData *INpcObject::getMover() const
{
	return m_mover;
}

bool INpcObject::init()
{
	FDASSERT(m_data);

	if (m_data->getDialogFileName()[0])
	{
		m_dialogScript = INpcDialogEnv::instance()->loadScript(m_data->getDialogFileName());

		if (!m_dialogScript ||
			!m_dialogScript->init(this))
		{
			Log::write(LOG_ERROR, "Could not load npc dialog script file \"%s\"!", m_data->getDialogFileName());
			return false;
		}
	}

	return true;
}

void INpcObject::onWorldRemove()
{
	IWorldObject::onWorldRemove();
}

void INpcObject::onDestroy()
{
	IWorldObject::onDestroy();
}

void INpcObject::update()
{
	if (m_data->getTextCount() &&
		_time() >= m_nextText)
	{
		if (m_world->isPlayerInLocalArea(this))
		{
			sendToLocalArea(IPacketCreator::chat(m_id, m_data->getText(m_text).Str.c_str()));
		}

		m_nextText = _time() + random(m_data->getText(m_text).Delay, 2 * m_data->getText(m_text).Delay);
		++m_text;

		//reset the current text
		if (m_text == m_data->getTextCount())
		{
			m_text = 0;
		}
	}
}

void INpcObject::dialogAction(const PlayerObjectPtr &_pObj, const char *_str, s32 _action1, s32 _action2, s32 _unknown)
{
	FDASSERT(_pObj);
	FDASSERT(_str);

	if (m_dialogScript)
	{
		m_dialogScript->OnDialogAction(_pObj, _str, _action1);
	}
}