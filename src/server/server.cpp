/*
 * server.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "server.h"



namespace dserver
{

DServer::DServer()
:	session_(NULL)
{
	EndPoint endpoint_(boost::asio::ip::tcp::v4(), 12341);
	Acceptor acceptor_(io_service_, endpoint_);
	Socket socket_(io_service_);

	session_ = new Session(acceptor_.get_io_service());
	acceptor_.async_accept(
			session_->GetSocket(),
			boost::bind(
					&DServer::AcceptHandler,
					this,
					session_,
					boost::asio::placeholders::error
				)
			);

	io_service_.run();
}

DServer::~DServer(void)
{

}

void DServer::AcceptHandler(Session* session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "Client connected" << std::endl;

		session->PostHandler();
	}
}

}
