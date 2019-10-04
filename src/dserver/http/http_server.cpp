#include "http_server.h"

HTTPServer::HTTPServer(std::string server_port)
	: acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
{
	web_protocol_.Initialize();

	http_server_thread_ = boost::thread(boost::bind(&HTTPServer::IoServiceHandler, this));
}

HTTPServer::~HTTPServer(void)
{

}

void HTTPServer::Start(void)
{
	io_service_.run();
}

void HTTPServer::IoServiceHandler(void)
{
	std::shared_ptr<Socket> socket_ptr(new Socket(io_service_));

	acceptor_.async_accept(
		*socket_ptr,
		boost::bind(
			&HTTPServer::AcceptHandler,
			this,
			socket_ptr,
			boost::asio::placeholders::error
		)
	);
}

void HTTPServer::AcceptHandler(std::shared_ptr<Socket> socket_ptr, const ErrorCode& ec)
{
	if (0 == ec)
	{
		(new HTTPService(socket_ptr, &web_protocol_))->StartHandler();
	}
	else
	{
		LL_DEBUG("ErrorCode:[%d] ErrorMessage:[%s]", ec.value(), ec.message().c_str());
	}

	IoServiceHandler();
}
