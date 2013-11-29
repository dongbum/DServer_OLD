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

#include <boost/bind.hpp>

#include "define.h"
#include "session.h"

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
	virtual ~DServer(void);
private :
	IoService io_service_;
	Session* session_;

	void AcceptHandler(Session* session, const boost::system::error_code& error);
};

}

#endif /* SERVER_H_ */
