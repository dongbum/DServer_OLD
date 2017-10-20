#pragma once

class HTTPUtil
{
public:
	void URLParser(std::string input_url)
	{
		size_t st = input_url.find("://");
		std::cout << st << std::endl;
	};

private:
	std::string scheme;
	std::string ip;
	std::string port;
};
