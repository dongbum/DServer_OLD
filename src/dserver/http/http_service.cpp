#include "http_service.h"

HTTPService::HTTPService(std::shared_ptr<Socket> socket_ptr)
	: socket_ptr_(socket_ptr)
{
}

HTTPService::~HTTPService(void)
{
}

void HTTPService::StartHandler(void)
{
	boost::asio::async_read_until(
		*socket_ptr_,
		request_,
		'\n',
		boost::bind(
			&HTTPService::RequestHandler,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void HTTPService::RequestHandler(const ErrorCode & ec, size_t bytes_transferred)
{
	if (0 != ec)
	{
		std::cout << "Error" << ec.value() << ec.message() << std::endl;

		Finish();
		return;
	}

	response_ = ProcessRequest(request_);

	boost::asio::async_write(
		*socket_ptr_,
		boost::asio::buffer(response_),
		boost::bind(
			&HTTPService::ResponseHandler,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

std::string HTTPService::ProcessRequest(StreamBuf& request)
{
	std::string response = "Response\n";
	return response;
}

void HTTPService::ResponseHandler(const ErrorCode& ec, size_t bytes_transferred)
{
	if (0 != ec)
	{
		std::cout << "Error" << ec.value() << ec.message() << std::endl;
	}

	Finish();
}



void HTTPService::Finish(void)
{
	delete this;
}
