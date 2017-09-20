/*
 * Session.h
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#ifndef SESSION_H_
#define SESSION_H_

#include "../define.h"
#include "../header.h"
#include "../server.h"
#include "../work_queue.h"
#include "../../user_protocol/user_protocol.h"

namespace dserver
{

class DServer;
class WorkQueue;

class Session : public std::enable_shared_from_this<Session>
{
public :
	typedef std::shared_ptr<WorkQueue>		WorkQueuePtr;

	Session(IoService& io_service, dserver::DServer* server);
	virtual ~Session();

	void		PostHandler(void);
	void		Init(WorkQueuePtr work_queue);

	Socket&		GetSocket();

private :
	void		ReceiveHandler(const boost::system::error_code& error, size_t bytes_transferred);
	void		WriteHandler(const boost::system::error_code& error, size_t bytes_transferred);

	std::shared_ptr<dserver::DServer> server_;
	Socket socket_;

	unsigned char packet_buffer_[1024];
	int packet_buffer_size_;

	unsigned char recv_buffer_[1024];

	user_protocol::UserProtocol user_protocol_manager;
	WorkQueuePtr work_queue_;
};

}

#endif /* SESSION_H_ */
