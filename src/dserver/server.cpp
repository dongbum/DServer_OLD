/*
 * server.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "server.h"
#include "work_thread_manager.h"

namespace dserver
{

// 생성자
DServer::DServer(std::string server_port)
:	session_(NULL)
,	acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
,	count_(0)
{
	// 세션을 필요한만큼 만들어서 큐에 넣는다.
	for (int i = 0; i < 8; i++)
	{
		Session* session = new Session(acceptor_.get_io_service(), this);
		// session_queue_.push(session);

		tbb_queue_.push(session);
	}

	IOServiceHandler();
}

// 소멸자
DServer::~DServer(void)
{

}

void DServer::IOServiceHandler(void)
{
	Session* new_session = NULL;

	// 큐에서 세션 한개를 뺀다.
	tbb_queue_.try_pop(new_session);

	// 그 세션에서 accept를 받는다.
	acceptor_.async_accept(
				new_session->GetSocket(),
				boost::bind(
						&DServer::AcceptHandler,
						this,
						new_session,
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

	IOServiceHandler();
}

// 시작
void DServer::Start(void)
{
	// 워커스레드 매니저 생성
	work_thread_manager_ = new WorkThreadManager(8);

	std::cout << "START" << std::endl;

	io_service_.run();
}

void DServer::Stop(void)
{

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
}

}
