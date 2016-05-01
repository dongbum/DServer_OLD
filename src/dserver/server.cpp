/*
 * server.cpp
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#include "server.h"
#include "work_queue.h"
#include "work_thread_manager.h"

namespace dserver
{

// 생성자
DServer::DServer(std::string server_port)
:	session_(nullptr)
,	acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
,	count_(0)
{
	std::cout << "Server port is " << server_port << std::endl;

	// 작업을 넣을 큐 생성
	work_queue_ = WorkQueuePtr(new WorkQueue);

	// 세션을 필요한만큼 만들어서 큐에 넣는다.
	for (int i = 0; i < 8; i++)
	{
		SessionPtr session = SessionPtr(new Session(acceptor_.get_io_service(), this));
		session->Init(work_queue_);
		// session_queue_.push(session);

		tbb_queue_.push(session);
	}

	std::cout << "tbb_queue_ size : " << tbb_queue_.size() << std::endl;

	IOServiceHandler();
}

// 소멸자
DServer::~DServer(void)
{

}

void DServer::IOServiceHandler(void)
{
	SessionPtr new_session = nullptr;

	// 큐에서 세션 한개를 뺀다.
	if (false == tbb_queue_.try_pop(new_session))
	{
		std::cout << "Session try_pop failed." << std::endl;
		exit(1);
	}
	
	std::cout << "tbb_queue_ try_pop() success. size : " << tbb_queue_.size() << std::endl;

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
void DServer::AcceptHandler(SessionPtr session, const boost::system::error_code& error)
{
	std::cout << "AcceptHandler START" << std::endl;

	if (false == acceptor_.is_open())
	{
		std::cout << "Acceptor is close." << std::endl;
		return;
	}

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

void DServer::Init(void)
{

}

// 시작
void DServer::Start(std::string& thread_count)
{
	// 워커스레드 매니저 생성
	work_thread_manager_ = new WorkThreadManager(boost::lexical_cast<uint16_t>(thread_count));

	std::cout << "START" << std::endl;

	io_service_.run();
}


void DServer::Stop(void)
{

}


// 세션 종료
void DServer::CloseHandler(SessionPtr session)
{
	std::cout << "CloseHandler" << std::endl;

	// std::cout << "before push : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "before push : tbb_queue_.size() : " << tbb_queue_.size() << std::endl;

	std::cout << "socket close" << std::endl;

	// 세션의 소켓을 닫는다.
	if (true == session->GetSocket().is_open())
	{
		boost::system::error_code ignored_error;
		session->GetSocket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
		session->GetSocket().close();
	}

	// 세션큐에 다시 이 세션을 넣는다.
	// session_queue_.push(session);

	std::cout << "push to tbb_queue_" << std::endl;

	// tbb 큐에 다시 이 세션을 넣는다.
	tbb_queue_.push(session);

	// std::cout << "push end : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "push end : tbb_queue_.size() : " << tbb_queue_.size() << std::endl;
}

}
