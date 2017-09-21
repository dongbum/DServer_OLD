#pragma once

#include "../define.h"
#include "../header.h"
#include "../server.h"
#include "../work_queue.h"
#include "../../user_protocol/user_protocol.h"

namespace dserver
{

class DServer;
class RequestWorkQueue;

class Session : public std::enable_shared_from_this<Session>
{
public :
	typedef std::shared_ptr<RequestWorkQueue>		RequestWorkQueuePtr;

	Session(IoService& io_service, dserver::DServer* server);
	virtual ~Session();

	void		PostReceive(void);
	void		Init(RequestWorkQueuePtr request_work_queue);

	Socket&		GetSocket();

private :
	void		HandleReceive(const boost::system::error_code& error, size_t bytes_transferred);
	void		WriteHandler(const boost::system::error_code& error, size_t bytes_transferred);

	std::shared_ptr<dserver::DServer> server_;
	Socket socket_;

	unsigned char packet_buffer_[1024];
	int packet_buffer_size_;

	unsigned char recv_buffer_[1024];

	user_protocol::UserProtocol user_protocol_manager;
	RequestWorkQueuePtr request_work_queue_;
};

}
