#pragma once

#include "../define.h"

#include "http_base_protocol.h"
#include "http_service.h"

class HTTPServer
{
public:
	HTTPServer(std::string server_port);
	virtual ~HTTPServer(void);

	void Start(void);

private:
	void IoServiceHandler(void);
	void AcceptHandler(std::shared_ptr<Socket> socket_ptr, const ErrorCode& ec);

private:
	IoService		io_service_;
	Acceptor		acceptor_;

	boost::thread	http_server_thread_;

	

};