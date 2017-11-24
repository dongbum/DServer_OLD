#pragma once

#include "../define.h"

template<typename T, unsigned int NEXT_SIZE = 32U, unsigned int MAX_POOL_SIZE = 0U>
class MemoryPool
{
public:
	static void* operator new(size_t size)
	{
		return boost::singleton_pool<T,
			sizeof(T),
			boost::default_user_allocator_new_delete,
			boost::details::pool::default_mutex,
			NEXT_SIZE,
			MAX_POOL_SIZE>::malloc();
	}

	static void operator delete(void* p)
	{
		boost::singleton_pool<T,
			sizeof(T),
			boost::default_user_allocator_new_delete,
			boost::details::pool::default_mutex,
			NEXT_SIZE,
			MAX_POOL_SIZE>::free(p);
	}
private:
};