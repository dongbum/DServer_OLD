#pragma once

#include "../define.h"
#include "http_define.h"
#include "../../web_protocol/web_protocol.h"

class HTTPService
{
public:
	typedef boost::asio::streambuf	StreamBuf;

	HTTPService(std::shared_ptr<Socket> socket_ptr, WebProtocol* web_protocol);
	virtual ~HTTPService(void);

	void StartHandler(void);
	void RequestHandler(const ErrorCode& ec, size_t bytes_transferred);
	void HeaderReceiveHandler(const ErrorCode& ec, size_t bytes_transferred);
	void ProcessRequest(void);

	void SendResponse(void);
	void ResponseHandler(const ErrorCode& ec, size_t bytes_transferred);
	void Finish(void);

	std::string extension_to_type(const std::string& extension);

private:
	std::shared_ptr<Socket>		socket_ptr_;

	HTTP_RESPONSE				response_;
	HTTP_STATUS_CODE			response_status_code_;
	std::vector<boost::asio::const_buffer>	response_buffer_;

	StreamBuf					request_;
	std::string					request_resource_;
	std::map<std::string, std::string>		request_header_;

	size_t			resource_size_bytes_;
	std::unique_ptr<char[]>	resource_buffer_;

	WebProtocol*	web_protocol_;
};