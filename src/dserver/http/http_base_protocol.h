#pragma once

#include "../define.h"

class HTTPBaseProtocol
{
public:
	typedef boost::function<std::string(void)>				HTTPProtocolFunction;
	typedef std::map<std::string, HTTPProtocolFunction>		HTTPProtocolMap;

	HTTPBaseProtocol(void) {};
	virtual ~HTTPBaseProtocol(void) {};

	std::string ExecuteProtocol(std::string reques_uri)
	{
		HTTPBaseProtocol::HTTPProtocolMap::iterator iter = http_protocol_map.find(reques_uri);
		if (iter == http_protocol_map.end())
			return std::string();

		HTTPProtocolFunction protocol_function = (*iter).second;

		return protocol_function();
	};

protected:
	void AddProtocol(std::string request_uri, HTTPBaseProtocol::HTTPProtocolFunction protocol_function)
	{
		http_protocol_map.insert(HTTPBaseProtocol::HTTPProtocolMap::value_type(request_uri, protocol_function));
	};

private:
	HTTPProtocolMap http_protocol_map;
};