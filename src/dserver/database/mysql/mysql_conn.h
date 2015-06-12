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

class MysqlConn
{
public:
	MysqlConn(void);
	virtual ~MysqlConn(void);

	bool	Connect(void);
	void	Disconnect(void);

	void	PrepareQuery(char* query_info);
	void	Execute(void);
	bool	Fetch(void);

	int32_t		GetInt(void);
private:
	sql::Driver*				driver_;
	sql::Connection*			conn_;
	sql::PreparedStatement*		pstmt_;
	sql::ResultSet*				resultset_;

};

}
}
}

#endif