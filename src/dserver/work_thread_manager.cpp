/*
 * work_thread_manager.cpp
 *
 *  Created on: 2013. 12. 4.
 *      Author: dongbum
 */

#include "define.h"
#include "work_thread_manager.h"


WorkThreadManager::WorkThreadManager(const unsigned int thread_count)
{
	// 설정된 스레드갯수만큼
	for (unsigned int i = 0; i < thread_count; i++)
	{
		// 스레드를 생성한다.
		boost::thread thread(boost::bind(&WorkThreadManager::Run, this));

		// 스레드그룹에 추가한다.
		thread_group_.add_thread(&thread);
	}
}

WorkThreadManager::~WorkThreadManager(void)
{

}

void WorkThreadManager::Run(void)
{
	LOG_MANAGER.Write(LL_DEBUG, "WorkThreadManager::Run");
}
