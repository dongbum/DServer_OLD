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
DServer::DServer(std::string server_port)
:	session_(NULL)
,	acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
,	socket_(io_service_)
,	count_(0)
{
	// 세션을 필요한만큼 만들어서 큐에 넣는다.
	for (int i = 0; i < 8; i++)
	{
		Session* session = new Session(acceptor_.get_io_service(), this);
		// session_queue_.push(session);

		tbb_queue_.push(session);
	}
}

// 소멸자
DServer::~DServer(void)
{

}

// 시
void DServer::Start(void)
{
	// Accept를 받는다.
	Accept();

	std::cout << "START" << std::endl;

	io_service_.run();
}

void DServer::Stop(void)
{

}

void DServer::Accept(void)
{
	std::cout << "Accept" << std::endl;

	// std::cout << "session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "tbb_queue_.size() : " << tbb_queue_.unsafe_size() << std::endl;

	// 맨 앞에 있는 세션 하나를 꺼낸다.
	// session_ = session_queue_.front();
	// session_queue_.pop();

	// tbb 큐에서 꺼낸다.
	tbb_queue_.try_pop(session_);

	// 세션에 접속을 받도록 설정
	// 접속이 되면 AcceptHandler를 호출한다.
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

		// Accept에 문제가 있다면 이 세션을 종료한다.
		CloseHandler(session);
	}
}

// 세션 종료
void DServer::CloseHandler(Session* session)
{
	std::cout << "CloseHandler" << std::endl;

	// std::cout << "before push : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "before push : tbb_queue_.size() : " << tbb_queue_.unsafe_size() << std::endl;

	// 세션의 소켓을 닫는다.
	session->GetSocket().close();

	// 세션큐에 다시 이 세션을 넣는다.
	// session_queue_.push(session);

	// tbb 큐에 다시 이 세션을 넣는다.
	tbb_queue_.push(session);

	// std::cout << "push end : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "push end : tbb_queue_.size() : " << tbb_queue_.unsafe_size() << std::endl;

	// Accept를 받는다.
	Accept();
}

}
