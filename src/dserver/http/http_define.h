#pragma once

// http://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml


struct HTTP_HEADER
{
	std::string name;
	std::string value;
};

const char name_value_separator[] = { ':', ' ' };
const char crlf[] = { '\r', '\n' };
