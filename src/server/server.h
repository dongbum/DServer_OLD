/*
 * server.h
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>



namespace dserver
{

class DServer
{
public :
	typedef boost::asio::io_service IoService;
	typedef boost::asio::ip::tcp::endpoint EndPoint;
	typedef boost::asio::ip::tcp::acceptor Acceptor;
	typedef boost::asio::ip::tcp::socket Socket;

	DServer();
	DServer(int i);
	virtual ~DServer(void);
	int a_server;
private :
	IoService io_service_;
};

}

#endif /* SERVER_H_ */
