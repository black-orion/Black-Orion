#ifndef DATABASEOBJECT_H
#define DATABASEOBJECT_H


#include "Base.h"
#include "RefCounted.h"


class IDatabaseManager;


class IDatabaseObject : public IRefCounted
{
public:

	enum E_DATABASE_STATE
	{
		DBST_NONE,
		DBST_LOADED,
		DBST_CREATED,
		DBST_DELETED
	};

	IDatabaseObject(IDatabaseManager *_manager);

	virtual ~IDatabaseObject();

	const char *getTypeName() const;

	IDatabaseManager *getManager();

	E_DATABASE_STATE getDatabaseState() const;

	void setDatabaseState(E_DATABASE_STATE _state);

	void setDatabaseStateLoaded();

	void setDatabaseStateCreated();

	void setDatabaseStateDeleted();

	virtual void solve();

private:

	IDatabaseManager *m_manager;

	E_DATABASE_STATE m_dbState;

};


#endif //DATABASEOBJECT_H
