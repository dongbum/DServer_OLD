#include "base_protocol.h"

namespace dserver
{
namespace protocol
{

BaseProtocol::BaseProtocol(void)
{

}


BaseProtocol::~BaseProtocol(void)
{

}


void BaseProtocol::AddProtocol(uint32_t protocol_no, BaseProtocol::ProtocolFunction protocol_function)
{
	protocol_map.insert(BaseProtocol::ProtocolMap::value_type(protocol_no, protocol_function));
}

bool BaseProtocol::ExecuteProtocol(uint32_t protocol_no, unsigned char* data, unsigned int& data_length)
{
	// �������� �˻�
	BaseProtocol::ProtocolMap::iterator iter = protocol_map.find(protocol_no);
	if (iter == protocol_map.end())
		return false;

	// �������� ó�� �Լ� ����
	ProtocolFunction protocol_function = (*iter).second;

	protocol_function(protocol_no, data, data_length);

	return true;
}

}
}