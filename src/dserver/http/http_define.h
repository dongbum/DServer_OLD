#pragma once

// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

enum HTTP_STATUS_CODE : uint32_t
{
	HTTP_STATUS_OK						= 200,
	HTTP_STATUS_NOT_FOUND				= 404,
	HTTP_STATUS_PAYLOAD_TOO_LARGE		= 413,
	HTTP_STATUS_SERVER_ERROR			= 500,
	HTTP_STATUS_NOT_IMPLEMENTED			= 501,
	HTTP_STATUS_SERVICE_UNAVAILABLE		= 503,
	HTTP_STATUS_NOT_SUPPORTED			= 505,
};

const std::map<unsigned int, std::string> http_status_table =
{
	{ HTTP_STATUS_OK,					"200 OK" },
	{ HTTP_STATUS_NOT_FOUND,			"400 Not Found" },
	{ HTTP_STATUS_PAYLOAD_TOO_LARGE,	"413 Request Entity Too Large" },
	{ HTTP_STATUS_SERVER_ERROR,			"500 Server Error" },
	{ HTTP_STATUS_NOT_IMPLEMENTED,		"501 Not Implemented" },
	{ HTTP_STATUS_SERVICE_UNAVAILABLE,	"503 Service Unavailable" },
	{ HTTP_STATUS_NOT_SUPPORTED,		"505 HTTP Version Not Supported" },
};

const std::map<std::string, std::string> mapping_table =
{
	{ "gif",	"image/gif" },
	{ "htm",	"text/html" },
	{ "html",	"text/html" },
	{ "jpg",	"image/jpeg" },
	{ "png",	"image/png" }
};

struct HTTP_HEADER
{
	std::string name;
	std::string value;
};

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };

struct HTTP_RESPONSE
{
	HTTP_STATUS_CODE status;
	std::vector<HTTP_HEADER> headers;
	std::string content;

	void to_buffers(std::vector<boost::asio::const_buffer>& buffer)
	{
		headers.resize(2);
		headers[0].name = "Content-Type";
		headers[0].value = "text/html";
		headers[1].name = "Content-Length";
		headers[1].value = std::to_string(content.size());

		std::string http_status_message;

		std::map<unsigned int, std::string>::const_iterator iter = http_status_table.find(status);
		if (http_status_table.end() == iter)
			http_status_message = std::string("HTTP/1.1 500 Server Error") + "\r\n";
		else
			http_status_message = std::string("HTTP/1.1 ") + (iter->second) + "\r\n";

		buffer.push_back(boost::asio::buffer(http_status_message));
		buffer.push_back(boost::asio::buffer(crlf));

		for (size_t i = 0; i < headers.size(); ++i)
		{
			HTTP_HEADER& header = headers[i];
			buffer.push_back(boost::asio::buffer(header.name));
			buffer.push_back(boost::asio::buffer(name_value_separator));
			buffer.push_back(boost::asio::buffer(header.value));
			buffer.push_back(boost::asio::buffer(crlf));
		}
		buffer.push_back(boost::asio::buffer(crlf));
		buffer.push_back(boost::asio::buffer(content));
	};
};