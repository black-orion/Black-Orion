#include "DatabaseObject.h"
#include "DatabaseManager.h"


IDatabaseObject::IDatabaseObject(IDatabaseManager *_manager)
	: m_manager(_manager)
	, m_dbState(DBST_NONE)
{
	if (m_manager != 0)
	{
		m_manager->add(this);
	}
}

IDatabaseObject::~IDatabaseObject()
{
	//FDASSERT(m_manager);
}

const char *IDatabaseObject::getTypeName() const
{
	return typeid(*this).name();
}

IDatabaseManager *IDatabaseObject::getManager()
{
	return m_manager;
}

IDatabaseObject::E_DATABASE_STATE IDatabaseObject::getDatabaseState() const
{
	return m_dbState;
}

void IDatabaseObject::setDatabaseState(E_DATABASE_STATE _state)
{
	m_dbState = _state;
}

void IDatabaseObject::setDatabaseStateLoaded()
{
	m_dbState = DBST_LOADED;
}

void IDatabaseObject::setDatabaseStateCreated()
{
	m_dbState = DBST_CREATED;
}

void IDatabaseObject::setDatabaseStateDeleted()
{
	m_dbState = DBST_DELETED;
}

void IDatabaseObject::solve()
{
}