/*
 * Session.cpp
 *
 *  Created on: 2013. 11. 28.
 *      Author: dongbum
 */

#include "session.h"

namespace dserver
{

Session::Session(IoService& io_service, DServer* server)
:	socket_(io_service)
,	server_(server)
,	packet_buffer_size_(0)
{
	// TODO Auto-generated constructor stub
}

Session::~Session()
{
	// TODO Auto-generated destructor stub
}

Socket& Session::GetSocket()
{
	return socket_;
}

// Accept가 되면 처리할 함수
void Session::PostReceive(void)
{
	LL_DEBUG("Session::PostReceive START");

	memset(recv_buffer_, 0, sizeof(recv_buffer_));

	// Recv를 한다.
	// HandleReceive로 처리를 넘긴다.

	socket_.async_read_some(
			boost::asio::buffer(recv_buffer_),
			boost::bind(
					&Session::HandleReceive,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred
					)
			);
}

void Session::Init(RequestWorkQueuePtr request_work_queue)
{
	request_work_queue_ = request_work_queue;
	user_protocol_manager.Initialize();
}

// Recv를 처리할 함수
void Session::HandleReceive(const boost::system::error_code& error, size_t bytes_transferred)
{
	LL_DEBUG("Session::HandleReceive : bytes_transferred(%d)", bytes_transferred);

	if (error)
	{
		if (error == boost::asio::error::eof)
		{
			LL_DEBUG("Client connection end");
		}
		else
		{
			LL_DEBUG("Client connection error : %d - msg : %s", error.value(), error.message().c_str());
		}

		// Recv가 실패하거나 소켓의 연결이 끊겼다면 소켓을 닫도록 한다.
		server_->CloseHandler(shared_from_this());
	}
	else
	{
		memcpy(&packet_buffer_[packet_buffer_size_], recv_buffer_, bytes_transferred);

		uint32_t packet_data_size = packet_buffer_size_ + static_cast<uint32_t>(bytes_transferred);
		uint32_t read_data = 0;

		while (packet_data_size > 0)
		{
			// 받은 데이터가 헤더보다 작다면 중지
			if (packet_data_size < sizeof(Header))
				break;

			// 헤더구하기
			Header* header = (Header*)&packet_buffer_[read_data];

			if (header->GetTotalLength() <= packet_data_size)
			{
				LL_DEBUG("Header.TotalLength : %d", header->GetTotalLength());
				LL_DEBUG("Header.ProtocolNo  : %d", header->GetProtocolNo());
				LL_DEBUG("Header.DataLength  : %d", header->GetDataLength());

				// 데이터 처리
				request_work_queue_.get()->Push(RequestWork(shared_from_this(), &packet_buffer_[read_data], header->GetTotalLength()));

				packet_data_size -= header->GetTotalLength();
				read_data += header->GetTotalLength();
			}
			else
			{
				break;
			}
		}

		if (packet_data_size > 0)
		{
			if (packet_data_size > RECV_BUFFER_SIZE)
				packet_data_size = RECV_BUFFER_SIZE;

			char TempBuffer[RECV_BUFFER_SIZE] = { 0, };
			memcpy(&TempBuffer[0], &packet_buffer_[read_data], packet_data_size);
			memcpy(&packet_buffer_[0], &TempBuffer[0], packet_data_size);
		}

		packet_buffer_size_ = packet_data_size;

		// 다시 PostReceive를 호출해서 Recv를 받는다.
		PostReceive();
	}
}

// 데이터를 전송한다.
void Session::WriteHandler(const boost::system::error_code& error, size_t bytes_transferred)
{
	LL_DEBUG("Session::WriteHandler : bytes_transferred(%d)", bytes_transferred);
}


}
