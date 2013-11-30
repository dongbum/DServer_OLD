/*
 * server.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "server.h"



namespace dserver
{

// 생성자
DServer::DServer()
:	session_(NULL)
{

}

// 소멸자
DServer::~DServer(void)
{

}

// 서버를 초기화한다.
void DServer::Init(void)
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

// 소켓 accept 핸들러
void DServer::AcceptHandler(Session* session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "Client connected" << std::endl;

		session->PostHandler();
	}
}

}
