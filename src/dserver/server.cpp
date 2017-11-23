#include "server.h"
#include "session/session.h"

std::shared_ptr<DServer> DServer::server_instance_ptr_;

DServer::DServer(std::string server_port, UserProtocol* user_protocol)
	: acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
	, user_protocol_(user_protocol)
	, http_server_(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "WEB_PORT"))
{
	acceptor_.set_option(Acceptor::reuse_address(true));

	LL_DEBUG("Server Port:[%s]", server_port.c_str());
	LL_DEBUG("WebServer Port:[%s]", CONFIG_MANAGER_INSTANCE.GetValue("DServer", "WEB_PORT").c_str());

	int32_t max_session_count = boost::lexical_cast<int32_t>(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "MAX_SESSION_COUNT"));
	max_session_count = std::max(max_session_count, 100);

	session_pool_.Init(acceptor_, this, user_protocol, max_session_count);

	LL_DEBUG("SessionPool Size:[%d]", session_pool_.Size());

	IOServiceHandler();
}


DServer::~DServer(void)
{

}


void DServer::IOServiceHandler(void)
{
	SessionPtr new_session = nullptr;
	new_session = session_pool_.GetSession();

	LL_DEBUG("SessionPool GetSession() success. Size:[%d]", session_pool_.Size());

	acceptor_.async_accept(
				new_session->GetSocket(),
				boost::bind(
						&DServer::AcceptHandler,
						this,
						new_session,
						boost::asio::placeholders::error
					)
				);
}


void DServer::AcceptHandler(SessionPtr session, const ErrorCode& error)
{
	LL_DEBUG("AcceptHandler START");

	if (false == acceptor_.is_open())
	{
		LL_DEBUG("Acceptor is close.");
		return;
	}

	if (!error)
	{
		LL_DEBUG("Client connected");

		session->PostReceive();
	}
	else
	{
		LL_DEBUG("%d : %s", error.value(), error.message().c_str());

		CloseHandler(session);
	}

	IOServiceHandler();
}


void DServer::Start(void)
{
	LL_DEBUG("START");

	int32_t thread_count = boost::lexical_cast<int32_t>(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "THREAD_COUNT"));
	if (0 == thread_count)
		thread_count = (std::max)(static_cast<int>(boost::thread::hardware_concurrency()), 1);

	LL_DEBUG("ThreadCount:[%d]", thread_count);

	for (int i = 0; i < thread_count; ++i)
	{
		boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
		io_thread_group_.add_thread(&io_thread);
	}

	http_server_.Start();
}


void DServer::Stop(void)
{

}


void DServer::CloseHandler(SessionPtr session)
{
	LL_DEBUG("CloseHandler");
	LL_DEBUG("before push : session_pool_.size() : %d", session_pool_.Size());
	LL_DEBUG("socket close");

	if (true == session->GetSocket().is_open())
	{
		ErrorCode ignored_error;
		session->GetSocket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
		session->GetSocket().close();
	}

	LL_DEBUG("push to session_queue_");

	session_pool_.ReleaseSession(session);

	LL_DEBUG("push end : session_pool_.size() : %d", session_pool_.Size());
}
