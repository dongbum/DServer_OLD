#pragma once


#include "../define.h"
#include "log_message.h"

namespace dserver
{
namespace logging
{

class LogManager : public boost::serialization::singleton<LogManager>
{
public:
	LogManager(void);
	virtual ~LogManager(void);

	bool Init(std::string log_directory_name, std::string log_file_name);
	void Write(dserver::logging::LOG_LEVEL log_level, const char* format, ...);

private:
	void Run(void);

private:
	bool CreateLogDirectory(void);
	bool CreateLogFile(void);
	bool FindFile(const boost::filesystem::path& target_path, std::string file_name, OUT boost::filesystem::path& path);

public:
	static LogManager& GetMutableInstance(void) { return LogManager::get_mutable_instance(); }

private:
	tbb::concurrent_bounded_queue<LogMessage> log_queue_;
	boost::thread log_thread_;

	std::string		log_directory_name_;
	std::string		log_file_name_;

	boost::filesystem::ofstream		ofs_;

};

}
}

#define LOG_MANAGER_INSTANCE dserver::logging::LogManager::GetMutableInstance()
#define LOG_MANAGER dserver::logging::LogManager::GetMutableInstance()