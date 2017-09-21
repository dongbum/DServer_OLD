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


void Session::PostSend(const bool bImmediately, const int size, unsigned char* data)
{
	boost::system::error_code error;
	boost::asio::ip::tcp::endpoint endpoint = socket_.remote_endpoint(error);
	if (error)
	{
		LL_DEBUG("%s - error No: %d error Message: %s", __FUNCTION__, error.value(), error.message().c_str());

		while (send_data_queue_.empty() == false)
		{
			delete[] send_data_queue_.front();
			send_data_queue_.pop_front();
		}

		server_->CloseHandler(shared_from_this());
		return;
	}

	unsigned char* target_data = nullptr;
	unsigned int target_data_size = size + sizeof(Header);

	unsigned char* encrypted_data = nullptr;
	unsigned int encrypted_data_size = 0;

	unsigned char* send_data = nullptr;
	unsigned int send_data_size = 0;

	if (bImmediately == false)
	{
		target_data = new unsigned char[target_data_size];
		if (nullptr == target_data)
			LL_DEBUG("new error");

		Header header;
		header.identifier = 0xFFFF;
		header.length = static_cast<int16_t>(target_data_size);

		memcpy(target_data, &header, sizeof(HEADER));
		memcpy(target_data + sizeof(HEADER), data, size);

		send_data = new unsigned char[target_data_size];
		if (nullptr == send_data)
			LL_DEBUG("new error");

		memset(send_data, 0, target_data_size);
		memcpy(send_data, target_data, target_data_size);

		send_data_size = target_data_size;

		send_data_queue_.push_back(send_data);
		// send_data_queue_.push(send_data);
		LL_DEBUG("Send target data push : %d", send_data_queue_.size());

		delete[] target_data;
	}
	else
	{
		target_data = data;
		send_data = new unsigned char[size];
		if (nullptr == send_data)
			LL_DEBUG("new error");

		memset(send_data, 0, size);
		memcpy(send_data, data, size);

		send_data_size = size;

		send_data_queue_.push_back(send_data);
		//send_data_queue_.push(send_data);
	}

	if (bImmediately == false && send_data_queue_.size() > 1)
	{
		LL_DEBUG("bImmediately is false and send_data_queue.size : %d", send_data_queue_.size());
		return;
	}

	LL_DEBUG("Send Start. Send target data size : %d", send_data_size);

	if (send_data_size <= 0)
		LL_DEBUG("Send Start. Send target data size : %d", send_data_size);

	boost::asio::async_write(socket_, boost::asio::buffer(send_data, send_data_size),
		boost::bind(&Session::HandleWrite, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred)
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
void Session::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred)
{
	LL_DEBUG("Session::HandleWrite : bytes_transferred(%d)", bytes_transferred);

	unsigned char* next_data = nullptr;

	{
		// LockGuard lock(rw_mutex_);

		if (error)
		{
			LL_DEBUG("HandleWrite error : %d - message : %s", error.value(), error.message().c_str());
			return;
		}

		LL_DEBUG("Send Complete!!! bytes_transferred : %d", bytes_transferred);

		if (send_data_queue_.empty() == true)
			return;

		delete[] send_data_queue_.front();
		send_data_queue_.pop_front();

		/*
		unsigned char* front_data = nullptr;
		send_data_queue_.pop(front_data);
		delete[] front_data;
		*/

		LL_DEBUG("send_data_queue_ size : %d", send_data_queue_.size());

		if (send_data_queue_.empty() == false)
		{
			// send_data_queue_.pop(next_data);
			next_data = send_data_queue_.front();
			send_data_queue_.pop_front();

			LL_DEBUG("Found next data!!!");
		}
	}

	if (nullptr == next_data)
		return;

	Header* header = (Header*)next_data;

	PostSend(true, header->length, next_data);
}


}
