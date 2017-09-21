#include "user_protocol.h"


UserProtocol::UserProtocol(void)
{

}


UserProtocol::~UserProtocol(void)
{

}


void UserProtocol::Initialize(void)
{
	AddProtocol(UserProtocolNo::USER_PROTOCOL_ECHO, boost::bind(&UserProtocol::Echo, this, _1, _2, _3, _4));
}
