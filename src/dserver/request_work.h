#pragma once

#include "define.h"
#include "server.h"
#include "session/session.h"


class DServer;
class Session;

class RequestWork
{
public:
	RequestWork(void);
	RequestWork(std::shared_ptr<Session> session, int32_t protocol_no, unsigned char buffer[], uint32_t length);
	virtual ~RequestWork(void);

	std::shared_ptr<Session>	GetSession(void);
	int32_t						GetProtocolNo(void);
	unsigned char*				GetData(void);
	uint32_t					GetDataLength(void);

private:
	std::shared_ptr<Session>	session_;
	int32_t						protocol_no_;
	unsigned char				buffer_[RECV_BUFFER_SIZE];
	uint32_t					data_length_;
};
