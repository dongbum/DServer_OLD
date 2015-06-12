#ifndef __C_MYSQL_CONN_POOL_H__
#define __C_MYSQL_CONN_POOL_H__

#include "../../define.h"
#include "mysql_conn.h"

namespace dserver
{
namespace database
{
namespace mysql
{


class MySQLConnPool
{
public:
	MySQLConnPool(int32_t& pool_count);
	virtual ~MySQLConnPool(void);

	bool			Init(void);

private:
	MySQLConn**		mysql_conn_;
	int32_t			pool_count_;
};


}
}
}

#endif