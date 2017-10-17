#pragma once

#include "../define.h"

class HTTPService
{
public:
	typedef boost::asio::streambuf	StreamBuf;

	HTTPService(std::shared_ptr<Socket> socket_ptr);
	virtual ~HTTPService(void);

	void StartHandler(void);
	void RequestHandler(const ErrorCode& ec, size_t bytes_transferred);
	std::string ProcessRequest(StreamBuf& request);
	void ResponseHandler(const ErrorCode& ec, size_t bytes_transferred);
	void Finish(void);

private:
	std::shared_ptr<Socket>		socket_ptr_;
	std::string					response_;
	StreamBuf					request_;
};