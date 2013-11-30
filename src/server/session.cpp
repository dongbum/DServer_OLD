/*
 * Session.cpp
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#include "session.h"

namespace dserver
{

Session::Session(IoService& io_service)
:	socket_(io_service)
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

void Session::PostHandler(void)
{
	char recv_buffer[1024] = {0,};

	socket_.async_read_some(
			boost::asio::buffer(recv_buffer),
			boost::bind(
					&Session::ReceiveHandler,
					this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
					)
			);

}

void Session::ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{

	}

	PostHandler();
}

void Session::WriteHandler(const boost::system::error_code& error, size_t bytes_transferred)
{

}

}
