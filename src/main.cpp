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

	// ���� ������ �ε��Ѵ�.
	dserver::config::Config config("./ServerConfig.ini");

	// ���� ��ü ����
	dserver::DServer server(config.GetValue("DServer", "PORT"));

	// ���� �ʱ�ȭ
	server.Init();

	// ���� ����
	server.Start(config.GetValue("DServer", "THREAD_COUNT"));

	// ���� ����
	std::cout << "���� ����" << std::endl;

	getchar();

	return 0;
}
