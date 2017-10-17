#pragma once

// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

enum HTTP_STATUS_CODE
{
	HTTP_STATUS_OK						= 200,
	HTTP_STATUS_NOT_FOUND				= 404,
	HTTP_STATUS_PAYLOAD_TOO_LARGE		= 413,
	HTTP_STATUS_SERVER_ERROR			= 500,
	HTTP_STATUS_NOT_IMPLEMENTED			= 501,
	HTTP_STATUS_SERVICE_UNAVAILABLE		= 503,
	HTTP_STATUS_NOT_SUPPORTED			= 505,
};