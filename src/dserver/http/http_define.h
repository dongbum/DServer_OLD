#pragma once

// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml

enum HTTP_CODE
{
	HTTP_OK						= 200,
	HTTP_NOT_FOUND				= 404,
	HTTP_PAYLOAD_TOO_LARGE		= 413,
	HTTP_SERVER_ERROR			= 500,
	HTTP_SERVICE_UNAVAILABLE	= 503,
};