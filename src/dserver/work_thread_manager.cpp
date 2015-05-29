/*
 * work_thread_manager.cpp
 *
 *  Created on: 2013. 12. 4.
 *      Author: dongbum
 */

#include "work_thread_manager.h"


WorkThreadManager::WorkThreadManager(const unsigned int thread_count)
{
	// ������ �����尹����ŭ
	for (unsigned int i = 0; i < thread_count; i++)
	{
		// �����带 �����Ѵ�.
		boost::thread thread(boost::bind(&WorkThreadManager::Run, this));

		// ������׷쿡 �߰��Ѵ�.
		thread_group_.add_thread(&thread);
	}
}

WorkThreadManager::~WorkThreadManager(void)
{

}

void WorkThreadManager::Run(void)
{
	// std::cout << "WorkThreadManager::Run" << std::endl;
}