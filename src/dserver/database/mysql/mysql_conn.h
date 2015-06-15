#ifndef _MYSQL_CONN_H_
#define _MYSQL_CONN_H_

#include "../../define.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

namespace dserver
{
namespace database
{
namespace mysql
{

class MySQLConn
{
public:
	MySQLConn(void);
	virtual ~MySQLConn(void);

	bool			Connect(void);
	void			Disconnect(void);

	void			PrepareQuery(char* query_info);
	void			Execute(void);
	bool			Fetch(void);

	void			BindParam(const int32_t value);
	void			BindParam(const int64_t value);
	void			BindParam(const uint32_t value);
	void			BindParam(const uint64_t value);
	void			BindParam(const double value);
	void			BindParam(const SYSTEMTIME value);
	void			BindParam(const char* value);
	void			BindParam(const bool value);

	int32_t			GetInt(void);
	int64_t			GetInt64(void);
	uint32_t		GetUInt(void);
	uint64_t		GetUInt64(void);
	double			GetDouble(void);
	const char*		GetString(void);
	bool			GetBool(void);
private:
	sql::Driver*				driver_;
	sql::Connection*			conn_;
	sql::PreparedStatement*		pstmt_;
	sql::ResultSet*				resultset_;

	unsigned int				param_index_;
	uint32_t					column_index_;

};

}
}
}

#endif