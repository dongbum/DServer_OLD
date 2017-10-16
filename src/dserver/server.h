#pragma once

#include "define.h"
#include "session/session_pool.h"


class Config;
class UserProtocol;
class Session;
class SessionPool;
class DServer
{
public :
	typedef boost::asio::io_service			IoService;
	typedef boost::asio::ip::tcp::endpoint	EndPoint;
	typedef boost::asio::ip::tcp::acceptor	Acceptor;
	typedef boost::asio::ip::tcp::socket	Socket;

	typedef std::shared_ptr<Session>		SessionPtr;

	// 생성자
	DServer(std::string server_port, UserProtocol* user_protocol);

	// 소멸자
	virtual ~DServer(void);

	void Start(void);
	void Stop(void);

	void Accept(void);

	// 소켓 accept 핸들러
	void AcceptHandler(SessionPtr session, const ErrorCode& error);

	// 소켓 close 핸들러
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
	UserProtocol*			user_protocol_;

};
