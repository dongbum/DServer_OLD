#include "mysql_conn_pool.h"

namespace dserver
{
namespace database
{
namespace mysql
{


MySQLConnPool::MySQLConnPool(int32_t& pool_count)
	: pool_count_(pool_count)
{
	mysql_conn_ = new MySQLConn*[pool_count_];

	for (int32_t i = 0; i < pool_count_; ++i)
	{
		mysql_conn_[i] = nullptr;
	}
}


MySQLConnPool::~MySQLConnPool(void)
{

}


bool MySQLConnPool::Init(void)
{
	for (int32_t i = 0; i < pool_count_; ++i)
	{
		if (false == mysql_conn_[i]->Connect())
			return false;
	}

	return true;
}


}
}
}
