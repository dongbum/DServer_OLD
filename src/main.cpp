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

int test(int a, int b)
{
	return a + b;
}

int main(void)
{
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
