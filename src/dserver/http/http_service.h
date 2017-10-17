#pragma once

#include "../define.h"
#include "http_define.h"

class HTTPService
{
public:
	typedef boost::asio::streambuf	StreamBuf;

	HTTPService(std::shared_ptr<Socket> socket_ptr);
	virtual ~HTTPService(void);

	void StartHandler(void);
	void RequestHandler(const ErrorCode& ec, size_t bytes_transferred);
	void HeaderReceiveHandler(const ErrorCode& ec, size_t bytes_transferred);
	void ProcessRequest(void);

	void SendResponse(void);
	void ResponseHandler(const ErrorCode& ec, size_t bytes_transferred);
	void Finish(void);

private:
	std::shared_ptr<Socket>		socket_ptr_;

	std::string					response_;
	HTTP_STATUS_CODE			response_status_code_;

	StreamBuf					request_;
	std::string					request_resource_;
	std::map<std::string, std::string>		request_header_;
};