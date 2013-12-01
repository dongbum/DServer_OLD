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

namespace dserver
{

class Session;

class DServer
{
public :
	typedef boost::asio::io_service IoService;
	typedef boost::asio::ip::tcp::endpoint EndPoint;
	typedef boost::asio::ip::tcp::acceptor Acceptor;
	typedef boost::asio::ip::tcp::socket Socket;

	// 생성자
	DServer(IoService& io_service_, std::string server_port);

	// 소멸자
	virtual ~DServer(void);

	void Start(void);
	void Stop(void);

	void Accept(void);

	// 소켓 accept 핸들러
	void AcceptHandler(Session* session, const boost::system::error_code& error);

	// 소켓 close 핸들러
	void CloseHandler(Session* session);
private :
	Acceptor acceptor_;
	Session* session_;
	Socket socket_;

	// 세션들을 담아둘 큐
	// 이 큐에서 세션을 빼서 처리한다.
	std::queue<Session*> session_queue_;

	int count_;
};

}

#endif /* SERVER_H_ */