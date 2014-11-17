#include "DatabaseConnection.h"


/// IQueryResult ///
////////////////////

IQueryResult::IQueryResult()
	: m_res(0)
	, m_row(0)
{
}

IQueryResult::~IQueryResult()
{
	if (m_res)
	{
		mysql_free_result(m_res);
	}
}

bool IQueryResult::nextRow()
{
	FDASSERT(m_res);
	return ((m_row = mysql_fetch_row(m_res)) != NULL);
}

char **IQueryResult::getRow()
{
	return m_row;
}

const char *IQueryResult::getFieldString(u32 _field) const
{
	FDASSERT(m_row);
	return m_row[_field];
}

bool IQueryResult::getFieldBool(u32 _field) const
{
	FDASSERT(m_row);
	return (xtoi(m_row[_field]) != 0);
}

s32 IQueryResult::getFieldS32(u32 _field) const
{
	FDASSERT(m_row);
	return xtoi(m_row[_field]);
}

u32 IQueryResult::getFieldU32(u32 _field) const
{
	FDASSERT(m_row);
	return u32(xtou(m_row[_field]));
}

s64 IQueryResult::getFieldS64(u32 _field) const
{
	FDASSERT(m_row);
	return xtoi64(m_row[_field]);
}

u64 IQueryResult::getFieldU64(u32 _field) const
{
	FDASSERT(m_row);
	return xtou64(m_row[_field]);
}

f32 IQueryResult::getFieldF32(u32 _field) const
{
	FDASSERT(m_row);
	return xtof(m_row[_field]);
}

f64 IQueryResult::getFieldF64(u32 _field) const
{
	FDASSERT(m_row);
	return xtod(m_row[_field]);
}


/// IDatabaseConnection ///
///////////////////////////

IDatabaseConnection::IDatabaseConnection()
	: m_mysql(0)
	, m_numqueries(0)
{
	m_buffer[0] = '\0';
}

IDatabaseConnection::~IDatabaseConnection()
{
	close();
	delete m_mysql;
}

bool IDatabaseConnection::connect(const char *_host, PORT _port, const char *_username, const char *_password, const char *_database)
{
	if (!m_mysql)
	{
		m_mysql = new MYSQL;
	}

	return (mysql_init(m_mysql) &&
		mysql_real_connect(m_mysql, _host, _username, _password, _database, _port, NULL, 0));
}

bool IDatabaseConnection::query(const char *format, ...)
{
	FDASSERT(format);
	++m_numqueries;

	va_list va_alist;

	va_start(va_alist, format);
	vsnprintf(m_buffer, BUF_SIZE-1, format, va_alist);
	va_end(va_alist);

	return (mysql_query(m_mysql, m_buffer) == 0);
}

bool IDatabaseConnection::query_simple(const char *_str)
{
	FDASSERT(_str);
	++m_numqueries;

	return (mysql_query(m_mysql, _str) == 0);
}

sdk::stringc IDatabaseConnection::escapeString(const char *_str)
{
	FDASSERT(_str);

	u32 t_strLen = xstrlen(_str);
	char *t_buffer = new char[t_strLen * 3];
	mysql_real_escape_string(m_mysql, t_buffer, _str, t_strLen);
	sdk::stringc r_str(t_buffer);
	delete[] t_buffer;
	return r_str;
}

u32 IDatabaseConnection::getQueryCount()
{
	return m_numqueries;
}

const char *IDatabaseConnection::getLastQuery() const
{
	return m_buffer;
}

bool IDatabaseConnection::ping()
{
	return (mysql_ping(m_mysql) == 0);
}

void IDatabaseConnection::close()
{
	if (m_mysql)
	{
		mysql_close(m_mysql);
	}
}

const char *IDatabaseConnection::getError()
{
	return mysql_error(m_mysql);
}

u32 IDatabaseConnection::getAffectedRows()
{
	return u32(mysql_affected_rows(m_mysql));
}

bool IDatabaseConnection::getResult(IQueryResult &_result)
{
	_result.m_res = mysql_store_result(m_mysql);

	return (_result.m_res != 0);
}
