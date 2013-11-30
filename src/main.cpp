/*
 * main.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "dserver/server.h"

int main(void)
{
	dserver::DServer server;
	server.Init();

	std::cout << "서버 종료" << std::endl;

	getchar();

	return 0;
}
