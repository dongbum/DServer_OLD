#pragma once

#include "../define.h"
#include "http_define.h"
#include "http_util.h"

class HTTPResponse
{
public:
	HTTPResponse(void)
	{
		headers_.resize(2);
		headers_[0].name = "Content-Type";
		headers_[0].value = "text/html";
		headers_[1].name = "Content-Length";
		headers_[1].value = "0";
	};

	void SetContent(std::string& content) { content_ = content; };
	void SetStatus(HTTP_STATUS_CODE& status) { status_ = status; };

	void ToBuffers(std::vector<boost::asio::const_buffer>& buffer)
	{
		headers_.resize(2);
		headers_[0].name = "Content-Type";
		headers_[0].value = "text/html";
		headers_[1].name = "Content-Length";
		headers_[1].value = std::to_string(content_.size());

		http_status_message_ = HTTP_UTIL_INSTANCE.FindHttpMessage(status_);

		buffer.push_back(boost::asio::buffer(http_status_message_));
		buffer.push_back(boost::asio::buffer(crlf));

		for (size_t i = 0; i < headers_.size(); ++i)
		{
			HTTP_HEADER& header = headers_[i];
			buffer.push_back(boost::asio::buffer(header.name));
			buffer.push_back(boost::asio::buffer(name_value_separator));
			buffer.push_back(boost::asio::buffer(header.value));
			buffer.push_back(boost::asio::buffer(crlf));
		}
		buffer.push_back(boost::asio::buffer(crlf));
		buffer.push_back(boost::asio::buffer(content_));
	};

private:
	HTTP_STATUS_CODE			status_;
	std::vector<HTTP_HEADER>	headers_;
	std::string					content_;
	std::string					http_status_message_;

};