#include "http_service.h"

HTTPService::HTTPService(std::shared_ptr<Socket> socket_ptr)
	: socket_ptr_(socket_ptr)
	, response_status_code_(HTTP_STATUS_OK)
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
		'\r\n',
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

		if (boost::asio::error::not_found == ec)
		{
			response_status_code_ = HTTP_STATUS_PAYLOAD_TOO_LARGE;
			SendResponse();
			return;
		}
	}
	else
	{
		Finish();
		return;
	}

	std::string request_line;
	std::istream request_stream(&request_);
	std::getline(request_stream, request_line, '\r');
	request_stream.get();

	std::string request_method;
	std::istringstream request_line_stream(request_line);
	request_line_stream >> request_method;

	if (0 != request_method.compare("GET"))
	{
		response_status_code_ = HTTP_STATUS_NOT_IMPLEMENTED;
		SendResponse();
		return;
	}

	request_line_stream >> request_resource_;

	std::string request_http_version;
	request_line_stream >> request_http_version;

	if (0 != request_http_version.compare("HTTP/1.1"))
	{
		response_status_code_ = HTTP_STATUS_NOT_SUPPORTED;
		SendResponse();
		return;
	}

	boost::asio::async_read_until(
		*socket_ptr_,
		request_,
		"\r\n\r\n",
		boost::bind(
			&HTTPService::HeaderReceiveHandler,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void HTTPService::HeaderReceiveHandler(const ErrorCode & ec, size_t bytes_transferred)
{
	if (0 != ec)
	{
		std::cout << "Error" << ec.value() << ec.message() << std::endl;

		if (boost::asio::error::not_found == ec)
		{
			response_status_code_ = HTTP_STATUS_PAYLOAD_TOO_LARGE;
			SendResponse();
			return;
		}
	}
	else
	{
		Finish();
		return;
	}

	std::istream request_stream(&request_);
	std::string header_name;
	std::string header_value;

	while (!request_stream.eof())
	{
		std::getline(request_stream, header_name, ':');
		
		if (!request_stream.eof())
		{
			std::getline(request_stream, header_value, '\r');
		}

		request_stream.get();
		request_header_[header_name] = header_value;
	}

	ProcessRequest();
	SendResponse();
}

void HTTPService::ProcessRequest(void)
{
	
}

void HTTPService::SendResponse(void)
{
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
