/*
 * Session.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "define.h"
#include "server.h"

namespace dserver
{

class DServer;

class Session
{
public :
	Session(IoService& io_service, dserver::DServer* server);
	virtual ~Session();

	void PostHandler(void);

	Socket& GetSocket();
private :
	void ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred);
	void WriteHandler(const boost::system::error_code& error, size_t bytes_transferred);

	dserver::DServer* server_;
	Socket socket_;
	char recv_buffer_[1024];
};

}

#endif /* SESSION_H_ */
