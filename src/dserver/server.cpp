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

// ������
DServer::DServer(std::string server_port)
:	session_(nullptr)
,	acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
,	count_(0)
{
	// ������ �ʿ��Ѹ�ŭ ���� ť�� �ִ´�.
	for (int i = 0; i < 8; i++)
	{
		std::shared_ptr<Session> session = std::shared_ptr<Session>(new Session(acceptor_.get_io_service(), this));
		session->Init();
		// session_queue_.push(session);

		tbb_queue_.push(session);
	}

	IOServiceHandler();
}

// �Ҹ���
DServer::~DServer(void)
{

}

void DServer::IOServiceHandler(void)
{
	std::shared_ptr<Session> new_session = nullptr;

	// ť���� ���� �Ѱ��� ����.
	tbb_queue_.try_pop(new_session);

	// �� ���ǿ��� accept�� �޴´�.
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

// ���� accept �ڵ鷯
void DServer::AcceptHandler(std::shared_ptr<Session> session, const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout << "Client connected" << std::endl;

		// Accept�� �Ǿ��ٸ� ������ PostHandler�� ó���� �ѱ��.

		count_++;
		std::cout << "count_ : " << count_ << std::endl;
		session->PostHandler();
	}
	else
	{
		std::cout << error.value() << " : " << error.message() << std::endl;

		// Accept�� ������ �ִٸ� �� ������ �����Ѵ�.
		CloseHandler(session);
	}

	IOServiceHandler();
}

void DServer::Init(void)
{

}

// ����
void DServer::Start(std::string& thread_count)
{
	// ��Ŀ������ �Ŵ��� ����
	work_thread_manager_ = new WorkThreadManager(boost::lexical_cast<uint16_t>(thread_count));

	std::cout << "START" << std::endl;

	io_service_.run();
}


void DServer::Stop(void)
{

}


// ���� ����
void DServer::CloseHandler(std::shared_ptr<Session> session)
{
	std::cout << "CloseHandler" << std::endl;

	// std::cout << "before push : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "before push : tbb_queue_.size() : " << tbb_queue_.unsafe_size() << std::endl;

	// ������ ������ �ݴ´�.
	session->GetSocket().close();

	// ����ť�� �ٽ� �� ������ �ִ´�.
	// session_queue_.push(session);

	// tbb ť�� �ٽ� �� ������ �ִ´�.
	tbb_queue_.push(session);

	// std::cout << "push end : session_queue_.size() : " << session_queue_.size() << std::endl;
	std::cout << "push end : tbb_queue_.size() : " << tbb_queue_.unsafe_size() << std::endl;
}

}
