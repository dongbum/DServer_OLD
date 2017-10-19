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
		LL_DEBUG("ErrorCode:[%d] ErrorMessage:[%s]", ec.value(), ec.message().c_str());

		if (boost::asio::error::not_found == ec)
		{
			response_status_code_ = HTTP_STATUS_PAYLOAD_TOO_LARGE;
			SendResponse();
			return;
		}
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
		LL_DEBUG("ErrorCode:[%d] ErrorMessage:[%s]", ec.value(), ec.message().c_str());

		if (boost::asio::error::not_found == ec)
		{
			response_status_code_ = HTTP_STATUS_PAYLOAD_TOO_LARGE;
			SendResponse();
			return;
		}
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
	

	std::string resource_file_path = request_resource_;

	if (false == boost::filesystem::exists(resource_file_path))
	{
		response_status_code_ = HTTP_STATUS_NOT_FOUND;
		return;
	}

	std::ifstream resource_fstream(resource_file_path, std::ifstream::binary);

	if (false == resource_fstream.is_open())
	{
		response_status_code_ = HTTP_STATUS_SERVER_ERROR;
		return;
	}

	resource_fstream.seekg(0, std::ifstream::end);
	resource_size_bytes_ = static_cast<size_t>(resource_fstream.tellg());

	resource_buffer_.reset(new char[resource_size_bytes_]);

	resource_fstream.seekg(std::ifstream::beg);
	resource_fstream.read(resource_buffer_.get(), resource_size_bytes_);

}



void HTTPService::SendResponse(void)
{
	socket_ptr_->shutdown(boost::asio::ip::tcp::socket::shutdown_receive);
	
	std::map<unsigned int, std::string>::const_iterator iter = http_status_table.find(response_status_code_);
	if (http_status_table.end() == iter)
	{
		Finish();
		return;
	}

	response_.status = response_status_code_;
	response_.to_buffers(response_buffer_);

	boost::asio::async_write(
		*socket_ptr_,
		response_buffer_,
		boost::bind(
			&HTTPService::ResponseHandler,
			this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred
		)
	);
}

void HTTPService::ResponseHandler(const ErrorCode & ec, size_t bytes_transferred)
{
	Finish();
}

void HTTPService::Finish(void)
{
	if (true == socket_ptr_->is_open())
	{
		ErrorCode ignored_error;
		socket_ptr_->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
		socket_ptr_->close();
	}

	delete this;
}

std::string HTTPService::extension_to_type(const std::string & extension)
{
	std::map<std::string, std::string>::const_iterator iter = mapping_table.find(extension);
	if (mapping_table.end() == iter)
		return "text/plain";

	return iter->second;
}
