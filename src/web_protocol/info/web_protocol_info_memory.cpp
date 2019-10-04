#include "../web_protocol.h"

std::string WebProtocol::GetMemoryInfo(void)
{
	Json::Value root;
	root["description"] = "Get memory information.";
	Json::Value& memory_info_node = root["memory_info"];

#ifdef _WIN32
	SystemResourceMonitor::MemoryInfo memory_info = SystemResourceMonitor::GetMemoryInfo();

	Json::Value memory_node;

	memory_node["TotalPhyicalMemory"] = memory_info.phys_total;
	memory_node["TotalPhyicalCurrentUsed"] = memory_info.phys_current_used;
	memory_node["TotalPhyicalCurrentUsedByProcess"] = memory_info.phys_current_process;

	memory_node["TotalVirtualMemory"] = memory_info.virtual_total;
	memory_node["TotalVirtualCurrentUsed"] = memory_info.virtual_current_used;
	memory_node["TotalVirtualCurrentUsedByProcess"] = memory_info.virtual_current_process;

	memory_info_node.append(memory_node);
#endif

	return root.toStyledString();
}