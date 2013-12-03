/*
 * main.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "dserver/config/config.h"
#include "dserver/server.h"

int main(void)
{
	// 설정 파일을 로딩한다.
	dserver::config::Config config("./ServerConfig.ini");

	// 서버 객체 생성
	dserver::DServer server(config.GetValue("DServer", "PORT"));

	// 서버 시작
	server.Start();

	// 서버 종료
	std::cout << "서버 종료" << std::endl;

	getchar();

	return 0;
}
