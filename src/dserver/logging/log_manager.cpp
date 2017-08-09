#include "log_manager.h"


namespace dserver
{
namespace logging
{


LogManager::LogManager(void)
{

}


LogManager::~LogManager(void)
{
	if (ofs_.is_open())
		ofs_.close();
}


bool LogManager::Init(std::string log_directory_name, std::string log_file_name)
{
	log_directory_name_ = log_directory_name;
	log_file_name_ = log_file_name;

	if (false == CreateLogDirectory())
		return false;

	if (false == CreateLogFile())
		return false;

	log_thread_ = boost::thread(boost::bind(&LogManager::Run, this));

	return true;
}


void LogManager::Write(dserver::logging::LOG_LEVEL log_level, const char* format, ...)
{
	LogMessage log_message;

	va_list ap;
	va_start(ap, format);
	
	vsnprintf_s(log_message.GetBuffer(), MAX_LOG_MESSAGE_LENGTH, MAX_LOG_MESSAGE_LENGTH, format, ap);

	va_end(ap);

	log_queue_.try_push(log_message);
}


void LogManager::Run(void)
{
	while (true)
	{
		LogMessage log_message;

		if (log_queue_.try_pop(log_message))
		{
			std::cout << log_message.GetBuffer() << std::endl;

			ofs_ << std::string(log_message.GetBuffer()) << '\n';
		}
	}
}


bool LogManager::CreateLogDirectory(void)
{
	try
	{
		boost::filesystem::path path("./" + log_directory_name_);

		if (false == boost::filesystem::exists(path))
		{
			if (false == boost::filesystem::create_directory(path))
			{
				std::cout << "CreateDirectory failed." << std::endl;
				return false;
			}
		}
	}
	catch (boost::filesystem::filesystem_error& fe)
	{
		std::cout << fe.code() << " - " << fe.what() << std::endl;
		return false;
	}
	catch (boost::system::error_code& ec)
	{
		std::cout << ec.value() << " - " << ec.message() << std::endl;
		return false;
	}

	return true;
}


bool LogManager::CreateLogFile(void)
{
	try
	{
		boost::filesystem::path path("./" + log_directory_name_);

		boost::filesystem::path file_path;
		if (true == FindFile(path, log_file_name_, file_path))
		{
			ofs_.open(file_path / log_file_name_, boost::filesystem::ofstream::out | boost::filesystem::ofstream::app);

			// ofs_ << "text add" << '\n';

			// ofs_.close();
		}
		else
		{
			ofs_.open(path / log_file_name_);
			
			// ofs_ << "this is test" << '\n';

			// ofs_.close();
		}
	}
	catch (boost::filesystem::filesystem_error& fe)
	{
		std::cout << fe.code() << " - " << fe.what() << std::endl;
		return false;
	}
	catch (boost::system::error_code& ec)
	{
		std::cout << ec.value() << " - " << ec.message() << std::endl;
		return false;
	}

	return true;
}


bool LogManager::FindFile(const boost::filesystem::path& target_path, std::string file_name, OUT boost::filesystem::path& path)
{
	if (false == boost::filesystem::exists(target_path))
		return false;

	boost::filesystem::directory_iterator end_iter;
	for (boost::filesystem::directory_iterator iter(target_path); iter != end_iter; ++iter)
	{
		if (boost::filesystem::is_directory(iter->status()))
		{
			if (FindFile(iter->path(), file_name, path))
				return true;
		}
		else if (boost::filesystem::is_regular_file(iter->status()))
		{
			if (file_name == iter->path().leaf())
			{
				path = iter->path().parent_path();
				return true;
			}
		}
	}

	return false;
}


}
}