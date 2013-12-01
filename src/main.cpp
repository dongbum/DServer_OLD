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
	dserver::config::Config config("./ServerConfig.ini");

	dserver::DServer server;
	server.Init(config.GetValue("DServer", "PORT"));

	std::cout << "서버 종료" << std::endl;

	getchar();

	return 0;
}
