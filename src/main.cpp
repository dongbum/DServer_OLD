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
	IoService io_service_;

	dserver::config::Config config("./ServerConfig.ini");

	dserver::DServer server(io_service_, config.GetValue("DServer", "PORT"));
	server.Start();

	io_service_.run();

	std::cout << "서버 종료" << std::endl;

	getchar();

	return 0;
}
