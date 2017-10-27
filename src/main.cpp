/*
 * main.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "dserver/define.h"
#include "dserver/server.h"
#include "user_protocol/user_protocol.h"


int main(void)
{
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