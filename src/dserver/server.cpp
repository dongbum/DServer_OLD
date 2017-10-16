#include "server.h"
#include "session/session.h"


// 생성자
DServer::DServer(std::string server_port, UserProtocol* user_protocol)
	: acceptor_(io_service_, EndPoint(boost::asio::ip::tcp::v4(), boost::lexical_cast<int32_t>(server_port)))
	, count_(0)
	, user_protocol_(user_protocol)
{
	LL_DEBUG("Server port is %s", server_port.c_str());

	// 세션을 필요한만큼 만들어서 큐에 넣는다.

	int32_t max_session_count = boost::lexical_cast<int32_t>(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "MAX_SESSION_COUNT"));
	max_session_count = std::max(max_session_count, 100);

	/*
	for (int i = 0; i < max_session_count; i++)
	{
		SessionPtr session = SessionPtr(new Session(acceptor_.get_io_service(), this, user_protocol));
		// session_queue_.push(session);

		session_queue_.Push(session);
	}
	*/

	session_pool_.Init(acceptor_, this, user_protocol, max_session_count);

	LL_DEBUG("session_pool_ size : %d", session_pool_.Size());

	IOServiceHandler();
}

// 소멸자
DServer::~DServer(void)
{

}

void DServer::IOServiceHandler(void)
{
	SessionPtr new_session = nullptr;

	// 큐에서 세션 한개를 뺀다.
	new_session = session_pool_.GetSession();

	LL_DEBUG("session_pool_ try_pop() success. size : %d", session_pool_.Size());

	// 그 세션에서 accept를 받는다.
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

// 소켓 accept 핸들러
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

		// Accept가 되었다면 세션의 PostReceive로 처리를 넘긴다.

		count_++;
		LL_DEBUG("count_ : %d", count_);
		session->PostReceive();
	}
	else
	{
		LL_DEBUG("%d : %s", error.value(), error.message().c_str());

		// Accept에 문제가 있다면 이 세션을 종료한다.
		CloseHandler(session);
	}

	IOServiceHandler();
}


// 시작
void DServer::Start(void)
{
	LL_DEBUG("START");

	int32_t thread_count = boost::lexical_cast<int32_t>(CONFIG_MANAGER_INSTANCE.GetValue("DServer", "THREAD_COUNT"));
	if (0 == thread_count)
		thread_count = (std::max)(static_cast<int>(boost::thread::hardware_concurrency()), 1);

	LL_DEBUG("ThreadCount:[%d]", thread_count);

	// io_service 처리 멀티스레드화
	for (int i = 0; i < thread_count; ++i)
	{
		boost::thread io_thread(boost::bind(&boost::asio::io_service::run, &io_service_));
		io_thread_group_.add_thread(&io_thread);
	}

	// io_thread_group_.join_all();
}


void DServer::Stop(void)
{

}


// 세션 종료
void DServer::CloseHandler(SessionPtr session)
{
	LL_DEBUG("CloseHandler");

	// std::cout << "before push : session_queue_.size() : " << session_queue_.size() << std::endl;
	LL_DEBUG("before push : session_pool_.size() : %d", session_pool_.Size());

	LL_DEBUG("socket close");

	// 세션의 소켓을 닫는다.
	if (true == session->GetSocket().is_open())
	{
		ErrorCode ignored_error;
		session->GetSocket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignored_error);
		session->GetSocket().close();
	}

	// 세션큐에 다시 이 세션을 넣는다.
	// session_queue_.push(session);

	LL_DEBUG("push to session_queue_");

	// 세션큐에 다시 이 세션을 넣는다.
	session_pool_.ReleaseSession(session);

	// std::cout << "push end : session_queue_.size() : " << session_queue_.size() << std::endl;
	LL_DEBUG("push end : session_pool_.size() : %d", session_pool_.Size());
}
