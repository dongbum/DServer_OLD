#pragma once

enum HTTP_STATUS_CODE : uint32_t
{
	HTTP_STATUS_OK = 200,
	HTTP_STATUS_NOT_FOUND = 404,
	HTTP_STATUS_PAYLOAD_TOO_LARGE = 413,
	HTTP_STATUS_SERVER_ERROR = 500,
	HTTP_STATUS_NOT_IMPLEMENTED = 501,
	HTTP_STATUS_SERVICE_UNAVAILABLE = 503,
	HTTP_STATUS_NOT_SUPPORTED = 505,
};

class HTTPUtil : public boost::serialization::singleton<HTTPUtil>
{
public:
	HTTPUtil(void)
	{
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_OK, "200 OK"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_NOT_FOUND, "400 Not Found"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_PAYLOAD_TOO_LARGE, "413 Request Entity Too Large"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_SERVER_ERROR, "500 Server Error"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_NOT_IMPLEMENTED, "501 Not Implemented"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_SERVICE_UNAVAILABLE, "503 Service Unavailable"));
		http_status_table.insert(std::map<unsigned int, std::string>::value_type(HTTP_STATUS_NOT_SUPPORTED, "505 HTTP Version Not Supported"));

		mapping_table.insert(std::map<std::string, std::string>::value_type("gif", "image/gif"));
		mapping_table.insert(std::map<std::string, std::string>::value_type("htm", "text/html"));
		mapping_table.insert(std::map<std::string, std::string>::value_type("html", "text/html"));
		mapping_table.insert(std::map<std::string, std::string>::value_type("jpg", "image/jpeg"));
		mapping_table.insert(std::map<std::string, std::string>::value_type("png", "image/png"));
	};

	virtual ~HTTPUtil(void)
	{
		http_status_table.clear();
		mapping_table.clear();
	}

	std::string FindHttpMessage(HTTP_STATUS_CODE status)
	{
		std::map<unsigned int, std::string>::const_iterator iter = http_status_table.find(status);
		if (http_status_table.end() == iter)
			return std::string("HTTP/1.1 500 Server Error");
		else
			return std::string("HTTP/1.1 ") + std::string(iter->second);
	};
	
	std::string FindMapping(std::string extension)
	{
		std::map<std::string, std::string>::const_iterator iter = mapping_table.find(extension);
		if (mapping_table.end() == iter)
			return "text/plain";

		return iter->second;
	}

public:
	static HTTPUtil& GetMutableInstance(void) { return HTTPUtil::get_mutable_instance(); }

private:
	std::map<unsigned int, std::string> http_status_table;
	std::map<std::string, std::string> mapping_table;

};

#define HTTP_UTIL_INSTANCE HTTPUtil::GetMutableInstance()