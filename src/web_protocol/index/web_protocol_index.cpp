#include "../web_protocol.h"

std::string WebProtocol::GetIndex(void)
{
	Json::Value root;
	root["description"] = "DServer";
	Json::Value& index_info_node = root["index_info"];

	Json::Value index_node;

	index_node["ServerStatus"] = "ONLINE";

	index_info_node.append(index_node);

	return root.toStyledString();
}