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
DServer::DServer(IoService& io_service_, std::string server_port)
:	session_(NULL)
,	acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
,	socket_(io_service_)
,	count_(0)
{
	// 세션을 필요한만큼 만들어서 큐에 넣는다.
	for (int i = 0; i < 8; i++)
	{
		Session* session = new Session(acceptor_.get_io_service(), this);
		session_queue_.push(session);
	}
}

// 소멸자
DServer::~DServer(void)
{

}

void DServer::Start(void)
{
	Accept();
}

void DServer::Stop(void)
{

}

void DServer::Accept(void)
{
	std::cout << "Accept" << std::endl;

	std::cout << "session_queue_.size() : " << session_queue_.size() << std::endl;

	session_ = session_queue_.front();
	session_queue_.pop();

	acceptor_.async_accept(
			session_->GetSocket(),
			boost::bind(
					&DServer::AcceptHandler,
					this,
					session_,
					boost::asio::placeholders::error
				)
			);
}

// 소켓 accept 핸들러
void DServer::AcceptHandler(Session* session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "Client connected" << std::endl;

		// Accept가 되었다면 세션의 PostHandler로 처리를 넘긴다.

		count_++;
		std::cout << "count_ : " << count_ << std::endl;
		session->PostHandler();
	}
	else
	{
		std::cout << error.value() << " : " << error.message() << std::endl;
		CloseHandler(session);
	}
}

// 소켓 close 핸들러
void DServer::CloseHandler(Session* session)
{
	std::cout << "CloseHandler" << std::endl;

	std::cout << "before push : session_queue_.size() : " << session_queue_.size() << std::endl;

	session->GetSocket().close();

	session_queue_.push(session);

	std::cout << "push end : session_queue_.size() : " << session_queue_.size() << std::endl;

	Accept();
}

}
