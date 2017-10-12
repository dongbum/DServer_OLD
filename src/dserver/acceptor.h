#pragma once

#include "define.h"
#include "session/session.h"


class Acceptor
{
public:
	Acceptor(IoService& io_service, unsigned short port_num)
		: io_service_(io_service)
		, acceptor_(io_service_,
			EndPoint(
				boost::asio::ip::address_v4::any(),
				port_num
			))
		, is_stopped_(false)
	{

	}

	void Start(void)
	{
		acceptor_.listen();
		InitAccept();
	}

	void Stop(void)
	{
		is_stopped_.store(true);
	}

private:
	void InitAccept(void)
	{
		std::shared_ptr<Socket> socket(new Socket(io_service_));

		/*
		acceptor_.async_accept(
			new_session->GetSocket(),
			boost::bind(
				&DServer::AcceptHandler,
				this,
				new_session,
				boost::asio::placeholders::error
			)
		);
		*/
	}

	void AcceptHandler(const ErrorCode& ec, std::shared_ptr<Session> session_ptr)
	{
		if (0 == ec)
		{
			session_ptr->PostReceive();
		}
		else
		{
			LL_DEBUG("Error occured! ErrorCode:[%d]", ec.value());
		}

		if (false == is_stopped_.load())
		{
			InitAccept();
		}
		else
		{
			acceptor_.close();
		}
	}

private:
	IoService&						io_service_;
	boost::asio::ip::tcp::acceptor	acceptor_;
	std::atomic<bool>				is_stopped_;
};