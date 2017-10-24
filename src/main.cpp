/*
 * main.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "dserver/define.h"
#include "dserver/server.h"
#include "user_protocol/user_protocol.h"
#include "dserver/database/mysql/mysql_conn.h"
#include "dserver/database/mysql/mysql_conn_pool.h"

int test(int a, int b)
{
	return a + b;
}

int main(void)
{
	/*
	// MySQL 커넥션풀 테스트
	int32_t thread_count = 4;
	std::shared_ptr<MySQLConnPool> pool;

	pool = std::shared_ptr<MySQLConnPool>(new MySQLConnPool(thread_count));
	pool->Init();
	
	std::shared_ptr<MySQLConn> conn = pool->GetMySQLConn();
	conn->PrepareQuery("SELECT 19830419");
	conn->Execute();

	while (conn->Fetch())
	{
		int32_t a = conn->GetInt();

		std::cout << a << std::endl;
	}
	*/

	/*
	// MySQL 커넥션 테스트
	MysqlConn conn;
	conn.Connect();
	conn.PrepareQuery("SELECT 19830419");
	conn.Execute();

	if (conn.Fetch())
	{
		std::cout << conn.GetInt() << std::endl;
	}

	conn.Disconnect();
	return 0;
	*/

	/*
	boost::function<int(int, int)> bind_test = boost::bind(test, _1, _2);

	std::cout << bind_test(3, 5) << std::endl;
	std::cout << bind_test(4, 8) << std::endl;
	return 0;
	*/

	if (false == CONFIG_MANAGER_INSTANCE.Initialize("D:\\Work\\DServer.git\\vs_solution\\Bin\\ServerConfig.ini"))
		return 0;

	if (false == LOG_MANAGER_INSTANCE.Init())
		return 0;

	UserProtocol user_protocol;
	user_protocol.Initialize();

	std::shared_ptr<DServer> server(new DServer(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "PORT"), &user_protocol));
	DServer::SetServerInstance(server);
	server->Start();

	LL_DEBUG("Server Shutdown");

	getchar();

	return 0;
}