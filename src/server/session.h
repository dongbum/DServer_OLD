/*
 * Session.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "define.h"

namespace dserver
{

class Session
{
public :
	Session(IoService& io_service);
	virtual ~Session();

	Socket& GetSocket();
private :
	void ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred);
	void WriteHandler(const boost::system::error_code& error, size_t bytes_transferred);

	Socket socket_;
};

}

#endif /* SESSION_H_ */