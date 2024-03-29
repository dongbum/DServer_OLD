#pragma once

#include "../define.h"
#include "../header.h"
#include "../server.h"


class DServer;
class UserProtocol;
class Session : public std::enable_shared_from_this<Session>
{
public :
	struct SEND_BUFFER_TAG {};

	typedef boost::singleton_pool<SEND_BUFFER_TAG, SEND_BUFFER_SIZE> SendBufferPool;

	Session(IoService& io_service, DServer* server, UserProtocol* user_protocol);
	virtual ~Session();

	void		PostReceive(void);
	void		PostSend(const bool bImmediately, const int nSize, unsigned char* pData);

	Socket&		GetSocket();

private :
	void		HandleReceive(const ErrorCode& error, size_t bytes_transferred);
	void		HandleWrite(const ErrorCode& error, size_t bytes_transferred, unsigned char* send_data);

	std::shared_ptr<DServer> server_;
	Socket socket_;

	unsigned char packet_buffer_[RECV_BUFFER_SIZE];
	int packet_buffer_size_;

	unsigned char recv_buffer_[RECV_BUFFER_SIZE];

	UserProtocol* user_protocol_;
	bool is_cgcii_test_;
};
