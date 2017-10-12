#pragma once

#include "../define.h"
#include "../header.h"
#include "../server.h"
#include "../work_queue.h"


class DServer;
class RequestWorkQueue;

class Session : public std::enable_shared_from_this<Session>
{
public :
	typedef std::shared_ptr<RequestWorkQueue>		RequestWorkQueuePtr;

	Session(IoService& io_service, DServer* server, UserProtocol* user_protocol);
	virtual ~Session();

	void		PostReceive(void);
	void		PostSend(const bool bImmediately, const int nSize, unsigned char* pData);
	void		Init(RequestWorkQueuePtr request_work_queue);

	Socket&		GetSocket();

private :
	void		HandleReceive(const ErrorCode& error, size_t bytes_transferred);
	void		HandleWrite(const ErrorCode& error, size_t bytes_transferred);

	std::deque< unsigned char* > send_data_queue_;
	unsigned char* send_data = nullptr;
	unsigned int send_data_size = 0;

	std::shared_ptr<DServer> server_;
	Socket socket_;

	unsigned char packet_buffer_[RECV_BUFFER_SIZE];
	int packet_buffer_size_;

	unsigned char recv_buffer_[RECV_BUFFER_SIZE];

	RequestWorkQueuePtr request_work_queue_;
	UserProtocol* user_protocol_;
};
