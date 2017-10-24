#pragma once

#include "define.h"
#include "session/session_pool.h"
#include "http/http_server.h"


class Config;
class UserProtocol;
class Session;
class SessionPool;
class DServer : public std::enable_shared_from_this<DServer>
{
public :
	typedef boost::asio::io_service			IoService;
	typedef boost::asio::ip::tcp::endpoint	EndPoint;
	typedef boost::asio::ip::tcp::acceptor	Acceptor;
	typedef boost::asio::ip::tcp::socket	Socket;

	typedef std::shared_ptr<Session>		SessionPtr;

	DServer(std::string server_port, UserProtocol* user_protocol);
	virtual ~DServer(void);

	void Start(void);
	void Stop(void);

	void Accept(void);

	void AcceptHandler(SessionPtr session, const ErrorCode& error);
	void CloseHandler(SessionPtr session);
	void IOServiceHandler();

public:
	static std::shared_ptr<DServer> server_instance_ptr_;

	static void SetServerInstance(std::shared_ptr<DServer>& server_instance_ptr) { server_instance_ptr_ = server_instance_ptr; }
	static std::shared_ptr<DServer>& GetServerInstance(void) { return server_instance_ptr_; }

public:
	UserProtocol*			GetUserProtocol(void) { return user_protocol_; }

private:
	IoService				io_service_;
	Acceptor				acceptor_;
	boost::thread_group		io_thread_group_;

	SessionPool				session_pool_;

	int count_;

private:
	HTTPServer				http_server_;

private:
	UserProtocol*			user_protocol_;

};
