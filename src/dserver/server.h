/*
 * server.h
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#pragma once

#include "define.h"
#include "work_thread_manager.h"
#include "session/session.h"
#include "../user_protocol/user_protocol.h"

namespace dserver
{

class Session;
class Config;
class RequestWorkQueue;

class DServer
{
public :
	typedef boost::asio::io_service			IoService;
	typedef boost::asio::ip::tcp::endpoint	EndPoint;
	typedef boost::asio::ip::tcp::acceptor	Acceptor;
	typedef boost::asio::ip::tcp::socket	Socket;

	typedef std::shared_ptr<Session>		SessionPtr;
	typedef std::shared_ptr<RequestWorkQueue>		WorkQueuePtr;

	// 생성자
	DServer(std::string server_port);

	// 소멸자
	virtual ~DServer(void);

	void Init(void);
	void Start(std::string& thread_count);
	void Start(Config& config);
	void Stop(void);

	void Accept(void);

	// 소켓 accept 핸들러
	void AcceptHandler(SessionPtr session, const boost::system::error_code& error);

	// 소켓 close 핸들러
	void CloseHandler(SessionPtr session);

	void IOServiceHandler();
private :
	IoService				io_service_;
	Acceptor				acceptor_;
	SessionPtr				session_;
	WorkThreadManager*		work_thread_manager_;
	WorkQueuePtr			work_queue_;				// 세션에서 데이터 수신시 작업 넣어둘 큐

	// 세션들을 담아둘 큐
	// 이 큐에서 세션을 빼서 처리한다.
	// std::queue<SessionPtr> session_queue_;

	tbb::concurrent_bounded_queue<SessionPtr> tbb_queue_;

	int count_;
};

}