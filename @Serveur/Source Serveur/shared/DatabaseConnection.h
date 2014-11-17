#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H


#include "Base.h"

#include "../libs/mysql/mysql.h"


class IDatabaseConnection;


class IQueryResult
{
public:

	IQueryResult();

	~IQueryResult();

	bool nextRow();

	char **getRow();

	const char *getFieldString(u32 _field) const;

	bool getFieldBool(u32 _field) const;

	s32 getFieldS32(u32 _field) const;

	u32 getFieldU32(u32 _field) const;

	s64 getFieldS64(u32 _field) const;

	u64 getFieldU64(u32 _field) const;

	f32 getFieldF32(u32 _field) const;

	f64 getFieldF64(u32 _field) const;

private:

	friend class IDatabaseConnection;

	MYSQL_RES *m_res;

	MYSQL_ROW m_row;

	IQueryResult(const IQueryResult &)
	{
	}

	IQueryResult &operator = (const IQueryResult &)
	{
		return *this;
	}

};


class IDatabaseConnection
{
public:

	IDatabaseConnection();

	~IDatabaseConnection();

	//connects to a MySQL server
	bool connect(const char *_host,
				 PORT _port,
				 const char *_username,
				 const char *_password,
				 const char *_database);

	//formats and sends a query to the server
	bool query(const char *format, ...);

	//same as query, without text formatting
	bool query_simple(const char *_str);

	//
	sdk::stringc escapeString(const char *_str);

	//statistic: count of queries sent
	u32 getQueryCount();

	const char *getLastQuery() const;

	//kind of connection test, not really important
	bool ping();

	//closes the connection
	void close();

	//returns error messages
	const char *getError();

	//returns the number of rows e.g. returned by a SELECT
	u32 getAffectedRows();

	//called after a SELECT to see if it was successful
	bool getResult(IQueryResult &_result);

private:

	MYSQL *m_mysql;

	u32 m_numqueries;

	enum
	{
		BUF_SIZE = 8192
	};

	char m_buffer[BUF_SIZE];

};


#define PRINT_ERROR(where_) printf(where_ " -> MySQL error: %s\n", m_dbc->getError())


#endif //DATABASECONNECTION_H
