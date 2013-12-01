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

class DServer
{
public :
	typedef boost::asio::io_service IoService;
	typedef boost::asio::ip::tcp::endpoint EndPoint;
	typedef boost::asio::ip::tcp::acceptor Acceptor;
	typedef boost::asio::ip::tcp::socket Socket;

	// 생성자
	DServer();

	// 소멸자
	virtual ~DServer(void);

	// 서버를 초기화한다.
	void Init(std::string server_port);
private :
	IoService io_service_;
	Session* session_;

	// 소켓 accept 핸들러
	void AcceptHandler(Session* session, const boost::system::error_code& error);
};

}

#endif /* SERVER_H_ */
