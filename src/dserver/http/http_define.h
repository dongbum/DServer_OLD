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
