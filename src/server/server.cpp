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
	acceptor_.async_accept(session_->GetSocket(),
				boost::bind(AcceptHandler, this, session_, boost::asio::placeholders::error)
			);

	/*
	while (true)
	{
		char buffer[1024] = {0,};
		boost::system::error_code error_code;

		size_t len = socket_.read_some(boost::asio::buffer(buffer), error_code);
		std::cout << "len : " << len << std::endl;

		if (error_code)
		{
			if (error_code == boost::asio::error::eof)
			{
				std::cout << "클라이언트와 연결이 끊겼습니다." << std::endl;
			}
			else
			{
				std::cout << "ErrorNo : " << error_code.value() << " - ErrorMessage : " << error_code.message() << std::endl;
			}
			break;
		}
		else
		{
			std::cout << "클라이언트에서 받은 메시지 : " << &buffer[0] << std::endl;
			size_t msg_len = strlen(buffer);

			boost::system::error_code ignored_error;
			socket_.write_some(boost::asio::buffer(buffer, msg_len), ignored_error);

			std::cout << "클라이언트로 보낸 메시지 : " << &buffer[0] << std::endl;
		}
	}
	*/
}

DServer::~DServer(void)
{

}

void DServer::AcceptHandler(Session* session, const boost::system::error_code& error)
{

}

}
