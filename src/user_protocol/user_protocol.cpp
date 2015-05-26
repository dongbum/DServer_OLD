#include "user_protocol.h"

namespace user_protocol
{

UserProtocol::UserProtocol(void)
{

}


UserProtocol::~UserProtocol(void)
{

}


void UserProtocol::Initialize(void)
{
	AddProtocol(UserProtocolNo::USER_PROTOCOL_ECHO, boost::bind(&user_protocol::UserProtocol::Echo, this, _1, _2, _3));
}

}