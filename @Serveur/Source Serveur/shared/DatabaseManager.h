#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H


#include "Base.h"
#include "Timed.h"


class IDatabaseObject;


class IDatabaseManager : public ITimed
{
public:

	IDatabaseManager();

	virtual void add(IDatabaseObject *_dbObj);

	virtual void remove(IDatabaseObject *_dbObj);

protected:

};


#endif //DATABASEMANAGER_H
