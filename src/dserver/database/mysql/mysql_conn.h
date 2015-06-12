#ifndef _MYSQL_CONN_H_
#define _MYSQL_CONN_H_

#include "../../define.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

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
private:
};

}
}
}

#endif