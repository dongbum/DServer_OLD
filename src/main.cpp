/*
 * main.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "dserver/define.h"
#include "dserver/server.h"
#include "dserver/config/config.h"
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
	std::shared_ptr<dserver::database::mysql::MySQLConnPool> pool;

	pool = std::shared_ptr<dserver::database::mysql::MySQLConnPool>(new dserver::database::mysql::MySQLConnPool(thread_count));
	pool->Init();
	
	std::shared_ptr<dserver::database::mysql::MySQLConn> conn = pool->GetMySQLConn();
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
	dserver::database::mysql::MysqlConn conn;
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

	// 설정 파일을 로딩한다.
	dserver::config::Config config("./ServerConfig.ini");

	// 서버 객체 생성
	dserver::DServer server(config.GetValue("DServer", "PORT"));

	// 서버 초기화
	server.Init();

	// 서버 시작
	server.Start(config.GetValue("DServer", "THREAD_COUNT"));

	// 서버 종료
	std::cout << "서버 종료" << std::endl;

	getchar();

	return 0;
}