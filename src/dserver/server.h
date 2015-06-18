/*
 * server.h
 *
 *  Created on: 2013. 11. 26.
 *      Author: dongbum
 */

#ifndef SERVER_H_
#define SERVER_H_

#include "define.h"
#include "session.h"
#include "work_thread_manager.h"
#include "../user_protocol/user_protocol.h"

namespace dserver
{

class Session;
class Config;

class DServer
{
public :
	typedef boost::asio::io_service IoService;
	typedef boost::asio::ip::tcp::endpoint EndPoint;
	typedef boost::asio::ip::tcp::acceptor Acceptor;
	typedef boost::asio::ip::tcp::socket Socket;

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
	void AcceptHandler(std::shared_ptr<Session> session, const boost::system::error_code& error);

	// 소켓 close 핸들러
	void CloseHandler(std::shared_ptr<Session> session);

	void IOServiceHandler();
private :
	IoService io_service_;
	Acceptor acceptor_;
	std::shared_ptr<Session> session_;
	WorkThreadManager* work_thread_manager_;

	// 세션들을 담아둘 큐
	// 이 큐에서 세션을 빼서 처리한다.
	// std::queue<Session*> session_queue_;

	tbb::concurrent_queue< std::shared_ptr<Session> > tbb_queue_;

	int count_;
};

}

#endif /* SERVER_H_ */
