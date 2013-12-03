/*
 * Session.cpp
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#include "session.h"

namespace dserver
{

Session::Session(IoService& io_service, DServer* server)
:	socket_(io_service)
,	server_(server)
{
	// TODO Auto-generated constructor stub
}

Session::~Session()
{
	// TODO Auto-generated destructor stub
}

Socket& Session::GetSocket()
{
	return socket_;
}

// Accept가 되면 처리할 함수
void Session::PostHandler(void)
{
	std::cout << "Session::PostHandler" << std::endl;

	memset(recv_buffer_, 0, sizeof(recv_buffer_));

	// Recv를 한다.
	// ReceiveHandler로 처리를 넘긴다.
	socket_.async_read_some(
			boost::asio::buffer(recv_buffer_),
			boost::bind(
					&Session::ReceiveHandler,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
					)
			);

}

// Recv를 처리할 함수
void Session::ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	std::cout << "Session::ReceiveHandler : bytes_transferred(" << bytes_transferred << ")" << std::endl;

	if (error)
	{
		if (error == boost::asio::error::eof)
		{
			std::cout << "Client connection end" << std::endl;
		}
		else
		{
			std::cout << "Client connection error : " << error.value() << " - msg : " << error.message() << std::endl;
		}

		// Recv가 실패하거나 소켓의 연결이 끊겼다면 소켓을 닫도록 한다.
		server_->CloseHandler(this);
	}
	else
	{
		std::cout << "Session::async_write" << std::endl;

		// WriteHandler를 이용해 데이터를 전송한다.
		char send_buffer[1024] = {0,};
		boost::asio::async_write(
				socket_,
				boost::asio::buffer(send_buffer),
				boost::bind(
						&Session::WriteHandler,
						this,
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred
						)
				);

		// 다시 PostHandler를 호출해서 Recv를 받는다.
		PostHandler();
	}
}

// 데이터를 전송한다.
void Session::WriteHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	std::cout << "Session::WriteHandler : bytes_transferred(" << bytes_transferred << ")" << std::endl;
}

}
